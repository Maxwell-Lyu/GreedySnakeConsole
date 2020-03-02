#include <iostream>
#include "Snake.h"
int main() {
  auto render = new Render();
  std::cout << "fuck" << std::endl;
  system("pause");
  render->SizeScreen(30, 30);
  render->ClearScreen();
  auto snake = new Snake(*render, Direction::DN);
  system("pause");
  snake->Print();
  system("pause");
  return 0;
}