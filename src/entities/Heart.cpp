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
  this->m_sprite.setTexture(this->m_texture);
  this->m_sprite.setOrigin(0, 0);
  //this->m_sprite.setTextureRect(sf::IntRect(0, 0, 13, 13));
}

Heart::~Heart()
{}
