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
    // 调整屏幕大小, 单位为全角字符个数, 2个半角字符占一个单位
    static void SizeScreen(int x, int y);
    // 清除屏幕
    static void ClearScreen();
    // 光标隐藏/显示
    static void HideCursor();
    static void ShowCursor();
    // 在指定坐标(x,y)绘制字符串c, 颜色为color, 可isBold加粗, 可delay添加延时以制造刷新效果
    static void Draw(int x, int y, const char *c, Color color, bool isBold = false, bool delay = false);
    // 绘制[xBound, yBound]的句型区域边界, 边界字符c, 颜色color
    static void DrawRect(std::pair<int, int> xBound, std::pair<int, int> yBound, const char *c, Color color);
    // 根据给定的边界[xBound, yBound], 进行点p的循环矫正
    static std::pair<int,int> justifyPoint(std::pair<int,int> p, std::pair<int, int> xBound, std::pair<int, int> yBound);
};

enum {FOOD, BONUS, EMPTY};

class Foods {
  private:
    // 当前普通食物的坐标
    std::pair<int,int> food = {-1, -1};
    // 当前额外食物的坐标, (-1, -1)表示不存在
    std::pair<int,int> bonus = {-1, -1};
  public:
    // 根据给定的坐标范围[xBound, yBound]与规避点列表avoid, 绘制普通食物或额外食物(isBonus)并保存坐标
    void setFood(std::deque<std::pair<int,int>> &avoid, std::pair<int, int> &xBound, std::pair<int, int> &yBound, bool isBonus = false);
    // 检查点target的类型, 返回 FOOD 普通食物, BONUS 额外食物, EMPTY 没有食物 
    int checkFood(std::pair<int, int> &target);
    // 丢弃Bonus食物, 消除食物标志
    void dropBonus();
};

enum Direction {UP, LT, DN, RT};

class Snake {
  public:
    // 构造函数, 需要提供蛇的移动范围[xBound, yBound]以便循环移动和判断越界
    // 初始化时, 默认的方向, 坐标和颜色如下, 且允许重新指定
    Snake(std::pair<int, int> xBound, std::pair<int, int> yBound, 
      Direction d = Direction::UP, int x = 10, int y = 10, int len = 3, Color color = Color::GRN
    );
    // 打印整条蛇, 仅用于初始化
    void Print();
    // 更改方向为d
    void setDirection(Direction d);
    // 向this->direction移动一格, 参数getFood控制是否因吞噬食物延长一格
    int Move(bool getFood = false);
    // 析构函数
    ~Snake();
  private:
    // 成员类: 食物
    Foods foods;
    // xBound与yBound约束
    std::pair<int, int> xBound = {-1,-1};
    std::pair<int, int> yBound = {-1,-1};
    // 蛇身所有点的坐标
    std::deque<std::pair<int,int>> points;
    // 方向 与 颜色
    Direction direction;
    const Color color;
    // 将Game设置为友元, 允许其访问蛇的Food属性, 进行相关的条件判断
    friend class Game;
};

enum {RUNNING, PAUSE, OVER, READY};
enum {FREE, WALL};
class Game {
  private:
    // 蛇与其初始方向
    Snake *snake = nullptr;
    // 
    std::pair<int, int> xBound = {1,30};
    std::pair<int, int> yBound = {1,30};

    int status = READY;
    int fps = 100;
    int mode = WALL;
    friend class Snake;
  public:
    Game();
    // 游戏框架循环, 管理游戏设置, 包括状态栏
    void Framework();
    // 游戏主循环, 包括蛇和状态栏
    int Loop();
    // 竞技模式逻辑: 检查边界
    bool checkBound();
    ~Game();
    // 面板方法组: 绘制面板, 调整面板数据
    void DrawPanel();                               // 绘制面板与LOGO
    void PanelSetScore(int score);                  // 绘制分数
    void PanelSetStatus(int state);                 // 设置游戏状态并绘制
    void PanelSetBonus(bool isCountDown, int val);  // 绘制额外食物状态: 所需普通食物/拾取剩余时间
    void PanelSetSpeed();                           // 绘制游戏速度
    void PanelSetMode();                            // 绘制游戏模式
    void PanelDelBonus();                           // 清除额外食物状态
    void PanelHint();                               // 打印提示信息, 根据模式
    // 排行榜, 拿取分数信息并请求用户输入
    void LeaderBoard(int score);
};

struct LeaderboardEntry {
  char name[32];
  int score;
};