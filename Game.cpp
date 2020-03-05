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
  this->PanelHint();
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
          this->getPlayerName(score);
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
