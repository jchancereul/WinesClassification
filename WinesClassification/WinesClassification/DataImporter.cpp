#include "DataImporter.h"
#include <fstream>

using namespace std;

//The aim of the Data Importer is to handle the input data
//and prepare it for the neural network.

//At this point we suppose that we have two datasets
//One for training the Multi Layer Perceptrons (MLP)
//The other to test the MLP

void GetData(char *filename, cv::Mat &inputdata, cv::Mat &outputdata, int nbsamples, int nbvariables)
{
	int label;			//label is the output classes labels
	double variable;	//variables are the input explanatory variables

	FILE* input = fopen(filename, "r"); //read the input data
	
	//determine the number of rows and cols in the input file
	const int rows = nbsamples;
	const int cols = nbvariables;

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j <= cols; j++)
		{
			//the input file gathers both the variables and the output classes
			//select the variables and the labels separately
			if (j < cols)
			{
				fscanf(input, "%f", &variable);
				inputdata.at<double>(i, j) = variable;
			}
			else if (j == cols)
			{
				fscanf(input, "%i", &label);
				outputdata.at<int>(i, label) = 1;
			}
		}
		//we have two cv::Matrices which contain the input and output data for the NN
	}
	fclose(input); //close the .csv file
}