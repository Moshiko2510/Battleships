
#ifndef TrackBoard_H  
#define TrackBoard_H

//#include "Battleship.h"
#include <iostream>
//#include "symbolics.h"
//#include  <stdio.h> 
//using namespace std;
#include "Coor.h"
#include "utils.h"
#include "symbolics.h"
using namespace std;



class TrackBoard
{
	public:
		TrackBoard();
		char m_track_board[STANDARD_BOARD][STANDARD_BOARD];
	    friend ostream& operator<<(ostream& os, const TrackBoard& tb);
};

#endif