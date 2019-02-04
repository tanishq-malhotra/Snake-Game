#include<bits/stdc++.h>
#include<fstream>
#include<conio.h>
#include<windows.h>
using namespace std;
//handle declared, extern is used because it is a global variable
extern HANDLE hOut;
class Snake
{
public:
//defining row, column, headx and heady
int r, c, x, y;
//food x and y coordinates
int fx,fy;
//used to quit the game
bool gameover = true;
//main game grid
char **grid;
//for storing snake's x and y coordinates
int *sx,*sy;
//counter to check the tail's length
int tailC;
//to check for snake's previous direction
string s;
//Score
int sc;

//default constructor
Snake();
//parameterised constructor to set value's
Snake(int ,int );
//generating food at random position
void food_random();
//printing the main game
void Print();
//display score
void display_score();
//function to update the values of the tail's position
void moveTail();
//to check the collision of snake with the wall
void checkWallCollision();
//pass through wall
void passThroughWall();
//to check the collision of food and snake
void eatFood();
//to check if snake snake hits itself or not
void checkHitItself();
//moving snake up
void up();
//moving snake down
void down();
//moving snake left
void left();
//moving snake right
void right();
//function which takes the input
void input();
//function to get the grid
char** pat2grid(int r,int c);
};