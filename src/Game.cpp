#include "Game.hpp"
#include "Player.hpp"
#include <iostream>

// Constructors & Destructors
Game::Game(): m_window("Tank Mania!", sf::Vector2u(1200, 675))
{
  this->m_player = new Player(
    2,
    "assets/tanks/blueTank.png",
    sf::Vector2f(0, 0),
    &this->m_elapsed);
}

Game::~Game()
{
  delete this->m_player;
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
  this->m_player->handleInput(*this->getWindow());
}

void Game::render()
{
  this->m_window.beginDraw();
  this->m_window.draw(*this->m_player);
  this->m_window.endDraw();
}

void Game::restartClock()
{
  this->m_elapsed = this->m_clock.restart();
}

// Private methods

