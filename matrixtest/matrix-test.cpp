#include <iostream>
#include <math.h>
#include <string>

#include "ascii.h"
#include "types.h"

using namespace std;

#define WIDTH 16
#define HEIGHT 16
#define PIXELS 256

#define PIN 4

int main() {
//	Sprite s = spritifyText("Text");
	for(int i = 32; i < 127; i++) {
		cout << i;
		cout << "\n";
		Sprite s = getAsciiValue(i);
		cout << "|";
		for(int x = 0; x < s.width; x++) {
			cout << "-";
		}
		cout << "|\n|";
		for(int y = 0; y < s.height; y++) {
			for(int x = 0; x < s.width; x++) {
				if(s.shape[(y*s.width)+x] == 0) {
					cout << ".";
				} else {
					cout << "#";
				}
			}
			cout << "|\n|";
		}
		for(int x = 0; x < s.width; x++) {
			cout << "-";
		}
		cout << "|\n\n";
	}
	return 0;
}
