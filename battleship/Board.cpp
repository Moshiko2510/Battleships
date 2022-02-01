
#include "Board.h"
#include "Ship.h"
#include "symbolics.h"
#include "utils.h"
using namespace std;

Board::Board()
{
	Init_Board();
	Add_Rand_Battelships(); 
}

Board::Board(const string &filename)
{
	Init_Board();
	Add_Battleships_From_File(filename);
	
}

Board::~Board()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (m_board[i][j].m_ship != nullptr)
				delete m_board[i][j].get_ship();
		}
	}
}

void Board::Init_Board()
{
	int i, j = 0;
	for ( i = 0; i < 10; i++)
	{
		for ( j = 0; j < 10; j++)
		{
			m_board[i][j].m_coor.m_col = j;
			m_board[i][j].m_coor.m_row = i + 'A';
			m_board[i][j].m_attacked = false;
			m_board[i][j].m_sunk = false;
		}
	}
}

void Board::Add_Rand_Battelships()
{
	/*This fuction add random battleships to our board and check if the Coor of every ship is leggal.
   we have two functions for this job: 
   check_position- check if the choosen coor and orientation are leggal
   coor_available- check if the choosen coor is available and the boared is empty from ships in the desired coors. */

	Coor coor;
	for (int i = 0; i < 5; i++)
	{
		bool x = 0;
		char row = 0;
		int col, symbol = 0, orientation = 0, size = 0;
		while (x != true)
		{
			row = rand() % 10 + 'A';					 // generate a random number and Convert to a character from A-Z (row in board)																 
			col = rand() % 10;							    //column in board
			orientation = rand() % 4 + 1;					//orientation  1-E/2-W/3-S/4-N
			coor.m_col = col;
			coor.m_row = row;
			symbol = i + 1;					    //ship type	1-D/2-Cruiser/3-S/4-B/5-C
			size = 0;
			if (symbol == 1) size = 2;
			if (symbol == 2 || symbol == 3) size = 3;
			if (symbol == 4) size = 4;
			if (symbol == 5) size = 5;

			check_position(orientation, symbol, coor);
			x = coor_available(coor, size, orientation);
		}
		for (int j = 0; j < size; j++)
		{
			if (orientation == 1) m_board[int(coor.m_row - 'A')][coor.m_col + j].m_ship = new Ship(coor, symbol, orientation);
			if (orientation == 2) m_board[int(coor.m_row - 'A')][coor.m_col - j].m_ship = new Ship(coor, symbol, orientation);
			if (orientation == 3) m_board[int(coor.m_row - 'A' + j)][coor.m_col].m_ship = new Ship(coor, symbol, orientation);
			if (orientation == 4) m_board[int(coor.m_row - 'A' - j)][coor.m_col].m_ship = new Ship(coor, symbol, orientation);
		}

	}
}

void Board::Add_Battleships_From_File(const string& filename) 
{
	/*This function reads all the ships detiles from external file and load it to the user board*/

	Coor coor;
    string line;
	ifstream myfile(filename);
	if (myfile.is_open())
	{
		int cnt = 0;
		bool x = 0;
		while (getline(myfile, line))
		{
			istringstream iss(line);
			string name;
			char row;
			int col;
			char orientation;
			int size = 0;
			int symbol = 0;
			iss >> name>>row>>col>> orientation;
			//myfile.close();

			if (name == "Carrier")symbol = 5;
			if (name == "Battleship")symbol = 4;
			if (name == "Cruiser")symbol = 2;
			if (name == "Submarine")symbol = 3;
			if (name == "Destroyer")symbol = 1;
			
			if (orientation == 'N')orientation = 4;
			if (orientation == 'S')orientation = 3;
			if (orientation == 'W')orientation = 2;
			if (orientation == 'E')orientation = 1;

			
			if (symbol == 1) size = 2;
			if (symbol == 2 || symbol == 3) size = 3;
			if (symbol == 4) size = 4;
			if (symbol == 5) size = 5;

			coor.m_row = row;
			coor.m_col = col-1;
			//check_position(int(orientation), symbol,coor);
			if (!(coor_available(coor, size, (int)orientation)))
			{
				cout << "Please replace your ships position and try again" << endl;
				error_flag = 1;
				return;
			}
			//coor.m_col = col;
			for (int j = 0; j < size; j++)
			{
				if (orientation == 1) m_board[int(coor.m_row - 'A')][coor.m_col + j].m_ship = new Ship(coor, symbol, (int)orientation);
				if (orientation == 2) m_board[int(coor.m_row - 'A')][coor.m_col - j].m_ship = new Ship(coor, symbol, (int)orientation);
				if (orientation == 3) m_board[int(coor.m_row - 'A' + j)][coor.m_col].m_ship = new Ship(coor, symbol, (int)orientation);
				if (orientation == 4) m_board[int(coor.m_row - 'A' - j)][coor.m_col].m_ship = new Ship(coor, symbol, (int)orientation);
			}
		}
		myfile.close();
	}
	else
	{
		cout << "Unable to open file";
		return;
	}
}
	
