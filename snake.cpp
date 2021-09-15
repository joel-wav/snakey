#include<iostream>
#include<vector>
#include<queue>
#include<utility>
#include<windows.h>

using namespace std;

class Arena
{
    private: 

    int length;
    queue<pair<int,int>> snakey;
    char snakerep;

    int w, h, size;
    vector<vector<char>> arena;

    public:

    Arena()
    {
        length = 5;
        snakerep = 'O';
        for(int i = 0 ; i < length ; i++)
            snakey.push({1, i+1});

        size = 25;
        h = size, w = 2*size;
        arena.resize(h, vector<char>(w, ' '));
 
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
    }

    void setSnake()
    {
        queue<pair<int,int>> temp_snakey = snakey;
        
        while(!temp_snakey.empty())
        {
            pair<int, int> xy = temp_snakey.front();
            temp_snakey.pop();

            int x = xy.first, y = xy.second;

            arena[x][y] = snakerep;
        }
    }

    void moveSnake()
    {
        //calculate the new location of the head or whatever according to the direction given within the brackets
        pair<int,int> prevHead = snakey.back();
        pair<int,int> newHead = {prevHead.first, prevHead.second+1};

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
    int i = 0;
    Arena A;

    A.setArena();
    A.setSnake();
    A.printAll();

    while(i<10)
    {
        A.setArena();
        A.moveSnake();
        A.setSnake();
        A.printAll();
        i++;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0, 0});
    }
    return 0;
}