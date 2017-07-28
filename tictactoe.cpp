#include <iostream>
#include <cstdlib>
#include <string>
#include <conio.h>

#include "Board.hpp"

using std::cout;
using std::cin;
using std::endl;
using std::string;

void draw (string option = "normal");
void update ();
void updatePlayer ();
void hasWon ();

Board board;
char player = 'X';

int
main ()
{
  draw("start");

  while (true)
  {
    draw ();
    update();
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
    cout << endl << "xo TIC - TAC - TOE xo" << endl
	 << "type \"h\" once in game for instructions" << endl
	 << "or type \"q\" once in game to exit" << endl;
   system("pause");
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

    // convert rom char to corresponding integer
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
hasWon()
{
  if (board.won)
  {
    draw ("win"); cout << "Player " << player << " is the winner!" << endl << endl; exit(EXIT_SUCCESS);
  }
  // if(board.topL+board.topM+board.topR==264||board.midL+board.midM+board.midR==264||board.botL+board.botM+
  //    board.botR==264||board.topR+board.midR+board.botR==264||board.topM+board.midM+board.botM==264||
  //    board.topL+board.midL+board.botL==264||board.topR+board.midM+board.botL==264||
  //    board.topL+board.midM+board.botR==264){
  //   draw("win"); cout << "Player X is the winner!" << endl << endl; exit(EXIT_SUCCESS);}
  //  if(board.topL+board.topM+board.topR==237||board.midL+board.midM+board.midR==237||board.botL+board.botM+
  //    board.botR==237||board.topR+board.midR+board.botR==237||board.topM+board.midM+board.botM==237||
  //    board.topL+board.midL+board.botL==237||board.topR+board.midM+board.botL==237||
  //    board.topL+board.midM+board.botR==237){
  //   draw("win"); cout << "Player O is the winner!" << endl << endl; exit(EXIT_SUCCESS);}
  //  if(*board.topleft+*board.topmid+*board.topright+*board.midleft+*board.midmid+*board.midright+*board.botleft+*board.botmid+*board.botright==756){
  //    draw("win"); cout << "It's a tie!" << endl << endl; exit(EXIT_SUCCESS);}
  
}

