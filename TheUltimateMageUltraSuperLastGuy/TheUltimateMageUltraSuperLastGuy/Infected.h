#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class infected
{
private:
	//==============Status Zone=================//
	//SPEED
	const float ALPHA_SPEED = 50;

	//HEALTH
	const float ALPHA_HEALTH = 5;

	//speed slighty
	const int MAX_VARRIANCE = 30;
	const int OFFSET = 101 - MAX_VARRIANCE;

	//=========================================//
	Vector2f infected_Position;
	Texture infected_texture;
	Sprite infected_Sprite;
	float infected_Speed;
	float infected_health;
	bool infected_Alive;

public:
	bool hit();

	bool isAlive();

	void spawn(float startX, float startY, int type, int seed);

	FloatRect getPosition();

	Sprite getSprite();

	void update(float elapsedTime, Vector2f playerLocation);

	infected infected_Spawn(Vector2f SpawnPosition,int type, int numinfected);

	void Destory();

 };