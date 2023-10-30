#include "Tank.hpp"

Tank::Tank(
  const std::string &name,
  const std::string &texturePath,
  const sf::Vector2f &pos,
  sf::Time *elapsed) :
  Entity(name, texturePath, pos, elapsed)
{}

Tank::~Tank()
{}

void Tank::handleInput()
{
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    this->moveForward();
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    this->moveBackward();
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    this->rotateLeft();
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    this->rotateRight();
}
