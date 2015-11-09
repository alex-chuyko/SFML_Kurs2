//#include <SFML/Graphics.hpp>
//#include <SFML/Audio.hpp>
//#include <iostream>
//#include "view.h"
//#include "level.h"
//#include <vector>
//#include <sstream>
//#include <Windows.h>
#include "Kub.h"

void CreatePlayWindow()
{
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_HIDE);

	String levelFile;

	Level lvl;
	lvl.LoadFromFile("Levels/level1.tmx");

	Font font;
	font.loadFromFile("birdman_bold.ttf");
	Text text("", font, 30);
	text.setColor(Color::White);
	text.setStyle(sf::Text::Bold);

	sf::RenderWindow window(sf::VideoMode(600, 600), "Impossible Game"); //800 640
	view.reset(sf::FloatRect(0, 0, 600, 600));

	Texture t;
	t.loadFromFile("images/background.jpg");
	Sprite background;
	background.setTexture(t);
	background.setTextureRect(sf::IntRect(0, 0, 14000, 1000));


	Object player = lvl.GetObj("player");
	Object finish = lvl.GetObj("finish");
	Kub k("kub.jpg", lvl, player.rect.left, player.rect.top, 32, 32);

	Clock clock;

	while (window.isOpen())
	{

		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;


		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		finish = k.checkFinish(player, finish, lvl);
		float x = k.getplayercoordinateX(); 
		float y = k.getplayercoordinateY();
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
		k.draw(window, lvl, text, background, time);

	}
}