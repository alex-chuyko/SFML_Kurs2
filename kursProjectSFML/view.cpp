#include "view.h"

void getplayercoordinateforview(float x, float y)
{
	float tempX = x; float tempY = y;
	if (y > 300) tempY = 400;
	else
		if (y < 500) tempY = 400;
	if (x < 300) tempX = 400;
	else
		if (x > 2000) tempX = 2000;
	view.setCenter(tempX, tempY);
}