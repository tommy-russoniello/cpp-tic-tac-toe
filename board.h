#ifndef BOARD_H
#define BOARD_H

#include <random>
#include <vector>

using std::mt19937;
using std::pair;
using std::vector;

class Board
{
  private:

  bool won;
  char spaces [10];
  vector<int> winningRow;
  vector<int> movesX;
  vector<int> movesO;
  mt19937 gen;

  // Sets given value at given position of board based on the indexes used internally for this
  // class.
  bool update (char xo, int pos);

  // Clears any marks from given space, resetting a victory if applicable.
  void clearSpace (int pos);

  // Determines whether current state of the board fulfills a victory condition and sets the 'won'
  // boolean accordingly.
  void checkIfWon (int pos, vector<int>& moves);

  // Determines if given middle space has fulfilled a victory condition and sets the 'won' boolean
  // accordingly.
  void midCheck (int pos, vector<int>& moves);

  // Determines if given corner space has fulfilled a victory condition and sets the 'won' boolean
  // accordingly.
  void cornerCheck (int pos, vector<int>& moves);

  // Determines if center space has fulfilled a victory condition and sets the 'won' boolean
  // accordingly.
  void centerCheck (vector<int>& moves);

  // Returns position opposite of given position.
  int opposite (int pos);

  // Returns whether or not the given vector contains the given element.
  bool vfind (vector<int> vec, int num);

  // Prints out the value of given space in proper color.
  void printSpace (int space);

  // Determines if given player is one away from having three of their marks in a row anywhere on
  // the board and returns a pair with (first) a boolean of whether or not it found a space that
  // satisfied the condition and (second) the position of the first space that satisfied the
  // condition.
  pair <bool, int> oneAway (char xo);

  // Returns vector containing the positions of all spaces that are unmarked.
  vector<int> allOpenSpaces ();

  // Returns position of a random unmarked corner space.
  int randomOpenCorner ();

  // Returns whether or not given position corresponds to a corner space.
  bool isCorner (int pos);

  // Returns whether or not given position corresponds to a mid space.
  bool isMid (int pos);

  // Returns whether or not given position corresponds to the center space.
  bool isCenter (int pos);

  // Returns whether or not given positions are adjacent to each other.
  bool isAdjacent (int pos_a, int pos_b);

  public:

  Board ();

  // Prints current state of board in typical format.
  void print ();

  // Prints board in typical format but with numbers in the spaces that correspond to the numbers
  // the user must enter to mark them.
  void printSample ();

  // Sets given value at given position of board based on the indexes known to the user.
  bool setValue (int pos, char xo);

  // Returns whether or not the current state of the board fulfills a victory condition.
  bool hasWon ();

  // Performs automatic movement for given player.
  void autoMove (char xo);
};

#endif
