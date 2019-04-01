#pragma once
class Snake
{
public:
	Snake();
	~Snake();

	void setSnakeHead(float x, float y);
	void setDirec(int x);
	void getHeadPos(float *x, float *y);
	int getDirec();
	int getLength();	
	void grow();
	void move(int i);//moves in Direction specified
	void getNodePos(int node, int *x, int *y, int * shape);//gives out the info about the node given, includin its x and y position and it's shape
	bool isAlive();
	void kill();
	


private:
	bool alive = true;
	int direction = 1;//Direction of the snake head. 1 - North, 2 - East, 3 - South, 4 - West.
	int length = 3;//Beginning length of the Snake, it has to be 3 because only 3 Nodes Locations were specifies in the constructor implementation

	struct Node {
		float xPos;
		float yPos;
		float prevXPos;
		float prevYPos;
		Node *next;
		Node *prev;
		int nextdir;
		int curdir;
		int shape = 5;
	};

	Node head;
};

