// OKAN YILDIRIM
// 150160537
//ANALYSIS OF ALGOROTIHMS I 
//PROJECT 1

#include <iostream> // 	Libraries
#include <fstream>  
#include <ctime>
#include <math.h>
#include <string>
#include <stdlib.h>
using namespace std;

class Warehouse{  						 // I create a Warehouse class
	
	private:      						// Each Warehouse is including id number, x axis , y axis and distance variables
	 int id_number;
	 int x_axis;
	 int y_axis;
	 
	public:
	float distance; 					// Distance is computed by using "euclidean_distance" method
	Warehouse(){
		id_number=0;
		x_axis=0;                        // I create a constructor without a parameter
		y_axis=0;
		distance=0;
	}
	Warehouse(int id,int x, int y){     // I create a constructor with three parameters
		id_number=id;
		x_axis=x;
		y_axis=y;
		
	}
	 void setAxis(int id,int x, int y){   // I create setter and getter methods for id, x axis, y axis and distance
	    id_number=id;
	 	x_axis=x;
		y_axis=y;
	 }	
	 void setDistance(float dist){
	 	distance=dist;
	 }
	 int get_x_axis(){
	 	return x_axis;
	 }
	 int get_y_axis(){
	 	return y_axis;
	 }
	 int get_id(){
	 	return id_number;
	 }
	 float get_distance(){
		return distance;
	}
	
  float euclidean_distance(Warehouse main_obj, Warehouse objs){ // euclidean formula for obtain distance
  int x1,x2,y1,y2;                                              // main obje is warehouse whose x and y axis values is given by 
  x1=main_obj.get_x_axis();                                     // user and  I give its id number as zeroin main method,
  x2=objs.get_x_axis();
  y1=main_obj.get_y_axis();
  y2=objs.get_y_axis();
  float dist = sqrt((((x2-x1)*(x2-x1))+((y2-y1)*(y2-y1)))); // euclidean formula
     return dist;                                            // This method return float distance value
}	 
};

void merge(Warehouse objects[],int first,int middle,int last, int n)
{
	Warehouse *tempArray= new Warehouse[n];
	int first1=first;
	int last1=middle;
	int first2=middle+1;
	int last2=last;
	int index=first1;
	for(;(first1<=last1)&&(first2<=last2);++index){
		if(objects[first1].get_distance()<objects[first2].get_distance()){
			tempArray[index]=objects[first1];
			++first1;
		}
	    else{
	    	tempArray[index]=objects[first2];
	    	++first2;
	    }
	}

for(;first1<=last1;++first1,++index)
tempArray[index]=objects[first1];
for(;first2<=last2;++first2,++index)
tempArray[index]=objects[first2];
for(index=first;index<=last;++index)
objects[index]=tempArray[index];
}

void mergesort(Warehouse objects[],int first,int last,int n){
	if(first<last){
		int middle =(first+last)/2;
		mergesort(objects,first,middle,n);
		mergesort(objects,middle+1,last,n);
		merge(objects,first,middle,last,n);
	}
}

