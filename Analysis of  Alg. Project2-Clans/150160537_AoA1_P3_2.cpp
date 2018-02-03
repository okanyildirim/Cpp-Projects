// ConsoleApplication2.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <fstream>
#include <ctime>
#include <stdlib.h>
using namespace std;

class Player{		// Player Class is created and each number has id and cp  

private:
	long int id;
	int cp;

public:
	Player(){		 // Constructer
		id = 0;
		cp = 0;
	}

	void Setter(int plyr_id, int plyr_cp){			// Setter and Getter functions
		id = plyr_id;	
		cp = plyr_cp;
	}

	long int Get_id(){
		return id;
	}

	int Get_cp(){
		return cp;
	}
};

void swap(Player & a, Player & b)

{
	Player x;
	x = a;
	a = b;
	b = x;

}

void MAX_HEAPIFY(Player arr[], int i,long int n)
{
	int l, r, largest;
	l = 2 * i;
	r = (2 * i + 1);
	if ((l <= n) && arr[l].Get_cp()>arr[i].Get_cp())
		largest = l;
	else
		largest = i;
	if ((r <= n) && (arr[r].Get_cp()>arr[largest].Get_cp()))
		largest = r;
	if (largest != i)
	{
		swap(arr[i],arr[largest]);
		MAX_HEAPIFY(arr, largest, n);
	}
}
void BUILD_MAX_HEAP(Player arr[],long int n)
{
	for (int k = n / 2; k >= 1; k--)
	{
		MAX_HEAPIFY(arr, k, n);
	}
}
void HEAPSORT(Player arr[], long int n)
{

	BUILD_MAX_HEAP(arr, n);
	int i;
	
	for (i = n; i >= 2; i--)
	{
		swap(arr[i], arr[1]);
		MAX_HEAPIFY(arr, 1, i - 1);
	}
}

