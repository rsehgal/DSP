#include <iostream>     // std::cout
#include <algorithm>    // std::copy
#include <vector>       // std::vector
#include "NewDSP.h"
#include <fstream>
#include <string>

int main()
{
	std::string filename="/home/raman/WORK/DSP/DataGoreSir/TEST/1stPulse.txt";
	std::string outFilename="/home/raman/WORK/DSP/DataGoreSir/TEST/trapezoidal.txt";
	//std::string filename="textFiles/25000Pulses.txt";
	int myIntArray[]={10,20,30,40,50,60,70};
	float myFloatArray[]={10.2,20.4,30.6,40.8,50.2,60.4,70.6};

	//Define windowSize and numOfSamples
	int windowSize=4;
	int numOfSamples=1024;
	int differenceWindowSize=10;
	//Create object of NewDSP class and specify the datatype as template arguement.
	NewDSP<float> obj(windowSize,numOfSamples,differenceWindowSize);

	std::vector<float> dataVector;
	//Filling vectors from Array
	//uncomment below block to fill dataVector from array
	
	//std::vector<float> dataVector;
	/*
  	dataVector.resize(numOfSamples);
	std::copy_n ( myFloatArray, numOfSamples, dataVector.begin() );
	*/

	//Creating Result vector
	int outSize=numOfSamples-windowSize;
	std::vector<float> resultVector;
  	//resultVector.resize(outSize+1);
    //std::cout<<" OutSize :  "<<outSize<<std::endl;
	//std::cout<<" ResultVector length : "<<resultVector.size()<<std::endl;

	//Call the required DSP algo. here we have called movingAverage
	//obj.movingAverageV(numOfSamples,resultVector,dataVector);//,fs);
	
    //Filling vector from file
	std::cout<<"Reading File"<<std::endl;
	obj.ReadFileAndFillDataVector(filename,dataVector);
	std::cout<<"Reading Over"<<std::endl;

	//Calling trapezoidal filter
	obj.MakeTrapezoidFilter(resultVector,dataVector);
	//obj.PrintVector(resultVector);
	obj.WriteDataVectorToFile(outFilename,resultVector);

    //printing Results
	//std::cout << "Resulting Vector contains : ";
  	//for (typename std::vector<float>::iterator it = resultVector.begin(); it!=resultVector.end(); ++it)
	//std::cout << ' ' << *it;
 	//std::cout << '\n';

/*
    std::cout<<"Reading File"<<std::endl;
	std::vector<float> newDataVector;
	obj.ReadFileAndFillDataVector(filename,newDataVector);
	std::cout<<"Reading Over"<<std::endl;
*/
	
}
