#include "DataHandler.h"
#include <sstream>
#include <fstream>
#include <math.h>
#include <random>

DataHandler::DataHandler(char *filepath)
{
	_filepath = filepath;
}


DataHandler::~DataHandler()
{
}


void DataHandler::DataAdapter(vector<vector<double>> dataMatrix)
{
	//Import the .csv file using the fstream class
	vector<vector<double>> inputdata(dataMatrix.size()+1,vector<double>(dataMatrix[0].size()));
	ifstream file(_filepath);
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
			convertor >> inputdata[row][col]; //Fill the inputdata matrix with the values of the .csv
			col = col + 1;
		}
		row = row + 1;
		col = 0;
	}

	//Delete the first row of the matrix (headers)
	for (int i = 1; i < inputdata.size(); i++) //Start from the second line of inputdata
	{
		for (int j = 0; j < inputdata[0].size(); j++)
		{
			dataMatrix[i - 1][j] = inputdata[i][j];
		}
	}

	//Normalization of the matrix (except the last column)
	for (int j = 0; j<dataMatrix[0].size() - 1; j++)
	{
		vector<double> v(dataMatrix.size());
		vector<double> w(dataMatrix.size());

		for (int i = 0; i < dataMatrix.size(); i++)
		{
			w[i] = dataMatrix[i][j];
		}

		double a = *max_element(w.begin(),w.end());
		double b = *min_element(w.begin(), w.end());

		for (int i = 0; i < inputdata.size() - 1; i++)
		{
			v[i] = (w[i] - b) / (a - b);
			dataMatrix[i][j] = v[i];
		}
	}

	//Shuffle the matrix
	random_device rd;
	mt19937 g(rd());
	shuffle(dataMatrix.begin(), dataMatrix.end(), g);

	//Save the adapted data into 3 .csv's
	ofstream myfile1;
	myfile1.open("..\\..\\Results\\training_dataset.csv");

	for (int i = 0; i<floor((0.666)*dataMatrix.size()); i++) //select the first 2/3 elements of the database
	{
		for (int j = 0; j < dataMatrix[0].size(); j++)
		{
			myfile1 << dataMatrix[i][j] << ";";
		}
		myfile1 << endl;
	}
	myfile1.close();

	ofstream myfile2;
	myfile2.open("..\\..\\Results\\testing_dataset.csv");

	for (int i = floor((0.666)*dataMatrix.size()); i< floor((0.666)*dataMatrix.size()) + floor((0.166)*dataMatrix.size()); i++) //Select the next 1/6 samples
	{
		for (int j = 0; j < dataMatrix[0].size(); j++)
		{
			myfile2 << dataMatrix[i][j] << ";";
		}
		myfile2 << endl;
	}
	myfile2.close();

	ofstream myfile3;
	myfile3.open("..\\..\\Results\\predict_dataset.csv");

	for (int i = floor((0.666)*dataMatrix.size()) + floor((0.166)*dataMatrix.size()); i< dataMatrix.size(); i++) //Select the last samples
	{
		for (int j = 0; j < dataMatrix[0].size(); j++)
		{
			myfile3 << dataMatrix[i][j] << ";";
		}
		myfile3 << endl;
	}
	myfile3.close();
}


void DataHandler::DataImporter(cv::Mat &sampleData, cv::Mat &labels)
{
	vector<vector<double>> input(sampleData.rows, vector<double>(sampleData.cols+1));

	ifstream file(_filepath);
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
			convertor >> input[row][col]; //Fill the sampleData matrix with the values of the .csv
			col = col + 1;
		}
		row = row + 1;
		col = 0;
	}
	file.close();

	double variable;	//variables are the input explanatory variables
	int label;			//label is the output classes labels

	for (int i = 0; i < input.size(); i++)
	{
		for (int j = 0; j < input[0].size(); j++)
		{
			//the input file gathers both the variables and the output classes
			//select the variables and the labels separately
			if (j < input[0].size()-1)
			{
				variable = input[i][j];
				sampleData.at<double>(i, j) = variable;
			}
			else if (j == input[0].size()-1)
			{
				label = input[i][j];
				labels.at<double>(i, label) = 1.0; //the labels begin at 3 and go to 9
			}
		}
		//we have two cv::Matrices which contain the input and output data for the NN
	}
}