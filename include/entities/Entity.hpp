#ifndef ENTITY_HPP
# define ENTITY_HPP
# define _USE_MATH_DEFINES

# include <string>
# include <SFML/Graphics.hpp>
# include "Arena.hpp"
# include "Collider.hpp"

# define BOUNDING_BUFFER 1

class Entity : public sf::Drawable, public Collider
{
  public:
    Entity(
      const std::string &texturePath,
      const sf::Vector2f &pos,
      const float &rotation,
      const sf::Vector2f &scale,
      const int &incrementSpeed,
      sf::Time *elapsed);
    ~Entity();

    // Transformations
    void move(const int direction);
    void rotate(const int direction);
    void setScale(sf::Vector2f scale);
    void setPos(sf::Vector2f pos);
    void setRotation(float rotation);
    sf::Vector2f getSize() const;
    sf::Vector2f getPos() const;
    
  protected:
    void _offsetArenaCollision(const Arena &arena);
    bool _isCollidingBoundary(const Arena &arena) const;
    bool _isCollidingWalls(std::vector<sf::FloatRect> walls);

    sf::Texture m_texture;
    sf::Sprite m_sprite;
    sf::Time *m_elapsed;
    int m_incrementSpeed;
    int m_rotationSpeed;

  private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void _boundInArena(const Arena &arena);
    void _offsetWallCollisions(std::vector<sf::FloatRect> walls);
};

#endif
