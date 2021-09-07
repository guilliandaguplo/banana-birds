#include "opponent.h"
#include <iostream>

 void Opponent::Move(const graphics::Image &gameScreen) {
   x_ += x_rate_;
   y_ += y_rate_;
 // Check for bounce conditions.
 if (x_ < 50) {
   x_rate_ *= -1;
   x_ = 50;
 } else if (x_ > gameScreen.GetWidth() - 100 / 2) {
   x_rate_ *= -1;
   x_ = gameScreen.GetWidth() - 101 / 2;
 }
 if (y_ < 50) {
   y_rate_ *= -1;
   y_ = 50;
 } else if (y_ > gameScreen.GetHeight() - 300) {
   y_rate_ *= -1;
   y_ = gameScreen.GetHeight() - 301;
 } else {
   //Create a function that tells the bird to the player x and y
 }
 }
 void OpponentProjectile::Move(const graphics::Image &gameScreen) {
    y_ += 10; // Temp
   if (IsOutOfBounds(gameScreen)) SetIsActive(false);
     // std::cout << "Error: unable to move OpponentProjectile object\n";
}
void Opponent::Draw(graphics::Image &background, std::vector<std::unique_ptr<graphics::Image> > &animations) {
  int x, y;
  x = GetX();
  y = GetY();
  if (x_rate_ < 0 && y_rate_ > 0) {
      Helper(background, animations[0].get(), x, y);
  } else if ( x_rate_ < 0 && y_rate_ < 0) {
     Helper(background, animations[frame].get(), x, y);
  } else if ( x_rate_ > 0 && y_rate_ > 0) {
     rHelper(background, animations[0].get(), x, y);
  } else if ( x_rate_ > 0 && y_rate_ < 0) {
     rHelper(background, animations[frame].get(), x, y);
  }
  frame == 3 ? frame = 0 : frame++;
}
void OpponentProjectile::Draw(graphics::Image &background, std::vector<std::unique_ptr<graphics::Image> > &animations) {
  Helper(background, poop, GetX(), GetY());
}
