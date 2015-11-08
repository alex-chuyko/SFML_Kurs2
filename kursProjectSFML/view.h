#include <SFML/Graphics.hpp>
using namespace sf;

sf::View view;

View getplayercoordinateforview(float x, float y){
	float tempX = x; float tempY = y;
	if (y > 300) tempY = 400;
	else
		if (y < 500) tempY = 400;
	if (x < 400) tempX = 400;
	else
		if (x > 2500) tempX = 2500;
	view.setCenter(tempX, tempY);
	return view;
}
