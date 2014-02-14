#include "Utilities.h"


Utilities::Utilities(vector<double> inputArray)
{
	_inputArray = inputArray;
}

Utilities::~Utilities()
{
}


double Utilities::MaximumValue()
{
	int length = _inputArray.size();
	float max = _inputArray[0];

	for (int i = 1; i<length; i++)
	{
		if (_inputArray[i] > max)
			max = _inputArray[i];
	}
	return max;
}


double Utilities::MinimumValue()
{
	int length = _inputArray.size();
	float min = _inputArray[0];

	for (int i = 1; i<length; i++)
	{
		if (_inputArray[i] < min)
			min = _inputArray[i];
	}
	return min;
}