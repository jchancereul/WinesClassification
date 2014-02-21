#include <iostream>
#include "DataHandler.h"
#include "NNModel.h"
#include <math.h>
#include <fstream>

using namespace std;

void main()
{
	/*******************************************************************************************************/
	/***********************************************TRAIN***************************************************/
	/*******************************************************************************************************/


	//Define the sizes of the array and matrices of the whole project
	int nbSamples = 4898;
	int nbVariables = 11;
	int nbLabels = 10;

	int nbTrainingSamples = floor((0.666)*nbSamples);
	int nbTestingSamples = floor((0.166)*nbSamples);
	int nbPredictSamples = nbSamples - nbTrainingSamples - nbTestingSamples;

	//Define the initial data matrix containing the data of the source .csv and the maxima & minima arrays
	vector<vector<double>> dataMatrix(nbSamples, vector<double>(nbVariables + 1));

	//Import data from the initial .csv and normalize them
	DataHandler initialcsv("..\\..\\Data\\winequality-white.csv");
	initialcsv.DataAdapter(dataMatrix);

	//Creation of the OpenCV matrices
	cv::Mat trainingData(nbTrainingSamples, nbVariables, CV_64F);
	cv::Mat trainingLabels(nbTrainingSamples, nbLabels, CV_64F, 0.0);
	cv::Mat testingData(nbTestingSamples, nbVariables, CV_64F);
	cv::Mat testingLabels(nbTestingSamples, nbLabels, CV_64F, 0.0);

	//Fill the matrix with the data using the DataImporter method
	DataHandler trainingcsv("..\\..\\Results\\training_dataset.csv");
	DataHandler testingcsv("..\\..\\Results\\testing_dataset.csv");
	trainingcsv.DataImporter(trainingData, trainingLabels);
	testingcsv.DataImporter(testingData, testingLabels);
	//The matrices are filled

	//Construction of the neural network model
	int nbInputVariables = 0;
	int nbOutputClasses = 0;
	CvANN_MLP MLP;
	NNModel nnmodel(nbInputVariables, nbOutputClasses, MLP);

	//Training of the model
	nnmodel.Train(trainingData, trainingLabels, "..\\..\\Results\\trained_models\\trained_model.xml");

	//Test for accuracy (optional)
	//nnmodel.ShowAccuracy("..\\..\\Results\\trained_models\\trained_model.xml", testingData, testingLabels);


	/*******************************************************************************************************/
	/**********************************************PREDICT**************************************************/
	/*******************************************************************************************************/


	//Get the data to predict in an array
	vector<double> predictVector;
	double result;

	cout << "Please enter your data:\n";
	vector<string> characteristics = { "fixed acidity", "volatile acidity", "citric acid", "residual sugar", "chlorides",
		"free sulfur dioxide", "total sulfur dioxide", "density", "pH", "sulphates", "alcohol" };

	for (int i = 0; i < nbVariables; i++)
	{
		cout << characteristics[i] << "\t";
		cin >> result;
		predictVector.push_back(result);
	}

	//Normalize the array
	vector<double> maxima = { 14.2, 1.1, 1.66, 19.95, 0.346, 82.5, 336.5, 1.03898, 3.82, 1.08, 14.2 };
	vector<double> minima = { 0.05, 0.08, 0, 0.01, 0.009, 0.02, 0.09, 0.01, 0.03, 0.01, 0.08 };

	vector<double> v = predictVector;
	for (int i = 0; i < nbVariables; i++)
	{
		double a = maxima[i];
		double b = minima[i];
		predictVector[i] = (v[i] - b) / (a - b);
	}
	
	//Add a fake label to fit the class dataHandel
	predictVector.push_back(0.0);

	//Save it into a .csv
	ofstream myfile;
	myfile.open("..\\..\\Results\\predict_data.csv");
	for (int i = 0; i< predictVector.size(); i++)
	{
		myfile << predictVector[i] << ";";
	}
	myfile.close();

	//Predict the class label using the stored neural network model
	cv::Mat predictData(1, nbVariables, CV_64F);
	cv::Mat predictLabels(1, nbLabels, CV_64F, 0.0);
	DataHandler predictcsv("..\\..\\Data\\predict_data.csv");
	predictcsv.DataImporter(predictData, predictLabels);

	cv::Mat classificationResults(1, 1, CV_32S);
	nnmodel.Predict("..\\..\\Results\\trained_models\\trained_model.xml", predictData, classificationResults);
}