int main(int argc, char* argv[]){
    clock_t  Insertionstart,Insertionfinish,Mergestart,Mergefinish,Linearstart,Linearfinish; // I create clock object for timer
	int id,x,y;
	int N = atoi(argv[1]); //Obtained values from user by entering on command line		*argv[1] = N							
	int K=atoi(argv[2]);   //		They are assigned													*argv[2] = K
	int* id_array=new int[N];
	int* x_array =new int[N];  // dynamic arrays are created for id, x and y axis. Actually they are not neccessaty but 
	int* y_array =new int[N];    //  I use these array for checking

	int Mymain_id=0;                // Mymain is a warehouse that entered by user using command line
	int Mymain_x=atoi(argv[4]);; 	//Obtained values from user by entering on command line         *argv[4] = x-axis              
	int Mymain_y=atoi(argv[5]);;    //																*argv[5] = y-axis
	string select_Alg=argv[3];     // for selection of the type of the algorithm on the command line																*argv[3] = algorithmType(IS, MS, LS)
	
	ifstream input ("numbers_to_sort.txt"); // for reading from warehouselocations.txt file
	ofstream output("output.txt");             // for writing on output.txt file
	
	Warehouse *objects=new Warehouse[N+1]; // I create a dynamic array that contains objects as  elements
	
	objects[0].setAxis(Mymain_id,Mymain_x,Mymain_y); // objects array first element whose index is zero, is Mymain warehouse entered by user at the same time
	objects[0].setDistance(0);      //Thus distance is for Mymain warehouse is equals 0
	
	
	int i=1;
	while(i<=N){

	input >> id_array[i]; // reading file and ids are put in id_array, x axis' are put in x_array and y axis' are put in y_array
	input >> x_array[i];
	input >> y_array[i];

	objects[i].setAxis(id_array[i], x_array[i],y_array[i]); // id,x_axis and y_axis are obtained for each objects
	objects[i].setDistance(objects[i].euclidean_distance(objects[0],objects[i]));// distance is also obtained and all they are assigned to objects
	i++;

	}
  
	if(select_Alg=="IS"){
		 cout << endl <<endl<< endl<< "     ==========================Insertion Sorting==========================\n\n";  
    	Insertionstart=clock(); // starting timer for Insertionsort
		Warehouse tmp;
  	 		for (int i = 1; i < N; i++)
   		{	
		   			for (int j=i; j>0 && objects[j].get_distance() < objects[j-1].get_distance(); j--){ // compare warehouses' distance
     					 tmp = objects[j-1];
	  					 objects[j-1]= objects[j] ; // but swap objects own order, 
        				 objects[j] = tmp;
   				}
      }         
	  Insertionfinish=clock(); // stop timer for Insertionsort
	                       // Warehouses are sorted
			for(int t=1;t<K+1;t++){  // write most K closest Warehouse on both console and output.txt file
		//	cout << objects[t].get_id() << "\t\t" << objects[t].get_x_axis() << "\t\t" << objects[t].get_y_axis()<< "\t\t" << objects[t].get_distance()<<endl;	
	        output << objects[t].get_id() << "\t\t" << objects[t].get_x_axis() << "\t\t" << objects[t].get_y_axis()<< "\t\t" << objects[t].get_distance()<<endl;

	}
    	//compute time and show
    	cout << "\n\n\t\t\t" <<"Insertionsort time: " << ((double)( Insertionfinish-Insertionstart))/(double)CLOCKS_PER_SEC<<endl;
    	
	}
	
else if(select_Alg=="MS"){
		cout << endl <<endl<< endl<< "        ==========================Merge Sorting==========================\n\n";  
   		 Mergestart=clock();  // starting timer for Mergesort
   		 mergesort(objects,1,N,N+2);
   	//	 mergesort(objects,0,N-1); // call mergesort method and sort Warehouses
   		 Mergefinish=clock();// stop timer for Insertionsort 
   		for(int t=1;t<K+1;t++){    // write most K closest Warehouse on both console and output.txt file
	   // cout << objects[t].get_id() << "\t\t" << objects[t].get_x_axis() << "\t\t" << objects[t].get_y_axis()<< "\t\t" << objects[t].get_distance()<<endl;
	    output << objects[t].get_id() << "\t\t" << objects[t].get_x_axis() << "\t\t" << objects[t].get_y_axis()<< "\t\t" << objects[t].get_distance()<<endl;
	        }
    	//compute time and show
    	 cout << "\n\n\t\t\t" <<"Mergesort time: " <<((double)( Mergefinish-Mergestart))/(double)CLOCKS_PER_SEC<<endl;
	}	
	
	else if(select_Alg=="LS"){
		cout << endl <<endl<< endl<< "        ==========================Linear Searching==========================\n\n"; 
	 Linearstart=clock();// starting timer for Linear Search
     int k2=K; // k2 is store K value since K is changing through while loop below
  		Warehouse tempobjs[K+1]; // I create temporary array
  	//	Warehouse *tempobjs=new Warehouse[K+1];
  		 for(int i=0;i<K+1;i++){
   			tempobjs[i]=objects[i]; // temporary array's first K index is the same as real object array
  	 }
  
       while(K+1<N+1){  
  	     int max=0; // max is a index of the maximum distance in the temporary array
  	        for (int t=0;t<K+1;t++){  
  	          if(tempobjs[t].get_distance()>tempobjs[max].get_distance()){ // for finding max distance of temporary array
  	        	max=t;
   	     }
	             }
	  /*if Warehouse in the real object array has smaller distance value than warehouse that has a max distance value in the temporary array,
	  put closer Warehouse in the temporary array instead of max indexed warehouse through Linear Search */
  				if(objects[K+1].get_distance()<tempobjs[max].get_distance()){ 
  					tempobjs[max]=objects[K+1];
  				}
  					K++;
			}
			Linearfinish=clock();  //stop timer for Insertionsort
					// K closest Warehouse are found but unsorted
       			for(int j=1;j<k2+1;j++){ // write most K closest Warehouse on both console and output.txt file
			     //	cout << tempobjs[j].get_id() << "\t\t" << tempobjs[j].get_x_axis() << "\t\t" << tempobjs[j].get_y_axis()<< "\t\t" << tempobjs[j].get_distance()<<endl;
					output << tempobjs[j].get_id() << "\t\t" << tempobjs[j].get_x_axis() << "\t\t" << tempobjs[j].get_y_axis()<< "\t\t" << tempobjs[j].get_distance()<<endl;
	        }
	

	 
	 //compute time and show
	 cout << "\n\n\t\t\t" <<"Linear Search time: " <<((double)( Linearfinish-Linearstart))/(double)CLOCKS_PER_SEC<<endl;
	}

	// if user enter neither algorithmType as a IS,MS or LS
	else{
		cout << "Your entry is not correct!!"; 
		output<<"Your entry is not correct!!"; 
	}
	
	return 0;
}
