#ifndef GAME_HPP
# define GAME_HPP

# include <SFML/Graphics.hpp>
# include "Window.hpp"
# include "Player.hpp"

# define MAP_WIDTH 1024
# define MAP_HEIGHT 512

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
    Window* getWindow();
    sf::Time getElapsed();

    // Functions
    void update();
    void render();
    void restartClock();

  private:
    void _setupPlayers();

    Window m_window;
    sf::Clock m_clock;
    sf::Time m_elapsed;
    std::pair<std::unique_ptr<Player>, std::unique_ptr<Player>> m_players;
};

#endif
