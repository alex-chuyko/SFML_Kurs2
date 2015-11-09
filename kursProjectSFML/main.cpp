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

	sf::Font font;
	font.loadFromFile("neuropol_x.ttf");
	sf::Text text("", font, 40);
	text.setColor(sf::Color::White);
	text.setStyle(sf::Text::Bold);

	sf::RenderWindow window(sf::VideoMode(600, 600), "Impossible Game"); //800 640


	Menu menu(window.getSize().x, window.getSize().y);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch(event.type)
			{
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					menu.MoveUp();
					break;

				case sf::Keyboard::Down:
					menu.MoveDown();
					break;

				case sf::Keyboard::Return:
					switch (menu.GetPressedItem())
					{
					case 0: 
						CreatePlayWindow();
						break;
					case 1:
						break;
					case 2:
						window.close();
						break;
					}
					break;
				}
				break;

			case sf::Event::Closed:
				window.close();

				break;
			}
		}

		window.clear();
		menu.draw(window);

		text.setString("My Game");
		text.setPosition(window.getSize().x - 400, 0);
		window.draw(text);

		window.display();
	}
}







/*#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "view.h"
#include "level.h"
#include <vector>
#include <sstream>
#include <Windows.h>

using namespace sf;

class Kub
{
//private: float x, y = 0;
public:
	float x, y = 0;
	std::vector<Object> obj;
	float w, h, dx, dy;
	bool onGround, life = true;
	int playerDeath, upDown = 1;
	Music music;
	String File;
	Image image;
	Texture texture;
	Sprite sprite;
	float CurrentFrame = 0;

	Kub(String F, Level &lev,  float X, float Y, float W, float H){
		
		music.openFromFile("music/musicLevel1.ogg");
		music.play();
		obj = lev.GetAllObjects();
		playerDeath = 0;
		dx = 0.22; dy = 0;
		onGround = false;
		life = true;
		File = F;
		w = W; h = H;
		image.loadFromFile("images/" + File);
		image.createMaskFromColor(Color(255, 255, 255));
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setTextureRect(IntRect(0, 0, 32, 32));
		x = X; y = Y;
	}

	void update(float time){
		control(time);
		x += dx*time;
		checkCollision(dx, 0);
		if (!life)
		{
			playerDeath++;
			life = true;
		}
		y += dy*time;
		sprite.setPosition(x, y);
		if (!onGround) {
			//sprite.setOrigin(w / 2, h / 2);
			//sprite.rotate(0.5*time);
			//sprite.setOrigin(0, 0);
			dy = dy + 0.0028*time* upDown;
		}
		onGround = false;
		checkCollision(0, dy);
	}

	float getplayercoordinateX(){
		return x;
	}
	float getplayercoordinateY(){	
		return y;
	}

	void control(float time){
		if (((Keyboard::isKeyPressed(Keyboard::Up)) || (Keyboard::isKeyPressed(Keyboard::Space))) && onGround){
			dy = -0.7 * upDown;
			dx = 0.22;
			onGround = false; 
		}
	}

	void checkCollision(float Dx, float Dy){
		for (int i = 0; i < obj.size(); i++)
			if (getRect().intersects(obj[i].rect)) 
			{
				if (obj[i].name == "solid")
				{
					if ((Dy * upDown) > 0) { y = obj[i].rect.top - h * upDown; dy = 0; onGround = true; }
					//if ((Dy * upDown) < 0) { y = obj[i].rect.top + obj[i].rect.height; dy = 0; onGround = false; }
					if (Dx > 0) { x = obj[i].rect.left - w; x = 32; y = 250; life = false; music.stop(); music.play(); upDown = 1; }
				}
				else
				{
					if (obj[i].name == "death"){
						x = obj[i].rect.left - w; x = 32; y = 250;
						life = false;
						music.stop();
						music.play();
						upDown = 1;
					}
					else
					{
						/*if (obj[i].name == "finish"){
							//Level lvl;
							//lvl.LoadFromFile("test30.tmx");
							//obj.clear();
							//obj = lvl.GetAllObjects();
							//x = obj[i].rect.left - w; x = 32; y = 250;
							playerDeath = 0;
							upDown = 1;
						}
						else
						{
							if (obj[i].name == "down"){
								upDown *= -1;
								x = 512; y = 416;
							}
						//}
					}
				}
				break;
			}
	}

	FloatRect getRect(){
		return FloatRect(x, y, w, h);
	}
};*/


/*int main()
{
	//HWND hWnd = GetConsoleWindow();
	//ShowWindow(hWnd, SW_HIDE);

	int levelNum = 1;
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
	background.setTextureRect(sf::IntRect(0, 0, 14000, 860));
	

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


		if (k.x > finish.rect.left){
			levelNum++;
			lvl.ClearObjects();
			lvl.ClearLayers();
			levelFile = "Levels/level" + std::to_string(levelNum);
			levelFile += ".tmx";
			lvl.LoadFromFile(levelFile);
			player = lvl.GetObj("player");
			finish = lvl.GetObj("finish");
			k.x = player.rect.left;
			k.y = player.rect.top;
			k.playerDeath = 0;
			k.upDown = 1;
			k.obj.clear();
			k.obj = lvl.GetAllObjects();
		}

		

		window.draw(k.sprite);
		lvl.Draw(window);
		window.display();

		getplayercoordinateforview(k.getplayercoordinateX(), k.getplayercoordinateY());
		k.update(time);
		window.draw(k.sprite);
		window.setView(view);
		window.clear();
		window.draw(background);
		
		std::ostringstream playerScoreString;
		playerScoreString << k.playerDeath;
		text.setString("Attempt " + playerScoreString.str());
		text.setPosition(view.getCenter().x - 75, view.getCenter().y - 290);
		window.draw(text);
		
		
	}

	return 0; 
}*/

/*if (!k.life)
{
k.playerDeath++;
k.image.loadFromFile("images/dieAnim.png");
k.image.createMaskFromColor(Color(255, 255, 255));
k.texture.loadFromImage(k.image);
k.sprite.setTexture(k.texture);
k.dx = 0;
for (int i = 0; i < 5; i++)
{
k.sprite.setTextureRect(IntRect(64 * i, 0, 64, 64));
window.draw(k.sprite);
window.display();
}
k.life = true;
k.dx = 0.22;
}*/