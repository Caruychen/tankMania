#include "Constants.hpp"
#include "Player.hpp"

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
  m_isHoldingFlag(false),
  m_hasCapturedFlag(false),
  m_spawnPos(configs.spawnPos),
  m_flagPos(configs.flagPos),
  m_zones(configs.zones),
  m_spawnRotation(configs.spawnRotation),
  m_respawnTime(0)
{
  /* Flag color is opposite to the Player's own color */
  this->_setupKeyBindings();
  this->_initHealth();
  this->m_flag = std::make_unique<Flag>(m_number == 1 ? "red" : "blue", m_flagPos);
}

Player::~Player()
{}

void Player::update(const Arena &arena)
{
  this->_respawn();
  this->updateProjectiles(arena);
  if (!this->m_isAlive)
    return;
  this->_updateFlag();
  this->_handleInput();
}

void Player::updateCollisions(
  std::unique_ptr<Player> &other,
  const Arena &arena)
{
  if (!this->m_isAlive)
    return;
  this->offsetCollision(other->getCollider());
  this->_checkCollision();
  this->_checkCollision(other);
  Entity::_checkCollision(arena);
}

const bool Player::checkPickup(std::unique_ptr<Heart> &heart)
{
  if (heart == nullptr)
    return false;
  if (!this->isColliding(heart->getCollider()))
    return false;
  if (this->m_health.current >= this->m_health.max)
    return false;
  return (this->_addHealth(), true);
}

const bool Player::checkPickup(std::unique_ptr<Projectile> &projectile)
{
  if (projectile == nullptr)
    return false;
  if (!this->isColliding(projectile->getCollider()))
    return false;
  if (this->m_ammunition.ammo.size() >= this->m_health.max)
    return false;
  return (this->_addAmmo(), true);
}

std::vector<Collider> Player::getZones() const
{
  return this->m_zones;
}

const sf::Keyboard::Key Player::getShootKey(void) const
{
  return this->m_shoot;
}

const unsigned int Player::getHealth(void) const
{
  return this->m_health.current;
}

const bool Player::isHoldingFlag(void) const
{
  return this->m_isHoldingFlag;
}

const bool Player::hasCapturedFlag(void) const
{
  return this->m_hasCapturedFlag;
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
}

void Player::_checkCollision(void)
{
  if (this->m_isHoldingFlag)
  {
    if (this->isCollidingGroup(this->m_zones))
      this->m_hasCapturedFlag = true;
    return ;
  }
  if (this->isColliding(this->m_flag->getCollider()))
    m_isHoldingFlag = true;
}

void Player::_checkCollision(std::unique_ptr<Player> &other)
{
  std::vector<std::unique_ptr<Projectile>> &projectiles = other->getProjectiles();
  for (int index = 0; index < projectiles.size(); ++index)
  {
    Collider collider = projectiles[index]->getCollider();
    if (!this->isColliding(collider))
      continue;
    this->_takeDamage();
    this->_dropFlag();
    this->_die();
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

void Player::_addHealth()
{
  if (this->m_health.current >= this->m_health.max)
    return ;
  this->m_health.hearts[this->m_health.current]->setAlive(true);
  this->m_health.hearts[this->m_health.current]->resetTexture();
  this->m_health.current++;
}

void Player::_takeDamage()
{
  if (this->m_health.current <= 0)
    return;
  this->m_health.current--;
  this->m_health.hearts[this->m_health.current]->setAlive(false);
  this->m_health.hearts[this->m_health.current]->resetTexture();
}

void Player::_die()
{
  const float offsetX = m_number == 1 ? -this->getSize().x : this->getSize().x;
  this->setRotation(this->m_spawnRotation);
  this->setPos(sf::Vector2f(ARENA_WIDTH / 2 + offsetX, ARENA_HEIGHT + 50));
  this->m_isAlive = false;
}

void Player::_respawn()
{
  if (this->m_isAlive)
    return ;
  this->m_respawnTime += this->m_elapsed->asSeconds();
  if (this->m_respawnTime <= RESPAWN_TIME)
    return ;
  this->m_isAlive = true;
  this->setPos(this->m_spawnPos);
  this->m_respawnTime = 0;
}

void Player::_updateFlag(void)
{
  auto &flag = this->m_flag;
  if (!this->m_isHoldingFlag)
    return ;
  flag->setPos(this->m_sprite.getPosition());
  flag->setRotation(this->m_sprite.getRotation());
}

void Player::_dropFlag(void)
{
  auto &flag = this->m_flag;
  flag->setPos(this->m_flagPos);
  flag->setRotation(0);
  this->m_isHoldingFlag = false;
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(this->m_sprite, states);
  target.draw(*this->m_flag);
  for (auto &heart : this->m_health.hearts)
    target.draw(*heart, states);
  for (auto &ammo : this->m_ammunition.ammo)
    target.draw(*ammo, states);
  for (auto &projectile : this->m_projectiles)
    target.draw(*projectile, states);
  if (this->m_ammunition.ammo.size() >= this->m_health.max)
    target.draw(this->m_ammunition.stateText);
}
