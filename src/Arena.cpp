#include "Arena.hpp"
#include <iostream>

Arena::Arena(const std::string &mapFile) : m_arenaSize(ARENA_WIDTH, ARENA_HEIGHT)
{
  this->_readMap(mapFile);
}

Arena::~Arena()
{}

void Arena::load(void)
{
  this->_loadTiles();
  this->_loadWalls();
}

void Arena::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(m_vertices, states);
}

void  Arena::_readMap(const std::string& mapFile)
{
  sf::FileInputStream stream;
  char buffer[1];

  if (!stream.open(mapFile))
    throw std::runtime_error("Could not open file!");
  while (stream.read(buffer, 1) > 0)
  {
    if (buffer[0] == '\n')
      continue;
    this->m_data.push_back(buffer[0] - '0');
  }
  this->m_heightInTiles = sqrt(this->m_data.size() / 2);
  this->m_widthInTiles = this->m_heightInTiles * 2;
  this->m_tileSize = sf::Vector2f(
    this->m_arenaSize.x / m_widthInTiles,
    this->m_arenaSize.y / m_heightInTiles);
}

void Arena::_loadTiles(void)
{
  unsigned int tileNumber;
  sf::Vertex *triangles;

  this->m_vertices.setPrimitiveType(sf::Triangles);
  this->m_vertices.resize(m_widthInTiles * m_heightInTiles * 6);
  sf::Color colors[2] = {sf::Color::Black, sf::Color::White};

  for (unsigned int x = 0; x < m_widthInTiles; ++x)
  {
    for (unsigned int y = 0; y < m_heightInTiles; ++y)
    {
      tileNumber = this->m_data[x + y * m_widthInTiles];
      triangles = &m_vertices[(x + y * m_widthInTiles) * 6];

      triangles[0].position = sf::Vector2f(x * m_tileSize.x, y * m_tileSize.y);
      triangles[1].position = sf::Vector2f((x + 1) * m_tileSize.x, y * m_tileSize.y);
      triangles[2].position = sf::Vector2f(x * m_tileSize.x, (y + 1) * m_tileSize.y);
      triangles[3].position = sf::Vector2f(x * m_tileSize.x, (y + 1) * m_tileSize.y);
      triangles[4].position = sf::Vector2f((x + 1) * m_tileSize.x, y * m_tileSize.y);
      triangles[5].position = sf::Vector2f((x + 1) * m_tileSize.x, (y + 1) * m_tileSize.y);

      triangles[0].color = colors[tileNumber];
      triangles[1].color = colors[tileNumber];
      triangles[2].color = colors[tileNumber];
      triangles[3].color = colors[tileNumber];
      triangles[4].color = colors[tileNumber];
      triangles[5].color = colors[tileNumber];
    }
  }
}

void Arena::_loadWalls(void)
{
  unsigned int tileNumber;
  sf::FloatRect rect;

  for (unsigned int x = 0; x < m_widthInTiles; ++x)
  {
    for (unsigned int y = 0; y < m_heightInTiles; ++y)
    {
      tileNumber = this->m_data[x + y * m_widthInTiles];
      if (tileNumber < 1)
        continue;
      rect = sf::FloatRect(
        x * m_tileSize.x,
        y * m_tileSize.y,
        m_tileSize.x,
        m_tileSize.y);
      this->m_walls.push_back(rect);
    }
  }
}
