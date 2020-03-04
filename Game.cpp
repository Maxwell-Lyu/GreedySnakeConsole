#include "Game.h"


std::pair<int,int> justifyPoint(std::pair<int,int> p, std::pair<int, int> xBound, std::pair<int, int> yBound) {
  int x = std::get<0>(p);
  int y = std::get<1>(p);
  int x0 = std::get<0>(xBound);
  int x1 = std::get<1>(xBound) - x0 + 1;
  if(x0 >= 0 && x1 > 0) {
    while(x < x0) x += x1;
    x = (x - x0) % x1 + x0;
  }
  int y0 = std::get<0>(yBound);
  int y1 = std::get<1>(yBound) - y0 + 1;
  if(y0 >= 0 && y1 > 0) {
    while(y < y0) y += y1;
    y = (y - y0) % y1 + y0;
  }
  return {x,y};
}



Game::Game() {
  this->render = new Render();
}

void Game::Framework() {
  render->SizeScreen(this->xBound.second + 10, this->yBound.second);
  render->ClearScreen();
  render->HideCursor();
  this->DrawPanel();
  this->PanelSetStatus(READY);
  this->PanelSetSpeed();
  this->PanelSetMode();
  while(1) {
    if(kbhit()) {
      switch (getch()) {
        case 115: {
          render->ClearScreen();
          this->DrawPanel();
          int score = this->Loop(); 
          this->PanelDelBonus();
          break;
        }
        case 109: {
          this->mode = 1 - this->mode; 
          this->PanelSetMode();
          break;
        }
        case 61: {
          this->fps = (this->fps - 200 + 400) % 400 + 100;
          this->PanelSetSpeed();
          break;
        }
      }
    }
    _sleep(200);
  }
}


void Game::Build() {

}

uint64_t getTime() {
  timeb time;
  ftime(&time);
  return time.time * 1000 + time.millitm;
}

int Game::Loop() {
  timeb time;
  ftime(&time);
  srand(time.time);
  // if(this->snake != nullptr) delete this->snake;
  this->snake = new Snake(this->xBound, this->yBound, this->direction, (this->xBound.first + this->xBound.second)/2, (this->yBound.first + this->yBound.second)/2);
  if(this->mode) this->render->DrawRect(this->xBound, this->yBound, "▓▓", Color::RED);
  int Score = 0;
  uint64_t time0 = getTime();
  int foodCount = 0;
  uint64_t time_bonus_start = 0;
  Direction d = this->direction;

  this->PanelSetStatus(RUNNING);
  this->PanelSetSpeed();
  this->PanelSetMode();
  while(1) {
    if(kbhit()) {
      switch(getch()) {
        case 224: {
          switch (getch()) {
            case 72: d = Direction::UP; break;
            case 75: d = Direction::LT; break;
            case 80: d = Direction::DN; break;
            case 77: d = Direction::RT; break;
          }
          break;
        }
        case 112: {
          this->PanelSetStatus(PAUSE);
          while(1) {
            if(kbhit()) {
              char ch = getch();
              if(ch == 112) break;
              else if(ch == 113) {
                this->PanelSetStatus(OVER);
                return Score;
              }
            }
            _sleep(200);
          }
          time0 = getTime() + 2000;
          this->PanelSetStatus(RUNNING);
        }
      }
    }
    

    if(time0 + fps < getTime()) {
      this->snake->setDirection(d);
      switch(this->snake->Move()) {
        case FOOD: {
          if(++foodCount == 5) {
            foodCount = 0;
            time_bonus_start = getTime();
            this->snake->foods.setFood(this->snake->points, this->snake->xBound, this->snake->yBound, true);
          }
          Score += 100;
          break;
        } 
        case BONUS: {
          Score += 500; 
          time_bonus_start = 0; 
          break;
        }
        case EMPTY: break;
      }
      time0 += fps;
    }
    else {
      _sleep(50);
    }


    if(time_bonus_start && getTime() > this->fps * 50 + time_bonus_start) {
      this->snake->foods.dropBonus();
      time_bonus_start = 0;
    }
    if(time_bonus_start) {
      this->PanelSetBonus(true, this->fps * 50 - getTime() + time_bonus_start);
    }
    else {
      this->PanelSetBonus(false, foodCount);
    }
    this->PanelSetScore(Score);

    if(this->checkBound()) {
      this->PanelSetStatus(OVER);
      break;
    }
  }
  delete this->snake;
  return Score;
}


bool Game::checkBound() {
  std::pair<int,int> p = this->snake->points.front();
  for(std::deque<std::pair<int,int>>::iterator it = this->snake->points.begin(); it != this->snake->points.end(); ++it)
    if(it != this->snake->points.begin() && *it == p)
      return true;
  if(this->mode)
    if(p.first == this->xBound.first || p.first == this->xBound.second || p.second == this->yBound.first || p.second == this->yBound.second)
      return true;
  return false;
}


