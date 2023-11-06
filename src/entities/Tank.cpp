#include "Constants.hpp"
#include <iostream>
#include "Tank.hpp"

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
  this->_initAmmoText();
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
  for (auto &ammo : this->m_ammunition.ammo)
  {
    sf::Vector2f currentPos = ammo->getPos();
    ammo->setPos({currentPos.x - AMMO_DISPLAY_PADDING, currentPos.y});
  }
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
  unsigned int ammoCount = this->m_ammunition.ammo.size();
  if (ammoCount >= this->m_ammunition.max)
    return;
  float padding = AMMO_DISPLAY_PADDING;
  float y = ARENA_HEIGHT + padding;
  float x = ARENA_WIDTH / 2;
  x += this->m_number == 1 ? -padding * (ammoCount + 1): padding * (ammoCount + 1);
  this->m_ammunition.ammo.push_back(
    std::make_unique<Projectile>(sf::Vector2f(x, y), 0, this->m_elapsed));
}

void Tank::_initAmmo()
{
  this->m_ammunition.max = MAX_AMMO;
  this->_addAmmo();
}

void Tank::_initAmmoText()
{
  sf::Text *text = &this->m_ammunition.stateText;

  if(!this->m_ammunition.stateFont.loadFromFile("assets/fonts/ArcadeClassic.ttf"))
    throw std::runtime_error("Could not load font");
  text->setString("Max Reached!");
  text->setCharacterSize(14);
  text->setFont(this->m_ammunition.stateFont);
  text->setFillColor(sf::Color::White);
  sf::FloatRect textRect = text->getLocalBounds();
  float x = this->m_number == 1 ?
    ARENA_WIDTH / 2 - textRect.width - 6:
    ARENA_WIDTH / 2 + 6;
  text->setPosition(x, ARENA_HEIGHT + AMMO_DISPLAY_PADDING + 1);
}
