#include "Game.h"

Game::Game() {
}

void Game::Framework() {
  Render::SizeScreen(this->xBound.second + 10, this->yBound.second);
  Render::ClearScreen();
  Render::HideCursor();
  this->DrawPanel();
  this->PanelHint();
  this->PanelSetStatus(READY);
  this->PanelSetSpeed();
  this->PanelSetMode();
  while(1) {
    if(kbhit()) {
      switch (getch()) {
        case 115: {
          Render::ClearScreen();
          this->DrawPanel();
          int score = this->Loop(); 
          this->LeaderBoard(score);
          this->PanelDelBonus();
          this->PanelHint();
          break;
        }
        case 109: {
          this->mode = 1 - this->mode; 
          this->PanelSetMode();
          break;
        }
        case 116: {
          this->fps = (this->fps - 200 + 400) % 400 + 100;
          this->PanelSetSpeed();
          break;
        }
      }
    }
    _sleep(200);
  }
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
  Direction d = UP;
  this->snake = new Snake(this->xBound, this->yBound, d, (this->xBound.first + this->xBound.second)/2, (this->yBound.first + this->yBound.second)/2);
  if(this->mode) Render::DrawRect(this->xBound, this->yBound, "▓▓", Color::RED);
  int Score = 0;
  uint64_t time0 = getTime();
  int foodCount = 0;
  uint64_t time_bonus_start = 0;

  this->PanelSetStatus(RUNNING);
  this->PanelSetSpeed();
  this->PanelSetMode();
  this->PanelHint();
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
          this->PanelHint();
          int bonusUsed = getTime() - time_bonus_start;
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
          this->PanelSetStatus(READY);
          _sleep(1000);
          time0 = getTime();
          if(time_bonus_start) time_bonus_start = time0 - bonusUsed;
          this->PanelSetStatus(RUNNING);
          this->PanelHint();
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
          Score += (int)(1000 / this->fps) * 10;
          break;
        } 
        case BONUS: {
          Score += (int)(1000 / this->fps) * 50; 
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


    if(time_bonus_start && getTime() > this->fps * 30 + time_bonus_start) {
      this->snake->foods.dropBonus();
      time_bonus_start = 0;
    }
    if(time_bonus_start) {
      this->PanelSetBonus(true, this->fps * 30 - getTime() + time_bonus_start);
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
}
