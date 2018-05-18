#include "stdafx.h"
#include "KMeans.h"


KMeans::KMeans(int initMode, int groups) : groups(groups)
{
	switch (initMode)
	{
	case 0:
		//---------------
		//Forgy init
		//Random observations
		break;
	case 1:
		//---------------
		//Random partition init
		//
		break;
	default:
		//---------------
		//TODO: Error handle
		break;
	}
}

KMeans::~KMeans()
{
}

void KMeans::Recalculate(vector<vector<double>> dataSet)
{
	for (vector<double> point : dataSet)
	{
		vector<double> distances;

		//Loop through all points per centroid and assign group
		for (int i = 0; i < groups; i++)
		{
			distances.push_back(distance(centroids[i][0], centroids[i][1], point[0], point[1]));
		}

		//Compare distances
	}
}

double KMeans::MSE()
{
	return 0;
}

double KMeans::distance(double x1, double y1, double x2, double y2)
{
	return (double)sqrtf((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
}
