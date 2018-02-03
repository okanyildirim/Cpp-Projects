/// OKAN YILDIRIM 150160537
// ANALYSIS of ALGORITHMS I - PROJECT - 3 PART A
#include <iostream>
#include <fstream>
#include <ctime>
#include <stdlib.h>
using namespace std;
class Numbers{					// Number Class is created and each number has id and value  

private:
	int id;
	long long int value;			// I use long long int for 10 digit numbers
public:
	Numbers(){				 // Constructer
		id = 0;
		value = 0;
	}

	void Setter(int number_id, double number_value){
		id = number_id;
		value = number_value;
	}													// Setter and Getter functions

	int Get_id(){
		return id;
	}

	long long int Get_value(){

		return value;
	}
};

long long int GetMax(Numbers arr[], int n)	// GetMax function is finding maximum value and return it. 
{															
	long long int max = arr[0].Get_value();		//Maximum value is important because we run counting sort as much as max value's
	for (int i = 1; i < n; i++)
	if (arr[i].Get_value() > max)
		max = arr[i].Get_value();
	return max;
}

// A function to do counting sort of arr[] according to
// the digit represented by exp.
void CountingSort(Numbers  arr[], int n, int dgt)
{

	Numbers *B_arr = new Numbers[n]; // B_array is output array 
	int i = 0;
	int C_arr[10];    // C_array is created and it's each element is zero
	for (i = 0; i < 10; i++) 
		C_arr[i] = 0;
	
	for (i = 0; i < n; i++)                               // counting part
		C_arr[(arr[i].Get_value() / dgt) % 10]++;


	for (i = 1; i < 10; i++)                     // cumulative additon part
		C_arr[i] += C_arr[i - 1];
	
	for (i = n - 1; i >= 0; i--)               // B_arr is built
	{
		B_arr[C_arr[(arr[i].Get_value() / dgt) % 10] - 1] = arr[i];
		C_arr[(arr[i].Get_value() / dgt) % 10]--;
	}
	
	for (i = 0; i < n; i++) // Our main array is arr so that copy B_arr
		arr[i] = B_arr[i];
}

// The main function to that sorts arr[] of size n using 
// Radix Sort
void Radixsort(Numbers arr[], int n)
{
	
	long long int max = GetMax(arr, n); // find max value

															
	for (int digit = 1; max / digit > 0; digit *= 10)		// sorting each digit until max digit
		CountingSort(arr, n, digit);
}

int main(int argc, char* argv[])
{
	clock_t  RadixSortstart, RadixSortfinish; // for displaying running time, use clock_t class from ctime library
	long int N = atoi(argv[1]); //Obtained values from user by entering on command line		*argv[2] = N

	
	Numbers * obj_arr = new Numbers[N]; // object array is created
	int n_id;
	long long int n_value;
	ifstream input("numbers_to_sort.txt"); //reading from file
	ofstream output("sorted_numbers.txt");// writing on file
	
	for (int i = 0; i < N; i++){
		input >> n_id;					//reading from file
		input >> n_value;
		obj_arr[i].Setter(n_id, n_value);
	//	cout << "id:" << obj_arr[i].Get_id() << "   value:" << obj_arr[i].Get_value() << endl; // if we want to check reading is done correctly
	}
	cout << endl << endl << endl << "        ==========================Radix Sorting==========================\n\n";
	RadixSortstart = clock(); // radix sort is beginning
	Radixsort(obj_arr, N);
	RadixSortfinish = clock(); // radix sort is completed


	for (int i = 0; i < N; i++) 
	  output << obj_arr[i].Get_id() << " " << obj_arr[i].Get_value() << endl; // write on file

	cout << "\n\n\t\t\t" << "RadixSort  Runingtime: " << ((double)(RadixSortfinish - RadixSortstart)) / (double)CLOCKS_PER_SEC << endl;// display runnin time

	system("Pause");
	return 0;
}

