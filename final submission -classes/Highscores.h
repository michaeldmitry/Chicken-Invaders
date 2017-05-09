#pragma once
#include<string>
#include<iostream>
#include <SFML/Graphics.hpp>
using namespace std;
#include<fstream>
#include<vector>
class Highscores
{
public:
	struct data
	{
		string name;
		int score;
	};
	Highscores();
	Highscores(string file);
	void setFilename(const string& file);
	void intializeScores( sf::Font  fontType);
	void drawScoresToWindow(sf::RenderWindow &window);
	~Highscores();
	void arrangingScores();
	bool openScores();
	void saveScores();
	void setScore(int s, string n);
	void getScore(vector<data> &vec);
	bool nameExists(string n);
	int getOneScore(string n);
    void updateScores(string s, int x);

private:
	string filename;
	int index;
	sf::Text text;
	vector<data> v;
	vector < sf::Text > t;
	int getIndex(string n)
	{
		for (int i = 0; i < v.size(); i++)
			if (n == v[i].name)
				return i;
		return -1;
	}

};

