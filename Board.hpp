#include <cstdlib>
#include <iostream>
#include <string>

using std::cout;
using std::endl;

class Board
{
 public :
  char topL, topM, topR, midL, midM, midR, botL, botM, botR;

  Board ()
    {
      topL = topM = topR = midL = midM = midR = botL = botM = botR = ' ';
    }

void
print ()
{
  cout << endl << " " << topL << " | " << topM << " | " << topR << "  " << endl
       << "___|___|___" << endl
       << " " << midL << " | " << midM << " | " << midR << " " << endl
       << "___|___|___" << endl
       << " " << botL << " | " << botM << " | " << botR << " " << endl
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
  setValue (int row, int column, char xo)
  {
    switch(row)
      {
      case(1):
	switch(column){
	case(1): if(topL != ' '){break;} topL = xo; return true;
	case(2): if(topM != ' '){break;} topM = xo; return true;
	case(3): if(topR != ' '){break;} topR = xo; return true;
	} break;
      case(2):
	switch(column){
	case(1):if(midL != ' '){break;} midL = xo; return true;
	case(2):if(midM != ' '){break;} midM = xo; return true;
	case(3):if(midR != ' '){break;} midR = xo; return true;
	} break;
      case(3):
	switch(column){
	case(1):if(botL != ' '){break;} botL = xo; return true;
	case(2):if(botM != ' '){break;} botM = xo; return true;
	case(3):if(botR != ' '){break;} botR = xo; return true;
	} break;
      }
    return false;
  }


 private :
  //none
};
