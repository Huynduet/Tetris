#include "table.h"
#include "table.cpp"
#include "console.h"
#include "GUI.h"




void GUI::mainMenu( )
{
	srand(time(NULL));
	cursor = 13; //Toa do dau tien cua con tro
	level = 1;
	exit = FALSE;
	COLOR = LIGHTGREEN;

	while ( !exit )		 		//chay den khi co lenh thoat
	{
		setTextColor( COLOR );
		printHeader( );		//in ra 
		
		gotoxy( 20, 10); std::cout << "                     MAIN MENU                     ";
		gotoxy( 20, 13); std::cout << "                       START                       ";
		gotoxy( 20, 15); std::cout << "                      SETTINGS                     ";
		gotoxy( 20, 17); std::cout << "                       INFO                        ";
		gotoxy( 20, 19); std::cout << "                       QUIT                        ";
		
		while( 1 )
		{
			printCursor(28, 60, cursor);
			
			KEY = key_press( );
			
			if( KEY == KEY_DOWN ) //Di chuyen con tro xuong
			{
				if(cursor <= 17)
					cursor += 2;
			}
			else if( KEY == KEY_UP ) //Di chuyen con tro len
			{
				if(cursor >= 15)
					cursor -= 2;
			}

			printCursor(28, 60, cursor);
			
			if( KEY == ENTER )
				break;
		}
		
		if(cursor == 13)
			start( );
		else if(cursor == 15)
			settings( );
		else if(cursor == 17)
			info( );
		else if(cursor == 19 || KEY == ESCAPE )
			quit( );	
	}

}

void GUI::start( )
{
	std::cout <<"Don't delete this line";

	score = play( );	
	if ( score == -1 )
	{
		exit = TRUE;
		return;
	}

	//gameOver == TRUE
	setTextColor( COLOR );
	gotoxy( 20, 9 ); std::cout << "                                                   ";
	gotoxy( 20, 10); std::cout << "_______________________GAME OVER___________________";
	gotoxy( 20, 11); std::cout << "                                                   ";
	gotoxy( 20, 12); std::cout << "                YOUR SCORE : " << score << "             ";
	gotoxy( 20, 13); std::cout << "                                                   ";

	getch( );
}

void GUI::settings( )
{
	while ( TRUE )
	{
		printHeader( );

		gotoxy( 20, 10); std::cout << "                      SETTINGS                     ";
		gotoxy( 20, 13); std::cout << "                       COLOR                       ";
		gotoxy( 20, 15); std::cout << "                       LEVEL                       ";
		gotoxy( 20, 17); std::cout << "                       BACK                        ";
		
		while( TRUE )
		{
			printCursor(28, 60, cursor);
			
			KEY = key_press( );
			
			if( KEY == KEY_DOWN ) //Di chuyen con tro xuong
			{
				if(cursor <= 15)
					cursor += 2;
			}
			else if( KEY == KEY_UP ) //Di chuyen con tro len
			{
				if(cursor >= 15)
					cursor -= 2;
			}

			printCursor(28, 60, cursor);
			
			if( KEY == ENTER )
				break;
		}
		
		if(cursor == 13)
			settingsColor( );
		else if(cursor == 15)
			settingsLevel( );
		else if(cursor == 17)
			return;
	}
}

void GUI::settingsColor( )
{
	char key;
	gotoxy( 15, 15);	std::cout << "NOTE: If you don't see any color of 8 colors";
	gotoxy( 15, 16);	std::cout << "     Perhaps it's your background color     ";
	gotoxy( 15, 17);	std::cout << "                                            ";

	gotoxy( 20, 18); 
	setTextColor(LIGHTYELLOW);	std::cout << "1.YELLOW   ";
	setTextColor(LIGHTBLUE);		std::cout << "2.BLUE    ";
	setTextColor(LIGHTGREEN);	std::cout << "3.GREEN   ";
	setTextColor(LIGHTCYAN);		std::cout << "4.CYAN    ";

	gotoxy( 20, 20); 
	setTextColor(LIGHTRED);		std::cout << "5.RED     ";
	setTextColor(LIGHTPURPLE);	std::cout << "6.PURPLE  ";
	setTextColor(LIGHTGRAY);		std::cout << "7.GRAY    ";
	setTextColor(LIGHTWHITE);	std::cout << "8.WHITE   ";

	while ( 1 )
	{
		key = getch( );

		// if ( key == '1' )	setTextColor( LIGHTYELLOW );
		// else if ( key == '2' )	setTextColor( LIGHTBLUE  );
		// else if ( key == '3' )	setTextColor( LIGHTGREEN );
		// else if ( key == '4' )	setTextColor( LIGHTCYAN  );
		// else if ( key == '5' )	setTextColor( LIGHTRED   );
		// else if ( key == '6' )	setTextColor( LIGHTPURPLE);
		// else if ( key == '7' )	setTextColor( LIGHTGRAY  );
		// else if ( key == '8' )	setTextColor( LIGHTWHITE );

		if ( key >= '1' && key <= '8' )
		{
			COLOR = key - '0' + 7;
			setTextColor( COLOR );
			return;
		}					//ket thuc ham khi da doi mau
	}
}

