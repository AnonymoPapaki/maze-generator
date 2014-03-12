#include <iostream>
#include "Maze.h"

int main()
{
    int size = 50;

	//Maze(height, width, classicFeel, dumpSteps)
	//dumpSteps requires a folder named seq already existing
    Maze m(size, size*3, true, false);

    m.genPath(size / 2 , size / 2);
    m.saveAsBmp();

    std::cout << "Map saved.";
	std::cin.get();

    return 0;
}
