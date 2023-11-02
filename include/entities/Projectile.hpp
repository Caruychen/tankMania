#ifndef PROJECTILE_HPP
# define PROJECTILE_HPP

# include "Entity.hpp"

class Projectile : public Entity
{
  public:
    Projectile(
      unsigned int type,
      const sf::Vector2f &pos,
      const float &rotation,
      const sf::Vector2f &scale,
      sf::Time *elapsed);
    ~Projectile();
      
  private:
};

#endif
