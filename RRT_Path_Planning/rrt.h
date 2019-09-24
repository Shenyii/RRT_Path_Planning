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
	int startRRTplanning();    //0-��ʾû������·����1-��ʾ������·����

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

	int collisionCheck(node node1, node node2);      //0-��ʾ����ײ��1-��ʾ����ײ
	int rrtStopCheck(node node1);                             //0-��ʾ��ֹͣ��1-��ʾֹͣ
	void clearMap();
	void findNearbyVertex(int x,int y);
	void productPath();
	int beInPathCheck(node node1);                                             //0-��ʾ����·���ϣ�1-��ʾ��·����
};

