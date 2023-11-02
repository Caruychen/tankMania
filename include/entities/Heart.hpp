#ifndef HEART_HPP
# define HEART_HPP

# include "Entity.hpp"
# define HEART_SCALE 1.f

class Heart : public Entity
{
  public:
    Heart(
      const bool &isAlive,
      const sf::Vector2f &pos);
    ~Heart();

  private:
    bool m_isAlive;
};

#endif
