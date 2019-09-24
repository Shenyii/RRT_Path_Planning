#pragma once
#include <iostream>
#include "node.h"
#include <vector>

using namespace std;

class rrt
{
public:
	rrt();
	~rrt();
	void setObstacle(int x, int y, int heigh, int length);
	void setStartAndGoal(int x_start, int y_start, int x_goal, int y_goal);
	void display();
	int startRRTplanning();    //0-表示没搜索到路径，1-表示搜索到路径。

private:
	node map_[100][100];
	int x_start_;
	int y_start_;
	int x_goal_;
	int y_goal_;
	int x_nearby_;
	int y_nearby_;
	vector<node*> vertex_;
	vector<node*> path_;
	int det_distance_;
	int max_sample_count_;

	int collisionCheck(node node1, node node2);      //0-表示无碰撞，1-表示有碰撞
	int rrtStopCheck(node node1);                             //0-表示不停止，1-表示停止
	void clearMap();
	void findNearbyVertex(int x,int y);
	void productPath();
	int beInPathCheck(node node1);                                             //0-表示不在路径上，1-表示在路径上
};

