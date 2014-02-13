#include <iostream>
#include "DataImporter.h"
#include "NNModel.h"

void main()
{
	//We need the dimensions of the 4 matrices we will use (2x train, 2x test)
	const int nb_var = 11; //number of explanatory variables in the input data
	const int nb_label = 6; //number of labels of output classes
	const int training_samples = 2500; //number of samples in the training dataset
	const int testing_samples = 1000; //number of samples in the testing dataset

	//Creation of the OpenCV matrices
	cv::Mat training_matrix(training_samples, nb_var, CV_32FC2);
	cv::Mat training_classes(training_samples, nb_label, CV_32FC2);
	cv::Mat testing_matrix(testing_samples, nb_var, CV_32FC2);
	cv::Mat testing_classes(testing_samples, nb_label, CV_32FC2);

	//Fill the matrix with the data using the DataImporter method
	DataImporter("..\\Results\\datasets\\training_dataset.csv", training_matrix, training_classes, training_samples, nb_var);
	DataImporter("..\\Results\\datasets\\testing_dataset.csv", testing_matrix, testing_classes, testing_samples, nb_var);
	//The matrices are filled

	//Construction of the neural network model
	int nbInputVariables = 0;
	int nbOutputClasses = 0;
	CvANN_MLP MLP;

	NNModel nnmodel(nbInputVariables, nbOutputClasses, MLP);

	//Training of the model
	nnmodel.Train(training_matrix, training_classes, "..\\Results\\trained_models\\trained_model.xml");

	//Test of accuracy
	nnmodel.ShowAccuracy("..\\Results\\trained_models\\trained_model.xml", testing_matrix, testing_classes);

	//Predict of the labels of the predict data
	int nbPredictSamples = 4897 - 3500;
	cv::Mat predictData;
	cv::Mat predictLabels;
	DataImporter("..\\Data\\predict_dataset.csv", predictData, predictLabels, nbPredictSamples, nb_var);

	cv::Mat classificationResults;

	nnmodel.Predict("..\\Results\\trained_models\\trained_model.xml", predictData, classificationResults);
}