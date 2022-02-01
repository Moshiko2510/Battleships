
#ifndef Player_H 
#define Player_H 


#include "TrackBoard.h"
#include "Board.h"
#include <iostream>
#include <string>
#include "Coor.h"
#include "Ship.h"
#include "Point.h"
using namespace std;

class Player
{
public:
	Player (string name,string f_name);
	Player(string name);
	~Player();
	Board* m_board;
	const string m_name;
	
	TrackBoard* m_track_board;
	char attack(const Coor& coor);
	bool check_for_sunked_ship(Coor coor);
	void mark_sink(int size, char symbol);
};

#endif