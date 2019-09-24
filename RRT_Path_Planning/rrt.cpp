#include "rrt.h"

rrt::rrt()
	:det_distance_(5),max_sample_count_(1000)
{
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			map_[i][j].setPosition(i, j);
		}
	}
}

rrt::~rrt()
{}

void rrt::setObstacle(int x, int y, int heigh, int length)
{
	for (int i = x; i < x + heigh; i++)
	{
		for (int j = y; j < y + length; j++)
		{
			map_[i][j].setObstacle(true); 
		}
	}
}

void rrt::setStartAndGoal(int x_start, int y_start, int x_goal, int y_goal)
{
	x_start_ = x_start;
	y_start_ = y_start;
	x_goal_ = x_goal;
	y_goal_ = y_goal;
}

void rrt::display()
{
	cout << "display the map." << endl;
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			if (map_[i][j].getObstacleState() == true)
			{
				cout << "x ";
			}
			else if (map_[i][j].getObstacleState() == false)
			{
				if (map_[i][j].getFatherNode() != NULL)
				{
					if (beInPathCheck(map_[i][j]) == 1)
					{
						cout << ">>";
					}
					else
					{
						cout << ". ";
					}
				}
				else
				{
					cout << ". ";
				}
			}
		}
		cout << endl;
	}
}

int rrt::startRRTplanning()
{
	cout << endl << "start rrt." << endl;
	vertex_.clear();
	path_.clear();
	vertex_.push_back(&map_[x_start_][y_start_]);
	if (rrtStopCheck(*vertex_[vertex_.size() - 1]) == 1)
	{
		return 1;
	}

	for(int i = 0;i < max_sample_count_;i++)
	{
		//if (vertex_.size() == 87)
		//{
		//	getchar();
		//}
		int x_init = rand() % 100;
		int y_init = rand() % 100;
		findNearbyVertex(x_init, y_init);
		int det_d = sqrt((x_init - x_nearby_) * (x_init - x_nearby_) + (y_init - y_nearby_) * (y_init - y_nearby_));
		if (det_d == 0)
		{
			continue;
		}

		int x_new = x_nearby_ + det_distance_ * (x_init - x_nearby_) / det_d;
		int y_new = y_nearby_ + det_distance_ * (y_init - y_nearby_) / det_d;
		if (x_new < 0)
		{
			x_new = 0;
		}
		else if (x_new > 99)
		{
			x_new = 99;
		}
		if (y_new < 0)
		{
			y_new = 0;
		}
		else if (y_new > 99)
		{
			y_new = 99;
		}

		if (collisionCheck(map_[x_nearby_][y_nearby_], map_[x_new][y_new]) == 0)
		{
			if (map_[x_new][y_new].getFatherNode() == NULL)
			{
				map_[x_new][y_new].setFatherNode(&map_[x_nearby_][y_nearby_]);
			}
			//cout << "test1" << endl;
			vertex_.push_back(&map_[x_new][y_new]);                                          //bug  bug  bug!!!
			//cout << "test2" << endl;
			if (rrtStopCheck(map_[x_new][y_new]) == 1)
			{
				cout << endl << "Find the path!" << endl;
				return 1;
			}
		}
	//	//display();
	}
	cout << "Can't find the path!" << endl;
	return 1;
}

int rrt::collisionCheck(node node1, node node2)
{
	//cout << "collision check." << endl;
	double x = node1.getX();
	double y = node1.getY();
	int det_d = sqrt((node2.getY() - node1.getY()) * (node2.getY() - node1.getY()) + (node2.getX() - node1.getX()) * (node2.getX() - node1.getX()));
	if (det_d == 0)
	{
		return 0;
	}
	for (int i = 0; i < det_d; i++)
	{
		x = node1.getX() + (node2.getX() - node1.getX()) * (i + 1) / (double)(det_d);
		y = node1.getY() + (node2.getY() - node1.getY()) * (i + 1) / (double)(det_d);
		if (map_[(int)(x)][(int)(y)].getObstacleState() == true)
		{
			return 1;
		}
	}
	return 0;
}

void rrt::clearMap()
{}

int rrt::rrtStopCheck(node node1)
{
	//cout << endl << "whether stop rrt." << endl;
	if ((node1.getX() - x_goal_) * (node1.getX() - x_goal_) + (node1.getY() - y_goal_) * (node1.getY() - y_goal_) < det_distance_ * det_distance_)
	{
		if (collisionCheck(node1,map_[x_goal_][y_goal_]) == 0)
		{
			map_[x_goal_][y_goal_].setFatherNode(&map_[node1.getX()][node1.getY()]);
			productPath();
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return 0;
	}
}

void rrt::findNearbyVertex(int x, int y)
{
	//cout << endl << "find nearby vertex." << endl;
	double distance = (vertex_[0]->getX() - x) * (vertex_[0]->getX() - x) + (vertex_[0]->getY() - y) * (vertex_[0]->getY() - y);
	x_nearby_ = vertex_[0]->getX();
	y_nearby_ = vertex_[0]->getY();
	for (int i = 1; i < vertex_.size(); i++)
	{
		if ((vertex_[i]->getX() - x) * (vertex_[i]->getX() - x) + (vertex_[i]->getY() - y) * (vertex_[i]->getY() - y) < distance)
		{
			distance = (vertex_[i]->getX() - x) * (vertex_[i]->getX() - x) + (vertex_[i]->getY() - y) * (vertex_[i]->getY() - y);
			x_nearby_ = vertex_[i]->getX();
			y_nearby_ = vertex_[i]->getY();
		}
	}
}

void rrt::productPath()
{
	//cout << endl << "product path." << endl;
	path_.push_back(&map_[x_goal_][y_goal_]);
	int stop_flag = 0;
	while (path_[path_.size() - 1]->getFatherNode() != NULL)
	//for(int i = 0;i < 20;i ++)
	{
		path_.push_back(&map_[path_[path_.size() - 1]->getFatherNode()->getX()][path_[path_.size() - 1]->getFatherNode()->getY()]);
		//cout << endl << "product the path." << endl;
		if (stop_flag++ > 1000)
		{
			cout << "path error!" << endl;
			return;
		}
	}
}

int rrt::beInPathCheck(node node1)
{
	//cout << endl << "be in path check." << endl;
	for (int i = 0; i < path_.size(); i++)
	{
		if (node1 == *path_[i])
		{
			return 1;
		}
	}
	return 0;
}
