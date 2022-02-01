
#ifndef Ship_H  
#define Ship_H 

//#include "Battleship.h"
#include "Coor.h"
//using namespace std;


class Ship
{
public:
	Ship(Coor coor,int symbol,int oroentation);
	void Init_Ship(Coor coor, int symbol, int orientation);

	//ship's fields
	Coor m_position;
	char m_orientation;
	char m_symbol;
	int m_size;

	int getColor() const;
	char getSymbol() const;
};

#endif
