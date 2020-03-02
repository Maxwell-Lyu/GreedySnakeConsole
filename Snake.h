#include "Render.h"
#include <deque>
#include <utility>

enum Direction {UP, LT, DN, RT};

class Snake {
  public:
    Snake(Render& render, Direction d = Direction::UP, int x = 10, int y = 10, int len = 3);
    void Print();
  private:
    Render &render;
    std::deque<std::pair<int,int>> points;
    Direction direction;
};