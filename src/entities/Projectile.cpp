#include "Projectile.hpp"

Projectile::Projectile(
  unsigned int type,
  const sf::Vector2f &pos,
  const float &rotation,
  const sf::Vector2f &scale,
  sf::Time *elapsed) :
  Entity(
    "assets/projectiles/bullet" + std::to_string(type) + ".png",
    pos,
    rotation,
    scale,
    400,
    elapsed)
{}

Projectile::~Projectile()
{}

bool Projectile::checkCollisions(const Arena &arena)
{
  return (this->_isCollidingBoundary(arena) || this->_isCollidingWalls(arena.getWalls()));
}
