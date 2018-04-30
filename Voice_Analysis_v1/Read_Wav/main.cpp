#include "AudioFile.h"
#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	AudioFile<double> audioFile;
	AudioFile<double> audioFile2;

	//load .wav files
	audioFile.load("/home/hopetolive/Desktop/Voice_Analysis_Final/Read_Wav/NormalMale/FIX1.wav");
	audioFile2.load("/home/hopetolive/Desktop/Voice_Analysis_Final/Read_Wav/StressedMale/FREEZE1.wav");

	//determine the channels
	int channel, channel2;
	if(audioFile.isMono())
		channel = 0;
	else
		channel = 1;

	if(audioFile2.isMono())
		channel2 = 0;
	else
		channel2 = 1;
	
	//determine the number of samples
	int numOfSamples = audioFile.getNumSamplesPerChannel();
	int numOfSamples2 = audioFile2.getNumSamplesPerChannel();

	//open text file to write to
	ofstream oFile;
	ofstream oFile2;
	oFile.open("/home/hopetolive/Desktop/Voice_Analysis_Final/Read_Wav/NormalMaleText/Normal_FIX1.txt");
	oFile2.open("/home/hopetolive/Desktop/Voice_Analysis_Final/Read_Wav/StressedMaleText/Stressed_FREEZE1.txt");

	//save samples to the text file
	for(int i = 0; i < numOfSamples; i++)
	{
		oFile << audioFile.samples[channel][i] << endl;
	}

	for(int i = 0; i < numOfSamples2; i++)
	{
		oFile2 << audioFile2.samples[channel2][i] << endl;
	}

	return 0;
}
