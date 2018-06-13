#include "stdafx.h"
#include "Input.h"

using namespace std;

/*VARIABLES*/
int shutDownTimer = 0;

boolean mousePressed(){
	if (GetKeyState(VK_LBUTTON) & 0x8000)
		return true;
	else
		return false;
}

boolean ctrlPressed(){
	if (GetKeyState(VK_LCONTROL) & 0x8000)
		return true;
	else
		return false;
}

void shutDown(boolean & run){
	if (GetKeyState(VK_F6) & 0x8000) {
		shutDownTimer++;
		Sleep(100);
		if (shutDownTimer == 30)
			run = false;
	}
	else
		shutDownTimer = 0;
}

void turnOnOff(boolean & enabled){
	if (GetKeyState(VK_MULTIPLY) & 0x8000) {
		enabled = !enabled;
		if (enabled)
			cout << "ON" << endl;
		else
			cout << "OFF" << endl;
		Sleep(1000);
	}
}
