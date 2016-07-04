#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;
int min(int x, int y, int z)
{
	if(x>=y)
	{
		if(y>=z)
			return z;
		else 
			return y;
	}
	else
	{
		if(x>=z)
			return z;
		else 
			return x;
	}
}

//  The function for reading the input text file. //
void openFile(string file_name, ifstream & input_file)
{
	input_file.open(file_name.c_str());

	// Checking if the input is valid. //
	while (input_file.fail())  
	{
		cout << "Could not open the file " << file_name << endl;
		cout << "Enter the name of the input file: ";
		cin  >> file_name;
		input_file.open(file_name.c_str());
	}		
}

string fileToString(ifstream & input_file)
{
	string line;
	string file = "";
	while(getline(input_file, line))
	{
		file += line + "\n";
	}
	input_file.close();
	return file;
}

int main()
{
	string word1, word2, file_name1, file_name2;
	ifstream input_file;
	/*cout << "Please enter the first word: ";
	cin >> word1;
	cout << "Please enter the second word that you would like the calculate its distance to the first: ";
	cin >> word2;*/

	cout << "Please enter the name of the first file: ";
	cin >> file_name1;
	cout << "Please enter the name of the second fil that you would like the calculate its distance to the first: ";
	cin >> file_name2;

	openFile(file_name1, input_file);
	word1 = fileToString(input_file);
	cout << endl << "File 1:" << endl << word1;
	
	openFile(file_name2, input_file);
	word2 = fileToString(input_file);
	cout << endl << "File 2:" << endl << word2;



	int row = word1.length() + 1;
	int column = word2.length() + 1;
	vector<vector<int>> edit_distance(row, vector<int>(column));
	for(int i = 0; i< row; i++)
	{
		edit_distance[i][0] = i;
	}

	for(int i = 0; i < column; i++)
	{
		edit_distance[0][i] = i;
	}

	for(int i = 1; i < row; i++)
	{
		for(int j = 1; j < column; j++)
		{
			if (word1[i-1] == word2[j-1])
			{
				edit_distance[i][j] = edit_distance[i-1][j-1];
			}
            else 
			{
				edit_distance[i][j] = 1 + min(edit_distance[i][j-1],edit_distance[i-1][j],edit_distance[i-1][j-1]);	
			}
		}
	}

	//  Console output for debugging reasons.  //
	/*
	cout << endl << endl; 
	for(int i = 0; i < row; i++)
	{
		for(int j = 0; j < column; j++)
		{
			cout << edit_distance[i][j] << "   ";
		}
		cout << endl;
	}*/

	cout << "The maximum distance from " << file_name1 << " to " << file_name2 << "  is: " << edit_distance[row-1][column-1] << endl;

	cin.get();
	cin.ignore();
	return 0;
}