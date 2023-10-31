#include "Game.hpp"
#include "Tank.hpp"
#include <iostream>

// Constructors & Destructors
Game::Game(): m_window("Tank Mania!", sf::Vector2u(1600, 900))
{
  this->m_tank = new Tank(
    "Tank",
    "assets/tanks/blueTank.png",
    sf::Vector2f(0, 0),
    &this->m_elapsed);
}

Game::~Game()
{
  delete this->m_tank;
}

// Accessors
const bool Game::running() const
{
  return !this->m_window.isDone();
}

Window *Game::getWindow()
{
  return &this->m_window;
}

sf::Time Game::getElapsed()
{
  return this->m_elapsed;
}

// Public Functions
void Game::update()
{
  this->m_window.update();
  this->m_tank->handleInput();
}

void Game::render()
{
  this->m_window.beginDraw();
  this->m_window.draw(*this->m_tank);
  this->m_window.endDraw();
}

void Game::restartClock()
{
  this->m_elapsed = this->m_clock.restart();
}

// Private methods
/*
void Game::_moveTank()
{
  sf::Vector2u windowSize = this->m_window.getWindowSize();
  sf::Vector2u textureSize = this->m_tankTexture.getSize();
  float timeElapsed = this->getElapsed().asSeconds();

  if ((this->m_tank.getPosition().x + textureSize.x > windowSize.x && m_increment.x > 0)
    || (this->m_tank.getPosition().x <= 0 && m_increment.x < 0))
    m_increment.x = -m_increment.x;
  if ((this->m_tank.getPosition().y + textureSize.y > windowSize.y && m_increment.y > 0)
    || (this->m_tank.getPosition().y <= 0 && m_increment.y < 0))
    m_increment.y = -m_increment.y;
  this->m_tank.setPosition(
    this->m_tank.getPosition().x + (m_increment.x * timeElapsed),
    this->m_tank.getPosition().y + (m_increment.y * timeElapsed));
}
*/
