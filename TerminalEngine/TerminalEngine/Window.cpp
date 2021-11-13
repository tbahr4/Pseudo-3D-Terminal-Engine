#include "Window.h"


Window::Window() {
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &screenInfo);		// Update screen info
	width = screenInfo.srWindow.Right - screenInfo.srWindow.Left + 1;		// Update screen width
	height = screenInfo.srWindow.Bottom - screenInfo.srWindow.Top + 1;		// Update screen height
}



// Updates and returns width
//
int Window::getWidth() {
	updateScreenDimensions();
	return width;
}

// Updates and returns height
//
int Window::getHeight() {
	updateScreenDimensions();
	return height;
}

// Minimizes calls to update()
//
void Window::updateWidthHeight(int& w, int& h) {
	updateScreenDimensions();
	w = width;
	h = height;
}

void Window::updateScreenDimensions() {
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &screenInfo);		// Update screen info
	width = screenInfo.srWindow.Right - screenInfo.srWindow.Left + 1;
	height = screenInfo.srWindow.Bottom - screenInfo.srWindow.Top + 1;
}
