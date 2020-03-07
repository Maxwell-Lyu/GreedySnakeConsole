#include "Game.h"

Snake::Snake(std::pair<int, int> xBound, std::pair<int, int> yBound, Direction d, int x, int y, int len, Color color): direction(d), color(color) {
  switch(d) {
    case UP: for(int i = 0; i < len; i++) this->points.emplace_back(std::make_pair(x, y + i)); break;
    case LT: for(int i = 0; i < len; i++) this->points.emplace_back(std::make_pair(x + i, y)); break;
    case DN: for(int i = 0; i < len; i++) this->points.emplace_back(std::make_pair(x, y - i)); break;
    case RT: for(int i = 0; i < len; i++) this->points.emplace_back(std::make_pair(x - i, y)); break;
  }
  this->Print();
  this->xBound = xBound;
  this->yBound = yBound;
  this->foods.setFood(this->points, xBound, yBound);
}


void Snake::Print() {
  for(std::deque<std::pair<int,int>>::iterator it = this->points.begin(); it != this->points.end(); ++it)
    Render::Draw( std::get<0>(*it), std::get<1>(*it), it == this->points.begin() ? "██" : "▓▓", this->color);
}

void Snake::setDirection(Direction d) {
  if((this->direction ^ d) & 1)
    this->direction = d; 
}




int Snake::Move(bool getFood) {
  std::pair<int,int> to_add, to_fad, to_del;
  switch(this->direction) {
    case Direction::UP: { 
      to_fad = this->points.front(); 
      to_del = this->points.back(); 
      to_add = Render::justifyPoint({std::get<0>(to_fad), std::get<1>(to_fad) - 1}, this->xBound, this->yBound); 
      break; }
    case Direction::LT: { 
      to_fad = this->points.front(); 
      to_del = this->points.back(); 
      to_add = Render::justifyPoint({std::get<0>(to_fad) - 1, std::get<1>(to_fad)}, this->xBound, this->yBound); 
      break; }
    case Direction::DN: { 
      to_fad = this->points.front(); 
      to_del = this->points.back(); 
      to_add = Render::justifyPoint({std::get<0>(to_fad), std::get<1>(to_fad) + 1}, this->xBound, this->yBound); 
      break; }
    case Direction::RT: { 
      to_fad = this->points.front(); 
      to_del = this->points.back(); 
      to_add = Render::justifyPoint({std::get<0>(to_fad) + 1, std::get<1>(to_fad)}, this->xBound, this->yBound); 
      break; }
  }
  Render::Draw(std::get<0>(to_add), std::get<1>(to_add), "██", this->color);
  Render::Draw(std::get<0>(to_fad), std::get<1>(to_fad), "▓▓", this->color);
  this->points.emplace_front(to_add);
  switch(this->foods.checkFood(to_add)) {
    case EMPTY: {
      Render::Draw(std::get<0>(to_del), std::get<1>(to_del), "  ", this->color);
      this->points.pop_back();
      return EMPTY;
    }
    case BONUS: return BONUS;
    case FOOD: this->foods.setFood(this->points, xBound, yBound); return FOOD;
  }
}


Snake::~Snake() {
  this->points.clear();
}