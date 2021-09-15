#include<iostream>
#include<conio.h>
#include<vector>
#include<queue>
#include<utility>
#include<windows.h>

using namespace std;

bool play = true;

class Arena
{
    private: 

    int length, w, h, size, fx, fy;
    char snakerep, fruitrep;
    queue<pair<int,int>> snakey;
    vector<vector<char>> arena;

    public:

    Arena()
    {
        //snake stuff
        length = 10;
        snakerep = 'O';
        for(int i = 0 ; i < length ; i++)
            snakey.push({1, i+1});
        
        //arena stuff
        size = 25;
        h = size, w = 2*size;
        arena.resize(h, vector<char>(w, ' '));
        
        //fruit stuff
        fruitrep = 'F';
        fx = 1 + (rand() % h);
        fy = 1 + (rand() % w);
        arena[fx][fy] = fruitrep;
    }

    void setFruit()
    {
        fx = 1 + (rand() % h);
        fy = 1 + (rand() % w);

        arena[fx][fy] = fruitrep;
    }
    
    void setArena()
    {
        
        for(int i = 0 ; i < w ; i++)
        {
            arena[0][i] = '*';
            arena[h-1][i] = '*';
        }

        for(int i = 1 ; i < h-1 ; i++)
        {
            arena[i][0] = '*';
            arena[i][w-1] = '*';
        }

        for(int i = 1 ; i < h-1; i++)
        {
            for(int j = 1; j < w-1 ; j++)
            {
                arena[i][j] = ' ';
            }
        }

        arena[fx][fy] = fruitrep;
    }

    void setSnake()
    {
        queue<pair<int,int>> temp_snakey = snakey;
        
        while(!temp_snakey.empty())
        {

            pair<int, int> xy = temp_snakey.front();
            temp_snakey.pop();

            int x = xy.first, y = xy.second;

            //condition for hitting any of the boundaries
            if (x <= 0 || y <= 0 || x >= size-1 || y >= 2*size-1)
                play = false;

            //condition for hitting itself
            if (arena[x][y] == snakerep)
                play = false;

            //condition for if a fruit is eaten
            if (arena[x][y] == fruitrep)
            {
                setFruit();
            }

            arena[x][y] = snakerep;
        }
    }

    void moveSnake(char dir)
    {
        //calculate the new location of the head or whatever according to the direction given within the brackets
        pair<int,int> prevHead = snakey.back(), newHead;

        if (dir == 'R')
            newHead = {prevHead.first, prevHead.second+1};
        else if (dir == 'L')
            newHead = {prevHead.first, prevHead.second-1};
        else if (dir == 'U')
            newHead = {prevHead.first-1, prevHead.second}; 
        else if (dir == 'D')
            newHead = {prevHead.first+1, prevHead.second};

        //pop the tail from the queue and add the new head
        snakey.pop();
        snakey.push(newHead);
    }

    void printAll()
    {
        //this function prints the board and the snake, basically everything in the matrix
        for(int i = 0 ; i < h ; i++)
        {
            for(int j = 0 ; j < w ; j++)
            {
                cout<<arena[i][j];
            }
            cout<<endl;
        }
    }
};

int main()
{
    Arena A;

    char dir = 'R';

    A.setArena();
    A.setSnake();
    A.printAll();

    while(play)
    {
        if(_kbhit())
        {
            char ch = _getch();
            if (dir == 'R' || dir == 'L')
            {
                if (ch == 'w')
                    dir = 'U'; 
                else if (ch == 's')
                    dir = 'D';
                else if (ch == 'x')
                    play = false;
            }   
            else if (dir == 'U' || dir == 'D')
            {
                if (ch == 'd')
                    dir = 'R'; 
                else if (ch == 'a')
                    dir = 'L';
                else if (ch == 'x')
                    play = false;
            }
        }
        
        A.setArena();
        A.moveSnake(dir);
        A.setSnake();
        A.printAll();

        //better than using system("cls"), because it moves cursor to beginning of console
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0, 0});
    }
    return 0;
}