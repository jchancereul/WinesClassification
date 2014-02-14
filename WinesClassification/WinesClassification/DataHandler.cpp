#include "DataHandler.h"
#include "Utilities.h"
#include <sstream>
#include <fstream>

DataHandler::DataHandler(string filepath)
{
	_filepath = filepath;
}


DataHandler::~DataHandler()
{
}


void DataHandler::DataAdapter(vector<vector<double>> dataMatrix)
{
	//Import the .csv file using the fstream class

	vector<vector<double>> inputdata;
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
			dataMatrix[i][j] = inputdata[i][j];
		}
	}

	//Normalization of the matrix (except the last column)

	for (int j = 0; j<dataMatrix[0].size() - 1; j++)
	{
		vector<double> v;
		vector<double> w;

		for (int i = 0; i < inputdata.size() - 1; i++)
		{
			w[i] = dataMatrix[i][j];
		}

		Utilities V(v); //bug, what??
		Utilities W(w);	//idem

		double a = W.MaximumValue(); //Functions cannot be reached....
		double b = W.MinimumValue();

		for (int i = 0; i < inputdata.size() - 1; i++)
		{
			v[i] = (w[i] - b) / (a - b);
			dataMatrix[i][j] = v[i];
		}
	}

	//Save the adapted data into 3 .csv's
	ofstream myfile1;
	myfile1.open("..//Results//training_dataset.csv");

	for (int i = 1; i<(2/3) * inputdata.size() -1; i++) //Select the 2500 first samples
	{
		for (int j = 0; j < inputdata[0].size(); j++)
		{
			myfile1 << dataMatrix[i][j] << ";";
		}
		myfile1 << endl;
	}
	myfile1.close();

	ofstream myfile2;
	myfile2.open("..//Results//testing_dataset.csv");

	for (int i = (2 / 3) * inputdata.size() - 1; i< (2 / 3) * inputdata.size() - 1 + (1/6) * inputdata.size(); i++) //Select 1000 other samples
	{
		for (int j = 0; j < inputdata[0].size(); j++)
		{
			myfile2 << dataMatrix[i][j] << ";";
		}
		myfile2 << endl;
	}
	myfile2.close();

	ofstream myfile3;
	myfile3.open("..//Results//predict_dataset.csv");

	for (int i = (2 / 3) * inputdata.size() - 1 + (1 / 6) * inputdata.size(); i< inputdata.size() -1; i++) //Select the last samples
	{
		for (int j = 0; j < inputdata[0].size(); j++)
		{
			myfile3 << dataMatrix[i][j] << ";";
		}
		myfile3 << endl;
	}
	myfile3.close();
}


void DataHandler::DataImporter(cv::Mat &sampleData, cv::Mat &labels)
{
	int label;			//label is the output classes labels
	double variable;	//variables are the input explanatory variables

	vector<vector<double>> input;

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

	for (int i = 0; i < input.size(); i++)
	{
		for (int j = 0; j <= input[0].size(); j++)
		{
			//the input file gathers both the variables and the output classes
			//select the variables and the labels separately
			if (j < input[0].size())
			{
				variable = input[i][j];
				sampleData.at<double>(i, j) = variable;
			}
			else if (j == input[0].size())
			{
				label = input[i][j];
				labels.at<int>(i, label) = 1;
			}
		}
		//we have two cv::Matrices which contain the input and output data for the NN
	}
}