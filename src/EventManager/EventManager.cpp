#include "EventManager.hpp"

EventManager::EventManager() : m_hasFocus(true)
{
  this->_loadBindings();
}

EventManager::~EventManager()
{
  for (auto &itr: this->m_bindings)
  {
    delete itr.second;
    itr.second = nullptr;
  }
}

bool EventManager::addBinding(Binding *binding)
{
  if (this->m_bindings.find(binding->m_name) != this->m_bindings.end())
    return (false);
  return (this->m_bindings.emplace(binding->m_name, binding).second);
}

bool EventManager::removeBinding(const std::string &name)
{
  auto itr = this->m_bindings.find(name);
  if (itr == this->m_bindings.end())
    return (false);
  delete itr->second;
  this->m_bindings.erase(itr);
  return (true);
}

void EventManager::setFocus(const bool &focus)
{
  m_hasFocus = focus;
}

void EventManager::removeCallback(const std::string &name)
{
  m_callbacks.erase(name);
}

void EventManager::handleEvent(sf::Event &event)
{
  /* Handles SFML Events */
  for (auto &b_itr: this->m_bindings)
  {
    Binding *bind = b_itr.second;
    for (auto &e_itr: bind->m_events)
    {
      EventType sfmlEvent = (EventType) event.type;
      if (e_itr.first != sfmlEvent)
        continue;
      switch (sfmlEvent)
      {
        case EventType::KeyDown:
        case EventType::KeyUp:
          if (e_itr.second.m_code == event.key.code)
          {
            if (bind->m_details.m_keyCode != -1)
              bind->m_details.m_keyCode = e_itr.second.m_code;
            ++(bind->m_count);
          }
          break;
        case EventType::MButtonDown:
        case EventType::MButtonUp:
          if (e_itr.second.m_code == event.mouseButton.button)
          {
            bind->m_details.m_mouse.x = event.mouseButton.x;
            bind->m_details.m_mouse.y = event.mouseButton.y;
            if (bind->m_details.m_keyCode != -1)
              bind->m_details.m_keyCode = e_itr.second.m_code;
            ++(bind->m_count);
          }
          break;
        case EventType::MouseWheel:
          bind->m_details.m_mouseWheelDelta = event.mouseWheel.delta;
          ++(bind->m_count);
          break;
        case EventType::WindowResized:
          bind->m_details.m_size.x = event.size.width;
          bind->m_details.m_size.y = event.size.height;
          ++(bind->m_count);
          break;
        case EventType::TextEntered:
          bind->m_details.m_textEntered = event.text.unicode;
          ++(bind->m_count);
          break;
        default:
          ++(bind->m_count);
          break;
      }
    }
  }
}

void EventManager::update()
{
  if (!m_hasFocus)
    return;
  for (auto &b_itr: this->m_bindings)
  {
    Binding *bind = b_itr.second;
    for (auto &e_itr: bind->m_events)
    {
      switch (e_itr.first)
      {
        case EventType::Keyboard:
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(e_itr.second.m_code)))
          {
            if (bind->m_details.m_keyCode != -1)
              bind->m_details.m_keyCode = e_itr.second.m_code;
            ++(bind->m_count);
          }
          break;
        case EventType::Mouse:
          if (sf::Mouse::isButtonPressed(sf::Mouse::Button(e_itr.second.m_code)))
          {
            if (bind->m_details.m_keyCode != -1)
              bind->m_details.m_keyCode = e_itr.second.m_code;
            ++(bind->m_count);
          }
          break;
        default:
          break;
      }
    }
    if (bind->m_events.size() == bind->m_count)
    {
      auto callItr = m_callbacks.find(bind->m_name);
      if (callItr != m_callbacks.end())
        callItr->second(&bind->m_details);
    }
    bind->m_count = 0;
    bind->m_details.clear();
  }
}

sf::Vector2i EventManager::getMousePos(sf::RenderWindow *window)
{
  return (window ? sf::Mouse::getPosition(*window) : sf::Mouse::getPosition());
}

void EventManager::_loadBindings()
{
  std::string delimiter = ":";
  std::ifstream bindings;
  std::string line;

  bindings.open("config/keys.cfg");
  if (!bindings.is_open())
    throw std::runtime_error("Failed loading keys.cfg");
  while (std::getline(bindings, line))
  {
    std::stringstream keystream(line);
    std::string callbackName;
    keystream >> callbackName;
    Binding *bind = new Binding(callbackName);
    while (!keystream.eof())
    {
      std::string keyval;
      keystream >> keyval;
      int start = 0;
      int end = keyval.find(delimiter);
      if (end == std::string::npos)
      {
        delete bind;
        bind = nullptr;
        break;
      }
      EventType type = EventType(stoi(keyval.substr(start, end - start)));
      int code = stoi(keyval.substr(
        end + delimiter.length(),
        keyval.find(delimiter, end + delimiter.length())
      ));
      EventInfo eventInfo;
      eventInfo.m_code = code;
      bind->bindEvent(type, eventInfo);
    }
    if (!this->addBinding(bind))
      delete bind;
    bind = nullptr;
  }
  bindings.close();
}
