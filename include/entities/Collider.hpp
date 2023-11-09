#ifndef COLLIDER_HPP
# define COLLIDER_HPP
# define _USE_MATH_DEFINES

# include <SFML/Graphics.hpp>

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
    Collider getCollider();

    // Boundary & Collisions
    const bool isCollidingGroup(std::vector<Collider> colliders);
    void offsetCollision(const Collider &other);
    const bool isColliding(
      const Collider &other,
      sf::Vector2f *offset = nullptr);

  private:
    const bool _intersects(const Collider &other, float *overlap) const;
    const Shadow _castOnAxis(const sf::Vector2f axis) const;

    std::vector<sf::Vector2f> m_localCorners;
    std::vector<sf::Vector2f> m_globalCorners;
    sf::Vector2f m_pos;
    sf::Sprite *m_spritePtr;
};

#endif
