
#include "stdafx.h"
#include "Input.h"
#include "Weapon.h"

using namespace std;

/*VARIABLES*/
boolean run = true;
boolean enabled = false;
int bulletNr = 0;
int divider = 10;
int restX = 0;
int restY = 0;



/*WEAPON SETTINGS                                     10             15                  20                     */
int ak47OffsetY[30] = { 58 ,56, 50,46 ,40,26,24,34,16,12,14,16,36,34,42 ,46 ,36 ,40 ,30 ,20 ,16 ,8  ,8  ,12,26,0,0,0,0,0};
int ak47OffsetX[30] = { -41,5 ,-60,-52,0 ,20,28,46,58,48,52,30,28,-8,-20,-30,-52,-54,-60,-56,-52,-44,-42,18,0 ,0,0,0,0,0};
Weapon ak47 = Weapon(120, 30, ak47OffsetY, ak47OffsetX);

int semiOffsetY[16] = { 52,52,40,40,40,40,40,40,40,40,40,40,40,40,40,40 };
int semiOffsetX[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
Weapon semi = Weapon(200, 1, semiOffsetY, semiOffsetX);

void macro(Weapon weapon) {
	Sleep(weapon.sleepTime);
	INPUT input;
	input.type = INPUT_MOUSE;
	input.mi.mouseData = 0;
	input.mi.time = 0;
	input.mi.dx = weapon.offsetX[bulletNr];
	input.mi.dy = weapon.offsetY[bulletNr];
	input.mi.dwFlags = MOUSEEVENTF_MOVE;
	SendInput(1, &input, sizeof(input));
	bulletNr++;
}


void macro3(Weapon weapon) {
	INPUT input;
	input.type = INPUT_MOUSE;
	input.mi.mouseData = 0;
	input.mi.time = 0;
	input.mi.dwFlags = MOUSEEVENTF_MOVE;

	for (int i = 1; i <= divider; i++) {
		Sleep(weapon.sleepTime / divider);
		input.mi.dx = weapon.offsetX[bulletNr] / divider;
		input.mi.dy = weapon.offsetY[bulletNr] / divider;
		
		restX += weapon.offsetX[bulletNr] % divider;
		restY += weapon.offsetY[bulletNr] % divider;
		if (restX >= 10) {
			restX -= 10;
			input.mi.dx++;
		}
		if (restY >= 10) {
			restY -= 10;
			input.mi.dy++;
		}

		SendInput(1, &input, sizeof(input));
	}
	bulletNr++;
	if (bulletNr > weapon.capacity)
		bulletNr = 0;
}


int main()
{
	Weapon actualWeapon = ak47;

	while (run) {
		shutDown(run);
		turnOnOff(enabled);

		if (enabled && mousePressed() && ctrlPressed()) {
			macro3(actualWeapon);
		}
		else {
			bulletNr = 0;
			restX = 0;
			restY = 0;
		}
	}
    return 0;
}

