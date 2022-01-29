#include "GameObject.h"

void Item::spawn(int x,int y,int type)
{
	switch (type)
	{
	case 0:
		texture.loadFromFile("GAsset/Item1.png");
		sprite.setTexture(texture);
		printf("0");
		break;
	case 1:
		texture.loadFromFile("GAsset/Item2.png");
		sprite.setTexture(texture);
		printf("1");
		break;
	case 2:
		texture.loadFromFile("GAsset/Item3.png");
		sprite.setTexture(texture);
		printf("2");
		break;
	case 3:
		texture.loadFromFile("GAsset/Item4.png");
		sprite.setTexture(texture);
		printf("3");
		break;
	}
	this->type = type;
	sprite.setPosition(x, y);
	Alive = true;
}
void Item::getItem()
{
	Alive = false;
}
int Item::getType()
{
	return type;
}
FloatRect Item::getPosition()
{
	return sprite.getGlobalBounds();
}
bool Item::isAlive()
{
	return Alive;
}
Sprite Item::getSprite()
{
	return sprite;
}