#include "game_element.h"
#include <memory>
#include "cpputils/graphics/image.h"

// in charge of checking for overlaps, so we know if a game element is hit (using coordinates and general size)
bool GameElement::IntersectsWith(GameElement* object) {
  return (!(GetX() > object->GetX() + object->GetWidth() ||
        GetX() + GetWidth() < object->GetX() ||
        GetY() > object->GetY() + object->GetHeight() ||
        GetY() + GetHeight() < object->GetY()));
}
// Will check to see if game element being created is within the game screen.
bool GameElement::IsOutOfBounds(const graphics::Image &gameScreen) {
  return GetX() < 0 || GetY() < 0 || GetX() + GetWidth() > gameScreen.GetWidth() || GetY() + GetHeight() > gameScreen.GetHeight();
}
// Abstracting function that draws the image itself onto the screen which will be displayed.
void GameElement::Helper(graphics::Image &background, graphics::Image* drawing, int x_, int y_) {
   for (int i = 0; i < drawing->GetWidth(); i++) {
     int x = i;
     for (int j = 0; j < drawing->GetHeight(); j++) {
       int y = j;
       if (drawing->GetColor(i,j) != graphics::Color(0, 0, 0) && y_ + drawing->GetHeight() < background.GetHeight()) {
         background.SetColor((i + x_), (j + y_), drawing->GetColor(i,j));
       } else {
         continue;
       }
     }
   }
}

void GameElement::rHelper(graphics::Image &background, graphics::Image* drawing, int x_, int y_) {
  for (int i = drawing->GetWidth(); i > 0; i--) {
    int x = i;
    for (int j = drawing->GetHeight(); j > 0; j--) {
      int y = j;
      if (drawing->GetColor(i,j) != graphics::Color(0, 0, 0) && y_ + drawing->GetHeight() < background.GetHeight()) {
        background.SetColor((x_ - i), (j + y_), drawing->GetColor(i,j));
      } else {
        continue;
      }
    }
  }
}
