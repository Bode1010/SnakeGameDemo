#include "Fruit.h"

Fruit::Fruit(float moveSp, int gridWidth, int gridHeight)
{
	getNewPos(moveSp, gridWidth, gridHeight);
}

//sets fruits new position
void Fruit::getNewPos(float moveSp, int gridWidth, int gridHeight) {
	xPos = rand() % gridWidth;
	xPos = xPos * moveSp;
	yPos = rand() % gridHeight;
	yPos = yPos * moveSp;
	value = 2;
}

int Fruit::getXPos() {
	return xPos;
}
int Fruit::getYPos() {
	return yPos;
}

int Fruit::getVal() {
	return value;
}

Fruit::~Fruit()
{
}
