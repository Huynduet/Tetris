#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <windows.h>
#include <ctime>

#include "table.h"
#include "console.h"



Table::Table( )		//khoi tao bang
{
	for ( int i = 1; i < 25; ++i )		//vung nhin thay
		for ( int j = 1; j <= 10; ++j )
			table[i][j] = 0;
	for ( int i = 1; i < 25; ++i )		//bien doc
		table[i][0] = table[i][11] = 1;

	for ( int i = 0; i < 12; ++i )		//bien ngang
		table[0][i] = 1;
	score = 0;
	srand ( time(NULL) );	//sinh so ngau nhien
}



void Table::show( ) const
{
	char chr = 219;

	gotoxy( 25, 1 );
	for ( int j = 0; j < 22; ++j )
	{
		setTextColor( LIGHTGRAY );
		std::cout << (char)220;
	}
		
	for ( int i = 20 ; i >= 1; i-- )
	{
		gotoxy( 25, 22 - i );
		std::cout << (char)221;	//bien

		for ( int j = 1; j <= 10; ++j )
		{
			if ( table[i][j] == 1 )
			{
				setTextColor( LIGHTRED );
				std::cout << chr << chr;
			}
			
			else if ( table[i][j] == 2 )
			{
				setTextColor( LIGHTGREEN );
				std::cout << chr << chr;
			}
				
			else
				std::cout << "  ";
		}
		setTextColor( LIGHTGRAY );
		std::cout << (char)222 << std::endl;
	}

	gotoxy( 25, 22 ); 
	for ( int j = 0; j < 22; ++j )
	{
		setTextColor( LIGHTGRAY );
		std::cout << (char)223;
	}
	
	setTextColor( LIGHTGREEN );
	gotoxy( 3, 2 );
	std::cout << "~~~~~~~~~~~~~~~";
	gotoxy( 3, 4 );
	std::cout << "  Score: " << score;
	gotoxy( 3, 6 );
	std::cout << "~~~~~~~~~~~~~~~";
	gotoxy( 5, 11);
	std::cout << "HOW TO PLAY";
	gotoxy( 4, 13 );
	std::cout << " Left  :  A";
	gotoxy( 4, 14 );
	std::cout << "Right  :  D";
	gotoxy( 4, 15 );
	std::cout << " Spin  :  W";
	gotoxy( 4, 16 );
	std::cout << " Drop  :  S";
	gotoxy( 4, 17 );
	std::cout << "Pause  :  P";
}

void Table::create ( int style )
{
	table[ pos[0][0] = 22 ][ pos[0][1] = 5] = 2;
	table[ pos[1][0] = 21 ][ pos[1][1] = 5] = 2;
	switch( style )
	{
		case 0:			// khoi O
		table[ pos[2][0] = 22 ][ pos[2][1] = 6] = 2;
		table[ pos[3][0] = 21 ][ pos[3][1] = 6] = 2;
		break;
			case 1:			//khoi I
			table[ pos[2][0] = 23 ][ pos[2][1] = 5] = 2;
			table[ pos[3][0] = 24 ][ pos[3][1] = 5] = 2;
			break;
				case 2:			//khoi 	J
				table[ pos[2][0] = 23 ][ pos[2][1] = 6] = 2;
				table[ pos[3][0] = 23 ][ pos[3][1] = 5] = 2;
				break;
					case 3:			//khoi L
					table[ pos[2][0] = 23 ][ pos[2][1] = 5] = 2;
					table[ pos[3][0] = 21 ][ pos[3][1] = 6] = 2;
					break;
				case 4:			//khoi T
				table[ pos[2][0] = 22 ][ pos[2][1] = 6] = 2;
				table[ pos[3][0] = 23 ][ pos[3][1] = 5] = 2;
				break;
			case 5:			//khoi S
			table[ pos[2][0] = 21 ][ pos[2][1] = 4] = 2;
			table[ pos[3][0] = 22 ][ pos[3][1] = 6] = 2;
			break;
		case 6:			//khoi Z
		table[ pos[2][0] = 21 ][ pos[2][1] = 6] = 2;
		table[ pos[3][0] = 22 ][ pos[3][1] = 4] = 2;
		break;
	}
}

