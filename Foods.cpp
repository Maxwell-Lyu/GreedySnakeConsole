#include "Game.h"

void Foods::setFood(std::deque<std::pair<int,int>> &avoid, std::pair<int, int> &xBound, std::pair<int, int> &yBound, bool isBonus) {
  const int padding = 2;
  std::pair<int,int> tmp;
  bool inAvoid = false;
  do {
    tmp = Render::justifyPoint({rand(), rand()}, {xBound.first + padding, xBound.second - padding}, {yBound.first + padding, yBound.second - padding});
    inAvoid = false;
    for(auto& point: avoid) 
      if(point == tmp)
        inAvoid = true;
  } while (inAvoid || tmp == this->bonus || tmp == this->food);
  if(isBonus) {
    Render::Draw(std::get<0>(tmp), std::get<1>(tmp), "➎ ", Color::YLW);
    this->bonus = tmp;
  }
  else {
    Render::Draw(std::get<0>(tmp), std::get<1>(tmp), "➊ ", Color::GRN);
    this->food = tmp;
  }
} 

int Foods::checkFood(std::pair<int, int> &target) {
  if(target == this->food) return FOOD;
  if(target == this->bonus) return BONUS;
  return EMPTY;
}

void Foods::dropBonus() {
  Render::Draw(this->bonus.first, this->bonus.second, "  ", Color::WHT);
  this->bonus = {-1,-1};
}