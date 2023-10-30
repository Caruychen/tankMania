#ifndef EVENTMANAGER_HPP
# define EVENTMANAGER_HPP

# include <fstream>
# include <sstream>
# include <SFML/Graphics.hpp>
# include "EventUtils.hpp"

class EventManager
{
  public:
    EventManager();
    ~EventManager();

    bool addBinding(Binding *binding);
    bool removeBinding(const std::string &name);

    void setFocus(const bool &focus);

    template<class T>
    bool addCallback(const std::string &name, void(T::*func)(EventDetails*), T *instance)
    {
      auto temp = std::bind(func, instance, std::placeholders::_1);
      return m_callbacks.emplace(name, temp).second;
    }
    void removeCallback(const std::string &name);

    void handleEvent(sf::Event &event);
    void update();
    sf::Vector2i getMousePos(sf::RenderWindow *window = nullptr);

  private:
    void _loadBindings();
    Bindings m_bindings;
    Callbacks m_callbacks;
    bool m_hasFocus;
};

#endif
