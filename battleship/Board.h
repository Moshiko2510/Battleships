
#ifndef Board_H
#define Board_H


#include <string>
#include <fstream>
#include <sstream>
#include "Point.h"
#include <iostream>
using namespace std;

#define STANDARD_BOARD 10

class Board
{
public:
	Board(const string& filename);
	Board();
	~Board();

	const static int num_of_rows = STANDARD_BOARD;
	const static int num_of_cols = STANDARD_BOARD;
	Point m_board[num_of_rows][num_of_cols];

	void Init_Board();
	void Add_Battleships_From_File(const string& filename);
	void Add_Rand_Battelships();
	static int get_num_of_cols();
	static int get_num_of_rows();
	void check_position(int orientation, int symbol,Coor &a);
	bool coor_available(const Coor coor,const int size,const int orientation)const;
	friend ostream& operator<<(ostream& os, const Board& b);
	bool get_error_flag();
	

private:
	bool error_flag=0;
};

#endif