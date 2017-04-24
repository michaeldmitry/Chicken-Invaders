#include "highscore.h"


highscore::highscore(string file)
{
	v.resize(0);
	filename = file;
}

	highscore::highscore()
	{
		v.resize(0);
	}

	void highscore::setFilename(const string& file)
	{
		filename = file;
	}


highscore::~highscore()
{
}
void highscore::setScore(int s,string n)
{
	data d;
	d.name = n;
	d.score = s;
	for (int i = 0; i < v.size(); i++)
		if (d.name == v[i].name)
		{
			v[i].score = d.score;
			arrangingScores();
			return;
		}

	v.push_back(d);
	arrangingScores();
}
void highscore::arrangingScores()
{
	for (int i = 0; i < v.size() - 1; i++)	
		for (int j = i + 1; j < v.size(); j++)		
			if (v[i].score < v[j].score)
			{
				swap(v[i].score, v[j].score);
				swap(v[i].name, v[j].name);
			}	
}
bool highscore::openScores()
{
	v.resize(0);
	ifstream input;
	int n, t;
	string s;
	input.open(filename);
	if (!input.fail())
	{
		input >> s;
		while (!input.eof())
		{
			input >> t;
			data d;
			d.name = s;
			d.score = t;
			v.push_back(d);
			input >> s;
		}


		input.close(); 
		return true;
	}
	else{
		return false;
	}
}

void highscore::saveScores()

{
	
	ofstream input;
	input.open(filename);
	if (!input.fail())
	{
		input.clear();
		for (int i = 0; i < v.size(); i++)
			input << v[i].name <<" " << v[i].score << endl;
		
	}

}
void highscore::getScore( vector<data>& vec)
{
	vec = v;
}
bool highscore::nameExists(string n)
{
	return (getIndex(n) != -1);
}
int highscore::getOneScore(string n)
{
	int j;
	
	j = getIndex(n);
	if (j == -1)
		return - 1;
	return (v[j].score);
}