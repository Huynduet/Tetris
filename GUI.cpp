#include <sstream>

#include "table.h"
#include "table.cpp"
#include "console.h"
#include "GUI.h"

// ================================ Main Menu ================================
void GUI::mainMenu( )
{
	
	level = 1; //Level ban dau
	exit = FALSE;
	COLOR = LIGHTGREEN; //Mau mac dinh cua game

	while ( !exit )		 		//chay den khi co lenh thoat
	{
		setTextColor( COLOR );
		printHeader( );	

		gotoxy( 20, 10); std::cout << "                     MAIN MENU                     ";
		gotoxy( 20, 13); std::cout << "                       START                       ";
		gotoxy( 20, 15); std::cout << "                      SETTINGS                     ";
		gotoxy( 20, 17); std::cout << "                     HIGH SCORE                    ";
		gotoxy( 20, 19); std::cout << "                       INFO                        ";
		gotoxy( 20, 21); std::cout << "                       QUIT                        ";

			//Thuc hien lenh tuy theo toa do con tro tuy chon
			switch ( cursor( 13, 21 , 5 ) )	
			{
				case 1:
				start( );
				break;
					case 2:
					settings( );
					break;
						case 3:
						printHighScore( );
						break;
					case 4:
					info( );
					break;
				case 5:
				quit( );
			}
	}
}

void GUI::start( )
{
	std::cout <<"Don't delete this line";

	score = play( );

	if ( score > -1 )
	{
		setTextColor( COLOR );
		gotoxy( 20, 9 ); std::cout << "                                                   ";
		gotoxy( 20, 10); std::cout << "_______________________GAME OVER___________________";
		gotoxy( 20, 11); std::cout << "                                                   ";
		gotoxy( 20, 12); std::cout << "                   YOUR SCORE : " << score << "          ";
		gotoxy( 20, 13); std::cout << "                                                   ";
		
		//luu lai diem cao
		setHighScore( score );	
	
		Sleep(1500);
		
		getch();
	}
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
			
		//Thuc hien lenh tuy theo toa do con tro tuy chon
		switch ( cursor( 13, 17 , 3) )
		{	
			case 1:
			settingsColor( );
			break;
				case 2:
				settingsLevel( );
				break;
			case 3:
			return;
		}
	}
}
void GUI::info( )		//In ra thong tin game
{
	printHeader( );

	std::stringstream sstringREADME;

	sstringREADME << "\t\t\t----------------------------------------------- \n\n";
    sstringREADME << "\t\t\tHOW TO PLAY \n\n";
    sstringREADME << "\t\t\t -  USE  \n\n";
    sstringREADME << "\t\t\t     W      OR    ^   TO PLAY \n";
    sstringREADME << "\t\t\t   A S D        < v > \n\n";
    sstringREADME << "\t\t\t -  PAUSE : ESC  |  P \n\n";
    sstringREADME << "\t\t\t----------------------------------------------- \n\n";
    sstringREADME << "\t\t\tDeveloped by:  \n\n";
    sstringREADME << "\t\t\t     Nguyen Duc Huy \n";
    sstringREADME << "\t\t\t     Nguyen Viet Hoang \n";

	std::fstream fileREADME;
    fileREADME.open("README.txt", std::ios::in);
    SetFileAttributes("README.txt", FILE_ATTRIBUTE_READONLY);

    if ( fileREADME.fail() )
    {
        fileREADME.open("README.txt", std::ios::out); // tao file moi  
        fileREADME << sstringREADME.str();
    }

    fileREADME.close();

    gotoxy( 0, 10 );
	std::cout << sstringREADME.str();

	getch();
}

void GUI::quit( )		//thoat game
{
	if ( confirm( "EXIT" ) )
		exit = TRUE;		//thoat game neu confirm = true
	else 
		exit = FALSE;
}
// ================================ End Main Menu ================================


