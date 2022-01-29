#include "Player.h"
Player::Player()
{
	player_Speed = START_SPEED;
	player_Health = START_HEALTH;
	player_MaxHealth = START_HEALTH;

	//sprite
	player_texture.loadFromFile("GAsset/player2.png");
	player_sprite.setTexture(player_texture);

	player_sprite.setOrigin(25, 25);
	
}
void Player::spawn(IntRect arena,Vector2f Resolution,int tileSize)
{
	//player spawn point
	player_Position.x = arena.width / 2;
	player_Position.y = arena.height / 2;

	//Arena data for player.h
	m_Arena.left = arena.left;
	m_Arena.width = arena.width;
	m_Arena.top = arena.top;
	m_Arena.height = arena.height;

	m_TileSize = tileSize;

	m_Resolution.x = Resolution.x;
	m_Resolution.y = Resolution.y;
	player_sprite.setPosition(player_Position);
}
void Player::resetPlayerStats()
{
	player_Speed = START_SPEED;
	player_Health = START_HEALTH;
	player_MaxHealth = START_HEALTH;
}
//=================player_damage_Zone===================//
Time Player::getLastHitTime()
{
	return player_LastHit;
}
bool Player::hit(Time timeHit,int Damage)
{
	if (timeHit.asMilliseconds() - player_LastHit.asMilliseconds() > 200)
	{
		player_LastHit = timeHit;
		player_Health -= Damage;
		return true;
	}
	else
	{
		return false;
	}
}
FloatRect Player::getPosition()
{
	return player_sprite.getGlobalBounds();
}
Vector2f Player::getCenter()
{
	return player_Position;
}
float Player::getRotation()
{
	return player_sprite.getRotation();
}

Sprite Player::getSprite()
{
	return player_sprite;
}

int Player::getHealth()
{
	return player_Health;
}

void Player::moveLeft()
{
	player_LeftPressed = true;
}

void Player::moveRight()
{
	player_RightPressed = true;
}

void Player::moveUp()
{
	player_UpPressed = true;
}

void Player::moveDown()
{
	player_DownPressed = true;
}

void Player::stopLeft()
{
	player_LeftPressed = false;
}

void Player::stopRight()
{
	player_RightPressed = false;
}

void Player::stopUp()
{
	player_UpPressed = false;
}

void Player::stopDown()
{
	player_DownPressed = false;
}

Vector2f normalize(Vector2f vec)
{
	float length = sqrt(vec.x * vec.x + vec.y * vec.y);
	return (length != 0) ? vec / length : Vector2f(0, 0);
}
float distance(Vector2f a, Vector2f b)
{
	Vector2f vec = a - b;
	return sqrt(vec.x * vec.x + vec.y * vec.y);
}
float vectorLength(Vector2f vec)
{
	return sqrt(vec.x * vec.x + vec.y * vec.y);
}
void Player::update(float elapsedTime, Vector2i mousePosition)
{
	// Rotate
	Vector2f velocity;
	if (player_UpPressed)
	{
		if (player_Position.y < m_Arena.top + m_TileSize)
		{
			velocity.y = 0;
		}
		else
		{
			velocity.y = -1;
		}
		//player_Position.y -= player_Speed * elapsedTime;

	}
	if (player_DownPressed)
	{
		if (player_Position.y > m_Arena.height - m_TileSize)
		{
			velocity.y = 0;
		}
		else
		{
			velocity.y = 1;
		}
		//player_Position.y += player_Speed * elapsedTime;

	}
	if (player_RightPressed)
	{
		if (player_Position.x > m_Arena.width - m_TileSize)
		{
			velocity.x = 0;
		}
		else
		{
			velocity.x = 1;
		}
		//player_Position.x += player_Speed * elapsedTime;

	}
	if (player_LeftPressed)
	{
		if (player_Position.x < m_Arena.left + m_TileSize)
		{
			velocity.x = 0;
		}
		else
		{
			velocity.x = -1;
		}
		//player_Position.x -= player_Speed * elapsedTime;

	}
	player_sprite.move(normalize(velocity) * player_Speed * elapsedTime);
	float angle = (atan2(mousePosition.y - m_Resolution.y / 2, mousePosition.x - m_Resolution.x / 2) * 180) / 3.141;
	player_sprite.setRotation(angle);
	player_Position = player_sprite.getPosition();

}
void Player::playerHeal(int Amount)
{
	player_Health += Amount;
	if(player_Health > player_MaxHealth)
	{
		player_Health = player_MaxHealth;
	}
}
void Player::upgradeHealth()
{
	player_MaxHealth += 10;
	playerHeal(10);
}
void Player::upgradeSpeed()
{
	player_Speed += 10;
}
