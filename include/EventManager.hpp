#ifndef EVENTMANAGER_HPP
# define EVENTMANAGER_HPP

class EventManager
{
  public:
    EventManager();
    ~EventManager();

    void handleEvent(sf::Event &event);

  private:
    bool m_hasFocus;
};

#endif
