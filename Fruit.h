#pragma once
class Fruit
{
public:
	Fruit(float moveSp, int GridWidth, int GridHeight);
	~Fruit();
	int getXPos();
	int getYPos();
	int getVal();
	void getNewPos(float moveSp, int gridWidth, int gridHeight);

private:
	int value;
	int xPos;
	int yPos;
};

