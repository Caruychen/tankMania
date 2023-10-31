#ifndef ARENA_HPP
# define ARENA_HPP

# include <SFML/Graphics.hpp>

# define ARENA_WIDTH 1200
# define ARENA_HEIGHT 600

class Arena : public sf::Drawable, public sf::Transformable
{
  public:
    Arena(const std::string &mapFile);
    ~Arena();
    void load(void);

  private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void  _readMap(const std::string& mapFile);

    std::vector<uint8_t> m_data;
    sf::VertexArray m_vertices;
    unsigned int m_heightInTiles;
    unsigned int m_widthInTiles;
    sf::Vector2f m_tileSize;
};

#endif
