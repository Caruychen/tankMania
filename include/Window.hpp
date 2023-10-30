#ifndef WINDOW_HPP
# define WINDOW_HPP

# include <SFML/Graphics.hpp>
# include "EventManager.hpp"
# define DEFAULT_WINDOW_WIDTH 640
# define DEFAULT_WINDOW_HEIGHT 480

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

    void update();
    void toggleFullScreen(EventDetails *details);
    void draw(sf::Drawable &drawable);
    void close(EventDetails *details = nullptr);

    // Accessors
    sf::Vector2u getWindowSize();
    EventManager *getEventManager();
    const bool isDone() const;
    const bool isFullScreen() const;
    const bool isFocused() const;

  private:
    void _setup(const std::string &title, const sf::Vector2u &size);
    void _create();
    void _destroy();

    sf::RenderWindow m_window;
    std::string m_windowTitle;
    sf::Vector2u m_windowSize;
    EventManager m_eventManager;
    bool m_isDone;
    bool m_isFullScreen;
    bool m_isFocused;
};

# endif
