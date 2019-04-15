#include"pch.h"
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/OpenGL.hpp>
#include<SFML/Audio.hpp>
#include<iostream>
#include<ctime>
#include<time.h>
#define MAX_NUMBER_OF_ITEMS 3
using namespace sf;
using namespace std;
const int length = 12, width = 17;
float position = 0;
float speed = 3;
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




int main()
{

	RenderWindow window(VideoMode(1280, 768), "Fuck");
	//###############################################################################
	// Menu Shits
	RenderWindow background(VideoMode(1280, 768), "Fuck");
	setmenustatus(background.getSize().x, background.getSize().y);
	Texture backgroundwall;
	backgroundwall.loadFromFile("background1(2).png");
	Sprite menuwall; menuwall.setTexture(backgroundwall);
	//###############################################################################
	// start game

	//###############################################################################
	// Making of Player
	int posx = 500, posy = 500;
	RectangleShape player(Vector2f(100, 120));
	player.setPosition(posx, posy);
	player.setScale(0.7, 0.7);
	Texture playertext;
	playertext.loadFromFile("monster.png");
	player.setTexture(&playertext);
	Vector2u text_size = playertext.getSize();
	text_size.x /= 9;
	text_size.y /= 4;
	player.setTextureRect(IntRect(text_size.x * 0, text_size.y * 2, text_size.x, text_size.y));
	Clock clock;
	Time time;
	//###############################################################################

	// Making of Grid

	// MAP DEFINATION

	Texture wall, ground, sidewall, wallpaper, ground2, breakable;
	Sprite s; s.setTexture(wall);

	if (!breakable.loadFromFile("42482223-490e-49bb-b83d-874397d4fd47.png"))
	{
		cout << "error loading breakable wall pic";
	}
	if (!wallpaper.loadFromFile("WP.jpg"))
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


	// Distribution of wall & ground on the Grid
	Sprite Grid[width + 1][length + 1];

	for (int i = 1; i <= width; i++)
	{
		for (int j = 1; j <= length; j++)
		{


			if (i == 1 || i == width)
			{
				Grid[i][j].setTexture(wall);
				Grid[i][j].setPosition((i + 1.97)*53.15, (j + 0.232)*50.5);
				Grid[i][j].setScale(Vector2f(0.1015, 0.169));
			}
			else if (j == 1 || j == length)
			{
				Grid[i][j].setTexture(wall);
				Grid[i][j].setPosition((i + 1.97)*53.15, (j + 0.232)*50.5);
				Grid[i][j].setScale(Vector2f(0.1015, 0.169));
			}
			else
			{
				if (i % 2 == j % 2) { Grid[i][j].setTexture(ground); }
				else { Grid[i][j].setTexture(ground2); }
				Grid[i][j].setPosition((i + 2) * 53, (j + 0.8)*48.5);
				Grid[i][j].setScale(0.1, 0.101);
			}

		}
	}
	Sprite Wallpaper;
	Wallpaper.setTexture(wallpaper);
	// Breakable Test
	Grid[5][6].setTexture(wall);

	while (window.isOpen())
	{
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
							window.close();
							break;
						}

						break;
					}

					break;
				case Event::Closed:
					background.close();
					break;
				}
			}
			background.clear();
			background.draw(menuwall);
			drawmenu(background);
			background.display();
		}
		// TESTING PLAYER POSITION
		int i = 0, j = 0;
		i = (float)((float)(player.getPosition().x - 183) / 53 + 1);
		j = (float)((float)(player.getPosition().y - 74) / 48 + 1);
		i++; j++;
		// j=row & i=col
		cout << j << "\t" << i << endl;
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			// Player Movement

			if (Keyboard::isKeyPressed(Keyboard::Key::Right))      // Moving Right
			{
				player.move(speed, 0.0);
				if (player.getGlobalBounds().intersects(Grid[i+1][j].getGlobalBounds())&&Grid[i+1][j].getTexture()==&wall) {
					player.move(-speed, 0.0);
				}
				else
				{
					player.move(speed, 0.0);
				}
				time = clock.getElapsedTime();
				if (time.asSeconds() >= 0.1) {
					clock.restart();
					position++;
					if (position > 8)
						position -= 8;
				}
				player.setTextureRect(IntRect(text_size.x*position, text_size.y * 3, text_size.x, text_size.y));
			}
			else if (Keyboard::isKeyPressed(Keyboard::Key::Left))         // Moving Left
			{
				player.move(-speed, 0.0);
				if (player.getGlobalBounds().intersects(Grid[i - 1][j].getGlobalBounds()) && Grid[i - 1][j].getTexture() == &wall) {
					player.move(speed, 0.0);
				}
				else
				{
					player.move(-speed, 0.0);
				}
				time = clock.getElapsedTime();
				if (time.asSeconds() >= 0.1) {
					clock.restart();
					position++;
					if (position > 8)
						position -= 8;
				}
				player.setTextureRect(IntRect(text_size.x*position, text_size.y * 1, text_size.x, text_size.y));
			}
			else if (Keyboard::isKeyPressed(Keyboard::Key::Up))           // Moving Up
			{
				player.move(0.0, -speed);
				if (player.getGlobalBounds().intersects(Grid[i][j-1].getGlobalBounds()) && Grid[i][j-1].getTexture() == &wall) {
					player.move(0.0, speed);
				}
				else
				{
					player.move(0.0, -speed);
				}
				posy = player.getPosition().y;
				time = clock.getElapsedTime();
				if (time.asSeconds() >= 0.1) {
					clock.restart();
					position++;
					if (position > 8)
						position -= 8;
				}
				player.setTextureRect(IntRect(text_size.x*position, text_size.y * 0, text_size.x, text_size.y));
			}
			else if (Keyboard::isKeyPressed(Keyboard::Key::Down))         // Moving Down
			{
				player.move(0.0, speed);
				if (player.getGlobalBounds().intersects(Grid[i][j+1].getGlobalBounds()) && Grid[i][j+1].getTexture() == &wall) {
					player.move(0.0, -speed);
				}
				else
				{
					player.move(0.0, speed);
				}
				time = clock.getElapsedTime();
				if (time.asSeconds() >= 0.1) {
					clock.restart();
					position++;
					if (position > 8)
						position -= 8;
				}
				player.setTextureRect(IntRect(text_size.x*position, text_size.y * 2, text_size.x, text_size.y));
			}

			// Drawing of the Wallpaper
			window.clear();
			window.draw(Wallpaper);



		}
		// Drawing of the ground

		for (int i = 2; i < width; i++)
		{
			for (int j = 2; j < length; j++)
			{
				window.draw(Grid[i][j]);
			}
		}


		// Drawing of the walls

			// Top wall
		for (int i = 1; i <= width; i++)
		{
			window.draw(Grid[i][1]);
		}

		// Bottom wall
		for (int i = 1; i <= width; i++)
		{
			window.draw(Grid[i][length]);
		}


		// Right wall
		for (int j = 1; j <= length; j++)
		{
			window.draw(Grid[1][j]);
		}

		// Left wall
		for (int j = 1; j <= length; j++)
		{
			window.draw(Grid[width][j]);
		}
		
	
	
		
		

		window.draw(player);
		window.display();

	}
}