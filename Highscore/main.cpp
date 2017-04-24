#include<iostream>
#include<fstream>
using namespace std;
#include"highscore.h"
int main()
{
	highscore x("Source1.txt");
	x.openScores();
	x.setScore(130,"Sherry");
	x.setScore(100, "Mohamed");
	//x.setScore(150, "Nour");
	x.saveScores();
	
	system("pause");
	return 0;
}