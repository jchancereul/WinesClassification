#include <iostream>
#include "DataHandler.h"
#include "NNModel.h"
#include <math.h>

void main()
{
	//Define the sizes of the array and matrices of the whole project
	int nbSamples = 4898;
	int nbVariables = 11;
	int nbLabels = 10;

	int nbTrainingSamples = floor((0.666)*nbSamples);
	int nbTestingSamples = floor((0.166)*nbSamples);
	int nbPredictSamples = nbSamples - nbTrainingSamples - nbTestingSamples;

	//Define the initial data matrix containing the data of the source .csv
	vector<vector<double>> dataMatrix(nbSamples,vector<double>(nbVariables+1));

	//Import data from the initial .csv and normalize them
	DataHandler initialcsv("..\\..\\Data\\winequality-white.csv");
	initialcsv.DataAdapter(dataMatrix);

	//Creation of the OpenCV matrices
	cv::Mat trainingData(nbTrainingSamples, nbVariables, CV_64F);
	cv::Mat trainingLabels(nbTrainingSamples, nbLabels, CV_64F,0.0);
	cv::Mat testingData(nbTestingSamples, nbVariables, CV_64F);
	cv::Mat testingLabels(nbTestingSamples, nbLabels, CV_64F,0.0);

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

	//Test for accuracy
	nnmodel.ShowAccuracy("..\\..\\Results\\trained_models\\trained_model.xml", testingData, testingLabels);

	//Predict of the labels of the predict data
	cv::Mat predictData(nbPredictSamples,nbVariables,CV_64F);
	cv::Mat predictLabels(nbPredictSamples,nbLabels,CV_64F,0.0);
	DataHandler predictcsv("..\\..\\Data\\predict_dataset.csv");
	predictcsv.DataImporter(predictData, predictLabels);

	cv::Mat classificationResults(nbPredictSamples,1,CV_32S);
	nnmodel.Predict("..\\..\\Results\\trained_models\\trained_model.xml", predictData, classificationResults);	
}