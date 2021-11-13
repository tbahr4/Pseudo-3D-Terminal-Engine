
#include <iostream>
#include <chrono>

#include "Engine.h"
#include "Room.h"
#include "Window.h"

#include <conio.h>

using namespace std;




int main() {
	cin.ignore();		// wait for resize

	
	Engine engine("rooms/rm_1.txt", 64, C_BLUE, 1, 3*64+32, 3*64+32, 0);

	
	auto start = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
	auto now = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
	
	while (1) {
		now = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
		if (now > start + 1000/60) {
			engine.buildFrame();
			engine.drawFrame();
			engine.clearFrame();
			engine.pollInputs();
			start = now;		// Reset timer
		}

		//while (1) cout << _getch() << endl;



		engine.updateScreenSize();
	}
	

	// Draw 2D room  -- engine funct



	// Get input  --- *** engine funct
	//while (1) {
	//	int key = _getch();
	//	posY += (key == key_W) - (key == key_S);
	//	posX += (key == key_D) - (key == key_A);
	//	cout << posX << " " << posY << endl;
	//}
	
	return 0;
}