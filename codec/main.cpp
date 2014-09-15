#include "stdmdm.h"
#include "DeltaCodec.h"
#include 	"generator.h"

//#include "norma_T3.h"	 // 2001
//#include "c_ecgIII.h"	 // 2048
//#include "c_epi_C4.h"  // 2048   !!!
#include "c_spaik_O1.h"  // 578   !!!

CDeltaCodec		DeltaCodec;
CDeltaCodec*	g_pDeltaCodec = &DeltaCodec;

/*
const	UINT16	DATA_LENGTH = 12;
INT16	g_nIn[DATA_LENGTH] = {100,112,90,80,70,150,120,50,90,90,80,70};
INT16	g_nOut[DATA_LENGTH]= {0,0,0,0,0,0,0,0,0,0,0,0};
INT16	g_nStep[DATA_LENGTH];
INT16	g_nCorr[DATA_LENGTH];
UINT16	nIndxDeCodSign;
INT16	g_nDeCodSign[DATA_LENGTH];
*/

//deb
UINT16	nCntr_Correction = 0;
//deb
int  main()
{
	InitGeneratorSignals();

//	GeneratorSignalsNoise16(&g_nIn[0],1,DATA_LENGTH);


// проблема если 3 подряд !!!, 1,2 проходит

//g_nIn[100] = 500;
//g_nIn[101] = 500;
//g_nIn[102] = 500;


//g_nIn[1000] = -1000;
//g_nIn[1001] = -1000;
//g_nIn[1002] = -1000;


	for (UINT16 i=0; i<DATA_LENGTH; i++)
	{
		g_nOut[i]  = 0;
		g_nStep[i] = 0;
		g_nCorr[i] = 0;
		g_nDeCodSign[i] = 0;
	}

	g_pDeltaCodec->Create();

// !!! ForSee			
nIndxDeCodSign = 0;
// !!! ForSee			
	for (UINT16 i=0; i<DATA_LENGTH; i++)
		g_pDeltaCodec->Proc(&g_nIn[i],&g_nOut[i]);


//deb
UINT16 Percent = (nCntr_Correction * 100) / DATA_LENGTH;
//deb


    return 0;
}

