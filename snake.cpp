#include <bits/stdc++.h>
//for using the kbhit function
#include <conio.h>
using namespace std;

//snake class
class Snake
{
public:
//defining row, column, headx and heady
int r, c, x, y;

//food x and y coordinates
int fx,fy;

//used to quit the game
bool gameover = true;

//for storing snake's x and y coordinates
int *sx, *sy;

//counter to check the tail's length
int tailC;

//to check for snake's previous direction
string s;

//Score
int sc;
//default constructor
  Snake(){}

  //parameterised constructor to set value's
  Snake(int n , int m): r(n), c(m), tailC(1), sc(0)
  {
  	//allocating memory to snake's array
  	sx = new int [100];
  	sy = new int [100];

  	//for generating a random position for the snake's head
  	redo:
  	x = rand() % r;
  	y = rand() % c;

  	//if the coordinates are zero then we will generate coordinates again
  	if(x == 0 || y == 0)
  		goto redo;

  	//used to generate food
  	food_random();
  }

  //generating food at random position
  void food_random()
  {
  	//if the coordinates are zero then we will generate coordinates again
  	re:
  		fx = rand() % (r - 2);
  		fy = rand() % (c - 5);
  	if (fx == 0 || fy == 0)
  		goto re;
    else
    {
      for(int i = 0; i < tailC; i++)
        if(fx == sx[i] || fy == sy[i])
          goto re;
    }
  }

//printing the main game
  void Print()
  {
  	//clear screen
	system("cls");

	//main loop
	for (int i = 0; i < r ; i++)
     {
      for (int j = 0; j < c; j++)
      	{
      		//defining border
	        if(i == 0 || j == c - 1 || i == r - 1 || j == 0 ) cout<<'#';
	        else
	        {
	        	//printing food
	        	if(i == fx && j == fy) cout<<"F";

	        	//printing head
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
    	}
    //printing new line
      cout<<endl;
    }
  }

  //display score
  void display_score()
  {
    cout<<endl<<endl<<"Score: "<<sc;
  }

//function to update the values of the tail's position
  void moveTail()
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

  //to check the collostion of snake with the wall
  void checkWallCollosition()
  {
  	//if x and y touches the boundary
  	if(x == 0 || x == r - 1 || y == 0 || y == c - 1)
    {
      cout<<endl<<"Snake Hit's The boundary";
  		gameover = false;
    }
  }

  //to check the collision of food and snake
  void eatFood()
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
  void checkHitItself()
  {
  	//iterate through the snake array
  	for(int i = 1; i < tailC; i++)
  		//if array coordinates matches the position of head
  		if(sx[i] == x && sy[i] == y)
      { 
        cout<<endl<<"Snake Hit Itsef at tail number:"<<i - 1<<endl;
         gameover = false;
       }
  }

//moving snake up
  void up()
  {
  	//if s is down then it will not move up
  	if(s != "d")
  	{
  	x -= 1;
  	s = "u";
  	//function's called
  	checkWallCollosition();
  	eatFood();
  	moveTail();
    checkHitItself();
	}
  }

//moving snake down
  void down()
  {
  	//if s is up the it will not move down
  	if(s != "u")
  	{
  	x += 1;
  	s = "d";
  	checkWallCollosition();
  	eatFood();
  	moveTail();
  	checkHitItself();
  }
  }

//moving snake left
  void left()
  {
  	//if s is right then it will not move left
  	if(s != "r")
  	{
  	y -= 1;
  	s = "l";
  	checkWallCollosition();
  	eatFood();
  	moveTail();
  	checkHitItself();
  }
  }

//moving snake right
  void right()
  {
  	//if s is left then it will not move right
  	if(s != "l")
  	{
  	y += 1;
  	s = "r";
  	checkWallCollosition();
  	eatFood();
  	moveTail();
  	checkHitItself();
  }
  }

//function which takes the input
  void input()
  {
  	//function used to continue the while loop and taking inputs
  	if(kbhit())
  	{
  		//getch takes the input and switch assign's the case
  		switch(getch())
  		{
  			//various cases
  			case 'w' : up(); break;

  			case 's' : down(); break;
  					   
  			case 'a' : left(); break;
  					    
  			case 'd' : right(); break;
  					    
			case 'q' : gameover = false; break;
  		}
  	}
  }
};

//main function
int main()
{
//function which matches the system time and generates different random values
  srand (time(NULL));

  //snake class object
  Snake s(20,50);

  //main loop to continue the game
  while(s.gameover)
  {
  	//print functin called
	  s.Print();
    s.display_score();
	  //input function called
	  s.input();
  }
  return 0;
}