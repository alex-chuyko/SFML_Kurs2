#include <SFML/Graphics.hpp>
using namespace sf;

sf::View view;

View getplayercoordinateforview(float x, float y){
	float tempX = x; float tempY = y;
	if (y > 500) tempY = 500;
	if (y < 500) tempY = 500;
	if (x < 400) tempX = 400;
	if (x > 2500) tempX = 2500;
	view.setCenter(tempX, tempY);
	return view;
}
