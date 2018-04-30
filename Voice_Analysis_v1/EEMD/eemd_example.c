/* Copyright 2013 Perttu Luukko

 * This file is part of libeemd.

 * libeemd is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * libeemd is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with libeemd.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_math.h>
const double pi = M_PI;

#include "eemd.h"

const size_t ensemble_size = 250;
const unsigned int S_number = 4;
const unsigned int num_siftings = 50;
const double noise_strength = 0.2;
const unsigned long int rng_seed = 0;


const char *outfile_n5[16];
const char *outfile_n4[16];
const char *outfile_n3[16];


//sample numbers
const int Normal_CHANGE1 = 45600; //number of samples
const int Normal_DESTIN1 = 77280; //number of samples
const int Normal_EAST1 = 60480; //number of samples
const int Normal_EIGHT = 29760; //number of samples
const int Normal_EIGHTY1 = 50400; //number of samples
const int Normal_ENTER1 = 51360; //number of samples
const int Normal_FIFTY1 = 39360; //number of samples
const int Normal_FIX1 = 73440; //number of samples

const int Stressed_CHANGE1 = 59017; //number of samples
const int Stressed_DESTIN1 = 67066; //number of samples
const int Stressed_EAST1 = 40925; //number of samples
const int Stressed_EIGHT1 = 34222; //number of samples
const int Stressed_EIGHTY1 = 32811; //number of samples
const int Stressed_ENTER1 = 31752; //number of samples
const int Stressed_FIFTY1 = 56333; //number of samples
const int Stressed_FREEZE1 = 64381; //number of samples

const int N[] = {45600,77280,60480,29760,50400,51360,39360,73440,59017,
67066,40925,34222,32811,31752,56333,64381};

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

//input file locations
const char normal_change_location[] = "/home/hopetolive/Desktop/Voice_Analysis_Final/Read_Wav/NormalMaleText/Normal_CHANGE1.txt";
const char normal_destin_location[] = "/home/hopetolive/Desktop/Voice_Analysis_Final/Read_Wav/NormalMaleText/Normal_DESTIN1.txt";
const char normal_east_location[] = "/home/hopetolive/Desktop/Voice_Analysis_Final/Read_Wav/NormalMaleText/Normal_EAST1.txt";
const char normal_eight_location[] = "/home/hopetolive/Desktop/Voice_Analysis_Final/Read_Wav/NormalMaleText/Normal_EIGHT1.txt";
const char normal_eighty_location[] = "/home/hopetolive/Desktop/Voice_Analysis_Final/Read_Wav/NormalMaleText/Normal_EIGHTY1.txt";
const char normal_enter_location[] = "/home/hopetolive/Desktop/Voice_Analysis_Final/Read_Wav/NormalMaleText/Normal_ENTER1.txt";
const char normal_fifty_location[] = "/home/hopetolive/Desktop/Voice_Analysis_Final/Read_Wav/NormalMaleText/Normal_FIFTY1.txt";
const char normal_fix_location[] = "/home/hopetolive/Desktop/Voice_Analysis_Final/Read_Wav/NormalMaleText/Normal_FIX1.txt";

const char stressed_change_location[] = "/home/hopetolive/Desktop/Voice_Analysis_Final/Read_Wav/StressedMaleText/Stressed_CHANGE1.txt";
const char stressed_destin_location[] = "/home/hopetolive/Desktop/Voice_Analysis_Final/Read_Wav/StressedMaleText/Stressed_DESTIN1.txt";
const char stressed_east_location[] = "/home/hopetolive/Desktop/Voice_Analysis_Final/Read_Wav/StressedMaleText/Stressed_EAST1.txt";
const char stressed_eight_location[] = "/home/hopetolive/Desktop/Voice_Analysis_Final/Read_Wav/StressedMaleText/Stressed_EIGHT1.txt";
const char stressed_eighty_location[] = "/home/hopetolive/Desktop/Voice_Analysis_Final/Read_Wav/StressedMaleText/Stressed_EIGHTY1.txt";
const char stressed_enter_location[] = "/home/hopetolive/Desktop/Voice_Analysis_Final/Read_Wav/StressedMaleText/Stressed_ENTER1.txt";
const char stressed_fifty_location[] = "/home/hopetolive/Desktop/Voice_Analysis_Final/Read_Wav/StressedMaleText/Stressed_FIFTY1.txt";
const char stressed_freeze_location[] = "/home/hopetolive/Desktop/Voice_Analysis_Final/Read_Wav/StressedMaleText/Stressed_FREEZE1.txt";


const char *inputs[16];

int main(void) {
	libeemd_error_code err;
//N-5 IMF
outfile_n5[8] = "/home/hopetolive/Desktop/Voice_Analysis_Final/EEMD/Stressed_EEMD/eemd_Stressed_CHANGE1_N-5.txt";
outfile_n5[9] = "/home/hopetolive/Desktop/Voice_Analysis_Final/EEMD/Stressed_EEMD/eemd_Stressed_DESTIN1_N-5.txt";
outfile_n5[10] = "/home/hopetolive/Desktop/Voice_Analysis_Final/EEMD/Stressed_EEMD/eemd_Stressed_EAST1_N-5.txt";
outfile_n5[11] = "/home/hopetolive/Desktop/Voice_Analysis_Final/EEMD/Stressed_EEMD/eemd_Stressed_EIGHT1_N-5.txt";
outfile_n5[12] = "/home/hopetolive/Desktop/Voice_Analysis_Final/EEMD/Stressed_EEMD/eemd_Stressed_EIGHTY1_N-5.txt";
outfile_n5[13] = "/home/hopetolive/Desktop/Voice_Analysis_Final/EEMD/Stressed_EEMD/eemd_Stressed_ENTER1_N-5.txt";
outfile_n5[14] = "/home/hopetolive/Desktop/Voice_Analysis_Final/EEMD/Stressed_EEMD/eemd_Stressed_FIFTY1_N-5.txt";
outfile_n5[15] = "/home/hopetolive/Desktop/Voice_Analysis_Final/EEMD/Stressed_EEMD/eemd_Stressed_FREEZE1_N-5.txt";

outfile_n5[0] = "/home/hopetolive/Desktop/Voice_Analysis_Final/EEMD/Normal_EEMD/eemd_Normal_CHANGE1_N-5.txt";
outfile_n5[1] = "/home/hopetolive/Desktop/Voice_Analysis_Final/EEMD/Normal_EEMD/eemd_Normal_DESTIN1_N-5.txt";
outfile_n5[2] = "/home/hopetolive/Desktop/Voice_Analysis_Final/EEMD/Normal_EEMD/eemd_Normal_EAST1_N-5.txt";
outfile_n5[3] = "/home/hopetolive/Desktop/Voice_Analysis_Final/EEMD/Normal_EEMD/eemd_Normal_EIGHT1_N-5.txt";
outfile_n5[4] = "/home/hopetolive/Desktop/Voice_Analysis_Final/EEMD/Normal_EEMD/eemd_Normal_EIGHTY1_N-5.txt";
outfile_n5[5] = "/home/hopetolive/Desktop/Voice_Analysis_Final/EEMD/Normal_EEMD/eemd_Normal_ENTER1_N-5.txt";
outfile_n5[6] = "/home/hopetolive/Desktop/Voice_Analysis_Final/EEMD/Normal_EEMD/eemd_Normal_FIFTY1_N-5.txt";
outfile_n5[7] = "/home/hopetolive/Desktop/Voice_Analysis_Final/EEMD/Normal_EEMD/eemd_Normal_FIX1_N-5.txt";

//N-4 IMF
outfile_n4[8] = "/home/hopetolive/Desktop/Voice_Analysis_Final/EEMD/Stressed_EEMD/eemd_Stressed_CHANGE1_N-4.txt";
outfile_n4[9] = "/home/hopetolive/Desktop/Voice_Analysis_Final/EEMD/Stressed_EEMD/eemd_Stressed_DESTIN1_N-4.txt";
outfile_n4[10] = "/home/hopetolive/Desktop/Voice_Analysis_Final/EEMD/Stressed_EEMD/eemd_Stressed_EAST1_N-4.txt";
outfile_n4[11] = "/home/hopetolive/Desktop/Voice_Analysis_Final/EEMD/Stressed_EEMD/eemd_Stressed_EIGHT1_N-4.txt";
outfile_n4[12] = "/home/hopetolive/Desktop/Voice_Analysis_Final/EEMD/Stressed_EEMD/eemd_Stressed_EIGHTY1_N-4.txt";
outfile_n4[13] = "/home/hopetolive/Desktop/Voice_Analysis_Final/EEMD/Stressed_EEMD/eemd_Stressed_ENTER1_N-4.txt";
outfile_n4[14] = "/home/hopetolive/Desktop/Voice_Analysis_Final/EEMD/Stressed_EEMD/eemd_Stressed_FIFTY1_N-4.txt";
outfile_n4[15] = "/home/hopetolive/Desktop/Voice_Analysis_Final/EEMD/Stressed_EEMD/eemd_Stressed_FREEZE1_N-4.txt";

outfile_n4[0] = "/home/hopetolive/Desktop/Voice_Analysis_Final/EEMD/Normal_EEMD/eemd_Normal_CHANGE1_N-4.txt";
outfile_n4[1] = "/home/hopetolive/Desktop/Voice_Analysis_Final/EEMD/Normal_EEMD/eemd_Normal_DESTIN1_N-4.txt";
outfile_n4[2] = "/home/hopetolive/Desktop/Voice_Analysis_Final/EEMD/Normal_EEMD/eemd_Normal_EAST1_N-4.txt";
outfile_n4[3] = "/home/hopetolive/Desktop/Voice_Analysis_Final/EEMD/Normal_EEMD/eemd_Normal_EIGHT1_N-4.txt";
outfile_n4[4] = "/home/hopetolive/Desktop/Voice_Analysis_Final/EEMD/Normal_EEMD/eemd_Normal_EIGHTY1_N-4.txt";
outfile_n4[5] = "/home/hopetolive/Desktop/Voice_Analysis_Final/EEMD/Normal_EEMD/eemd_Normal_ENTER1_N-4.txt";
outfile_n4[6] = "/home/hopetolive/Desktop/Voice_Analysis_Final/EEMD/Normal_EEMD/eemd_Normal_FIFTY1_N-4.txt";
outfile_n4[7] = "/home/hopetolive/Desktop/Voice_Analysis_Final/EEMD/Normal_EEMD/eemd_Normal_FIX1_N-4.txt";

//N-3 IMF
outfile_n3[8] = "/home/hopetolive/Desktop/Voice_Analysis_Final/EEMD/Stressed_EEMD/eemd_Stressed_CHANGE1_N-3.txt";
outfile_n3[9] = "/home/hopetolive/Desktop/Voice_Analysis_Final/EEMD/Stressed_EEMD/eemd_Stressed_DESTIN1_N-3.txt";
outfile_n3[10] = "/home/hopetolive/Desktop/Voice_Analysis_Final/EEMD/Stressed_EEMD/eemd_Stressed_EAST1_N-3.txt";
outfile_n3[11] = "/home/hopetolive/Desktop/Voice_Analysis_Final/EEMD/Stressed_EEMD/eemd_Stressed_EIGHT1_N-3.txt";
outfile_n3[12] = "/home/hopetolive/Desktop/Voice_Analysis_Final/EEMD/Stressed_EEMD/eemd_Stressed_EIGHTY1_N-3.txt";
outfile_n3[13] = "/home/hopetolive/Desktop/Voice_Analysis_Final/EEMD/Stressed_EEMD/eemd_Stressed_ENTER1_N-3.txt";
outfile_n3[14] = "/home/hopetolive/Desktop/Voice_Analysis_Final/EEMD/Stressed_EEMD/eemd_Stressed_FIFTY1_N-3.txt";
outfile_n3[15] = "/home/hopetolive/Desktop/Voice_Analysis_Final/EEMD/Stressed_EEMD/eemd_Stressed_FREEZE1_N-3.txt";

outfile_n3[0] = "/home/hopetolive/Desktop/Voice_Analysis_Final/EEMD/Normal_EEMD/eemd_Normal_CHANGE1_N-3.txt";
outfile_n3[1] = "/home/hopetolive/Desktop/Voice_Analysis_Final/EEMD/Normal_EEMD/eemd_Normal_DESTIN1_N-3.txt";
outfile_n3[2] = "/home/hopetolive/Desktop/Voice_Analysis_Final/EEMD/Normal_EEMD/eemd_Normal_EAST1_N-3.txt";
outfile_n3[3] = "/home/hopetolive/Desktop/Voice_Analysis_Final/EEMD/Normal_EEMD/eemd_Normal_EIGHT1_N-3.txt";
outfile_n3[4] = "/home/hopetolive/Desktop/Voice_Analysis_Final/EEMD/Normal_EEMD/eemd_Normal_EIGHTY1_N-3.txt";
outfile_n3[5] = "/home/hopetolive/Desktop/Voice_Analysis_Final/EEMD/Normal_EEMD/eemd_Normal_ENTER1_N-3.txt";
outfile_n3[6] = "/home/hopetolive/Desktop/Voice_Analysis_Final/EEMD/Normal_EEMD/eemd_Normal_FIFTY1_N-3.txt";
outfile_n3[7] = "/home/hopetolive/Desktop/Voice_Analysis_Final/EEMD/Normal_EEMD/eemd_Normal_FIX1_N-3.txt";

inputs[0] = "/home/hopetolive/Desktop/Voice_Analysis_Final/Read_Wav/NormalMaleText/Normal_CHANGE1.txt";
inputs[1] = "/home/hopetolive/Desktop/Voice_Analysis_Final/Read_Wav/NormalMaleText/Normal_DESTIN1.txt";
inputs[2] = "/home/hopetolive/Desktop/Voice_Analysis_Final/Read_Wav/NormalMaleText/Normal_EAST1.txt";
inputs[3] = "/home/hopetolive/Desktop/Voice_Analysis_Final/Read_Wav/NormalMaleText/Normal_EIGHT.txt";
inputs[4] = "/home/hopetolive/Desktop/Voice_Analysis_Final/Read_Wav/NormalMaleText/Normal_EIGHTY1.txt";
inputs[5] = "/home/hopetolive/Desktop/Voice_Analysis_Final/Read_Wav/NormalMaleText/Normal_ENTER1.txt";
inputs[6] = "/home/hopetolive/Desktop/Voice_Analysis_Final/Read_Wav/NormalMaleText/Normal_FIFTY1.txt";
inputs[7] = "/home/hopetolive/Desktop/Voice_Analysis_Final/Read_Wav/NormalMaleText/Normal_FIX1.txt";

inputs[8] = "/home/hopetolive/Desktop/Voice_Analysis_Final/Read_Wav/StressedMaleText/Stressed_CHANGE1.txt";
inputs[9] = "/home/hopetolive/Desktop/Voice_Analysis_Final/Read_Wav/StressedMaleText/Stressed_DESTIN1.txt";
inputs[10] = "/home/hopetolive/Desktop/Voice_Analysis_Final/Read_Wav/StressedMaleText/Stressed_EAST1.txt";
inputs[11] = "/home/hopetolive/Desktop/Voice_Analysis_Final/Read_Wav/StressedMaleText/Stressed_EIGHT1.txt";
inputs[12] = "/home/hopetolive/Desktop/Voice_Analysis_Final/Read_Wav/StressedMaleText/Stressed_EIGHTY1.txt";
inputs[13] = "/home/hopetolive/Desktop/Voice_Analysis_Final/Read_Wav/StressedMaleText/Stressed_ENTER1.txt";
inputs[14] = "/home/hopetolive/Desktop/Voice_Analysis_Final/Read_Wav/StressedMaleText/Stressed_FIFTY1.txt";
inputs[15] = "/home/hopetolive/Desktop/Voice_Analysis_Final/Read_Wav/StressedMaleText/Stressed_FREEZE1.txt";


	int counter = 0;
	while(counter <= 15)
	{
		// Define input data
		double* inp = malloc((N[counter])*sizeof(double));
	
		//gets input signal
		FILE* fp2 = fopen(inputs[counter], "r");
		if(fp2)
			printf("File is read\n");
		else
			printf("File could not be read\n");


		//stores input signal
		for (int j=0; j<N[counter]; j++) {
			fscanf (fp2, "%lf\n", &inp[j]);
		}
		fclose(fp2);


		// Allocate memory for output data
		const int M = emd_num_imfs(N[counter]);
		double* outp = malloc(M*(N[counter])*sizeof(double));


		// Run eemd
		err = eemd(inp, N[counter], outp, M, ensemble_size, noise_strength, S_number, num_siftings, rng_seed);
		if (err != EMD_SUCCESS) {
			emd_report_if_error(err);
			exit(1);
		}
		printf("eemd %d is done!\n", counter);


		// Write output to file
		FILE* fp5 = fopen(outfile_n5[counter], "w");
		FILE* fp4 = fopen(outfile_n4[counter], "w");
		FILE* fp3 = fopen(outfile_n3[counter], "w");

		for (int j=0; j<N[counter]; j++)
		{
			fprintf (fp5, "%lf\n", outp[((M-5)*(N[counter]))+j]);
			fprintf (fp4, "%lf\n", outp[((M-4)*(N[counter]))+j]);
			fprintf (fp3, "%lf\n", outp[((M-3)*(N[counter]))+j]);
		}



		// Cleanup
		fclose(fp5);
		fclose(fp4);
		fclose(fp3);
		free(inp); inp = NULL;
		free(outp); outp = NULL;
		counter++;
	}
	return 0;
}
