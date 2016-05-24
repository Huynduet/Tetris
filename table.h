#ifndef __TABLE_H__
#define __TABLE_H__

#include "console.h"
/*Note:
	*** Trong bang:
	- 0 la vi tri ko co gach
	- 1 - 7 la vi tri gach
*/

class Table
{
private:
	int  table [25][12];  //bang chua vi tri vien gach	hang 0 chua cac so 1, cot 0 , 11 la bien
	int  style;			  //kieu vien gach ( O I J L T S Z)

	int  pos[4][2];	      // chua vi tri vien gach con, [][0] = X , [][1] = Y , [0][] la vien ko thay vi tri khi xoay
	int  posNext[4][2];   //Chua vien gach tiep theo hien len man hinh
	int  fullRows[4];
	int  deletedLines;
	WORD COLOR;

public:
	Table( );		                //tao bang toan 0 tru hang 0
	void show ( ) const ;			//ve bang

	void create ( int ID );         // Tao vien gach theo ID
	void printNextBrick ( int ID ); //In ra vien gach xuat hien tiep theo theo ID
	void setBrickNum ( int number );//chuyen so o cac vien gach dang roi ve number
	bool rotate ( );			    //quay pi/2, neu la hinh vuong tra ve 0
	void moveLeft ( );		        //dich trai
	void moveRight ( );		        //dich phai
	void moveDown ( );		        //dich xuong

	bool checkEmpty ( int x, int y ) const;	// ktra o trong
	void getFullRows ( );		            //tra ve hang full gach va tang diem
	bool checkGameOver ( ) const ;		    //GameOver??

	void delRow ( int row );	            //xoa hang fullRows (xoa den dau ve lai den do)

	int  getDeletedLines ( ) const ;        //Tra ve diem cua game

};


#endif  //__TABLE_H__
