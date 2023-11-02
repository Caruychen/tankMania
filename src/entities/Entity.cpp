#include "Entity.hpp"
#include <iostream>

Entity::Entity(
  const std::string &name,
  const std::string &texturePath,
  const sf::Vector2f &pos,
  const sf::Vector2f &scale,
  const int &incrementSpeed,
  sf::Time *elapsed) :
  m_name(name), m_incrementSpeed(incrementSpeed), m_rotationSpeed(200), m_elapsed(elapsed),
  Collider(&this->m_sprite)
{
  if (!this->m_texture.loadFromFile(texturePath))
    std::cerr << "Error loading texture: " << texturePath << std::endl;
  this->m_sprite.setTexture(this->m_texture);
  this->m_sprite.setPosition(pos);
  this->m_sprite.setOrigin(
    this->m_texture.getSize().x / 2,
    this->m_texture.getSize().y / 2);
  this->m_sprite.setScale(scale.x, scale.y);
  this->initCollider();
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

void Entity::checkBoundaryCollisions(const Arena &arena)
{
  this->updateCollider();
  this->boundInArena(arena);
  this->offsetWallCollisions(arena.getWalls());
}

void Entity::boundInArena(const Arena &arena)
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

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(this->m_sprite, states);
}
