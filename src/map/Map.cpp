#include <cmath>
#include <SFML/System.hpp>
#include "Map.hpp"
#include <iostream>

Map::Map(const std::string& mapFile)
{
  this->readMap(mapFile);
}

void Map::load(void)
{
  unsigned int heightInTiles = sqrt(this->m_data.size() / 2);
  unsigned int widthInTiles = heightInTiles * 2;
  unsigned int tileNumber;
  sf::Vector2u tileSize = sf::Vector2u(MAP_WIDTH / widthInTiles, MAP_HEIGHT / heightInTiles);

  m_vertices.setPrimitiveType(sf::Triangles);
  m_vertices.resize(widthInTiles * heightInTiles * 6);
  sf::Color colors[2] = {sf::Color::Black, sf::Color::White};

  for (unsigned int x = 0; x < widthInTiles; ++x)
  {
    for (unsigned int y = 0; y < heightInTiles; ++y)
    {
      tileNumber = this->m_data[x + y * widthInTiles];

      sf::Vertex *triangles = &m_vertices[(x + y * widthInTiles) * 6];

      triangles[0].position = sf::Vector2f(x * tileSize.x, y * tileSize.y);
      triangles[1].position = sf::Vector2f((x + 1) * tileSize.x, y * tileSize.y);
      triangles[2].position = sf::Vector2f(x * tileSize.x, (y + 1) * tileSize.y);
      triangles[3].position = sf::Vector2f(x * tileSize.x, (y + 1) * tileSize.y);
      triangles[4].position = sf::Vector2f((x + 1) * tileSize.x, y * tileSize.y);
      triangles[5].position = sf::Vector2f((x + 1) * tileSize.x, (y + 1) * tileSize.y);

      triangles[0].color = colors[tileNumber];
      triangles[1].color = colors[tileNumber];
      triangles[2].color = colors[tileNumber];
      triangles[3].color = colors[tileNumber];
      triangles[4].color = colors[tileNumber];
      triangles[5].color = colors[tileNumber];

    }
  }
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  states.transform *= getTransform();
  states.texture = &this->m_tileset;
  target.draw(m_vertices, states);
}

void Map::readMap(const std::string& mapFile)
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
  std::cout << "Map size: " << this->m_data.size() << std::endl;
  std::cout << sqrt(this->m_data.size() / 2) << std::endl;
}
