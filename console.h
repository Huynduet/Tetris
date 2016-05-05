#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#include <windows.h>
#include <iostream>

enum
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

    // Will contain exe path
    HMODULE hModule = GetModuleHandle(NULL);
    if (hModule != NULL)
    {
     // When passing NULL to GetModuleHandle, it returns handle of exe itself
        GetModuleFileName(hModule,ownPth, (sizeof(ownPth))); 

        system( ownPth );       //khoi dong lai 
        return -1 ;
    }
    else
    {
        std::cout << "Module handle is NULL!" << std::endl << "Restart manually!!" ;
        return -1 ;
    }
}

void gotoxy(int x, int y)       //chuyen con tro ve vi tri x, y
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
    key = getch( );     //doc phim
    if ( key == 'Y' || key == 'y' || key == 13 )
        return TRUE;
    else if ( key == 'N' || key == 'n' )
        return FALSE;
    else 
        std::cout << "Unknown key...";
    Sleep ( 500 );
    return FALSE;
}

#endif  //__CONSOLE_H__ 
