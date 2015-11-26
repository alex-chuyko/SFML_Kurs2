//#include <SFML\Graphics.hpp>
//#include <iostream>
//#include <sstream>
#include "Menu.h"
//#include "Kub.h"
#include "PlayWindow.h"

void main()
{
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_HIDE);

	

	window.setVisible(false);

	sf::Font font;
	font.loadFromFile("akashi.ttf");
	sf::Text text("", font, 50);
	text.setColor(sf::Color::White);
	text.setStyle(sf::Text::Bold);

	sf::RenderWindow windowMenu(sf::VideoMode(600, 600), "Impossible Game", sf::Style::Close); //800 640


	Menu menu(windowMenu.getSize().x, windowMenu.getSize().y, "images/btn", 3);

	while (windowMenu.isOpen())
	{
		sf::Event event;
		while (windowMenu.pollEvent(event))
		{
			switch(event.type)
			{
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				break;

				case sf::Keyboard::Up:
					menu.MoveUp();
					break;

				case sf::Keyboard::Down:
					menu.MoveDown(3);
					break;

				case sf::Keyboard::Return:
					switch (menu.GetPressedItem())
					{
					case 0: 
						CreatePlayWindow(windowMenu);
						break;
					case 1:
					{
						sf::Text textH("", font, 50);
						textH.setColor(sf::Color::White);
						textH.setStyle(sf::Text::Bold);

						Texture t;
						t.loadFromFile("images/help.png");
						Sprite help;
						help.setTexture(t);
						help.setPosition(10, 250);

						sf::RenderWindow helpWindow(sf::VideoMode(500, 500), "Impossible Game", sf::Style::None);
						while (helpWindow.isOpen())
						{
							windowMenu.setVisible(false);
							sf::Event eventHelp;
							while (helpWindow.pollEvent(eventHelp))
							{

								if ((eventHelp.type == sf::Event::Closed) || (eventHelp.key.code == sf::Keyboard::Escape))
								{
									helpWindow.close();
									windowMenu.setVisible(true);
								}
							}

							helpWindow.clear();

							helpWindow.draw(help);

							textH.setCharacterSize(50);
							textH.setString("Help");
							textH.setPosition(helpWindow.getSize().x - 480, 0);
							helpWindow.draw(textH);
							textH.setCharacterSize(20);
							textH.setColor(Color(133, 133, 133));
							textH.setString("The bottom line is that - jump over the \ncube through obstacles, \nclimb on the blocks, and in any case \nnot mistaken - \nwill start from the beginning!");
							textH.setPosition(10, 80);
							helpWindow.draw(textH);
							textH.setCharacterSize(15);
							textH.setColor(Color::White);
							textH.setString("Press ESC to return to the menu");
							textH.setPosition(10, helpWindow.getSize().y - 50);
							helpWindow.draw(textH);

							helpWindow.display();

						}
					}
						break;
					case 2:
						windowMenu.close();
						break;
					}
					break;
				}
				break;

			case sf::Event::Closed:
				windowMenu.close();

				break;
			}
		}

		windowMenu.clear();
		menu.draw(windowMenu, 3);

		text.setCharacterSize(50);
		text.setString("Impossible Game");
		text.setPosition(windowMenu.getSize().x - 520, 0);
		windowMenu.draw(text);
		text.setCharacterSize(15);
		text.setString("Created by Alex");
		text.setPosition(10, window.getSize().y - 30);
		windowMenu.draw(text);

		windowMenu.display();
	}
}