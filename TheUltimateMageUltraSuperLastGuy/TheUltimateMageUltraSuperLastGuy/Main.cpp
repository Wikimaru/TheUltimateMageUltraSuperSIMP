#include <SFML/Graphics.hpp>
#include "Player.h"
#include "CreateBackground.h"
#include "Infected.h"
#include "GameObject.h"
#include <sstream>
#include <fstream>
#include "MENU.h"
#include <SFML/Audio.hpp>

using namespace sf;
int randrange(int start, int stop);
void collision();
void playerShootBullet();
void loadScore();
void PlayerController();
void AllUpdate(Time dt, Vector2f playerPosition);
void DebugCommand();
void playerGetItem(int type);
void summonItem(int x, int y, int type);
void saveScore();
void updatescoreBoard();
int numInfected = 0, numSpawner = 0, maxInfected = 100, maxSpawner = 15,numItem = 0,maxItem = 15;
infected* Infected = new infected[100];
Bullet bullet[100];
Spawner* portal = new Spawner[15];
Tank* tank = new Tank[1];
Item* item = new Item[15];
void spawnInfected(int x, int y, int type, int seed);
void summonSpawner(int x, int y, int Amount, int type, int delay);
Time gameTimeTotal,lastSpawn[2];
int TimeToSpawn[2];
//=========name and text=============//
Text PlayerName[5],PlayerScore[5],PlayerNameInput,InputYourName,ShowScore;
String NameInput;
Font font;
bool isPressNameinput;
Time inputNameTimer;
//==================================//
enum class sceneManager
{
	START_MENU, MAIN_GAME, PAUSE_GAME, GAME_OVER, HI_SCORE, NAME_INPUT
};
sceneManager scene = sceneManager::START_MENU;
Player player;
IntRect arena;
VertexArray background;
Texture textureBackground;
Vector2f mouseWorldPosition;
Vector2i mouseScreenPosition;
//Gun
int currentBullet = 0;
float fireRate = 1;
Time lastPressed;
RectangleShape HealthBar,HealthBarBackground;
int score[6];
std::string loadPlayerName[6];
int current_score = 0;

MENU menu;

SoundBuffer BMGBuffer,ShootBuffer,GetItemBuffer,hitBuffer,menuBuffer;
Sound BMGMusic,Shootsound,GetItemSound,hitSound,menuMusic;

