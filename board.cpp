#include <algorithm>
#include <ctime>
#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "board.h"
#include "color.h"

using std::cout;
using std::endl;
using std::find;
using std::make_pair;
using std::pair;
using std::remove;
using std::vector;

Board::Board () : won (false)
{
  gen.seed (time (NULL));
  for (int i = 0; i < 9; ++i)
  {
    spaces [i] = ' ';
  }
}

void
Board::print ()
{
  cout << endl << " ";
  printSpace (0);
  cout << " | ";
  printSpace (1);
  cout << " | ";
  printSpace (2);
  cout  << "  " << endl << "___|___|___" << endl << " ";
  printSpace (3);
  cout  << " | ";
  printSpace (4);
  cout  << " | ";
  printSpace (5);
  cout  << " " << endl << "___|___|___" << endl << " ";
  printSpace (6);
  cout  << " | ";
  printSpace (7);
  cout  << " | ";
  printSpace (8);
  cout  << " " << endl << "   |   |   " << endl << endl;
}

void
Board::printSample ()
{
  cout << endl << " " << 7 << " | " << 8 << " | " << 9 << "  " << endl
        << "___|___|___" << endl
        << " " << 4 << " | " << 5 << " | " << 6 << " " << endl
        << "___|___|___" << endl
        << " " << 1 << " | " << 2 << " | " << 3 << " " << endl
        << "   |   |   " << endl << endl;
}

bool
Board::setValue (int pos, char xo)
{
  switch (pos)
    {
      case (7): return update (xo, 1);
      case (8): return update (xo, 2);
      case (9): return update (xo, 3);
      case (4): return update (xo, 4);
      case (5): return update (xo, 5);
      case (6): return update (xo, 6);
      case (1): return update (xo, 7);
      case (2): return update (xo, 8);
      case (3): return update (xo, 9);
      default: return false; break;
    }
}

bool
Board::hasWon ()
{
  return won;
}

void
Board::autoMove (char xo)
{
  // TODO: when O puts their first mark on a mid space, marking some corners (2 out of 3 for when O puts
  // their mark on mid space adjacent to X's first mark and 1 out of 3 when O puts their mark in mid
  // space NOT adjacent to X's first mark) can make a tie possible. Make the x bot always go for a
  // corner that cannot result in a tie on it's second move. (this should make it impossible to tie
  // the x bot without taking the middle first)
  if (xo == 'X')
  {
    if (movesX.size () < 2)
    {
      update ('X', randomOpenCorner ());
      return;
    }
    else
    {
      auto oneAwayX = oneAway ('X');
      if (oneAwayX.first)
      {
        update ('X', oneAwayX.second);
        return;
      }

      auto oneAwayO = oneAway ('O');
      if (oneAwayO.first)
      {
        update ('X', oneAwayO.second);
        return;
      }

      if (update ('X', randomOpenCorner ()))
      {
        return;
      }
    }

    vector<int> openSpaces = allOpenSpaces ();

    update ('X', openSpaces [gen () % openSpaces.size ()]);
  }
  else
  {
    if (movesO.empty ())
    {
      if (movesX [0] == 2 || movesX [0] == 4 || movesX [0] == 6 || movesX [0] == 8)
      {
        update ('O', opposite (movesX [0]));
        return;
      }
      if (!update ('O', 5))
      {
        update ('O', randomOpenCorner ());
      }
      return;
    }
    else if (movesO.size () == 1 && movesX [1] == opposite (movesX [0]))
    {
      vector<int> mids { 2, 4, 6, 8 };

      update ('O', mids [gen () % mids.size ()]);
      return;
    }
    else if (movesO [0] == opposite (movesX [0]) && movesO.size () == 2 && spaces [4] == ' ')
    {
      update ('O', 5);
      return;
    }
    else if (
      movesO [0] == opposite (movesX [0]) &&
      movesO.size () == 1 &&
      (movesX [1] == 2 || movesX [1] == 4 || movesX [1] == 6 || movesX [1] == 8)
    )
    {
      int biggerMid, smallerMid;
      if (movesX [0] > movesX [1])
      {
        biggerMid = movesX [0];
        smallerMid = movesX [1];
      }
      else
      {
        biggerMid = movesX [1];
        smallerMid = movesX [0];
      }

      if (movesX [0] == 2 || movesX [1] == 2)
      {
        update ('O', biggerMid - smallerMid - 1);
        return;
      }
      else
      {
        update ('O', 10 + (smallerMid - biggerMid) + 1);
        return;
      }
    }
    else
    {
      auto oneAwayO = oneAway ('O');
      if (oneAwayO.first)
      {
        update ('O', oneAwayO.second);
        return;
      }

      auto oneAwayX = oneAway ('X');
      if (oneAwayX.first)
      {
        update ('O', oneAwayX.second);
        return;
      }

      if (update ('O', randomOpenCorner ()))
      {
        return;
      }
    }

    vector<int> openSpaces = allOpenSpaces ();

    update ('O', openSpaces [gen () % openSpaces.size ()]);
  }
}

