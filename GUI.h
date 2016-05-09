#ifndef __GUI_H__
#define __GUI_H__


class GUI
{
private:
	int  level;
	int  score;
	WORD COLOR;
	bool exit;
	WORD KEY;
	int  cursor;
public:

	void mainMenu( );	//man hinh khoi dong
	void start (  );		//bat dau choi, lay diem tu play( )
	void settings( );	//cai dat
	void info( );		//thong tin game
	void quit( );		//thoat game


	void printHeader( );	//cls va in ra chua tetris tren 6 dong dau
	int  play( );		//tra ve diem cua lan choi do

	void settingsColor( );	//thay mau trong settings f c
	void settingsLevel( );	//thay va tra ve do kho 1 - easy, 2 - normal, 3 - hard

	void printBackground( ); //nen game
	int  randIDBrick(); //tao so ngau nhien
	
	void printCursor(int x1, int x2, int y); //In tuy chon, x1, x2, y la toa do 
	void delCursor(int x1, int x2, int y); //Xoa tuy chon cu


};


#endif //__GUI_H__
