#include "Kub.h"
#include "Menu.h"


Kub::Kub(String F, Level &lev, float X, float Y, float W, float H)
{
	music.openFromFile("music/musicLevel1.ogg");
	music.play();
	obj = lev.GetAllObjects();
	playerDeath = 0;
	dx = 0.22; 
	dy = 0;
	onGround = false;
	life = true;
	File = F;
	w = W; 
	h = H;
	image.loadFromFile("images/" + File);
	image.createMaskFromColor(Color(255, 255, 255));
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(0, 0, 32, 32));
	x = X; 
	y = Y;
}


Kub::~Kub()
{
}


void Kub::update(float time)
{
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
	if (!onGround)
	{
		dy = dy + 0.0028*time* upDown;
	}
	onGround = false;
	checkCollision(0, dy);
}

float Kub::getplayercoordinateX()
{
	return x;
}

float Kub::getplayercoordinateY()
{
	return y;
}

void Kub::control(float time)
{
	if (((Keyboard::isKeyPressed(Keyboard::W)) || (Keyboard::isKeyPressed(Keyboard::Space))) && onGround)
	{
		dy = -0.7 * upDown;
		dx = 0.22;
		onGround = false;
	}
}

void Kub::checkCollision(float Dx, float Dy)
{
	for (int i = 0; i < obj.size(); i++)
		if (getRect().intersects(obj[i].rect))
		{
			if (obj[i].name == "solid")
			{
				if ((Dy * upDown) > 0) 
				{ 
					y = obj[i].rect.top - h * upDown; 
					dy = 0; 
					onGround = true; 
				}
				if (Dx > 0) 
				{ 
					x = obj[i].rect.left - w; 
					x = 32; 
					y = 250; 
					life = false; 
					music.stop(); 
					music.play(); 
					upDown = 1;
				}
			}
			else
			{
				if (obj[i].name == "death")
				{
					x = obj[i].rect.left - w; x = 32; y = 250;
					life = false;
					music.stop();
					music.play();
					upDown = 1;
				}
				else
				{
					if (obj[i].name == "down")
					{
						upDown *= -1;
						x = 512; y = 416;
						
					}

				}
			}
		}
}

FloatRect Kub::getRect()
{
	return FloatRect(x, y, w, h);
}

Object Kub::checkFinish(Object player, Object finish, Level &lvl, sf::RenderWindow &window, sf::RenderWindow &windowMenu)
{
	String levelFile, musicFile;
	if (x > finish.rect.left)
	{
		levelNum++;
		if (levelNum < 3)
		{
			lvl.ClearObjects();
			lvl.ClearLayers();
			levelFile = "Levels/level" + std::to_string(levelNum);
			levelFile += ".tmx";
			lvl.LoadFromFile(levelFile);
			player = lvl.GetObj("player");
			finish = lvl.GetObj("finish");
			musicFile = "music/musicLevel" + std::to_string(levelNum) + ".ogg";
			music.openFromFile(musicFile);
			music.play();
			x = player.rect.left;
			y = player.rect.top;
			playerDeath = 0;
			upDown = 1;
			obj.clear();
			obj = lvl.GetAllObjects();
		}
		else
		{
			window.close();
			windowMenu.setVisible(true);
		}
	}
	return finish;
}

void Kub::draw(RenderWindow &window, Level &lvl, Text text, Sprite background, float time, Text textLvl)
{
	window.draw(sprite);
	lvl.Draw(window);
	window.display();

	window.draw(sprite);
	update(time);
	window.clear();
	window.draw(background);

	std::ostringstream playerScoreString, levelNumString;
	levelNumString << levelNum;
	playerScoreString << playerDeath;
	text.setString("Attempt " + playerScoreString.str());
	textLvl.setString("Level " + levelNumString.str());
	window.draw(text);
	window.draw(textLvl);
}

