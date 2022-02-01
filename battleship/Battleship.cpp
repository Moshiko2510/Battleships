
#include "Battleship.h"
using namespace std;


Battleship::Battleship(string f_name)
{
	string name;
	
	cout << "Enter your name: ";
	cin>>name;
	User = new Player(name,f_name);    //create User 
	cout << *User->m_board;
	
	Computer = new Player("Computer");   //create computer
	//cout << *Computer->m_board;
	cout << *Computer->m_track_board;
}

Battleship::~Battleship()
{
	delete Computer;
	delete User;
}

string Battleship::Play()
{
	/*This function manage the game for the two users.
	user choose Coor/Rand Coor and send it to Attack function that return the result for the Trackboard.
	when all 5 ships is sunked win condition is true and the game is over.*/

	Coor coor;
	coor.m_col = 0;
	coor.m_row = 0;
	if (User->m_board->get_error_flag() == true)
	{
		return "No one";
	}
	bool user_turn = true, comp_turn = true;
	char result = 0;
	int size = 0;
	char symbol = 0;
	user_turn = true;
	comp_turn = false;
	int comp_sunk_cnt = 0,user_sunk_cnt=0;

	while (1)
	{	
		while (comp_turn)       //computer turn loop
		{
			cout << *User->m_board;
			cout << *User->m_track_board;
			coor.m_row = rand() % 10 + 'A';
			coor.m_col = rand() % 10;
			cout << "computer attack coor: " << coor.m_row << coor.m_col+1 << endl;
			result = User->attack(coor);

			//Results:
			if (result != 'H' || result != 'S')
			{ 
				comp_turn = false;
				user_turn = true;
			}
			if (result == 'M') cout << "computer missed" << endl;
			else if (result == 'H') cout << "your ship was hit" << endl;
			else if (result == 'S')
			{
				comp_sunk_cnt++;
				size = Computer->m_board->m_board[coor.m_row - 'A'][coor.m_col-1].get_ship()->m_size;
				symbol = Computer->m_board->m_board[coor.m_row - 'A'][coor.m_col - 1].get_ship()->getSymbol();
				mark_sink_trackboard(size,symbol);
				if (comp_sunk_cnt == TOTAL_SHIPS)  return "Computer";     //loss condition
				cout << "your ship is sunk" << endl;
			}
			system("PAUSE");
			if (result != 0)
			Computer->m_track_board->m_track_board[coor.m_row - 'A'][coor.m_col-1] = result;   
		}

		while (user_turn)    //user turn loop
		{
			cout << *User->m_board;
			cout << *User->m_track_board;
			coor = choose_coor_for_attack(coor);
			result = Computer->attack(coor);			//check the choosen coor in board

			//Results:
			if (result != 'H' && result != 'S')
			{
				user_turn = false;
				comp_turn = true;
			}
			if (result == 'M') cout << "you missed this one, try next time" << endl;	
			else if (result == 'H') cout << "great move, you earned another turn" << endl;
			else if (result==0) cout << "point already attacked, try next time" << endl;
			else if (result == 'S')
			{
				user_sunk_cnt++;
				size = Computer->m_board->m_board[coor.m_row - 'A'][coor.m_col-1].get_ship()->m_size;
				symbol = Computer->m_board->m_board[coor.m_row - 'A'][coor.m_col - 1].get_ship()->getSymbol();
				mark_sink_trackboard(size,symbol);
				if (user_sunk_cnt == TOTAL_SHIPS)  return User->m_name;   //loss condition
				cout << "great move, you earned another turn,ship is sunk" << endl;	
			}
			system("PAUSE");
			if(result!=0)
			User->m_track_board->m_track_board[coor.m_row - 'A'][coor.m_col-1] = result;
			
			}
		}
}


Coor Battleship::choose_coor_for_attack(Coor coor)
{
	cout << User->m_name<< " Please choose position for attack: " << endl;
	cin >> coor.m_row;
	cin >> coor.m_col;
	return coor;
}

void Battleship::mark_sink_trackboard(int size,char symbol)
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (Computer->m_board->m_board[i][j].get_ship() != nullptr)
			{
				if ((size == Computer->m_board->m_board[i][j].get_ship()->m_size) && (symbol == Computer->m_board->m_board[i][j].get_ship()->getSymbol()))
					User->m_track_board->m_track_board[i][j] = 'S';
			}
		}
	}
}

