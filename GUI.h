#ifndef __GUI_H__
#define __GUI_H__

#include <windows.h>
#include <sstream>
#include <fstream>

class GUI
{
private:
	int  level;                      //Level cua game
	int  score;                      //Diem cua nguoi choi
	int  lines;                      //So hang da an duoc
	WORD COLOR;                      //Mau cua game
	bool exit;                       //exit = true -> thoat game, false -> tiep tuc
	WORD KEY;                        //Phim vua nhap
	int  h_score[10];                //10 diem cao nhat
	char pathHighScore[MAX_PATH];    //Ten file chua high score
	char pathREADME[MAX_PATH];       //Ten file chua readme.txt
	std::stringstream sstringREADME; //Noi dung file README
	std::fstream fileHighScore;      //Luong nhap va ghi high score
	std::fstream fileREADME;         //Luong nhap va ghi README
public:
	GUI( );			        // constructor khoi tao cac gia tri
	void mainMenu( );	    //man hinh khoi dong
	void start (  );		//bat dau choi, lay diem tu play( )
	void settings( );	    //cai dat
	void printHighScore( ); //hien thi thong tin high score
	void info( );		    //thong tin game
	void quit( );		    //thoat game

	void printHeader( );	//cls va in ra chua tetris tren 6 dong dau
	int  play( );		    //tra ve diem cua lan choi do

	void settingsColor( );	      //thay mau trong settings f c
	void settingsLevel( );	      //thay va tra ve do kho 1 - easy, 2 - normal, 3 - hard
	void setHighScore(int score); //Luu diem cao vao file

	void printBackground( );      //Nen game
	
};


#endif //__GUI_H__
