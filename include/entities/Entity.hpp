#ifndef ENTITY_HPP
# define ENTITY_HPP

# include <string>
# include <SFML/Graphics.hpp>
# include "Window.hpp"

class Entity : public sf::Drawable
{
  public:
    Entity(
      const std::string &name,
      const std::string &texturePath,
      const sf::Vector2f &pos,
      const int &incrementSpeed,
      sf::Time *elapsed);
    ~Entity();

    void moveForward();
    void moveBackward();
    void rotateLeft();
    void rotateRight();
    //bool isColliding(const Entity &other) const;
    void boundInWindow(const Window &window);

  private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    const float _getMoveSpeed() const;
    const float _getRotationSpeed() const;
    const float _getAngleRadians() const;

  protected:
    std::string m_name;
    sf::Texture m_texture;
    sf::Sprite m_sprite;
    sf::Time *m_elapsed;
    int m_incrementSpeed;
    int m_rotationSpeed;
};

#endif
