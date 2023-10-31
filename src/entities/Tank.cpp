#include "Tank.hpp"

Tank::Tank(
  const std::string &name,
  const std::string &texturePath,
  const sf::Vector2f &pos,
  const int &incrementSpeed,
  sf::Time *elapsed) :
  Entity(name, texturePath, pos, incrementSpeed, elapsed)
{
  this->m_sprite.setScale(0.3f, 0.3f);
}

Tank::~Tank()
{}

void Tank::fire()
{}
