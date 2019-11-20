#include "types.h"

typedef std::string String;

void init();
void printSprite(Sprite s);
void printMatrix();
int brightness(Color c);
Sprite spritifyText(String str);
void cleanMatrix();
void clearMatrix();
void color(Color col);
int addSprite(Sprite spr, int x, int y, Color col);
void removeSprite(int id);
DisplayElement getDisplayElement(int id);
void showSprites();
void displaySprite(Sprite spr, int x, int y, Color col);
void colorMatrix();
Color mixCol(Color col1, Color col2, double mix);
void showMatrix();
