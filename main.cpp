#include <iostream>
#include "Snake.h"
int main() {
  auto render = new Render();
  render->SizeScreen(30, 30);
  render->ClearScreen();
  auto snake = new Snake(*render);
  snake->Print();
  system("pause");
  snake->Move();
  system("pause");
  snake->Move(1);
  snake->setDirection(Direction::LT);
  system("pause");
  snake->Move(1);
  system("pause");
  snake->Move();
  system("pause");
  return 0;
}