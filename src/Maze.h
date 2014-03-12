#ifndef MAZE_H_INCLUDED
#define MAZE_H_INCLUDED

#include "Color.h"
#include "Bitmap.h"
#include <stack>
#include <sstream>
#include <ctime>
#include <cstdlib>

#include <memory> // unique_ptr

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define CLASSIC_FEEL true

using namespace std;

class Maze
{
	private:
		Bitmap* maze;
		Color wallColor;
		Color pathColor;
		int mazeHeight;
		int mazeWidth;
		bool classicFeel;
		bool dumpSteps;

		int getOpposite(int direction);
		bool checkValidPos(int x, int y, int from);
		bool isPath(int x, int y) {return maze->isColor(x, y, &pathColor);};
		int getNextDirection(int x, int y);
		bool canMoveThere(int x, int y, int from);

	public:
		Maze(int height, int width, bool classic, bool steps);
		Maze(int height, int width);
		~Maze();

		void genPath(int startx, int starty);
		void saveAsBmp() { maze->createFile("test.bmp"); }
		void saveAsBmp(std::string fileName) { maze->createFile(fileName); }
};

Maze::Maze(int height, int width, bool classic, bool steps) :
	mazeHeight(height), mazeWidth(width), classicFeel(classic), dumpSteps(steps),
	pathColor(Color::Yellow)
{
	maze = new Bitmap(height, width);
	srand((unsigned int)time(NULL));
}

Maze::Maze(int height, int width)
{
	Maze(height, width, true, false);
}

Maze::~Maze()
{
	delete maze;
}

int Maze::getOpposite(int direction)
{
	switch(direction)
	{
		case(UP): return DOWN; break;
		case(DOWN): return UP; break;
		case(LEFT): return RIGHT; break;
		case(RIGHT): return LEFT; break;
		default: return -1;
	}
}

bool Maze::checkValidPos(int x, int y, int from)
{
	bool invalid = false;

	if(from != UP && y+1 <= mazeHeight)
		invalid = invalid || maze->isColor(x, y+1, &wallColor);
	if(from != DOWN && y-1 >= 0)
		invalid = invalid || maze->isColor(x, y-1, &wallColor);
	if(from != RIGHT && x-1 >= 0)
		invalid = invalid || maze->isColor(x-1, y, &wallColor);
	if(from != LEFT && x+1 >= mazeWidth)
		invalid = invalid || maze->isColor(x+1, y, &wallColor);

	return invalid;
}

bool Maze::canMoveThere(int x, int y, int from)
{
	if(x < 0 || y < 0 || x >= mazeWidth || y >= mazeHeight)
		return false;

	if(isPath(x, y))
		return false;

	if( (isPath(x, y-1) && from != UP  ) ||
		(isPath(x, y+1) && from != DOWN) ||
		(isPath(x-1, y) && from != LEFT) ||
		(isPath(x+1, y) && from != RIGHT))
	return false;

	if(classicFeel)
		if( (isPath(x-1, y-1) && isPath(x+1, y-1) && from != UP  ) ||
			(isPath(x-1, y+1) && isPath(x+1, y+1) && from != DOWN) ||
			(isPath(x-1, y+1) && isPath(x-1, y-1) && from != LEFT) ||
			(isPath(x+1, y+1) && isPath(x+1, y-1) && from != RIGHT))
		return false;

    return true;
}

int Maze::getNextDirection(int x, int y)
{
    stack<int> possibleDirs;

    if(canMoveThere(x, y-1, DOWN))
        possibleDirs.push(UP);
    if(canMoveThere(x, y+1, UP))
        possibleDirs.push(DOWN);
    if(canMoveThere(x+1, y, LEFT))
        possibleDirs.push(RIGHT);
    if(canMoveThere(x-1, y, RIGHT))
        possibleDirs.push(LEFT);

    if(!possibleDirs.empty())
    {
        int nextDir = rand() % possibleDirs.size();

        for(int i = 0; i < nextDir; i++)
            possibleDirs.pop();

        return possibleDirs.top();
    }
    else
        return -1;
}

void Maze::genPath(int startx, int starty)
{
    stack<pair<int, int>> pointsToVisit;

	int dir = RIGHT;
	maze->Add(startx, starty, &pathColor);

	int step = 0;

	while(startx >= 0 && starty >= 0 &&
		startx < mazeWidth && starty < mazeHeight)
	{
		step++;
		dir = getNextDirection(startx, starty);

		if(dir == -1)
		{
            if(!pointsToVisit.empty())
            {
                pair<int, int> p = pointsToVisit.top();
                startx = p.first;
                starty = p.second;
                pointsToVisit.pop();
                dir = RIGHT;
                continue;
            }
            else
                break;

		}

		switch(dir)
		{
			case(UP): starty--; break;
			case(DOWN): starty++; break;
			case(LEFT): startx--; break;
			case(RIGHT): startx++; break;
			default: break;
		}

		maze->Add(startx, starty, &pathColor);
        pointsToVisit.push(pair<int, int>(startx, starty));
		
		if(dumpSteps)
		{
			stringstream ss;
			ss << "seq/step" << step << ".bmp";
			saveAsBmp(ss.str());
		}
	}

	Color* c = new Color(0xFF, 0x00, 0x00);
	maze->Add(mazeWidth / 2, mazeHeight / 2, c);
}

#endif // MAZE_H_INCLUDED
