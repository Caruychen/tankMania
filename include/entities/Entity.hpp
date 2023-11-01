#ifndef ENTITY_HPP
# define ENTITY_HPP

# include <string>
# include <SFML/Graphics.hpp>
# include "Arena.hpp"
# include "Collider.hpp"

# define BOUNDING_BUFFER 1

class Entity : public sf::Drawable, public Collider
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
    void updateBounds(const Arena &arena);

  private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    // Accessors
    const float _getMoveSpeed() const;
    const float _getRotationSpeed() const;
    const float _getAngleRadians() const;

    // Functions
    void _boundInArena(const Arena &arena);

  protected:
    std::string m_name;
    sf::Texture m_texture;
    sf::Sprite m_sprite;
    sf::Time *m_elapsed;
    int m_incrementSpeed;
    int m_rotationSpeed;
};

#endif
