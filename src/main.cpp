#include <SFML/Graphics.hpp>
#include "Map.hpp"
#include <iostream>

int main()
{
  sf::RenderWindow window(sf::VideoMode(MAP_WIDTH, MAP_HEIGHT), "Tank Blast!");

  Map map("assets/maps/map_00.txt");
  map.load();
  while (window.isOpen())
  {
      sf::Event event;
      while (window.pollEvent(event))
      {
          if (event.type == sf::Event::Closed)
              window.close();
      }

      window.clear();
      window.draw(map);
      window.display();
  }

  return 0;
}
