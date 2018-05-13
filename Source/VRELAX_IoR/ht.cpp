/* _    _   _   _   _                     _       _______                                 __                            
  | |  | | (_) | | | |                   | |     |__   __|                               / _|                           
  | |__| |  _  | | | |__     ___   _ __  | |_       | |     _ __    __ _   _ __    ___  | |_    ___    _ __   _ __ ___  
  |  __  | | | | | | '_ \   / _ \ | '__| | __|      | |    | '__|  / _` | | '_ \  / __| |  _|  / _ \  | '__| | '_ ` _ \ 
  | |  | | | | | | | |_) | |  __/ | |    | |_       | |    | |    | (_| | | | | | \__ \ | |   | (_) | | |    | | | | | |
  |_|  |_| |_| |_| |_.__/   \___| |_|     \__|      |_|    |_|     \__,_| |_| |_| |___/ |_|    \___/  |_|    |_| |_| |_|                                                                                                                                                                                                                                              
*/

/*
ht.c		Joe Mietus		Dec 19 2001

-------------------------------------------------------------------------------
ht: Perform Hilbert transform
Copyright (C) 2002 Joe Mietus

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation; either version 2 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
this program; if not, write to the Free Software Foundation, Inc., 59 Temple
Place - Suite 330, Boston, MA 02111-1307, USA.

You may contact the author by e-mail (joe at physionet dot org) or postal mail
(MIT Room E25-505A, Cambridge, MA 02139 USA).  For updates to this software,
please visit PhysioNet (http://www.physionet.org/).
_______________________________________________________________________________

Perform Hilbert transform and calculate instantaneous magnitude and frequency.
*/

#include "ht.h"
#include <math.h>
#include <gsl/gsl_math.h>
#include <stdlib.h>
#include <fstream>

#define SAMPLINGRATE 44100
#define LMAX 200000
#define LFILT 1024	/* impulse response filter length; must be even!!! */


void convol(double *source, double *target, double *filt, int npt, int lfilt)
{
	int i, l;
	double yt;

	for (l = 1; l <= npt - lfilt + 1; l++) {
		yt = 0.0;
		for (i = 1; i <= lfilt; i++)
			yt = yt + source[l + i - 1] * filt[lfilt + 1 - i];
		target[l] = yt;
	}

	/* shifting lfilt/1+1/2 points */
	for (i = 1; i <= npt - lfilt; i++) {
		target[i] = 0.5*(target[i] + target[i + 1]);
	}
	for (i = npt - lfilt; i >= 1; i--)
		target[i + lfilt / 2] = target[i];

	/* writing zeros */
	for (i = 1; i <= lfilt / 2; i++) {
		target[i] = 0.0;
		target[npt + 1 - i] = 0.0;
	}
}

bool ht()
{
	FILE *f = fopen("input_imf.txt", "r");
	int i, npt;
	static double x[LMAX + 1];
	static double xh[LMAX + 1], ampl[LMAX + 1], phase[LMAX + 1], omega[LMAX + 1];
	double hilb[LFILT + 1], xt, xht;

	double pi = M_PI;
	double pi2 = 2 * pi;
	int lfilt = LFILT;

	for (i = 1; i <= lfilt; i++)
		hilb[i] = 1 / ((i - lfilt / 2) - 0.5) / pi;

	for (i = 1; i <= LMAX; i++) 
	{
		fscanf(f, "%lf", &x[i]);
		if (feof(f))
		{
			break;
		}
		xh[i] = 0.0;
		ampl[i] = 0.0;
	}
	npt = i - 1;
	fclose(f);


	//if (npt < lfilt) {
	//	fprintf(stderr, "%s : insufficient data\n", argv[0]);
	//	exit(2);
	//}

	/* Hilbert transform */
	convol(x, xh, hilb, npt, lfilt);

	/* Ampl and phase */
	for (i = lfilt / 2 + 1; i <= npt - lfilt / 2; i++) {
		xt = x[i];
		xht = xh[i];
		ampl[i] = sqrt(xt*xt + xht * xht);
		phase[i] = atan2(xht, xt);

		if (phase[i] < phase[i - 1])
			omega[i] = phase[i] - phase[i - 1] + pi2;
		else
			omega[i] = phase[i] - phase[i - 1];
	}

	//FILE *out = fopen("output.txt", "w");

	//for (i = lfilt / 2 + 2; i <= npt - lfilt / 2; i++)
	//	fprintf(out, "%.6f %.6f\n",ampl[i], (omega[i] / pi2)*SAMPLINGRATE); // Kendi zaten angle ve diff yapýyor.
	//fclose(out);

	double output[44100];
	int stressed_sample_num = 0;
	int normal_sample_num = 0;

	for (i = lfilt / 2 + 2; i <= npt - lfilt / 2; i++)
	{
		output[i] = (omega[i] / pi2)*SAMPLINGRATE;
	}

	for (i = lfilt / 2 + 2; i <= npt - lfilt / 2; i++)
	{
		if (output[i] > 8 && output[i] < 12)
		{
			normal_sample_num++;
		}
		else if (output[i] > 12 && output[i] < 17)
		{
			stressed_sample_num++;
		}
	}

	if (normal_sample_num > stressed_sample_num)
	{
		return false; //normal
	}
	else
	{
		return true; //stressed
	}

}

//usage(prog)
//char * prog;
//{
//	fprintf(stderr, "Usage : %s\n\n", prog);
//	fprintf(stderr, " Reads 2 columns of input (time and x) and outputs\n");
//	fprintf(stderr, " time and Hilbert transform ampltudes and frequencies.\n");
//}