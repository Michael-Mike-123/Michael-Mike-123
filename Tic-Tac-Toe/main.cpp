#include <iostream>
#include <windows.h>
#include <thread>

using namespace std;

//Clears console
void clear_screen(char fill = ' ') {
    COORD tl = {0,0};
    CONSOLE_SCREEN_BUFFER_INFO s;
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(console, &s);
    DWORD written, cells = s.dwSize.X * s.dwSize.Y;
    FillConsoleOutputCharacter(console, fill, cells, tl, &written);
    FillConsoleOutputAttribute(console, s.wAttributes, cells, tl, &written);
    SetConsoleCursorPosition(console, tl);
}

int main()
{
    bool isWin = false;
    char mark[2] = {'O', 'X'};
    char side;

    //The grid by default
    char grid[9] = {'0', '1', '2', '3', '4', '5', '6', '7', '8'};

    //Needed to check, if a place is not used by a mark
    int usedGrid[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

    int putMark;
    int turns = 0;

    while(turns < 9 && isWin == false){

        //Decides which turn is now
        if (turns % 2){
            side = mark[0];
        }else{
            side = mark[1];
        }

        cout << " " << grid[0] << " | " << grid[1] << " | " << grid[2] << "  " << endl;
        cout << "___|___|___" << endl;
        cout << " " << grid[3] << " | " << grid[4] << " | " << grid[5] << "  " << endl;
        cout << "___|___|___" << endl;
        cout << " " << grid[6] << " | " << grid[7] << " | " << grid[8] << "  " << endl;
        cout << "   |   |   " << endl;
        cout << endl;
        cout << side << " turn!" << endl;
        cout << "Put a mark (0-8): ";
        cin >> putMark;

        //Prevents user from typing not int
        while (cin.fail())
        {
            cin.clear(); // clear input buffer to restore cin to a usable state
            cin.ignore(INT_MAX, '\n'); // ignore last input
            cout << "You can only enter numbers!" << endl;
            cout << "Enter a number: ";
            cin >> putMark;
        }
        turns++;


        //Checks if the place is not used by mark
        if(usedGrid[putMark] == 1)
        {
            cout << "This place is used! Put somewhere else" << endl;

            //1 second timer
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            turns--;
        } else{
            grid[putMark] = side;
            usedGrid[putMark] = 1;
        }

        //Checks if there's a winner
        if(grid[0] == grid[1] && grid[1] == grid[2] || grid[0] == grid[3] && grid[3] == grid[6] || grid[0] == grid[4] && grid[4] == grid[8] || grid[1] == grid[4] && grid[4] == grid[7] || grid[2] == grid[5] && grid[5] == grid[8] || grid[2] == grid[4] && grid[4] == grid[6] || grid[3] == grid[4] && grid[4] == grid[5] || grid[6] == grid[7] && grid[7] == grid[8])
        {
            isWin = true;
        }
        clear_screen(); //clears console to avoid a mess
    }

    //Control check, if wins on last move (if not - draw)
    if(grid[0] == grid[1] && grid[1] == grid[2] || grid[0] == grid[3] && grid[3] == grid[6] || grid[0] == grid[4] && grid[4] == grid[8] || grid[1] == grid[4] && grid[4] == grid[7] || grid[2] == grid[5] && grid[5] == grid[8] || grid[2] == grid[4] && grid[4] == grid[6] || grid[3] == grid[4] && grid[4] == grid[5] || grid[6] == grid[7] && grid[7] == grid[8])
    {
        turns--;
        cout << side << " wins!" << endl;
    } else{
        cout << "Draw!" << endl;
    }

    return 0;
}

//CREDITS
//Timer code by Polar: https://stackoverflow.com/questions/14650885/how-to-create-timer-events-using-c-11
//Char input in int detector by Ryan Hallberg: https://stackoverflow.com/questions/11523569/how-can-i-avoid-char-input-for-an-int-variable
//Clear console function by Jerry Coffin: https://stackoverflow.com/questions/5866529/how-do-we-clear-the-console-in-assembly/5866648#5866648
