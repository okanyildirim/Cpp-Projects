// ConsoleApplication3.cpp : Konsol uygulamasý için giriþ noktasýný tanýmlar.
//

#include <string>
#include <iostream>
#include <fstream>
#include <math.h>
#include <stdlib.h>

using namespace std;
int featureNumber = 93;

class Product {
private:
	int id;
	int feature[93];        // Each produch has id, feature array and label. Label represents class of product
	string label;
public:

	Product() {
		id = 0;						// Constructor
		label = "Class_0";
	}

	void setID(int idNumber) {       // Setter and Getter Methods
		id = idNumber;
	}

	void setLabel(string labelNumber) {
		label = labelNumber;
	}
	void setFeature(int featureArr[]) {

		for (int i = 0; i<93; i++) {
			feature[i] = featureArr[i];
		}
	}
	int getID() {
		return id;
	}
	string getLabel() {
		return label;
	}

	int getOneFeature(int index) {

		return feature[index];
	}

	int *getAllFeature() {
		return feature;
	}

	void displayFeatures() {

		for (int i = 0; i < featureNumber; i++)
		{
			cout << feature[i] << ",";
		}
		cout << endl << endl;
	}
};
struct forDistance {                          // At the merg sort part we come across a problem that we can not know product id of sorted distances. I add struc for solving this problem
	double distance;
	int id;
};

double eucledianDistance(int testArray[], int trainArray[]) {  // This function compute eucledian distances between products

	double distance = 0;
	int dimension = 0;
	for (int i = 0; i < featureNumber; i++) {

		dimension = (testArray[i] - trainArray[i])*(testArray[i] - trainArray[i]);
		distance += dimension;
		//cout << "arr1:  "<< testArray[i] << "  Arr2:  " << trainArray[i] << "    dimension:" <<dimension<< "    distance" << distance<<endl;
	}
	distance = sqrt(distance);
	//cout << "Nihai dis:" << distance;
	return distance;
}
void merge(forDistance objects[], int first, int middle, int last, int n) // mergesort is used for sorting distances of product from each other
{
	forDistance *tempArray = new forDistance[n];
	int first1 = first;
	int last1 = middle;
	int first2 = middle + 1;
	int last2 = last;
	int index = first1;
	for (; (first1 <= last1) && (first2 <= last2); ++index) {
		if (objects[first1].distance <objects[first2].distance) {
			tempArray[index] = objects[first1];
			++first1;
		}
		else {
			tempArray[index] = objects[first2];
			++first2;
		}
	}

	for (; first1 <= last1; ++first1, ++index)
		tempArray[index] = objects[first1];
	for (; first2 <= last2; ++first2, ++index)
		tempArray[index] = objects[first2];
	for (index = first; index <= last; ++index)
		objects[index] = tempArray[index];
}

void mergesort(forDistance object[], int first, int last, int n) {
	if (first<last) {
		int middle = (first + last) / 2;
		mergesort(object, first, middle, n);
		mergesort(object, middle + 1, last, n);
		merge(object, first, middle, last, n);
	}
}
int Max(int numbers[],int size) {   // for finding class of maximum number of nearest products

	int max = 0;
	for (int i = 1; i < size; i++)
	{
		if (numbers[i] > numbers[max]) {
			max = i;
		}
	}

	return max;
}

