#include"pch.h"
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/OpenGL.hpp>
#include<SFML/Audio.hpp>
#include<iostream>
#include<ctime>
#include<time.h>
using namespace sf;
using namespace std;
const int length = 12, width = 17;
float position = 0;
float speed = 3;
int main()
{

	RenderWindow window(VideoMode(1024, 768), "Fuck");

	// Making of Player
	int posx = 206, posy = 206;
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

	Sprite Grid[width + 1][length + 1];





	// Distribution of wall & ground on the Grid

	for (int i = 1; i <= width; i++)
	{
		for (int j = 1; j <= length; j++)
		{


			if (i == 1 || i == width)
			{
				Grid[i][j].setTexture(wall);
				Grid[i][j].setPosition((i + 2) * 52, (j + 0.25) * 44);
				Grid[i][j].setScale(0.0995, 0.15);
			}
			else if (j == 1 || j == length)
			{
				Grid[i][j].setTexture(wall);
				Grid[i][j].setPosition((i + 2) * 52, (j + 0.25) * 44);
				Grid[i][j].setScale(0.0995, 0.15);
			}
			else
			{
				if (i % 2 == j % 2) { Grid[i][j].setTexture(ground); }
				else { Grid[i][j].setTexture(ground2); }
				Grid[i][j].setPosition((i + 2) * 52, (j + 0.7) * 44);
				Grid[i][j].setScale(0.1, 0.1);
			}

		}
	}
	// Breakable Test
	Grid[5][6].setTexture(wall);
	Grid[5][6].setPosition((5 + 2) * 52, (6 + 0.8) * 40);
	Grid[5][6].setScale(0.0995, 0.15);




	Grid[1][length].setTexture(wall);
	Grid[width][length].setTexture(wall);


	Sprite Wallpaper;
	Wallpaper.setTexture(wallpaper);


	while (window.isOpen())
	{

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || Keyboard::isKeyPressed(Keyboard::Enter))
				window.close();

			// Player Movement

			if (Keyboard::isKeyPressed(Keyboard::Key::Right))      // Moving Right
			{
				player.move(speed, 0.0);
				if (player.getGlobalBounds().intersects(Grid[5][6].getGlobalBounds())) {  //incorrect intersection delete if&else if you wanna disable it

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
				if (player.getGlobalBounds().intersects(Grid[5][6].getGlobalBounds())) {
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
				if (player.getGlobalBounds().intersects(Grid[5][6].getGlobalBounds())) {
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
				if (player.getGlobalBounds().intersects(Grid[5][6].getGlobalBounds())) {
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

			window.clear();
			// Drawing of the Wallpaper
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

	}	return 0;
}

