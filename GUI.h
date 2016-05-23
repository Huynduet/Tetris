#ifndef __GUI_H__
#define __GUI_H__


class GUI
{
private:
	int  level; //Level cua game
	int  score; //Diem cua nguoi choi
	int  lines; //So hang da an duoc
	WORD COLOR; 
	bool exit;
	WORD KEY; //Phim vua nhap

public:

	void mainMenu( );	//man hinh khoi dong
	void start (  );		//bat dau choi, lay diem tu play( )
	void settings( );	//cai dat
	void printHighScore( ); //hien thi thong tin high score
	void info( );		//thong tin game
	void quit( );		//thoat game


	void printHeader( );	//cls va in ra chua tetris tren 6 dong dau
	int  play( );		//tra ve diem cua lan choi do

	void settingsColor( );	//thay mau trong settings f c
	void settingsLevel( );	//thay va tra ve do kho 1 - easy, 2 - normal, 3 - hard
	void setHighScore(int score); //Luu diem cao vao file

	void printBackground( ); //nen game
	
};


#endif //__GUI_H__
