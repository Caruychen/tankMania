#ifndef PROJECTILE_HPP
# define PROJECTILE_HPP

# include "Entity.hpp"

class Projectile : public Entity
{
  public:
    Projectile(
      const sf::Vector2f &pos,
      const float &rotation,
      sf::Time *elapsed = nullptr);
    ~Projectile();
      
    bool checkCollisions(const Arena &arena);
  private:
};

#endif
