#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#include <windows.h>
#include <iostream>
#include <conio.h>

enum COLOR
{
    BLACK,
    BLUE,
    GREEN,
    CYAN,
    RED,
    PURPLE,
    GRAY,
    WHITE,
    LIGHTGRAY,
    LIGHTBLUE,
    LIGHTGREEN,
    LIGHTCYAN,
    LIGHTRED,
    LIGHTPURPLE,
    LIGHTYELLOW,
    LIGHTWHITE
};

enum KEY_PRESSED //Phim dieu khien
{
	KEY_UP ,
	KEY_DOWN ,
	KEY_LEFT ,
	KEY_RIGHT ,
	ENTER ,
	ESCAPE ,
	PAUSE ,
	UNKNOWN 
};

void setTextColor(WORD color)       //doi mau chu
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
 
    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
 
    WORD wAttributes = screen_buffer_info.wAttributes;
    color &= 0x000f;
    wAttributes &= 0xfff0;
    wAttributes |= color;
 
    SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}

int restart()          //khoi dong lai chuong trinh, tra ve -1 khi thoat ctr vua goi,
{
    char ownPth[MAX_PATH]; 
    char absPth[MAX_PATH + 5] = "";	//duong dan co " "

    // Will contain exe path
    HMODULE hModule = GetModuleHandle(NULL);
    if (hModule != NULL)
    {
     // When passing NULL to GetModuleHandle, it returns handle of exe itself
        GetModuleFileName(hModule,ownPth, (sizeof(ownPth))); 
		
		strncat ( absPth, "\"", 1 );
		strncat ( absPth, ownPth, MAX_PATH );
		strncat ( absPth, "\"", 1 );
//		std::cout << absPth;
//		getch();
        system( absPth );       //khoi dong lai 
        return -1 ;
    }
    else
    {
        std::cout << "Module handle is NULL!" << std::endl << "Restart manually!!" ;
        return -1 ;
    }
}

WORD key_press()
{
	char key;
	
	key = getch( );	
	
	if ( key == -32 )
	{
		switch( getch() )
		{
			case 72:
			return KEY_UP;
				case 80:
				return KEY_DOWN;
					case 75:
					return KEY_LEFT;
						case 77:
						return KEY_RIGHT;
		}
	}

	switch( key )
	{
		case 'a': case 'A':
		return KEY_LEFT;
			case 's': case 'S':
			return KEY_DOWN;
				case 'd': case 'D':
				return KEY_RIGHT;
					case 'w': case 'W':
					return KEY_UP;
				case 'p': case 'P':
				return	PAUSE;
			case 13: case 32:
			return ENTER;
		case 27:
		return ESCAPE;
	}

	return UNKNOWN;	//ko co trong khai bao
}

void gotoxy(int x, int y)       //chuyen con tro ve vi tri cot x, hang y
{
    static HANDLE h = NULL;
    if(!h)
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = { x, y };
    SetConsoleCursorPosition(h,c);
}

bool confirm( char const action[] )     //xac nhan lua chon
{
    system( "cls" );
    char key;
    gotoxy ( 20, 10 );    

    std::cout << "COMFIRM: " << (action) << "  (Y/N)  ";

    while ( TRUE )
    {
        key = getch( );     //doc phim
        if ( key == 'Y' || key == 'y' || key == 13 )
            return TRUE;
        else if ( key == 'N' || key == 'n' || key == 27 )
            return FALSE;
    }
}
void changeCursor( int oldPos, int newPos )
{
    //Xoa con tro tuy chon o vi tri cu
    gotoxy( 28, oldPos );
    std::cout << "   ";
    gotoxy( 60, oldPos );
    std::cout << "   ";

    //Ve lai con tro tuy chon o vi tri ms
    gotoxy( 28, newPos );
    std::cout << (char) 175 << (char) 175 << (char) 175;
    gotoxy( 60, newPos );
    std::cout << (char) 174 << (char) 174 << (char) 174;


}

//tao con tro trong Menu
//inp: 
//  begin   : vi tri dau tien 
//  end     : vi tri cuoi
//  default : gia tri tra ve khi an ESC
//out: thu tu cua lựa chọn, từ trên xuống
int cursor ( int begin, int end, int defaut )
{
    WORD KEY;
    int cursor = begin;

    changeCursor( begin + 2, begin ); //In ra con tro tuy chon

    while ( 1 )
    {
            KEY = key_press( );
            if ( KEY == ESCAPE )
                return defaut;

            else if ( KEY == ENTER )
                return ( cursor - begin) / 2 + 1;    

            else if( KEY == KEY_DOWN ) //Di chuyen con tro xuong
            {
                //Thay doi toa do con tro tuy chon
                if( cursor < end )
                    changeCursor ( cursor - 2, cursor += 2 );
                else if ( cursor == end )   
                    changeCursor ( end, cursor = begin );     //ve dau            
            }
            
            else if( KEY == KEY_UP ) //Di chuyen con tro len
            {
                //Thay doi toa do con tro tuy chon
                if( cursor > begin )
                    changeCursor ( cursor + 2, cursor -= 2 );
                else if ( cursor== begin )   
                    changeCursor ( begin, cursor = end );     //ve cuoi
            }
    }
}

#endif  //__CONSOLE_H__ 

