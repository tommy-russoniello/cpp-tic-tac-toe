#include <iostream>
#include <cstdlib>
#include <string>
#include <conio.h>

#include "windows.h"
#include "Board.hpp"

using std::cout;
using std::cin;
using std::endl;
using std::string;

void draw (string option = "normal");
bool update ();
void updatePlayer ();
void hasWon ();

Board board;
char player = 'X';
string error = "Command Not Recognized\n";

int
main ()
{
  draw("start");

  while (true)
  {
    draw ();
    update()
    hasWon();
    updatePlayer();
  }
}

void
draw (string option)
{
  if (option != "help") { system("cls"); }
  if (option == "start")
  {
    cout << endl << " TIC - TAC - TOE" << endl
	 << "type \"h\" at any time for instructions" << endl
	 << "or type \"q\" at any time to exit" << endl;
   system("pause");
   return;
  }
  if (option == "help")
  {
    cout << "          ~~~~~~~HELP~~~~~~~" << endl
         << "COMMANDS:" << endl
         << "Help: \"h\" \"help\"" << endl
         << "Play: \"p\" \"play\" \"y\" \"yes\"" << endl
         << "Quit: \"quit\" (or \"n\"/\"no\" when prompted to play)" << endl
         << "Placing a mark~" << endl
         << "type row then column separated by a SPACE" << endl
         << "ROWS   : top, middle, bottom" << endl
         << "COLUMNS: left, middle, right" << endl
         << "Alternatively, type center for middle-middle" << endl << endl;
    system("pause");
    system("cls");
  }
  board.print();
  if (option == "normal" || option == "help")
    cout << "Player " << player << " : Your Move..." << endl;
}

void
update ()
{
  int rowNum, colNum;
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
          case '7' : rowNum = 1; colNum = 1;  break;
          case '8' : rowNum = 1; colNum = 2;  break;
          case '9' : rowNum = 1; colNum = 3;  break;
          case '4' : rowNum = 2; colNum = 1;  break;
          case '5' : rowNum = 2; colNum = 2;  break;
          case '6' : rowNum = 2; colNum = 3;  break;
          case '1' : rowNum = 3; colNum = 1;  break;
          case '2' : rowNum = 3; colNum = 2;  break;
          case '3' : rowNum = 3; colNum = 3;  break;
          case 'q' : exit(EXIT_SUCCESS);      break;
          case 'h' : draw ("help");        continue;
          default  : cout << error;        continue;
        }
      break;
    }

    if(!board.setValue(rowNum, colNum, player))
    {
      draw ();
      cout << "Space already taken\n";
      continue;
    }
    break;
  }
  return false;
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
hasWon()
{
  if(board.topL+board.topM+board.topR==264||board.midL+board.midM+board.midR==264||board.botL+board.botM+
     board.botR==264||board.topR+board.midR+board.botR==264||board.topM+board.midM+board.botM==264||
     board.topL+board.midL+board.botL==264||board.topR+board.midM+board.botL==264||
     board.topL+board.midM+board.botR==264){
    draw("win"); cout << "Player X is the winner!" << endl << endl; exit(EXIT_SUCCESS);}
   if(board.topL+board.topM+board.topR==237||board.midL+board.midM+board.midR==237||board.botL+board.botM+
     board.botR==237||board.topR+board.midR+board.botR==237||board.topM+board.midM+board.botM==237||
     board.topL+board.midL+board.botL==237||board.topR+board.midM+board.botL==237||
     board.topL+board.midM+board.botR==237){
    draw("win"); cout << "Player O is the winner!" << endl << endl; exit(EXIT_SUCCESS);}
   if(board.topL+board.topM+board.topR+board.midL+board.midM+board.midR+board.botL+board.botM+board.botR==756){
     draw("win"); cout << "It's a tie!" << endl << endl; exit(EXIT_SUCCESS);}
  
}
