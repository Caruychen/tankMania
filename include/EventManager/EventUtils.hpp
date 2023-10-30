#ifndef EVENTUTILS_HPP
# define EVENTUTILS_HPP

# include <functional>
# include <SFML/Window.hpp>

enum class EventType
{
  KeyDown = sf::Event::KeyPressed,
  KeyUp = sf::Event::KeyReleased,
  MButtonDown = sf::Event::MouseButtonPressed,
  MButtonUp = sf::Event::MouseButtonReleased,
  MouseWheel = sf::Event::MouseWheelMoved,
  WindowResized = sf::Event::Resized,
  GainedFocus = sf::Event::GainedFocus,
  LostFocus = sf::Event::LostFocus,
  MouseEntered = sf::Event::MouseEntered,
  MouseLeft = sf::Event::MouseLeft,
  Closed = sf::Event::Closed,
  TextEntered = sf::Event::TextEntered,
  Keyboard = sf::Event::Count + 1, Mouse
};

struct EventInfo
{
  EventInfo();
  EventInfo(int event);
  union
  {
    int m_code;
  };
};

using Events = std::vector<std::pair<EventType, EventInfo>>;

struct EventDetails
{
  EventDetails(const std::string& bindName);
  void clear();

  std::string m_name;
  sf::Vector2i m_size;
  sf::Uint32 m_textEntered;
  sf::Vector2i m_mouse;
  int m_mouseWheelDelta;
  int m_keyCode;
};

struct Binding
{
  Binding(const std::string &name);
  void bindEvent(EventType type, EventInfo info = EventInfo());

  std::string m_name;
  int m_count;
  Events m_events;
  EventDetails m_details;
};

using Bindings = std::unordered_map<std::string, Binding*>;
using Callbacks = std::unordered_map<std::string, std::function<void(EventDetails*)>>;

#endif
