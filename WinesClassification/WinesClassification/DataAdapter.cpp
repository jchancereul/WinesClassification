#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

const int ROWS = 4899; //Number of lines in the input .csv
const int COLS = 12; //Number of columns in the input .csv
char *path = "..\\Data\\winequality-white.csv";

/*This method updates the matrix data into a reusable C++ capable matrix*/

void DataAdapter(string filename, vector<vector<double>> data)
{
	//Import the .csv file using the fstream class

	vector<vector<double>> inputdata;
	ifstream file(filename);
	string line;
	int col = 0;
	int row = 0;
	while (getline(file, line))
	{
		istringstream iss(line);
		string result;
		while (getline(iss, result, ';')) //The delimiter of the csv file is ";"
		{
			istringstream convertor(result); //Convert the string into a float number
			convertor >> inputdata[row][col]; //Fill the inputdata matrix with the values of the .csv
			col = col + 1;
		}
		row = row + 1;
		col = 0;
	}

	//Delete the first row of the matrix (headers)

	for (int i = 1; i < inputdata.size(); i++) //Start from the second line of inputdata
	{
		for (int j = 0; j < inputdata[0].size(); j++)
		{
			data[i][j] = inputdata[i][j];
		}
	}
}