int main()
{	

	BMGBuffer.loadFromFile("GAsset/BMG.wav");
	BMGMusic.setBuffer(BMGBuffer);
	BMGMusic.setLoop(true);
	ShootBuffer.loadFromFile("GAsset/Shoot.wav");
	Shootsound.setBuffer(ShootBuffer);
	GetItemBuffer.loadFromFile("GAsset/Get2.wav");
	hitBuffer.loadFromFile("GAsset/Hit.wav");
	GetItemSound.setBuffer(GetItemBuffer);
	hitSound.setBuffer(hitBuffer);
	menuBuffer.loadFromFile("GAsset/MenuBMG.wav");
	menuMusic.setBuffer(menuBuffer);
	menuMusic.setLoop(true);
	loadScore();
	updatescoreBoard();
	HealthBar.setFillColor(Color::Red);
	HealthBar.setOutlineThickness(2);
	HealthBar.setOutlineColor(Color::Black);
	HealthBarBackground.setFillColor(Color::White);
	HealthBarBackground.setOutlineThickness(2);
	HealthBarBackground.setOutlineColor(Color::Black);
	ShowScore.setCharacterSize(48);
	ShowScore.setFillColor(Color::Blue);
	ShowScore.setFont(font);
	//Get the screen resolution and create an SFML window//เก็บค่าขนาดwindow
	Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;
	RenderWindow window(VideoMode(resolution.x, resolution.y), "TheUltimateMageUltraSuperLastSIMP", Style::Fullscreen);
	Clock clock;
	//create a an SFML View for the main action
	View mainView(sf::FloatRect(0, 0, resolution.x, resolution.y));
	View menuView(sf::FloatRect(0, 0, resolution.x, resolution.y));
	textureBackground.loadFromFile("GAsset/Background.png");
	menu.NewMENU();
	//main loop
	window.setFramerateLimit(60);
	int Debug[10];
	menuMusic.play();
	while (window.isOpen())
	{
		//Keyboard_controll//
		//======DeBug======//
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Return && scene == sceneManager::MAIN_GAME)
				{
					scene = sceneManager::PAUSE_GAME;
				}
				if (event.key.code == Keyboard::Return && scene == sceneManager::PAUSE_GAME)
				{
					scene = sceneManager::MAIN_GAME;
					clock.restart();
				}
				if (event.key.code == Keyboard::Escape)
				{
					window.close();
				}
			}
		}
		//ifควบคุมตัวละคร
		if (scene == sceneManager::MAIN_GAME)
		{
			//ifควบคุมการเครื่อนไหว
			PlayerController();
			//End_ifควบคุมการเครื่อนไหว
		}


		//ifเริ่มเกม
		if (scene == sceneManager::START_MENU)
		{
			menu.updateMenu();
			if (event.key.code == Keyboard::Num1||menu.isStartGame())
			{
				menu.hasStart();
				BMGMusic.play();
				menuMusic.stop();
				scene = sceneManager::MAIN_GAME;
				printf("Start_game");
			}
			if (scene == sceneManager::MAIN_GAME)
			{
				arena.width = 1500;
				arena.height = 1200;
				arena.left = 0;
				arena.top = 0;
				int tileSize = createBackground(background, arena);
				fireRate = 1;
				player.resetPlayerStats();
				player.spawn(arena, resolution, tileSize);
				for(int i=0;i<maxInfected;i++)
				{
					Infected[i].Destory();
				}
				for(int i=0;i<maxSpawner;i++)
				{
					portal[i].destory();
				}
				summonSpawner(randrange(40, 1460), randrange(40, 1160), randrange(4, 8), 0, randrange(3, 9));
				summonSpawner(randrange(40, 1460), randrange(40, 1160), randrange(4, 8), 0, randrange(3, 9));
				HealthBarBackground.setSize(Vector2f(player.player_MaxHealth * 3, 25));
				clock.restart();
			}
			if(menu.ExitGame())
			{
				window.close();
			}
		}
		//====================//
		//==UPDATE THE FRAME==//
		//====================//
		Time dt = clock.restart();
		gameTimeTotal += dt;
		if (scene == sceneManager::MAIN_GAME)
		{
			float dtAsSeconds = dt.asSeconds();
			mouseScreenPosition = Mouse::getPosition();
			mouseWorldPosition = window.mapPixelToCoords(Mouse::getPosition(), mainView);
			player.update(dtAsSeconds, Mouse::getPosition());
			Vector2f playerPosition(player.getCenter());
			mainView.setCenter(player.getCenter());


			AllUpdate(dt,player.getCenter());
			collision();
			
		}
		DebugCommand();
		//=============================================//
		if (scene == sceneManager::MAIN_GAME)
		{
			window.clear();
			window.setView(mainView);
			window.draw(background, &textureBackground);
			for(int i = 0;i< maxSpawner;i++)
			{
				if(portal[i].isOpen())
				{
					window.draw(portal[i].getSprite());
				}
			}
			for (int i = 0; i < maxInfected; i++)
			{
				if(Infected[i].isAlive())
				{
					window.draw(Infected[i].getSprite());
				}
			}
			for(int i = 0;i<maxItem;i++)
			{
				if(item[i].isAlive())
				{
					window.draw(item[i].getSprite());
				}
			}
			if(tank[0].isAlive())
			{
				window.draw(tank[0].getSprite());
			}
			for (int i = 0; i < 100; i++)
			{
				if (bullet[i].isInFlight())
				{
					//window.draw(bullet[i].getShape());
					window.draw(bullet[i].getSprite(0));
				}
			}
			window.draw(HealthBarBackground);
			window.draw(HealthBar);
			window.draw(ShowScore);
			window.draw(player.getSprite());
		}
		if(scene == sceneManager::START_MENU)
		{
			window.clear();
			window.draw(menu.MenuBackGround);
			if(menu.ScoreScene())
			{
				window.draw(menu.ScoreBackGround);
				for(int i=0;i<5;i++)
				{
					window.draw(PlayerName[i]);
					window.draw(PlayerScore[i]);
				}

			}
			window.draw(menu.SpriteButton[0]);
			window.draw(menu.SpriteButton[2]);
			window.draw(menu.SpriteButton[1]);
		}
		if(scene == sceneManager::GAME_OVER)
		{
			window.setView(menuView);
			window.draw(menu.NameInputBackGround);
				if(event.type==Event::TextEntered&&!isPressNameinput)
				{
					isPressNameinput = true;
					if(Keyboard::isKeyPressed(Keyboard::BackSpace)&&NameInput.getSize()>0)
					{
						NameInput.erase(NameInput.getSize() - 1, 1);
						PlayerNameInput.setString(NameInput);
					}
					else if(!Keyboard::isKeyPressed(Keyboard::BackSpace)&&NameInput.getSize()<13&&!Keyboard::isKeyPressed(Keyboard::Space))
					{
						NameInput += static_cast<char>(event.text.unicode);;
						PlayerNameInput.setString(NameInput);
					}
					inputNameTimer = gameTimeTotal;
				}
				if(gameTimeTotal.asMilliseconds()-inputNameTimer.asMilliseconds()>125&&isPressNameinput)
				{
					isPressNameinput = false;
				}
			if(NameInput.getSize()==0)
			{
				window.draw(InputYourName);
			}
			window.draw(PlayerNameInput);
			if (Keyboard::isKeyPressed(Keyboard::Space) && NameInput.getSize() > 0)
			{
				scene = sceneManager::START_MENU;
				menu.isPressOK = true;
				saveScore();
				loadScore();
				updatescoreBoard();
				NameInput.clear();
				PlayerNameInput.setString(NameInput);
				current_score = 0;
				BMGMusic.stop();
				menuMusic.play();
			}

		}
		window.display();
	}

	return 0;
}
int randrange(int start, int stop)
{
	return (rand() % (stop - start + 1)) + start;
}
void spawnInfected(int x,int y,int type,int seed)
{
	if (numInfected >= maxInfected)
	{
		numInfected = 0;
	}
	Infected[numInfected].spawn(x, y, randrange(0,3), seed);
	numInfected++;
}
void summonSpawner(int x,int y,int Amount,int type,int delay)
{
	if(numSpawner >=maxSpawner)
	{
		numSpawner = 0;
	}
	portal[numSpawner].spawnSpawner(x, y, Amount, type, delay);
	numSpawner++;
}
void collision()
{
	for(int i=0;i<maxInfected;i++)
	{
		if(player.getPosition().intersects(Infected[i].getPosition())&&Infected[i].isAlive())
		{
			if(player.hit(gameTimeTotal,10))
			{

			}
			hitSound.play();
			if(player.getHealth()<=0)
			{
				scene = sceneManager::GAME_OVER;
				
			}
		}
	}
	for(int i=0;i<100;i++)
	{
		for(int j=0;j<maxInfected;j++)
		{
			if(bullet[i].isInFlight()&&Infected[j].isAlive())
			{
				if(bullet[i].getPosition().intersects(Infected[j].getPosition()))
				{
					bullet[i].stop();
					hitSound.play();
					if(Infected[j].hit())
					{
						current_score += randrange(6 , 18);
						printf("%d \n", current_score);
					}
				}
			}
		}
	}
	for(int i=0;i<maxItem;i++)
	{
		if(player.getPosition().intersects(item[i].getPosition())&&item[i].isAlive())
		{
			item[i].getItem();
			GetItemSound.play();
			playerGetItem(item[i].getType());
		}
	}
}
void AllUpdate(Time dt,Vector2f playerPosition)
{
	float dtAsSeconds = dt.asSeconds();

	ShowScore.setPosition(playerPosition.x-850,playerPosition.y-500);
	ShowScore.setString(std::to_string(current_score));
	HealthBar.setPosition(playerPosition.x - 900, playerPosition.y + 450);
	HealthBar.setSize(Vector2f(player.getHealth() * 3, 25));
	HealthBarBackground.setPosition(playerPosition.x - 900, playerPosition.y + 450);

	for (int i = 0; i < maxInfected; i++)
	{
		if (Infected[i].isAlive())
		{
			Infected[i].update(dt.asSeconds(), playerPosition);
		}
	}
	for (int i = 0; i < maxSpawner; i++)
	{
		if (portal[i].isOpen())
		{
			if (portal[i].canSpawn(gameTimeTotal))
			{
				portal[i].resetSpawntime(gameTimeTotal);
				spawnInfected(portal[i].position.x + 25, portal[i].position.y + 25, portal[i].type, randrange(0, 30));
			}
		}
	}
	for (int i = 0; i < 100; i++)
	{
		if (bullet[i].isInFlight())
		{
			bullet[i].update(dtAsSeconds);
		}
	}
	if (tank[0].isAlive())
	{
		tank[0].update(dt.asSeconds());
	}
	if(gameTimeTotal.asMilliseconds() - lastSpawn[0].asMilliseconds() > TimeToSpawn[0])
	{
		int minToSpawn, maxtoSpawn;
		minToSpawn = 5000 - (gameTimeTotal.asSeconds() * 1.2f*10);
		maxtoSpawn = 8000 - (gameTimeTotal.asSeconds() * 0.8f*10);
		if(minToSpawn < 1000)
		{
			minToSpawn = 1000;
		}
		if(maxtoSpawn < 3000)
		{
			maxtoSpawn = 3000;
		}
		TimeToSpawn[0] = randrange(minToSpawn,maxtoSpawn);
		lastSpawn[0] = gameTimeTotal;
		summonSpawner(randrange(40, 1460), randrange(40, 1160), randrange(4, 8), 0, randrange(3,9));
	}	if (gameTimeTotal.asMilliseconds() - lastSpawn[1].asMilliseconds() > TimeToSpawn[1])
	{
		TimeToSpawn[1] = randrange(10000, 20000);
		lastSpawn[1] = gameTimeTotal;
		summonItem(randrange(100, 1400), randrange(100, 1100), randrange(0, 3));
	}
}
void PlayerController()
{
	if (scene == sceneManager::MAIN_GAME)
	{
		//ifควบคุมการเครื่อนไหว
		if (Keyboard::isKeyPressed(Keyboard::W))
		{
			player.moveUp();
		}
		else
		{
			player.stopUp();
		}

		if (Keyboard::isKeyPressed(Keyboard::S))
		{
			player.moveDown();
		}
		else
		{
			player.stopDown();
		}

		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			player.moveLeft();
		}
		else
		{
			player.stopLeft();
		}

		if (Keyboard::isKeyPressed(Keyboard::D))
		{
			player.moveRight();
		}
		else
		{
			player.stopRight();
		}

		playerShootBullet();
	}
}
void playerShootBullet()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (gameTimeTotal.asMilliseconds() - lastPressed.asMilliseconds() > 1000 / fireRate)
		{
			Shootsound.play();
			bullet[currentBullet].shoot(player.getCenter().x-10, player.getCenter().y-10, mouseWorldPosition.x, mouseWorldPosition.y);
			currentBullet++;
			if (currentBullet > 99)
			{
				currentBullet = 0;
			}
			lastPressed = gameTimeTotal;
		}
	}
}
void loadScore()
{
	std::ifstream inputFile1("GameData/1.txt");
	std::ifstream inputFile2("GameData/2.txt");
	std::ifstream inputFile3("GameData/3.txt");
	std::ifstream inputFile4("GameData/4.txt");
	std::ifstream inputFile5("GameData/5.txt");
	std::ifstream NameFile1("GameData/Name1.txt");
	std::ifstream NameFile2("GameData/Name2.txt");
	std::ifstream NameFile3("GameData/Name3.txt");
	std::ifstream NameFile4("GameData/Name4.txt");
	std::ifstream NameFile5("GameData/Name5.txt");
	if (inputFile1.is_open())
	{
		inputFile1 >> score[5];
		inputFile1.close();
	}
	if (inputFile2.is_open())
	{
		inputFile2 >> score[4];
		inputFile2.close();
	}
	if (inputFile3.is_open())
	{
		inputFile3 >> score[3];
		inputFile3.close();
	}
	if (inputFile4.is_open())
	{
		inputFile4 >> score[2];
		inputFile4.close();
	}
	if (inputFile5.is_open())
	{
		inputFile5 >> score[1];
		inputFile5.close();
	}
	if(NameFile1.is_open())
	{
		if(std::getline(NameFile1, loadPlayerName[5]))
		{
		}
		NameFile1.close();
	}
	if (NameFile2.is_open())
	{
		if (std::getline(NameFile2, loadPlayerName[4]))
		{
		}
		NameFile2.close();
	}
	if (NameFile3.is_open())
	{
		if (std::getline(NameFile3, loadPlayerName[3]))
		{
		}
		NameFile3.close();
	}
	if (NameFile4.is_open())
	{
		if (std::getline(NameFile4, loadPlayerName[2]))
		{
		}
		NameFile4.close();
	}
	if (NameFile5.is_open())
	{
		if (std::getline(NameFile5, loadPlayerName[1]))
		{
		}
		NameFile5.close();
	}
}
void saveScore()
{
	int passScore[6];
	std::string LoadPlayerName[6];
	for(int i=1;i<=5;i++)
	{
		passScore[i] = score[i];
		LoadPlayerName[i] = loadPlayerName[i];
	}
	LoadPlayerName[0] = NameInput.toAnsiString();
	score[0] = current_score;
	passScore[0] = current_score;
	int n = sizeof(score) / sizeof(score[0]);
	std::sort(score, score + n);
	for (int i = 0; i <= 5; i++)
	{
		for (int j = 0; j <= 5; j++)
		{
			if(score[i]==passScore[j])
			{
				loadPlayerName[i] = LoadPlayerName[j];
			}
		}
	}
	std::ofstream inputFile1("GameData/1.txt");
	std::ofstream inputFile2("GameData/2.txt");
	std::ofstream inputFile3("GameData/3.txt");
	std::ofstream inputFile4("GameData/4.txt");
	std::ofstream inputFile5("GameData/5.txt");
	std::ofstream NameFile1("GameData/Name1.txt");
	std::ofstream NameFile2("GameData/Name2.txt");
	std::ofstream NameFile3("GameData/Name3.txt");
	std::ofstream NameFile4("GameData/Name4.txt");
	std::ofstream NameFile5("GameData/Name5.txt");
	if (inputFile1.is_open())
	{
		inputFile1 << score[5];
		inputFile1.close();
	}
	if (inputFile2.is_open())
	{
		inputFile2 << score[4];
		inputFile2.close();
	}
	if (inputFile3.is_open())
	{
		inputFile3 << score[3];
		inputFile3.close();
	}
	if (inputFile4.is_open())
	{
		inputFile4 << score[2];
		inputFile4.close();
	}
	if (inputFile5.is_open())
	{
		inputFile5 << score[1];
		inputFile5.close();
	}
	if(NameFile1.is_open())
	{
		NameFile1 << loadPlayerName[5];
		NameFile1.close();
	}
	if (NameFile2.is_open())
	{
		NameFile2 << loadPlayerName[4];
		NameFile2.close();
	}
	if (NameFile3.is_open())
	{
		NameFile3 << loadPlayerName[3];
		NameFile3.close();
	}
	if (NameFile4.is_open())
	{
		NameFile4 << loadPlayerName[2];
		NameFile4.close();
	}
	if (NameFile5.is_open())
	{
		NameFile5 << loadPlayerName[1];
		NameFile5.close();
	}
}
void updatescoreBoard()
{
	for (int i = 1; i < 6; i++)
	{
		printf("%d \n", score[i]);
	}
	font.loadFromFile("GAsset/Minecraft.ttf");
	PlayerNameInput.setFont(font);
	PlayerNameInput.setPosition(750, 440);
	PlayerNameInput.setCharacterSize(48);
	InputYourName.setFont(font);
	InputYourName.setPosition(720, 440);
	InputYourName.setCharacterSize(48);
	InputYourName.setString("Input Your Name");
	for (int i = 1; i <= 5; i++)
	{
		PlayerName[i - 1].setPosition(600, 925 - (125 * i));
		PlayerName[i - 1].setString(loadPlayerName[i]);
		PlayerName[i - 1].setCharacterSize(48);
		PlayerName[i - 1].setFont(font);
		PlayerScore[i - 1].setPosition(1100, 925 - (125 * i));
		PlayerScore[i - 1].setString(std::to_string(score[i]));
		PlayerScore[i - 1].setCharacterSize(48);
		PlayerScore[i - 1].setFont(font);
		//PlayerName[i - 1].setColor(Color::White);
	}
}
void DebugCommand()
{
	//if (Keyboard::isKeyPressed(Keyboard::P))
	//{
	//	spawnInfected(1200, 900, 0, 0);
	//}
	//if (Keyboard::isKeyPressed(Keyboard::I))
	//{
	//	summonSpawner(randrange(200, 1200), randrange(200, 900), randrange(2, 8), 0, randrange(6, 16));
	//}
	//if (Keyboard::isKeyPressed(Keyboard::O))
	//{
	//	tank[0].spawn(2000, mouseWorldPosition.y);
	//}
	//if(Keyboard::isKeyPressed(Keyboard::U))
	//{
	//	summonItem(randrange(200, 1200), randrange(200, 900), randrange(0, 3));
	//}
}
void playerGetItem(int type)
{
	switch (type)
	{
	case 0:
		printf("Item01");
		player.playerHeal(60);
		fireRate+=0.25f;
		player.upgradeSpeed();
		current_score += randrange(40,60);
		break;
	case 1:
		printf("Item02");
		fireRate+=0.5f;
		current_score += randrange(30, 50);
		break;
	case 2:
		printf("Item03");
		player.upgradeHealth();
		HealthBarBackground.setSize(Vector2f(player.player_MaxHealth * 3, 25));
		player.upgradeSpeed();
		current_score += randrange(20, 40);
		break;
	case 3:
		printf("Item04");
		player.playerHeal(40);
		fireRate += 0.1f;
		current_score += randrange(10, 30);
		break;
	default:
		break;
	}
}
void summonItem(int x,int y,int type)
{
	if (numItem >= maxItem)
	{
		numItem = 0;
	}
	item[numItem].spawn(x, y, type);
	numItem++;
}