#include <iostream>
#include "DataImporter.h"

void main()
{
	//We need the dimensions of the 4 matrices we will use (2x train, 2x test)
	const int nb_var = 10; //number of explanatory variables in the input data
	const int nb_label = 6; //number of labels of output classes
	const int training_samples = 3000; //number of samples in the training dataset
	const int testing_samples = 1000; //number of samples in the testing dataset

	//Creation of the OpenCV matrices
	cv::Mat training_matrix(training_samples, nb_var,CV_32FC2);
	cv::Mat training_classes(training_samples, nb_label, CV_32FC2);
	cv::Mat testing_matrix(testing_samples, nb_var, CV_32FC2);
	cv::Mat testing_classes(testing_samples, nb_label, CV_32FC2);

	//Fill the matrix with the data using the GetData method
	GetData("C:\\Users\\Julien\\Documents\\ENSAE\\C++\\Projet\\WinesClassification\\Data\\training_dataset.csv", training_matrix, training_classes, training_samples, nb_var);
	GetData("C:\\Users\\Julien\\Documents\\ENSAE\\C++\\Projet\\WinesClassification\\Data\\testing_dataset.csv", testing_matrix, testing_classes, testing_samples, nb_var);
	//The matrices are filled

	//Create the MLP network using the CvANN_MLP class in OpenCV
	//1- Choosing the number of neurons in each layer.
	//We arbitrary choose 3 layers:
		//10 neurons in the input layer (10 explanatory variables)
		//8 neurons in the hidden layer (arbitrary)
		//6 neurons in the output layer (6 qualitites of wine)
	cv::Mat layers(3, 1, CV_32FC2);
	layers.at<int>(0, 0) = 10;
	layers.at<int>(1, 0) = 8;
	layers.at<int>(2, 0) = 6;

	//2- Create the structure of the neural network
	CvANN_MLP MLP(layers, CvANN_MLP::SIGMOID_SYM, 1, 1);

	//3- Train the weights of the neural network
	CvANN_MLP_TrainParams params(
		cvTermCriteria(CV_TERMCRIT_ITER + CV_TERMCRIT_EPS, 1000, 0.001),	//Terminaison criterion: either the maximum number of iterations is reached or the error is below epsilon
		CvANN_MLP_TrainParams::BACKPROP,									//Training method: back-propagation
		0.1,																//Back-propagation method parameters (found in the CvANN_MLP documentation)
		0.1);

	//The neural network is now created
	//Training
	MLP.train(training_matrix, training_classes, cv::Mat(), cv::Mat(), params);
	//Model trained using the previous training matrices and the params method

	//Save the trained model into a .xml file
	CvFileStorage* saved_model = cvOpenFileStorage("C:\\Users\\Julien\\Documents\\ENSAE\\C++\\Projet\\WinesClassification\\Results\\trained_models\\trained_model.xml", 0, CV_STORAGE_WRITE);
	MLP.write(saved_model,"Wines Classification");
	cvReleaseFileStorage(&saved_model);

	//Testing
	//Check if the trained model is still exact using unknown data
	cv::Mat testing_results;
	cv::Mat testing_sample;
	int good_prediction;
	int bad_prediction;

	for (int i = 0; i < testing_matrix.rows; i++)
	{
		testing_sample = testing_matrix.row(i);
		MLP.predict(testing_sample, testing_results);

		//predict returns an array of the probability for the sample of being in each output class
		//Compute the right predicted value for the sample
		float right_value = testing_results.at<float>(0,0);
		int right_value_rank;

		for (int j = 0; j < testing_results.cols; j++)
		{
			if (testing_results.at<float>(0, j) > right_value)
			{
				right_value = testing_results.at<float>(0, j);
				right_value_rank = j;
			}
		}
		//The predicted class of the sample i is now calculated

		//Check if the predicted class is the good one
		if (testing_classes.at<int>(i, right_value_rank) == 1) { good_prediction++; }
		else { bad_prediction++; }
	}

	//Print the accuracy of the model
	printf("Correct classification: %f%% \n Incorrect classification: %f%%\n",
		(float)good_prediction / nb_var * 100, (float)bad_prediction / nb_var * 100);
}