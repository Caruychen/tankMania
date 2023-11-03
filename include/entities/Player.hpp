#ifndef PLAYER_HPP
# define PLAYER_HPP

# include "Tank.hpp"
# include "Heart.hpp"

# define MOVEMENT_SPEED 180
# define MAX_HEALTH 5
# define INITIAL_HEALTH 3
# define RESPAWN_TIME 2.f

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

struct Health
{
  unsigned int current;
  unsigned int max;
  std::vector<std::unique_ptr<Heart>> hearts;
};

class Player : public Tank
{
  public:
    Player(
      const unsigned int &number,
      const std::string &texturePath,
      const PlayerConfigs configs,
      sf::Time *elapsed);
    ~Player();

    void update(const Arena &arena);
    void checkCollisions(std::unique_ptr<Player> &other, const Arena &arena);
    const bool checkCollisionsHeart(std::unique_ptr<Heart> &heart);
    std::vector<Collider> getZones(void) const;

  private:
    void _setupKeyBindings();
    void _handleInput(void);
    void _checkCollisionsZone(std::unique_ptr<Player> &other);
    void _checkCollisionsProjectile(std::unique_ptr<Player> &other);
    void _initHealth();
    const bool _addHealth();
    void _takeDamage(void);
    void _respawn(void);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    const unsigned int m_number;
    bool m_isAlive;
    sf::Keyboard::Key m_forward;
    sf::Keyboard::Key m_backward;
    sf::Keyboard::Key m_left;
    sf::Keyboard::Key m_right;
    sf::Keyboard::Key m_shoot;
    Health m_health;
    const sf::Vector2f m_spawnPos;
    const float m_spawnRotation;
    const sf::Vector2f m_flagPos;
    const std::vector<Collider> m_zones;
};

#endif
