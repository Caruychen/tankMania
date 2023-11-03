#include "Player.hpp"
#include <iostream>

Player::Player(
  const unsigned int &number,
  const std::string &texturePath,
  const PlayerConfigs configs,
  sf::Time *elapsed) :
  Tank(
    number,
    texturePath,
    configs.spawnPos,
    configs.spawnRotation,
    MOVEMENT_SPEED,
    elapsed),
  m_number(number),
  m_isAlive(true),
  m_spawnPos(configs.spawnPos),
  m_flagPos(configs.flagPos),
  m_zones(configs.zones),
  m_spawnRotation(configs.spawnRotation)
{
  this->_setupKeyBindings();
  this->_initHealth();
}

Player::~Player()
{}

void Player::update(const Arena &arena)
{
  this->_respawn();
  if (!this->m_isAlive)
    return;
  this->_handleInput();
  this->updateProjectiles(arena);
}

void Player::checkCollisions(
  std::unique_ptr<Player> &other,
  const Arena &arena)
{
  if (!this->m_isAlive)
    return;
  this->offsetCollision(other->getCollider());
  this->_checkCollisionsZone(other);
  this->_checkCollisionsBoundary(arena);
  this->_checkCollisionsProjectile(other);
}

const bool Player::checkCollisionsHeart(std::unique_ptr<Heart> &heart)
{
  if (heart == nullptr)
    return false;
  if (!this->isColliding(heart->getCollider()))
    return false;
  return this->_addHealth();
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

void Player::_handleInput(void)
{
  if (sf::Keyboard::isKeyPressed(this->m_forward))
    this->move(1);
  else if (sf::Keyboard::isKeyPressed(this->m_backward))
    this->move(-1);
  if (sf::Keyboard::isKeyPressed(this->m_left))
    this->rotate(-1);
  else if (sf::Keyboard::isKeyPressed(this->m_right))
    this->rotate(1);
  if (sf::Keyboard::isKeyPressed(this->m_shoot))
    this->shoot();
}

void Player::_checkCollisionsZone(std::unique_ptr<Player> &other)
{
  const bool ownZone = this->isCollidingGroup(this->m_zones);
  const bool otherZone = this->isCollidingGroup(other->getZones());
}

void Player::_checkCollisionsProjectile(std::unique_ptr<Player> &other)
{
  std::vector<std::unique_ptr<Projectile>> &projectiles = other->getProjectiles();
  for (int index = 0; index < projectiles.size(); ++index)
  {
    Collider collider = projectiles[index]->getCollider();
    if (!this->isColliding(collider))
      continue;
    this->_takeDamage();
    this->m_isAlive = false;
    this->setPos(sf::Vector2f(ARENA_WIDTH / 2, ARENA_HEIGHT + 20));
    this->setRotation(this->m_spawnRotation);
    other->deleteProjectile(index);
    return ;
  }
}

void Player::_initHealth()
{
  this->m_health.current = INITIAL_HEALTH;
  this->m_health.max = MAX_HEALTH;
  float textureSpacing = HEART_TEXTURE_SIZE * 4;
  const float scaledWidth = HEART_TEXTURE_SIZE * DEFAULT_HEART_SCALE / 2;
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

const bool Player::_addHealth()
{
  if (this->m_health.current >= this->m_health.max)
    return false;
  this->m_health.hearts[this->m_health.current]->setAlive(true);
  this->m_health.hearts[this->m_health.current]->resetTexture();
  this->m_health.current++;
  return true;
}

void Player::_takeDamage()
{
  if (this->m_health.current <= 0)
    return;
  this->m_health.current--;
  this->m_health.hearts[this->m_health.current]->setAlive(false);
  this->m_health.hearts[this->m_health.current]->resetTexture();
}

void Player::_respawn()
{
  static float seconds;

  if (this->m_isAlive)
    return ;
  seconds += this->m_elapsed->asSeconds();
  if (seconds <= RESPAWN_TIME)
    return ;
  this->m_isAlive = true;
  this->setPos(this->m_spawnPos);
  seconds = 0;
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(this->m_sprite, states);
  for (auto &heart : this->m_health.hearts)
    target.draw(*heart, states);
  for (auto &ammo : this->m_ammunition.ammo)
    target.draw(*ammo, states);
  for (auto &projectile : this->m_projectiles)
    target.draw(*projectile, states);
}
