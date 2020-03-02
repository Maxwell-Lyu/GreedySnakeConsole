#include "Snake.h"
Snake::Snake(Render& render, Direction d, int x, int y, int len): render(render), direction(d) {
  switch(d) {
    case UP: for(int i = 0; i < len; i++) this->points.emplace_back(std::make_pair(x, y + i)); break;
    case LT: for(int i = 0; i < len; i++) this->points.emplace_back(std::make_pair(x + i, y)); break;
    case DN: for(int i = 0; i < len; i++) this->points.emplace_back(std::make_pair(x, y - i)); break;
    case RT: for(int i = 0; i < len; i++) this->points.emplace_back(std::make_pair(x - i, y)); break;
  }
}


void Snake::Print() {
  for(std::deque<std::pair<int,int>>::iterator it = this->points.begin(); it != this->points.end(); ++it)
    this->render.Draw( std::get<0>(*it), std::get<1>(*it), it == this->points.begin() ? "██" : "▒▒", Color::GRN);
}