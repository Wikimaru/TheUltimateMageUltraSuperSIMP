#include <cstdlib>
#include <ctime>
#include "Infected.h"
#include "TextureHolder.h"

using namespace std;

void infected::spawn(float startX,float startY,int type,int seed)
{
	switch(type)
	{
	case 0:
		//Alpha
		infected_texture.loadFromFile("GAsset/Enemy.png");
		infected_Sprite.setTexture(infected_texture);
		infected_Speed = 60;
		infected_health = 1;
		break;
	case 1:
		infected_texture.loadFromFile("GAsset/Enemy2.png");
		infected_Sprite.setTexture(infected_texture);
		infected_Speed = 300;
		infected_health = 1;
		break;
	case 2:
		infected_texture.loadFromFile("GAsset/Enemy3.png");
		infected_Sprite.setTexture(infected_texture);
		infected_Speed = 120;
		infected_health = 2;
		break;
	case 3:
		infected_texture.loadFromFile("GAsset/Enemy4.png");
		infected_Sprite.setTexture(infected_texture);
		infected_Speed = 45;
		infected_health = 4;
		break;
	}

	srand((int)time(0) * seed);

	float modifier = (rand() & MAX_VARRIANCE) + OFFSET;

	modifier /= 100;
	infected_Speed *= modifier;
	infected_Position.x = startX;
	infected_Position.y = startY;
	infected_Sprite.setOrigin(25, 25);
	infected_Sprite.setPosition(infected_Position);
	infected_Alive = true;
}

bool infected::hit()
{
	infected_health--;
	if(infected_health <= 0)
	{
		infected_Alive = false;
		//infected_texture.loadFromFile("GAsset/blood.png");
		//infected_Sprite.setTexture(infected_texture);

		return true;
	}
	return false;
}

bool infected::isAlive()
{
	return infected_Alive;
}

FloatRect infected::getPosition()
{
	return infected_Sprite.getGlobalBounds();
}

Sprite infected::getSprite()
{
	return infected_Sprite;
}
//Vector2f normalize(Vector2f vec)
//{
//	float length = sqrt(vec.x * vec.x + vec.y * vec.y);
//	return (length != 0) ? vec / length : Vector2f(0, 0);
//}

void infected::update(float elapsedTime,Vector2f playerLocation)
{
	float playerX = playerLocation.x;
	float playerY = playerLocation.y;
	Vector2f velocity;
	if (playerX > infected_Position.x)
	{
		infected_Position.x = infected_Position.x + infected_Speed * elapsedTime;
		velocity.x = 1;
	}
	if (playerY > infected_Position.y)
	{
		infected_Position.y = infected_Position.y + infected_Speed * elapsedTime;
		velocity.y = 1;
	}
	if (playerX < infected_Position.x)
	{
		infected_Position.x = infected_Position.x - infected_Speed * elapsedTime;
		velocity.x = -1;
	}
	if (playerY < infected_Position.y)
	{
		infected_Position.y = infected_Position.y - infected_Speed * elapsedTime;
		velocity.y = 1;
	}
	//infected_Sprite.move(normalize(velocity) * infected_Speed * elapsedTime);
	infected_Sprite.setPosition(infected_Position);
	float angle = (atan2(playerY - infected_Position.y, playerX - infected_Position.x) * 180) / 3.141;
	infected_Sprite.setRotation(angle);
}

infected infected_Spawn(Vector2f SpawnPosition, int type,int numinfected)
{
	float x=SpawnPosition.x, y=SpawnPosition.y;
	infected Infected;
	Infected.spawn(x, y, type, 1);
	return Infected;
}

void infected::Destory()
{
	infected_Alive = false;
}