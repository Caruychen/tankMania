#include "Flag.hpp"

Flag::Flag(const std::string &colour, const sf::Vector2f &pos) :
  Entity(
    "assets/flags/" + colour + "Flag.png",
    pos,
    0,
    {DEFAULT_FLAG_SCALE, DEFAULT_FLAG_SCALE},
    0,
    nullptr)
{}

Flag::~Flag()
{}