int Board::get_num_of_cols()
{
	return  num_of_cols;
}

int Board::get_num_of_rows()
{
	return  num_of_rows;
}

void Board::check_position(int orientation, int symbol,Coor &a)
{
	//orientation  1-E/2-W/3-S/4-N 
	//symbol	   1-Destroir(size of 2)/2-Cruiser(size of 3)/3-S(size of 3)/4-B(size of 4)/5-C(size of 5)
	
	if((symbol==1)&&(orientation==2)&& (a.m_col==0)) a.m_col= (rand() % 9)+1;
	if ((symbol == 1) && (orientation == 1) && (a.m_col == 9)) a.m_col = rand() % 9;
	if ((symbol == 1) && (orientation == 3) && (a.m_row == 9+'A')) a.m_row = (rand() % 9)+'A';
	if ((symbol == 1) && (orientation == 4) && (a.m_row == 0 + 'A')) a.m_row = (rand() % 9) + 'B';

	if ((symbol == 2|| symbol == 3) && (orientation == 1) && (a.m_col == 9|| a.m_col == 8)) a.m_col = rand() % 8 ;
	if ((symbol == 2|| symbol == 3) && (orientation == 2) && (a.m_col == 0 || a.m_col == 1)) a.m_col = (rand() % 8)+2;
	if ((symbol == 2|| symbol == 3) && (orientation == 3) && (a.m_row == 9+'A' || a.m_row == 8+'A')) a.m_row = rand() % 8 + 'A';
	if ((symbol == 2|| symbol == 3) && (orientation == 4) && (a.m_row == 0 + 'A' || a.m_row == 1 + 'A')) a.m_row = rand() % 7 + 'C';

	if ((symbol == 4) && (orientation == 1) && (a.m_col == 9  || a.m_col == 8 || a.m_col == 7)) a.m_col = rand() % 7;
	if ((symbol == 4) && (orientation == 2) && (a.m_col == 0 || a.m_col == 1 || a.m_col == 2)) a.m_col = (rand() % 7)+3;
	if ((symbol == 4) && (orientation == 3) && (a.m_row == 9 + 'A' || a.m_row == 8 + 'A'|| a.m_row == 7 + 'A')) a.m_row = rand() % 7 + 'A';
	if ((symbol == 4) && (orientation == 4) && (a.m_row == 0 + 'A' || a.m_row == 1 + 'A' || a.m_row == 2 + 'A')) a.m_row = rand() % 6 + 'D';
	 
	if ((symbol == 5) && (orientation == 1) && (a.m_col == 9 || a.m_col == 8 || a.m_col == 7|| a.m_col == 6)) a.m_col = rand() % 6;
	if ((symbol == 5) && (orientation == 2) && (a.m_col == 0 || a.m_col == 1 || a.m_col == 2|| a.m_col == 3)) a.m_col = (rand() % 6) + 4;
	if ((symbol == 5) && (orientation == 3) && (a.m_row == 9 + 'A' || a.m_row == 8 + 'A' || a.m_row == 7 + 'A' || a.m_row == 6 + 'A')) a.m_row = rand() % 6 + 'A';
	if ((symbol == 5) && (orientation == 4) && (a.m_row == 0 + 'A' || a.m_row == 1 + 'A' || a.m_row == 2 + 'A' || a.m_row == 3 + 'A')) a.m_row = rand() % 5 + 'E';
}

