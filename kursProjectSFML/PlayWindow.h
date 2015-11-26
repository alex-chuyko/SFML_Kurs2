//#include <SFML/Graphics.hpp>
//#include <SFML/Audio.hpp>
//#include <iostream>
//#include "view.h"
//#include "level.h"
//#include <vector>
//#include <sstream>
//#include <Windows.h>
#include "Kub.h"

namespace
{
	sf::RenderWindow window(sf::VideoMode(700, 600), "Impossible Game", sf::Style::Close);
}

void CreatePlayWindow(sf::RenderWindow &menuWindow)
{
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_HIDE);

	String levelFile;

	Level lvl;
	lvl.LoadFromFile("Levels/level1.tmx");

	Font font;
	font.loadFromFile("akashi.ttf");
	Text text("", font, 30);
	text.setColor(Color::White);
	text.setStyle(sf::Text::Bold);
	Text textLvl("", font, 15);
	textLvl.setColor(Color::White);
	textLvl.setStyle(sf::Text::Bold);
 
	if (!window.isOpen())
		window.create(sf::VideoMode(700, 600), "Impossible Game", sf::Style::Close);
		//sf::RenderWindow window(sf::VideoMode(700, 600), "Impossible Game", sf::Style::Close); //800 640
	else
		window.setVisible(true);
	view.reset(sf::FloatRect(0, 0, 700, 600));

	Texture t;
	t.loadFromFile("images/background.jpg");
	Sprite background;
	background.setTexture(t);
	background.setTextureRect(sf::IntRect(0, 0, 14000, 1000));


	Object player = lvl.GetObj("player");
	Object finish = lvl.GetObj("finish");
	Kub kub("kub.jpg", lvl, player.rect.left, player.rect.top, 32, 32);

	Clock clock;

	while (window.isOpen())
	{
		menuWindow.setVisible(false);
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;


		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				menuWindow.setVisible(true);
				//window.setVisible(false);
				window.close();
			}
		}

		finish = kub.checkFinish(player, finish, lvl, window, menuWindow);
		float x = kub.getplayercoordinateX();
		float y = kub.getplayercoordinateY();
		float tempX = x; float tempY = y;
		if (y > 300) tempY = 400;
		else
			if (y < 500) tempY = 400;
		if (x < 400) tempX = 400;
		else
			if (x > 2500) tempX = 2500;
		view.setCenter(tempX, tempY);
		window.setView(view);
		text.setPosition(view.getCenter().x - 80, view.getCenter().y - 280);
		textLvl.setPosition(view.getCenter().x - 340, view.getCenter().y - 300);
		kub.draw(window, lvl, text, background, time, textLvl);

	}
}