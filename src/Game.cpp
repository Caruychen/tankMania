#include "Constants.hpp"
#include "Game.hpp"
#include <iostream>

// Constructors & Destructors
Game::Game(): 
  m_window("Tank Mania!", sf::Vector2u(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT)),
  m_arena(Arena({
    "assets/maps/map_1.txt",
    "assets/maps/map_2.txt",
    "assets/maps/map_3.txt",
    "assets/maps/map_4.txt"})),
  m_isHeartSpawned(false),
  m_isProjectileSpawned(false),
  m_gameState(GameState::Menu),
  m_gen(m_rd())
{
  if(!this->m_font.loadFromFile("assets/fonts/ArcadeClassic.ttf"))
    throw std::runtime_error("Could not load font");
  this->_initText(&this->m_menuText);
  this->_initText(&this->m_gameOverText);
  this->m_menuText.setString(
    "Welcome to Tank Mania!\n\n" \
    "Press 1  2  3  or  4  to open an arena\n" \
    "Press F5 to toggle fullscreen\n");
  sf::FloatRect textRect = this->m_menuText.getLocalBounds();
  this->m_menuText.setPosition(
    (ARENA_WIDTH - textRect.width) / 2,
    ARENA_HEIGHT / 2 - textRect.height);
}

Game::~Game()
{}

// Accessors
const bool Game::running() const
{
  return !this->m_window.isDone();
}

// Public Functions
void Game::update()
{
  unsigned int mapNumber = 0;

  this->m_window.pollEvents(&mapNumber);
  switch (this->m_gameState)
  {
    case GameState::Menu:
      if (mapNumber)
        this->_loadGame(mapNumber);
      return ;
    case GameState::Playing:
      break ;
    case GameState::GameOver:
      return ;
    default:
      break ;
  }

  std::unique_ptr<Player> &playerOne = this->m_players.first;
  std::unique_ptr<Player> &playerTwo = this->m_players.second;

  this->_checkWinCondition();
  playerOne->update(this->m_arena);
  playerTwo->update(this->m_arena);
  playerOne->updateCollisions(playerTwo, this->m_arena);
  playerTwo->updateCollisions(playerOne, this->m_arena);
  if (playerOne->checkCollisionsPickup(this->m_heart))
    this->_spawnHeart(false);
  if (playerTwo->checkCollisionsPickup(this->m_heart))
    this->_spawnHeart(false);
  this->_spawnHeart(true);
  if (playerOne->checkCollisionsPickup(this->m_projectile))
    this->_spawnProjectile(false);
  if (playerTwo->checkCollisionsPickup(this->m_projectile))
    this->_spawnProjectile(false);
  this->_spawnProjectile(true);
}

void Game::render()
{
  this->m_window.beginDraw();
  switch (this->m_gameState)
  {
    case GameState::Menu:
      this->m_window.draw(this->m_menuText);
      break;
    case GameState::Playing:
      this->m_window.draw(this->m_arena);
      this->m_window.draw(*this->m_players.first);
      this->m_window.draw(*this->m_players.second);
      if (this->m_isHeartSpawned)
        this->m_window.draw(*this->m_heart);
      if (this->m_isProjectileSpawned)
        this->m_window.draw(*this->m_projectile);
      break;
    case GameState::GameOver:
      this->m_window.draw(this->m_gameOverText);
      break;
    default:
      break;
  }
  this->m_window.endDraw();
}

void Game::restartClock()
{
  this->m_elapsed = this->m_clock.restart();
}

// Private methods
void Game::_initText(sf::Text *text)
{
  text->setFont(this->m_font);
  text->setCharacterSize(32);
  text->setFillColor(sf::Color::White);
  text->setStyle(sf::Text::Bold);
  text->setLineSpacing(1.5f);
  text->setLetterSpacing(1.5f);
}

void Game::_loadGame(unsigned int mapNumber)
{
  this->m_arena.load(mapNumber);
  this->_spawnPlayers();
  this->m_window.setPlayers(this->m_players);
  this->m_dist = std::uniform_int_distribution<>(0, this->m_arena.getSpaces().size() - 1);
  this->m_gameState = GameState::Playing;
}

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
  static float seconds;

  if (!spawn)
  {
    seconds = 0.0f;
    this->m_isHeartSpawned = false;
    this->m_heart.reset();
    return ;
  }
  seconds += this->m_elapsed.asSeconds();
  if (this->m_isHeartSpawned || seconds <= HEART_SPAWN_RATE)
    return ;
  this->m_isHeartSpawned = true;
  this->m_heart = std::unique_ptr<Heart>(
    new Heart(true, this->m_arena.getSpaces()[this->m_dist(this->m_gen)], 2.0f));
}

void Game::_spawnProjectile(const bool spawn)
{
  static float seconds;

  if (!spawn)
  {
    seconds = 0.0f;
    this->m_isProjectileSpawned = false;
    this->m_projectile.reset();
    return ;
  }
  seconds += this->m_elapsed.asSeconds();
  if (this->m_isProjectileSpawned || seconds <= PROJECTILE_SPAWN_RATE)
    return ;
  this->m_isProjectileSpawned = true;
  this->m_projectile = std::unique_ptr<Projectile>(
    new Projectile(
      this->m_arena.getSpaces()[this->m_dist(this->m_gen)],0));
}

void Game::_checkWinCondition()
{
  std::unique_ptr<Player> &playerOne = this->m_players.first;
  std::unique_ptr<Player> &playerTwo = this->m_players.second;

  if (!playerOne->hasCapturedFlag() &&
      !playerTwo->hasCapturedFlag() &&
      playerOne->getHealth() > 0 &&
      playerTwo->getHealth() > 0)
    return ;
  this->m_gameState = GameState::GameOver;
  if ((playerOne->hasCapturedFlag() && playerTwo->hasCapturedFlag()) ||
      (playerOne->getHealth() <= 0 && playerTwo->getHealth() <= 0))
    this->m_gameOverText.setString("It's a tie!\n");
  else if (playerOne->hasCapturedFlag())
    this->m_gameOverText.setString("Player 1 wins!\nBy capturing the flag!\n");
  else if (playerTwo->getHealth() <= 0)
    this->m_gameOverText.setString("Player 1 wins!\nBy destroying their enemy and all that is dear to them!\n");
  else if (playerTwo->hasCapturedFlag())
    this->m_gameOverText.setString("Player 2 wins!\nBy capturing the flag!\n");
  else if (playerOne->getHealth() <= 0)
    this->m_gameOverText.setString("Player 2 wins!\nBy destroying their enemy and all that is dear to them!\n");
  sf::FloatRect textRect = this->m_gameOverText.getLocalBounds();
  this->m_gameOverText.setPosition(
    (ARENA_WIDTH - textRect.width) / 2,
    ARENA_HEIGHT / 2 - textRect.height);
}
