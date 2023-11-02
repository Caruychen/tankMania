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

class Collider
{
  public:
    Collider();
    Collider(sf::Sprite *spritePtr);
    Collider(const sf::FloatRect &wall);
    ~Collider();

    void initCollider();

  protected:
    void _updateCollider();
    const Shadow _castOnAxis(const Vec2d axis) const;
    const bool _intersects(const Collider &other, float *overlap) const;
    const bool _isColliding(const Collider &other, sf::Vector2f *offset) const;
    void _boundInWalls(const Arena &arena);

  private:
    std::vector<Vec2d> m_localCorners;
    std::vector<Vec2d> m_globalCorners;
    sf::Vector2f m_pos;
    sf::Sprite *m_spritePtr;
};

#endif
