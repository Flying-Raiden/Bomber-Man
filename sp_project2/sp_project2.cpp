#include"pch.h"
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/OpenGL.hpp>
#include<SFML/Audio.hpp>
#include<iostream>
#include<algorithm>
#include<vector>
#include<functional>
#include<ctime>
#include<time.h>
#define MAX_NUMBER_OF_ITEMS 3
using namespace sf;
using namespace std;
struct leftmovement {
	int i, j;
};
struct rightmovement {
	int i, j;
};
struct upmovement {
	int i, j;
};
struct downmovement {
	int i, j;
};
struct postions {
	int posx, posy;
};
const int length = 12, width = 17;
float position = 0,p=0;
float speed = 2;
int selectedItemIndex = 0;
Font font,fnt; Text menu[MAX_NUMBER_OF_ITEMS],names[5];
void setmenustatus(float width, float height) {
	if (!font.loadFromFile("arial.ttf"))
	{
		// handle error 
		cout << "SHIIIIT" << endl;
	}

	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		menu[i].setFont(font);
		if (i == 0) {
			menu[i].setFillColor(Color::Red);
			menu[i].setString("Play");
			menu[i].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 1));
		}
		else if (i == 1) {
			menu[i].setFillColor(Color::White);
			menu[i].setString("About Us");
			menu[i].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 2));

		}
		else
		{
			menu[2].setFillColor(Color::White);
			menu[2].setString("Exit");
			menu[2].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 3));
		}

	}
	
}

void drawmenu(RenderWindow &window)
{
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window.draw(menu[i]);
	}
}

void MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		menu[selectedItemIndex].setFillColor(Color::White);
		selectedItemIndex--;
		menu[selectedItemIndex].setFillColor(Color::Red);
	}
}

void MoveDown()
{
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
	{
		menu[selectedItemIndex].setFillColor(Color::White);
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(Color::Red);
	}
}

int GetPressedItem() {
	return selectedItemIndex; 
}

void About_Us() {
	if (!fnt.loadFromFile("arial.ttf"))
	{
		// handle error
		cout << "SHIIIIT" << endl;
	}
	for (int i = 0; i < 5; i++)
	{
		names[i].setFont(fnt);
		names[i].setFillColor(Color::Red);
		if (i == 0)
			names[i].setString("Mrawan El Masry");
		else if(i==1)
			names[i].setString("Mahmoud Sameh");
		else if (i == 2)
			names[i].setString("Mahmoud Saeed");
		else if (i == 3)
			names[i].setString("Mahmoud Adel");
		else
			names[i].setString("Mahmoud Alaa");

		names[i].setPosition(100,100);
	}
	
}
void draw_about_us(RenderWindow &window)
{
	for (int i = 0; i < 5; i++)
	{
		window.draw(names[i]);
	}
}

int GetXindx(float a)
{
	return (a - 183) / 53 + 2;
}


int GetYindx(float a)
{
	return (a - 74) / 48 + 2;
}


