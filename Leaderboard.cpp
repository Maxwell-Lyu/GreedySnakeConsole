#include "Game.h"

bool sortFun(const struct LeaderboardEntry &e1, const struct LeaderboardEntry &e2) { return e1.score > e2.score; }

void Game::LeaderBoard(int score) {

  Render::Draw(5 , 7 , "█████████████▶  GREEDY SNAKE  ◀█████████████", Color::YLW, true);
  Render::Draw(5 , 8 , "██                                        ██", Color::YLW, true);
  char scorebuf[16];
  sprintf(scorebuf, "%d", score);
  Render::Draw(5 , 9 , "██  YOUR SCORE:                           ██", Color::YLW, true);
  Render::Draw(13, 9 , scorebuf, Color::YLW, true);
  Render::Draw(5 , 10, "██  YOUR NAME:                            ██", Color::YLW, true);
  Render::Draw(5 , 11, "██                                        ██", Color::YLW, true);
  Render::Draw(5 , 12, "█████████████▶   BY MAXWELL   ◀█████████████", Color::YLW, true);
  
  std::vector<struct LeaderboardEntry> leaderboard;
  FILE *fp = fopen("Leaderboard.csv", "r");
  if(fp == nullptr)
    fp = fopen("Leaderboard.csv", "a");
  LeaderboardEntry tmp;
  if(fp == nullptr) {
    Render::Draw(7 , 11, " LEADERBOARD CURRENTLY UNACCESSIBLE", Color::RED);
    return;
  }
  while(~fscanf(fp, "%s%d", &tmp.name, &tmp.score)) {
    leaderboard.push_back(tmp);
  }

  if(this->mode) {
    Render::Draw(this->xBound.second + 1, 27, "[↩] ▶ ENTER NAME", Color::YLW, true);
    Render::Draw(13, 10, "", Color::YLW);
    Render::ShowCursor();
    char name[32];
    int index = 0;
    unsigned char ch;
    std::cin >> std::setw(20) >> name;
    Render::HideCursor();
    fclose(fp);
    strcpy(tmp.name, name);
    tmp.score = score;
    leaderboard.push_back(tmp);
    Render::Draw(this->xBound.second + 1, 27, "                    ", Color::YLW, true);
  } 
  else
  {
    Render::Draw(13, 10, "MASTER NONAME", Color::GRN);
  }
  
 
  std::sort(leaderboard.begin(), leaderboard.end(), sortFun);

  Render::Draw(5 , 12, "█████████████▶  LEADER BOARD  ◀█████████████", Color::YLW, true);
  Render::Draw(5 , 13, "██ RANK                 NAME SCORE        ██", Color::YLW, true);
  char boardbuf[128];
  int count = 1;
  fp = fopen("Leaderboard.csv", "w");
  for(auto& e: leaderboard) {
    sprintf(boardbuf, "██  %2d  %20s %-12d ██", count, e.name, e.score);
    Render::Draw(5, 13 + count, boardbuf, Color::YLW, true);
    if(++count > 10) break;
  }
  Render::Draw(5 , 13 + count, "██                                        ██", Color::YLW, true);
  Render::Draw(5 , 14 + count, "█████████████▶   BY MAXWELL   ◀█████████████", Color::YLW, true);
  



  count = 1;
  fp = fopen("Leaderboard.csv", "w");
  for(auto& e: leaderboard) {
    fprintf(fp, "%s\n%d\n", e.name, e.score);
    if(++count > 10) break;
  }
  fclose(fp);
}