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

void Game::Build() {
  timeb time;
  ftime(&time);
  srand(time.time);
  render->SizeScreen(48, 30);
  render->ClearScreen();
  render->HideCursor();
  if(this->snake != nullptr) delete this->snake;
  this->Score = 0;
  this->snake = new Snake({1,30}, {1,30}, this->direction);
}

uint64_t getTime() {
  timeb time;
  ftime(&time);
  return time.time * 1000 + time.millitm;
}

void Game::Loop() {
  const int fps = 100;
  uint64_t time0 = getTime();
  int foodCount = 0;
  uint64_t time_bonus_start = 0;
  Direction d = this->direction;
  while(1) {
    if(kbhit()) {
      switch(getch()) {
        case 224:
          switch (getch()) {
            case 72: d = Direction::UP; break;
            case 75: d = Direction::LT; break;
            case 80: d = Direction::DN; break;
            case 77: d = Direction::RT; break;
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
          break;
        } 
        case BONUS:   break;
        case EMPTY:   break;
      }
      time0 += fps;
    }
    else {
      _sleep(50);
    }


    if(time_bonus_start && getTime() > 5000 + time_bonus_start) {
      this->snake->foods.dropBonus();
      time_bonus_start = 0;
    }
  }
}

Game::~Game() {
  delete this->snake;
  delete this->render;
}