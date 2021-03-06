#include "stdafx.h"
#include <iostream>
#include <vector>
#include <fstream>
#include "windows.h"
#include "KMeans.h"
#include <string>

using namespace std;

int main()
{
	int n = 2; //Amount of iterations
	vector<vector<double>> points;
	fstream file("attract.txt", ios_base::in);

	if (file.is_open()) {
		while (!file.eof()) {
			vector<double> temp;
			string number;
			double data1, data2;
			getline(file, number, ',');
			data1 = stod(number);
			getline(file, number);
			data2 = stod(number);
			temp.push_back(data1);
			temp.push_back(data2);
			temp.push_back(0);
			points.push_back(temp);
		}
	}
	file.close();

	/*for (int i = 0; i < points.size(); i++)
	{
		for (int j = 0; j < points[0].size(); j++)
		{
			cout << points[i][j] << "\n";
		}
	}*/

	//Read points

	KMeans network(RANDOM_PARTITION, 6, points); //Init algorithm

	for (int i = 0; i < n; i++)
	{
		network.Recalculate(points); //Iterate the algorithm so grouping points find their place, and calculate SSE
		cout<<network.MSE(points)<<"\n";
	}

	//Write to file positions of found points
	network.outputCentroids("centroidy.txt");
	//Write to file SSE for each iteration

	system("pause");
    return 0;
}

