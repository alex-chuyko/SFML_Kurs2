#pragma once
#include <SFML\Graphics.hpp>

//#define MAX_NUMBER_OF_ITEMS 3


class Menu
{
public:
	Menu(float width, float height, sf::String FileName, int MAX_NUMBER_OF_ITEMS);
	~Menu();

	void draw(sf::RenderWindow &window, int MAX_NUMBER_OF_ITEMS);
	void MoveUp();
	void MoveDown(int MAX_NUMBER_OF_ITEMS);
	int GetPressedItem() { return selectedItemIndex; }

private:
	int selectedItemIndex;
	sf::Image image[3];
	sf::Texture texture[3];
	sf::Sprite sprite[3];
};


