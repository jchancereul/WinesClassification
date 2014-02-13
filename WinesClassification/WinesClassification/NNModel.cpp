#include "NNModel.h"
#include "opencv2/opencv.hpp"
#include "opencv2/ml/ml.hpp"

using namespace std;

NNModel::NNModel(int nbInputVariables, int nbOutputClasses, CvANN_MLP MLP)
{
	_nbInputVariables = nbInputVariables;
	_nbOutputClasses = nbOutputClasses;
	_MLP = MLP;
}

NNModel::~NNModel()
{
}

void NNModel::Train(cv::Mat trainingData, cv::Mat trainingClasses, char *path)
{
	_nbInputVariables = trainingData.cols;
	_nbOutputClasses = trainingClasses.cols;

	//Create the MLP network using the CvANN_MLP class in OpenCV
	//1- Choosing the number of neurons in each layer.
	//We arbitrary choose 3 layers:
	//10 neurons in the input layer (10 explanatory variables)
	//8 neurons in the hidden layer (arbitrary)
	//6 neurons in the output layer (6 qualitites of wine)
	cv::Mat layers(3, 1, CV_32FC2);
	layers.at<int>(0, 0) = _nbInputVariables;
	layers.at<int>(1, 0) = (_nbInputVariables+_nbOutputClasses)/2; //check here
	layers.at<int>(2, 0) = _nbOutputClasses;

	//2- Create the structure of the neural network
	_MLP = CvANN_MLP(layers, CvANN_MLP::SIGMOID_SYM, 1, 1);

	//3- Train the weights of the neural network
	CvANN_MLP_TrainParams params(
		cvTermCriteria(CV_TERMCRIT_ITER + CV_TERMCRIT_EPS, 10000, 0.0001),	//Terminaison criterion: either the maximum number of iterations is reached or the error is below epsilon
		CvANN_MLP_TrainParams::BACKPROP,									//Training method: back-propagation
		0.1,																//Back-propagation method parameters (found in the CvANN_MLP documentation)
		0.1);

	//The neural network is now created
	//Training
	_MLP.train(trainingData, trainingClasses, cv::Mat(), cv::Mat(), params);
	//Model trained using the previous training matrices and the params method

	//Save the trained model into a .xml file
	CvFileStorage* saved_model = cvOpenFileStorage(path, 0, CV_STORAGE_WRITE);
	_MLP.write(saved_model, "WinesClassification");
	cvReleaseFileStorage(&saved_model);
}

void Predict(char *path, cv::Mat predictData, cv::Mat classificationResults)
{
	/*
	path is the path of the stored trained NNModel if it exists
	The predictData matrix is the samples matrix to use during the prediction
	The classificationResults matrix is a (nbSamples, 1) array. It will be filled with the predicted labels of each sample.
	*/

	//Preliminary step: load the saved model from the HDD
	CvANN_MLP nnmodel;
	CvFileStorage* stored_model = cvOpenFileStorage(path, 0, CV_STORAGE_READ);
	CvFileNode *node = cvGetFileNodeByName(stored_model, 0, "WinesClassification");
	nnmodel.read(stored_model, node);
	cvReleaseFileStorage(&stored_model);

	int nbSamples = predictData.rows;
	int nbVar = predictData.cols;
	cv::Mat predictResults;

	nnmodel.predict(predictData, predictResults); //Fill the predict_results matrix with the probability of being in a class for each sample

	for (int i = 0; i < predictResults.rows; i++)
	{
		double predictedClass = predictResults.at<double>(0, 0);
		for (int j = 0; j < predictResults.cols; j++)
		{
			if (predictResults.at<double>(0, j) > predictedClass)
			{
				predictedClass = predictResults.at<double>(0, j);
			}
			int sampleLabel = predictedClass;
			classificationResults.at<double>(i, 0) = sampleLabel; //working??
		}
	}
}

double Test(char *path, cv::Mat testData, cv::Mat testLabels)
{
	//Check if the trained model is still exact using unknown data
	cv::Mat testingResults;
	cv::Mat testingSample;
	int goodPrediction = 0;

	Predict(path, testData, testingResults);

	for (int i = 0; i < testingResults.rows; i++)
	{
		int labelRank;
		for (int j = 0; j < testLabels.cols; j++)
		{
			if (testLabels.at<int>(i, j) == 1) { labelRank = j; }
		}
		if (testingResults.at<double>(0, i) == labelRank){ goodPrediction++; }
	}
	return (double)goodPrediction / testData.rows * 100;
}

void ShowAccuracy(char *path, cv::Mat testData, cv::Mat testLabels)
{
	printf("Model accuracy: %f%% \n", Test(path, testData, testLabels));
}