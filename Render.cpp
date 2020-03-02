#include "Render.h"

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
void Render::Draw(int x, int y, const char *c, Color color) { std::cout<<"\033["<<color<<"m\033["<<y<<";"<<x * 2<<"H"<<c;};

