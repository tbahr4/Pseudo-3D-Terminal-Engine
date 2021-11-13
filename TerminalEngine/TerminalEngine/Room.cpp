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

		for (int x = 0; x < sizeX; x++)
			roomLayout[x + (y * sizeX)] = int(line[x] - '0');
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


// Updates distance and returns the first collision block type of a ray shot from x,y at given angle
//

int Room::getFirstCollision(double x, double y, double angle, double& distance) {
	double xf = x;
	double yf = y;
	while (!cellExistsAt(xf,yf))
	{
		xf += cos(angle) * 0.1;
		yf += sin(angle) * 0.1;
		
		// Check out of bounds
		if (xf < 0 || yf < 0 || xf >= sizeX * cellSize || yf >= sizeY * cellSize) return -1;
	}

	distance = sqrt(pow(xf - x, 2) + pow(yf - y, 2));
	return getCellAt(xf,yf);
}

