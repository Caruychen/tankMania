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

const Shadow Collider::_findShadowOnAxis(const Vec2d projectedAxis) const
{
  Shadow shadow = {INFINITY, -INFINITY};
  std::vector<Vec2d> gCorners = this->m_globalCorners;
  int size = gCorners.size();

  for (int cornerIndex = 0; cornerIndex < size; ++cornerIndex)
  {
    float dotProd = (gCorners[cornerIndex].x * projectedAxis.x + gCorners[cornerIndex].y * projectedAxis.y);
    shadow.min = std::min(shadow.min, dotProd);
    shadow.max = std::max(shadow.max, dotProd);
  }
  return shadow;
}

const bool Collider::_intersects(const Collider &other, float *overlap) const
{
  std::vector<Vec2d> gCorners = this->m_globalCorners;
  int size = gCorners.size();
  float l_overlap = INFINITY;

  for (int i = 0; i < size; ++i)
  {
    int j = (i + 1) % size;
    Vec2d projectedAxis = {gCorners[j].y - gCorners[i].y, -(gCorners[j].x - gCorners[i].x)};
    float div = sqrtf(projectedAxis.x * projectedAxis.x + projectedAxis.y * projectedAxis.y);
		projectedAxis = { projectedAxis.x / div, projectedAxis.y / div };

    Shadow shadow1 = this->_findShadowOnAxis(projectedAxis);
    Shadow shadow2 = other._findShadowOnAxis(projectedAxis);
    l_overlap = std::min(
      std::min(shadow1.max, shadow2.max) - std::max(shadow1.min, shadow2.min),
      l_overlap);
    if (!(shadow2.max >= shadow1.min && shadow1.max >= shadow2.min))
      return false;
  }
  *overlap = std::min(l_overlap, *overlap);
  if (*overlap < 1.0f)
    *overlap = 1.0f;
  return true;
}

Offset Collider::_computeOffset(const Collider &other) const
{
  Offset offset = {false, {0, 0}};
  float overlap = INFINITY;
  Vec2d vecDistance;
  float straightDistance;

  offset.isOverlapping = this->_intersects(other, &overlap) &&
    other._intersects(*this, &overlap);
  if (!offset.isOverlapping)
    return offset;
  vecDistance = { other.m_pos.x - this->m_pos.x, other.m_pos.y - this->m_pos.y };
  straightDistance = sqrtf(vecDistance.x * vecDistance.x + vecDistance.y * vecDistance.y);
  offset.value = {
    -overlap * vecDistance.x / straightDistance,
    -overlap * vecDistance.y / straightDistance};
  return offset;
}

const Offset Collider::_getWallOffset(const Arena &arena) const
{
  std::vector<sf::FloatRect> arenaWalls = arena.getWalls();
  Collider wallCollider;
  Offset offset = {false, {0, 0}};
  static unsigned int lastIndex;
  unsigned int index = lastIndex;

  while (index < arenaWalls.size())
  {
    wallCollider = Collider(arenaWalls[index]);
    offset = this->_computeOffset(wallCollider);
    if (offset.isOverlapping)
    {
      lastIndex = index;
      break;
    }
    ++index;
  }
  if (index == arenaWalls.size())
    lastIndex = 0;
  return offset;
}
