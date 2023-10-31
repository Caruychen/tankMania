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
    this->m_sprite.setRotation(90);
  else if (number == 2)
    this->m_sprite.setRotation(270);
  this->_setupKeyBindings();
}

Player::~Player()
{}

void Player::handleInput(const Arena &arena)
{
  if (sf::Keyboard::isKeyPressed(this->m_forward))
    this->moveForward();
  else if (sf::Keyboard::isKeyPressed(this->m_backward))
    this->moveBackward();
  if (sf::Keyboard::isKeyPressed(this->m_left))
    this->rotateLeft();
  else if (sf::Keyboard::isKeyPressed(this->m_right))
    this->rotateRight();
  this->boundInArena(arena);
}

void Player::_setupKeyBindings()
{
  this->m_forward = m_number == 1 ? (sf::Keyboard::Key) P1::UP : (sf::Keyboard::Key) P2::UP;
  this->m_backward = m_number == 1 ? (sf::Keyboard::Key) P1::DOWN : (sf::Keyboard::Key) P2::DOWN;
  this->m_left = m_number == 1 ? (sf::Keyboard::Key) P1::LEFT : (sf::Keyboard::Key) P2::LEFT;
  this->m_right = m_number == 1 ? (sf::Keyboard::Key) P1::RIGHT : (sf::Keyboard::Key) P2::RIGHT;
  this->m_shoot = m_number == 1 ? (sf::Keyboard::Key) P1::SHOOT : (sf::Keyboard::Key) P2::SHOOT;
}
