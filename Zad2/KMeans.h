#pragma once
#include <vector>

using namespace std;

class KMeans
{
private:
	int groups;
	vector<vector<double>> centroids;
public:
	KMeans(int initMode, int groups); // 0 - Forgy; 1 - Random partition
	~KMeans();
	void Recalculate(vector<vector<double>> dataSet); //Euclidean distance from observation point to every given point and adjusting observation accordingly
	double MSE(); //Mean square error
	double distance(double x1, double y1, double x2, double y2); //Euclidean distance
};

