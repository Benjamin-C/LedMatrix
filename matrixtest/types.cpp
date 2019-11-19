#include "types.h"

Sprite_t makeSprite(int width, int height, double* shape) {
	Sprite_t s;
	s.width = width;
	s.height = height;
	s.shape = shape;
	return s;
}

DisplayElement makeDisplayElement(int id, Sprite sprite, int x, int y, Color color) {
	DisplayElement e;
	e.id = id;
	e.sprite = sprite;
	e.x = x;
	e.y = y;
	e.color = color;
	return e;
};

Color makeColor(int r, int g, int b) {
	Color c;
	c.red = r;
	c.green = g;
	c.blue = b;
	return c;
};


