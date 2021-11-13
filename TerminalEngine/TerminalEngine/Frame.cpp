#include "Frame.h"



Frame::Frame(int sizeX, int sizeY, color foregroundColor, int foregroundBrightness, color backgroundColor, int backgroundBrightness) {
	this->sizeX = sizeX;
	this->sizeY = sizeY;
	this->foregroundColor = foregroundColor;
	this->backgroundColor = backgroundColor;
	this->foregroundBrightness = foregroundBrightness;
	this->backgroundBrightness = backgroundBrightness;

	int i = 0;
	for (; i < (sizeX * sizeY / 2); i++)
		pixels.push_back(pixel{ backgroundColor, backgroundBrightness });
	for (; i < (sizeX * sizeY); i++)
		pixels.push_back(pixel{ foregroundColor, foregroundBrightness });
}




pixel& Frame::at(const int& x, const int& y) {
	return operator()(x, y);
}


pixel& Frame::operator()(const int& x, const int& y) {
	return pixels[x + (y * sizeX)];
}

void Frame::setColor(int x, int y, color color, int brightness) {
	if (x<0 || y<0 || x>=sizeX || y>=sizeY) return;
	
	pixels[x + (y * sizeX)].color = color;
	pixels[x + (y * sizeX)].brightness = brightness;
}

void Frame::drawRect(int x1, int y1, int x2, int y2, color color, int brightness) {
	for (int y=y1; y<y2; y++)
		for (int x=x1; x<x2; x++)
			setColor(x, y, color, brightness);
}

// Draws a pillar centered on y
//
void Frame::drawPillar(int x, int length, color color, int brightness) {
	if (length % 2 != sizeY % 2) length++;	// length should match the even/odd property of window size
	if (length >= sizeY) {	// out of bounds
		length = sizeY;									// adjust length
		setColor(x, 0, color, brightness);		// Add extra missing bar
	}
	
	int yStart = sizeY / 2;
	for (int y = 0; y < length / 2; y++) {
		setColor(x, yStart + y, color, brightness);
		setColor(x, yStart - y , color, brightness);
	}
}

void Frame::clear() {
	int y = 0;
	for (; y < sizeY/2; y++)
		for (int x = 0; x < sizeX; x++)
			setColor(x, y, backgroundColor, backgroundBrightness);
	for (; y < sizeY; y++)
		for (int x = 0; x < sizeX; x++)
			setColor(x, y, foregroundColor, foregroundBrightness);
}
