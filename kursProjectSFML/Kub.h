#pragma once
#include <SFML/Graphics.hpp>
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
public:
	Kub(String F, Level &lev, float X, float Y, float W, float H);
	~Kub();
	void update(float time);
	float getplayercoordinateX();
	float getplayercoordinateY();
	void control(float time);
	void checkCollision(float Dx, float Dy);
	FloatRect getRect();
	Object checkFinish(Object player, Object finish, Level &lvl);
	void draw(RenderWindow &window, Level &lvl, Text text, Sprite background, float time);

private:
	float x, y = 0;
	int levelNum = 1;
	std::vector<Object> obj;
	float w, h, dx, dy;
	bool onGround, life = true;
	int playerDeath, upDown = 1;
	Music music;
	String File;
	Image image;
	Texture texture;
	Sprite sprite;
};

