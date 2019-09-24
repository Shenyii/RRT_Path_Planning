#include <iostream>
#include "rrt.h"

using namespace std;

int main()
{
	srand((unsigned)time(NULL));
	cout << "Start rrt path planning!" << endl;
	rrt rrt_test;
	rrt_test.setObstacle(20, 30, 10,80);
	rrt_test.setObstacle(20, 30, 75, 10);
	rrt_test.setStartAndGoal(10, 10, 90, 90);
	rrt_test.startRRTplanning();
	rrt_test.display();
	getchar();
}