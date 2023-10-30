#include "Window.hpp"

// Constructors & Destructors
Window::Window()
{
  this->_setup("Window", sf::Vector2u(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT));
}

Window::Window(const std::string &title, const sf::Vector2u &size)
{
  this->_setup(title, size);
}

Window::~Window()
{
  this->_destroy();
}

// Public Methods
void Window::beginDraw()
{
  this->m_window.clear(sf::Color::Black);
}

void Window::endDraw()
{
  this->m_window.display();
}

void Window::update()
{
  sf::Event event;

  while (this->m_window.pollEvent(event))
  {
    switch (event.type)
    {
      case sf::Event::Closed:
        this->m_isDone = true;
        break;
      case sf::Event::KeyPressed:
        if (event.key.code == sf::Keyboard::F5)
          this->toggleFullScreen();
        break;
      default:
        break;
    }
  }
}

void Window::toggleFullScreen()
{
  this->m_isFullScreen = !this->m_isFullScreen;
  this->_destroy();
  this->_create();
}

void Window::draw(sf::Drawable &drawable)
{
  this->m_window.draw(drawable);
}

// Accessors
const bool Window::isDone() const
{
  return this->m_isDone;
}

const bool Window::isFullScreen() const
{
  return this->m_isFullScreen;
}

sf::Vector2u Window::getWindowSize()
{
  return this->m_windowSize;
}

// Private methods
void Window::_setup(const std::string &title, const sf::Vector2u &size)
{
  this->m_windowTitle = title;
  this->m_windowSize = size;
  this->m_isFullScreen = false;
  this->m_isDone = false;
  this->_create();
}

void Window::_create()
{
  auto style = (this->m_isFullScreen ? sf::Style::Fullscreen : sf::Style::Default);
  this->m_window.create(
    sf::VideoMode(this->m_windowSize.x, this->m_windowSize.y),
    this->m_windowTitle,
    style
  );
}

void Window::_destroy()
{
  this->m_window.close();
}
