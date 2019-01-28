#include<bits/stdc++.h>
#include "snake.hpp"
using namespace std;

int main()
{
//function which matches the system time and generates different random values
srand (time(NULL));
//snake class object
Snake *s = new Snake(20,35);
s->right();
return 0;
}