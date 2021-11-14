#pragma once

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

#define PI 3.1415926535

enum BLOCK_TYPE
{
	block_empty = 0,
	block_wall = 1,
	block_door_closed = 2,
	block_wall_tall = 3
};

class Room
{
private:
	int sizeX, sizeY;		// Room size
	int* roomLayout;		// 2D Array for room layout
	int cellSize;			// Size of a room cell

public:
	Room(string roomLayoutPath, int cellSize);
	void dump();

	int getWidth() const;
	int getHeight() const;
	int getCellSize() const;

	int& at(int x, int y);
	int& at(int index);
	int& operator()(const int& x, const int& y);

	// Raytracing
	bool cellExistsAt(double x, double y);
	int getFirstCollision(double x, double y, double angle, double& collisionX, double& collisionY, double& distance, int& collisionFace, bool findDoors);		// Updates distance and returns the first collision block type; also updates the face of the collision
	int getCellAt(double x, double y);
	int& cellAt(double x, double y);
	int getCollisionFace(double x, double y);			// returns the face of the block collided at (xPos,yPos)	
	
};

