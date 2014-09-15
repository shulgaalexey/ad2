#ifndef __DeltaCodec_h__
#define __DeltaCodec_h__

#include "stdmdm.h"

/*
1.	Кол-во шагов усреднения : STEP_AVERAGE_MIN=3, STEP_AVERAGE_MAX=9 (оптимально для ЭЭГ сигнала)

*/

//	Минимальное, максимальное количество шагов усреднения
#define	STEP_AVERAGE_MIN	3
#define	STEP_AVERAGE_MAX	9

	// debug
//	#define	STEP_AVERAGE_MIN	3
//	#define	STEP_AVERAGE_MAX	4

//	Количество эталонных деревьев
#define	AMOUNT_TREES		(STEP_AVERAGE_MAX+1)

//	Размерности эталонных деревьев
#define	LENGTH_DELTA_BIT_3	3
#define	SIZE_TREE_3			8

#define	LENGTH_DELTA_BIT_4	4
#define	SIZE_TREE_4			16

#define	LENGTH_DELTA_BIT_5	5
#define	SIZE_TREE_5			32

#define	LENGTH_DELTA_BIT_6	6
#define	SIZE_TREE_6			64

#define	LENGTH_DELTA_BIT_7	7
#define	SIZE_TREE_7			128

#define	LENGTH_DELTA_BIT_8	8
#define	SIZE_TREE_8			256

#define	LENGTH_DELTA_BIT_9	9
#define	SIZE_TREE_9			512
	
//	Ошибка
#define	ERROR	8
//	???
#define	STEP_BOARD	3


//	Структура эталонного дерева
typedef struct{
	UINT16			LengthDeltaBit;
	UINT16			SizeTree;
	float*			pYNorm;		//	амплитуда апроксимирующей функции нормированная
	float*			pYDerNorm;	//	производная апроксимирующей функции нормированная
	UINT16*			pCode;		//	код !!!возможно в случае экономии памяти удалить
	INT16*			pDeltaBit;	//	последовательность дельта-бит
	INT16*			pE;			//	имя ?
	INT16*			pH;			//	имя ?
} StrEtalonTree;

class CDeltaCodec
{
public:
	CDeltaCodec();

	BOOL	Create();
	BOOL	DeCreate();
	void	Init();
	BOOL	Proc(INT16* nIn,INT16* nOut);
	
protected:
	void	CompositionEtalonTrees();
	
	void 	CalcCodeEH_Normal();
	void 	CalcCodeEH_AKO();

	//	Таблицы эталонных деревьев
	float 	m_YNorm_3[SIZE_TREE_3];
	float 	m_YDerNorm_3[SIZE_TREE_3];
	UINT16	m_Code_3[SIZE_TREE_3];
	INT16	m_DeltaBit_3[SIZE_TREE_3*LENGTH_DELTA_BIT_3];
	INT16	m_E_3[SIZE_TREE_3];
	INT16	m_H_3[SIZE_TREE_3];
	
	float 	m_YNorm_4[SIZE_TREE_4];
	float 	m_YDerNorm_4[SIZE_TREE_4];
	UINT16	m_Code_4[SIZE_TREE_4];
	INT16	m_DeltaBit_4[SIZE_TREE_4*LENGTH_DELTA_BIT_4];
	INT16	m_E_4[SIZE_TREE_4];
	INT16	m_H_4[SIZE_TREE_4];

	float 	m_YNorm_5[SIZE_TREE_5];
	float 	m_YDerNorm_5[SIZE_TREE_5];
	UINT16	m_Code_5[SIZE_TREE_5];
	INT16	m_DeltaBit_5[SIZE_TREE_5*LENGTH_DELTA_BIT_5];
	INT16	m_E_5[SIZE_TREE_5];
	INT16	m_H_5[SIZE_TREE_5];

	float 	m_YNorm_6[SIZE_TREE_6];
	float 	m_YDerNorm_6[SIZE_TREE_6];
	UINT16	m_Code_6[SIZE_TREE_6];
	INT16	m_DeltaBit_6[SIZE_TREE_6*LENGTH_DELTA_BIT_6];
	INT16	m_E_6[SIZE_TREE_6];
	INT16	m_H_6[SIZE_TREE_6];

	float 	m_YNorm_7[SIZE_TREE_7];
	float 	m_YDerNorm_7[SIZE_TREE_7];
	UINT16	m_Code_7[SIZE_TREE_7];
	INT16	m_DeltaBit_7[SIZE_TREE_7*LENGTH_DELTA_BIT_7];
	INT16	m_E_7[SIZE_TREE_7];
	INT16	m_H_7[SIZE_TREE_7];

	float 	m_YNorm_8[SIZE_TREE_8];
	float 	m_YDerNorm_8[SIZE_TREE_8];
	UINT16	m_Code_8[SIZE_TREE_8];
	INT16	m_DeltaBit_8[SIZE_TREE_8*LENGTH_DELTA_BIT_8];
	INT16	m_E_8[SIZE_TREE_8];
	INT16	m_H_8[SIZE_TREE_8];

	float 	m_YNorm_9[SIZE_TREE_9];
	float 	m_YDerNorm_9[SIZE_TREE_9];
	UINT16	m_Code_9[SIZE_TREE_9];
	INT16	m_DeltaBit_9[SIZE_TREE_9*LENGTH_DELTA_BIT_9];
	INT16	m_E_9[SIZE_TREE_9];
	INT16	m_H_9[SIZE_TREE_9];

	//	Структуры эталонных деревьев
	StrEtalonTree  m_EtalonTree_3;
	StrEtalonTree  m_EtalonTree_4;
	StrEtalonTree  m_EtalonTree_5;
	StrEtalonTree  m_EtalonTree_6;
	StrEtalonTree  m_EtalonTree_7;
	StrEtalonTree  m_EtalonTree_8;
	StrEtalonTree  m_EtalonTree_9;
	StrEtalonTree* m_pEtalonTree;

	
	UINT16	m_nState;		//	Состояние кодера :  	0 - на входе 1я точка
							//							1 - на входе 2я точка
							//						   >1 - на входе следующие точки
	
	INT16	m_nIn[2];		//	Два предыдущих значения входного сигнала
	
	UINT16	m_nError;		//	Ошибка
	UINT16	m_nNB;			//	Шаг усреднения/учашения
	UINT16	m_nN;			//	Кол-во шагов усреднения/учашения
	UINT16	m_nA;			//	Вес 2й производной
	INT16	m_nYDerProgn;	//	Приближённое/прогнозируемое значение 1й производной исх сигн в следующей точке

	float	m_fYNorm;		//	Амплитуда апроксимирующей функции нормированная
	float	m_fYDerNorm;	//	Производная апроксимирующей функции нормированная
	float	m_fErrorNorm;	//	Нормированная ошибка

	INT16	m_nY;			//	Амплитуда апроксимирующей функции
	INT16	m_nYDer;		//	Производная апроксимирующей функции

	INT16	m_E;
	INT16	m_H;
	INT16	m_Code;
	INT16	m_Correction;
	
	UINT16* m_pIndx;
};

#endif//__DeltaCodec_h__


//	UINT16*	m_pDeltaBit;
