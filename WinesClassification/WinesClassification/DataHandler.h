#pragma once
#include <vector>
#include "opencv2/opencv.hpp"

using namespace std;

class DataHandler
{
public:
	DataHandler(char *filepath);
	~DataHandler();

	void DataAdapter(vector<vector<double>> dataMatrix);
	void DataImporter(cv::Mat &sampleData, cv::Mat &labels);

private:
	char *_filepath;
};

