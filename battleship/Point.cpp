#include "Point.h"
#include "Ship.h"


 Point::Point()
 {
	 m_ship = nullptr;
	 bool m_attacked=0;
	 bool m_sunk=0;

 }


 Ship* Point::get_ship() const
 {
	 return m_ship;
 }


