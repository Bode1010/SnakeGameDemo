﻿#include <SFML/Graphics.hpp>//used for drawing to display window
#include <thread>//used for sleep_for function to delay the program
#include <chrono>//used for nanoseconds specification in the sleep_for function
#include "Snake.h"
#include "Fruit.h"
using namespace std;

int main()
{
	//creating a display
	sf::RenderWindow window(sf::VideoMode(512, 512), "Snake Game");

	//number of pixels moved per frame
	float pixPerFrame = 8;

	//grid specs
	const int GRIDX = 64;
	const int GRIDY = 64;

	//init player
	Snake playerSn;
	playerSn.setSnakeHead(256, 256);

	//value used as a small pause between each frame so the snake isn't moving at light speed
	//delay gets smaller as the snake gets larger to gradually increase difficulty
	int delayVal = 50000000 / sqrt(sqrt(sqrt(playerSn.getLength())));

	//init player head rect
	sf::RectangleShape playerRect(sf::Vector2f(8, 8));
	float x, y;
	playerSn.getHeadPos(&x, &y);
	playerRect.setPosition(x, y);

	//init player head texture
	sf::Texture playerTx;
	playerTx.loadFromFile("Snake Sprite Sheet.png");
	playerRect.setTexture(&playerTx);
	sf::Vector2u texSize = playerTx.getSize();
	texSize.x /= 5;
	texSize.y /= 4;

	//Snake initially faces north, hence first head sprite 
	//displayed is at the position 3, 0 on the sprite sheet(head north sprite)
	playerRect.setTextureRect(sf::IntRect(texSize.x * 3, texSize.y * 0, texSize.x, texSize.y));
	
	//snake skin texture initialization
	sf::Texture bodySkin;
	bodySkin.loadFromFile("Snake Sprite Sheet.png");
	sf::Vector2u bodyTexSize = bodySkin.getSize();
	bodyTexSize.x /= 5;
	bodyTexSize.y /= 4;

	//snake skin rectangle initialization (the rectangle will contain the texture
	sf::RectangleShape body(sf::Vector2f(8, 8));
	//links skin rectangle to skin texture
	body.setTexture(&bodySkin);

	//fruit init
	Fruit fruit(pixPerFrame, GRIDX,GRIDY);


	while (playerSn.isAlive()) {
		sf::Event evnt;
		while (window.pollEvent(evnt)) 
		{
			//when a key is pressed, change player direction accordingly
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
				if (playerSn.getDirec() != 4) {
					playerSn.setDirec(2);
					playerRect.setTextureRect(sf::IntRect(texSize.x * 4, texSize.y * 0, texSize.x, texSize.y));
				}
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
				if (playerSn.getDirec() != 2) {
					playerSn.setDirec(4);
					playerRect.setTextureRect(sf::IntRect(texSize.x * 3, texSize.y * 1, texSize.x, texSize.y));
				}
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
				if (playerSn.getDirec() != 3) {
					playerSn.setDirec(1);
					playerRect.setTextureRect(sf::IntRect(texSize.x * 3, texSize.y * 0, texSize.x, texSize.y));
				}
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
				if (playerSn.getDirec() != 1) {
					playerRect.setTextureRect(sf::IntRect(texSize.x * 4, texSize.y * 1, texSize.x, texSize.y));
					playerSn.setDirec(3);
				}
			}
			
		};

		//uses the players' direction to move it one block over every iteration
		playerSn.getHeadPos(&x, &y);
		switch (playerSn.getDirec()) {
		case 1:
			playerRect.move(0, -1 * pixPerFrame);
			playerSn.setSnakeHead(x, y -1 * pixPerFrame);
			if (y <= 0) {
				playerSn.kill();
			}
			break;
		case 2:
			playerRect.move(pixPerFrame, 0);
			playerSn.setSnakeHead(x + 1 * pixPerFrame, y);
			if (x > 512) {
				playerSn.kill();
			}
			break;
		case 3:
			playerRect.move(0, 1 * pixPerFrame);
			playerSn.setSnakeHead(x, y + 1 * pixPerFrame);
			if (y > 512) {
				playerSn.kill();
			}
			break;
		case 4:
			playerRect.move(-1 * pixPerFrame, 0);
			playerSn.setSnakeHead(x - 1 * pixPerFrame, y);
			if (x <= 0) {
				playerSn.kill();
			}
			break;
		}

		//iterate through the body setting them to their desired positions
		playerSn.move(playerSn.getDirec());
		
		//if player meets fruit, create new fruit, grow player
		playerSn.getHeadPos(&x, &y);
		if (x == static_cast <float>(fruit.getXPos()) && y == static_cast<float>(fruit.getYPos())) {
			fruit.getNewPos(pixPerFrame, GRIDX, GRIDY);
			for (int i = 0; i < fruit.getVal(); i++) {
				playerSn.grow();
			}
			//recalculate delay due to change in player length
			delayVal = 50000000 / sqrt(sqrt(sqrt(playerSn.getLength())));
		}

		//clear screen
		window.clear();

		//delay implementation
		std::this_thread::sleep_for(std::chrono::nanoseconds(delayVal));

		//Draw player Body
		for (int i = 1; i < playerSn.getLength(); i++) {
			int x, y, shape;
			playerSn.getNodePos(i, &x, &y, &shape);
			switch (shape) {//traverses the player nodes determining their shape and applying the correct image to the assigned shape
			case 1:
				body.setTextureRect(sf::IntRect(texSize.x * 0, texSize.y * 1, texSize.x, texSize.y));
				break;
			case 2:
				body.setTextureRect(sf::IntRect(texSize.x * 0, texSize.y * 0, texSize.x, texSize.y));
				break;
			case 3:
				body.setTextureRect(sf::IntRect(texSize.x * 1, texSize.y * 0, texSize.x, texSize.y));
				break;
			case 4:
				body.setTextureRect(sf::IntRect(texSize.x * 2, texSize.y * 0, texSize.x, texSize.y));
				break;
			case 5:
				body.setTextureRect(sf::IntRect(texSize.x * 2, texSize.y * 1, texSize.x, texSize.y));
				break;
			case 6:
				body.setTextureRect(sf::IntRect(texSize.x * 2, texSize.y * 2, texSize.x, texSize.y));
				break;
			case 7:
				body.setTextureRect(sf::IntRect(texSize.x * 3, texSize.y * 2, texSize.x, texSize.y));
				break;
			case 8:
				body.setTextureRect(sf::IntRect(texSize.x * 4, texSize.y * 2, texSize.x, texSize.y));
				break;
			case 9:
				body.setTextureRect(sf::IntRect(texSize.x * 4, texSize.y * 3, texSize.x, texSize.y));
				break;
			case 10:
				body.setTextureRect(sf::IntRect(texSize.x * 3, texSize.y * 3, texSize.x, texSize.y));
				break;
			}
			body.setPosition(sf::Vector2f(x, y));
			window.draw(body);
		}
		
		//draw player Head
		window.draw(playerRect);

		//Draw fruit
		body.setTextureRect(sf::IntRect(texSize.x * 0, texSize.y * 3, texSize.x, texSize.y));
		body.setPosition(sf::Vector2f(fruit.getXPos(), fruit.getYPos()));
		window.draw(body);

		//show board
		window.display();
	}
	return 0;
}
