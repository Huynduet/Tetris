#include "table.h"
#include "table.cpp"
#include "console.h"
#include "GUI.h"
#include <sstream>

void GUI::mainMenu( )
{
	
	level = 1; //Level ban dau
	exit = FALSE;
	COLOR = LIGHTGREEN; //Mau mac dinh cua game

	while ( !exit )		 		//chay den khi co lenh thoat
	{
		setTextColor( COLOR );
		printHeader( );	

		cursorY = 13; //Toa do dau tien cua con tro
		gotoxy( 20, 10); std::cout << "                     MAIN MENU                     ";
		gotoxy( 20, 13); std::cout << "                       START                       ";
		gotoxy( 20, 15); std::cout << "                      SETTINGS                     ";
		gotoxy( 20, 17); std::cout << "                     HIGH SCORE                    ";
		gotoxy( 20, 19); std::cout << "                       INFO                        ";
		gotoxy( 20, 21); std::cout << "                       QUIT                        ";
		
		while( 1 )
		{
			printCursor(28, 60, cursorY); //In ra con tro tuy chon
			
			KEY = key_press( );
			
			if( KEY == KEY_DOWN ) //Di chuyen con tro xuong
			{
				//Thay doi toa do con tro tuy chon
				if(cursorY <= 19)
					cursorY += 2; 
				else if(cursorY == 21)
				{
					delCursor(28, 60, cursorY);
					cursorY = 13;
				}
			}
			else if( KEY == KEY_UP ) //Di chuyen con tro len
			{
				//Thay doi toa do con tro tuy chon
				if(cursorY >= 15)
					cursorY -= 2;
				else if(cursorY == 13)
					{
					delCursor(28, 60, cursorY);
					cursorY = 21;
				}
			}

			printCursor(28, 60, cursorY); //In ra con tro tuy chon
			
			if( KEY == ENTER || KEY == ESCAPE )
				break;
		}
		
		//Thuc hien lenh tuy theo toa do con tro tuy chon
		if(cursorY == 21 || KEY == ESCAPE )
			quit( );
		else if ( cursorY == 13 )
			start( );
		else if ( cursorY == 15 ) 
			settings( );
		else if ( cursorY == 17 )
			printHighScore( );
		else if ( cursorY == 19 )
			info( );
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
	cursorY = 13;

	while ( TRUE )
	{
		printHeader( ); 

		gotoxy( 20, 10); std::cout << "                      SETTINGS                     ";
		gotoxy( 20, 13); std::cout << "                       COLOR                       ";
		gotoxy( 20, 15); std::cout << "                       LEVEL                       ";
		gotoxy( 20, 17); std::cout << "                       BACK                        ";
		
		while( TRUE )
		{
			printCursor(28, 60, cursorY); //In ra con tro tuy chon
			
			KEY = key_press( );
			
			if( KEY == KEY_DOWN ) //Di chuyen con tro xuong
			{
				//Thay doi toa do con tro tuy chon
				if(cursorY <= 15)
					cursorY += 2;
				else if(cursorY == 17)
				{
					delCursor(28, 60, cursorY);
					cursorY = 13;
				}
			}
			else if( KEY == KEY_UP ) //Di chuyen con tro len
			{
				//Thay doi toa do con tro tuy chon
				if(cursorY >= 15)
					cursorY -= 2;
				else if(cursorY == 13)
				{
					delCursor(28, 60, cursorY);
					cursorY = 17;
				}
			}

			printCursor(28, 60, cursorY);
			
			if( KEY == ENTER )
				break;
		}
		
		//Thuc hien lenh tuy theo toa do con tro tuy chon
		if(cursorY == 13)
			settingsColor( );
		else if(cursorY == 15)
			settingsLevel( );
		else if(cursorY == 17)
		{
			cursorY = 13;
			return;
		}
	}
}

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

void GUI::setHighScore(int score)
{
	char fileName[] = "HighScore.txt"; //Ten file chua high score
	int i, h_score[10]; //10 diem cao nhat

	//Kiem tra xem co dat high score khong???
	std::ifstream highScore;
	highScore.open(fileName);

	//Nhap 10 diem cao nhat tu file
	for(i = 0; i < 10; i++)
	{
		highScore >> h_score[i];
	}
	highScore.close();

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

	//Ghi ra file neu dat high score
	std::ofstream outputHighScore;
	outputHighScore.open(fileName);
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
	for(i = 0; i < 10; i++)
	{
		outputHighScore << h_score[i] << std::endl;
	}
	outputHighScore.close();
}

void GUI::printHighScore( )
{
	char fileName[] = "HighScore.txt"; //Ten file chua high score
	int i, score[10]; //10 diem cao nhat
	std::ifstream highScore;
	
	//Lay diem da luu tu file highScore
	highScore.open(fileName);
	for(i = 0; i < 10; i++)
	{
		highScore >> score[i];
	}
	highScore.close();

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

void GUI::info( )		//In ra thong tin game
{
	printHeader( );

	std::ifstream readme("README.txt");
	std::string line, info;

	while (readme)
	{
		getline(readme, line);
		info += "\t\t\t" + line + "\n";
	}

	gotoxy(5, 10);
	std::cout << info;
	getch();
}

void GUI::quit( )		//thoat game
{
	if ( confirm( "EXIT" ) )
		exit = TRUE;		//thoat game neu confirm = true
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

int randIDBrick() //Tao so ngau nhien la thu tu cua cac loai gach tu 0 - 6
{	
	return rand() % 7;
}

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
	IDBrick = randIDBrick(); 
	IDNextBrick = randIDBrick();
	
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
	        			gotoxy( 30, 9 );
	        			std::cout << "_____PAUSE_____";
	        			gotoxy( 30, 12 );
	        			std::cout << "   RESUME";
	        			gotoxy( 30, 14 );
	        			std::cout << "   RESTART";
	        			gotoxy( 30, 16 );
	        			std::cout << "  MAIN MENU";
	
	        			cursorY = 12; // Toa do dau tien cua con tro
						while( 1 )
						{
							printCursor(20, 50, cursorY);
							
							KEY = key_press( );
							
							if( KEY == KEY_DOWN ) //Di chuyen con tro xuong
							{
								//Thay doi toa do con tro tuy chon
								if(cursorY <= 14)
									cursorY += 2;
								else if(cursorY == 16)
								{
									delCursor(20, 50, cursorY);
									cursorY = 12;
								}
							}
							else if( KEY == KEY_UP ) //Di chuyen con tro len
							{
								//Thay doi toa do con tro tuy chon
								if(cursorY >= 14)
									cursorY -= 2;
								else if(cursorY == 12)
								{
									delCursor(20, 50, cursorY);
									cursorY = 16;
								}
							}
				
							printCursor(20, 50, cursorY);
							
							if( KEY == ENTER || KEY == ESCAPE )
								break;
						}
						
						//Thuc hien lenh tuy theo toa do con tro tuy chon
						if(cursorY == 12 || KEY == ESCAPE ) //tiep tuc
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
						else if(cursorY == 14 && confirm("RESTART") ) //choi lai ( can  xac nhan )
							return play( );
						else if(cursorY == 16 && confirm("BACK TO MAIN MENU") ) //quay ve
							return -1;
							//return restart( );
        		}	        		
	    	}
	    
			t.moveDown( );		// dich xuong
			
	   	}
	   	t.setBrickNum( IDBrick + 7 );
	   	t.getFullRows( );	//Lay diem

	   	//Tinh diem hien tai
	   	score = score + level +  level * level * t.getScore() * t.getScore();
	   	lines += t.getScore();

	   	//In ra level, lines va score hien tai
	   	setTextColor ( COLOR ); 
	   	gotoxy( 12, 4 );
		std::cout << level;
	   	gotoxy( 12, 6 );
		std::cout << score;
		gotoxy( 12, 8 );
		std::cout << lines;

	   	IDBrick = IDNextBrick; //Gan khoi cu thanh khoi moi
		IDNextBrick = randIDBrick(); //Tao khoi gach tiep theo

		tempTimeDelay = timeDelay *= 0.99;
		level = ( 1000 - timeDelay ) / 100;
	} while ( t.checkGameOver() == 0 );

	cursorY = 13; //Dat lai ve toa do ban dau
	return score;	//lay diem 
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

void GUI::printCursor(int x1, int x2, int cursorY)
{
	gotoxy( x1, cursorY );
	std::cout << (char) 175 << (char) 175 << (char) 175;
	gotoxy( x2, cursorY );
	std::cout << (char) 174 << (char) 174 << (char) 174;

	//Xoa con tro tuy chon o vi tri cu
	gotoxy( x1, cursorY+2 );
	std::cout << "   ";
	gotoxy( x2, cursorY+2 );
	std::cout << "   ";

	gotoxy( x1, cursorY-2 );
	std::cout << "   ";
	gotoxy( x2, cursorY-2 );
	std::cout << "   ";
}

void GUI::delCursor(int x1, int x2, int cursorY)
{
	gotoxy( x1, cursorY );
	std::cout << "   ";
	gotoxy( x2, cursorY );
	std::cout << "   ";
}
