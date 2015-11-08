#include "Menu.h"


Menu::Menu(float width, float heigth)
{
	sf::String FileName;
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		FileName = "images/btn" + std::to_string(i + 1) + ".png";
		image[i].loadFromFile(FileName);
		texture[i].loadFromImage(image[i]);
		sprite[i].setTexture(texture[i]);
		sprite[i].setPosition(sf::Vector2f(width - width / 1.5, heigth / (MAX_NUMBER_OF_ITEMS + 1) * (i + 0.5)));
	}
	sprite[0].setColor(sf::Color::Red);

	selectedItemIndex = 0;
}


Menu::~Menu()
{
}

void Menu::draw(sf::RenderWindow &window)
{
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window.draw(sprite[i]);
	}
}

void Menu::MoveUp()
{
	sf::Color color;
	if (selectedItemIndex - 1 >= 0)
	{
		color = sprite[selectedItemIndex - 1].getColor();
		sprite[selectedItemIndex].setColor(color);
		selectedItemIndex--;
		sprite[selectedItemIndex].setColor(sf::Color::Red);
	}
}

void Menu::MoveDown()
{
	sf::Color color;
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
	{
		color = sprite[selectedItemIndex + 1].getColor();
		sprite[selectedItemIndex].setColor(color);
		selectedItemIndex++;
		sprite[selectedItemIndex].setColor(sf::Color::Red);
	}
}
