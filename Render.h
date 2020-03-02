#include <iostream>

enum Color { BLK = 30, RED, GRN, YLW, BLU, MAG, CYN, WHT };

class Render {
  public:
    void SizeScreen(int x, int y);
    void ClearScreen();
    void HideCursor();
    void ShowCursor();
    void Draw(int x, int y, const char *c, Color color);
    void Test();
};