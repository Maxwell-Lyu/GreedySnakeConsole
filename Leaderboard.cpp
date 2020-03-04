#include "Game.h"

bool sortFun(const struct LeaderboardEntry &e1, const struct LeaderboardEntry &e2) { return e1.score > e2.score; }

void Game::getPlayerName(int score) {
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

  char name[32];
  int index = 0;
  while(index < 31) {
    if(kbhit())
      if((name[index++] = getche()) == 13)
        break;
    _sleep(100);
  }
  name[index - 1] = '\0';

  std::vector<struct LeaderboardEntry> leaderboard;
  FILE *fp = fopen("Leaderboard.csv", "r");
  if(fp == nullptr)
    fp = fopen("Leaderboard.csv", "a");
  LeaderboardEntry tmp;
  while(~fscanf(fp, "%s%d", &tmp.name, &tmp.score)) {
    leaderboard.push_back(tmp);
  }
  fclose(fp);
  strcpy(tmp.name, name);
  tmp.score = score;
  leaderboard.push_back(tmp);
 
  std::sort(leaderboard.begin(), leaderboard.end(), sortFun);

  int count = 0;
  fp = fopen("Leaderboard.csv", "w");
  for(auto& e: leaderboard) {
    fprintf(fp, "%s\n%d\n", e.name, e.score);
    if(++count >= 10) break;
  }
  fclose(fp);
}