int main(int argc, char* argv[])
{
    long int N = atoi(argv[2]); //Obtained values from user by entering on command line		*argv[2] = N							
	int selection=atoi(argv[1]); 
	clock_t  HeapSortstart, HeapSortfinish;
	Player *obj_arr = new Player[N];// object array is created
	Player *obj_arrB = new Player[N];// object array is created

	ifstream inputA("ClanA.txt");		//reading from file
	ifstream inputB("ClanB.txt");		// writing on file
	ifstream inputC("gamelogs.txt");
	ofstream output("A_sorted.txt");
	int p_id, p_cp;
	int log_id, attacker_id,attacked_id;		//reeading from file
	char clantype;

	obj_arr[0].Setter(0, 0);
	obj_arrB[0].Setter(0, 0);
	switch (selection)
	{

	case 1:
		
		for (int i = 1; i <= N; i++)
	{
			   inputA >> p_id;		//reeading from file
			   inputA >> p_cp;
			   obj_arr[i].Setter(p_id, p_cp);
			   //cout << i << "   id: " << obj_arr[i].Get_id() << "       cp: " << obj_arr[i].Get_cp() << endl;
	}
		   cout << endl << endl << endl << "        ==========================HeapSorting==========================\n\n";
		   HeapSortstart = clock();// heapsort is beginning
		   HEAPSORT(obj_arr, N);
		   HeapSortfinish = clock(); //heapsort is completed

		   /*for (int i = 1; i <= N; i++)
		   {
		   cout << obj_arr[i].Get_id() << "--------------------->" << obj_arr[i].Get_cp() << endl;
		   }*/

		   for (int i = 1; i < N; i++)
			   output << obj_arr[i].Get_id() << " " << obj_arr[i].Get_cp() << endl;	// write on file

		   cout << "\n\n\t\t\t" << "HeapSort  Runingtime: " << ((double)(HeapSortfinish - HeapSortstart)) / (double)CLOCKS_PER_SEC << endl;// display runnin time

		break;

	case 2:
		/*for (int i = 1; i <= N; i++)
		{
		inputA >> p_id;		//reeading from file
		inputA >> p_cp;
		obj_arr[i].Setter(p_id, p_cp);
		//cout << i << "   id: " << obj_arr[i].Get_id() << "       cp: " << obj_arr[i].Get_cp() << endl;
		}
		for (int i = 1; i <= N; i++)
		{
		inputB >> p_id;		//reeading from file
		inputB >> p_cp;
		obj_arrB[i].Setter(p_id, p_cp);
		cout << i << "   id: " << obj_arrB[i].Get_id() << "       cp: " << obj_arrB[i].Get_cp() << endl;
		}

		BUILD_MAX_HEAP(obj_arrB, N);
		BUILD_MAX_HEAP(obj_arr, N);
		obj_arr[1].TypeSetter("Leader");
		obj_arrB[1].TypeSetter("Leader");

		for (int i = 0; i <= 8; i++){
		obj_arr[i].TypeSetter("Henchmen");
		obj_arrB[i].TypeSetter("Henchmen");

		}
		for (int i = 9; i <= N; i++){
		obj_arr[i].TypeSetter("Soldier");
		obj_arrB[i].TypeSetter("Soldier");

		}
		for (int j = 1; j <= N; j++)
		{
		cout << obj_arr[j].Get_id() << "--------->" << obj_arr[j].Get_cp() << "______" << obj_arrB[j].Get_id() << "----------->" << obj_arrB[j].Get_cp() << "--------->" << endl;
		string Atype = obj_arr[j].Get_type();
		string Btype = obj_arrB[j].Get_type();


		}


		for (int x = 1; x <= N; x++)
		{
		inputC >> log_id;		//reeading from file
		inputC >> clantype;
		inputC >> attacker_id;
		inputC >> attacked_id;
		obj_arrB[x].Setter(p_id, p_cp);
		cout << x << "   id: " << log_id << "       clantype: " << clantype << "      attacker:" << attacker_id << "     attacked:" << attacked_id << endl;

		if (clantype == 'A')
		{
		if (obj_arr[attacker_id].Get_type() == "Leader"){

		if (obj_arr[attacker_id].Get_cp > obj_arrB[attacked_id].Get_cp){
		int cp1, cp2;
		cp1 = obj_arr[attacker_id].Get_cp() + (obj_arrB[attacked_id].Get_cp / 2);
		cp2 = (obj_arrB[attacked_id].Get_cp / 2);
		obj_arr[attacker_id].Setter(attacker_id, cp1);
		obj_arrB[attacked_id].Setter(attacked_id, cp2);

		}
		else{
		int cp1, cp2;
		cp2 = obj_arr[attacked_id].Get_cp() + (obj_arrB[attacker_id].Get_cp / 2);
		cp1 = (obj_arrB[attacker_id].Get_cp() / 2);
		obj_arr[attacker_id].Setter(attacker_id, cp1);
		obj_arrB[attacked_id].Setter(attacked_id, cp2);
		}


		}

		else if (obj_arr[attacker_id].Get_type() == "Henchmen")
		{
		if (obj_arr[attacker_id].Get_cp > obj_arrB[attacked_id].Get_cp){
		int cp1, cp2;
		cp1 = obj_arr[attacker_id].Get_cp() + 500;
		cp2 = (obj_arrB[attacked_id].Get_cp() - 500);
		obj_arr[attacker_id].Setter(attacker_id, cp1);
		obj_arrB[attacked_id].Setter(attacked_id, cp2);

		}
		else{
		int cp1, cp2;
		cp2 = obj_arr[attacked_id].Get_cp() + 500;
		cp1 = (obj_arrB[attacker_id].Get_cp() - 500);
		obj_arr[attacker_id].Setter(attacker_id, cp1);
		obj_arrB[attacked_id].Setter(attacked_id, cp2);
		}

		}

		else if (obj_arr[attacker_id].Get_type() == "Soldier")
		{
		if (obj_arr[attacker_id].Get_cp > obj_arrB[attacked_id].Get_cp){
		int cp1, cp2;
		cp1 = obj_arr[attacker_id].Get_cp() + (obj_arrB[attacked_id].Get_cp / 2);
		cp2 = (obj_arrB[attacked_id].Get_cp / 2);
		obj_arr[attacker_id].Setter(attacker_id, cp1);
		obj_arrB[attacked_id].Setter(attacked_id, cp2);

		}
		else{
		int cp1, cp2;
		cp2 = obj_arr[attacked_id].Get_cp() + (obj_arrB[attacker_id].Get_cp / 2);
		cp1 = (obj_arrB[attacker_id].Get_cp / 2);
		obj_arr[attacker_id].Setter(attacker_id, cp1);
		obj_arrB[attacked_id].Setter(attacked_id, cp2);
		}
		}
		}

		if (clantype == 'B')
		{
		if (obj_arrB[attacker_id].Get_cp > obj_arr[attacked_id].Get_cp){
		int cp1, cp2;
		cp1 = obj_arrB[attacker_id].Get_cp() + (obj_arr[attacked_id].Get_cp / 2);
		cp2 = (obj_arr[attacked_id].Get_cp / 2);
		obj_arr[attacker_id].Setter(attacker_id, cp1);
		obj_arrB[attacked_id].Setter(attacked_id, cp2);

		}
		else{
		int cp1, cp2;
		cp2 = obj_arr[attacked_id].Get_cp() + (obj_arrB[attacker_id].Get_cp / 2);
		cp1 = (obj_arrB[attacker_id].Get_cp() / 2);
		obj_arr[attacker_id].Setter(attacker_id, cp1);
		obj_arrB[attacked_id].Setter(attacked_id, cp2);
		}



		}

		else if (obj_arr[attacker_id].Get_type() == "Henchmen")
		{
		if (obj_arr[attacker_id].Get_cp > obj_arrB[attacked_id].Get_cp){
		int cp1, cp2;
		cp1 = obj_arr[attacker_id].Get_cp() + (obj_arrB[attacked_id].Get_cp / 2);
		cp2 = (obj_arrB[attacked_id].Get_cp / 2);
		obj_arr[attacker_id].Setter(attacker_id, cp1);
		obj_arrB[attacked_id].Setter(attacked_id, cp2);

		}
		else{
		int cp1, cp2;
		cp2 = obj_arr[attacked_id].Get_cp() + (obj_arrB[attacker_id].Get_cp / 2);
		cp1 = (obj_arrB[attacker_id].Get_cp / 2);
		obj_arr[attacker_id].Setter(attacker_id, cp1);
		obj_arrB[attacked_id].Setter(attacked_id, cp2);
		}

		}

		else if (obj_arr[attacker_id].Get_type() == "Soldier")
		{
		if (obj_arr[attacker_id].Get_cp > obj_arrB[attacked_id].Get_cp){
		int cp1, cp2;
		cp1 = obj_arr[attacker_id].Get_cp() + (obj_arrB[attacked_id].Get_cp / 2);
		cp2 = (obj_arrB[attacked_id].Get_cp / 2);
		obj_arr[attacker_id].Setter(attacker_id, cp1);
		obj_arrB[attacked_id].Setter(attacked_id, cp2);

		}
		else{
		int cp1, cp2;
		cp2 = obj_arr[attacked_id].Get_cp() + (obj_arrB[attacker_id].Get_cp / 2);
		cp1 = (obj_arrB[attacker_id].Get_cp / 2);
		obj_arr[attacker_id].Setter(attacker_id, cp1);
		obj_arrB[attacked_id].Setter(attacked_id, cp2);
		}
		}
		}
*/       
        cout <<" I try to complete this part, yet it is not works correctly." <<endl;

		break;

	


	default: cout << "Please try again!!";
		break;
	}

	system("Pause");
	return 0;
}


