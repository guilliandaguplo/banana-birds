#include <iostream>
// #include "game_element.h"
#include "opponent.h"
#include "player.h"
#include "cpputils/graphics/image_event.h"

#ifndef GAME_H
#define GAME_H

class Game : public graphics::AnimationEventListener, public graphics::MouseEventListener {
 public:
  Game() : Game(800, 600) {}
  Game(const int &width, const int &height) : gameState(false), score_(0) {
    gameScreen.Initialize(width, height);
    gameScreen.Load("map.bmp");
    LoadAnimations();
    playerTalking.SetX(0);
    playerTalking.SetY(399);
  }
  void CreateOpponents(int count);
  void LaunchProjectiles();
  void Init();
  void UpdateScreen();
  void Start();
  void MoveGameElements();
  void FilterIntersections();
  void OnAnimationStep() override;
  void OnMouseEvent(const graphics::MouseEvent &event) override;
  bool HasLost() const { return gameState; }
  int GetScore() const { return score_; }
  void RemoveInactive();

  // Accessors
  graphics::Image &GetGameScreen() { return gameScreen; }
  std::vector<std::unique_ptr<Opponent> > &GetOpponents() { return olist; }
  std::vector<std::unique_ptr<OpponentProjectile> > &GetOpponentProjectiles() { return oshots_; }
  std::vector<std::unique_ptr<PlayerProjectile> > &GetPlayerProjectiles() { return pshots_; }
  Player &GetPlayer() { return player_; }

  void LoadAnimations() {
    for (size_t i = 1; i <= 9; i++) {
      int p = i;
      std::unique_ptr<graphics::Image> frame = std::make_unique<graphics::Image>();
      std::string prefix = "player";
      frame->Load(prefix + std::to_string(p) + ".bmp");
      paFrames.push_back(std::move(frame));
    }
    for (size_t i = 1; i <= 4; i++) {
      int p = i;
      std::unique_ptr<graphics::Image> frame = std::make_unique<graphics::Image>();
      std::string prefix = "opponent";
      frame->Load(prefix + std::to_string(p) + ".bmp");
      oaFrames.push_back(std::move(frame));
    }
    for (size_t i = 0; i < 8; i++) {
      int p = i;
      std::unique_ptr<graphics::Image> frame = std::make_unique<graphics::Image>();
      std::string prefix = "test";
      frame->Load(prefix + std::to_string(p) + ".bmp");
      playerTalkFrames.push_back(std::move(frame));
    }
  }

 private:
  graphics::Image gameScreen, map;
  std::vector<std::unique_ptr<Opponent> > olist;
  std::vector<std::unique_ptr<OpponentProjectile> > oshots_;
  std::vector<std::unique_ptr<PlayerProjectile> > pshots_;

  Player player_;
  PlayerTalking playerTalking;
  int score_, deathCount = 0;
  bool gameState, gameStarted = false;

  std::vector<std::unique_ptr<graphics::Image> > paFrames;
  std::vector<std::unique_ptr<graphics::Image> > oaFrames;
  std::vector<std::unique_ptr<graphics::Image> > gameAnimation;
  std::vector<std::unique_ptr<graphics::Image> > playerTalkFrames;
};

#endif
