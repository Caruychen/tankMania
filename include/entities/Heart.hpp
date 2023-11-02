#ifndef HEART_HPP
# define HEART_HPP

# include "Entity.hpp"
# define HEART_SCALE 4.f
# define HEART_TEXTURE_SIZE 13

class Heart : public Entity
{
  public:
    Heart(
      const bool &isAlive,
      const sf::Vector2f &pos);
    ~Heart();

    void setAlive(const bool &isAlive);
    void resetTexture(void);

  private:
    bool m_isAlive;
};

#endif
