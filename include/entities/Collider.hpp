#ifndef COLLIDER_HPP
# define COLLIDER_HPP

# include <SFML/Graphics.hpp>
# include "Arena.hpp"

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
    void updateCollider();

    // Boundary & Collisions
    void boundInWalls(const Arena &arena);
    const bool isColliding(
      const Collider &other,
      sf::Vector2f *offset = nullptr) const;

  private:
    const bool _intersects(const Collider &other, float *overlap) const;
    const Shadow _castOnAxis(const sf::Vector2f axis) const;

    std::vector<sf::Vector2f> m_localCorners;
    std::vector<sf::Vector2f> m_globalCorners;
    sf::Vector2f m_pos;
    sf::Sprite *m_spritePtr;
};

#endif
