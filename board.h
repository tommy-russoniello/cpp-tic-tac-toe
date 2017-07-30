#ifndef BOARD_H
#define BOARD_H

#include <vector>

using std::vector;

class Board
{
  private:

  bool won;
  char spaces [10];
  vector<int> winningRow;
  vector<int> movesX;
  vector<int> movesO;

  bool update (char xo, int pos);
  void checkIfWon (int pos, vector<int>& moves);
  void midCheck (int pos, vector<int>& moves);
  void cornerCheck (int pos, vector<int>& moves);
  void centerCheck (vector<int>& moves);
  int opposite (int pos);
  bool vfind (vector<int> vec, int num);
  void printSpace (int space);

  public:

  Board ();
  void print ();
  void printSample ();
  bool setValue (int pos, char xo);
  bool hasWon ();
};

#endif
