
#include "Ship.h"
using namespace std;
//#include "Battleship.h"
#include "symbolics.h"

Ship::Ship(Coor coor, int symbol, int orientation)
{
	Init_Ship( coor,  symbol, orientation);
}


int Ship::getColor() const
{
	if (m_symbol == 'D') return 4;  //RED
	else if (m_symbol == 'C' && m_size==3) return 14; // YELLOW
	else if (m_symbol == 'S') return 9;  //LIGHTBLUE
	else if (m_symbol == 'B') return 2; //GREEN
	else if (m_symbol == 'C' && m_size==5) return 3;//CYAN
}

char Ship::getSymbol() const
{
	return m_symbol;
}



void Ship::Init_Ship(Coor coor, int symbol, int orientation)
{
	m_position.m_row = coor.m_row;
	m_position.m_col = coor.m_col;
	m_size = 0;
	m_symbol = symbol;
	if (orientation == 1) m_orientation = 'E';
	else if (orientation == 2) m_orientation = 'W';
	else if (orientation == 3) m_orientation = 'S';
	else if (orientation == 4) m_orientation = 'N';

	if (symbol == 1) { m_symbol = 'D';  m_size = 2; }		   //Destoyer
	else if (symbol == 2) { m_symbol = 'C'; m_size = 3; }	  //Cruiser
	else if (symbol == 3) { m_symbol = 'S'; m_size = 3; }    //Submarine
	else if (symbol == 4) { m_symbol = 'B'; m_size = 4; }   //Battleship
	else if (symbol == 5) { m_symbol = 'C'; m_size = 5; }  //Carrier
}

