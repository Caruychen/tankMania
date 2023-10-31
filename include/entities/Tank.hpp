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
      const int &incrementSpeed,
      sf::Time *elapsed);
    ~Tank();

    void fire();
    void handleInput(const Window &window);

  private:
};

#endif