int main()
{
	/*int objTrainNumber = 61878;
	int objTestNumber = 144368;*/
	int objTrainNumber = 1000; // product number of given train data set
	int objTestNumber = 10; // product number of given test data set
	string titleArray[100];
	int objFeautereArray[93];

	int titleSize = 94;
	int key;
	string labelName;


Product *objTrain = new Product[objTrainNumber]; // object arrays are created
	Product *objTest = new Product[objTestNumber];
	forDistance *fordistance = new forDistance[objTrainNumber];

	ifstream inputTrain("train.txt");              // for reading from file
	ifstream inputTest("test.txt");
	cout << endl << "**********************Start*************************" << endl;
	/////////////////////////////////////////////////////////////////
	for (int i = 0; i < titleSize; i++)
	{
		inputTest >> titleArray[i];
		inputTrain >> titleArray[i];                // in given input set, we seperate title of file from exact data
		//cout << titleArray[i] ;
	}
	inputTrain >> titleArray[95];
	//cout << titleArray[95] << endl<< "********************** Start of Reading Train file*************************"<<endl;

	////////////////////////////////////////////////////////////////////
	for (int i = 0; i < objTrainNumber; i++)
	{
		//inputTrain >> array[i];
		inputTrain >> key;
		objTrain[i].setID(key);
		fordistance[i].id = key;
		//	cout << i <<". Object ID= " << objTrain[i].getID() << "F:";

		for (int j = 0; j < featureNumber; j++)
		{
			inputTrain >> objFeautereArray[j];
			//cout << " "<< objFeautereArray[j] <<"";
		}

		objTrain[i].setFeature(objFeautereArray);
		//	objTrain[i].displayFeatures();

		inputTrain >> labelName;
		objTrain[i].setLabel(labelName);
		//cout << "C:" << objTrain[i].getLabel() << endl;
	}
	//////////////////////////////////////////////////////////////////////////////////////*/
	cout << endl << "**********************Training Finish*************************" << endl;
	for (int i = 0; i < objTestNumber; i++)
	{
		inputTest >> key;
		objTest[i].setID(key);
		//cout << i << ". Object ID= " << objTest[i].getID() << "F:";

		for (int j = 0; j < featureNumber; j++)
		{
			inputTest >> objFeautereArray[j];
			//cout << " "<< objFeautereArray[j] <<"";
		}

		objTest[i].setFeature(objFeautereArray);
		//objTest[i].displayFeatures();
		cout << endl;
	}
	cout << endl << "**********************Reading Test Finish*************************" << endl;
	//////////////////////////////////////////////////////////////////////////

	int K = 123;
	int j = 0;
	while (j<objTestNumber) {
		//cout << j << ". Object ID= " << objTest[j].getID() << " Features:";
		objTest[j].displayFeatures();

		for (int i = 0; i < objTrainNumber; i++)
		{
			fordistance[i].distance = eucledianDistance(objTest[j].getAllFeature(), objTrain[i].getAllFeature()); // distances are calculated and located array for sorting
		}
		cout << "\n Distances are located in right places ";
		////////////////////////////////////////////////////////////////////////////

		/*for (int i = 0; i < objTrainNumber; i++)
		{
			cout << "id" << fordistance[i].id << "\t distances: " << fordistance[i].distance << endl;
		}*/

		mergesort(fordistance, 0, objTrainNumber-1, objTrainNumber); // objeler distancelarýna bakýlarak sýralandý

		cout << "\n ordered: \n";
		/*for (int i = 0; i < objTrainNumber; i++)
		{
			cout << "id" << fordistance[i].id << "\t distances: " << fordistance[i].distance << endl;
		}*/
		cout << "\n distancelar sýralandý";
		int counter[9] = { 0,0,0,0,0,0,0,0,0 }; // for counting class labels

		for (int i = 0; i < K ; i++)   // K many nearest distance of objects are counted
		{

			if (objTrain[fordistance[i].id-1].getLabel() == "Class_1") {
				counter[0]++;
			}
			else if (objTrain[fordistance[i].id - 1].getLabel() == "Class_2") {
				counter[1]++;
			}
			else if (objTrain[fordistance[i].id - 1].getLabel() == "Class_3") {
				counter[2]++;
			}
			else if (objTrain[fordistance[i].id - 1].getLabel() == "Class_4") {
				counter[3]++;
			}
			else if (objTrain[fordistance[i].id - 1].getLabel() == "Class_5") {
				counter[4]++;
			}
			else if (objTrain[fordistance[i].id - 1].getLabel() == "Class_6") {
				counter[5]++;
			}
			else if (objTrain[fordistance[i].id - 1].getLabel() == "Class_7") {
				counter[6]++;
			}
			else if (objTrain[fordistance[i].id - 1].getLabel() == "Class_8") {
				counter[7]++;
			}
			else if (objTrain[fordistance[i].id - 1].getLabel() == "Class_9") {
				counter[8]++;
			}

			else {
				cout << "*********There was an error. Class is undefined!*************" << endl;
			}
		}
		cout << "\n Class: \n";
		for (int i = 0; i < 9; i++)
		{
			cout << "Class counter " << counter[i] << endl;
		}

		int Class = Max(counter, 9); // Max nearest class label is determined
		for (int i = 0; i < 9; i++)
		{
			if (Class == 0) {
				objTest[j].setLabel("Class_1");
			}
			else if (Class == 1)
			{
				objTest[j].setLabel("Class_2");
			}
			else if (Class == 2)
			{
				objTest[j].setLabel("Class_3");
			}
			else if (Class == 3)
			{
				objTest[j].setLabel("Class_4");
			}
			else if (Class == 4)
			{
				objTest[j].setLabel("Class_5");
			}
			else if (Class == 5)
			{
				objTest[j].setLabel("Class_6");
			}
			else if (Class == 6)
			{
				objTest[j].setLabel("Class_7");
			}
			else if (Class == 7)
			{
				objTest[j].setLabel("Class_8");
			}
			else if (Class == 8)
			{
				objTest[j].setLabel("Class_9");
			}
		}

		cout << "\t\t************************************\n\n FINAL CLASS= " << objTest[j].getID() << "------->" << objTest[j].getLabel() << endl; // determined class label assigned to object

		for (int i = 0; i < objTrainNumber; i++) // fordistance id and distance are renewed
		{
			fordistance[i].id = i + 1;
			fordistance[i].distance = 0;
		}
		j++;


	}
	system("Pause");
	return 0;
}