bool Board::coor_available(const Coor coor,const int size,const int orientation)const
{
	if (m_board[coor.m_row - 'A'][coor.m_col].get_ship() == nullptr) //orientation  1-E/2-W/3-S/4-N
	{
		if (orientation == 1 && size == 2)
		{
			for (int i = 0; i < size; i++) { if (m_board[coor.m_row - 'A'][coor.m_col + i].get_ship() != nullptr) return false; }
		}

		if (orientation == 1 && size == 3)
		{
			for (int i = 0; i < size; i++) { if (m_board[coor.m_row - 'A'][coor.m_col + i].get_ship() != nullptr) return false; }
		}

		if (orientation == 1 && size == 4)
		{
			for (int i = 0; i < size; i++) { if (m_board[coor.m_row - 'A'][coor.m_col + i].get_ship() != nullptr) return false; }
		}

		if (orientation == 1 && size == 5)
		{
			for (int i = 0; i < size; i++) { if (m_board[coor.m_row - 'A'][coor.m_col + i].get_ship() != nullptr) return false; }
		}

		if (orientation == 2 && size == 2)
		{
			for (int i = 0; i < size; i++) { if (m_board[coor.m_row - 'A'][coor.m_col - i].get_ship() != nullptr) return false; }
		}

		if (orientation == 2 && size == 3)
		{
			for (int i = 0; i < size; i++) { if (m_board[coor.m_row - 'A'][coor.m_col - i].get_ship() != nullptr) return false; }
		}

		if (orientation == 2 && size == 4)
		{
			for (int i = 0; i < size; i++) { if (m_board[coor.m_row - 'A'][coor.m_col - i].get_ship() != nullptr) return false; }
		}

		if (orientation == 2 && size == 5)
		{
			for (int i = 0; i < size; i++) { if (m_board[coor.m_row - 'A'][coor.m_col - i].get_ship() != nullptr) return false; }
		}
	

		if (orientation == 3 && size == 2)
		{
			for (int i = 0; i < size; i++) { if (m_board[coor.m_row - 'A' + i][coor.m_col].get_ship() != nullptr) return false; }
		}

		if (orientation == 3 && size == 3)
		{
			for (int i = 0; i < size; i++) { if (m_board[coor.m_row - 'A' + i][coor.m_col].get_ship() != nullptr) return false; }
		}

		if (orientation == 3 && size == 4)
		{
			for (int i = 0; i < size; i++) { if (m_board[coor.m_row - 'A' + i][coor.m_col].get_ship() != nullptr) return false; }
		}
		if (orientation == 3 && size == 5)
		{
			for (int i = 0; i < size; i++) { if (m_board[coor.m_row - 'A' + i][coor.m_col].get_ship() != nullptr) return false; }
		}
		if (orientation == 4 && size == 2)
		{
			for (int i = 0; i < size; i++) { if (m_board[coor.m_row - 'A' - i][coor.m_col].get_ship() != nullptr) return false; }
		}
		if (orientation == 4 && size == 3)
		{
			for (int i = 0; i < size; i++) { if (m_board[coor.m_row - 'A' - i][coor.m_col].get_ship() != nullptr) return false; }
		}

		if (orientation == 4 && size == 4)
		{
			for (int i = 0; i < size; i++) { if (m_board[coor.m_row - 'A' - i][coor.m_col].get_ship() != nullptr) return false; }
		}

		if (orientation == 4 && size == 5)
		{
			for (int i = 0; i < size; i++) { if (m_board[coor.m_row - 'A' - i][coor.m_col].get_ship() != nullptr) return false; }
		}
	}
	else return false;
	return true;
}

bool Board::get_error_flag()
{
	return error_flag;
}

ostream& operator<<(ostream& os, const Board& b)
{
	clrscr();
	setcolor(GREEN, WHITE);
	for (int i = 0; i < b.num_of_cols; i++) {
		gotoxy(i * 2 + 2, 0);
		//printf("%d", i + 1);
		cout << 1 + i;
	}
	for (int i = 0; i < b.num_of_rows; i++) {
		gotoxy(0, i + 1);
		//printf("%c", i + 'A');
		cout << (char)('A' + i);
	}
	/* Prints board */
	for (int i = 0; i < b.num_of_rows; i++) {
		for (int j = 0; j < b.num_of_cols; j++) {
			gotoxy(j * 2 + 1, i + 1);
			const Ship* ship = b.m_board[i][j].get_ship(); //check if we have ship in the ndx[i][j]
			if (ship)
			{
				setcolor(ship->getColor(), LIGHTGRAY);
				//cout << " " << 'S' << " ";
				cout << " " << ship->getSymbol() << " ";
			}
			else {
				setcolor(LIGHTBLUE, LIGHTGRAY);
				cout << " . ";
			}
		}
	}
	setcolor(GREEN, WHITE);
	cout << endl << endl;
	return os;
}

