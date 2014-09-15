#include 	<std.h>

#include 	"generator.h"

#define 	_TI_ENHANCED_MATH_H 1
#include 	<math.h>

// ТОЛЬКО (2^N) ВАЖНО ПРИ ПРОСМОТРЕ В 'MATLAB' ДЛЯ FFT
//int			nFsample = 2500;	//	для fir32_sp01
//int			nFsample = 256;	// для четных Md
//int			nFsample = 240;	// для нечетных Md
//int			nFsample = 200;
int			nFsample = 250;

#define		MAXCHANNELS		6
double		dFsignals[MAXCHANNELS];
int 		nAttitudes[MAXCHANNELS];
double		dScales[MAXCHANNELS];
int			nIndexs[MAXCHANNELS];

/*
#ifdef work_fir_m02v01_on
int			nIndexFiles;
#define		SIZE				8192
INT16 		nDataFromFile[SIZE] = 	{ 
										#include "zInit\1k_sine.dat"
										//#include "zInit\noise.dat"
										//#include "zInit\test.dat"
									};
#endif//work_fir_m02v01_on
*/

void InitGeneratorSignals()
{
	int i;

	// ТОЛЬКО (2^N) ВАЖНО ПРИ ПРОСМОТРЕ В 'MATLAB' ДЛЯ FFT
	dFsignals[0]	=	2;	//4;
	dFsignals[1]	=	4;	//8;
	dFsignals[2]	=	8;	//16;
	dFsignals[3]	=	12;	//32;
	dFsignals[4]	=	16;
	dFsignals[5]	=	32;

	for (i = 0; i < MAXCHANNELS; i++ )
	{
		nAttitudes[i] = nFsample / dFsignals[i];
		dScales[i] 	  = 6.2831853071795862 * dFsignals[i] / nFsample;
		nIndexs[i] = 1;
	}
}

/*
#ifdef work_fir_m02v01_on
void	InitFileSignals()
{
	nIndexFiles=0;										
}
#endif//work_fir_m02v01_on
*/

void GeneratorSignals16(int* nData, int nCh, int nFrame)
{
	int i,j;

	for ( i = 0; i < nFrame; i++ )
	{
		for ( j = 0; j < nCh; j++ )
		{
			*(nData+i*nCh+j) = sin( nIndexs[j]++ * dScales[j] ) * 32767;
			if (nIndexs[j] == nAttitudes[j] ) 
				nIndexs[j] = 0;
		}
	}
}

void GeneratorNoise16(int* nData, int nCh, int nFrame)
{
	int i,j;

	for ( i = 0; i < nFrame; i++ )
	{
		for ( j = 0; j < nCh; j++ )
			*(nData+i*nCh+j) = rand() * 32767;
	}
}

void GeneratorSignalsNoise16(int* nData, int nCh, int nFrame)
{
	int 	i,j;
	int		nDataS,nDataN;
	
	#define	N15	32766
	#define	N14	16382
	#define	N13	8190
	#define	N12	4094
	#define	N11	2046
	#define	N10	1022
	#define	N09	510
	#define	N08	254
	#define	N07	126
	#define	N06	62
	#define	N05	30
	#define	N04	14
	#define	N03	6
	#define	N02	2

	for ( i = 0; i < nFrame; i++ )
	{
		for ( j = 0; j < nCh; j++ )
		{
			//	1. Сигнал в разрядной сетке +/- NXX
			nDataS = sin( nIndexs[j]++ * dScales[j] ) * N14;
			if (nIndexs[j] == nAttitudes[j] ) 
				nIndexs[j] = 0;
			//	2. Шум +/- 1
			nDataN = ((int)round((rand()-16383)/16383.0)) * N10;
//			nDataN = 0;
			//	3. Сигнал плюс шум
			*(nData+i*nCh+j) = nDataS + nDataN;
//			*(nData+i*nCh+j) = nDataN;
		}
	}
}

/*
#ifdef work_fir_m02v01_on
void FileSignals16(int* nData, int nCh, int nFrame)
{
	int 	i,j;

	for ( i = 0; i < nFrame; i++ )
	{
		for ( j = 0; j < nCh; j++ )
		{
			*(nData+i*nCh+j) = nDataFromFile[nIndexFiles++];
		}
	}
}
#endif//work_fir_m02v01_on
*/

void GeneratorSignalsNoise32(INT32* nData, int nCh, int nFrame)
{
	int 	i,j;
	int		nDataS,nDataN;
	
	#define	N15	32766
	#define	N14	16382
	#define	N13	8190
	#define	N12	4094
	#define	N11	2046
	#define	N10	1022
	#define	N09	510
	#define	N08	254
	#define	N07	126
	#define	N06	62
	#define	N05	30
	#define	N04	14
	#define	N03	6
	#define	N02	2

	for ( i = 0; i < nFrame; i++ )
	{
		for ( j = 0; j < nCh; j++ )
		{
			//	1. Сигнал в разрядной сетке +/- NXX
			nDataS = sin( nIndexs[j]++ * dScales[j] ) * N15;
			if (nIndexs[j] == nAttitudes[j] ) 
				nIndexs[j] = 0;
			//	2. Шум +/- 1
			nDataN = ((int)round((rand()-16383)/16383.0)) * N10;
			nDataN = 0;
			//	3. Сигнал плюс шум
			*(nData+i*nCh+j) = (INT32)(nDataS + nDataN)*64; // 64=2^6
//			*(nData+i*nCh+j) = (INT32)(nDataS + nDataN)*4096; // 4096=2^12
		}
	}
}
