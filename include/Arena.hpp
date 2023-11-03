#ifndef ARENA_HPP
# define ARENA_HPP

# include <SFML/Graphics.hpp>
# include "Collider.hpp"

# define ARENA_WIDTH 1200
# define ARENA_HEIGHT 600

enum class TileType
{
    EMPTY = 0,
    WALL,
    ZONE_ONE,
    ZONE_TWO,
    FLAG_ONE,
    FLAG_TWO,
    PLAYER_ONE,
    PLAYER_TWO
};

struct PlayerConfigs
{
    std::vector<Collider> zones;
    sf::Vector2f flagPos;
    sf::Vector2f spawnPos;
    float spawnRotation;
};

class Arena : public sf::Drawable
{
  public:
    Arena(const std::string &mapFile);
    Arena(const std::vector<std::string> &mapFiles);
    ~Arena();
    void load(unsigned int mapNumber);
    const sf::Vector2u getSize() const;
    const std::vector<sf::FloatRect> getWalls() const;
    const std::pair<PlayerConfigs, PlayerConfigs> getPlayerConfigs() const;
    const std::vector<sf::Vector2f> getSpaces() const;

  private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void _initColors(void);
    void _readMap(const std::string& mapFile);
    void _loadTiles(void);
    void _loadBounds(void);
    void _loadObjects(void);

    std::vector<std::string> m_mapFiles;
    std::vector<unsigned int> m_data;
    std::vector<sf::FloatRect> m_walls;
    std::pair<PlayerConfigs, PlayerConfigs> m_playerConfigs;
    sf::VertexArray m_vertices;
    sf::VertexArray m_bounds;
    sf::Vector2f m_arenaSize;
    sf::Vector2f m_tileSize;
    std::vector<sf::Vector2f> m_spaces;
    std::vector<sf::Color> m_colors;
    unsigned int m_heightInTiles;
    unsigned int m_widthInTiles;
};

#endif
