#ifndef TANK_HPP
# define TANK_HPP

# include "Entity.hpp"

class Tank : public Entity
{
  public:
    Tank(
      const std::string &name,
      const std::string &texturePath,
      const sf::Vector2f &pos,
      sf::Time *elapsed);
    ~Tank();

    void handleInput();

  private:
};

#endif
