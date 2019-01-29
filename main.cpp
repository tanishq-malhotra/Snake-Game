#include<iostream>
#include "snake.hpp"
using namespace std;
int main()
{
	CONSOLE_CURSOR_INFO ci;
	ci.dwSize=50;
	ci.bVisible=0;
	SetConsoleCursorInfo(hOut,&ci);
//function which matches the system time and generates different random values
srand (time(NULL));
//snake class object
Snake *s = new Snake(20,35);
s->right();
return 0;
}