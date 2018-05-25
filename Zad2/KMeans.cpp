#include "stdafx.h"
#include "KMeans.h"
#include <ctime>
#include <cstdio>
#include <random>
#include <algorithm>
#include <fstream>
#include <iostream>

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
			this->centroids.push_back(dataSet[select]);
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
		//shuffle(begin(id), end(id), rng);

		for (vector<double> &points : dataSet)
		{
			//i = rand() % groups;
			points[2] = id[i];
			i++;
			if (i == groups)
			{
				i = 0;
				//shuffle(begin(id), end(id), rng);
			}
		}

		for (i = 0; i < groups; i++)
		{
			double sumX = 0;
			double sumY = 0;
			vector<double> temp;
			double count = 0;
			for (vector<double> &point : dataSet)
			{
				if ((int)point[2] == i)
				{
					sumX += point[0];
					sumY += point[1];
					count++;
				}
			}
			temp.push_back(sumX / count);
			temp.push_back(sumY / count);

			this->centroids.push_back(temp);
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
	
	for (int j = 0; j < dataSet.size(); j++)
	{
		vector<double> distances;

		//Loop through all points per centroid and assign group
		for (i = 0; i < groups; i++)
		{
			distances.push_back(distance(dataSet[j][0], dataSet[j][1], centroids[i][0], centroids[i][1]));
		}
		compare.push_back(distances);
	}

	i = 0;
	//Compare distances
	/*for (int j = 0; j < compare[0].size(); j++)
	{
		int minGroup = 0;
		double min = compare[i][0];
		for (int i = 0; i < groups; i++)
		{
			if (min > compare[i][j])
			{
				minGroup = i;
				min = compare[i][j];
				if (i == 3)
					cout << "3";
			}
		}
		dataSet[j][2] = (double)minGroup;
	}*/

	for (int j = 0; j < compare[0].size(); j++)
	{
		vector<double>::iterator result = min_element(begin(compare[j]), end(compare[j]));
		dataSet[j][2] = std::distance(begin(compare[j]), result);
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

		this->centroids[i][0] = sumX;
		this->centroids[i][1] = sumY;
	}
}

double KMeans::MSE(vector<vector<double>> dataSet)
{
	double sum = 0;
	for (int i = 0; i < dataSet.size(); i++)
	{
		double pointsum = 0;
		for (int j = 0; j < groups; j++)
		{
			pointsum += distance(dataSet[i][0], dataSet[i][1], centroids[j][0], centroids[j][1]);
		}
		sum += pointsum;
	}
	double result = (1 / (double)dataSet.size() * groups) * sum;
	return result;
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
