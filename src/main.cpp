#include "Game.hpp"

int main()
{
  // Init game engine
  Game game;

  // Event polling
  while (game.running())
  {
    // Update
    game.update();

    // Rendering
    game.render();
    game.restartClock();
  }

  return 0;
}
