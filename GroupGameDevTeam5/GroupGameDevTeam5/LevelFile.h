#pragma once
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class LevelFile
{
public:
	LevelFile();

	bool ReadFile(string path);

	bool WriteFile(string path);

private:

};