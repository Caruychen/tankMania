#ifndef COLLIDER_HPP
# define COLLIDER_HPP

# include <SFML/Graphics.hpp>
# include "Arena.hpp"

struct Vec2d
{
  float x;
  float y;
};

struct Shadow
{
  float min;
  float max;
};

struct Offset
{
  bool isOverlapping;
  sf::Vector2f value;
};

class Collider
{
  public:
    Collider();
    Collider(const sf::FloatRect &wall);
    ~Collider();

    void init(
      sf::Vector2f pos,
      sf::Vector2f origin,
      sf::FloatRect rect,
      const sf::Vector2f scale);

    int getNumCorners() const;
    sf::Vector2f getPosition() const;

  protected:
    void _updateCollider(const sf::Vector2f pos, const float angle);
    const Shadow _findShadowOnAxis(const Vec2d axis) const;
    const bool _intersects(const Collider &other, float *overlap) const;
    const Offset _getWallOffset(const Arena &arena) const;

  private:
    std::vector<Vec2d> m_localCorners;
    std::vector<Vec2d> m_globalCorners;
    sf::Vector2f m_pos;
};

#endif
