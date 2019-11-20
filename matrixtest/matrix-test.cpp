#include <iostream>
#include <math.h>
#include <string>

#include "ascii.h"
#include "types.h"

#include "matrix-test.h"

using namespace std;

// Matrix CONFIG
#define WIDTH 16 // The matrix width
#define HEIGHT 16 // The matrix height
#define PIN 4 // the pin on the ESP8266. 4 = D2 on NodeMCU

// DisplayElemtnt CONFIG
#define MAX_DISPLAY_ELEMENTS 64 // Sets the maximum number of allowed DisplayElements. This is a software limitation to save RAM.

// DisplayElement vars
int nextDisplayElementID = 0;
DisplayElement displayElementArray[MAX_DISPLAY_ELEMENTS];
DisplayElement nullDisplayElement;

// Matrix vars
Color colorArray[WIDTH*HEIGHT];
int mode = 0;
Color bgcol = makeColor(0, 0, 0);

int main() {
//	Sprite s = spritifyText("Text");
	Sprite s = spritifyText("..");
	printSprite(s);
	return 0;
}

// Prints a sprite to cout. Any other prints will interrupt the sprite printing
void printSprite(Sprite s) {
	cout << "Sprite[" << s.width  << "," << s.height  << "]\n|";
	for(int x = 0; x < s.width; x++) {
		cout << "-";
	}
	cout << "|\n|";
	for(int y = 0; y < s.height; y++) {
		for(int x = 0; x < s.width; x++) {
			if(s.shape[(y*s.width)+x] < .5) {
				cout << ".";
			} else {
				cout << "#";
			}
//			cout << s.shape[(y*s.width)+x] << " ";
		}
		cout << "|\n|";
	}
	for(int x = 0; x < s.width; x++) {
		cout << "-";
	}
	cout << "|\n\n";
}

// Turns the text into a sprite
Sprite spritifyText(String str) {
	int length = str.length();

	int sprwidth = length - 1;
	for(int i = 0; i < length; i++) { // Find width in px
		sprwidth = sprwidth + getAsciiValue(str[i]).width;
	}

	double *spr = new double[5*sprwidth];
//	std::fill(spr[0], spr[0] + 5 * sprwidth, 0);

//	printSprite(makeSprite(sprwidth, 5, spr));

	int pos = 0;
	for(int i = 0; i < length; i++) {
		Sprite cspr = getAsciiValue(str[i]);
//		cout << "cspr\n";
//		printSprite(cspr);
		for(int j = 0; j < cspr.width; j++) {
			spr[(0*sprwidth)+pos] = cspr.shape[j];
			spr[(1*sprwidth)+pos] = cspr.shape[cspr.width + j];
			spr[(2*sprwidth)+pos] = cspr.shape[(2*cspr.width) + j];
			spr[(3*sprwidth)+pos] = cspr.shape[(3*cspr.width) + j];
			spr[(4*sprwidth)+pos] = cspr.shape[(4*cspr.width) + j];
			pos++;
		}
		pos++;
	}
	Sprite out = makeSprite(sprwidth, 5, spr);
//	cout << "spr\n";
//	printSprite(out);
//	cout << "...\n";
	return out;
}
