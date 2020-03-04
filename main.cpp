#include "Game.h"
int main() {
  // auto render = new Render();
  // render->SizeScreen(30, 30);
  // render->ClearScreen();
  // render->HideCursor();
  // auto snake = new Snake(render, UP, 10, 10);
  // snake->Print();
  system("pause");
  auto game = new Game();
  game->Build();
  game->Framework();
  // while(1) {
  //   snake->Move({1, 30}, {1, 30});
  //   system("pause");
  // }
  return 0;
}