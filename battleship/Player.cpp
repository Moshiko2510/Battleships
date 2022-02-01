#include "Player.h"


Player::Player(string name,string f_name) : m_name(name)
{
	m_board=new Board(f_name);
	m_track_board= new TrackBoard;
}

Player::Player(string name) : m_name(name)
{	
	m_board = new Board();
	m_track_board = new TrackBoard;
}

Player::~Player()
{
	delete m_board;
	delete m_track_board;	
}

char Player::attack(const Coor& coor)
{
	bool sunked = 0;
	int sunk_cnt = 0;
	if (m_board->m_board[coor.m_row - 'A'][coor.m_col - 1].m_attacked == true)
	{
		return 0;  //point already attacked
	}
		
	if (m_board->m_board[coor.m_row - 'A'][coor.m_col - 1].get_ship() == nullptr)
	{
		m_board->m_board[coor.m_row - 'A'][coor.m_col - 1].m_attacked = true;	//miss
		
		return 'M';
	}	
	else
	{
		m_board->m_board[coor.m_row - 'A'][coor.m_col - 1].m_attacked = true;
		sunked=check_for_sunked_ship (coor);   //hit

		if (sunked == false)
		{
			return 'H';
		}
		else
		{	
			return 'S';
		}
	}	
}

bool Player::check_for_sunked_ship(Coor coor)
{
	/*This function scan the board and check size and symbol of every ships. 
	all the ships that match the selected ship will be mark as sunked when counter equel to original size of the ship by the function mark_sink.*/

	int cnt = 0;
	int size = 0;
	char symbol = 0;
	if (m_board->m_board[coor.m_row - 'A'][coor.m_col - 1].get_ship())
	{
		size = m_board->m_board[coor.m_row - 'A'][coor.m_col - 1].get_ship()->m_size;
		symbol = m_board->m_board[coor.m_row - 'A'][coor.m_col - 1].get_ship()->getSymbol();
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				if (m_board->m_board[i][j].get_ship() != nullptr)
				{
					if ((size == m_board->m_board[i][j].get_ship()->m_size) &&(symbol== m_board->m_board[i][j].get_ship()->getSymbol())&& m_board->m_board[i][j].m_attacked == true)
						cnt++;
					if (cnt == m_board->m_board[coor.m_row - 'A'][coor.m_col - 1].get_ship()->m_size)
					{
						mark_sink(size,symbol);
						return true;
					}

				}
			}
		}
		return false;
	}
}

void Player::mark_sink(int size,char symbol)
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (m_board->m_board[i][j].get_ship() != nullptr)
			{
				if (size == m_board->m_board[i][j].get_ship()->m_size && (symbol == m_board->m_board[i][j].get_ship()->getSymbol()))
					m_board->m_board[i][j].m_sunk = true;
					
			}
		}
	}
}