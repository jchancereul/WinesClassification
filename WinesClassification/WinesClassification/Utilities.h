#pragma once
#include <vector>

using namespace std;

class Utilities
{
	Utilities(vector<double> inputArray);
	~Utilities();

	double MinimumValue();
	double MaximumValue();

private:
	vector<double> _inputArray;
};