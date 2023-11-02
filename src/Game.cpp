#include "Game.hpp"
#include <iostream>

// Constructors & Destructors
Game::Game(): 
  m_window("Tank Mania!", sf::Vector2u(1200, 675)),
  m_arena(Arena("assets/maps/map_00.txt"))
{
  this->m_arena.load();
  this->_setupPlayers();
}

Game::~Game()
{}

// Accessors
const bool Game::running() const
{
  return !this->m_window.isDone();
}

sf::Time Game::getElapsed()
{
  return this->m_elapsed;
}

// Public Functions
void Game::update()
{
  this->m_window.update();
  this->m_players.first->handleInput(this->m_arena);
  this->m_players.second->handleInput(this->m_arena);
}

void Game::render()
{
  this->m_window.beginDraw();
  this->m_window.draw(this->m_arena);
  this->m_window.draw(*this->m_players.first);
  this->m_window.draw(*this->m_players.second);
  this->m_window.endDraw();
}

void Game::restartClock()
{
  this->m_elapsed = this->m_clock.restart();
}

// Private methods
void Game::_setupPlayers()
{
  std::pair<PlayerConfigs, PlayerConfigs> playerConfigs = this->m_arena.getPlayerConfigs();

  this->m_players.first = std::unique_ptr<Player>(new Player(
    1,
    "assets/tanks/blueTank.png",
    playerConfigs.first.spawnPos,
    &this->m_elapsed));
  this->m_players.second = std::unique_ptr<Player>(new Player(
    2,
    "assets/tanks/redTank.png",
    playerConfigs.second.spawnPos,
    &this->m_elapsed));
}