// ================================ START Menu ================================
int GUI::play( )
{
	Table t;	// choi tren Table nay
	srand(time(NULL)); //Sinh so ngau nhien

	double timeDelay = 1000 - level * 100 ;	//thoi gian de roi
	double tempTimeDelay = timeDelay;
	int IDBrick, IDNextBrick; //So thu tu cua gach
	score = 0; //Diem ban dau
	lines = 0; //So hang da an duoc ban dau
	
	system( "cls" );
	
	//Tao 2 khoi gach dau tien
	IDBrick = createIDBrick(); 
	IDNextBrick = createIDBrick();
	
	//In ra background, level, line va score ban dau
	printBackground( );
	gotoxy( 12, 4 );
	std::cout << level;
	gotoxy( 12, 6 );
	std::cout <<  score;
	gotoxy( 12, 8 );
	std::cout << lines;

	do
	{	
		t.create( IDBrick );	//tao khoi moi

		while ( t.checkEmpty( -1, 0 ) )
		{
			//In ra vien gach tiep theo va mau cua no
			setTextColor( IDNextBrick + 7 );
			t.printNextBrick( IDNextBrick );
		
			Sleep( ( tempTimeDelay ) );
			int count = 5; //So lan xoay toi da trong timeDelay

			while (--count  && kbhit() ) 				//doi phim an	
	        {
	        	KEY = key_press( );
	        	if ( KEY == KEY_LEFT ) 			// dich trai neu nhap phim trai
	        		t.moveLeft( );
	        	else if ( KEY == KEY_RIGHT ) 		// dich phai neu nhap phim phai
	        		t.moveRight( );
	        	else if ( KEY == KEY_DOWN ) 		// roi luon neu nhap phim xuong
	        		tempTimeDelay /= 10;
	        	else if ( KEY == KEY_UP ) 		// xoay neu nhap phim len
	        		t.rotate( );
	        	else if ( KEY == PAUSE || KEY == ESCAPE )		// tam dung pause
	        		while ( 1 ) //man hinh pause 
	        		{
	        			system( "cls" );	//xoa man hinh, chong gian lan

	        			//In ra tuy chon o man hinh pause
    					setTextColor( COLOR );
	        			gotoxy( 20, 9 );
	        			std::cout << "                   _____PAUSE_____                 ";
	        			gotoxy( 20, 12 );
	        			std::cout << "                       RESUME                      ";
	        			gotoxy( 20, 14 );
	        			std::cout << "                       RESTART                     ";
	        			gotoxy( 20, 16 );
	        			std::cout << "                      MAIN MENU                    ";
	
	        			int chosenMenu = cursor( 12, 16, 1 );
					
						//Thuc hien lenh tuy theo toa do con tro tuy chon
						if(chosenMenu == 1 ) //tiep tuc
						{
							//In ra nen game, level, lines va score hien tai va tiep tuc game
							printBackground( );
							gotoxy( 12, 4 );
							std::cout << level;
							gotoxy( 12, 6 );
							std::cout << score;
							gotoxy( 12, 8 );
							std::cout << lines;
							break;
						}
						else if(chosenMenu == 2 && confirm("RESTART") ) //choi lai ( can  xac nhan )
							return play( );
						else if(chosenMenu == 3 && confirm("BACK TO MAIN MENU") ) //quay ve
							return -1;
							//return restart( );
        		}	        		
	    	}
	    
			t.moveDown( );		// dich xuong
			
	   	}
	   	t.setBrickNum( IDBrick + 7 );
	   	t.getFullRows( );	//Lay diem

	   	//Tinh diem hien tai
	   	score = score + level +  level * level * t.getDeletedLines() * t.getDeletedLines();
	   	lines += t.getDeletedLines();

	   	//In ra level, lines va score hien tai
	   	setTextColor ( COLOR ); 
	   	gotoxy( 12, 4 );
		std::cout << level;
	   	gotoxy( 12, 6 );
		std::cout << score;
		gotoxy( 12, 8 );
		std::cout << lines;

	   	IDBrick = IDNextBrick; //Gan khoi cu thanh khoi moi
		IDNextBrick = createIDBrick(); //Tao khoi gach tiep theo

		tempTimeDelay = timeDelay *= 0.99;
		level = ( 1000 - timeDelay ) / 100;
	} while ( t.checkGameOver() == 0 );

	return score;	//lay diem 
}

// ================================ SETTINGS Menu ================================

