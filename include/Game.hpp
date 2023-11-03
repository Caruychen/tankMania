#ifndef GAME_HPP
# define GAME_HPP

# include <random>
# include <SFML/Graphics.hpp>
# include "Window.hpp"
# include "Player.hpp"
# include "Arena.hpp"

/*
* Game class acts as basic game engine.
*/

class Game
{
  public:
    // Constructor / Destructor
    Game();
    ~Game();

    // Accessors
    const bool running() const;
    sf::Time getElapsed();

    // Functions
    void update();
    void render();
    void restartClock();

  private:
    void _spawnHeart(const bool spawn);
    void _spawnProjectile(const bool spawn);
    void _spawnPlayers();

    Window m_window;
    Arena m_arena;
    sf::Clock m_clock;
    sf::Time m_elapsed;
    std::random_device m_rd;
    std::mt19937 m_gen;
    std::uniform_int_distribution<> m_dist;
    std::pair<std::unique_ptr<Player>, std::unique_ptr<Player>> m_players;
    bool m_isHeartSpawned;
    std::unique_ptr<Heart> m_heart;
    bool m_isProjectileSpawned;
    std::unique_ptr<Projectile> m_projectile;
};

#endif
