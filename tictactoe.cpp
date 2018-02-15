#include <cstdlib>
#include <iostream>
#include <limits>
#include <string>

#include "board.h"
#include "clearscreen.h"
#include "color.h"

using std::cin;
using std::cout;
using std::endl;
using std::numeric_limits;
using std::streamsize;
using std::string;

void intro ();
void draw (string option = "normal");
void update ();
void updatePlayer ();
void gameOver ();

Board board;
char player = 'X', autoPlayer;
int moveCount = 0;

int
main ()
{
  intro ();

  while (true)
  {
    draw ();
    if (autoPlayer == player)
    {
      board.autoMove (player);
    }
    else
    {
      update ();
    }

    ++moveCount;
    gameOver ();
    updatePlayer ();
  }
}

// Displays intro message and handles user input to set up desired play settings.
void
intro ()
{
  ClearScreen ();

  string introMessage = "\nxo TIC - TAC - TOE xo\n"
    "type \"h\" once in game for instructions\n"
    "or type \"q\" at any time to exit\n"
    "Press enter to continue...\n";

  cout << introMessage;

  char input;
  cin.get (input);

  if (input == 'q')
  {
    exit (EXIT_SUCCESS);
  }
  else if (input != '\n')
  {
    cin.ignore (numeric_limits<streamsize>::max (), '\n');
  }

  cout << "1 or 2 players? (enter the number 1 or 2)" << endl;
  while (true)
  {
    cin.get (input);
    cin.ignore (numeric_limits<streamsize>::max (), '\n');
    switch (input)
    {
      case '1' :
        ClearScreen ();
        cout << introMessage << endl << "Do you want to be (X)s or (O)s? (X goes first)" << endl;
        while (true)
        {
          cin.get (input);
          cin.ignore (numeric_limits<streamsize>::max (), '\n');
          switch (input)
          {
            case 'x' : case 'X' : autoPlayer = 'O'; break;
            case 'o' : case 'O' : autoPlayer = 'X'; break;
            case 'q' : exit (EXIT_SUCCESS);         break;
            default  :
              ClearScreen ();
              cout << introMessage << endl << "Do you want to be (X)s or (O)s? (X goes first)" << endl;
              RedOnBlack ();
              cout << "Enter 'x'/'X' to be player X or 'o'/'O' to be player O." << endl;
              ResetColors ();
              continue;
          }

          break;
        }

        break;
      case '2' : autoPlayer = ' ';    break;
      case 'q' : exit (EXIT_SUCCESS); break;
      default  :
        ClearScreen ();
        cout << introMessage << endl << "1 or 2 players? (enter the number 1 or 2)\n";
        RedOnBlack ();
        cout << "Enter '1' for 1-player or '2' for 2-player.\n";
        ResetColors ();
        continue;
    }

    break;
  }
}

// Prints current state of board including any extra messages depending on given option.
void
draw (string option)
{
  if (option != "help")
  {
    ClearScreen ();
  }

  if (option == "help")
  {
    cout << "          ~~~~~~~HELP~~~~~~~" << endl
         << "COMMANDS:" << endl
         << "Help: \"h\"" << endl
         << "Quit: \"q\"" << endl
         << "HOW TO PLACE A MARK:" << endl
         << "Type a number 1-9 (preferably on num-pad) for corresponding space:" << endl;
    board.printSample ();
    cout << "Press enter to continue...";
    cin.ignore (numeric_limits<streamsize>::max (), '\n');
    ClearScreen ();
  }

  board.print ();

  if (option == "normal" || option == "help")
  {
    cout << "Player " << player << " : Your Move..." << endl;
  }
  if (option == "win")
  {
    cout << "Player " << player << " is the winner!" << endl << endl;
    exit (EXIT_SUCCESS);
  }

  if (option == "tie")
  {
    cout << "It's a tie!" << endl << endl;
    exit (EXIT_SUCCESS);
  }
}

// Handles user input to take in a move and update the board accordingly.
void
update ()
{
  char move;
  while (true)
  {
    while (true)
    {
        cin.get (move);
        cin.ignore (numeric_limits<streamsize>::max (), '\n');
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

          case 'q' : exit (EXIT_SUCCESS);   break;
          case 'h' : draw ("help");      continue;

          default  :
            draw ();
            RedOnBlack ();
            if (move == '\n')
            {
              move = ' ';
            }
            cout << "Command \"" << move << "\" Not Recognized\n";
            ResetColors ();
            continue;
        }
      break;
    }

    /* convert from char to corresponding integer */
    int moveNum = move - '0';

    if (!board.setValue (moveNum, player))
    {
      draw ();
      cout << "Space already taken\n";
      continue;
    }
    break;
  }
}

// Updates player to be the next in the sequence (opposite of current player).
void
updatePlayer ()
{
  if (player == 'X')
  {
    player = 'O';
  }
  else
  {
    player = 'X';
  }
}

// Determines if game has been ended and takes correct course of action.
void
gameOver ()
{
  if (board.hasWon ())
  {
    draw ("win");
  }
  if (moveCount == 9)
  {
    draw ("tie");
  }
}
