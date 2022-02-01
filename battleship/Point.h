
#ifndef Point_H
#define Point_H


#include "Coor.h"
class Ship;


class Point 
{
public:
	Point();
	
	Coor m_coor;
	bool m_attacked;
	bool m_sunk;

	Ship* get_ship() const;
	Ship* m_ship;
};

#endif