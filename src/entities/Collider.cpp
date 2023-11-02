#include "Collider.hpp"
#include <cmath>
#include <numbers>
#include <iostream>

Collider::Collider() : m_spritePtr(nullptr)
{}

Collider::Collider(sf::Sprite *spritePtr) : m_spritePtr(spritePtr)
{}

Collider::Collider(const sf::FloatRect &wall)
{
  sf::Vector2f localCenter = {wall.width / 2, wall.height / 2};
  this->m_localCorners.push_back({-localCenter.x, -localCenter.y});
  this->m_localCorners.push_back({localCenter.x, -localCenter.y});
  this->m_localCorners.push_back({localCenter.x, localCenter.y});
  this->m_localCorners.push_back({-localCenter.x, localCenter.y});
  this->m_globalCorners.push_back({wall.left, wall.top});
  this->m_globalCorners.push_back({wall.left + wall.width, wall.top});
  this->m_globalCorners.push_back({wall.left + wall.width, wall.top + wall.height});
  this->m_globalCorners.push_back({wall.left, wall.top + wall.height});
  this->m_pos = {wall.left + localCenter.x, wall.top + localCenter.y};
}

Collider::~Collider()
{}

void Collider::initCollider()
{
  if (this->m_spritePtr == nullptr)
    return;
  sf::Vector2f origin = this->m_spritePtr->getOrigin();
  sf::FloatRect rect = this->m_spritePtr->getLocalBounds();
  const sf::Vector2f scale = this->m_spritePtr->getScale();

  origin = {origin.x * scale.x, origin.y * scale.y};
  rect.width *= scale.x;
  rect.height *= scale.y;
  this->m_localCorners.push_back({rect.left - origin.x, rect.top - origin.y});
  this->m_localCorners.push_back({rect.width - origin.x, rect.top - origin.y});
  this->m_localCorners.push_back({rect.width - origin.x, rect.height - origin.y});
  this->m_localCorners.push_back({rect.left - origin.x, rect.height - origin.y});
  this->m_globalCorners.push_back({rect.left - origin.x, rect.top - origin.y});
  this->m_globalCorners.push_back({rect.width - origin.x, rect.top - origin.y});
  this->m_globalCorners.push_back({rect.width - origin.x, rect.height - origin.y});
  this->m_globalCorners.push_back({rect.left - origin.x, rect.height - origin.y});
  this->m_pos = this->m_spritePtr->getPosition();
}

void Collider::updateCollider()
{
  if (this->m_spritePtr == nullptr)
    return;
  const std::vector<sf::Vector2f> lCorners = this->m_localCorners;
  const sf::Vector2f pos = this->m_spritePtr->getPosition();
  const float angle = this->m_spritePtr->getRotation() * M_PI / 180;

  for (int index = 0; index < this->m_globalCorners.size(); ++index)
  {
    this->m_globalCorners[index].x =
      pos.x + lCorners[index].x * cos(angle) - lCorners[index].y * sin(angle);
    this->m_globalCorners[index].y =
      pos.y + lCorners[index].x * sin(angle) + lCorners[index].y * cos(angle);
  }
  this->m_pos = pos;
}

Collider Collider::getCollider() const
{
  return *this;
}

void Collider::offsetWallCollisions(std::vector<sf::FloatRect> walls)
{
  if (this->m_spritePtr == nullptr)
    return;
  for (sf::FloatRect wall: walls)
  {
    Collider wallCollider = Collider(wall);
    this->offsetCollision(wallCollider);
  }
}

const bool Collider::isCollidingGroup(std::vector<Collider> colliders) const
{
  if (this->m_spritePtr == nullptr)
    return false;
  for (Collider collider: colliders)
  {
    if (this->isColliding(collider))
      return true;
  }
  return false;
}

void Collider::offsetCollision(const Collider &other)
{
  sf::Vector2f offset = {0, 0};
  if (!this->isColliding(other, &offset))
    return;
  this->m_spritePtr->move(offset);
  this->updateCollider();
}

const bool Collider::isColliding(const Collider &other, sf::Vector2f *offset) const
{
  float overlap = INFINITY;
  sf::Vector2f vecDistance;
  float scalarDistance;

  if (!(this->_intersects(other, &overlap) && other._intersects(*this, &overlap)))
    return false;
  if (offset == nullptr)
    return true;
  vecDistance = { other.m_pos.x - this->m_pos.x, other.m_pos.y - this->m_pos.y };
  scalarDistance = sqrtf(vecDistance.x * vecDistance.x + vecDistance.y * vecDistance.y);
  *offset = {
    -overlap * vecDistance.x / scalarDistance,
    -overlap * vecDistance.y / scalarDistance};
  return true;
}

const bool Collider::_intersects(const Collider &other, float *overlap) const
{
  std::vector<sf::Vector2f> gCorners = this->m_globalCorners;

  for (int i = 0; i < gCorners.size(); ++i)
  {
    int j = (i + 1) % gCorners.size();
    sf::Vector2f projectedAxis = {gCorners[j].y - gCorners[i].y, -(gCorners[j].x - gCorners[i].x)};
    float div = sqrtf(projectedAxis.x * projectedAxis.x + projectedAxis.y * projectedAxis.y);
		projectedAxis = { projectedAxis.x / div, projectedAxis.y / div }; //Normalize

    Shadow shadow1 = this->_castOnAxis(projectedAxis);
    Shadow shadow2 = other._castOnAxis(projectedAxis);
    *overlap = std::min(std::min(shadow1.max, shadow2.max) - std::max(shadow1.min, shadow2.min), *overlap);
    if (!(shadow2.max >= shadow1.min && shadow1.max >= shadow2.min))
      return false;
  }
  if (*overlap < 1.0f)
    *overlap = 1.0f; // Set a minimum overlap to avoid trivially small offsets
  return true;
}

const Shadow Collider::_castOnAxis(const sf::Vector2f projectedAxis) const
{
  Shadow shadow = {INFINITY, -INFINITY};
  std::vector<sf::Vector2f> gCorners = this->m_globalCorners;
  int size = gCorners.size();

  for (int cornerIndex = 0; cornerIndex < size; ++cornerIndex)
  {
    float dotProd = (gCorners[cornerIndex].x * projectedAxis.x + gCorners[cornerIndex].y * projectedAxis.y);
    shadow.min = std::min(shadow.min, dotProd);
    shadow.max = std::max(shadow.max, dotProd);
  }
  return shadow;
}
