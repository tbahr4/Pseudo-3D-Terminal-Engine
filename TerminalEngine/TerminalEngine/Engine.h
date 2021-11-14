#pragma once

#include <sstream>
#include <conio.h>

#include "Frame.h"
#include "Room.h"
#include "Window.h"


// Keys
#define key_W 119				// Movement
#define key_A 97
#define key_S 115
#define key_D 100
#define key_rotateLeft 111		// Rotation
#define key_rotateRight 112
#define key_debug_fov_minus 110		// FOV
#define key_debug_fov_plus 109
#define key_interact 102




class Engine
{
private:
	int windowSizeX, windowSizeY;
	Frame* frame;
	Room* room;
	Window* window;
	color foregroundColor;
	int foregroundBrightness;
	color backgroundColor;
	int backgroundBrightness;
	double posX, posY;
	double rotation;

	// Options
	bool enableVSync = true;
	double fov = 70;
	int cubeSize = 80;
	double rotationSpeed = PI / 16;
	int movementSpeed = 25;
	double reachDistance = 100;

public:
	Engine(const string& initialRoomPath, int roomCellSize, color foregroundColor, int foregroundBrightness, color backgroundColor, int backgroundBrightness, double startPosX, double startPosY, double startRotation);

	void updateScreenSize();		// Used for when window is resized

	// Drawing
	void draw2DMap(int cellSize);	// Draws the 2D topdown map of the room to the frame
	void drawFrame();				// Draws the current frame
	void clear();					// Clears the console screen
	void clearFrame();				// Clears the frame for next display
	void buildFrame(bool applyPseudoLighting);				// Builds the frame using rays

	// Control
	void pollInputs();

private:
	void fireRay(double x, double y, double angle, int screenPosition, bool applyPseudoLighting);		// Fires a ray and paints its collision relative to the player
	int getBrightnessFromFace(int face);
	
	// Helpers
	void outputFrame(ostream& output);		// Helper function for drawFrame. Outputs the frame to 'output'
	int getHeightFromDistance(double distance, double angleFromCenter);		// Returns the height of a pillar given the distance
	color getBlockColor(int cellValue);
	int getBlockBrightness(int cellValue);
	bool getBlockSolid(int cellValue);

};

