#pragma once
#include <iostream>
#include <vector>
#include <time.h>

using namespace std;

class node
{
public:
	node();
	~node();
	void setPosition(int x, int y);
	void setObstacle(bool state);
	bool getObstacleState();
	int getX();
	int getY();
	void setFatherNode(node* node1);
	node* getFatherNode();

private:
	int x_;
	int y_;
	bool obstacle_flag_;
	node* father_node_;
};

bool operator==(node node1, node node2);

