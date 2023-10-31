#ifndef ARENA_HPP
# define ARENA_HPP

# include <SFML/Graphics.hpp>

# define ARENA_WIDTH 1200
# define ARENA_HEIGHT 600

class Arena : public sf::Drawable
{
  public:
    Arena(const std::string &mapFile);
    ~Arena();
    void load(void);
    const sf::Vector2u getSize() const;

  private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void _readMap(const std::string& mapFile);
    void _loadTiles(void);
    void _loadWalls(void);

    std::vector<uint8_t> m_data;
    std::vector<sf::FloatRect> m_walls;
    sf::VertexArray m_vertices;
    sf::Vector2f m_arenaSize;
    sf::Vector2f m_tileSize;
    unsigned int m_heightInTiles;
    unsigned int m_widthInTiles;
};

#endif
