#ifndef GAME_HPP
# define GAME_HPP

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
    Window* getWindow();
    sf::Time getElapsed();

    // Functions
    void update();
    void render();
    void restartClock();

  private:
    void _setupPlayers();

    Window m_window;
    Arena m_arena;
    sf::Clock m_clock;
    sf::Time m_elapsed;
    std::pair<std::unique_ptr<Player>, std::unique_ptr<Player>> m_players;
};

#endif
