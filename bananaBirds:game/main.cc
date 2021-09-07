#include "player.h"
#include "opponent.h"
#include "game.h"
#include "game_element.h"

int main() {
  //Creates a game object which starts the game.
  Game gameO;
  //will add events listeners to be able to detect mouse clicks and event listeners.
  gameO.Init();
  //Will show the screen until the game is exited out of.
  gameO.Start();
  return 0;
}
