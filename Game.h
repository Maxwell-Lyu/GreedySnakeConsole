#include <iostream>
#include <utility>
#include <deque>
#include <conio.h>
#include <sys/timeb.h>
#include <cstring>
#include <vector>
#include<algorithm>

enum Color { BLK = 30, RED, GRN, YLW, BLU, MAG, CYN, WHT };

class Render {
  public:
    static void SizeScreen(int x, int y);
    static void ClearScreen();
    static void HideCursor();
    static void ShowCursor();
    // bound: [xl, xr, yl, yr]
    static void Draw(int x, int y, const char *c, Color color, bool isBold = false, bool delay = false);
    static void DrawRect(std::pair<int, int> xBound, std::pair<int, int> yBound, const char *c, Color color);
    static std::pair<int,int> justifyPoint(std::pair<int,int> p, std::pair<int, int> xBound, std::pair<int, int> yBound);
    static void Test();
};

enum {FOOD, BONUS, EMPTY};

class Foods {
  private:
    int count = 0;
    std::pair<int,int> food = {-1, -1};
    std::pair<int,int> bonus = {-1, -1};
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
    Foods foods;
    std::pair<int, int> xBound = {-1,-1};
    std::pair<int, int> yBound = {-1,-1};
    std::deque<std::pair<int,int>> points;
    Direction direction;
    const Color color;
    friend class Game;
};

enum {RUNNING, PAUSE, OVER, READY};
enum {FREE, WALL};
class Game {
  private:
    Snake *snake = nullptr;
    Direction direction = Direction::UP;
    std::pair<int, int> xBound = {1,30};
    std::pair<int, int> yBound = {1,30};

    int status = READY;
    int fps = 100;
    int mode = WALL;
    friend class Snake;
  public:
    Game();
    void Framework();
    int Loop();
    bool checkBound();
    ~Game();

    void DrawPanel();
    void PanelSetScore(int score);
    void PanelSetStatus(int state);
    void PanelSetBonus(bool isCountDown, int val);
    void PanelSetSpeed();
    void PanelSetMode();
    void PanelDelBonus();
    void PanelHint();

    void getPlayerName(int score);
};

struct LeaderboardEntry {
  char name[32];
  int score;
};