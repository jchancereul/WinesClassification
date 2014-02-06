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

	//We now have a MLP model and we also have the quality of the prediction thanks to the testing part
	//We can use the model to predict the label of other external data

	//Preliminary step: load the saved model from the HDD
	CvANN_MLP nnmodel;
	CvFileStorage* saved_model = cvOpenFileStorage("C:\\Users\\Julien\\Documents\\ENSAE\\C++\\Projet\\WinesClassification\\Results\\trained_models\\trained_model.xml", 0, CV_STORAGE_READ);
	CvFileNode *node = cvGetFileNodeByName(saved_model, 0, "WinesClassification");
	nnmodel.read(saved_model, node);
	cvReleaseFileStorage(&saved_model);

	//1- We have a whole matrix of samples to classify

	int nb_predict_samples = 100;

	//We still have to convert the data into an OpenCV matrix
	//We don't need the labels because we want to act as if we haven't them but it is much easier to use the same GetData method
	//so we will define two cv::Mat but use only one

	cv::Mat predict_var;
	cv::Mat predict_labels;
	cv::Mat predict_results;

	GetData("C:\\Users\\Julien\\Documents\\ENSAE\\C++\\Projet\\WinesClassification\\Data\\testing_dataset.csv", predict_var, predict_labels, nb_predict_samples,nb_var);
	
	nnmodel.predict(predict_var, predict_results); //Fill the predict_results matrix with the probability of being in a class for each sample

	cv::Mat classification_results(nb_predict_samples,1,CV_32FC2); //Matrix of the results of the classification using MLP (without probabilities)

	for (int i = 0; i < predict_results.rows; i++)
	{
		float predicted_class = predict_results.at<float>(0, 0);

		for (int j = 0; j < predict_results.cols; j++)
		{
			if (predict_results.at<float>(0, j) > predicted_class)
			{
				predicted_class = predict_results.at<float>(0, j);
			}
			int sample_classification = predicted_class;
			classification_results.at<float>(i,0) = sample_classification; //working??
		}
	}

	//The matrix of the results for each sample is now filled
	printf("Predicted quality of wines:\n");
	for (int i = 0; i < classification_results.rows; i++)
	{
		printf("Sample %d: class %d", i, classification_results.at<float>(i));
	}

	//2- We have only one sample to classify

	//Make a method that takes that sample and that calculate the predicted class using the MLP model: nnmodel.predict(sample,result)

	/**************************
	WORK TO DO:
	- The basic code is done but needs the data
	- Makes methods with the predict and 'extract the right predicted class' things
	- Re-organize the code into classes & methods ? --> object = MLP?
	- Method fot the very last point
	- Export to Qt
	***************************/

	/**************************
	WHAT IS DONE?
	- Creation of the MLP model -->perhaps add some error controlling methods and a 'number of layers in the network' method
	- Training and testing of the neural network
	- Save/ load the file containing the model
	- Predict the class of any external sample --> perhaps add a function 'recalcultate the model' if you don't want to use the .xml saved model
	***************************/
}