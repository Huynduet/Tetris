#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <windows.h>
#include "table.cpp"
#include "table.h"



// class Table
// {
// private:
// 	int table [25][10];	 //bang chua vi tri vien gach	hang 0 chua cac so 1
// 	int style;				//kieu vien gach ( O I J L T S Z)

// 	int pos[4][2];	// chua vi tri vien gach con, [][0] = X , [][1] = Y , [0][] la vien ko thay vi tri khi xoay
// 	int fullRows[4];
// 	int score;

// public:
// 	Table( );		//tao bang toan 0 tru hang 0
// 	void show ( ) const ;			//ve bang

// 	void create ( );
// 	void setBrickNum ( int number );	//chuyen so o cac vien gach dang roi ve number
// 	bool spin ( );			//quay pi/2, neu la hinh vuong tra ve 0
// 	void moveLeft ( );		//dich trai
// 	void moveRight ( );		//dich phai
// 	void moveDown ( );		//dich xuong
// 	void fall ( );			//roi luon

// 	bool checkMoveLeft ( ) const ;	//dich trai dc return TRUE
// 	bool checkMoveRight ( )const ;//d ich phai dc return TRUE
// 	bool checkMoveDown ( );		//gach cham gach return TRUE
// 	void getFullRows ( );		//tra ve hang full gach va tang diem
// 	bool checkGameOver ( ) const ;		//GameOver??

// 	void delRow ( int row );	//xoa hang fullRows (xoa den dau ve lai den do)

// 	int getScore ( ) const ;

// };



//tra ve diem sau khi GameOver
int play( )
{
	Table t;	// choi tren Table nay
	unsigned int timeDelay = 1000;	//thoi gian de roi
	char key;		//phim bam vao

	while ( t.checkGameOver() == 0 )
	{
		t.create( );	//tao khoi moi

		while ( t.checkMoveDown( ) )
		{
			Sleep( timeDelay-- );
			
			while ( kbhit() ) 				//doi phim an	
	        {
	        	key = getch();

	        	if ( key == 'a' || key == 'A' ) 			// dich trai neu nhap a || A
	        		t.moveLeft( );
	        	else if ( key == 'd' || key == 'D' ) 		// dich phai neu nhap d || D
	        		t.moveRight( );
	        	else if ( key == 's' || key == 'S' ) 		// roi luon neu nhap s || S
	        		t.fall( );
	        	else if ( key == 'w' || key == 'W' ) 		// xoay
	        		t.spin( );
	        	else if ( key == 'p' || key == 'P' )		// tam dung pause
	        		while ( 1 )
	        		{
	        			//doi den khi an p lan nua thi tiep tuc
	        			if ( key = getch( ) == 'p' || key == 'P' )
	        				break;
	        		}	        		
	       }

	       t.moveDown( );		// dich xuong
	   	}

	   	t.getFullRows( );	//lay diem
	}

	return t.getScore( );	//lay diem 

}


int main() 
{
	play();
	return 0;
}
