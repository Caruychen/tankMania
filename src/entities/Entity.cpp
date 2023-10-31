#include "Entity.hpp"
#include <iostream>

Entity::Entity(
  const std::string &name,
  const std::string &texturePath,
  const sf::Vector2f &pos,
  const int &incrementSpeed,
  sf::Time *elapsed) :
  m_name(name), m_incrementSpeed(incrementSpeed), m_rotationSpeed(200), m_elapsed(elapsed)
{
  this->m_texture.loadFromFile(texturePath);
  this->m_sprite.setTexture(this->m_texture);
  this->m_sprite.setPosition(pos);
  this->m_sprite.setOrigin(
    this->m_texture.getSize().x / 2,
    this->m_texture.getSize().y / 2);
}

Entity::~Entity()
{}

void Entity::moveForward()
{
  float angle = this->_getAngleRadians();
  float x = sin(angle) * this->_getMoveSpeed();
  float y = cos(angle) * this->_getMoveSpeed();
  this->m_sprite.move(x, -y);
}

void Entity::moveBackward()
{

  float angle = this->_getAngleRadians();
  float x = sin(angle) * this->_getMoveSpeed();
  float y = cos(angle) * this->_getMoveSpeed();
  this->m_sprite.move(-x, y);
}

void Entity::rotateLeft()
{
  this->m_sprite.rotate(-this->_getRotationSpeed());
}

void Entity::rotateRight()
{
  this->m_sprite.rotate(this->_getRotationSpeed());
}

void Entity::updateBounds(const Arena &arena)
{
  this->_boundInArena(arena);
  this->_boundAgainstWalls(arena);
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(this->m_sprite, states);
}

const float Entity::_getMoveSpeed() const
{
  return this->m_incrementSpeed * this->m_elapsed->asSeconds();
}

const float Entity::_getRotationSpeed() const
{
  return this->m_rotationSpeed * this->m_elapsed->asSeconds();
}

const float Entity::_getAngleRadians() const
{
  return this->m_sprite.getRotation() * M_PI / 180;
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

void Entity::_boundAgainstWalls(const Arena &arena)
{
  sf::FloatRect spriteBounds = this->m_sprite.getGlobalBounds();
  const float widthOffset = spriteBounds.width / 2 + BOUNDING_BUFFER;
  const float heightOffset = spriteBounds.height / 2 + BOUNDING_BUFFER;
  const sf::Vector2f &pos = this->m_sprite.getPosition();
  const std::vector<sf::FloatRect> arenaWalls = arena.getWalls();
  float widthOverlap;
  float heightOverlap;

  for (sf::FloatRect wall: arenaWalls)
  {
    if (wall.contains(spriteBounds.left, spriteBounds.top))
    {
      std::cout << "test" << std::endl;
      widthOverlap = wall.left + wall.width - spriteBounds.left;
      heightOverlap = wall.top + wall.height - spriteBounds.top;
      if (widthOverlap < heightOverlap)
        this->m_sprite.setPosition(wall.left + wall.width + widthOffset, pos.y);
      else 
        this->m_sprite.setPosition(pos.x, wall.top + wall.height + heightOffset);
    }
    else if (wall.contains(spriteBounds.left, spriteBounds.top + spriteBounds.height))
    {
      std::cout << "test" << std::endl;
      widthOverlap = wall.left + wall.width - spriteBounds.left;
      heightOverlap = spriteBounds.top + spriteBounds.height - wall.top;
      if (widthOverlap < heightOverlap)
        this->m_sprite.setPosition(wall.left + wall.width + widthOffset, pos.y);
      else
        this->m_sprite.setPosition(pos.x, wall.top - heightOffset);
    }
    else if (wall.contains(spriteBounds.left + spriteBounds.width, spriteBounds.top))
    {
      std::cout << "test" << std::endl;
      widthOverlap = spriteBounds.left + spriteBounds.width - wall.left;
      heightOverlap = wall.top + wall.height - spriteBounds.top;
      if (widthOverlap < heightOverlap)
        this->m_sprite.setPosition(wall.left - widthOffset, pos.y);
      else
        this->m_sprite.setPosition(pos.x, wall.top + wall.height + heightOffset);
    }
    else if (wall.contains(spriteBounds.left + spriteBounds.width, spriteBounds.top + spriteBounds.height))
    {
      std::cout << "test" << std::endl;
      widthOverlap = spriteBounds.left + spriteBounds.width - wall.left;
      heightOverlap = spriteBounds.top + spriteBounds.height - wall.top;
      if (widthOverlap < heightOverlap)
        this->m_sprite.setPosition(wall.left - widthOffset, pos.y);
      else
        this->m_sprite.setPosition(pos.x, wall.top - heightOffset);
    }
  }
}
