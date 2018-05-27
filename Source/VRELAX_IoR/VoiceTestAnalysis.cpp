// Fill out your copyright notice in the Description page of Project Settings.

#include "VoiceTestAnalysis.h"

#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <math.h>
#include <gsl/gsl_math.h>
#include "ht.h"
#include "audio_record.h"
#include "AudioFile.h"
#include "eemd.h"
using namespace std;

//const double pi = M_PI;

const size_t ensemble_size = 250;
const unsigned int S_number = 4;
const unsigned int num_siftings = 50;
const double noise_strength = 0.2;
const unsigned long int rng_seed = 0;
const char outfile[] = "input_imf.txt";

const int N = 44100; //number of samples
					 /*
					 Normal_CHANGE1 = 45600
					 Normal_DESTIN1 = 77280
					 Normal_EAST1 = 60480
					 Normal_EIGHT = 29760
					 Normal_EIGHTY1 = 50400
					 Normal_ENTER1 = 51360
					 Normal_FIFTY1 = 39360
					 Normal_FIX1 = 73440

					 Stressed_CHANGE1 = 59017
					 Stressed_DESTIN1 = 67066
					 Stressed_EAST1 = 40925
					 Stressed_EIGHT1 = 34222
					 Stressed_EIGHTY1 = 32811
					 Stressed_ENTER1 = 31752
					 Stressed_FIFTY1 = 56333
					 Stressed_FREEZE1 = 64381
					 */

bool UVoiceTestAnalysis::StartVoiceAnalysis(FString message)
{
	int stressed = 0;
	int not_stressed = 0;
	UE_LOG(LogTemp, Log, TEXT("%s"), *message)
		UE_LOG(LogTemp, Log, TEXT("Voice Recording Starts"))
		/*                                                                   _   _
		                                                                    | | (_)
	__      __   __ _  __   __       _ __    ___    ___    ___    _ __    __| |  _   _ __     __ _
	\ \ /\ / /  / _` | \ \ / /      | '__|  / _ \  / __|  / _ \  | '__|  / _` | | | | '_ \   / _` |
	 \ V  V /  | (_| |  \ V /       | |    |  __/ | (__  | (_) | | |    | (_| | | | | | | | | (_| |
	  \_/\_/    \__,_|   \_/        |_|     \___|  \___|  \___/  |_|     \__,_| |_| |_| |_|  \__, |
	                                                                                          __/ |
		                                                                                      |___/ */
		const int size = (FREQUENCY * LENGTH);
		char *data = (char *)malloc(sizeof(char)*size);

		printf("Recording...\r");
		StartRecord(data, size);
		printf("Processing..\r");
		printf("Saving   ...\r");
		FILE *f = fopen("data.raw", "w");   // raw data name
		fwrite(data, sizeof(char), size, f);
		fclose(f);

		{ 
			// wav encoding
			const int SAMPLE_RATE = 44100;
			const int NUM_CHANNELS = 1;
			const int BITS_PER_SAMPLE = 8;
			const int BYTE_RATE = SAMPLE_RATE * NUM_CHANNELS * BITS_PER_SAMPLE / 8;

			const std::string file_path = "";
			const std::string file_name = "data"; // wav data name. It must be same with the raw data name!
			raw_to_wav(file_path, file_name, SAMPLE_RATE, BITS_PER_SAMPLE, NUM_CHANNELS, BYTE_RATE);
		}

		PlaySound(L"data.wav", NULL, SND_FILENAME); // VOICE TEST FEEDBACK

	free(data); // memory free
	UE_LOG(LogTemp, Log, TEXT("Voice Recording Ends"))
		/*                                                       _
		| |
		__      __   __ _  __   __        _ __    ___    __ _    __| |   ___   _ __
		\ \ /\ / /  / _` | \ \ / /       | '__|  / _ \  / _` |  / _` |  / _ \ | '__|
		 \ V  V /  | (_| |  \ V /        | |    |  __/ | (_| | | (_| | |  __/ | |
		  \_/\_/    \__,_|   \_/         |_|     \___|  \__,_|  \__,_|  \___| |_|

		*/

		UE_LOG(LogTemp, Log, TEXT("Voice Reader Starts"))

		AudioFile<double> audioFile;

		//load .wav file
		audioFile.load("data.wav");

		//determine the channels
		int channel;
		if (audioFile.isMono())
		channel = 0;
		else
		channel = 1;

		//determine the number of samples
		int numOfSamples = audioFile.getNumSamplesPerChannel();

		//open text file to write to
		ofstream oFile;
		oFile.open("input.txt");

		//save samples to the text file
		for (int i = 0; i < numOfSamples; i++)
		{
		oFile << audioFile.samples[channel][i] << endl;
		}

		UE_LOG(LogTemp, Log, TEXT("Voice Reader Ends"))
		

		/*
		______   ______   __  __   _____
		|  ____| |  ____| |  \/  | |  __ \
		| |__    | |__    | \  / | | |  | |
		|  __|   |  __|   | |\/| | | |  | |
		| |____  | |____  | |  | | | |__| |
		|______| |______| |_|  |_| |_____/
		*/
		
		UE_LOG(LogTemp, Log, TEXT("EEMD Starts"))
		libeemd_error_code err;
		//Define input data
		double* inp = (double*)malloc(N * sizeof(double));

			//gets input signal
		FILE* fp2 = fopen("input.txt", "r");
		if (fp2)
		printf("File is read\n");
		else
		printf("File could not be read\n");


			//stores input signal
		for (int j = 0; j < N; j++)
		{
			fscanf(fp2, "%lf\n", &inp[j]);
		}
		fclose(fp2);


			//Allocate memory for output data
		const int M = emd_num_imfs(N);
		double* outp = (double*)malloc(M * N * sizeof(double));


		 //Run eemd
		err = eemd(inp, N, outp, M, ensemble_size, noise_strength, S_number, num_siftings, rng_seed);
		if (err != EMD_SUCCESS)
		{
			emd_report_if_error(err);
			exit(1);
		}
		printf("eemd is done!\n");


		 //Write output to file
		FILE* fp = fopen(outfile, "w");
		 int this_imf = M-3;

		for (int i = M - 4; i <= M - 4; i++) //IMF number
		for (int j = 0; j < N; j++)
		{
		fprintf(fp, "%lf\n", outp[i * N + j]);
		}

		 //Cleanup
		fclose(fp);
		free(inp);
		inp = nullptr;
		free(outp);
		outp = nullptr;
		
		UE_LOG(LogTemp, Log, TEXT("EEMD Ends"))

		UE_LOG(LogTemp, Log, TEXT("HT Starts"))
		if (ht(&stressed , &not_stressed))
		{
			UE_LOG(LogTemp, Log, TEXT("\nYou are stressed!\n"))
			UE_LOG(LogTemp, Log, TEXT("\nStressed Sample: %d \n"), stressed)
			UE_LOG(LogTemp, Log, TEXT("\nUnstressed Sample: %d \n"), not_stressed)
			return true;
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("\nYou are not stressed!"))
			UE_LOG(LogTemp, Log, TEXT("\nStressed Sample: %d \n"), stressed)
			UE_LOG(LogTemp, Log, TEXT("\nUnstressed Sample: %d \n"), not_stressed)
			return false;
		}

}