void GUI::settingsLevel( )
{
	char key = 0;
	gotoxy( 20, 19);
	std::cout << " CHOOSE LEVEL:    1. EASY     2. NORMAL     3. HARD ";
	while( ! ( key >= '1' && key <= '3' ) )		//lap den khi doc dung phim
	{
		key = getch( );
	}

	if ( key == '1' ) level = 1;
	else if ( key == '2' ) level = 2;
	else if ( key == '3' ) level = 3;

}
void GUI::info( )		//thong tin game
{
	printHeader( );

	system("notepad README.txt");
}
void GUI::quit( )		//thoat game
{
	if ( confirm( "EXIT" ) )
		exit = TRUE;		//thoat game
	else 
		exit = FALSE;
}



void GUI::printHeader( )
{

	system( "cls" );

	gotoxy( 20, 1 ); std::cout << " __________ ________ __________ _________ ___ ___________";
	gotoxy( 20, 2 ); std::cout << "/___   ___//  _____//___   ___//        //  //  ________/";
	gotoxy( 20, 3 ); std::cout << "   /  /   /  /___      /  /   /   /____//  //  /_______";
	gotoxy( 20, 4 ); std::cout << "  /  /   /  ____/     /  /   /  ___   //  //_______   /";
	gotoxy( 20, 5 ); std::cout << " /  /   /  /____     /  /   /  /  /  //  / _______/  /";
	gotoxy( 20, 6 ); std::cout << "/__/   /_______/    /__/   /__/  /__//__/ /_________/";
}

int GUI::randIDBrick()
{
	
	return rand() % 7 ;
}

