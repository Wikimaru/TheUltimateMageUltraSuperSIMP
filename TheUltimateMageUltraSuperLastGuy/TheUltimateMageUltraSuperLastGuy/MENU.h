#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class MENU
{
private:

	Sprite PlayButton[2],ScoreButton[2],ExitButton[2];


	Texture MenuTexture;
	Texture PlayTexture[2], ScoreTexture[2], ExitTexture[2];
	Texture ScoreBackGroundTexture;
	Texture NameInputTexture;

	int Button=0,scene=0;
	bool isPressW = false, isPressS = false, GameBegin = false, Exit = false, seeScore = false;;

	void select(int selectButton);
public:
	void NewMENU();
	void updateMenu();
	bool isStartGame();
	void hasStart();
	bool ExitGame();
	bool ScoreScene();
	Sprite SpriteButton[3];
	Sprite MenuBackGround;
	Sprite NameInputBackGround;
	Sprite ScoreBackGround;
	bool isPressOK = false;
};