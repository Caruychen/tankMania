#include "Entity.hpp"
#include <iostream>

Entity::Entity(
  const std::string &texturePath,
  const sf::Vector2f &pos,
  const float &rotation,
  const sf::Vector2f &scale,
  const int &incrementSpeed,
  sf::Time *elapsed) :
  m_incrementSpeed(incrementSpeed), m_rotationSpeed(200), m_elapsed(elapsed),
  Collider(&this->m_sprite)
{
  /* 
   * Load texture, set sprite and origin 
  * This assuees that the texture is a square
   * */
  if (!this->m_texture.loadFromFile(texturePath))
    std::cerr << "Error loading texture: " << texturePath << std::endl;
  int size = std::min(this->m_texture.getSize().x, this->m_texture.getSize().y);
  this->m_sprite.setTextureRect(sf::IntRect(0, 0, size, size));
  this->m_sprite.setTexture(this->m_texture);
  this->m_sprite.setPosition(pos);
  this->m_sprite.setOrigin(size / 2, size / 2);
  this->m_sprite.setScale(scale.x, scale.y);
  this->initCollider();
  this->m_sprite.setRotation(rotation);
}

Entity::~Entity()
{}

void Entity::move(const int direction)
{
  if (this->m_elapsed == nullptr)
    return;
  const float speed = this->m_incrementSpeed * this->m_elapsed->asSeconds();
  const float angle = this->m_sprite.getRotation() * M_PI / 180;
  const float x = direction * speed * sin(angle);
  const float y = -direction * speed * cos(angle);
  this->m_sprite.move(x, y);
}

void Entity::rotate(const int direction)
{
  if (this->m_elapsed == nullptr)
    return;
  const float speed = this->m_rotationSpeed * this->m_elapsed->asSeconds();
  this->m_sprite.rotate(direction * speed);
}

void Entity::setScale(sf::Vector2f scale)
{
  this->m_sprite.setScale(scale);
  this->initCollider();
}

void Entity::setPos(sf::Vector2f pos)
{
  this->m_sprite.setPosition(pos);
  this->initCollider();
}

void Entity::setRotation(float rotation)
{
  this->m_sprite.setRotation(rotation);
  this->initCollider();
}

sf::Vector2f Entity::getSize() const
{
  sf::FloatRect rect = this->m_sprite.getLocalBounds();
  const sf::Vector2f scale = this->m_sprite.getScale();
  return {rect.width * scale.x, rect.height * scale.y};
}

sf::Vector2f Entity::getPos() const
{
  return this->m_sprite.getPosition();
}

void Entity::_checkCollision(const Arena &arena)
{
  this->_boundInArena(arena);
  this->_offsetWallCollisions(arena.getWalls());
}

void Entity::_boundInArena(const Arena &arena)
{
  sf::FloatRect spriteBounds = this->m_sprite.getGlobalBounds();
  const float widthOffset = spriteBounds.width / 2 + BOUNDING_BUFFER;
  const float heightOffset = spriteBounds.height / 2 + BOUNDING_BUFFER;
  const sf::Vector2f &pos = this->m_sprite.getPosition();

  if (spriteBounds.left < 0)
    this->m_sprite.setPosition(widthOffset, pos.y);
  else if (spriteBounds.left + spriteBounds.width > arena.getSize().x)
    this->m_sprite.setPosition(arena.getSize().x - widthOffset, pos.y);
  if (spriteBounds.top < 0)
    this->m_sprite.setPosition(pos.x, heightOffset);
  else if (spriteBounds.top + spriteBounds.height > arena.getSize().y)
    this->m_sprite.setPosition(pos.x, arena.getSize().y - heightOffset);
}

void Entity::_offsetWallCollisions(std::vector<sf::FloatRect> walls)
{
  for (sf::FloatRect wall: walls)
  {
    Collider wallCollider = Collider(wall);
    this->offsetCollision(wallCollider);
  }
}

bool Entity::_isCollidingBoundary(const Arena &arena) const
{
  sf::FloatRect spriteBounds = this->m_sprite.getGlobalBounds();
  return (
    spriteBounds.left < 0 ||
    spriteBounds.top < 0 ||
    spriteBounds.left + spriteBounds.width > arena.getSize().x ||
    spriteBounds.top + spriteBounds.height > arena.getSize().y);
}

bool Entity::_isCollidingWalls(std::vector<sf::FloatRect> walls)
{
  for (sf::FloatRect wall: walls)
  {
    Collider wallCollider = Collider(wall);
    if (this->isColliding(wallCollider))
      return true;
  }
  return false;
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(this->m_sprite, states);
}
