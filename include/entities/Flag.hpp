#ifndef FLAG_HPP
# define FLAG_HPP

# include "Entity.hpp"
# define DEFAULT_FLAG_SCALE 2.f

class Flag : public Entity
{
  public:
    Flag(
      const std::string &colour,
      const sf::Vector2f &pos
    );
    ~Flag();
};

#endif
