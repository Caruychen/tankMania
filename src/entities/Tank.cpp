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

void Tank::handleInput(const Window &window)
{
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    this->moveForward();
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    this->moveBackward();
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    this->rotateLeft();
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    this->rotateRight();
  this->boundInWindow(window);
}
