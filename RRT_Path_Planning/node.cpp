#include "node.h"

node::node()
	:x_(-1), y_(-1), obstacle_flag_(false),father_node_(NULL)
{}

node::~node()
{}

void node::setPosition(int x, int y)
{
	x_ = x;
	y_ = y;
}

void node::setObstacle(bool state)
{
	obstacle_flag_ = state;
}

bool node::getObstacleState()
{
	//getchar();
	return obstacle_flag_;
}

int node::getX()
{
	return x_;
}

int node::getY()
{
	return y_;
}

void node::setFatherNode(node* node1)
{
	father_node_ = node1;
}

node* node::getFatherNode()
{
	return father_node_;
}

bool operator==(node node1, node node2)
{
	if ((node1.getX() == node2.getX()) && (node1.getY() == node2.getY()))
	{
		return true;
	}
	else
	{
		return false;
	}
}