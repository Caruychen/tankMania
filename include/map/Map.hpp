#ifndef MAP_HPP
# define MAP_HPP

# include <SFML/Graphics.hpp>

# define MAP_WIDTH 1024
# define MAP_HEIGHT 512

class Map : public sf::Drawable, public sf::Transformable
{
  public:
    Map(const std::string& mapFile);
    void load(void);
      
  private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void  readMap(const std::string& mapFile);
    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
    std::vector<uint8_t> m_data;
};

#endif
