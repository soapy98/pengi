#pragma once
#include <CustomLevel.h>

typedef std::vector<std::pair<int, int>> Path;
static class PathFinder
{
public:
	static void SetLevel(CustomLevel*);
	static Path PathAStar(int, int, int, int);
private:
	static CustomLevel* mCustomLevel;
	PathFinder();
};