int main()
{
	
	RenderWindow window(VideoMode(1280, 768), "Fuck");
	//###############################################################################
	// Menu Shits
	RenderWindow background(VideoMode(1280, 768), "Fuck");
	setmenustatus(background.getSize().x, background.getSize().y);
	Texture backgroundwall;
	backgroundwall.loadFromFile("FantasyLand.png");
	Sprite menuwall; menuwall.setTexture(backgroundwall);
	//###############################################################################


	//###############################################################################
	// General stuf for the player and the monsters
	postions Player,Monster1, Monster2, Monster3;
	RectangleShape player(Vector2f(100, 120)), monster1(Vector2f(100, 120)), monster2(Vector2f(100, 120)), monster3(Vector2f(100, 120));
	player.setScale(0.7, 0.7), monster1.setScale(0.7, 0.7), monster2.setScale(0.7, 0.7), monster3.setScale(0.7, 0.7);
	Texture playertexture,monster1_texture, monster2_texture, monster3_texture;
	Clock Pclock,clock; Time Ptime,time;
	leftmovement left; rightmovement right; upmovement up; downmovement down;
	//###############################################################################
	


	//###############################################################################
	// Making of Player
	Player.posx = 500, Player.posy = 500;
	player.setPosition(Player.posx, Player.posy);
	playertexture.loadFromFile("player.png");
	player.setTexture(&playertexture);
	Vector2u player_size = playertexture.getSize();
	player_size.x /= 9;
	player_size.y /= 4;
	player.setTextureRect(IntRect(player_size.x * 0, player_size.y * 2, player_size.x, player_size.y));
	//###############################################################################
	

	//###############################################################################
	// Making of Monster 1
	Monster1.posx = 490, Monster1.posy = 500;
	monster1.setPosition(Monster1.posx, Monster1.posy);
	monster1_texture.loadFromFile("monster (1).png");
	monster1.setTexture(&monster1_texture);
	Vector2u monster1_size = monster1_texture.getSize();
	monster1_size.x /= 9;
	monster1_size.y /= 4;
	monster1.setTextureRect(IntRect(monster1_size.x * 0, monster1_size.y * 2, monster1_size.x, monster1_size.y));
	//###############################################################################
	//###############################################################################
	// Making of Monster 2
	Monster2.posx = 300, Monster2.posy = 300;
	monster2.setPosition(Monster2.posx, Monster2.posy);
	monster2_texture.loadFromFile("monster (5).png");
	monster2.setTexture(&monster2_texture);
	Vector2u monster2_size = monster2_texture.getSize();
	monster2_size.x /= 9;
	monster2_size.y /= 4;
	monster2.setTextureRect(IntRect(monster2_size.x * 0, monster2_size.y * 2, monster2_size.x, monster2_size.y));
	//###############################################################################
	int Pxindx=0, Pyindx=0,Mxindx=0,Myindx=0;
	// Making of Grid

	// MAP DEFINATION

	Texture wall, ground, wallpaper, ground2, breakable, life, bomb, range, hurt;



	if (!breakable.loadFromFile("42482223-490e-49bb-b83d-874397d4fd47.png"))
	{
		cout << "error loading breakable wall pic";
	}
	if (!wallpaper.loadFromFile("b0465160-5fa4-4de9-a876-2e95d50359c9.jpg"))
	{
		cout << "error loading wallpaper pic";
	}
	if (!wall.loadFromFile("3d wall.png"))
	{
		cout << "error loading wall pic";
	}

	if (!ground.loadFromFile("ground 1.png"))
	{
		cout << "error loading ground pic";
	}
	if (!ground2.loadFromFile("grass.png"))
	{
		cout << "error loading grass pic";
	}

	if (!life.loadFromFile("flife.png"))
	{
		cout << "error loading life pic";
	}
	life.setSmooth(1);
	if (!range.loadFromFile("frange.png"))
	{
		cout << "error loading range pic";
	}
	if (!bomb.loadFromFile("fbomb.png"))
	{
		cout << "error loading bomb pic";
	}

	if (!hurt.loadFromFile("hurt.png"))
	{
		cout << "error loading  hurt pic";
	}



	//###############################################################################
	// Player abilities
	Sprite lifeS, bombS, rangeS, Hurt, Wallpaper;
	lifeS.setTexture(life);
	lifeS.setPosition(0, 180);
	lifeS.setScale(0.4, 0.4);

	rangeS.setTexture(range);
	rangeS.setPosition(0, 250);
	rangeS.setScale(0.4, 0.4);

	bombS.setTexture(bomb);
	bombS.setPosition(0, 330);
	bombS.setScale(0.4, 0.4);

	Hurt.setTexture(hurt);
	Wallpaper.setTexture(wallpaper);
	//###############################################################################


	
	//###############################################################################
	// Distribution of wall & ground on the Grid

	Sprite Grid[width + 1][length + 1];

	for (int i = 1; i <= width; i++)
	{
		for (int j = 1; j <= length; j++)
		{
			if (i % 2 != 0 && j % 2 != 0)
			{

				Grid[i][j].setTexture(wall);
				Grid[i][j].setPosition((i + 1.97)*53.15, (j + 0.255) * 48);
				Grid[i][j].setScale(Vector2f(0.1009, 0.165));

			}

			else if (i == 1 || i == width)
			{
				Grid[i][j].setTexture(wall);
				Grid[i][j].setPosition((i + 1.97)*53.15, (j + 0.255) * 48);
				Grid[i][j].setScale(Vector2f(0.1009, 0.165));
			}
			else if (j == 1 || j == length)
			{
				Grid[i][j].setTexture(wall);
				Grid[i][j].setPosition((i + 1.97)*53.15, (j + 0.255) * 48);
				Grid[i][j].setScale(Vector2f(0.1009, 0.165));
			}
			else
			{
				if (i % 2 == j % 2) { Grid[i][j].setTexture(ground); }
				else { Grid[i][j].setTexture(ground2); }
				Grid[i][j].setPosition((i + 2) * 53, (j + 0.8) * 48);
				Grid[i][j].setScale(0.1, 0.101);
			}
		}
	}
	for (int i = 1; i <= 43; i++)
	{
		int x = rand() % 16 + 2, y = rand() % 9 + 2;
		if (x % 2 != 0 && y % 2 != 0)
		{
			x++;
		}
		Grid[x][y].setTexture(breakable);
		Grid[x][y].setPosition((x + 1.97)*53.15, (y + 0.255) * 48);
		Grid[x][y].setScale(Vector2f(0.1009, 0.165));
	}

	//###############################################################################



	// start game
	while (background.isOpen())
	{

		Event evnt;
		while (background.pollEvent(evnt))
		{
			switch (evnt.type)
			{
			case sf::Event::KeyReleased:
				switch (evnt.key.code)
				{
				case sf::Keyboard::Up:
					MoveUp();
					break;

				case sf::Keyboard::Down:
					MoveDown();
					break;

				case sf::Keyboard::Return:
					switch (GetPressedItem())
					{
					case 0:
						background.close();
						break;
					case 1:
						cout << "About Us button has been pressed \n";
						break;
					case 2:
						background.close();
						//window.close();
						return 0;
						break;
					}

					break;
				}

				break;
			case Event::Closed:
				background.close();
				return 0;
				break;
			}
		}
		
		background.clear();
		background.draw(menuwall);
		drawmenu(background);
		background.display();
	}
	int cnt = 0;
	//Game Window
	while (window.isOpen())
	{
		// Monster 1 movement
		Mxindx = (float)((float)(monster1.getPosition().x - 183) / 53 + 2);
		Myindx = (float)((float)(monster1.getPosition().y - 74) / 48 + 2);
		right.i = GetXindx(monster1.getPosition().x + 12); right.j = Myindx;
		left.i = GetXindx(monster1.getPosition().x - 12); left.j = Myindx;
		up.i = Mxindx; up.j = GetYindx(monster1.getPosition().y - 7);
		down.i = Mxindx; down.j = GetYindx(monster1.getPosition().y + 7);

		if (cnt == 0)      // Moving Right
		{
			if (Grid[right.i][right.j].getTexture() == &ground || Grid[right.i][right.j].getTexture() == &ground2) {
				monster1.move(speed, 0.0);
				time = clock.getElapsedTime();
				if (time.asSeconds() >= 0.1) {
					clock.restart();
					p++;
					if (p > 8)
						p -= 8;
				}
				monster1.setTextureRect(IntRect(monster1_size.x*p, monster1_size.y * 3, monster1_size.x, monster1_size.y));

			}
			else
			{
				cnt++;
			}

		}
		else if (cnt == 1) {
			if (Grid[up.i][up.j].getTexture() == &ground || Grid[up.i][up.j].getTexture() == &ground2)           // Moving Up
			{
				monster1.move(0.0, -speed);
				time = clock.getElapsedTime();
				if (time.asSeconds() >= 0.1) {
					clock.restart();
					p++;
					if (p > 8)
						p -= 8;
				}
				monster1.setTextureRect(IntRect(monster1_size.x*p, monster1_size.y * 0, monster1_size.x, monster1_size.y));

			}
			else
			{
				cnt++;
			}
		}
		else if (cnt == 2) {
			if (Grid[left.i][left.j].getTexture() == &ground || Grid[left.i][left.j].getTexture() == &ground2)         // Moving Left
			{
				monster1.move(-speed, 0.0);
				time = clock.getElapsedTime();
				if (time.asSeconds() >= 0.1) {
					clock.restart();
					p++;
					if (p > 8)
						p -= 8;
				}
				monster1.setTextureRect(IntRect(monster1_size.x*p, monster1_size.y * 1, monster1_size.x, monster1_size.y));


			}
			else
			{
				cnt++;
			}
		}
		else if (cnt == 3) {
			if (Grid[down.i][down.j].getTexture() == &ground || Grid[down.i][down.j].getTexture() == &ground2)         // Moving Down
			{
				monster1.move(0.0, speed);
				time = clock.getElapsedTime();
				if (time.asSeconds() >= 0.1) {
					clock.restart();
					p++;
					if (p > 8)
						p -= 8;
				}
				monster1.setTextureRect(IntRect(monster1_size.x*p, monster1_size.y * 2, monster1_size.x, monster1_size.y));

			}
			else
			{
				cnt = 0;
			}
		}
		//######################################################################################################
		// Player Movement
		Pxindx = (float)((float)(player.getPosition().x - 183) / 53 + 2);
		Pyindx = (float)((float)(player.getPosition().y - 74) / 48 + 2);
		right.i = GetXindx(player.getPosition().x + 12); right.j = Pyindx;
		left.i = GetXindx(player.getPosition().x - 12); left.j = Pyindx;
		up.i = Pxindx; up.j = GetYindx(player.getPosition().y - 7);
		down.i = Pxindx; down.j = GetYindx(player.getPosition().y + 7);

		if (Keyboard::isKeyPressed(Keyboard::Key::Right) && (Grid[right.i][right.j].getTexture() == &ground || Grid[right.i][right.j].getTexture() == &ground2))      // Moving Right
		{
			player.move(speed, 0.0);
			Ptime = Pclock.getElapsedTime();
			if (Ptime.asSeconds() >= 0.1) {
				Pclock.restart();
				position++;
				if (position > 8)
					position -= 8;
			}
			player.setTextureRect(IntRect(player_size.x*position, player_size.y * 3, player_size.x, player_size.y));
		}

		else if (Keyboard::isKeyPressed(Keyboard::Key::Left) && (Grid[left.i][left.j].getTexture() == &ground || Grid[left.i][left.j].getTexture() == &ground2))         // Moving Left
		{
			player.move(-speed, 0.0);
			Ptime = Pclock.getElapsedTime();
			if (Ptime.asSeconds() >= 0.1) {
				Pclock.restart();
				position++;
				if (position > 8)
					position -= 8;
			}
			player.setTextureRect(IntRect(player_size.x*position, player_size.y * 1, player_size.x, player_size.y));

		}
		else if (Keyboard::isKeyPressed(Keyboard::Key::Up) && (Grid[up.i][up.j].getTexture() == &ground || Grid[up.i][up.j].getTexture() == &ground2))           // Moving Up
		{
			player.move(0.0, -speed);
			Ptime = Pclock.getElapsedTime();
			if (Ptime.asSeconds() >= 0.1) {
				Pclock.restart();
				position++;
				if (position > 8)
					position -= 8;
			}
			player.setTextureRect(IntRect(player_size.x*position, player_size.y * 0, player_size.x, player_size.y));
		}
		else if (Keyboard::isKeyPressed(Keyboard::Key::Down) && (Grid[down.i][down.j].getTexture() == &ground || Grid[down.i][down.j].getTexture() == &ground2))         // Moving Down
		{
			player.move(0.0, speed);
			Ptime = Pclock.getElapsedTime();
			if (Ptime.asSeconds() >= 0.1) {
				Pclock.restart();
				position++;
				if (position > 8)
					position -= 8;
			}
			player.setTextureRect(IntRect(player_size.x*position, player_size.y * 2, player_size.x, player_size.y));
		}

		//######################################################################################################


		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || Keyboard::isKeyPressed(Keyboard::Enter))
				window.close();

		}
		window.clear();
		// Drawing of the Wallpaper
		//
    // Drawing of the Wallpaper
		window.draw(Wallpaper);

		//Drawing of The Map
		for (int i = 2; i < width; i++)
		{
			for (int j = 2; j < length; j++)
			{
				if (Grid[i][j].getTexture() == &ground || Grid[i][j].getTexture() == &ground2)
				{
					window.draw(Grid[i][j]);
				}
			}

		}

		for (int j = 1; j <= length; j++)
		{
			for (int i = 1; i <= width; i++)
			{
				if (Grid[i][j].getTexture() == &ground || Grid[i][j].getTexture() == &ground2)
				{
					continue;
				}

				window.draw(Grid[i][j]);

				if (GetYindx(player.getPosition().y) >= j)
				{
					window.draw(player);
				}

				if (GetYindx(monster1.getPosition().y) >= j)
				{
					window.draw(monster1);
				}
			}
		}

		
		window.draw(lifeS);
		window.draw(rangeS);
		window.draw(bombS);
		if (Keyboard::isKeyPressed(Keyboard::N)) window.draw(Hurt);
		window.display();


	}
}