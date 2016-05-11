#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <windows.h>
#include <ctime>

#include "table.h"
#include "console.h"



Table::Table(  )		//khoi tao bang
{
	for ( int i = 1; i < 25; ++i )		//vung nhin thay
		for ( int j = 1; j <= 10; ++j )
			table[i][j] = 0;
	for ( int i = 1; i < 25; ++i )		//bien doc
		table[i][0] = table[i][11] = 1;

	for ( int i = 0; i < 12; ++i )		//bien ngang
		table[0][i] = 1;
	srand ( time(NULL) );	//sinh so ngau nhien
}



void Table::show( ) const
{
	for ( int i = 20 ; i >= 1; i-- )
	{
		gotoxy( 26, 22 - i );
		for ( int j = 1; j <= 10; ++j )
		{
			if ( table[i][j] > 0 )
			{
				setTextColor(  ( table[i][j] >= 15 ) ? table[i][j] - 8 :  table[i][j] );
				std::cout << (char)219 << (char)219;
			}
			else
				std::cout << "  ";
		}
	}
}


void Table::create ( int ID )
{
	pos[0][0] = 22; pos[0][1] = 5;
	pos[1][0] = 21; pos[1][1] = 5;
	switch( ID )
	{
		case 0:			// khoi O
		pos[2][0] = 22; pos[2][1] = 6;
		pos[3][0] = 21; pos[3][1] = 6;
		break;
			case 1:			//khoi I
			pos[2][0] = 23; pos[2][1] = 5;
			pos[3][0] = 24; pos[3][1] = 5;
			break;
				case 2:			//khoi 	J
				pos[2][0] = 23; pos[2][1] = 6;
				pos[3][0] = 23; pos[3][1] = 5;
				break;
					case 3:			//khoi L
					pos[2][0] = 23; pos[2][1] = 5;
					pos[3][0] = 21; pos[3][1] = 6;
					break;
				case 4:			//khoi T
				pos[2][0] = 22; pos[2][1] = 6;
				pos[3][0] = 23; pos[3][1] = 5;
				break;
			case 5:			//khoi S
			pos[2][0] = 21; pos[2][1] = 4;
			pos[3][0] = 22; pos[3][1] = 6;
			break;
		case 6:			//khoi Z
		pos[2][0] = 21; pos[2][1] = 6;
		pos[3][0] = 22; pos[3][1] = 4;
		break;
	}
	style = ID + 15;
	setBrickNum( style );
	tempScore = 0;
}

void Table::printNextBrick( int ID )
{
	int i, j, y;
	//Khai bao mang[4][2] chua gach tiep theo
	int **posNext = new int*[4];
	for(i = 0; i < 4; i++)
		posNext[i] = new int[2];
	
	for(i = 0; i < 4; i++)
		for(j = 0; j < 2; j++)
			posNext[i][j] = -1;
	
	switch( ID )
	{
		case 0:			// khoi O
		posNext[2][0] = ID; posNext[1][0] = ID; 
		posNext[1][1] = ID; posNext[2][1] = ID; 
		break;
			case 1:			//khoi I
			posNext[0][0] = ID; posNext[2][0] = ID; 
			posNext[1][0] = ID; posNext[3][0] = ID;
			break;
				case 2:			//khoi 	J
				posNext[0][0] = ID; posNext[0][1] = ID; 
				posNext[1][1] = ID; posNext[2][1] = ID;
				break;
					case 3:			//khoi L
					posNext[2][0] = ID; posNext[0][1] = ID; 
					posNext[1][1] = ID; posNext[2][1] = ID;
					break;
				case 4:			//khoi T
				posNext[1][0] = ID; posNext[0][1] = ID; 
				posNext[1][1] = ID; posNext[2][1] = ID;
				break;
			case 5:			//khoi S
			posNext[1][0] = ID; posNext[0][1] = ID; 
			posNext[1][1] = ID; posNext[2][0] = ID;
			break;
		case 6:			//khoi Z
		posNext[1][0] = ID; posNext[0][0] = ID; 
		posNext[1][1] = ID; posNext[2][1] = ID;
		break;
	}
	//In ra vien gach tiep theo 
	y = 6; //Tung do
	for(j = 0; j < 2; j++)
	{
		gotoxy(58, y);
		for(i = 0; i < 4; i++)
		{
			if( posNext[i][j] >= 0 )
			{
				setTextColor ( ID + 7 );
				std::cout << (char)219 << (char)219;
			}
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


bool Table::rotate ( )			//quay pi/2, neu la hinh vuong tra ve 0
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

		if ( table[ pos[i][0] ][ pos[i][1] ] > 0
			&& table[ pos[i][0] ][ pos[i][1] ] != style  )		//kiem tra co gach bi vuong khi quay ko
		{
			for ( int i = 0; i < 4; ++i )		// phuc hoi vi tri
				pos[i][0] = oldPos[i][0] , pos[i][1] = oldPos[i][1];

			setBrickNum( style );	//phuc hoi khoi gach
			return FALSE;
		}
	}

	setBrickNum( style ); //phuc hoi khoi gach
	show( );	//ve lai
	return TRUE;


}
void Table::moveLeft ( )
{
	if ( checkEmpty( 0, -1 ) )		//check left
	{
		setBrickNum ( 0 );	// xoa

		for ( int i = 0; i < 4; ++i )
			table[ pos[i][0] ][ --pos[i][1] ] = style;	//tai lap
			show( );
	}

}

void Table::moveRight ( )
{
	if ( checkEmpty ( 0, +1 ) )
	{
		setBrickNum ( 0 );	// xoa
		for ( int i = 0; i < 4; ++i )
			table[ pos[i][0] ][ ++pos[i][1] ] = style;	//tai lap
		show( );
	}

}

void Table::moveDown ( )
{
	if ( checkEmpty( -1, 0 ) )
	{
		setBrickNum ( 0 );	// xoa
		for ( int i = 0; i < 4; ++i )
			table[ --pos[i][0] ][ pos[i][1] ] = style;	//tai lap
		show( );
	}
}

bool Table::checkEmpty ( int x, int y ) const
{
	for ( int i = 0; i < 4; ++i )
		if ( table[ pos[i][0] + x ][ pos[i][1] + y ] > 0
			&& table[ pos[i][0] + x ][ pos[i][1] + y ] != style )
			return FALSE;

	return TRUE;
}

void Table::getFullRows ( )	//tra ve hang full gach va tang diem
{
	bool ok;
	for ( int i = 20; i > 0; -- i )
	{
		ok = 1;
		for ( int j = 1; j <= 10; ++j )
			if ( table[i][j] == 0 )
				ok = 0;
		if( ok )	
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
	tempScore ++;
	show( );	//ve lai
}

int Table::getScore ( ) const { return tempScore; }
