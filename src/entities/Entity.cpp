#include "Entity.hpp"
#include <iostream>

Entity::Entity(
  const std::string &name,
  const std::string &texturePath,
  const sf::Vector2f &pos,
  sf::Time *elapsed) :
  m_name(name), m_incrementSpeed(200), m_rotationSpeed(200), m_elapsed(elapsed)
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
  float angle = this->_getAngle();
  float x = sin(angle) * this->_getMoveSpeed();
  float y = cos(angle) * this->_getMoveSpeed();
  this->m_sprite.move(x, -y);
}

void Entity::moveBackward()
{

  float angle = this->_getAngle();
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

const float Entity::_getAngle() const
{
  return this->m_sprite.getRotation() * M_PI / 180;
}
