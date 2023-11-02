#ifndef TANK_HPP
# define TANK_HPP

# include "Entity.hpp"
# define TANK_SCALE 0.25f

class Tank : public Entity
{
  public:
    Tank(
      const std::string &name,
      const std::string &texturePath,
      const sf::Vector2f &pos,
      const int &incrementSpeed,
      sf::Time *elapsed);
    ~Tank();

    void fire();

  private:
};

#endif
