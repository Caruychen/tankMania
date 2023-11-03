#ifndef TANK_HPP
# define TANK_HPP

# include "Entity.hpp"
# include "Projectile.hpp"

# define TANK_SCALE 0.25f
# define AMMO_DISPLAY_PADDING 15
# define MAX_AMMO 5
# define INITIAL_AMMO 1

struct Ammunition
{
  unsigned int max;
  std::vector<std::unique_ptr<Projectile>> ammo;
};

class Tank : public Entity
{
  public:
    Tank(
      const unsigned int &number,
      const std::string &texturePath,
      const sf::Vector2f &pos,
      const float &rotation,
      const int &incrementSpeed,
      sf::Time *elapsed);
    ~Tank();

    void shoot();
    std::vector<std::unique_ptr<Projectile>> &getProjectiles(void);

  protected:
    void updateProjectiles(const Arena &arena);
    void deleteProjectile(int index);
    void _addAmmo();

    Ammunition m_ammunition;
    std::vector<std::unique_ptr<Projectile>> m_projectiles;

  private:
    void _initAmmo();
    const unsigned int m_number;
};

#endif
