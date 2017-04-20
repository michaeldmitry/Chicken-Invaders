#include<iostream>
#include<fstream>
using namespace std;
#include"highscore.h"
int main()
{
	
	string z;
	z = "Source1.txt";
	highscore x(z);
	x.setScore("50"," sherry", z);
	system("pause");
	return 0;
}