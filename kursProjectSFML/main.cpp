#include <SFML/Graphics.hpp>
#include <iostream>
//#include "map.h"
#include "view.h"
#include "level.h"
#include <vector>
#include <sstream>

using namespace sf;

class Kub
{
private: float x, y = 0;
public:
	std::vector<Object> obj;
	float w, h, dx, dy, speed = 0;
	bool onGround, life;
	int playerDeath;
	String File;
	Image image;
	Texture texture;
	Sprite sprite;

	Kub(String F, Level &lev,  float X, float Y, float W, float H){
		obj = lev.GetAllObjects();
		playerDeath = 0;
		dx = 0.15; dy = 0;
		onGround = false;
		life = true;
		File = F;
		w = W; h = H;
		image.loadFromFile("images/" + File);
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		x = X; y = Y;
	}

	void update(float time){
		control();
		x += dx*time;
		checkCollision(dx, 0);
		y += dy*time;
		speed = 0;
		sprite.setPosition(x, y);
		if (!onGround) { dy = dy + 0.0013*time; }
		onGround = false;
		checkCollision(0, dy);
	}

	float getplayercoordinateX(){
		return x;
	}
	float getplayercoordinateY(){	
		return y;
	}

	void control(){
		if ((Keyboard::isKeyPressed(Keyboard::Up)) && onGround){
			dy = -0.5;
			//dx = 0.1;
			onGround = false;
		}
	}

	void checkCollision(float Dx, float Dy){
		for (int i = 0; i < obj.size(); i++)
			if (getRect().intersects(obj[i].rect)) 
			{
				if (obj[i].name == "solid")
				{
					if (Dy > 0) { y = obj[i].rect.top - h; dy = 0; onGround = true; }
					if (Dy < 0) { y = obj[i].rect.top + obj[i].rect.height; dy = 0; onGround = false; }
					if (Dx > 0) { x = obj[i].rect.left - w; x = 86; y = 559; playerDeath++; }
				}

				if (obj[i].name == "death"){
					x = obj[i].rect.left - w; x = 86; y = 559;
					playerDeath++;
				}

				if (obj[i].name == "finish"){
					x = obj[i].rect.left - w; x = 86; y = 559;
					playerDeath = 0;
				}
			}
	}


	FloatRect getRect(){
		return FloatRect(x, y, w, h);
	}
};


int main()
{
	Level lvl;
	lvl.LoadFromFile("map.tmx");

	Font font;
	font.loadFromFile("birdman_bold.ttf");
	Text text("", font, 30);
	text.setColor(Color::White);
	text.setStyle(sf::Text::Bold);

	sf::RenderWindow window(sf::VideoMode(800, 640), "Impossible Game");
	view.reset(sf::FloatRect(0, 0, 800, 640));


	

	Object player = lvl.GetObject("player");


	Texture t;
	t.loadFromFile("images/background.jpg");
	Sprite background;
	background.setTexture(t);
	

	Kub k("kub.png", lvl, player.rect.left, player.rect.top, 43, 43);

	
	

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

		getplayercoordinateforview(k.getplayercoordinateX(), k.getplayercoordinateY());
		k.update(time);
		window.setView(view);
		window.clear();
		window.draw(background);
		
		lvl.Draw(window);

		std::ostringstream playerScoreString;
		playerScoreString << k.playerDeath;
		text.setString("Attempt " + playerScoreString.str());
		text.setPosition(view.getCenter().x - 75, view.getCenter().y - 300);
		window.draw(text);
		

		window.draw(k.sprite);
		window.display();
	}

	return 0; 
}












//ASCII art

/*#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>  

//using namespace sf;


int main()
{
	sf::RenderWindow window(sf::VideoMode(600, 540), "Project");

	sf::Image img;
	img.loadFromFile("images/and.jpg");
	
	int height = 439, width = 604;

	sf::Color cl, cl2,cl3,cl4,cl5,cl6,cl7,cl8, cl9;


	for (int i = 0; i < width; ++i)
		for (int j = 0; j < height; ++j)
		{
			cl = img.getPixel(i,j);
			cl.b = cl.r*0.2125 + cl.b*0.0721 + cl.g*0.7154;
			cl.g = cl.r*0.2125 + cl.b*0.0721 + cl.g*0.7154;
			cl.r = cl.b*0.0721 + cl.r*0.2125 + cl.g*0.7154;
			img.setPixel(i, j, cl);
		}
			
	sf::Texture imag;
	imag.loadFromImage(img);
	sf::Sprite imgSpr;
	imgSpr.setTexture(imag);

	int b = 0;

	std::ofstream fout;
	fout.open("output.txt");
	for (int i = 0; i < (height-2); i += 2)
	{
		for (int j = 0; j < (width-2); j += 1)
		{
			cl = img.getPixel(j, i);
			cl2 = img.getPixel(j+1, i);
			cl3 = img.getPixel(j, i+1);
			cl4 = img.getPixel(j+1, i+1);
			cl5 = img.getPixel(j + 2, i + 2);
			cl6 = img.getPixel(j , i + 2);
			cl7 = img.getPixel(j + 2, i);
			cl8 = img.getPixel(j + 1, i + 2);
			cl9 = img.getPixel(j + 2, i + 1);
			b = ((cl.b + cl.g + cl.r) + (cl2.b + cl2.g + cl2.r) + (cl3.b + cl3.g + cl3.r) + (cl4.b + cl4.g + cl4.r) + (cl5.b + cl5.g + cl5.r) + (cl6.b + cl6.g + cl6.r) + (cl7.b + cl7.g + cl7.r) + (cl8.b + cl8.g + cl8.r) + (cl9.b + cl9.g + cl9.r)) / 81;
			if (b < 5) fout << "¨";
			else
				if (b < 10) fout << "@";
				else
					if (b < 15) fout << "Ø";
					else
						if (b < 20) fout << "$";
						else
							if (b < 25)	fout << "&";
							else
								if (b < 30)	fout << "#";
								else
									if (b < 35)	fout << "¤";
									else
										if (b < 40)	fout << "~";
										else
											if (b < 45)	fout << "´";
											else
												if (b < 50) fout << ".";
												else
													fout << " ";
		}
		fout << "\n";
	}
	fout.close();



	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(imgSpr);
		window.display();
	}

	return 0;
}*/