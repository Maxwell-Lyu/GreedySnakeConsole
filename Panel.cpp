#include "Game.h"

void Game::DrawPanel() {
  Render::Draw(this->xBound.second + 3, 3, "▓▓▓▓▓▓", Color::GRN, true);
  Render::Draw(this->xBound.second + 3, 4, "▓▓    ", Color::GRN, true);
  Render::Draw(this->xBound.second + 3, 5, "▓▓  ▓▓", Color::GRN, true);
  Render::Draw(this->xBound.second + 3, 6, "▓▓  ▓▓", Color::GRN, true);
  Render::Draw(this->xBound.second + 3, 7, "▓▓▓▓▓▓", Color::GRN, true);
  Render::Draw(this->xBound.second + 6, 3, "▓▓▓▓▓▓", Color::BLU, true);
  Render::Draw(this->xBound.second + 6, 4, "▓▓    ", Color::BLU, true);
  Render::Draw(this->xBound.second + 6, 5, "▓▓▓▓▓▓", Color::BLU, true);
  Render::Draw(this->xBound.second + 6, 6, "    ▓▓", Color::BLU, true);
  Render::Draw(this->xBound.second + 6, 7, "▓▓▓▓▓▓", Color::BLU, true);

  Render::Draw(this->xBound.second + 1, 10, "█████▶ STATUS ◀█████", Color::WHT, true);
  Render::Draw(this->xBound.second + 1, 11, "░░░              ░░░", Color::CYN, true);
  Render::Draw(this->xBound.second + 1, 13, "█████▶ POINTS ◀█████", Color::WHT, true);
  Render::Draw(this->xBound.second + 1, 14, "░░░              ░░░", Color::BLU, true);
  Render::Draw(this->xBound.second + 1, 16, "█████▶ BONUS  ◀█████", Color::WHT, true);
  Render::Draw(this->xBound.second + 1, 17, "░░░              ░░░", Color::CYN, true);
  Render::Draw(this->xBound.second + 1, 19, "█████▶ SPEED  ◀█████", Color::WHT, true);
  Render::Draw(this->xBound.second + 1, 20, "░░░              ░░░", Color::BLU, true);
  Render::Draw(this->xBound.second + 1, 22, "█████▶  MODE  ◀█████", Color::WHT, true);
  Render::Draw(this->xBound.second + 1, 23, "░░░              ░░░", Color::CYN, true);
}


void Game::PanelSetScore(int score) {
  char buf[16];
  sprintf(buf, "% *d", 12, score);
  Render::Draw(this->xBound.second + 3, 14, buf, Color::BLU, true);
}
void Game::PanelSetStatus(int state) {
  this->status = state;
  switch (state) {
    case RUNNING : Render::Draw(this->xBound.second + 1, 11, "░░░ GAME RUNNING ░░░", Color::GRN, true); break;
    case PAUSE   : Render::Draw(this->xBound.second + 1, 11, "░░░    PAUSED    ░░░", Color::YLW, true); break;
    case OVER    : Render::Draw(this->xBound.second + 1, 11, "░░░  GAME OVER!  ░░░", Color::RED, true); break;
    case READY   : Render::Draw(this->xBound.second + 1, 11, "░░░  GAME READY  ░░░", Color::CYN, true); break;
  }
}

void Game::PanelSetBonus(bool isCountDown, int val) {
  if(isCountDown) {
    char buf[4];
    sprintf(buf, "%d", val / 1000 + 1);
    Render::Draw(this->xBound.second + 1, 17, "░░░              ░░░", Color::YLW, true);
    Render::Draw(this->xBound.second + 6, 17, buf, Color::YLW, true);
  }
  else {
    char buf[4];
    sprintf(buf, "%d", 5-val);
    Render::Draw(this->xBound.second + 1, 17, "░░░              ░░░", Color::GRN, true);
    Render::Draw(this->xBound.second + 6, 17, buf, Color::GRN, true);
  }
}

void Game::PanelSetSpeed() {
  
  char buf[8];
  sprintf(buf, "%2d FPS", 1000 / this->fps);
  Render::Draw(this->xBound.second + 4, 20, buf, Color::BLU, true);
}

void Game::PanelSetMode() {
  if(this->mode)
    Render::Draw(this->xBound.second + 1, 23, "░░░   CHAMPION   ░░░", Color::YLW, true);
  else
    Render::Draw(this->xBound.second + 1, 23, "░░░   ZEN MODE   ░░░", Color::GRN, true);
}

void Game::PanelDelBonus() {
  Render::Draw(this->xBound.second + 1, 17, "░░░              ░░░", Color::CYN, true);
}


void Game::PanelHint() {
  switch (this->status) {
    case READY:
    case OVER: {
      Render::Draw(this->xBound.second + 1, 25, "█████▶  HINT  ◀█████", Color::WHT, true);
      Render::Draw(this->xBound.second + 1, 26, "[S] ▶ START GAME    ", Color::CYN, true);    
      Render::Draw(this->xBound.second + 1, 27, "[T] ▶ TOGGLE SPEED  ", Color::CYN, true);
      Render::Draw(this->xBound.second + 1, 28, "[M] ▶ TOGGLE MODE   ", Color::CYN, true);
      break;
    }
    case RUNNING: {
      Render::Draw(this->xBound.second + 1, 25, "█████▶  HINT  ◀█████", Color::WHT, true);
      Render::Draw(this->xBound.second + 1, 26, "[P] ▶ PAUSE         ", Color::CYN, true);    
      Render::Draw(this->xBound.second + 1, 27, "[↕][↔] ▶ MOVE       ", Color::GRN, true);
      Render::Draw(this->xBound.second + 1, 28, "                    ", Color::CYN, true);
      break;
    }
    case PAUSE: {
      Render::Draw(this->xBound.second + 1, 25, "█████▶  HINT  ◀█████", Color::WHT, true);
      Render::Draw(this->xBound.second + 1, 26, "[P] ▶ RESUME        ", Color::CYN, true);    
      Render::Draw(this->xBound.second + 1, 27, "[Q] ▶ QUIT GAME     ", Color::CYN, true);
      Render::Draw(this->xBound.second + 1, 28, "                    ", Color::CYN, true);
      break;
    }
  }
}