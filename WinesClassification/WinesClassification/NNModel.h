#pragma once
#include "opencv2/opencv.hpp"
#include "opencv2/ml/ml.hpp"

class NNModel
{
public:
	NNModel(int nbInputVariables, int nbOutputClasses, CvANN_MLP MLP);
	~NNModel();

	void Train(cv::Mat trainingData, cv::Mat trainingClasses, char *path);
	void Predict(char *path, cv::Mat predictData, cv::Mat classificationResults);
	double Test(char *path, cv::Mat testData, cv::Mat testLabels);
	void ShowAccuracy(char *path, cv::Mat testData, cv::Mat testLabels);

private:
	int _nbInputVariables;
	int _nbOutputClasses;
	CvANN_MLP _MLP;
};