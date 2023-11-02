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
  this->m_sprite.setOrigin(
    this->m_texture.getSize().x / 4,
    this->m_texture.getSize().y / 2);
}

Heart::~Heart()
{}

void Heart::setAlive(const bool &isAlive)
{
  this->m_isAlive = isAlive;
}

void Heart::resetTexture(void)
{
  int textureWidth = this->m_texture.getSize().x / 2;
  int textureHeight = this->m_texture.getSize().y;
  this->m_sprite.setTextureRect(sf::IntRect(
    textureWidth * this->m_isAlive,
    0,
    textureWidth,
    textureHeight));
}
