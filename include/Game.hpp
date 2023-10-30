#ifndef GAME_HPP
# define GAME_HPP

# include <SFML/Graphics.hpp>
# include "Window.hpp"

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
    void handleInput();
    void update();
    void render();
    void restartClock();

  private:
    void  _moveTank();

    Window m_window;
    sf::Clock m_clock;
    sf::Time m_elapsed;
    sf::Texture m_tankTexture;
    sf::Sprite m_tank;
    sf::Vector2i m_increment;

};

#endif
