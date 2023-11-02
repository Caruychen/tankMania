#include "Heart.hpp"
#include <iostream>

Heart::Heart(
  const bool &isAlive,
  const sf::Vector2f &pos) :
  m_isAlive(isAlive),
  Entity(
    "Heart",
    "assets/health/hearts.png",
    pos,
    sf::Vector2f(HEART_SCALE, HEART_SCALE),
    1,
    nullptr)
{
  this->resetTexture();
  this->m_sprite.setOrigin(0, 0);
}

Heart::~Heart()
{}

void Heart::setAlive(const bool &isAlive)
{
  this->m_isAlive = isAlive;
}

void Heart::resetTexture(void)
{
  this->m_sprite.setTextureRect(sf::IntRect(
    TEXTURE_SIZE * this->m_isAlive,
    0,
    TEXTURE_SIZE,
    TEXTURE_SIZE));
}
