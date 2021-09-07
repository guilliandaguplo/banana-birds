#include "game.h"
#include "opponent.h"
#include "player.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>

//Determines how fast frames will switch.
const int kAnimationMs = 35;

//Will create active opponents on the screen(but not drawn yet)
void Game::CreateOpponents(int count) {
  for (size_t i = 0; i < count; i++) {
    int x = rand() % 700 + 1;
    int y = rand() % 300 + 1;
    olist.push_back(std::make_unique<Opponent>(x,y));
  }
}
//Initializes the game screen and ensures that there is a player and clicking and animation features.
void Game::Init() {
  GetGameScreen().AddMouseEventListener(*this);
  GetGameScreen().AddAnimationEventListener(*this);
  //sets where player will be drawn
  player_.SetX(400);
  player_.SetY(500);
}
//Will start the game with the frame speed[see kAnimationMs desc.]
void Game::Start() {
  gameScreen.ShowUntilClosed("Banana Birds C:", kAnimationMs);
}
// Will move the GameElements to create a moving screen (Not drawing it though)
void Game::MoveGameElements() {
  for (int i = 0; i < olist.size(); i++) {
    if (olist[i]->GetIsActive())
    olist[i]->Move(GetGameScreen());
  }
  for (int i = 0; i < oshots_.size(); i++) {
    if (oshots_[i]->GetIsActive())
    oshots_[i]->Move(GetGameScreen());
  }
  for (int i = 0; i < pshots_.size(); i++) {
    if (pshots_[i]->GetIsActive())
    pshots_[i]->Move(GetGameScreen());
  }
}
void Game::LaunchProjectiles() {
   for (int i = 0; i < GetOpponents().size(); i++) {
    if (olist[i]->GetIsActive()) {
      std::unique_ptr<OpponentProjectile> oshot = olist[i]->LaunchProjectile();
      if (oshot != nullptr) {
        oshots_.push_back(std::move(oshot));
      } else continue;
    }
  }
}
void Game::RemoveInactive() {
  for (int i = olist.size() - 1; i >= 0; i--) {
    if (!(olist[i]->GetIsActive())) {
      olist.erase(olist.begin() + (i));
    }
  }
  for (int i = oshots_.size(); i > 0; i--) {
      if (!(oshots_[i-1]->GetIsActive())) {
      oshots_.erase(oshots_.begin() + (i-1));
    } else continue;
    }
  for (int i = pshots_.size(); i > 0; i--) {
      if (!(pshots_[i-1]->GetIsActive())) {
      pshots_.erase(pshots_.begin() + (i-1));
    } else continue;
  }
}
void Game::FilterIntersections() {
  for (int i = 0; i < olist.size(); i++) {
    for (int j = 0; j < pshots_.size(); j++) {
      if (olist[i]->IntersectsWith(pshots_[j].get())) {
        pshots_[j]->SetIsActive(false);
        olist[i]->SetIsActive(false);
        if (player_.GetIsActive()) score_ += 1;
      }
    }
  }
  for (int i = 0; i < oshots_.size(); i++) {
    if (player_.IntersectsWith(oshots_[i].get())) {
      oshots_[i]->SetIsActive(false);
      GetPlayer().SetIsActive(false);
      gameState = true;
  }
 }
 for (int i = 0; i < olist.size(); i++) {
   if (player_.IntersectsWith(olist[i].get())) {
     olist[i]->SetIsActive(false);
     GetPlayer().SetIsActive(false);
     gameState = true;
   }
 }
}
void Game::UpdateScreen() {

  if (!(HasLost())) {
  gameScreen.Load("map.bmp");
  std::string score = "Score: ";
  gameScreen.DrawText(0,0, score + std::to_string(GetScore()), 32, graphics::Color(0,0,0));
  std::string deathTrack = "Deaths: ";
  gameScreen.DrawText(650, 0, deathTrack + std::to_string(deathCount), 32, graphics::Color(0,0,0));
  if (player_.GetIsActive()) player_.Draw(gameScreen, paFrames);
  for (int i = 0; i < olist.size(); i++) {
      if (olist[i]->GetIsActive()) {
        olist[i]->Draw(gameScreen, oaFrames);
      }
    }
    for (int i = 0; i < oshots_.size(); i++) {
      if (oshots_[i]->GetIsActive() && !(oshots_[i]->IsOutOfBounds(gameScreen))) {
        oshots_[i]->Draw(gameScreen, oaFrames);
      }
    }
    for (int i = 0; i < pshots_.size(); i++) {
      if (pshots_[i]->GetIsActive() && !(pshots_[i]->IsOutOfBounds(gameScreen))) {
        pshots_[i]->Draw(gameScreen, paFrames);
      }
    }
  } else {
  oshots_.erase(oshots_.begin(),oshots_.end());
  pshots_.erase(pshots_.begin(),pshots_.end());
  olist.erase(olist.begin(),olist.end());
  gameScreen.Load("map.bmp");
  gameScreen.DrawText(gameScreen.GetWidth()/2 - 125,gameScreen.GetHeight()/2 - 50, "GAME OVER", 50, graphics::Color(196, 22, 22));
  gameScreen.DrawText(gameScreen.GetWidth()/2 - 225, gameScreen.GetHeight()/2, "Left Click to play again", 50, graphics::Color(225, 225, 225));
  }
}
void Game::OnAnimationStep() {
  if (olist.size() == 0) CreateOpponents(10 + rand() % 23);
  else if (olist.size() == 3) CreateOpponents(5 + rand() % 10);

  if (gameStarted) {
  MoveGameElements();
  LaunchProjectiles();
  FilterIntersections();
  RemoveInactive();
  UpdateScreen();
} else {
  gameScreen.Load("map.bmp");
  playerTalking.Draw(gameScreen,playerTalkFrames);
  gameScreen.DrawText(240,400, "Welcome to Banana Birds!", 50, graphics::Color(255, 255, 255));
  gameScreen.DrawText(200,450, "LEFT CLICK TO START THE GAME", 35, graphics::Color(255, 255, 255));
  for (size_t i = 0; i < olist.size(); i++) {
    olist[i]->Draw(gameScreen,oaFrames);
    olist[i]->Move(gameScreen);
  }

}
  GetGameScreen().Flush();
}
void Game::OnMouseEvent(const graphics::MouseEvent &event) {
  if (!gameStarted && event.GetMouseAction() == graphics::MouseAction::kPressed) {
    gameStarted = true;
  }
  if (event.GetMouseAction() == graphics::MouseAction::kMoved ||
      event.GetMouseAction() == graphics::MouseAction::kDragged) {
    int new_x = event.GetX() - player_.GetWidth() / 2;
    int new_y = event.GetY() - player_.GetHeight() / 2;
    int old_x = player_.GetX();
    int old_y = player_.GetY();
    player_.SetX(new_x);
    player_.SetY(new_y);

    if (player_.IsOutOfBounds(gameScreen)) {
      player_.SetX(old_x);
      player_.SetY(old_y);
    }
  }
  if (gameStarted && score_ < 100 && !HasLost() && event.GetMouseAction() == graphics::MouseAction::kPressed || event.GetMouseAction() == graphics::MouseAction::kReleased) {
     std::unique_ptr<PlayerProjectile> pshot = std::make_unique<PlayerProjectile>(GetPlayer().GetX()+(GetPlayer().GetWidth()/2), GetPlayer().GetY());
     GetPlayerProjectiles().push_back(std::move(pshot));
  } else if (gameStarted && HasLost() && event.GetMouseAction() == graphics::MouseAction::kPressed) {
    gameState = false;
    score_ = 0;
    deathCount++;
    player_.SetIsActive(true);
    UpdateScreen();
  }
}
