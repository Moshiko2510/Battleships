
#ifndef Battleship_H
#define Battleship_H


#include <iostream>
#include <string>
#include "ship.h"
#include "Player.h"
#include "Board.h"
#include "TrackBoard.h"
using namespace std;

#define TOTAL_SHIPS 5

class Battleship
{
public:
	Battleship(string f_name);
	~Battleship();
	Player* User;
	Player* Computer;
	string Play();
	Coor choose_coor_for_attack(Coor coor);
	void mark_sink_trackboard(int size,char symbol);
};

#endif
