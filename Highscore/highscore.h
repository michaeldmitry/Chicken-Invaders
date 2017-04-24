#pragma once
#include<string>
#include<iostream>
using namespace std;
#include<fstream>
#include<vector>
class highscore
{
public:
	struct data
	{
		string name;
		int score;
	};
	highscore();
	highscore(string file);
	void setFilename(const string& file);
	~highscore();
	void arrangingScores();
	bool openScores();
	void saveScores();
	void setScore(int s,string n);
	void getScore( vector<data> &vec);
	bool nameExists(string n);
	int getOneScore(string n);
private:
	string filename;
	int index;
	vector<data> v;
	int getIndex(string n)
	{
		for (int i = 0; i < v.size(); i++)
			if (n == v[i].name)
				return i;
		return -1;
	}
	
};

