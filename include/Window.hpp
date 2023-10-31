#ifndef WINDOW_HPP
# define WINDOW_HPP

# include <SFML/Graphics.hpp>
# define DEFAULT_WINDOW_WIDTH 1200
# define DEFAULT_WINDOW_HEIGHT 675

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
    void toggleFullScreen();
    void draw(sf::Drawable &drawable);

    // Accessors
    const sf::Vector2u getSize() const;
    const bool isDone() const;
    const bool isFullScreen() const;

  private:
    void _setup(const std::string &title, const sf::Vector2u &size);
    void _create();
    void _destroy();

    sf::RenderWindow m_window;
    std::string m_windowTitle;
    sf::Vector2u m_windowSize;
    bool m_isDone;
    bool m_isFullScreen;
};

# endif
