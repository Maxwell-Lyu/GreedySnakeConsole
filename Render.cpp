#include "Game.h"

void Render::SizeScreen(int x, int y) {
  system("chcp 65001");
  system("title Greedy Snake");
  char cmd[32];
  sprintf(cmd, "mode con cols=%d lines=%d", x * 2, y);
  system(cmd);
}
void Render::ClearScreen() { std::cout<<"\033[2J"; }
void Render::HideCursor() { std::cout<<"\033[?25l"; }
void Render::ShowCursor() { std::cout<<"\033[?25h"; }
void Render::Draw(int x, int y, const char *c, Color color, std::pair<int, int> xBound, std::pair<int, int> yBound) { 
  int x0 = std::get<0>(xBound);
  int x1 = std::get<1>(xBound) - x0 + 1;
  if(x0 >= 0 && x1 > 0) {
    while(x < x0) x += x1;
    x = (x - x0) % x1 + x0;
  }
  int y0 = std::get<0>(yBound);
  int y1 = std::get<1>(yBound) - y0 + 1;
  if(y0 >= 0 && y1 > 0) {
    while(y < y0) y += y1;
    y = (y - y0) % y1 + y0;
  }
  std::cout<<"\033["<<color<<"m\033["<<y<<";"<<x * 2<<"H"<<c;
}



void Render::DrawRect(int x1, int y1, int x2, int y2, const char *c, Color color) {

}
