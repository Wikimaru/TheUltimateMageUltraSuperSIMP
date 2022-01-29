#include "MENU.h"
#include <SFML/Graphics.hpp>

void MENU::NewMENU()
{
	MenuTexture.loadFromFile("GAsset/MenuBackground.png");
	PlayTexture[0].loadFromFile("GAsset/PlayButton1.png");
	PlayTexture[1].loadFromFile("GAsset/PlayButton2.png");
	ScoreTexture[0].loadFromFile("GAsset/ScoreButton1.png");
	ScoreTexture[1].loadFromFile("GAsset/ScoreButton2.png");
	ExitTexture[0].loadFromFile("GAsset/ExitButton1 .png");
	ExitTexture[1].loadFromFile("GAsset/ExitButton2.png");
	ScoreBackGroundTexture.loadFromFile("GAsset/HiScoreBackground.png");
	NameInputTexture.loadFromFile("GAsset/GameOverBackGround.png");

	MenuBackGround.setTexture(MenuTexture);
	PlayButton[0].setTexture(PlayTexture[0]);
	PlayButton[1].setTexture(PlayTexture[1]);
	ScoreButton[0].setTexture(ScoreTexture[0]);
	ScoreButton[1].setTexture(ScoreTexture[1]);
	ExitButton[0].setTexture(ExitTexture[0]);
	ExitButton[1].setTexture(ExitTexture[1]);
	PlayButton[0].setPosition(125,300);
	PlayButton[1].setPosition(125, 300);
	ScoreButton[0].setPosition(125, 450);
	ScoreButton[1].setPosition(125, 450);
	ExitButton[0].setPosition(125, 600);
	ExitButton[1].setPosition(125, 600);
	ScoreBackGround.setTexture(ScoreBackGroundTexture);
	NameInputBackGround.setTexture(NameInputTexture);
}
void MENU::updateMenu()
{
	switch (scene)
	{
	case 0:
		if (Keyboard::isKeyPressed(Keyboard::W)&&!isPressW)
		{
			isPressW = true;
			Button--;
			if(Button<0)
			{
				Button = 0;
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::S)&&!isPressS)
		{
			isPressS = true;
			Button++;
			if (Button > 2)
			{
				Button = 2;
			}
		}
		if(!Keyboard::isKeyPressed(Keyboard::W)&&isPressW)
		{
			isPressW = false;
		}
		if(!Keyboard::isKeyPressed(Keyboard::S)&&isPressS)
		{
			isPressS = false;
		}

		if(Button==0)
		{
			SpriteButton[0] = PlayButton[1];
			SpriteButton[1] = ScoreButton[0];
			SpriteButton[2] = ExitButton[0];
		}
		if (Button == 1)
		{
			SpriteButton[0] = PlayButton[0];
			SpriteButton[1] = ScoreButton[1];
			SpriteButton[2] = ExitButton[0];
		}
		if (Button == 2)
		{
			SpriteButton[0] = PlayButton[0];
			SpriteButton[1] = ScoreButton[0];
			SpriteButton[2] = ExitButton[1];
		}


		break;
	case 1:
		break;
	case 2:
		break;
	default:
		break;
	}

	if(Keyboard::isKeyPressed(Keyboard::Space)&&!isPressOK)
	{
		isPressOK = true;
		select(Button);
	}
	if(!Keyboard::isKeyPressed(Keyboard::Space)&&isPressOK)
	{
		isPressOK = false;
	}
}
void MENU::select(int selectButton)
{
	int selectB = selectButton;
	if(selectB==0)
	{
		GameBegin = true;
	}
	if (selectB == 1)
	{
		seeScore = !seeScore;
	}
	if (selectB == 2)
	{
		Exit = true;
	}
}
bool MENU::isStartGame()
{
	return GameBegin;
}
void MENU::hasStart()
{
	GameBegin = false;
}
bool MENU::ExitGame()
{
	return Exit;
}
bool MENU::ScoreScene()
{
	return seeScore;
}
