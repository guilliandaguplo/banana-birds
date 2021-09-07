#include "player.h"
#include <iostream>


void Player::Draw(graphics::Image &background, std::vector<std::unique_ptr<graphics::Image> > &animations) {
  Helper(background, animations[frame].get(), GetX(), GetY());
  (frame == 8) ? frame = 0 : frame++;
}
void PlayerProjectile::Draw(graphics::Image &background, std::vector<std::unique_ptr<graphics::Image> > &animations) {
  int x, y;
  x = GetX();
  y = GetY();
  Helper(background, banana, x, y);
}

void Player::Move(const graphics::Image &gameScreen) {}
void PlayerProjectile::Move(const graphics::Image &gameScreen) {
  if (!IsOutOfBounds(gameScreen)) {
   y_ -= 20; // Temp
  } else {
    SetIsActive(false);
    std::cout << "Error: unable to move PlayerProjectile object\n";
  }
}
