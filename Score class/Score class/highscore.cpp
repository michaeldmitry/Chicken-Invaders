#include "highscore.h"


highscore::highscore(string filename)
{
	string text = "scores", text2 = "players";
	input.open(filename,ios::out|ios::in);
	if (!input.fail())
	{
		input << text << setw(14) << text2 << endl;

	}
	input.close();
	
}


highscore::~highscore()
{
}
void highscore::setScore(string s,string n, string f)
{
	
	input.open(f,ios::out|ios::in);
	if (!input.fail())
	{
		score = s;
		name = n;
		
		input << score << setw(14) << name << endl;

	
	}
	input.close();
}
bool highscore::openScores(const string& file)
{
	v.resize(0);
	ifstream input;
	int n, t;
	string s;
	input.open(file.c_str);
	if (!input.fail())
	{
		input >> n;

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

void highscore::saveScores(const string& file)

{
	int i = 0;
	ifstream input;
	input.open(file);
	if (!input.fail())
	{
		input.clear();
		/*while (!input.eof())
		{*/
			input<<v[0].score;
		//}
	}

}