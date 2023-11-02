#include "Tank.hpp"

Tank::Tank(
  const std::string &name,
  const std::string &texturePath,
  const sf::Vector2f &pos,
  const int &incrementSpeed,
  sf::Time *elapsed) :
  Entity(
    name,
    texturePath,
    pos,
    sf::Vector2f(TANK_SCALE, TANK_SCALE),
    incrementSpeed,
    elapsed)
{}

Tank::~Tank()
{}

void Tank::fire()
{}
