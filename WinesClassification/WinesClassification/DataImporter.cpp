#include "opencv2/opencv.hpp"
#include "opencv2/ml/ml.hpp"
#include <fstream>
#include <vector>

using namespace std;

void DataImporter(char *filename, cv::Mat &inputdata, cv::Mat &outputdata, int nbsamples, int nbvariables)
{
	int label;			//label is the output classes labels
	double variable;	//variables are the input explanatory variables

	vector<vector<double>> input;

	ifstream file(filename);
	string line;
	int col = 0;
	int row = 0;
	while (getline(file, line))
	{
		istringstream iss(line);
		string result;
		while (getline(iss, result, ';')) //The delimiter of the csv file is ";"
		{
			istringstream convertor(result); //Convert the string into a float number
			convertor >> input[row][col]; //Fill the inputdata matrix with the values of the .csv
			col = col + 1;
		}
		row = row + 1;
		col = 0;
	}
	file.close();

	for (int i = 0; i < input.size(); i++)
	{
		for (int j = 0; j <= input[0].size(); j++)
		{
			//the input file gathers both the variables and the output classes
			//select the variables and the labels separately
			if (j < input[0].size())
			{
				variable = input[i][j];
				inputdata.at<double>(i, j) = variable;
			}
			else if (j == input[0].size())
			{
				label = input[i][j];
				outputdata.at<int>(i, label) = 1;
			}
		}
		//we have two cv::Matrices which contain the input and output data for the NN
	}
}