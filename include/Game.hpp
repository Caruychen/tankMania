#ifndef GAME_HPP
# define GAME_HPP

# include <random>
# include <SFML/Graphics.hpp>
# include "Window.hpp"
# include "Player.hpp"
# include "Arena.hpp"

# define HEART_SPAWN_RATE 15.f
# define PROJECTILE_SPAWN_RATE 2.f

/*
* Game class acts as basic game engine.
*/

enum class GameState
{
  Menu,
  Playing,
  GameOver
};

class Game
{
  public:
    // Constructor / Destructor
    Game();
    ~Game();

    // Accessors
    const bool running() const;

    // Functions
    void update();
    void render();
    void restartClock();

  private:
    void _initText(sf::Text *text);
    void _loadGame(unsigned int mapNumber);
    void _spawnHeart(const bool spawn);
    void _spawnProjectile(const bool spawn);
    void _spawnPlayers();
    void _checkWinCondition();

    Window m_window;
    Arena m_arena;
    GameState m_gameState;
    sf::Text m_gameOverText;
    sf::Text m_menuText;
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