void GUI::settingsColor( )
{
	char key;
	gotoxy( 24, 15);	std::cout << "NOTE: If you don't see any color of 8 colors";
	gotoxy( 24, 16);	std::cout << "     Perhaps it's your background color     ";
	gotoxy( 24, 17);	std::cout << "                                            ";

	gotoxy( 28, 18); 
	setTextColor(LIGHTGRAY);	std::cout << "1.GRAY    ";
	setTextColor(LIGHTBLUE);	std::cout << "2.BLUE    ";
	setTextColor(LIGHTGREEN);	std::cout << "3.GREEN   ";
	setTextColor(LIGHTCYAN);	std::cout << "4.CYAN    ";

	gotoxy( 28, 20); 
	setTextColor(LIGHTRED);		std::cout << "5.RED     ";
	setTextColor(LIGHTPURPLE);	std::cout << "6.PURPLE  ";
	setTextColor(LIGHTYELLOW);	std::cout << "7.YELLOW  ";
	setTextColor(LIGHTWHITE);	std::cout << "8.WHITE   ";

	while ( 1 )
	{
		key = getch( );

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

	//tao level cua game
	if ( key == '1' ) level = 1;
	else if ( key == '2' ) level = 4;
	else if ( key == '3' ) level = 7;

}

// ================================ Ham ho tro ================================

void GUI::setHighScore(int score)
{
	char fileName[] = "HighScore.txt"; //Ten file chua high score
	int i, h_score[10]; //10 diem cao nhat

	std::fstream highScore;
	highScore.open(fileName, std::ios::in | std::ios::out);

	if(!highScore.is_open()) //Tao file high score neu chua co
	{
		for(i = 0; i < 10; i++)
		{
			h_score[i] = 0;
		}
	}
	else //Nhap diem neu da co file high score
	{
		for(i = 0; i < 10; i++)
		{
			highScore >> h_score[i];
		}
	}

	//Tra ve neu khong dat high score
	if(score < h_score[9])
	{
		gotoxy( 24, 14 );
		std::cout << "     You can't make it to the Hall of Fame :(      ";
		gotoxy( 24, 15 );
		std::cout << "             Do better next time !                 ";
		gotoxy( 24, 16 );
		std::cout << "                                                   ";
		return;
	}

	//Them diem hien tai neu dat high score
	for(i = 8; i >= 0; i--)
	{
		if(score > h_score[i])
			h_score[i+1] = h_score[i];
		else 
			break;
	}
	h_score[i+1] = score;

	//In ra thong bao thang va vi tri tren bang high score 
	if(i == -1)
	{
		gotoxy( 20, 14 );
		std::cout << "CONGRATULATIONS. YOU HAVE ARCHIEVED THE HIGHEST SCORE !!!";
	}
	else 
	{
		gotoxy ( 20, 14 );
		std::cout << "         Well done!!! You are now rank " << i+2 << "         " ;
	}
	gotoxy( 24, 15 );
	std::cout << "                                                   ";

	//Ghi ra file sau khi da them high score
	highScore.open(fileName, std::ios::out);
	highScore.seekp(0, std::ios::beg);
	for(i = 0; i < 10; i++)
	{
		highScore << h_score[i] << std::endl;
	}
	highScore.close();
}

void GUI::printHighScore( )
{
	char fileName[] = "HighScore.txt"; //Ten file chua high score
	int i, score[10]; //10 diem cao nhat
	std::fstream highScore;
	highScore.open(fileName, std::ios::in);
	
	//Lay diem da luu tu file highScore
	if(highScore.is_open()) //Luu diem neu da co file high score
	{
		for(i = 0; i < 10; i++)
		{
			highScore >> score[i];
		}
		highScore.close();	
	}
	else 
	{
		//Tao file high score neu chua co
		highScore.open(fileName, std::ios::out);

		for(i = 0; i < 10; i++)
		{
			score[i] = 0;
			highScore << score[i] << std::endl;
		}
		highScore.close();
	}

	//In ra 10 diem cao nhat
	printHeader( );
	gotoxy( 20, 10 ); std::cout << "                     HIGH SCORE                    ";
	for(i = 0; i < 10; i++)
	{
		if(i < 3)
		{
			if(i == 0)
				setTextColor( LIGHTYELLOW );
			if(i == 1)
				setTextColor( LIGHTWHITE );
			if(i == 2)
				setTextColor( GRAY );
			gotoxy( 35, 13 + 2*i ); 
			std::cout << i+1 << ".  " << score[i];
		}
		else if(i < 5)
		{
			setTextColor( LIGHTGRAY );
			gotoxy( 35, 13 + 2*i ); 
			std::cout << i+1 << ".  " << score[i];
		}
		else if(i < 9)
		{
			gotoxy( 50, 13 + 2*(i-5) ); 
			std::cout << i+1 << ".  " << score[i];
		}
		else 
		{
			gotoxy( 50, 13 + 2*(i-5) ); 
			std::cout << i+1 << ". " << score[i];
		}
	}

	getch();

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

void GUI::printBackground( )
{
	int i;
	setTextColor( COLOR );
	system( "cls" );

	gotoxy( 3, 2 );
	for ( int j = 0; j < 16; ++j )
		std::cout << (char)205;
	gotoxy( 3, 4 );
	std::cout << " Level : ";
	gotoxy( 3, 6 );
	std::cout << " Score : ";
	gotoxy( 3, 8 );
	std::cout << " Lines : ";
	gotoxy( 3, 10 );
	for ( int j = 0; j < 16; ++j )
		std::cout << (char)205;

	gotoxy(58, 2);
	std::cout << "NEXT";
		
	//in vien table
	gotoxy( 25, 1 );
	for ( int j = 0; j < 22; ++j )
		std::cout << (char)220;
		
	for ( int i = 20 ; i >= 1; i-- )
	{
		gotoxy( 25, 22 - i );
		std::cout << (char)221;	
		gotoxy( 46, 22 - i );
		std::cout << (char)222;
	}

	gotoxy( 25, 22 ); 
	for ( int j = 0; j < 22; ++j )
		std::cout << (char)223;	
}