Game::~Game() {
  delete this->snake;
  delete this->render;
}





void Game::DrawPanel() {
  this->render->Draw(this->xBound.second + 3, 3, "▓▓▓▓▓▓", Color::GRN);
  this->render->Draw(this->xBound.second + 3, 4, "▓▓    ", Color::GRN);
  this->render->Draw(this->xBound.second + 3, 5, "▓▓  ▓▓", Color::GRN);
  this->render->Draw(this->xBound.second + 3, 6, "▓▓  ▓▓", Color::GRN);
  this->render->Draw(this->xBound.second + 3, 7, "▓▓▓▓▓▓", Color::GRN);
  this->render->Draw(this->xBound.second + 6, 3, "▓▓▓▓▓▓", Color::BLU);
  this->render->Draw(this->xBound.second + 6, 4, "▓▓    ", Color::BLU);
  this->render->Draw(this->xBound.second + 6, 5, "▓▓▓▓▓▓", Color::BLU);
  this->render->Draw(this->xBound.second + 6, 6, "    ▓▓", Color::BLU);
  this->render->Draw(this->xBound.second + 6, 7, "▓▓▓▓▓▓", Color::BLU);

  this->render->Draw(this->xBound.second + 1, 10, "█████▶ STATUS ◀█████", Color::WHT, true);
  this->render->Draw(this->xBound.second + 1, 11, "░░░              ░░░", Color::CYN, true);
  this->render->Draw(this->xBound.second + 1, 13, "█████▶ POINTS ◀█████", Color::WHT, true);
  this->render->Draw(this->xBound.second + 1, 14, "░░░              ░░░", Color::BLU, true);
  this->render->Draw(this->xBound.second + 1, 16, "█████▶ BONUS  ◀█████", Color::WHT, true);
  this->render->Draw(this->xBound.second + 1, 17, "░░░              ░░░", Color::CYN, true);
  this->render->Draw(this->xBound.second + 1, 19, "█████▶ SPEED  ◀█████", Color::WHT, true);
  this->render->Draw(this->xBound.second + 1, 20, "░░░              ░░░", Color::BLU, true);
  this->render->Draw(this->xBound.second + 1, 22, "█████▶  MODE  ◀█████", Color::WHT, true);
  this->render->Draw(this->xBound.second + 1, 23, "░░░              ░░░", Color::CYN, true);
}


void Game::PanelSetScore(int score) {
  char buf[16];
  sprintf(buf, "% *d", 12, score);
  this->render->Draw(this->xBound.second + 3, 14, buf, Color::BLU, true);
}
void Game::PanelSetStatus(int state) {
  switch (state) {
    case RUNNING : this->render->Draw(this->xBound.second + 1, 11, "░░░ GAME RUNNING ░░░", Color::GRN, true); break;
    case PAUSE   : this->render->Draw(this->xBound.second + 1, 11, "░░░    PAUSED    ░░░", Color::YLW, true); break;
    case OVER    : this->render->Draw(this->xBound.second + 1, 11, "░░░  GAME OVER!  ░░░", Color::RED, true); break;
    case READY   : this->render->Draw(this->xBound.second + 1, 11, "░░░  GAME READY  ░░░", Color::CYN, true); break;
  }
}

void Game::PanelSetBonus(bool isCountDown, int val) {
  if(isCountDown) {
    char buf[4];
    sprintf(buf, "%d", val / 1000 + 1);
    this->render->Draw(this->xBound.second + 1, 17, "░░░              ░░░", Color::YLW, true);
    this->render->Draw(this->xBound.second + 6, 17, buf, Color::YLW, true);
  }
  else {
    char buf[4];
    sprintf(buf, "%d", 5-val);
    this->render->Draw(this->xBound.second + 1, 17, "░░░              ░░░", Color::GRN, true);
    this->render->Draw(this->xBound.second + 6, 17, buf, Color::GRN, true);
  }
}

void Game::PanelSetSpeed() {
  
  char buf[8];
  sprintf(buf, "%2d FPS", 1000 / this->fps);
  this->render->Draw(this->xBound.second + 4, 20, buf, Color::BLU, true);
}

void Game::PanelSetMode() {
  if(this->mode)
    this->render->Draw(this->xBound.second + 1, 23, "░░░     WALL     ░░░", Color::RED, true);
  else
    this->render->Draw(this->xBound.second + 1, 23, "░░░     FREE     ░░░", Color::GRN, true);
}

void Game::PanelDelBonus() {
  this->render->Draw(this->xBound.second + 1, 17, "░░░              ░░░", Color::CYN, true);
}
