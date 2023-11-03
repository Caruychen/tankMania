#include "Tank.hpp"
#include <iostream>

Tank::Tank(
  const unsigned int &number,
  const std::string &texturePath,
  const sf::Vector2f &pos,
  const float &rotation,
  const int &incrementSpeed,
  sf::Time *elapsed) :
  Entity(
    texturePath,
    pos,
    rotation,
    sf::Vector2f(TANK_SCALE, TANK_SCALE),
    incrementSpeed,
    elapsed),
  m_number(number)
{
  this->_initAmmo();
}

Tank::~Tank()
{}

void Tank::shoot()
{
  if (this->m_ammunition.ammo.empty())
    return;
  auto &ammo = this->m_ammunition.ammo[0];
  ammo->setRotation(this->m_sprite.getRotation());
  ammo->setPos(this->m_sprite.getPosition());

  this->m_projectiles.push_back(std::move(ammo));
  this->m_ammunition.ammo.erase(this->m_ammunition.ammo.begin());
}

std::vector<std::unique_ptr<Projectile>> &Tank::getProjectiles()
{
  return this->m_projectiles;
}

void Tank::updateProjectiles(const Arena &arena)
{
  for (int index = 0; index < this->m_projectiles.size(); ++index)
  {
    if (this->m_projectiles[index]->checkCollisions(arena))
      this->deleteProjectile(index);
  }
  for (auto &projectile : this->m_projectiles)
      projectile->move(1);
}

void Tank::deleteProjectile(int index)
{
  if (index < 0 || index >= this->m_projectiles.size())
    return;
  this->m_projectiles.erase(this->m_projectiles.begin() + index);
}

void Tank::_addAmmo()
{
  if (this->m_ammunition.ammo.size() >= this->m_ammunition.max)
    return;
  float padding = 10;
  float y = ARENA_HEIGHT + padding;
  float x = ARENA_WIDTH / 2;

  x += this->m_number == 1 ? - padding : padding;
  this->m_ammunition.ammo.push_back(
    std::make_unique<Projectile>(
      1, sf::Vector2f(x, y), 0, this->m_elapsed));
}

void Tank::_initAmmo()
{
  this->m_ammunition.max = MAX_AMMO;
  this->_addAmmo();
}