void Table::printNextBrick( int style )
{
	int i, j, y;
	//Khai bao mang[4][2] chua gach tiep theo
	int **posNext = new int*[4];
	for(i = 0; i < 4; i++)
		posNext[i] = new int[2];
	
	for(i = 0; i < 4; i++)
		for(j = 0; j < 2; j++)
			posNext[i][j] = 0;
	
	switch( style )
	{
		case 0:			// khoi O
		posNext[0][0] = 1; posNext[1][0] = 1; 
		posNext[1][1] = 1; posNext[0][1] = 1; 
		break;
			case 1:			//khoi I
			posNext[0][0] = 1; posNext[2][0] = 1; 
			posNext[1][0] = 1; posNext[3][0] = 1;
			break;
				case 2:			//khoi 	J
				posNext[0][0] = 1; posNext[0][1] = 1; 
				posNext[1][1] = 1; posNext[2][1] = 1;
				break;
					case 3:			//khoi L
					posNext[2][0] = 1; posNext[0][1] = 1; 
					posNext[1][1] = 1; posNext[2][1] = 1;
					break;
				case 4:			//khoi T
				posNext[1][0] = 1; posNext[0][1] = 1; 
				posNext[1][1] = 1; posNext[2][1] = 1;
				break;
			case 5:			//khoi S
			posNext[1][0] = 1; posNext[0][1] = 1; 
			posNext[1][1] = 1; posNext[2][0] = 1;
			break;
		case 6:			//khoi Z
		posNext[1][0] = 1; posNext[0][0] = 1; 
		posNext[1][1] = 1; posNext[2][1] = 1;
		break;
	}
	//In ra vien gach tiep theo 
	y = 6; //Tung do
	for(j = 0; j < 2; j++)
	{
		gotoxy(58, y);
		for(i = 0; i < 4; i++)
		{
			if( posNext[i][j] == 1 )
				std::cout << (char)219 << (char)219;
			else 
				std:: cout << "  ";
		}
		y++;
	}
	//Giai phong bo nho
	for(i = 0; i < 4; i++)
		delete []posNext[i];
	delete []posNext;
}

void Table::setBrickNum ( int number )
{
	for ( int i = 0 ; i < 4 ; ++i )
		table[ pos[i][0] ][ pos [i][1] ] = number;
}


bool Table::spin ( )			//quay pi/2, neu la hinh vuong tra ve 0
{
	if ( style == 0 )	//la kieu O thi dung lai
		return FALSE;

	int deltaX, deltaY;
	int oldPos[4][2];	//luu vi tri luc dau
	for ( int i = 0; i < 4; ++i )		// sao chep vi tri
		oldPos[i][0] = pos[i][0] , oldPos[i][1] = pos[i][1];

	setBrickNum( 0 );	//xoa bo tam khoi gach
	for ( int i = 1; i < 4; ++i )
	{
		deltaX = pos[i][0] - pos[0][0];
		deltaY = pos[i][1] - pos[0][1];

		table[ pos[i][0] ][ pos[i][1] ] = 0;	//xoa bo trang thai

		pos[i][0] = pos[0][0] + deltaY;
		pos[i][1] = pos[0][1] - deltaX;

		if ( table[ pos[i][0] ][ pos[i][1] ] == 1 )		//kiem tra co gach bi vuong khi quay ko
		{
			for ( int i = 0; i < 4; ++i )		// phuc hoi vi tri
				pos[i][0] = oldPos[i][0] , pos[i][1] = oldPos[i][1];

			setBrickNum( 2 );	//phuc hoi khoi gach
			return FALSE;
		}
	}

	setBrickNum( 2 ); //phuc hoi khoi gach
	show( );	//ve lai
	return TRUE;


}
void Table::moveLeft ( )
{
	if ( checkMoveLeft() )
	{
		setBrickNum ( 0 );	// xoa

		table[ pos[0][0] ][ --pos[0][1] ] = 2;	//tai lap
		table[ pos[1][0] ][ --pos[1][1] ] = 2;
		table[ pos[2][0] ][ --pos[2][1] ] = 2;
		table[ pos[3][0] ][ --pos[3][1] ] = 2;

		show( );
	}

}

