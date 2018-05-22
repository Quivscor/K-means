#pragma once
#include <vector>
#define FORGY 0
#define RANDOM_PARTITION 1

using namespace std;

class KMeans
{
private:
	int groups;
	vector<vector<double>> centroids;
public:
	KMeans(int initMode, int groups, vector<vector<double>> &dataSet); // 0 - Forgy; 1 - Random partition
	~KMeans();
	void Recalculate(vector<vector<double>> &dataSet); //Euclidean distance from observation point to every given point and adjusting observation accordingly
	double MSE(vector<vector<double>> dataSet); //Mean square error
	double distance(double x1, double y1, double x2, double y2); //Euclidean distance
	void outputCentroids(string filename);
	void outputMSE(string filename);
};

