#include "Game.hpp"
#include <iostream>

// Constructors & Destructors
Game::Game(): 
  m_window("Tank Mania!", sf::Vector2u(1200, 675)),
  m_arena(Arena("assets/maps/map_00.txt")),
  m_isHeartSpawned(false),
  m_gen(m_rd())
{
  this->m_arena.load();
  this->_spawnPlayers();
  this->m_dist = std::uniform_int_distribution<>(0, this->m_arena.getSpaces().size() - 1);
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
  std::unique_ptr<Player> &playerOne = this->m_players.first;
  std::unique_ptr<Player> &playerTwo = this->m_players.second;

  this->m_window.update();
  this->_spawnHeart(true);
  playerOne->update();
  playerTwo->update();
  playerOne->checkCollisions(playerTwo, this->m_arena);
  playerTwo->checkCollisions(playerOne, this->m_arena);
  if (playerOne->checkHeartCollision(this->m_heart))
    this->_spawnHeart(false);
  if (playerTwo->checkHeartCollision(this->m_heart))
    this->_spawnHeart(false);
}

void Game::render()
{
  this->m_window.beginDraw();
  this->m_window.draw(this->m_arena);
  this->m_window.draw(*this->m_players.first);
  this->m_window.draw(*this->m_players.second);
  if (this->m_isHeartSpawned)
    this->m_window.draw(*this->m_heart);
  this->m_window.endDraw();
}

void Game::restartClock()
{
  this->m_elapsed = this->m_clock.restart();
}

// Private methods
void Game::_spawnPlayers()
{
  std::pair<PlayerConfigs, PlayerConfigs> playerConfigs = this->m_arena.getPlayerConfigs();

  this->m_players.first = std::unique_ptr<Player>(new Player(
    1,
    "assets/tanks/blueTank.png",
    playerConfigs.first,
    &this->m_elapsed));
  this->m_players.second = std::unique_ptr<Player>(new Player(
    2,
    "assets/tanks/redTank.png",
    playerConfigs.second,
    &this->m_elapsed));
}

void Game::_spawnHeart(const bool spawn)
{
  static sf::Clock localClock;

  if (!spawn)
  {
    localClock.restart();
    this->m_isHeartSpawned = false;
    this->m_heart.reset();
    return ;
  }
  if (this->m_isHeartSpawned ||
      localClock.getElapsedTime().asSeconds() <= 10.0f)
    return ;
  this->m_isHeartSpawned = true;
  this->m_heart = std::unique_ptr<Heart>(
    new Heart(true, this->m_arena.getSpaces()[this->m_dist(this->m_gen)], 2.0f));
}
