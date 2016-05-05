#ifndef __GUI_H__
#define __GUI_H__

#include "table.h"
#include "table.cpp"
#include "console.h"

void mainMenu( );	//man hinh khoi dong
bool start ( char level );		//bat dau choi, lay diem tu play( )
char settings( );	//cai dat
void info( );		//thong tin game
bool quit( );		//thoat game

void printHeader( );	//cls va in ra chua tetris tren 6 dong dau
int  play( int level );		//tra ve diem cua lan choi do
void settingsColor( );	//thay mau trong settings
char settingsLevel( );	//thay va tra ve do kho 1 - easy, 2 - normal, 3 - hard



void mainMenu( )
{

	char key;
	char level; //easy
	bool exit;		//ktra thoat

	level = 1;
	exit = FALSE;

	setTextColor( LIGHTYELLOW );

	while ( !exit )		 		//chay den khi co lenh thoat
	{
		printHeader( );		//in ra 
	
		gotoxy( 20, 10); std::cout << "                     MAIN MENU                     ";
		gotoxy( 20, 13); std::cout << "                  1.   START                       ";
		gotoxy( 20, 15); std::cout << "                  2.  SETTINGS                     ";
		gotoxy( 20, 17); std::cout << "                  3.   INFO                        ";
		gotoxy( 20, 19); std::cout << "                  4.   QUIT                        ";
	
		key = getch( );
	
		if ( key == '1' )
			//std::cout <<"ffffffffffff''", getch();
			exit = !start( level );		
		else if ( key == '2' )
			level = settings( );
		else if ( key == '3' )
			info( );
		else if ( key == '4' )
			exit = quit( );
	}
}

bool start( char level )
{
	int score;
	std::cout <<"Don't delete this line";

	score = play( level );		//chuyen level ve so

	if ( score == -1 )		//thoat ctr
		return FALSE;
	//gameOver == TRUE
	gotoxy( 20, 9 ); std::cout << "                                                   ";
	gotoxy( 20, 10); std::cout << "_______________________GAME OVER___________________";
	gotoxy( 20, 11); std::cout << "                                                   ";
	gotoxy( 20, 12); std::cout << "                YOUR SCORE : " << score << "             ";
	gotoxy( 20, 13); std::cout << "                                                   ";

	Sleep( 5000 );		// wait 5 second
	
	return TRUE;	//tiep tuc
}

char settings( )
{
	char key;
	char level = '1';	

	while ( 1 )
	{
		printHeader( );

		gotoxy( 20, 10); std::cout << "                      SETTINGS                     ";
		gotoxy( 20, 13); std::cout << "                  1.   COLOR                       ";
		gotoxy( 20, 15); std::cout << "                  2.   LEVEL                       ";
		gotoxy( 20, 17); std::cout << "                  3.   BACK                        ";
		
		key = getch( );
		if ( key == '1' )	settingsColor( );
		else if ( key == '2' ) level = settingsLevel( );
		else if ( key == '3' ) return level;	
	}



}

void settingsColor( )
{
	char key;
	bool exit = 0;		//ktra thoat

	gotoxy( 15, 15);	std::cout << "NOTE: If you don't see any color of 8 colors";
	gotoxy( 15, 16);	std::cout << "     Perhaps it's your background color     ";
	gotoxy( 15, 17);	std::cout << "                                            ";

	gotoxy( 20, 18); 
	setTextColor(BLACK);	std::cout << "1.BLACK   ";
	setTextColor(BLUE);		std::cout << "2.BLUE    ";
	setTextColor(GREEN);	std::cout << "3.GREEN   ";
	setTextColor(CYAN);		std::cout << "4.CYAN    ";

	gotoxy( 20, 20); 
	setTextColor(RED);		std::cout << "5.RED     ";
	setTextColor(PURPLE);	std::cout << "6.PURPLE  ";
	setTextColor(GRAY);		std::cout << "7.GRAY    ";
	setTextColor(WHITE);	std::cout << "8.WHITE   ";

	while ( 1 )
	{
		key = getch( );

		if ( key == '1' )	setTextColor( BLACK );
		else if ( key == '2' )	setTextColor( BLUE  );
		else if ( key == '3' )	setTextColor( GREEN );
		else if ( key == '4' )	setTextColor( CYAN  );
		else if ( key == '5' )	setTextColor( RED   );
		else if ( key == '6' )	setTextColor( PURPLE);
		else if ( key == '7' )	setTextColor( GRAY  );
		else if ( key == '8' )	setTextColor( WHITE );

		if ( key >= '1' && key <= '8' )
			return;							//ket thuc ham khi da doi mau
	}
}

