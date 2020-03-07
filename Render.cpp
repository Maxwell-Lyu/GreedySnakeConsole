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
void Render::Draw(int x, int y, const char *c, Color color, bool isBold, bool delay) { 
  // int x0 = std::get<0>(xBound);
  // int x1 = std::get<1>(xBound) - x0 + 1;
  // if(x0 >= 0 && x1 > 0) {
  //   while(x < x0) x += x1;
  //   x = (x - x0) % x1 + x0;
  // }
  // int y0 = std::get<0>(yBound);
  // int y1 = std::get<1>(yBound) - y0 + 1;
  // if(y0 >= 0 && y1 > 0) {
  //   while(y < y0) y += y1;
  //   y = (y - y0) % y1 + y0;
  // }
  if(delay) _sleep(50);
  if(isBold) std::cout<<"\033["<<color<<";1m\033["<<y<<";"<<x * 2 - 1<<"H"<<c;
  else std::cout<<"\033["<<color<<"m\033["<<y<<";"<<x * 2 - 1<<"H"<<c;
  std::cout<<"\033[0m";

}



void Render::DrawRect(std::pair<int, int> xBound, std::pair<int, int> yBound, const char *c, Color color) {
  for (size_t x = xBound.first; x <= xBound.second; x++) {
    Draw(x, yBound.first, c, color);
    Draw(x, yBound.second, c, color);
  }
  for (size_t y = yBound.first; y <= yBound.second; y++) {
    Draw(xBound.first, y, c, color);
    Draw(xBound.second, y, c, color);
  }
}


std::pair<int,int> Render::justifyPoint(std::pair<int,int> p, std::pair<int, int> xBound, std::pair<int, int> yBound) {
  int x = std::get<0>(p);
  int y = std::get<1>(p);
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
  return {x,y};
}