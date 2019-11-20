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
int nextDisplayElementID = 1;
DisplayElement nullDisplayElement;
DisplayElement displayElementArray[MAX_DISPLAY_ELEMENTS] = {nullDisplayElement};

// Matrix vars
Color colorArray[WIDTH*HEIGHT];
int mode = 0;
Color bgcol = makeColor(0, 0, 0);

int main() {
	init();
//	Sprite s = spritifyText("Text");
	Sprite s = spritifyText(".^.");
	printMatrix();
	cout << "start\n";
	int id = addSprite(s, 0, 0, makeColor(0xFF, 0xFF, 0xFF));
	showMatrix();
	removeSprite(id);
	showMatrix();
	return 0;
}

void init() {
	clearMatrix();
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
	cout << "|\n";
}

// Prints a sprite to cout. Any other prints will interrupt the sprite printing
void printMatrix() {
	cout << "Matrix[" << WIDTH  << "," << WIDTH  << "]\n|";
	for(int x = 0; x < WIDTH; x++) {
		cout << "-";
	}
	cout << "|\n|";
	for(int y = 0; y < HEIGHT; y++) {
		for(int x = 0; x < WIDTH; x++) {
			if(brightness(colorArray[(y*WIDTH)+x]) < 128) {
				cout << ".";
			} else {
				cout << "#";
			}
//			cout << s.shape[(y*s.width)+x] << " ";
		}
		cout << "|\n|";
	}
	for(int x = 0; x < WIDTH; x++) {
		cout << "-";
	}
	cout << "|\n\n";
}

int brightness(Color c) {
	return (int) (0.2126*c.red + 0.7152*c.green + 0.0722*c.blue);
}
// Turns the text into a sprite
Sprite spritifyText(String str) {
	int length = str.length();
	int sprwidth = length - 1;
	for(int i = 0; i < length; i++) { // Find width in px
		sprwidth = sprwidth + getAsciiValue(str[i]).width;
	}

	double *spr = new double[5*sprwidth]; // Used as 2d array double[5][sprwidth]
	int pos = 0;
	for(int i = 0; i < length; i++) { // For each character in the string
		Sprite cspr = getAsciiValue(str[i]);
		for(int j = 0; j < cspr.width; j++) { // For each column in the character's representation
			spr[(0*sprwidth)+pos] = cspr.shape[j];
			spr[(1*sprwidth)+pos] = cspr.shape[cspr.width + j];
			spr[(2*sprwidth)+pos] = cspr.shape[(2*cspr.width) + j];
			spr[(3*sprwidth)+pos] = cspr.shape[(3*cspr.width) + j];
			spr[(4*sprwidth)+pos] = cspr.shape[(4*cspr.width) + j];
			pos++;
		}
		pos++; // To add a space between characters
	}
	return makeSprite(sprwidth, 5, spr);
}

// Sets all pixels to black
void cleanMatrix() {
	for(int y = 0; y < HEIGHT; y++) {
		for(int x = 0; x < WIDTH; x++) {
			colorArray[(y*WIDTH)+x].red = 0;
			colorArray[(y*WIDTH)+x].green = 0;
			colorArray[(y*WIDTH)+x].blue = 0;
		}
	}
}

// Removes all display elements from the list
void clearMatrix() {
	for(int i = 0; i < MAX_DISPLAY_ELEMENTS; i++) {
		displayElementArray[i] = nullDisplayElement;
	}
}

// Set the screen to a color
void color(Color col) {
	mode = 1;
	bgcol = col;
}

// Adds a sprite as a new display element
// Returns the ID of the DisplayElement
int addSprite(Sprite spr, int x, int y, Color col) {
	mode = 0;
	int loc = 0;
	for(int i = 0; i < MAX_DISPLAY_ELEMENTS; i++) { // Put the element in the first avaliable spot
		if(&displayElementArray[i] == &nullDisplayElement) {
			loc = i;
			break;
		}
	}
	int id = nextDisplayElementID++;
	displayElementArray[loc] = makeDisplayElement(id, spr, x, y, col);
	return id;
}

// Removes a sprite from the array
void removeSprite(int id) {
	for(int i = 0; i < MAX_DISPLAY_ELEMENTS; i++) {
		if(displayElementArray[i].id == id) {
			displayElementArray[i] = nullDisplayElement;
			cout << "Removed\n";
		}
	}
}

// Gets a dispaly element by id
DisplayElement getDisplayElement(int id) {
	for (int i = 0; i < MAX_DISPLAY_ELEMENTS; i++) {
		if (displayElementArray[i].id == id) {
			return displayElementArray[i];
		}
	}
	return nullDisplayElement;
}

// Prints the sprites to the matrix
void showSprites() {
	if(mode == 0) {
		cleanMatrix();
		for(int i = 0; i < MAX_DISPLAY_ELEMENTS; i++) {
			DisplayElement spr = displayElementArray[i];
			if((&spr != &nullDisplayElement) && (spr.sprite.width != 0) && (spr.sprite.height != 0)) {
				printSprite(spr.sprite);
				displaySprite(spr.sprite, spr.x, spr.y, spr.color);
			}
		}
	} else {
		for(int i = 0; i < WIDTH*HEIGHT; i++) {
			colorArray[i] = bgcol;
		}
	}
}

// Shows a single sprite on the matrix;
void displaySprite(Sprite spr, int xos, int yos, Color col) {
	for(int r = 0; r < spr.height; r++) {
		for(int c = 0; c < spr.width; c++) {
			int x = xos + c;
			int y = yos + r;
			if(x >= 0 && y >= 0 && x < WIDTH && y < HEIGHT) {
				int arpos = (y*WIDTH) + x;
				colorArray[arpos] = mixCol(col, colorArray[arpos], spr.shape[(r*spr.width)+c]);
			}
		}
	}
}

// Send the color array to the matrix;
void colorMatrix() {
	for(int y = 0; y < HEIGHT; y++) {
		for(int x = 0; x < WIDTH; x++) {
			// TODO print to pixel matrix
			Color c = colorArray[(y*WIDTH)+x];
			cout << "Color r:" << c.red << " g:" << c.green << " b:" << c.blue << "\n";
		}
	}
}

// Mixes 2 colors with the ratio of 1:2 equil to mix
Color mixCol(Color col1, Color col2, double mix) {
	Color col = {
		(int) (((col1.red)* mix) + (col2.red) * (1 - mix)),
		(int) ((col1.green * mix) + (col2.green * (1 - mix))),
		(int) ((col1.blue * mix) + (col2.blue * (1 - mix))) };
	return col;
}

// Everything to show the matrix
void showMatrix() {
	showSprites();
	printMatrix();
	colorMatrix();
}
