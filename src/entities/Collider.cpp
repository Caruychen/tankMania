#include "Collider.hpp"
#include <iostream>

Collider::Collider()
{}

Collider::Collider(const sf::FloatRect &wall)
{
  Vec2d localCenter = {wall.width / 2, wall.height / 2};
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

void Collider::init(sf::Vector2f pos, sf::Vector2f origin, sf::FloatRect rect, const sf::Vector2f scale)
{
  origin.x *= scale.x;
  origin.y *= scale.y;
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
  this->m_pos = pos;
}

int Collider::getNumCorners() const
{
  return this->m_globalCorners.size();
}

sf::Vector2f Collider::getPosition() const
{
  return this->m_pos;
}

void Collider::_updateCollider(const sf::Vector2f pos, const float angle)
{
  const std::vector<Vec2d> lCorners = this->m_localCorners;

  for (int index = 0; index < this->m_globalCorners.size(); ++index)
  {
    this->m_globalCorners[index].x = pos.x + lCorners[index].x * cos(angle) - lCorners[index].y * sin(angle);
    this->m_globalCorners[index].y = pos.y + lCorners[index].x * sin(angle) + lCorners[index].y * cos(angle);
  }
  this->m_pos = pos;
}

const Shadow Collider::_findShadowOnAxis(const Vec2d axis) const
{
  Shadow shadow = {INFINITY, -INFINITY};
  std::vector<Vec2d> gCorners = this->m_globalCorners;
  int size = gCorners.size();

  for (int cornerIndex = 0; cornerIndex < size; ++cornerIndex)
  {
    float q = (gCorners[cornerIndex].x * axis.x + gCorners[cornerIndex].y * axis.y);
    shadow.min = std::min(shadow.min, q);
    shadow.max = std::max(shadow.max, q);
  }
  return shadow;
}

const bool Collider::_intersects(const Collider &other, float *overlap) const
{
  std::vector<Vec2d> gCorners = this->m_globalCorners;
  int size = gCorners.size();

  for (int i = 0; i < size; ++i)
  {
    int j = (i + 1) % size;
    Vec2d axis = {-(gCorners[j].y - gCorners[i].y), gCorners[j].x - gCorners[i].x};

    Shadow shadow1 = this->_findShadowOnAxis(axis);
    Shadow shadow2 = other._findShadowOnAxis(axis);
    *overlap = std::min(
      std::min(shadow1.max, shadow2.max) - std::max(shadow1.min, shadow2.min),
      *overlap);
    if (!(shadow2.max >= shadow1.min && shadow1.max >= shadow2.min))
      return false;
  }
  return true;
}

const Offset Collider::_getWallOffset(const Arena &arena) const
{
  std::vector<sf::FloatRect> arenaWalls = arena.getWalls();
  Offset offset = {false, {0, 0}};
  float overlap = INFINITY;
  Collider wallCollider;

  for (sf::FloatRect wall: arenaWalls)
  {
    wallCollider = Collider(wall);
    overlap = INFINITY;
    offset.isOverlapping = this->_intersects(wallCollider, &overlap);
    if (offset.isOverlapping)
      offset.isOverlapping = wallCollider._intersects(*this, &overlap);
    if (offset.isOverlapping)
      break;
  }
  Vec2d d = { wallCollider.m_pos.x - this->m_pos.x, wallCollider.m_pos.y - this->m_pos.y };
  float s = sqrtf(d.x*d.x + d.y*d.y);
  offset.value = {overlap * d.x / s, overlap * d.y / s};
  if (offset.isOverlapping)
    std::cout << "Overlap: " << overlap << std::endl;
  return offset;
}
