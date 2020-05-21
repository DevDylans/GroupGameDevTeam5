#include "LevelFile.h"
#include "pch.h"

LevelFile::LevelFile()
{
	string path = "test level file.txt";
	ReadFile(path);
	WriteFile(path);
}

bool LevelFile::ReadFile(string path)
{
	ifstream levelFile(path);
	string line;

	if (levelFile.is_open())
	{
		while (getline(levelFile, line))
		{
			cout << line << '\n';	
		}
		levelFile.close();
		return true;
	}
	else
	{
		return false;
	}
}

bool LevelFile::WriteFile(string path)
{
	ofstream levelFile(path);

	if (levelFile.is_open())
	{
		levelFile << "test_write" << endl;
		levelFile.close();
		return true;
	}
	else
	{
		return false;
	}
}