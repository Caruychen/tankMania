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
  this->_initHealth();
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
  const bool ownZone = this->isCollidingGroup(this->m_zones);
  const bool otherZone = this->isCollidingGroup(other->getZones());
}

void Player::takeDamage()
{
  if (this->m_health.current <= 0)
    return;
  this->m_health.current--;
  this->m_health.hearts[this->m_health.current]->setAlive(false);
  this->m_health.hearts[this->m_health.current]->resetTexture();
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

void Player::_initHealth()
{
  this->m_health.current = INITIAL_HEALTH;
  this->m_health.max = MAX_HEALTH;
  float textureSpacing = HEART_TEXTURE_SIZE * 4;
  const float scaledWidth = HEART_TEXTURE_SIZE * HEART_SCALE / 2;
  const float padding = 10;

  for (unsigned int i = 0; i < this->m_health.max; i++)
  {
    float increment = i * scaledWidth * 2 + scaledWidth + padding;
    float heartX = this->m_number == 1 ? increment : ARENA_WIDTH - increment;
    float heartY = ARENA_HEIGHT + scaledWidth + padding;
    this->m_health.hearts.push_back(std::unique_ptr<Heart>(
      new Heart(
        i < m_health.current,
        sf::Vector2f(heartX, heartY))));
  }
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(this->m_sprite, states);
  for (auto &heart : this->m_health.hearts)
    target.draw(*heart, states);
}
