// copy_n algorithm example
#include <iostream>     // std::cout
#include <algorithm>    // std::copy
#include <vector>       // std::vector
#include <functional>
#include <fstream>
#include <string>
#include <iterator>
#include "MemoryMapped.h"
#define MMAP_SIZE 2147483648  // 2GB Map Size //1073741824

int steps=0;

template <class T>
class NewDSP{

public:
	int windowSize;
	int numOfSamples;
	int differenceWindowSize;
	//T averageValue;
	//std::fstream fs;

public:
	NewDSP(){
		//averageValue=0.0;
		windowSize=0;
		numOfSamples=0;
		differenceWindowSize=0.0;
		//fs.open("filtered.txt",std::fstream::out);
		}

    NewDSP(int windowSize_,int numOfSamples_,int differenceWindowSize_):windowSize(windowSize_),numOfSamples(numOfSamples_),differenceWindowSize(differenceWindowSize_){}
	void movingAverageV(int newNumOfSamples,std::vector<T> &,std::vector<T>);
	void ReadFileAndFillDataVector(std::string, std::vector<T> &);
	void MakeTrapezoidFilter(std::vector<T> &, std::vector<T>);
	//void read_bytes (void * buffer, unsigned long int num_bytes);
	void PrintVector(std::vector<T>);
	void WriteDataVectorToFile(std::string, std::vector<T> );
    
};

template <class T>
void NewDSP<T>::WriteDataVectorToFile(std::string filename, std::vector<T> dataVector){
	std::ofstream outfile(filename);
	for (typename std::vector<T>::iterator it = dataVector.begin(); it!=dataVector.end(); ++it)
	    outfile << (*it * 1.26) <<std::endl;	
	outfile.close();
}


template <class T>
void NewDSP<T>::MakeTrapezoidFilter(std::vector<T> &resultVector, std::vector<T> dataVector){
	typename std::vector<T>::const_iterator first;//=dataVector.begin();
	typename std::vector<T>::const_iterator last;
 	first = dataVector.begin();
	last = dataVector.end()- differenceWindowSize;
	std::vector<T> firstVector(first, last);

	first = dataVector.begin() + differenceWindowSize;
	last = dataVector.end();
	std::vector<T> secondVector(first, last);

	int newNumOfSamples = numOfSamples -differenceWindowSize;
	int outSize=newNumOfSamples-windowSize;
	std::vector<T> firstResultVector;
	std::vector<T> secondResultVector;

	movingAverageV(newNumOfSamples,firstResultVector,firstVector);
	//PrintVector(firstResultVector);
	movingAverageV(newNumOfSamples,secondResultVector,secondVector);
	//PrintVector(secondResultVector);
	//Doing subtraction of vectors
	std::transform(secondResultVector.begin(), secondResultVector.end(), firstResultVector.begin(), std::back_inserter(resultVector),	std::minus<T>());
}

template <class T>
void NewDSP<T>::ReadFileAndFillDataVector(std::string filename,std::vector<T> &dataVector){
	
	clock_t c1 = clock();
	
	std::ifstream infile(filename);
    
	T dataValue=0.0;
	
	while(!infile.eof())
	{
		infile >> dataValue;
		dataVector.push_back(dataValue);
	}
	
	
	/*
	std::istream_iterator<T> start(infile), end;
	std::vector<T> numbers(start, end);
	std::cout << "Read " << numbers.size() << " numbers" << std::endl;
	*/
	/*
	std::vector<T> coords(114012160); 
	typename std::vector<T>::iterator it = coords.begin();
	while (infile >> *(it++)) {}
	*/

	/*
	MemoryMapped data(filename, MemoryMapped::WholeFile, MemoryMapped::SequentialScan);
	std::cout<<"File Size : "<<data.size()<<std::endl;
	std::cout << "took " << (clock() - c1)/(double)CLOCKS_PER_SEC << " seconds." << std::endl;
	*/
}

template <class T>
void NewDSP<T>::movingAverageV(int newNumOfSamples,std::vector<T> &resultVector,std::vector<T> dataVector){

	int outSize=newNumOfSamples-windowSize;

	typename std::vector<T>::const_iterator first;//=dataVector.begin();
	typename std::vector<T>::const_iterator last;
  
	T averageValue=0.0;

    
    for(int i=0;i<=(outSize);i++)
  	{
		//Need to copy windowSize vector to a new vector called myvector;
   		first=dataVector.begin() + i;
		last = first + windowSize;
		std::vector<T> myvector(first, last);

	 	//For Debugging
		/*
 	 	std::cout << "myvector contains:";
  	 	for (typename std::vector<T>::iterator it = myvector.begin(); it!=myvector.end(); ++it)
	    std::cout << ' ' << *it;
 		std::cout << '\n';
 		*/
		//Implementing ACCUMULATE function
		
	 	T sum=0;
	 	for (typename std::vector<T>::iterator it = myvector.begin(); it!=myvector.end(); ++it)
		{
			sum += *it;
		}
	 	//T sum = std::accumulate(myvector.begin(), myvector.end(), 0,myadd);
  	 	//std::cout<<"Average :  "<<sum/myvector.size() <<std::endl;
		averageValue=sum/myvector.size();
		resultVector.push_back(averageValue);
		
	}
}

template <class T>
void NewDSP<T>::PrintVector(std::vector<T> dataVector){
		std::cout<<"-----------------------------"<<std::endl;
 	 	std::cout << "Vector contains : ";
  	 	for (typename std::vector<T>::iterator it = dataVector.begin(); it!=dataVector.end(); ++it)
	    std::cout << ' ' << *it;
 		std::cout << '\n';
 		
}
