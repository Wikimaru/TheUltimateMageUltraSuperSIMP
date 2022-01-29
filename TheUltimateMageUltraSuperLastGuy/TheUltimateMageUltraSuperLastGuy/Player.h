#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
class Player
{
private:
	//player state
	const float START_SPEED = 200;
	const float START_HEALTH = 100;
	int player_Health;
	Time player_LastHit;
	float player_Speed;

	//Player Position
	Vector2f player_Position;
	//Sprite
	Sprite player_sprite;
	Texture player_texture;

	//direction is the player currently moving in
	bool player_UpPressed;
	bool player_DownPressed;
	bool player_LeftPressed;
	bool player_RightPressed;


	//========game=========//
	Vector2f m_Resolution;
	IntRect m_Arena;
	int m_TileSize;

public:
	Player();

	void spawn(IntRect arena, Vector2f resolution, int tileSize);

	void resetPlayerStats();

	bool hit(Time timeHit,int Damage);

	Time getLastHitTime();

	FloatRect getPosition();

	Vector2f getCenter();

	float getRotation();

	Sprite getSprite();

	//player movement
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	//Stop the player moving in a specific direction
	void stopLeft();
	void stopRight();
	void stopUp();
	void stopDown();

	//Õ¬Ë“≈◊¡„ Ë„πmain loop#########################
	void update(float elapsedTime, Vector2i mousePosition);

	//Give player a speed boost
	void upgradeSpeed();

	//Give the player some Health
	void upgradeHealth();

	//increase the maximun amount of health the player can have
	void increaseHealthLevel(int amount);

	//How much health has the player currently got?
	int getHealth();

	Vector2f getPositionxy();

	void playerHeal(int Amount);

	int player_MaxHealth;
};