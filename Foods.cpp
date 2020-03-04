#include "Game.h"

std::pair<int,int> Foods::setFood(std::deque<std::pair<int,int>> &avoid, std::pair<int, int> &xBound, std::pair<int, int> &yBound, bool isBonus) {
  std::pair<int,int> tmp;
  do {
    tmp = justifyPoint({rand(), rand()}, {xBound.first + 1, xBound.second - 1}, {yBound.first + 1, yBound.second - 1});
    for(auto& point: avoid) 
      if(point == tmp)
        continue;
  } while (tmp == this->bonus || tmp == this->food);
  if(isBonus) {
    this->render.Draw(std::get<0>(tmp), std::get<1>(tmp), "ボ", Color::YLW);
    this->bonus = tmp;
  }
  else {
    this->render.Draw(std::get<0>(tmp), std::get<1>(tmp), "フ", Color::MAG);
    this->food = tmp;
  }
  return tmp;
} 

int Foods::checkFood(std::pair<int, int> &target) {
  if(target == this->food) return FOOD;
  if(target == this->bonus) return BONUS;
  return EMPTY;
}

void Foods::dropBonus() {
  this->render.Draw(this->bonus.first, this->bonus.second, "  ", Color::WHT);
  this->bonus = {-1,-1};
}