int GUI::play( )
{
	Table t;	// choi tren Table nay
	double timeDelay = 1000 - level * 300 ;	//thoi gian de roi
	int IDBrick, IDNextBrick; //So thu tu cua gach
	score = 0;
	system( "cls" );



	// std::cout << "HINT";
	// gotoxy( 4, 13 );
	// // std::cout << "  Left  :  A";
	// gotoxy( 4, 14 );
	// std::cout << " Right  :  D";
	// gotoxy( 4, 15 );
	// std::cout << "Rotate  :  W";
	// gotoxy( 4, 16 );
	// std::cout << "  Drop  :  S";
	// gotoxy( 4, 17 );
	// std::cout << " Pause  :  P";
	
	//Tao 2 khoi gach dau tien
	IDBrick = randIDBrick(); 
	IDNextBrick = randIDBrick();
	printBackground( );
	while ( t.checkGameOver() == 0 )
	{	
		t.create( IDBrick );	//tao khoi moi
		
		while ( t.checkMoveDown( ) )
		{
			//In ra vien gach tiep theo

			setTextColor( IDNextBrick + 7 );
			t.printNextBrick( IDNextBrick );
		
			Sleep( ( timeDelay *= 0.995 ) );
			int count = 5;
			while (--count  && kbhit() ) 				//doi phim an	
	        {
	        	KEY = key_press( );
	        	if ( KEY == KEY_LEFT ) 			// dich trai neu nhap A
	        		{
						t.moveLeft( );
						//continue;
					}
	        	else if ( KEY == KEY_RIGHT ) 		// dich phai neu nhap D
	        		t.moveRight( );
	        	else if ( KEY == KEY_DOWN ) 		// roi luon neu nhap s
	        		t.fall( );
	        	else if ( KEY == KEY_UP ) 		// xoay
	        		t.rotate( );
	        	else if ( KEY == PAUSE || KEY == ESCAPE )		// tam dung pause
	        		while ( 1 ) //man hinh pause 
	        		{
	        			system( "cls" );	//xoa man hinh, chong gian lan

    					setTextColor( COLOR );
	        			gotoxy( 35, 9 );
	        			std::cout << "PAUSE";
	        			gotoxy( 30, 12 );
	        			std::cout << "   RESUME";
	        			gotoxy( 30, 14 );
	        			std::cout << "   RESTART";
	        			gotoxy( 30, 16 );
	        			std::cout << "  MAIN MENU";
	
	        			int cursor = 12; // Toa do dau tien cua con tro
						while( 1 )
						{
							printCursor(20, 50, cursor);
							
							KEY = key_press( );
							
							if( KEY == KEY_DOWN ) //Di chuyen con tro xuong
							{
								if(cursor <= 14)
									cursor += 2;
							}
							else if( KEY == KEY_UP ) //Di chuyen con tro len
							{
								if(cursor >= 14)
									cursor -= 2;
							}
				
							printCursor(20, 50, cursor);
							
							if( KEY == ENTER )
								break;
						}
						
						if(cursor == 12) //tiep tuc
						{
							printBackground( );
							gotoxy( 12, 6 );
							std::cout <<  score;
							break;
						}
						else if(cursor == 14 && confirm("RESTART") ) //choi lai ( can  xac nhan )
							return play( );
						else if(cursor == 16 && confirm("BACK TO MAIN MENU") ) //quay ve
							return restart( );
        		}	        		
	    	}
	    
			t.moveDown( );		// dich xuong
			
	   	}

	   	t.getFullRows( );	//lay diem
	   	score = score + 1 +  level * 50 * t.getScore();
	   	gotoxy( 12, 6 );
		std::cout <<  score;

	   	IDBrick = IDNextBrick; //Gan khoi cu thanh khoi moi
		IDNextBrick = randIDBrick(); //Tao khoi gach tiep theo
	}

	return score;	//lay diem 

}

void GUI::printBackground( )
{


	int i;
	setTextColor( COLOR );
	system( "cls" );

	gotoxy( 3, 2 );
	std::cout << "~~~~~~~~~~~~~~~";
	gotoxy( 3, 4 );
	std::cout << " Level: " << level;
	gotoxy( 3, 6 );
	std::cout << " Score: ";
	gotoxy( 3, 8 );
	std::cout << "~~~~~~~~~~~~~~~";

	gotoxy(58, 2);
	std::cout << "NEXT";
		
	//in vien table
	gotoxy( 25, 1 );
	for ( int j = 0; j < 22; ++j )
	{
		std::cout << (char)220;
	}
		
	for ( int i = 20 ; i >= 1; i-- )
	{
		gotoxy( 25, 22 - i );
		std::cout << (char)221;	//bien
		gotoxy( 46, 22 - i );
		std::cout << (char)222;
	}

	gotoxy( 25, 22 ); 
	for ( int j = 0; j < 22; ++j )
	{
		std::cout << (char)223;
	}


	//in bien gach tiep
	// gotoxy( 56, 4 );
	// for ( i = 0; i < 12; i++ )
	// 	std::cout << (char)220;
	// for ( i = 5 ; i < 10; i++ )
	// {
	// 	gotoxy( 56, i );
	// 	std::cout << (char)221;	//bien
	// 	gotoxy( 67, i );
	// 	std::cout << (char)222;	//bien
	// }
	// gotoxy( 56, 9 );
	// for ( i = 0; i < 12; i++ )
	// 	std::cout << (char)223;
	
}

void GUI::printCursor(int x1, int x2, int cursor)
{
	gotoxy( x1, cursor );
	std::cout << "-->";
	gotoxy( x2, cursor );
	std::cout << "<--";
	
	//Xoa con tro cu di
	gotoxy( x1, cursor+2 );
	std::cout << "   ";
	gotoxy( x2, cursor+2 );
	std::cout << "   ";

	gotoxy( x1, cursor-2 );
	std::cout << "   ";
	gotoxy( x2, cursor-2 );
	std::cout << "   ";
}

//Xoa con tro vua hien len man hinh
void GUI::delCursor(int x1, int x2, int cursor)
{
	gotoxy( x1, cursor );
	std::cout << "   ";
	gotoxy( x2, cursor );
	std::cout << "   ";
}


