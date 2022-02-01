
#include "TrackBoard.h"
#include "Board.h"
//#include <string>
//#include <iostream>
//using namespace std;
//#include "Battleship.h"


TrackBoard::TrackBoard()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			m_track_board[i][j] = '.';
		}
	}
}

ostream& operator<<(ostream& os, const TrackBoard& tb)
{
	setcolor(BLUE, WHITE);
	int cols = Board::get_num_of_cols();
	int rows = Board::get_num_of_rows();
	int gap = cols * 3;
	for (int i = 0; i < cols; i++) {
		gotoxy(i * 2 + 2 + gap, 0);
		cout << 1 + i;
	}
	for (int i = 0; i < rows; i++) {
		gotoxy(gap, i + 1);
		cout << (char)('A' + i);
	}
	/* Prints board */
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			gotoxy(j * 2 + 1 + gap, i + 1);
			char c = tb.m_track_board[i][j];
			int color = mark2color(c);
			setcolor(color, LIGHTGRAY);
			cout << " " << c << " ";
		}
	}
	setcolor(GREEN, WHITE);
	cout << endl << endl;
	return os;
}

