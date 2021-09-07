#ifndef GAME_ELEMENT_H
#define GAME_ELEMENT_H

#include <iostream>
#include "cpputils/graphics/image.h"


class GameElement {
 public:
  GameElement() : GameElement(0, 0, 50, 50) {}

  GameElement(const int &x, const int &y, const int width, const int &height)
      : x_(x), y_(y), width_(width), height_(height), is_active(true) {
        bananaImg.Load("banana.bmp");
        poopImg.Load("poop.bmp");
      }
  int GetWidth() const { return width_; }
  int GetHeight() const { return height_; }

  int GetX() const { return x_; }
  int GetY() const { return y_; }
  void SetX(int x) { x_ = x; }
  void SetY(int y) { y_ = y; }

  bool GetIsActive() const { return is_active; }
  void SetIsActive(const bool &active) { is_active = active; }

  void Helper(graphics::Image &background, graphics::Image* drawing, int x_, int y_);
  void rHelper(graphics::Image &background, graphics::Image* drawing, int x_, int y_);

  bool IntersectsWith(GameElement* object);
  bool IsOutOfBounds(const graphics::Image &gameScreen);
  
  virtual void Draw(graphics::Image &background, std::vector<std::unique_ptr<graphics::Image> > &animations) = 0;
  virtual void Move(const graphics::Image &gameScreen) = 0;
 protected:
  int width_, height_, x_, y_;
  bool is_active;
  graphics::Image bananaImg, poopImg;
  graphics::Image* banana = &bananaImg;
  graphics::Image* poop = &poopImg;
};

#endif
//Loading Animations???
// void LoadAnimations() {
  //   for (size_t i = 1; i <= 9; i++) {
  //     int p = i;
  //     std::unique_ptr<graphics::Image> frame = std::make_unique<graphics::Image>();
  //     std::string prefix = "player";
  //     frame->Load(prefix + std::to_string(p) + ".bmp");
  //     paFrames.push_back(std::move(frame));
  //   }
  //   for (size_t i = 0; i < 8; i++) {
  //     int p = i;
  //     std::unique_ptr<graphics::Image> frame = std::make_unique<graphics::Image>();
  //     std::string prefix = "test";
  //     frame->Load(prefix + std::to_string(p) + ".bmp");
  //     playerTalkFrames.push_back(std::move(frame));
  //   }
  //   for (size_t i = 1; i <= 4; i++) {
  //     int p = i;
  //     std::unique_ptr<graphics::Image> frame = std::make_unique<graphics::Image>();
  //     std::string prefix = "opponent";
  //     frame->Load(prefix + std::to_string(p) + ".bmp");
  //     oaFrames.push_back(std::move(frame));
  //   }
  //   // for (size_t i = 0; i < 64; i++) {
  //   //   int p = i;
  //   //   std::unique_ptr<graphics::Image> frame = std::make_unique<graphics::Image>();
  //   //   std::string prefix = std::to_string(p);
  //   //   frame->Load(prefix + "ICON.bmp");
  //   //   gameAnimation.push_back(std::move(frame));
  //   // }
  // }