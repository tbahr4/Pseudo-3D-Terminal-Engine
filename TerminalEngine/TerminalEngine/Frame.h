#pragma once

#include <string>
#include <vector>

using namespace std;


// ASCII colors
const string black = "\u001b[30m";
const string red = "\u001b[31m";
const string green = "\u001b[32m";
const string yellow = "\u001b[33m";
const string blue = "\u001b[34m";
const string magenta = "\u001b[35m";
const string cyan = "\u001b[36m";
const string white = "\u001b[37m";
const string reset = "\u001b[0m";
static vector<string> colors = { black, red, green, yellow, blue, magenta, cyan, white};

enum color
{
	C_BLACK = 0,
	C_RED = 1,
	C_GREEN = 2,
	C_YELLOW = 3,
	C_BLUE = 4,
	C_MAGENTA = 5,
	C_CYAN = 6,
	C_WHITE = 7
};

struct pixel
{
	color color = C_BLACK;
	int brightness = 0;
};

static char pixelOutputs[5] = {' ', char(176), char(177), char(178), char(219)};		// Shading chars




class Frame
{
private:
	int sizeX, sizeY;
	vector<pixel> pixels;
	color foregroundColor;
	color backgroundColor;
	int foregroundBrightness;
	int backgroundBrightness;
	

public:
	Frame(int sizeX, int sizeY, color foregroundColor, int foregroundBrightness, color backgroundColor, int backgroundBrightness);

	pixel& at(const int& x, const int& y);
	pixel& operator()(const int& x, const int& y);
	void setColor(int x, int y, color color, int brightness);

	void drawRect(int x1, int y1, int x2, int y2, color color, int brightness);		// Draws a rectangle from (x1,y1) to (x2,y2)
	void drawPillar(int x, int length, color color, int brightness);				// Draws a pillar centered on y
	void clear();		// Resets the frame to default colors
};

