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
    void toggleFullScreen();
    void draw(sf::Drawable &drawable);

    // Accessors
    const sf::Vector2u getSize() const;
    void setPlayers(const std::pair<std::unique_ptr<Player>, std::unique_ptr<Player>> &players);
    sf::Font &getFont();
    const bool isDone() const;
    const bool isFullScreen() const;

  private:
    void _create();
    void _destroy();

    sf::RenderWindow m_window;
    sf::Font m_font;
    std::string m_windowTitle;
    sf::Vector2u m_windowSize;
    bool m_isDone;
    bool m_isFullScreen;
    const std::pair<std::unique_ptr<Player>, std::unique_ptr<Player>> *m_players;
};

# endif
