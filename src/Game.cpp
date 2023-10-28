#include "Game.hpp"

// Constructors & Destructors
Game::Game()
{
  this->_initVariables();
  this->_initWindow();
}

Game::~Game()
{
  delete this->_window;
}

// Accessors
const bool Game::running() const
{
  return this->_window->isOpen();
}

// Public Functions
void Game::pollEvents()
{
  while (this->_window->pollEvent(this->_event))
  {
    switch (this->_event.type)
    {
      case sf::Event::Closed:
        this->_window->close();
        break;
      default:
        break;
    }
  }
}

void Game::update()
{
  /* Updates game state */
  this->pollEvents();
}

void Game::render()
{
  /* Renders Game objects */
  this->_window->clear();
  this->_window->display();
}

// Private methods
void Game::_initVariables()
{
  this->_window = nullptr;
}

void Game::_initWindow()
{
  this->_videoMode.width = MAP_WIDTH;
  this->_videoMode.height = MAP_HEIGHT;
  this->_window = new sf::RenderWindow(
    this->_videoMode,
    "Tank Mania!",
    sf::Style::Titlebar | sf::Style::Close
  );
  this->_window->setFramerateLimit(FRAME_RATE_LIMIT);
}
