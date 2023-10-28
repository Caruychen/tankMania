#ifndef GAME_HPP
# define GAME_HPP

# include <SFML/Graphics.hpp>

# define FRAME_RATE_LIMIT 60
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
    virtual ~Game();

    // Accessorsj
    const bool running() const;

    // Functions
    void pollEvents();
    void update();
    void render();


  private:
    void              _initVariables();
    void              _initWindow();
    sf::RenderWindow  *_window;
    sf::VideoMode     _videoMode;
    sf::Event         _event;
};

#endif
