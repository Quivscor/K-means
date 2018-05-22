#include "stdafx.h"
#include "KMeans.h"
#include <ctime>
#include <cstdio>
#include <random>
#include <algorithm>
#include <fstream>

KMeans::KMeans(int initMode, int groups, vector<vector<double>> &dataSet) : groups(groups)
{
	vector<int> id;
	auto rng = default_random_engine{};

	switch (initMode)
	{
	case 0:
		//---------------
		//Forgy init
		//Random observations
		int select;

		srand(time(NULL));
		for (int i = 0; i < groups; i++)
		{
			select = rand() % 1000;
			centroids.push_back(dataSet[select]);
		}
		break;
	case 1:
	{
		//---------------
		//Random partition init
		//Assign random clusters and spawn centroids at the weight center
		for (int i = 0; i < groups; i++)
			id.push_back(i);

		int i = 0;
		shuffle(begin(id), end(id), rng);

		for (vector<double> points : dataSet)
		{
			points[2] = id[i];
			i++;
			if (i == groups)
			{
				i = 0;
				shuffle(begin(id), end(id), rng);
			}
		}

		for (i = 0; i < groups; i++)
		{
			double sumX = 0;
			double sumY = 0;
			vector<double> temp;
			double count = 0;
			for (vector<double> point : dataSet)
			{
				if (point[2] == i)
				{
					sumX += point[0];
					sumY += point[1];
					count++;
				}
			}
			temp.push_back(sumX / count);
			temp.push_back(sumY / count);

			centroids.push_back(temp);
		}
		break;
	}
	default:
		//---------------
		//TODO: Error handle
		break;
	}
}

KMeans::~KMeans()
{
}

void KMeans::Recalculate(vector<vector<double>> &dataSet)
{
	int i = 0;
	vector<vector<double>> compare;
	for (i = 0; i < groups; i++)
	{
		vector<double> distances;

		//Loop through all points per centroid and assign group
		for (vector<double> point : dataSet)
		{
			distances.push_back(distance(point[0], point[1], centroids[i][0], centroids[i][1]));
		}
		compare.push_back(distances);
	}

	i = 0;
	//Compare distances
	for (int j = 0; j < compare[0].size(); j++)
	{
		int minGroup = 0;
		double min = compare[i][0];
		for (int i = 0; i < groups; i++)
		{
			if (min > compare[i][j])
			{
				minGroup = i;
				min = compare[i][j];
			}
		}
		dataSet[j][2] = (double)minGroup;
	}

	//Calculating center of mass
	for (i = 0; i < groups; i++)
	{
		double sumX = 0;
		double sumY = 0;
		double count = 0;
		for (vector<double> point : dataSet)
		{
			if (point[2] == i)
			{
				sumX += point[0];
				sumY += point[1];
				count++;
			}
		}
		sumX = sumX / count;
		sumY = sumY / count;

		centroids[i][0] = sumX;
		centroids[i][1] = sumY;
	}
}

double KMeans::MSE(vector<vector<double>> dataSet)
{
	double sum;
	for (int i = 0; i < dataSet.size(); i++)
	{
		double pointsum;
		for (int j = 0; j < groups; j++)
		{
			
		}
	}
	return 1/ dataSet.size();
}

double KMeans::distance(double x1, double y1, double x2, double y2)
{
	return (double)sqrtf((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
}

void KMeans::outputCentroids(string filename)
{
	fstream file(filename, ios_base::out);
	for (vector<double> point : centroids)
	{
		file << point[0];
		file << ",";
		file << point[1];
		file << "\n";
	}
	file.close();
}

void KMeans::outputMSE(string filename)
{

}
