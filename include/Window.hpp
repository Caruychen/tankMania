#ifndef WINDOW_HPP
# define WINDOW_HPP

# include <SFML/Graphics.hpp>
# include "Player.hpp"

class Window
{
  public:
    // Constructors & Destructors
    Window();
    Window(const std::string &title, const sf::Vector2u &size);
    ~Window();

    // Methods
    void beginDraw(); // Clear the window
    void endDraw(); // Display the changes

    void pollEvents(unsigned int *mapNumber);
    void draw(sf::Drawable &drawable);

    // Accessors
    const sf::Vector2u getSize() const;
    void setPlayers(const std::pair<std::unique_ptr<Player>, std::unique_ptr<Player>> &players);
    const bool isDone() const;

  private:
    void _create();
    void _destroy();

    sf::RenderWindow m_window;
    std::string m_windowTitle;
    sf::Vector2u m_windowSize;
    bool m_isDone;
    const std::pair<std::unique_ptr<Player>, std::unique_ptr<Player>> *m_players;
};

# endif
