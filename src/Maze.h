#ifndef MAZE_H_INCLUDED
#define MAZE_H_INCLUDED


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
		bool isPath(int x, int y);
		int getNextDirection(int x, int y);
		bool canMoveThere(int x, int y, int from);

	public:
		Maze(int height, int width, bool classic, bool steps);
		Maze(int height, int width);
		~Maze();

		void genPath(int startx, int starty);
		void saveAsBmp() ;
		void saveAsBmp(std::string fileName);
};


#endif // MAZE_H_INCLUDED
