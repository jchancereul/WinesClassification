#include <fstream>
#include <string>
#include <sstream>

using namespace std;

const int ROWS = 4899; //Number of lines in the input .csv
const int COLS = 12; //Number of columns in the input .csv
char *path = "..\\Data\\winequality-white.csv";

/*This method updates the matrix data into a reusable C++ capable matrix*/

void ImportData(char *filename, float data[ROWS - 1][COLS])
{
	//Import the .csv file using the fstream class

	float inputdata[ROWS][COLS];
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

	for (int i = 1; i < ROWS; i++) //Start from the second line of inputdata
	{
		for (int j = 0; j < COLS; j++)
		{
			data[i][j] = inputdata[i][j];
		}
	}
}

//WORK TO DO:
//See if one cannot use struct or build a matrix class