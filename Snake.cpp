#include "Snake.h"

Snake::Snake(Render& render, Direction d, int x, int y, int len, Color color): render(render), direction(d), color(color) {
  switch(d) {
    case UP: for(int i = 0; i < len; i++) this->points.emplace_back(std::make_pair(x, y + i)); break;
    case LT: for(int i = 0; i < len; i++) this->points.emplace_back(std::make_pair(x + i, y)); break;
    case DN: for(int i = 0; i < len; i++) this->points.emplace_back(std::make_pair(x, y - i)); break;
    case RT: for(int i = 0; i < len; i++) this->points.emplace_back(std::make_pair(x - i, y)); break;
  }
}


void Snake::Print() {
  for(std::deque<std::pair<int,int>>::iterator it = this->points.begin(); it != this->points.end(); ++it)
    this->render.Draw( std::get<0>(*it), std::get<1>(*it), it == this->points.begin() ? "██" : "▒▒", this->color);
}

void Snake::Move() {
  std::pair<int,int> to_add, to_fad, to_del;
  switch(this->direction) {
    case Direction::UP: { to_fad = this->points.front(); to_del = this->points.back(); to_add = std::make_pair(std::get<0>(to_fad), std::get<1>(to_fad) - 1); break; }
    case Direction::LT: { to_fad = this->points.front(); to_del = this->points.back(); to_add = std::make_pair(std::get<0>(to_fad) - 1, std::get<1>(to_fad)); break; }
    case Direction::DN: { to_fad = this->points.front(); to_del = this->points.back(); to_add = std::make_pair(std::get<0>(to_fad), std::get<1>(to_fad) + 1); break; }
    case Direction::RT: { to_fad = this->points.front(); to_del = this->points.back(); to_add = std::make_pair(std::get<0>(to_fad) + 1, std::get<1>(to_fad)); break; }
  }
  this->render.Draw(std::get<0>(to_add), std::get<1>(to_add), "██", this->color);
  this->render.Draw(std::get<0>(to_fad), std::get<1>(to_fad), "▒▒", this->color);
  this->render.Draw(std::get<0>(to_del), std::get<1>(to_del), "  ", this->color);
  this->points.emplace_front(to_add);
  this->points.pop_back();
}