#pragma once
#include<string>
#include<iostream>
#include<iomanip>
using namespace std;
#include<fstream>
#include<vector>
class highscore
{
public:
	highscore(string filename);
	~highscore();
	bool openScores(const string& file);
	void saveScores(const string& file);
	void setScore(string s,string n, string f);
private:
	struct data
	{
		string name;
		int score;
	};
	vector<data> v;
	//fstream input;
	
};

