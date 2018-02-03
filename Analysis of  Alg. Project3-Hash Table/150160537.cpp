// ConsoleApplication3.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <cstring>
using namespace std;
	ofstream output("150160537_outout.txt");
class Line{ // I create Line class. Each line include method type and key 
	private: 
		string key;
		string method;
	public:
		
	Line(){
		key="";
		method="";
	}

	void setKey(string word){
		key=word;
	}	
	
	void setMethod(string function){  // set and get methods
	  method=function;
    }
    
    string getKey(){
    	return key;
    }
    
    string getMethod(){
    	return method;
    }
    
     int hashFunction(){ // hash function
    	long long int f=1;
    	for(int i=0;i<key.length();i++){
    	int ascii=key[i];
    	f=f*ascii; 
    	f=f%337;// I used mod operation's disturbition feature in order to avoid get larger number than long long long int
    	}
    	 int index=f; 
    	return index;
    }
    
};

class HashTable{ // I create hashTable class
	private:
			string *myHashTable;
			int totalEntries;
	public:
		int _tableSize;
		int totalCollision;
		
		
	HashTable(int tableSize){ // constructor with one parameter. Table sized is gotten from user
	     _tableSize=tableSize;
		myHashTable=new string[tableSize];
		totalCollision=0;
		totalEntries=0;
		for(int i=0;i<_tableSize;i++){
			myHashTable[i]="€";      // € is marker and it means empty and firstly hashtable full with empty
		}
		}
		void display(){  // Show last situtation of hashtable
		for(int i=0;i<_tableSize;i++){
		output << i << " " <<	myHashTable[i] << endl;  
		    
		}
	}
	void insert(string word, int index){
		int collision=0;
		int firstindex=index;
		if(totalEntries>=_tableSize){ // first controll for overflow on hashtable
			cout<<"WARNING: There are no empty space in the hash table for the word: "<<word<<endl;
			cout <<"-------------------------------------"<<endl;
		}
        else if(myHashTable[index]==word){  //  second  control for if key is already exist
        	cout<<"WARNING: The word '"<<word<<"' is already in the dictionary!"<<endl;
        	cout <<"-------------------------------------"<<endl;
        }
        else{
        
		while(myHashTable[index]!="€" && myHashTable[index]!="#"){ // if probe not indicates empty or deleted, it means collision 
				index++;											//continue liner probing
				collision++;
				totalCollision++;
				if(index>=_tableSize){ // control for if index indicates larger value than table size, return first index
					index=0;
				}
			}
			myHashTable[index]=word;
			totalEntries++;
		cout << "h(x) result is " << firstindex << " for: "<< word << endl;	
		cout<<"INSERT: The word '"<<word<<"' is put in the cell number "<<index <<endl;
		cout <<"COLLISION : "<< collision << endl;
		cout <<"-------------------------------------"<<endl;
	}
		
	}
	
	void remove(string word,int index){
		bool isnotFound=true;
		int collision=0; // retrieve function can be called for searching and after search deleted is could be done. I did not prefer so
		for(int i=index;i<_tableSize;i++){ // search for key and deleted 
			if(myHashTable[i]==word){
			myHashTable[i]="#"; // # means deleted
			isnotFound=false;
			cout<<"REMOVE: The word '"<<word<<"' is removed from the dictionary."<<endl; 
			cout <<"COLLISION : "<< collision << endl;
			cout <<"-------------------------------------"<<endl;  	
		break;   // if found break loop 
			}  
			collision++;  
			totalCollision++;
		}
		if(isnotFound){
				cout<<"WARNING: The word '"<<word<<"' couldn't be found in the dictionary"<<endl;
				cout <<"-------------------------------------"<<endl; 
			}
		
	}
		
	void retrieve(string word, int index ){ // search
		int collision=0;
		bool isnotFound=true;
		for(index;index<_tableSize;index++){
			if(myHashTable[index]==word){
			cout<<"RETRIEVE: The word '"<<word<<"' found in the dictionary with index: "<< index <<endl;
			cout <<"COLLISION : "<< collision << endl;
			cout <<"-------------------------------------"<<endl;
			isnotFound=false;
			break;     
			}   
			collision++; 
			totalCollision++;
			}
			if(isnotFound){ // give a suggestion
				cout<<"WARNING: The word '"<<word<<"' couldn't be found in the dictionary"<<endl;
				cout<< "Looking for possible suggestions."<< endl;
				string originalKey=word;
				string suggestion="";
				// I can use spell checker function and call it in this part yet, I didn't prefer
				for(int i=0;i<word.length();i++){ // for control each letter of word
					word=originalKey;            // after ith letter changed, when passed the i+1 th letter word must be orginal
					for(int j=97;j<123;j++){
					
					word[i]=j;                     // change ith letter with 97=a .......to......123=z and control 	
						for(int k=0;k<_tableSize;k++){ // if suggestion is found on hashtable give suggestion
							
							if(myHashTable[k]==word){
							suggestion+=word+", ";
							break;
						}
						
					}
					
					
				}
			}
		cout << "SUGGESTIONS for "<<  originalKey << ": " <<suggestion << endl;
        cout <<"-------------------------------------"<<endl;
		}
	}
	int getTotolCollision(){
		return totalCollision;
	}

};

void lineDivider(string arr[], Line obj[], int n){ // in order to get method type and key by seperating from ":" sign
string delimeter=":";
size_t pos=0;
string word;
for(int i=0;i<n;i++){
	word=arr[i];
	pos=word.find(delimeter);
	string key=word.substr(pos+1); // obtain method type and key distinctly
	string method=word.substr(0,pos);

	obj[i].setKey(key);
	obj[i].setMethod(method); //and each line's method type and key are set

}
}


int main(int argc, char* argv[]){
   	//argv[1] = file
    //argv[2] = n
  string file=argv[1];
   int n= atoi(argv[2]);
  HashTable hashtable(n);// object is created
  	ifstream input(file.c_str());
	string word;
	
int linenumber=0;
while(input){       // in order to get there are how many lines 
	input >> word;
	linenumber++;
}
input.close(); // close file

Line *obj=new Line[linenumber]; // create objecets for each line  

string line[linenumber];
ifstream input2(file.c_str());
linenumber =0;

while(input2){
	input2 >> line[linenumber]; // get each line for each index of line array
	linenumber++;
}

lineDivider(line,obj,linenumber);// separete method and key and assign them objects

for(int i=0;i<linenumber-1;i++){ // this loop get each line's method type and call that method

int methodType;

if (obj[i].getMethod()=="insert"){
	methodType=1;
}
else if(obj[i].getMethod()=="delete"){
	methodType=2;
} 
else if(obj[i].getMethod()=="retrieve"){
	methodType=3;
} 
switch(methodType){
	
	case 1: 	
	hashtable.insert(obj[i].getKey(),obj[i].hashFunction());
		break;
	case 2:
	hashtable.remove(obj[i].getKey(),obj[i].hashFunction());
		break;
	case 3:
	hashtable.retrieve(obj[i].getKey(),obj[i].hashFunction());
		break;
	default:cout<<"Error. Method type is not insert, delete or remove. "<<endl;
		break;
}
}

 hashtable.display(); // write on file last hashtable
 cout <<"-------------------------------------"<<endl;
 cout << "TOTAL COLLISION : "<<hashtable.getTotolCollision() <<endl<<"Final form of hash table is saved as 150160537_output.txt \n";
 cout << "n:" << n << " linenumber:" << linenumber;
	system("Pause");
	return 0;
}

