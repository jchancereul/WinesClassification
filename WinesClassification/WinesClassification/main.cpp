#include <iostream>
#include "DataHandler.h"
#include "NNModel.h"

void main()
{
	int nbSamples = 4898; 
	int nbVariables = 11;
	int nbLabels = 9;

	vector<vector<double>> dataMatrix(4898,vector<double>(12));

	//Import data from the initial .csv and normalize them
	DataHandler initialcsv("C:\\Users\\Julien\\Documents\\ENSAE\\C++\\Projet\\WinesClassification\\Data\\winequality-white.csv");
	initialcsv.DataAdapter(dataMatrix);

	//Get the dimensions of the matrix
	int rows = dataMatrix.size();
	int cols = dataMatrix[0].size();
	int nb_var = 11;
	int nb_label = 9;

	int training_samples = 2500;
	int testing_samples = 1000;

	//Creation of the OpenCV matrices
	cv::Mat training_matrix(training_samples, nb_var, CV_64F);
	cv::Mat training_classes(training_samples, nb_label+1, CV_64F,0.0); //nb_label +1 because the loop goes from 0 to 9 values so 10 values
	cv::Mat testing_matrix(testing_samples, nb_var, CV_64F);
	cv::Mat testing_classes(testing_samples, nb_label+1, CV_64F,0.0);

	//Fill the matrix with the data using the DataImporter method
	DataHandler trainingcsv("C:\\Users\\Julien\\Documents\\ENSAE\\C++\\Projet\\WinesClassification\\Results\\training_dataset.csv");
	DataHandler testingcsv("C:\\Users\\Julien\\Documents\\ENSAE\\C++\\Projet\\WinesClassification\\Results\\testing_dataset.csv");

	trainingcsv.DataImporter(training_matrix, training_classes, training_samples);
	testingcsv.DataImporter(testing_matrix, testing_classes, testing_samples);
	//The matrices are filled

	//Construction of the neural network model
	int nbInputVariables = 0;
	int nbOutputClasses = 0;
	CvANN_MLP MLP;

	NNModel nnmodel(nbInputVariables, nbOutputClasses, MLP);

	//Training of the model
	//nnmodel.Train(training_matrix, training_classes, "C:\\Users\\Julien\\Documents\\ENSAE\\C++\\Projet\\WinesClassification\\Results\\trained_models\\trained_model.xml");

	//Test of accuracy
	nnmodel.ShowAccuracy("C:\\Users\\Julien\\Documents\\ENSAE\\C++\\Projet\\WinesClassification\\Results\\trained_models\\trained_model.xml", testing_matrix, testing_classes);

	//Predict of the labels of the predict data
	int nbPredictSamples = 1398;
	cv::Mat predictData(nbPredictSamples,nb_var,CV_64F);
	cv::Mat predictLabels(nbPredictSamples,nb_label,CV_64F,0.0);
	DataHandler predictcsv("C:\\Users\\Julien\\Documents\\ENSAE\\C++\\Projet\\WinesClassification\\Data\\predict_dataset.csv");
	predictcsv.DataImporter(predictData, predictLabels, nbPredictSamples);

	cv::Mat classificationResults(nbPredictSamples,1,CV_32S);
	nnmodel.Predict("C:\\Users\\Julien\\Documents\\ENSAE\\C++\\Projet\\WinesClassification\\Results\\trained_models\\trained_model.xml", predictData, classificationResults);	
}