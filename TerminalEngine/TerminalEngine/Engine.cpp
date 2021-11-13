#include "Engine.h"



Engine::Engine(const string& initialRoomPath, int roomCellSize, color backgroundColor, int backgroundBrightness, double startPosX, double startPosY, double startRotation) {
	window = new Window();						// Create window
	this->windowSizeX = window->getWidth();
	this->windowSizeY = window->getHeight();
	this->backgroundColor = backgroundColor;
	this->backgroundBrightness = backgroundBrightness;

	frame = new Frame(windowSizeX, windowSizeY, backgroundColor, backgroundBrightness);		// Init frame
	room = new Room(initialRoomPath, roomCellSize);					// Generate room

	posX = startPosX;
	posY = startPosY;
	rotation = startRotation;
	if (posX < 0 || posY < 0 || posX > room->getWidth() || posY > room->getHeight()) throw runtime_error("player out of bounds");

	// Settings
	fov *= PI / 180;		// Convert to radians
}


// Draws the current frame
//
void Engine::drawFrame() {
	if (enableVSync) {
		stringstream ss;
		outputFrame(ss);
		string s = ss.str();
		cout << s << '\r';
		
	} else {
		outputFrame(cout);
	}
}

// Helper function for drawFrame. Outputs the frame to 'output'
//
void Engine::outputFrame(ostream& output) {
	for (int y = 0; y < windowSizeY; y++) {
		for (int x = 0; x < windowSizeX; x++) {
			pixel p1 = frame->at(x, y);
			output << colors[p1.color] << pixelOutputs[p1.brightness];
		}
	}
}


// Clears the console screen to black
//
void Engine::clear() {
	for (int y = 0; y < windowSizeY/8; y++)
		cout << "\n\n\n\n\n\n\n\n";
}


// Used for when window is resized
//
void Engine::updateScreenSize() {
	int w = windowSizeX;
	int h = windowSizeY;
	window->updateWidthHeight(windowSizeX, windowSizeY);

	// Update frame size if resized
	if (w != windowSizeX || h != windowSizeY) {
		delete frame;
		frame = new Frame(windowSizeX, windowSizeY, backgroundColor, backgroundBrightness);		// Init frame
	}
}


// Displays the 2D topdown map of the room
//
void Engine::draw2DMap(int cellSize) {
	int roomWidth = room->getWidth();
	int roomHeight = room->getHeight();
	int mapWidth = cellSize * roomWidth;		// cellSize of map, not room
	int mapHeight = cellSize * roomHeight;

	// Draw map top-left
	for (int y = 0; y < roomHeight; y++)
		for (int x=0; x< roomWidth; x++)
			if (room->at(x,y) == 1)		// Draw box
				frame->drawRect(x*cellSize, y*cellSize, (x * cellSize) + cellSize, (y * cellSize) + cellSize, C_WHITE, 4);
}



// Fires a ray and draws the collision line
//
void Engine::fireRay(double x, double y, double angle, int screenPosition) {
	if (room->cellExistsAt(x, y)) return;		// Inside object: do not draw

	double distance = -1;
	int blockValue = room->getFirstCollision(x, y, angle, distance);		// Get first collision and update distance
	
	// Draw ray if collision occured (distance >= 0)
	frame->drawPillar(screenPosition, getHeightFromDistance(distance, rotation-angle), getBlockColor(blockValue), getBlockBrightness(blockValue));
}

// Returns the height of a pillar given the distance
//
int Engine::getHeightFromDistance(double distance, double angleFromCenter) {
	if (distance <= -1) return 0;
	
	//return int(((cubeSize * windowSizeY) / distance)*cos(angleFromCenter));
	return int(cubeSize * windowSizeY / distance);
}

void Engine::clearFrame() {
	frame->clear();
}

// Builds the frame using rays
//
void Engine::buildFrame()				
{
	int screenPos = windowSizeX;
	for (double angle = rotation - (fov / 2); angle <= rotation + (fov / 2); angle += fov / windowSizeX) {
		fireRay(posX, posY, angle, screenPos--);
	}
}

color Engine::getBlockColor(int cellValue) {
	switch (cellValue)
	{
	case 1: return C_RED;
	case 2: return C_MAGENTA;
	default: return C_BLACK;
	}
}

int Engine::getBlockBrightness(int cellValue) {
	switch (cellValue)
	{
	case 1: return 4;
	case 2: return 2;
	default: return 0;
	}
}

void Engine::pollInputs() {
	int key = _getch();

	// X-Y movement
	int y = ((key == key_W) - (key == key_S));
	int x = ((key == key_A) - (key == key_D));
	posY += (movementSpeed) * ((x * cos(rotation)) + (y * sin(rotation)));
	posX += (movementSpeed) * ((y * cos(rotation)) - (x * sin(rotation)));
	
		
	// Rotation
	rotation += rotationSpeed * ((key == key_rotateLeft) - (key == key_rotateRight));

	// FOV
	if (key == key_debug_fov_plus)
		fov += PI / 16;
	else if (key == key_debug_fov_minus)
		fov -= PI / 16;
}

