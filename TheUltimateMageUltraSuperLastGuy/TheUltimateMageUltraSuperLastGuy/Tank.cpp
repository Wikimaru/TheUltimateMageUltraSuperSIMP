#include "GameObject.h"
#include <cstdlib>
#include <ctime>

using namespace std;

void Tank::spawn(int x,int y)
{
	texture.loadFromFile("GAsset/tank.png");
	sprite.setTexture(texture);
	sprite.setOrigin(48,42);
	sprite.setPosition(x, y);
	position.x = x;
	position.y = y;
	Alive = true;
}
void Tank::update(float elapsedTime)
{
	if(position.x<-1000&&Alive)
	{
		Alive = false;
	}
	if(Alive)
	{
		position.x = position.x - speed * elapsedTime;
		//position.x--;
		sprite.setPosition(position);
	}

}
FloatRect Tank::getPosition()
{
	return sprite.getGlobalBounds();
}
bool Tank::isAlive()
{
	return Alive;
}
Sprite Tank::getSprite()
{
	return sprite;
}