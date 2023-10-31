#ifndef ENTITY_HPP
# define ENTITY_HPP

# include <string>
# include <SFML/Graphics.hpp>
# include "Arena.hpp"

# define BOUNDING_BUFFER 1

class Entity : public sf::Drawable
{
  public:
    Entity(
      const std::string &name,
      const std::string &texturePath,
      const sf::Vector2f &pos,
      const sf::Vector2f &scale,
      const int &incrementSpeed,
      sf::Time *elapsed);
    ~Entity();

    void moveForward();
    void moveBackward();
    void rotateLeft();
    void rotateRight();
    //bool isColliding(const Entity &other) const;
    void updateBounds(const Arena &arena);

  private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    // Accessors
    const float _getMoveSpeed() const;
    const float _getRotationSpeed() const;
    const float _getAngleRadians() const;

    // Boundary Handlers
    void _updateGlobalCorners(void);
    void _boundInArena(const Arena &arena);
    void _boundAgainstWalls(const Arena &arena);
    //const bool _test(sf::FloatRect wall)
    //const bool _isOverlapWall(const Arena &arena) const;
    struct vec2d
    {
      float x;
      float y;
    };
    std::vector<vec2d> m_lRelativeCorners;
    std::vector<vec2d> m_globalCorners;

  protected:
    std::string m_name;
    sf::Texture m_texture;
    sf::Sprite m_sprite;
    sf::Time *m_elapsed;
    int m_incrementSpeed;
    int m_rotationSpeed;
};

#endif
