#include "cpputils/graphics/image.h"
#include "game_element.h"
#include "opponent.h"

#ifndef PLAYER_H
#define PLAYER_H

class Player : public GameElement {
 public:
  Player() : GameElement(0, 0, 35, 35) {}
  Player(const int &x, const int &y) : GameElement(x, y, 40, 40) {}
  //Added to satisfy Virtual function from game element, How the player is drawn is different
  void Draw(graphics::Image &background, std::vector<std::unique_ptr<graphics::Image> > &animations) override;
  //Added to satisfy Virtual function from game element, How the player is moved different
  void Move(const graphics::Image &gameScreen) override;
 private:
   int frame = 0;
};

class PlayerProjectile : public GameElement {
 public:
  PlayerProjectile() : GameElement(0, 0, 15, 15) {}
  PlayerProjectile(const int &x, const int &y) : GameElement(x, y, 15, 15) {}
  //Added to satisfy Virtual function from game element, How the playerprojectile is drawn is different
  void Draw(graphics::Image &background,std::vector<std::unique_ptr<graphics::Image> > &animations) override;
  //Added to satisfy Virtual function from game element, How the playerprojectile is drawn is different
  void Move(const graphics::Image &gameScreen) override;
};

#endif
