#include "Snake.h"
#include <iostream>
using namespace std;
//Initializes the snake by setting the properties of the snakes' 3(length) body nodes.
Snake::Snake()
{
	//set head properties
	Node *body = new Node;
	head.shape = 0;
	head.curdir = 1;
	head.next = 0;
	head.prev = body;

	//set first body part properties
	body->xPos = head.xPos - 1;
	body->yPos = head.yPos;
	body->prevXPos = head.xPos - 2;
	body->next = &head;
	body->prev = new Node;

	//set tail properties
	body->prev->next = body;
	body->prev->xPos = body->xPos - 1;
	body->prev->yPos = body->yPos;
	body->prev->prevXPos = body->xPos - 2;
	body->prev->prev = 0;
}

//sets the x and y position values of the snake head. Also changes the heads' prev position
void Snake::setSnakeHead(float x, float y) {
	head.prevXPos = head.xPos;
	head.prevYPos = head.yPos;
	head.xPos = x;
	head.yPos = y;
}

//sets the direction of the snake head.
void Snake::setDirec(int x) {
	direction = x;
	head.curdir = x;
}

//gives the variables x and y input into the function the value of the snakes x and y position
void Snake::getHeadPos(float* x, float* y) {
	*x = head.xPos;
	*y = head.yPos;
}

//returns the direction of the snake head
int Snake::getDirec() {
	return direction;
}

//returns the snake's length;
int Snake::getLength() {
	return length;
}

/*moves every node of the snake to its next position
*also assings the node what shape it should be based on its direction 
*and the direction of the node in front of it
*/
void Snake::move(int i/*direction*/) {
	//starts from the head.prev node because the head node has already been set to a new value 
	//based on what the player input
	Node *curNode = head.prev;

	for (int i = 0; i < length-1; i++) {
		//changes the current and next direction of each node
		curNode->curdir = curNode->nextdir;
		curNode->nextdir = curNode->next->curdir;

		//changes the shape of the node based on its' current and next direction
		//************************************************************
		if ((curNode->nextdir == 1 && curNode->curdir == 1) || (curNode->nextdir == 3 && curNode->curdir == 3)) {
			curNode->shape = 5;
		}
		else if ((curNode->nextdir == 2 && curNode->curdir == 2) || (curNode->nextdir == 4 && curNode->curdir == 4)) {
			curNode->shape = 3;
		}
		else {
			if (curNode->curdir == 4 && curNode->nextdir == 1) {
				curNode->shape = 1;
			}
			else if (curNode->curdir == 4 && curNode->nextdir == 3) {
				curNode->shape = 2;
			}
			else if (curNode->curdir == 2 && curNode->nextdir == 1) {
				curNode->shape = 6;
			}
			else if (curNode->curdir == 2 && curNode->nextdir == 3) {
				curNode->shape = 4;
			}
			else if (curNode->curdir == 1 && curNode->nextdir == 2) {
				curNode->shape = 2;
			}
			else if (curNode->curdir == 1 && curNode->nextdir == 4) {
				curNode->shape = 4;
			}
			else if (curNode->curdir == 3 && curNode->nextdir == 2) {
				curNode->shape = 1;
			}
			else if (curNode->curdir == 3 && curNode->nextdir == 4) {
				curNode->shape = 6;
			}
		}
		//***********************************************************

		//changes the position of each node on the snake to the node ahead of it.
		curNode->prevXPos = curNode->xPos;
		curNode->xPos = curNode->next->prevXPos;
		curNode->prevYPos = curNode->yPos;
		curNode->yPos = curNode->next->prevYPos;

		//if the snake hits its' own body, it dies
		if (head.xPos == curNode->xPos && head.yPos == curNode->yPos)
			alive = false;
		//sets the shape for the last Node, ie the tail shape
		if (curNode->prev == 0) {
			switch (curNode->curdir) {
			case 1:
				curNode->shape = 7;
				break;
			case 2:
				curNode->shape = 8;
				break;
			case 3:
				curNode->shape = 9;
				break;
			case 4:
				curNode->shape = 10;
				break;
			}
		}
		
		curNode = curNode->prev;
	}
}

//increases the snakes length by one
void Snake::grow() {
	Node *newTail = new Node;
	Node *curNode = head.prev;

	for (int i = 0; i < length - 2; i++) {//traverses to last Node in the list
		curNode = curNode->prev;
	}
	//makes node newTail the new tail of the snake.
	newTail->xPos = curNode->prevXPos;
	newTail->yPos = curNode->prevYPos;
	curNode->prev = newTail;
	newTail->next = curNode;
	newTail->prev = 0;
	newTail->curdir = curNode->curdir;
	length ++;
}

//returns alive bool
bool Snake::isAlive() {
	return alive;
}

//sets the value of x, y and shape to the input nodes x, y and shape
void Snake::getNodePos(int node, int *x, int *y, int *shape) {
	Node *curNode = &head;
	for (int i = 0; i < node; i++) {
		curNode = curNode->prev;
	}
	*x = static_cast<int>(curNode->xPos);
	*y = static_cast<int>(curNode->yPos);
	*shape = curNode->shape;
	return;
}

//sets alive to false
void Snake::kill() {
	alive = false;
}

Snake::~Snake()
{
}
