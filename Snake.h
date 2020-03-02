#include "Render.h"
#include <deque>
#include <utility>

enum Direction {UP, LT, DN, RT};

class Snake {
  public:
    Snake(Render& render, Direction d = Direction::UP, int x = 10, int y = 10, int len = 3, Color color = Color::GRN);
    void Print();
    void setDirection(Direction d) { this->direction = d; }
    void Move(bool getFood = false);
  private:
    Render &render;
    std::deque<std::pair<int,int>> points;
    Direction direction;
    const Color color;
};