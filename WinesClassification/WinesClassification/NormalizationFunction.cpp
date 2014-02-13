float MaximumValue(float inputarray[], int length)
{
	float max = inputarray[0];

	for (int i = 1; i<length; i++)
	{
		if (inputarray[i] > max)
			max = inputarray[i];
	}
	return max;
}

float MinimumValue(float inputarray[], int length)
{
	float min = inputarray[0];

	for (int i = 1; i<length; i++)
	{
		if (inputarray[i] < min)
			min = inputarray[i];
	}
	return min;
}