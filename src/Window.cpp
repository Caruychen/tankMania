#include "Constants.hpp"
#include "Window.hpp"
#include <iostream>

// Constructors & Destructors
Window::Window() :
  m_windowTitle("Window"),
  m_windowSize(sf::Vector2u(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT)),
  m_isFullScreen(false),
  m_isDone(false),
  m_players(nullptr)
{
  if(!this->m_font.loadFromFile("assets/fonts/ArcadeClassic.ttf"))
    throw std::runtime_error("Could not load font");
  this->_create();
}

Window::Window(const std::string &title, const sf::Vector2u &size) :
  m_windowTitle(title),
  m_windowSize(size),
  m_isFullScreen(false),
  m_isDone(false),
  m_players(nullptr)
{
  if(!this->m_font.loadFromFile("assets/fonts/ArcadeClassic.ttf"))
    throw std::runtime_error("Could not load font");
  this->_create();
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

void Window::pollEvents(unsigned int *mapNumber)
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
        if (event.key.code == sf::Keyboard::Num1)
          *mapNumber = 1;
        if (event.key.code == sf::Keyboard::Num2)
          *mapNumber = 2;
        if (event.key.code == sf::Keyboard::Num3)
          *mapNumber = 3;
        if (event.key.code == sf::Keyboard::Num4)
          *mapNumber = 4;
        if (m_players == nullptr)
          break;
        if (event.key.code == this->m_players->first->getShootKey())
          this->m_players->first->shoot();
        if (event.key.code == this->m_players->second->getShootKey())
          this->m_players->second->shoot();
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
const sf::Vector2u Window::getSize() const
{
  return this->m_windowSize;
}

void Window::setPlayers(const std::pair<std::unique_ptr<Player>, std::unique_ptr<Player>> &players)
{
  this->m_players = &players;
}

sf::Font &Window::getFont()
{
  return this->m_font;
}

const bool Window::isDone() const
{
  return this->m_isDone;
}

const bool Window::isFullScreen() const
{
  return this->m_isFullScreen;
}

// Private methods
void Window::_create()
{
  auto style = (this->m_isFullScreen ? sf::Style::Fullscreen : sf::Style::Default);
  this->m_window.create(
    sf::VideoMode(this->m_windowSize.x, this->m_windowSize.y),
    this->m_windowTitle,
    style
  );
  this->m_window.setFramerateLimit(FRAME_RATE_LIMIT);
}

void Window::_destroy()
{
  this->m_window.close();
}
