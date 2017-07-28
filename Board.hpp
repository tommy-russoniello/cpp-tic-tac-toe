#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;
using std::vector;
using std::find;
using std::iterator;

class Board
{
 public :
  bool won;
  char spaces [10];
  vector<int> movesX;
  vector<int> movesO;

  Board () : won (false)
    {
      for (int i = 0; i < 9; ++i) { spaces[i] = ' '; }
    }

void
print ()
{
  cout << endl << " " << spaces [0] << " | " << spaces [1] << " | " << spaces [2] << "  " << endl
       << "___|___|___" << endl
       << " " << spaces [3] << " | " << spaces [4] << " | " << spaces [5] << " " << endl
       << "___|___|___" << endl
       << " " << spaces [6] << " | " << spaces [7] << " | " << spaces [8] << " " << endl
       << "   |   |   " << endl << endl;
}

void
printSample ()
{
  cout << endl << " " << 7 << " | " << 8 << " | " << 9 << "  " << endl
       << "___|___|___" << endl
       << " " << 4 << " | " << 5 << " | " << 6 << " " << endl
       << "___|___|___" << endl
       << " " << 1 << " | " << 2 << " | " << 3 << " " << endl
       << "   |   |   " << endl << endl;
}

  bool
  setValue (int pos, char xo)
  {
    switch(pos)
      {
        case(7): return update(xo, 1);
        case(8): return update(xo, 2);
        case(9): return update(xo, 3);
        case(4): return update(xo, 4);
        case(5): return update(xo, 5);
        case(6): return update(xo, 6);
        case(1): return update(xo, 7);
        case(2): return update(xo, 8);
        case(3): return update(xo, 9);
        default: return false; break;
      }
  }


  private :
  
  bool
  update (char xo, int pos)
  {
    if (!isspace(spaces[pos - 1])) { return false; }
    spaces [pos - 1] = xo;

    if (xo == 'X')
    {
      movesX.push_back(pos);
      if (movesX.size() >= 3) { hasWon(pos, movesX); }
    }
    else
    {
      movesO.push_back(pos);
      if (movesO.size() >= 3) { hasWon(pos, movesO); }
    }
    return true;
  }

  void
  hasWon (int pos, vector<int>& moves)
  {
    if    (!(pos & 1)) { midCheck (pos, moves);   }
    else if (pos != 5) { cornerCheck(pos, moves); }
    else               { centerCheck(moves); }
  }

  void
  midCheck (int pos, vector<int>& moves)
  {
    won = true;
    if (pos == 2 || pos == 8) {
      if (vfind (moves, pos - 1) && vfind (moves, pos + 1)) { return; }
    }
    else
    {
      if (vfind (moves, pos - 3) && vfind (moves, pos + 3)) { return; }
    }
    won = (vfind (moves, 5) && vfind (moves, opposite(pos)));
  }

  void
  cornerCheck (int pos, vector<int>& moves)
  {
    won = true;
    if (pos == 3 || pos == 9)
    {
      if (vfind (moves, pos - 1) && vfind (moves, pos - 2)) { return; }
    }
    else{
      if (vfind (moves, pos + 1) && vfind (moves, pos + 2)) { return; }
    }
    won = (
      (vfind (moves, pos - 3) && vfind (moves, pos - 6)) ||
      (vfind (moves, pos + 3) && vfind (moves, pos + 6)) ||
      (vfind (moves, 5) && vfind (moves, opposite(pos)))
    );
  }

  void
  centerCheck (vector<int>& moves)
  {
    won = true;
    for (int i = 1; i <= 4; ++i)
    {
      if (vfind (moves, 5 - i) && vfind (moves, 5 + i)) { return; }
    }
    won = false;
  }

  int
  opposite (int pos)
  {
     return 5 - (pos - 5);
  }

  bool
  vfind (vector<int> vec, int num)
  {
    return (vec.end() != find (vec.begin(), vec.end(), num));
  }
};