char settingsLevel( )
{
	char key;

	gotoxy( 20, 19);
	std::cout << " CHOOSE LEVEL:    1. EASY     2. NORMAL     3. HARD ";
	while( ! ( key = getch( ) >= '1' && key <= '3' ) )		//lap den khi doc dung phim
	{
		//do nothing
	}

	return key;
}
void info( )		//thong tin game
{
	printHeader( );

	
}
bool quit( )		//thoat game
{
	if ( confirm( "EXIT") )
		return 1;		//thoat game
	return 0;
}



void printHeader( )
{

	system( "cls" );

	gotoxy( 20, 1 ); std::cout << " __________ ________ __________ _________ ___ ___________";
	gotoxy( 20, 2 ); std::cout << "/___   ___//  _____//___   ___//        //  //  ________/";
	gotoxy( 20, 3 ); std::cout << "   /  /   /  /___      /  /   /   /____//  //  /_______";
	gotoxy( 20, 4 ); std::cout << "  /  /   /  ____/     /  /   /  ___   //  //_______   /";
	gotoxy( 20, 5 ); std::cout << " /  /   /  /____     /  /   /  /  /  //  / _______/  /";
	gotoxy( 20, 6 ); std::cout << "/__/   /_______/    /__/   /__/  /__//__/ /_________/";
}




int play( int level )
{
	Table t;	// choi tren Table nay
	unsigned int timeDelay = 1000 - level * 150 ;	//thoi gian de roi
	char key;		//phim bam vao

	system( "cls" );

	std::cout <"""""""""""";
	while ( t.checkGameOver() == 0 )
	{
		t.create( );	//tao khoi moi

		while ( t.checkMoveDown( ) )
		{
			Sleep( ( timeDelay --  ) + 3 );
			
			while ( kbhit() ) 				//doi phim an	
	        {
	        	key = getch();

	        	if ( key == 'a' || key == 'A' ) 			// dich trai neu nhap A
	        		t.moveLeft( );
	        	else if ( key == 'd' || key == 'D' ) 		// dich phai neu nhap D
	        		t.moveRight( );
	        	else if ( key == 's' || key == 'S') 		// roi luon neu nhap s
	        		t.fall( );
	        	else if ( key == 'w' || key == 'W' ) 		// xoay
	        		t.spin( );
	        	else if ( key == 'p' || key == 'P' || key == 13 )		// tam dung pause
	        		while ( 1 )
	        		{
	        			system( "cls" );	//xoa man hinh, chong gian lan
	        			gotoxy( 35, 9 );
	        			std::cout << "PAUSE";
	        			gotoxy( 30, 12 );
	        			std::cout << "1. RESUME";
	        			gotoxy( 30, 14 );
	        			std::cout << "2. RESTART";
	        			gotoxy( 30, 16 );
	        			std::cout << "3. MAIN MENU";

	        			key = getch( );		//doc lua chon
	        			if ( key == 'p' || key == 'P' || key == 13 || key == '1' )	//tiep tuc
	        				break;
	        			else if ( key == '2' && confirm("RESTART") )		//choi lai ( can  xac nhan )
	        				return play( level );			
	        			else if ( key == '3' && confirm("BACK TO MAIN MENU") )		//quay ve
	        				return restart( );
	        		}	        		
	       }

	       t.moveDown( );		// dich xuong
	   	}

	   	t.getFullRows( );	//lay diem
	}

	return t.getScore( );	//lay diem 

}



#endif //__GUI_H__
