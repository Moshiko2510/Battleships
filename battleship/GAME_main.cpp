/***********************************************------Battleship Game-----********************************
***********************************************---Made by: Moshiko Nissim----****************************
***********************************************-------Date: 10/12/20------*******************************/

#include "Battleship.h"
#include <time.h>

void func()
{
	srand(time(0));
	string board_fn = "board.txt";
	Battleship bs(board_fn);
	cout << "The winner is " << bs.Play() << endl;
	system("PAUSE");
}

int main()
{
	func();
	//srand(time(0));
	//string board_fn = "board.txt";
	//Battleship bs(board_fn);
	//cout << "The winner is " << bs.Play() << endl;
	//system("PAUSE");
	
	cout << "Leaks: " << _CrtDumpMemoryLeaks() << endl;
	return 0;
}

