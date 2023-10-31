#ifndef PLAYER_HPP
# define PLAYER_HPP

# include "Tank.hpp"
# define MOVEMENT_SPEED 180

enum class P1
{
  UP = sf::Keyboard::W,
  DOWN = sf::Keyboard::S,
  LEFT = sf::Keyboard::A,
  RIGHT = sf::Keyboard::D,
  SHOOT = sf::Keyboard::Q
};

enum class P2
{
  UP = sf::Keyboard::Up,
  DOWN = sf::Keyboard::Down,
  LEFT = sf::Keyboard::Left,
  RIGHT = sf::Keyboard::Right,
  SHOOT = sf::Keyboard::Space
};

class Player : public Tank
{
  public:
    Player(
      const unsigned int &number,
      const std::string &texturePath,
      const sf::Vector2f &pos,
      sf::Time *elapsed);
    ~Player();

    void handleInput(const Arena &arena);

  private:
    void _setupKeyBindings();
    const unsigned int m_number;
    sf::Keyboard::Key m_forward;
    sf::Keyboard::Key m_backward;
    sf::Keyboard::Key m_left;
    sf::Keyboard::Key m_right;
    sf::Keyboard::Key m_shoot;
};

#endif
