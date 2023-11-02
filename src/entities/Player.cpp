#include "Player.hpp"
#include <iostream>

Player::Player(
  const unsigned int &number,
  const std::string &texturePath,
  const sf::Vector2f &pos,
  sf::Time *elapsed) :
  Tank("Player " + std::to_string(number), texturePath, pos, MOVEMENT_SPEED, elapsed),
  m_number(number)
{
  if (number == 1)
    this->m_sprite.setRotation(0);
  else if (number == 2)
    this->m_sprite.setRotation(0);
  this->_setupKeyBindings();
}

Player::~Player()
{}

void Player::handleInput(const Arena &arena)
{
  if (sf::Keyboard::isKeyPressed(this->m_forward))
    this->move(1);
  else if (sf::Keyboard::isKeyPressed(this->m_backward))
    this->move(-1);
  if (sf::Keyboard::isKeyPressed(this->m_left))
    this->rotate(-1);
  else if (sf::Keyboard::isKeyPressed(this->m_right))
    this->rotate(1);
  this->updateEntity(arena);
}

void Player::_setupKeyBindings()
{
  this->m_forward = m_number == 1 ? (sf::Keyboard::Key) P1::UP : (sf::Keyboard::Key) P2::UP;
  this->m_backward = m_number == 1 ? (sf::Keyboard::Key) P1::DOWN : (sf::Keyboard::Key) P2::DOWN;
  this->m_left = m_number == 1 ? (sf::Keyboard::Key) P1::LEFT : (sf::Keyboard::Key) P2::LEFT;
  this->m_right = m_number == 1 ? (sf::Keyboard::Key) P1::RIGHT : (sf::Keyboard::Key) P2::RIGHT;
  this->m_shoot = m_number == 1 ? (sf::Keyboard::Key) P1::SHOOT : (sf::Keyboard::Key) P2::SHOOT;
}
