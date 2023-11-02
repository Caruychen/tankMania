#include "Player.hpp"

Player::Player(
  const unsigned int &number,
  const std::string &texturePath,
  const PlayerConfigs configs,
  sf::Time *elapsed) :
  Tank("Player " + std::to_string(number),
    texturePath,
    configs.spawnPos,
    MOVEMENT_SPEED,
    elapsed),
  m_number(number),
  m_spawnPos(configs.spawnPos),
  m_flagPos(configs.flagPos),
  m_zones(configs.zones),
  m_spawnRotation(configs.spawnRotation)
{
  this->m_sprite.setRotation(configs.spawnRotation);
  this->_setupKeyBindings();
}

Player::~Player()
{}

void Player::handleInput(void)
{
  if (sf::Keyboard::isKeyPressed(this->m_forward))
    this->move(1);
  else if (sf::Keyboard::isKeyPressed(this->m_backward))
    this->move(-1);
  if (sf::Keyboard::isKeyPressed(this->m_left))
    this->rotate(-1);
  else if (sf::Keyboard::isKeyPressed(this->m_right))
    this->rotate(1);
}

void Player::checkCollisions(std::unique_ptr<Player> &other)
{
  this->updateCollider();
  this->offsetCollision(other->getCollider());
  this->checkZoneCollision(other);
}

void Player::checkZoneCollision(std::unique_ptr<Player> &other)
{
  const bool collidingZoneOne = this->isCollidingGroup(this->m_zones);
  const bool collidingZoneTwo = this->isCollidingGroup(other->getZones());
}

std::vector<Collider> Player::getZones() const
{
  return this->m_zones;
}

void Player::_setupKeyBindings()
{
  this->m_forward = m_number == 1 ? (sf::Keyboard::Key) P1::UP : (sf::Keyboard::Key) P2::UP;
  this->m_backward = m_number == 1 ? (sf::Keyboard::Key) P1::DOWN : (sf::Keyboard::Key) P2::DOWN;
  this->m_left = m_number == 1 ? (sf::Keyboard::Key) P1::LEFT : (sf::Keyboard::Key) P2::LEFT;
  this->m_right = m_number == 1 ? (sf::Keyboard::Key) P1::RIGHT : (sf::Keyboard::Key) P2::RIGHT;
  this->m_shoot = m_number == 1 ? (sf::Keyboard::Key) P1::SHOOT : (sf::Keyboard::Key) P2::SHOOT;
}
