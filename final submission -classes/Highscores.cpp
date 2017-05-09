#include "Highscores.h"


Highscores::Highscores(string file)
{
	v.resize(0);
	filename = file;
}

Highscores::Highscores()
{
	v.resize(0);
}

void Highscores::setFilename(const string& file)
	{
		filename = file;
	}


Highscores::~Highscores()
{
}
void Highscores::setScore(int s, string n)
{
	data d;
	d.name = n;
	d.score = s;
	for (int i = 0; i < v.size(); i++)
		if (d.name == v[i].name)
		{
            if(d.score > v[i].score){
                v[i].score = d.score;
                arrangingScores();
            }
			return;
		}

	v.push_back(d);
	arrangingScores();
}
void Highscores::arrangingScores()
{
	for (int i = 0; i < v.size() - 1; i++)	
		for (int j = i + 1; j < v.size(); j++)		
			if (v[i].score < v[j].score){
				swap(v[i].score, v[j].score);
				swap(v[i].name, v[j].name);
			}	
}
bool Highscores::openScores()
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
void Highscores:: updateScores(string s, int x)
{
    data temp;
    temp.name=s;
    temp.score=x;
    v.push_back(temp);
}
void Highscores::saveScores()
{
	ofstream output;
	output.open(filename);
	if (!output.fail())
	{
		output.clear();
		for (int i = 0; i < v.size(); i++)
			output << v[i].name <<" " << v[i].score << endl;
		
	}

}
void Highscores::getScore(vector<data>& vec)
{
	vec = v;
}
bool Highscores::nameExists(string n)
{
	return (getIndex(n) != -1);
}
int Highscores::getOneScore(string n)
{
	int j;
	
	j = getIndex(n);
	if (j == -1)
		return - 1;
	return (v[j].score);
}
void Highscores::intializeScores( sf::Font  fontType)
{
	text.setCharacterSize(30);
	text.setFont(fontType);
	for (int i = 0; i < v.size(); i++)
	{
		text.setString(v[i].name + "       " + to_string(v[i].score));
		t.push_back(text);
		t[i].setPosition(sf::Vector2f(100, 100 * i));
	}
}
void Highscores::drawScoresToWindow(sf::RenderWindow &window)
{
	for (int i = 0; i < v.size(); i++)
		window.draw(t[i]);
}
