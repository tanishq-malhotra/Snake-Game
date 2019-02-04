#include "snake.hpp"
//handle created, used to clear the screen
HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
Snake::Snake() {}
//parameterised constructor to set value's
Snake::Snake(int n, int m):r(n),c(m),tailC(0),sc(0),x(10),y(3)
{
	s = "r";
	//creating grid and storing stage in grid
    grid = pat2grid(r, c);

    sx = new int[101];
    sy = new int[101];
  	//used to generate food
  	food_random();
}

//generating food at random position
void Snake::food_random()
{
//if the coordinates are zero then we will generate coordinates again
  re:
    fx = rand() % (r);
    fy = rand() % (c);
    //if fx = 0 and fy = 0 or is with border then goto re
    if (fx == 0 || fy == 0 || fx == r - 1 || fy == c - 1 || fx > r || fy > c)
      goto re;
     //if fx and fy matches with the coordinates of the tail
      for(int i = 0; i < tailC; i++)
        if(fx == sx[i] || fy == sy[i])
          {
            fx = rand() % (r);
            fy = rand() % (c);
          }
    
//if food coordinates matches with the coordinates of the pattern in grid
   for(int i = 0; i < r; i++)
    {
     for(int j = 0; j < c; j++)
      {
       if(grid[i][j] == '#' && i == fx && j == fy)
        {
          fx = rand() % (r); fy = rand() % (c);
        }
      }
    }
}

//printing the main game
void Snake::Print()
{
//clear screen by setting the cursor back to 0,0 coordinates
 SetConsoleCursorPosition(hOut, {0,0});
//main loop
 for (int i = 0; i < r ; i++)
  {
   for (int j = 0; j < c; j++)
    {
     //printing grid
	 cout<<grid[i][j];
	 //printing food
	 if(i == fx && j == fy) cout<<"F";
     //printing head of snake
	 else if(i == x && j == y) cout<<'O';
	 else
	  {
	 //flag used for printing space if there is no tail
	   int f = 0;
     //loop for iterating the snake array
	   for(int k = 0; k < tailC; k++)
	    {
	   //if coordinates matches then print the tail and set flag to 1
	      if(sx[k] == i && sy[k] == j)
	       {
	        f = 1; cout<<"*";
	       }
	    }
	   //if flag is zero, we print space
	    if(f == 0) cout<<' ';
	   }
    }
//printing new line
  cout<<endl;
    }
}

//display score
void Snake::display_score()
{
cout<<endl<<endl<<"Score: "<<sc;
}

//function to update the values of the tail's position
void Snake::moveTail()
{
//storing the initial coordinates of the tail
int tempx = sx[0], tempy = sy[0], tx, ty;
//assigning new coordinates to the tail
sx[0] = x; sy[0] = y;
//loop used to shift the coordinates to the previous tail's
for(int i = 1; i < tailC; i++)
 {
//storing the coodintes of the next tail
   tx = sx[i]; ty = sy[i];
 //assigning new coordinates to the tail
   sx[i] = tempx; sy[i] = tempy;
//updating the value of the temp variables
    tempx = tx; tempy = ty;
  }
}

//to check the collision of snake with the wall
void Snake::checkWallCollision()
{
  for(int i = 0; i < r; i++)
   {
    for(int j = 0; j < c; j++)
     {
       if(grid[i][j] == '#' && i == x && j == y && (i != 0 && i != r - 1 && j != 0 && j != c - 1))
            gameover = false;
     }
   } 
}

//pass through wall
void Snake::passThroughWall()
{
  if(y == c - 1) y = 0;
  else if(y == 0) y = c - 1;
  else if (x == 0) x = r - 1;
  else if(x == r - 1) x = 0;
}
//to check the collision of food and snake
void Snake::eatFood()
{
//if the coordinates of the head matches with the coordinates of the food
if(x == fx && y == fy)
{
//if collision then increment the score
  sc += 10;
//to generate new food at a new random position
food_random();
//incrementing the counter means adding new tail
tailC += 1;
}
}

//to check if snake snake hits itself or not
void Snake::checkHitItself()
{
//iterate through the snake array
  for(int i = 1; i < tailC; i++)
  //if array coordinates matches the position of head
  	if(sx[i] == x && sy[i] == y)
     gameover = false;
}

//moving snake up
void Snake::up()
{
 while(gameover && s == "u")
  {
    Sleep(50);
  //if s is down then it will not move up
  	x -= 1;
  	//function's called
    Print();
    passThroughWall();
    display_score();
    input();
  	checkWallCollision();
  	eatFood();
  	moveTail();
    checkHitItself();   
  }
}

//moving snake down
void Snake::down()
{
  while(gameover && s == "d")
   {
    Sleep(50);
  	//if s is up the it will not move down  	
  	x += 1;
    Print();
    display_score();
    passThroughWall();
    input();
  	checkWallCollision();
  	eatFood();
  	moveTail();
  	checkHitItself();
  }
}

//moving snake left
void Snake::left()
{
 while(gameover && s == "l")
 {
  Sleep(50);
  	//if s is right then it will not move left
  	y -= 1;
    Print();
    display_score();
    passThroughWall();
    input();
  	checkWallCollision();
  	eatFood();
  	moveTail();
  	checkHitItself();
 }
}

//moving snake right
void Snake::right()
{
 while(gameover && s == "r")
 {
  Sleep(50);
//if s is left then it will not move right
  y += 1;   
  Print();
  display_score();
  passThroughWall();
  input();
 checkWallCollision();
 eatFood();
 moveTail();
 checkHitItself();    
  }
}

//function which takes the input
void Snake::input()
{
//function used to continue the while loop and taking inputs
if(kbhit())
 {
//getch takes the input and switch assign's the case
  switch(getch())
  {
  //various cases
  case 'w' : if(s != "d"){
             s = "u"; up(); break;
             }
             else break;
                  
  case 's' : if(s != "u"){
             s = "d"; down(); break;
             }
              else break;
  					   
  case 'a' : if(s != "r"){
             s = "l"; left(); break;
             }
             else break;
                    	    
  case 'd' : if(s != "l"){
              s = "r"; right(); break;
              }
              else break;
                  
  case 'q' : gameover = false; break;
  }
 }
}

char** Snake::pat2grid(int r,int c)
{
char **grid = new char*[r];
for(int i = 0; i < r; i++) grid[i] = new char [c];
fstream file;
file.open("pattern.txt");
string line;
int i = 0, j = 0;
while(getline(file,line))
{
 for(j = 0; j < line.length(); j++)
	grid[i][j] = (char)line[j];
	i++;
}
file.close();
return grid;
}