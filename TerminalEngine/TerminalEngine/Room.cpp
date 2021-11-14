#include "Room.h"



// Create room from file
//
Room::Room(string roomLayoutPath, int cellSize) {
	// Set vars
	this->cellSize = cellSize;
	
	// Open file
	ifstream file;
	file.open(roomLayoutPath);

	if (!file.is_open())
		throw runtime_error(roomLayoutPath + ": file path not found");

	// Parse file
	string line;
	
	// First line: size
	getline(file, line, ',');
	sizeY = stoi(line);
	getline(file, line, '\n');
	sizeX = stoi(line);
	
	if (sizeX <= 0 || sizeY <= 0) {
		file.close();
		throw runtime_error("room size error");
	}

	// Build room
	roomLayout = new int[sizeY*sizeX];		// Allocate array
	for (int y = 0; y < sizeY; y++) {
		getline(file, line, '\n');

		for (string::size_type x = 0; x < string::size_type(sizeX); x++) {
			if (x < line.length())
				roomLayout[x + (y * sizeX)] = int(line[x] - '0');
			else
				roomLayout[x + (y * sizeX)] = 0;
		}
	}

	
	file.close();
}



void Room::dump() {
	cout << sizeX << "x" << sizeY << endl;
	for (int y=0; y<sizeX; y++) {
		for (int x=0; x<sizeX; x++) {
			cout << operator()(x,y);
		}
		cout << endl;
	}
}

int& Room::at(int x, int y) {
	return operator()(x, y);
}

int& Room::at(int index){
	if (index < 0 || index > sizeX * sizeY - 1) throw out_of_range("index out of range");
	return roomLayout[index];
}

int& Room::operator()(const int& x, const int& y) {
	return roomLayout[x + (y * sizeX)];
}

int Room::getWidth() const {
	return sizeX*cellSize;
}

int Room::getHeight() const {
	return sizeY*cellSize;
}

int Room::getCellSize() const {
	return cellSize;
}

bool Room::cellExistsAt(double x, double y) {
	return getCellAt(x, y);
}

int Room::getCellAt(double x, double y) {
	if (x < 0 || y < 0 || x >= sizeX * cellSize || y >= sizeY * cellSize) return 0;
	return at(int(x / cellSize), int(y / cellSize));
}

int& Room::cellAt(double x, double y) {
	if (x < 0 || y < 0 || x >= sizeX * cellSize || y >= sizeY * cellSize) throw out_of_range("cellAt: out_of_range");
	return at(int(x / cellSize), int(y / cellSize));
}


// Updates distance and returns the first collision block type of a ray shot from x,y at given angle
//

int Room::getFirstCollision(double x, double y, double angle, double& collisionX, double& collisionY, double& distance, int& collisionFace, bool findDoors) {
	double xf = x;
	double yf = y;
	while (!cellExistsAt(xf, yf))
	{
		xf += cos(angle) * 0.1;
		yf += sin(angle) * 0.1;
		
		// Check out of bounds
		if (xf < 0 || yf < 0 || xf >= sizeX * cellSize || yf >= sizeY * cellSize) return -1;
	}

	// Update reference values
	collisionX = xf;
	collisionY = yf;
	collisionFace = getCollisionFace(xf, yf);
	distance = sqrt(pow(xf - x, 2) + pow(yf - y, 2));
	
	return getCellAt(xf,yf);
}

// Updates xFace and yFace of the block at (xPos,yPos)
// 0-right, 1-top, 2-left, 3-bottom
//
int Room::getCollisionFace(double x, double y) {
	int cellX = int(x / cellSize);
	int cellY = int(y / cellSize);
	
	if (cellX < 0 || cellY < 0 || cellX >= sizeX || cellY >= sizeY) return -1;

	// distance from (0,0) of current block
	double dx = x - (cellX * cellSize);
	double dy = y - (cellY * cellSize);
	//
	double dx2 = ((cellX + 1) * cellSize) - x;
	double dy2 = ((cellY + 1) * cellSize) - y;

	// Find closest bound
	double minVal = min(min(dx, dy), min(dx2, dy2));
	if (minVal == dx)
		return 2;
	else if (minVal == dy)
		return 1;
	else if (minVal == dx2)
		return 0;
	else if (minVal == dy2)
		return 3;
	else
		return -1;
}

