#include "Game.h"

std::string *Game::getPlayerName(int score) {
  this->render->Draw(5 , 7 , "█████████████▶ CONGRATULATION ◀█████████████", Color::YLW, true);
  this->render->Draw(5 , 8 , "██                                        ██", Color::YLW, true);
  char scorebuf[16];
  sprintf(scorebuf, "%d", score);
  this->render->Draw(5 , 9 , "██  YOUR SCORE:                           ██", Color::YLW, true);
  this->render->Draw(13, 9 , scorebuf, Color::YLW, true);
  this->render->Draw(5 , 10, "██  YOUR NAME:                            ██", Color::YLW, true);
  this->render->Draw(5 , 11, "██                                        ██", Color::YLW, true);
  this->render->Draw(5 , 12, "█████████████▶  GREEDY SNAKE  ◀█████████████", Color::YLW, true);
  this->render->Draw(13, 10, "", Color::YLW);
  this->render->ShowCursor();

  auto buf = new std::string;
  char ch;
  // this->render->Draw(10,10,"NAME: ", Color::WHT);
  while(buf->length() < 44) {
    if(kbhit()) {
      if((ch = getche()) == 13)
        break;
      else
        buf->append(&ch);
    }
  }
  return buf;
}