#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;
using std::vector;
using std::find;
//using std::push_back;

class Board
{
 public :
  bool won;
  char topleft, topmid, topright, midleft, midmid, midright, botleft, botmid, botright;
  vector<int> movesX;
  vector<int> movesO;

  Board ()
    {
      topleft = topmid = topright = midleft = midmid = midright = botleft = botmid = botright = ' ';
      won = false;
    }

void
print ()
{
  cout << endl << " " << topleft << " | " << topmid << " | " << topright << "  " << endl
       << "___|___|___" << endl
       << " " << midleft << " | " << midmid << " | " << midright << " " << endl
       << "___|___|___" << endl
       << " " << botleft << " | " << botmid << " | " << botright << " " << endl
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
        case(7): return update(topleft, xo, 1);
        case(8): return update(topmid, xo, 2);
        case(9): return update(topright, xo, 3);
        case(4): return update(midleft, xo, 4);
        case(5): return update(midmid, xo, 5);
        case(6): return update(midright, xo, 6);
        case(1): return update(botleft, xo, 7);
        case(2): return update(botmid, xo, 8);
        case(3): return update(botright, xo, 9);
        default: return false; break;
      }
  }


 private :
  
  bool
  update (char& pos, char xo, int posNum)
  {
    if (pos != ' ') { return false; }

    topleft = xo;

    if (xo == 'X')
    {
      movesX.push_back(posNum);
      if (movesX.size() >= 3) { hasWon(posNum, movesX); }
    }
    else
    {
      movesO.push_back(posNum);
      if (movesO.size() >= 3) { hasWon(posNum, movesO); }
    }
    return true;
  }

  void
  hasWon (int pos, vector<int>& moves)
  {
    if      (!pos & 1) { midCheck (pos, moves);   }
    else if (pos != 5) { cornerCheck(pos, moves); }
    else               { centerCheck(moves); }
  }

  void
  midCheck (int pos, vector<int>& moves)
  {
    won = (
      (vfind (moves, pos - 1) && vfind (moves, pos + 1)) ||
      (vfind (moves, pos - 3) && vfind (moves, pos + 3)) ||
      (vfind (moves, 5) && vfind (moves, opposite(pos)))
    );
  }

  void
  cornerCheck (int pos, vector<int>& moves)
  {
    won = (
      (vfind (moves, pos - 1) && vfind (moves, pos - 2)) ||
      (vfind (moves, pos + 1) && vfind (moves, pos + 2)) ||
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
