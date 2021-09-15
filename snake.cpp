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

    int length, w, h, size;
    char snakerep;
    queue<pair<int,int>> snakey;
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
            switch (_getch()) 
            {
                case 'a': dir = 'L'; break;
                case 'd': dir = 'R'; break;
                case 'w': dir = 'U'; break;
                case 's': dir = 'D' ; break;
                case 'x': play = false; break;
            }
        }
        
        A.setArena();
        A.moveSnake(dir);
        A.setSnake();
        A.printAll();

        //to stop the flickering of the screen
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0, 0});
    }
    return 0;
}






/*


#include<iostream>
#include<conio.h>

using namespace std;

bool gameover;

const int width = 20;

const int height = 17;

int x, y, fruitX, fruitY, score;

int tailX[100], tailY[100]; //snake coordinates

int nTail;

enum eDirecton {STOP = 0, LEFT,RIGHT, UP, DOWN}; // Controls

eDirecton dir;

void Setup() {
gameover = false;

dir = STOP;

x = width / 2;

y = height / 2;

fruitX = rand() % width; //display fruit in a random place

fruitY = rand() % height; score = 0;

}

void Draw() {
system("cls");

for(int i = 0; i < width+2; i++)

cout << "#";

cout << endl ;

for (int i = 0; i < height ; i++) {

for (int j = 0; j < width; j++) {

if (j == 0)

cout << "#"; //walls

if (i == y && j == x)

cout << "*"; // snake tale

else if (i == fruitY && j == fruitX )

cout << "%"; // change it to change the fruit

else {

bool print = false;

for (int k = 0; k< nTail ; k++) {

if (tailX [k] == j && tailY [k] == i) {

cout << "*"; print = true;

}

}

if (!print) cout << " ";

}

if (j == width -1)

cout << "#";

}

cout << endl;

}

for (int i = 0; i< width+2; i++)

cout << "#";

cout << endl;

cout << "Score:" << score << endl ;

}

void Input ()
{

if (_kbhit ()) {

switch (_getch ()) {

case 'a':

dir = LEFT;

break;

case 'd':

dir = RIGHT;

break;

case 'w':

dir = UP;

break;

case 's':

dir = DOWN ;

break;

case 'x':

gameover = true;

break;

}

}

}

void algorithm()
{

int prevX = tailX [0];

int prevY = tailY [0];

int prev2X, prev2Y;

tailX[0] = x;

tailY[0] = y;

for(int i = 1;i < nTail ; i++) {

prev2X = tailX[i];

prev2Y = tailY[i];

tailX[i] = prevX;

tailY[i] = prevY;

prevX = prev2X;

prevY = prev2Y ;

}

switch (dir) {

case LEFT:

x--;

break;

case RIGHT:

x++;

break;

case UP:

y--;

break;

case DOWN:

y++;

break;

default:

break;

}

if (x >= width) x =0;else if (x <0) x = width -1;

if (y >= height) y = 0; else if (y < 0) y = height - 1;

for (int i =0; i< nTail ;i++)

if (tailX[i] == x && tailY[i] == y)
gameover = true;

if (x == fruitX && y == fruitY) {

score +=10;

fruitX = rand() % width;

fruitY = rand() % height;

nTail ++;

}

}

int main()
{

Setup();

while (!gameover) {

Draw ();

Input ();

algorithm ();

}

return 0;

}*/