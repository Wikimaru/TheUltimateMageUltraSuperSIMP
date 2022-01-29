#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Spawner
{
private:
	Texture texture;
	Sprite sprite;
	int spawnAmount;
	int alreadySpawn;
	float delay;
	bool open;
	Time lastSpawn;
public:
	Vector2f position;
	int type;
	void spawnSpawner(int x,int y,int Amount,int type,int delay);
	bool canSpawn(Time gameTimeTotal);
	void resetSpawntime(Time gameTimeTotal);
	bool isOpen();
	Sprite getSprite();
	void destory();
};
class Item
{
private:
	Texture texture;
	Sprite sprite;
	int type;
	Vector2f position;
	bool Alive = false;
public:
	void spawn(int x,int y,int type);
	void getItem();
	int getType();
	FloatRect getPosition();
	bool isAlive();
	Sprite getSprite();
};
class Tank
{
private: 
	Vector2f position;
	Texture texture;
	Sprite sprite;
	bool Alive = false;
	const float speed = 150;
public:
	void spawn(int x, int y);
	void update(float elapsedTime);
	FloatRect getPosition();
	bool isAlive();
	Sprite getSprite();
};
class Bullet
{
private: 
	Vector2f m_Position;
	RectangleShape m_BulletShape;
	Sprite sprite[2];
	Texture texture[2];
	bool m_Inflight = false;
	float m_BulletSpeed = 1000;
	float m_BulletDistanceX;
	float m_BulletDistanceY;
	float m_MaxX;
	float m_MinX;
	float m_MaxY;
	float m_MinY;
public:

	Bullet();

	void stop();

	bool isInFlight();

	void shoot(float startX, float startY, float xTarget, float yTarget);

	FloatRect getPosition();

	RectangleShape getShape();

	void update(float elapsedTime);

	Sprite getSprite(int type);
};