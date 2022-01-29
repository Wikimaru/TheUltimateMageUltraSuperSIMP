#include <cstdlib>
#include <ctime>
#include "GameObject.h"

using namespace std;

void Spawner::spawnSpawner(int x,int y,int Amount,int type,int delay)
{
	position.x = x;
	position.y = y;
	this->delay=delay;
	spawnAmount = Amount;
	alreadySpawn = 0;
	texture.loadFromFile("GAsset/portal.png");
	sprite.setTexture(texture);
	sprite.setPosition(x,y);
	this->type = type;
	open = true;
}
bool Spawner::canSpawn(Time gameTimeTotal)
{
	if(gameTimeTotal.asMilliseconds()-lastSpawn.asMilliseconds()>1000*delay&&spawnAmount>=alreadySpawn&&open)
	{
		return true;
	}
	if(spawnAmount<alreadySpawn&&open)
	{
		open = false;
	}
	return false;
}
void Spawner::resetSpawntime(Time gameTimeTotal)
{
	alreadySpawn++;
	lastSpawn = gameTimeTotal;
}
bool Spawner::isOpen()
{
	return open;
}
Sprite Spawner::getSprite()
{
	return sprite;
}
void Spawner::destory()
{
	open = false;
}