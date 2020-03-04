#include "common.h"


enum Color { BLK = 30, RED, GRN, YLW, BLU, MAG, CYN, WHT };

class Render {
  public:
    void SizeScreen(int x, int y);
    void ClearScreen();
    void HideCursor();
    void ShowCursor();
    // bound: [xl, xr, yl, yr]
    void Draw(int x, int y, const char *c, Color color, bool isBold = false, std::pair<int, int> xBound = {-1,-1}, std::pair<int, int> yBound = {-1,-1});
    void DrawRect(std::pair<int, int> xBound, std::pair<int, int> yBound, const char *c, Color color);
    void Test();
};

enum {FOOD, BONUS, EMPTY};

class Foods {
  private:
    int count = 0;
    std::pair<int,int> food = {-1, -1};
    std::pair<int,int> bonus = {-1, -1};
    Render render;
  public:
    std::pair<int,int> setFood(std::deque<std::pair<int,int>> &avoid, std::pair<int, int> &xBound, std::pair<int, int> &yBound, bool isBonus = false);
    int checkFood(std::pair<int, int> &target);
    void dropBonus();
};

enum Direction {UP, LT, DN, RT};

class Snake {
  public:
    Snake(std::pair<int, int> xBound, std::pair<int, int> yBound, Direction d = Direction::UP, int x = 10, int y = 10, int len = 3, Color color = Color::GRN);
    void Print();
    void setDirection(Direction d);
    int Move(bool getFood = false);
    ~Snake();
  private:
    Render render;
    Foods foods;
    std::pair<int, int> xBound = {-1,-1};
    std::pair<int, int> yBound = {-1,-1};
    std::deque<std::pair<int,int>> points;
    Direction direction;
    const Color color;
    friend class Game;
};

enum {RUNNING, PAUSE, OVER};
enum {FREE, WALL};
class Game {
  private:
    Render *render = nullptr;
    Snake *snake = nullptr;
    Direction direction = Direction::UP;
    std::pair<int, int> xBound = {1,30};
    std::pair<int, int> yBound = {1,30};

    int status = OVER;
    int fps = 100;
    int mode = WALL;
    friend class Snake;
  public:
    Game();
    void Build();
    int Loop();
    bool checkBound();
    ~Game();

    void DrawPanel();
    void PanelSetScore(int score);
    void PanelSetStatus(int state);
    void PanelSetBonus(bool isCountDown, int val);
    void PanelSetSpeed();
    void PanelSetMode();
    void Refresh();
};

std::pair<int,int> justifyPoint(std::pair<int,int> p, std::pair<int, int> xBound, std::pair<int, int> yBound);
