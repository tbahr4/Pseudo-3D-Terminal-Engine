#pragma once

#include <windows.h>



class Window
{
private:
	CONSOLE_SCREEN_BUFFER_INFO screenInfo{};
	int width, height;

public:
	Window();
	int getWidth();
	int getHeight();
	void updateWidthHeight(int& w, int& h);

private:
	void updateScreenDimensions();
	
};
