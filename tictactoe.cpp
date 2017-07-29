#include <iostream>
#include <cstdlib>
#include <string>
#include <conio.h>

#include "board.h"
#include "clearscreen.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;

void draw (string option = "normal");
void update ();
void updatePlayer ();
void gameOver ();

Board board;
char player = 'X';
int moveCount = 0;

int
main ()
{
  draw("start");

  while (true)
  {
    draw ();
    update();
    ++moveCount;
    gameOver();
    updatePlayer();
  }
}

void
draw (string option)
{
  if (option != "help") { ClearScreen(); }

  if (option == "start")
  {
    cout << endl << "xo TIC - TAC - TOE xo" << endl
         << "type \"h\" once in game for instructions" << endl
	       << "or type \"q\" once in game to exit" << endl
         << "Press enter to continue...";
    cin.get();
    return;
  }

  if (option == "help")
  {
    cout << "          ~~~~~~~HELP~~~~~~~" << endl
         << "COMMANDS:" << endl
         << "Help: \"h\"" << endl
         << "Quit: \"q\"" << endl
         << "HOW TO PLACE A MARK:" << endl
         << "Type a number 1-9 (preferably on num-pad) for corresponding space:" << endl;
    board.printSample();
    cout << "Press enter to continue...";
    cin.get();
    cin.ignore();
    ClearScreen();
  }

  board.print();
  if (option == "normal" || option == "help")
    cout << "Player " << player << " : Your Move..." << endl;

  if (option == "win")
  {
    cout << "Player " << player << " is the winner!" << endl << endl;
    exit(EXIT_SUCCESS);
  }

  if (option == "tie")
  {
    cout << "It's a tie!" << endl << endl;
    exit (EXIT_SUCCESS);
  }
}

void
update ()
{
  int position;
  string input;
  char move;
  while (true)
  {
    while (true)
    {
        cin >> input;
        move = input[0];
        switch (move)
        {
          case '1' : break;
          case '2' : break;
          case '3' : break;
          case '4' : break;
          case '5' : break;
          case '6' : break;
          case '7' : break;
          case '8' : break;
          case '9' : break;

          case 'q' : exit(EXIT_SUCCESS); break;
          case 'h' : draw ("help");      continue;

          default  : cout << "Command Not Recognized\n"; continue;
        }
      break;
    }

    /* convert from char to corresponding integer */
    int moveNum = move - '0';

    if(!board.setValue(moveNum, player))
    {
      draw ();
      cout << "Space already taken\n";
      continue;
    }
    break;
  }
}

void
updatePlayer ()
{
  if (player == 'X')
    player = 'O';
  else
    player = 'X';
}

void
gameOver()
{
  if (board.hasWon())
  {
    draw ("win");
  }
  if (moveCount == 9)
  {
    draw ("tie");
  }
}

