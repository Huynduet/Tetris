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
		gotoxy( 20, 17); std::cout << "                     HIGH SCORE                    ";
		gotoxy( 20, 19); std::cout << "                       INFO                        ";
		gotoxy( 20, 21); std::cout << "                       QUIT                        ";
		
		while( 1 )
		{
			printCursor(28, 60, cursor);
			
			KEY = key_press( );
			
			if( KEY == KEY_DOWN ) //Di chuyen con tro xuong
			{
				if(cursor <= 19)
					cursor += 2;
			}
			else if( KEY == KEY_UP ) //Di chuyen con tro len
			{
				if(cursor >= 15)
					cursor -= 2;
			}

			printCursor(28, 60, cursor);
			
			if( KEY == ENTER || KEY == ESCAPE )
				break;
		}
		
		if(cursor == 21 || KEY == ESCAPE )
			quit( );
		else if(cursor == 13)
			start( );
		else if(cursor == 15)
			settings( );
		else if(cursor == 17)
			printHighScore( );
		else if(cursor == 19)
			info( );
		
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
	gotoxy( 20, 12); std::cout << "                   YOUR SCORE : " << score << "          ";
	gotoxy( 20, 13); std::cout << "                                                   ";
	
	//luu lai diem cao
	setHighScore( score );
	
	Sleep(1500);
	
	getch();
}

void GUI::settings( )
{
	cursor = 13;

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
		{
			delCursor ( 28, 60, cursor);
			settingsColor( );
		}
		else if(cursor == 15)
			settingsLevel( );
		else if(cursor == 17)
		{
			cursor = 13;
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
	for(i = 0; i < 10; i++)
	{
		highScore >> h_score[i];
	}
	highScore.close();

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

	//In ra thong bao thang 
	if(i == -1)
	{
		gotoxy( 20, 14 );
		std::cout << "CONGRATULATIONS. YOU HAVE ARCHIEVED THE HIGHEST SCORE !!!";
	}
	else 
	{
		gotoxy ( 20, 14 );
		std::cout << "         Well done!!! You are now rank " << i+2 ;
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
	
	highScore.open(fileName);
	for(i = 0; i < 10; i++)
	{
		highScore >> score[i];
	}
	highScore.close();

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
			gotoxy( 36, 13 + 2*i ); 
			std::cout << i+1 << ".  " << score[i];
		}
		else if(i < 5)
		{
			setTextColor( COLOR );
			gotoxy( 36, 13 + 2*i ); 
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
	double timeDelay = 1000 - level * 100 ;	//thoi gian de roi
	double tempTimeDelay = timeDelay;
	int IDBrick, IDNextBrick; //So thu tu cua gach
	score = 0;
	system( "cls" );
	
	//Tao 2 khoi gach dau tien
	IDBrick = randIDBrick(); 
	IDNextBrick = randIDBrick();
	printBackground( );
	gotoxy( 12, 4 );
	std::cout << level;
	gotoxy( 12, 6 );
	std::cout <<  score;

	do
	{	
		t.create( IDBrick );	//tao khoi moi

		while ( t.checkEmpty( -1, 0 ) )
		{
			//In ra vien gach tiep theo

			setTextColor( IDNextBrick + 7 );
			t.printNextBrick( IDNextBrick );
		
			Sleep( ( tempTimeDelay ) );
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
	        		tempTimeDelay /= 10;
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
							
							if( KEY == ENTER || KEY == ESCAPE )
								break;
						}
						
						if(cursor == 12 || KEY == ESCAPE ) //tiep tuc
						{
							printBackground( );
							gotoxy( 12, 4 );
							std::cout << level;
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
	   	t.setBrickNum( IDBrick + 7 );
	   	t.getFullRows( );	//lay diem

	   	score = score + level +  level * level * t.getScore() * t.getScore();

	   	setTextColor ( COLOR ); 
	   	gotoxy( 12, 4 );
		std::cout << level;
	   	gotoxy( 12, 6 );
		std::cout <<  score;

	   	IDBrick = IDNextBrick; //Gan khoi cu thanh khoi moi
		IDNextBrick = randIDBrick(); //Tao khoi gach tiep theo

		tempTimeDelay = timeDelay *= 0.99;
		level = ( 1000 - timeDelay ) / 100;
	} while ( t.checkGameOver() == 0 );

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
	std::cout << " Level: ";
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
}

void GUI::printCursor(int x1, int x2, int cursor)
{
	gotoxy( x1, cursor );
	std::cout << (char) 175 << (char) 175 << (char) 175;
	gotoxy( x2, cursor );
	std::cout << (char) 174 << (char) 174 << (char) 174;
	
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