void Table::moveRight ( )
{
	if ( checkMoveRight() )
	{
		setBrickNum ( 0 );	// xoa

		table[ pos[0][0] ][ ++pos[0][1] ] = 2;	//tai lap
		table[ pos[1][0] ][ ++pos[1][1] ] = 2;
		table[ pos[2][0] ][ ++pos[2][1] ] = 2;
		table[ pos[3][0] ][ ++pos[3][1] ] = 2;

		show( );
	}

}

void Table::moveDown ( )
{
	if ( checkMoveDown() )
	{
		setBrickNum ( 0 );	// xoa

		table[ --pos[0][0] ][ pos[0][1] ] = 2;	//tai lap
		table[ --pos[1][0] ][ pos[1][1] ] = 2;
		table[ --pos[2][0] ][ pos[2][1] ] = 2;
		table[ --pos[3][0] ][ pos[3][1] ] = 2;

		show( );
	}
}


void Table::fall ( )
{
	while ( checkMoveDown() )			//dich xuong neu co the
	{
		moveDown( );
	}
}

bool Table::checkMoveLeft ( ) const
{
	if ( table[ pos[0][0] ][ pos[0][1] - 1 ] == 1
		 || table[ pos[1][0] ][ pos[1][1] - 1 ] == 1
		 || table[ pos[2][0] ][ pos[2][1] - 1 ] == 1
		 || table[ pos[3][0] ][ pos[3][1] - 1 ] == 1 )

		return FALSE;
	else
		return TRUE;

}

bool Table::checkMoveRight ( ) const
{
	if ( table[ pos[0][0] ][ pos[0][1] + 1 ] == 1
		 || table[ pos[1][0] ][ pos[1][1] + 1 ] == 1
		 || table[ pos[2][0] ][ pos[2][1] + 1 ] == 1
		 || table[ pos[3][0] ][ pos[3][1] + 1 ] == 1 )

		return FALSE;
	else
		return TRUE;

}

bool Table::checkMoveDown ( )
{
	if ( table[ pos[0][0] - 1 ][ pos[0][1] ] == 1
		 || table[ pos[1][0] - 1 ][ pos[1][1] ] == 1
		 || table[ pos[2][0] - 1 ][ pos[2][1] ] == 1
		 || table[ pos[3][0] - 1 ][ pos[3][1] ] == 1 )

	{
		setBrickNum ( 1 );	///bien thanh gach cu
		return FALSE;
	}
	else
		return TRUE;

}

void Table::getFullRows ( )	//tra ve hang full gach va tang diem
{
	int sum;
	for ( int i = 20; i > 0; -- i )
	{
		sum = 0;
		for ( int j = 1; j <= 10; ++j )
			sum += table[i][j];
		if ( sum == 10 )
			delRow( i );
	}
}
bool Table::checkGameOver ( ) const		//GameOver??
{
	for ( int i = 0; i < 4; ++i )
		if ( pos[i][0] > 20 ) //cham max
			return TRUE;
	return FALSE;
}

void Table::delRow ( int row )	//xoa hang  row  (xoa den dau ve lai den do)
{
	for ( int j = row ; j < 21; ++j )
		for ( int k = 1; k <= 10; ++k )
			table[j][k] = table[j + 1][k];
	score ++;
	show( );	//ve lai
}

int Table::getScore ( ) const { return score; }
