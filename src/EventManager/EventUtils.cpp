#include "EventUtils.hpp"

// Event Info Struct
EventInfo::EventInfo()
{
  m_code = 0;
}

EventInfo::EventInfo(int event)
{
  m_code = event;
}

// Event Details Struct
EventDetails::EventDetails(const std::string& bindName) : m_name(bindName)
{
  clear();
}

void EventDetails::clear()
{
  m_size = sf::Vector2i(0, 0);
  m_textEntered = 0;
  m_mouse = sf::Vector2i(0, 0);
  m_mouseWheelDelta = 0;
  m_keyCode = -1;
}

// Binding Struct
Binding::Binding(const std::string& name) : m_name(name), m_details(name), m_count(0)
{}

void Binding::bindEvent(EventType type, EventInfo info)
{
  m_events.emplace_back(type, info);
}
