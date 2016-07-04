#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// The struct for holding the weights and the values of the items that are going to be put in the knapsack. //
struct Item
{
	int weight;
	int value;
	Item::Item(int w, int v)
		:weight(w), value(v)
	{}
};

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

vector<Item> createList(ifstream & input_file, int & capacity)
{
	string line;
	int value, weight;
	vector <Item> list;
	bool firstline = true;
	
	while(getline(input_file, line))
	{
		stringstream ss(line);

		//  The first line on the file is the capacity of the knapsack. //
		if(firstline)
		{
			ss>>value;
			capacity = value;
			firstline = false;
		}

		// The rest of the file consists of the weights and values. //
		else
		{
			while(ss >> weight >> value)
			{
				list.push_back(Item(weight,value));
			}
		}	
	}
	return  list;
}

int max(int x, int y)
{
	if(x >= y)
		return x;
	else 
		return y;
}

int main()
{
	ifstream input_file;
	string file_name;
	int capacity;
	vector <Item> list;

	//  Console output for asking the name of the file. //
	cout << "Please note that for this program to work properly, the first line should be the capacity of the knapsack. " << endl <<endl
		 << "And the following lines should consist of the weight and the value of the object with white space inbetween respectively. " << endl << endl
         << "Please enter the name of the input file: ";
	cin >> file_name;

	//  The function that opens the text file. //
	openFile(file_name, input_file);

	//  The function that reads the input file line by line and inserts the values and weights into a vector.  //
	list = createList(input_file, capacity);

	//  Console output for debugging reasons.  //
	cout << "Capacity: " << capacity << endl;
	for(int i= 0; i<list.size(); i++)
	{
		cout << "Weight: " << list[i].weight <<  " Value: " << list[i].value << endl; 
	}

	//  Creating the matrix for calculating the maximal solution. //
	int row = list.size() + 1;
	int column = capacity + 1; 
	vector<vector <int>> knapsack(row, vector<int>(column));
	vector<vector <int>> keep(row, vector<int>(column));

	//  If there is no item to pick then the knapsack can't take anything.  //
	for(int i = 0; i < column; i++)
	{
		knapsack[0][i] = 0;
		keep[0][i] = 0;
	}

	// If the knapsack capacity is 0, then we can't put anything in.  //
	for(int i = 0; i < row; i++)
	{
		knapsack[i][0] = 0;
		keep[i][0] = 0;
	}
	
	for(int i = 1; i < row; i++)
	{
		for(int j = 1; j < column; j++ )
		{
			//  If the item is too heavy for the current column, then we copy the upper row's value on the same column. //
			if(list[i-1].weight > j)
			{
				knapsack[i][j] = knapsack[i-1][j];
				keep[i][j] = 0;
			}

			// Otherwise, the value is the maximum between the value of the current row's item and the extra weight (if there is any) from the items until that row  //
			// and the upper row's value on the same column.  /////////////////////////////////////////////////////////////////////////////////////////////////////////
			else
			{
				int maximum = max(knapsack[i-1][j], ((knapsack[i-1][j-list[i-1].weight]) + list[i-1].value));
				knapsack[i][j] = maximum;
				if(maximum == knapsack[i-1][j])
				{
					keep[i][j] = 0;
				}
				else
				{
					keep[i][j] = 1;
				}
			}
		}
	}

	// Console output for debugging reasons. //
	cout << endl << "Knapsack array: " << endl;
	for(int i = 0; i < row; i ++)
	{
		for(int j = 0; j < column; j++ )
		{
			cout << knapsack[i][j] << "  ";
		}
		cout << endl;
	}

	cout << endl << "Keep array: " << endl;
	for(int i = 0; i < row; i ++)
	{
		for(int j = 0; j < column; j++ )
		{
			cout << keep[i][j] << "  ";
		}
		cout << endl;
	}

	//  After we find the maximum value that the knapsack can hold, we backtrack our keep array to find the items which gives us the maximum value.  //
	int i = row - 1;
	int j= column - 1;
	int c = capacity;
	vector<Item> inside;
	//  While the knapsack isn't full  //
	while(j > 0)
	{
		// If the item we have had changed the maximum value in the knapsack.  //
		if(keep[i][j] == 1)
		{
			inside.push_back(list[i-1]);
			j = j - list[i-1].weight;
			i--;
			//j--;
		}
		else
		{
			i--;
		}
	}

	//  Console output for debugging reasons.  //
	cout << endl << "The item/items in the knapsack: " << endl;
	for(int a = 0; a < inside.size(); a++)
	{
		cout << "Weight: " << inside[a].weight << " Value: " << inside[a].value << endl;
	}

	cin.get();
	cin.ignore();
	return 0;
}