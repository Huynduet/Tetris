#ifndef __TABLE_H__
#define __TABLE_H__

#include "console.h"
/*Note:
	*** Trong bang:
	- 0 la vi tri ko co gach
	- 1 la vi tri gach cu, da roi
	- 2 la nhung vien gach dang roi

*/

class Table
{
private:
	int table [25][12];	 //bang chua vi tri vien gach	hang 0 chua cac so 1, cot 0 , 11 la bien
	int style;				//kieu vien gach ( O I J L T S Z)

	int pos[4][2];	// chua vi tri vien gach con, [][0] = X , [][1] = Y , [0][] la vien ko thay vi tri khi xoay
	int fullRows[4];
	int tempScore;
	WORD COLOR;

public:
	Table( );		//tao bang toan 0 tru hang 0
	void show ( ) const ;			//ve bang

	void create ( int style );
	void printNextBrick ( int style );
	void setBrickNum ( int number );	//chuyen so o cac vien gach dang roi ve number
	bool rotate ( );			//quay pi/2, neu la hinh vuong tra ve 0
	void moveLeft ( );		//dich trai
	void moveRight ( );		//dich phai
	void moveDown ( );		//dich xuong
	void fall ( );			//roi luon

	bool checkMoveLeft ( ) const ;	//dich trai dc return TRUE
	bool checkMoveRight ( )const ;//dich phai dc return TRUE
	bool checkMoveDown ( );		//dich xuong dc return TRUE
	void getFullRows ( );		//tra ve hang full gach va tang diem
	bool checkGameOver ( ) const ;		//GameOver??

	void delRow ( int row );	//xoa hang fullRows (xoa den dau ve lai den do)

	int getScore ( ) const ;

};


#endif  //__TABLE_H__