bool
Board::update (char xo, int pos)
{
  if (pos < 1 || !isspace (spaces [pos - 1]))
  {
    return false;
  }
  spaces [pos - 1] = xo;

  if (xo == 'X')
  {
    movesX.push_back (pos);
    if (movesX.size () >= 3)
    {
      checkIfWon (pos, movesX);
    }
  }
  else
  {
    movesO.push_back (pos);
    if (movesO.size () >= 3)
    {
      checkIfWon (pos, movesO);
    }
  }
  return true;
}

void
Board::clearSpace (int pos)
{
  char xo = spaces [pos - 1];
  if (isspace (xo))
  {
    return;
  }
  else if (xo == 'X')
  {
    movesX.erase (remove (movesX.begin (), movesX.end (), pos), movesX.end ());
  }
  else if (xo == 'O')
  {
    movesO.erase (remove (movesO.begin (), movesO.end (), pos), movesO.end ());
  }

  spaces [pos - 1] = ' ';

  if (vfind (winningRow, pos))
  {
    winningRow.clear ();
    won = false;
  }
}

void
Board::checkIfWon (int pos, vector<int>& moves)
{
  if    (!(pos & 1))
  {
    midCheck (pos, moves);
  }
  else if (pos != 5)
  {
    cornerCheck (pos, moves);
  }
  else
  {
    centerCheck (moves);
  }
}

void
Board::midCheck (int pos, vector<int>& moves)
{
  won = true;
  if (pos == 2 || pos == 8) {
    if (vfind (moves, pos - 1) && vfind (moves, pos + 1)) {
      winningRow.push_back (pos);
      winningRow.push_back (pos - 1);
      winningRow.push_back (pos + 1);
      return;
    }
  }
  else
  {
    if (vfind (moves, pos - 3) && vfind (moves, pos + 3)) {
      winningRow.push_back (pos);
      winningRow.push_back (pos - 3);
      winningRow.push_back (pos + 3);
      return;
    }
  }
  if (vfind (moves, 5) && vfind (moves, opposite (pos)))
  {
    winningRow.push_back (pos);
    winningRow.push_back (5);
    winningRow.push_back (opposite (pos));
    return;
  }
  else
  {
    won = false;
  }
}

void
Board::cornerCheck (int pos, vector<int>& moves)
{
  won = true;
  if (pos == 3 || pos == 9)
  {
    if (vfind (moves, pos - 1) && vfind (moves, pos - 2)) {
      winningRow.push_back (pos);
      winningRow.push_back (pos - 1);
      winningRow.push_back (pos - 2);
      return;
    }
  }
  else
  {
    if (vfind (moves, pos + 1) && vfind (moves, pos + 2))
    {
      winningRow.push_back (pos);
      winningRow.push_back (pos + 1);
      winningRow.push_back (pos + 2);
      return;
    }
  }
  if (vfind (moves, pos - 3) && vfind (moves, pos - 6))
  {
    winningRow.push_back (pos);
    winningRow.push_back (pos - 3);
    winningRow.push_back (pos - 6);
    return;
  }
  else if (vfind (moves, pos + 3) && vfind (moves, pos + 6))
  {
    winningRow.push_back (pos);
    winningRow.push_back (pos + 3);
    winningRow.push_back (pos + 6);
    return;
  }
  else if (vfind (moves, 5) && vfind (moves, opposite (pos)))
  {
    winningRow.push_back (pos);
    winningRow.push_back (5);
    winningRow.push_back (opposite (pos));
    return;
  }
  won = false;
}

void
Board::centerCheck (vector<int>& moves)
{
  won = true;
  for (int i = 1; i <= 4; ++i)
  {
    if (vfind (moves, 5 - i) && vfind (moves, 5 + i))
    {
      winningRow.push_back (5);
      winningRow.push_back (5 - i);
      winningRow.push_back (5 + i);
      return;
    }
  }
  won = false;
}

int
Board::opposite (int pos)
{
  return 5 - (pos - 5);
}

bool
Board::vfind (vector<int> vec, int num)
{
  return (vec.end () != find (vec.begin (), vec.end (), num));
}

void
Board::printSpace (int space)
{
  if (vfind (winningRow, space + 1))
  {
    GreenOnBlack ();
    cout << spaces [space];
    ResetColors ();
  }
  else
  {
    cout << spaces [space];
  }
}

pair <bool, int>
Board::oneAway (char xo)
{
  vector<int> openSpaces = allOpenSpaces ();

  for (int i : openSpaces)
  {
    update (xo, i);
    if (won)
    {
      clearSpace (i);
      return make_pair (true, i);
    }

    clearSpace (i);
  }

  return make_pair (false, -1);
}

vector<int>
Board::allOpenSpaces ()
{
  vector<int> openSpaces;
  for (int i = 1; i < 10; ++i)
  {
    if (isspace (spaces [i - 1]))
    {
      openSpaces.push_back (i);
    }
  }

  return openSpaces;
}

int
Board::randomOpenCorner ()
{
  vector<int> openCorners;
  if (isspace (spaces [0]))
  {
    openCorners.push_back (1);
  }
  if (isspace (spaces [2]))
  {
    openCorners.push_back (3);
  }
  if (isspace (spaces [6]))
  {
    openCorners.push_back (7);
  }
  if (isspace (spaces [8]))
  {
    openCorners.push_back (9);
  }
  if (openCorners.empty ())
  {
    return -1;
  }

  return openCorners [gen () % openCorners.size ()];
}
