#ifndef TYPES_WERE_DEFINED
#define TYPES_WERE_DEFINED
struct color_t {
	int red;
	int green;
	int blue;
};
typedef color_t Color;
Color makeColor(int r, int g, int b);

struct Sprite_t {
	int width;
	int height;
	double* shape;
};
typedef Sprite_t Sprite;
Sprite_t makeSprite(int width, int height, double* shape);

struct DisplayElement_t {
	int id;
	Sprite sprite;
	int x;
	int y;
	Color color;
};
typedef DisplayElement_t DisplayElement;

DisplayElement makeDisplayElement(int id, Sprite sprite, int x, int y, Color color);

#endif
