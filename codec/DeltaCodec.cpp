#include "DeltaCodec.h"

#define _TI_ENHANCED_MATH_H 1
#include <cmath>	

/*
вопросы для решения после отладки :
!!!(1)
...
*/

UINT16	MaxAmountIndx = 100; // !!!(1) Уточнить сколько может быть одинаковых в дереве максимального размера


//deb
extern	UINT16	nCntr_Correction;
//deb


// !!! ForSee
UINT16	StateSee;			
extern	UINT16	nIndxDeCodSign;
extern	INT16	g_nDeCodSign[];
extern	INT16	g_nStep[];
extern	INT16	g_nCorr[];
// !!! ForSee


////////////////////////////////////////////////////////////////////////////
//class CDeltaCodec

CDeltaCodec::CDeltaCodec()
{
	m_nError = ERROR;
	m_nNB 	 = STEP_BOARD;
}

BOOL	CDeltaCodec::Create()
{
	m_pEtalonTree = (StrEtalonTree*)MEM_valloc(0, AMOUNT_TREES*sizeof(StrEtalonTree), 0, 0);
	if ( m_pEtalonTree == MEM_ILLEGAL )
	{
	    ASSERT(FALSE);	return FALSE;
	}

	//	Подготовка и наполнение структур для эталонных деревьев
	m_EtalonTree_3.LengthDeltaBit= LENGTH_DELTA_BIT_3;
	m_EtalonTree_3.SizeTree 	 = SIZE_TREE_3;
	m_EtalonTree_3.pYNorm		 = &m_YNorm_3[0];
	m_EtalonTree_3.pYDerNorm	 = &m_YDerNorm_3[0];
	m_EtalonTree_3.pCode		 = &m_Code_3[0];
	m_EtalonTree_3.pDeltaBit	 = &m_DeltaBit_3[0];
	m_EtalonTree_3.pE			 = &m_E_3[0];
	m_EtalonTree_3.pH			 = &m_H_3[0];
	*(m_pEtalonTree+3) = m_EtalonTree_3;

	m_EtalonTree_4.LengthDeltaBit= LENGTH_DELTA_BIT_4;
	m_EtalonTree_4.SizeTree 	 = SIZE_TREE_4;
	m_EtalonTree_4.pYNorm		 = &m_YNorm_4[0];
	m_EtalonTree_4.pYDerNorm	 = &m_YDerNorm_4[0];
	m_EtalonTree_4.pCode		 = &m_Code_4[0];
	m_EtalonTree_4.pDeltaBit	 = &m_DeltaBit_4[0];
	m_EtalonTree_4.pE			 = &m_E_4[0];
	m_EtalonTree_4.pH			 = &m_H_4[0];
	*(m_pEtalonTree+4) = m_EtalonTree_4;

	m_EtalonTree_5.LengthDeltaBit= LENGTH_DELTA_BIT_5;
	m_EtalonTree_5.SizeTree 	 = SIZE_TREE_5;
	m_EtalonTree_5.pYNorm		 = &m_YNorm_5[0];
	m_EtalonTree_5.pYDerNorm	 = &m_YDerNorm_5[0];
	m_EtalonTree_5.pCode		 = &m_Code_5[0];
	m_EtalonTree_5.pDeltaBit	 = &m_DeltaBit_5[0];
	m_EtalonTree_5.pE			 = &m_E_5[0];
	m_EtalonTree_5.pH			 = &m_H_5[0];
	*(m_pEtalonTree+5) = m_EtalonTree_5;

	m_EtalonTree_6.LengthDeltaBit= LENGTH_DELTA_BIT_6;
	m_EtalonTree_6.SizeTree 	 = SIZE_TREE_6;
	m_EtalonTree_6.pYNorm		 = &m_YNorm_6[0];
	m_EtalonTree_6.pYDerNorm	 = &m_YDerNorm_6[0];
	m_EtalonTree_6.pCode		 = &m_Code_6[0];
	m_EtalonTree_6.pDeltaBit	 = &m_DeltaBit_6[0];
	m_EtalonTree_6.pE			 = &m_E_6[0];
	m_EtalonTree_6.pH			 = &m_H_6[0];
	*(m_pEtalonTree+6) = m_EtalonTree_6;

	m_EtalonTree_7.LengthDeltaBit= LENGTH_DELTA_BIT_7;
	m_EtalonTree_7.SizeTree 	 = SIZE_TREE_7;
	m_EtalonTree_7.pYNorm		 = &m_YNorm_7[0];
	m_EtalonTree_7.pYDerNorm	 = &m_YDerNorm_7[0];
	m_EtalonTree_7.pCode		 = &m_Code_7[0];
	m_EtalonTree_7.pDeltaBit	 = &m_DeltaBit_7[0];
	m_EtalonTree_7.pE			 = &m_E_7[0];
	m_EtalonTree_7.pH			 = &m_H_7[0];
	*(m_pEtalonTree+7) = m_EtalonTree_7;

	m_EtalonTree_8.LengthDeltaBit= LENGTH_DELTA_BIT_8;
	m_EtalonTree_8.SizeTree 	 = SIZE_TREE_8;
	m_EtalonTree_8.pYNorm		 = &m_YNorm_8[0];
	m_EtalonTree_8.pYDerNorm	 = &m_YDerNorm_8[0];
	m_EtalonTree_8.pCode		 = &m_Code_8[0];
	m_EtalonTree_8.pDeltaBit	 = &m_DeltaBit_8[0];
	m_EtalonTree_8.pE			 = &m_E_8[0];
	m_EtalonTree_8.pH			 = &m_H_8[0];
	*(m_pEtalonTree+8) = m_EtalonTree_8;

	m_EtalonTree_9.LengthDeltaBit= LENGTH_DELTA_BIT_9;
	m_EtalonTree_9.SizeTree 	 = SIZE_TREE_9;
	m_EtalonTree_9.pYNorm		 = &m_YNorm_9[0];
	m_EtalonTree_9.pYDerNorm	 = &m_YDerNorm_9[0];
	m_EtalonTree_9.pCode		 = &m_Code_9[0];
	m_EtalonTree_9.pDeltaBit	 = &m_DeltaBit_9[0];
	m_EtalonTree_9.pE			 = &m_E_9[0];
	m_EtalonTree_9.pH			 = &m_H_9[0];
	*(m_pEtalonTree+9) = m_EtalonTree_9;


	//	Почистить структуры/деревья
	/*
	for (UINT16 i=STEP_AVERAGE_MIN; i<(STEP_AVERAGE_MAX+1); i++)
	{
		StrEtalonTree	EtalonTree = *(m_pEtalonTree+i);
		for (UINT16 j=0; j<EtalonTree.SizeTree; j++)
		{
			*(EtalonTree.pYNorm + j) 	 = 0.0;
			*(EtalonTree.pYDerNorm + j)  = 0.0;
			*(EtalonTree.pCode + j) 	 = 0;
			for (UINT16 k=0; k<EtalonTree.LengthDeltaBit; k++)
				*(EtalonTree.pDeltaBit + j*EtalonTree.LengthDeltaBit + k) = 0;
			*(EtalonTree.pE + j) 	 	 = 0;
			*(EtalonTree.pH + j) 	 	 = 0;
		}
	}
	*/

	m_pIndx = (UINT16*)MEM_valloc(0, MaxAmountIndx*sizeof(UINT16), 0, 0);
	if ( m_pIndx == MEM_ILLEGAL )
	{
    	ASSERT(FALSE);	return FALSE;
	}

	
	//	Построить/создать эталонные деревья
	CompositionEtalonTrees();
	
	Init();

	return TRUE;
}

BOOL	CDeltaCodec::DeCreate()
{
	if ( !MEM_free(0, m_pIndx, MaxAmountIndx*sizeof(UINT16)) )
	{
		ASSERT(FALSE);	return FALSE;
	}

	if ( !MEM_free(0, m_pEtalonTree, AMOUNT_TREES*sizeof(StrEtalonTree)) )
	{
		ASSERT(FALSE);	return FALSE;
	}

	return TRUE;
}

void	CDeltaCodec::Init()
{
	m_nState = 0;

	m_nIn[0] = 0;
	m_nIn[1] = 0;
}

void	CDeltaCodec::CompositionEtalonTrees()
{
	//	Построение эталонных деревьев, сортировка и оптимизация

	//	1.	Построить эталонные деревья
	//		YNorm = E / (2*N^2); 
	//			где : E = Sym(от G=1, до G=N)[(2*N-2*G+1)*dG]
	//		YDerNorm = Sym(от G=1, до G=N)[dG/N]
	INT16	Val;
	for (UINT16 i=STEP_AVERAGE_MIN; i<(STEP_AVERAGE_MAX+1); i++)
	{
		StrEtalonTree	EtalonTree = *(m_pEtalonTree+i);
		for (UINT16 j=0; j<EtalonTree.SizeTree; j++)
		{
			//	1.
			*(EtalonTree.pCode + j) = j;
			//	2.
			for (UINT16 k=0; k<i; k++)
			{
				if ( (0x01&(j>>k)) == 1)
					*(EtalonTree.pDeltaBit + j*i + k) = 1;
				else
					*(EtalonTree.pDeltaBit + j*i + k) = -1;
			}
			//	3.
			Val = 0;
			for (UINT16 k=0; k<i; k++)
				Val += (2*i - 2*(k+1) + 1)*(*(EtalonTree.pDeltaBit + j*i + i-1-k));
			*(EtalonTree.pE + j) 	 = Val;
			*(EtalonTree.pYNorm + j) = (float)Val / (2*i*i);
			
			//	4.
			Val = 0;
			for (UINT16 k=0; k<i; k++)
				Val += *(EtalonTree.pDeltaBit + j*i+i-1-k);
			*(EtalonTree.pH + j) 	 	= Val;
			*(EtalonTree.pYDerNorm + j) = (float)Val / i;
		}
	}
	
	//	2.	Cортировка эталонных деревьев
	//	2.1. в стеке задачи строим/выделяем эталонное дерево максимального размера,
	//		 и используем его в качестве рабочего/промежуточного буфера
	StrEtalonTree  EtalonTree_Sort;

	float 	YNorm_Sort[SIZE_TREE_9];
	float 	YDerNorm_Sort[SIZE_TREE_9];
	UINT16	Code_Sort[SIZE_TREE_9];
	INT16	DeltaBit_Sort[SIZE_TREE_9*LENGTH_DELTA_BIT_9];
	INT16	E_Sort[SIZE_TREE_9];
	INT16	H_Sort[SIZE_TREE_9];

	EtalonTree_Sort.pYNorm		= &YNorm_Sort[0];
	EtalonTree_Sort.pYDerNorm   = &YDerNorm_Sort[0];
	EtalonTree_Sort.pCode		= &Code_Sort[0];
	EtalonTree_Sort.pDeltaBit	= &DeltaBit_Sort[0];
	EtalonTree_Sort.pE			= &E_Sort[0];
	EtalonTree_Sort.pH			= &H_Sort[0];

	//	2.2. работаем с текущими деревьями
	for (UINT16 i=STEP_AVERAGE_MIN; i<(STEP_AVERAGE_MAX+1); i++)
	{
		StrEtalonTree	EtalonTree_Current = *(m_pEtalonTree+i);

		//	почистить рабочее дерево (НУЖНО НА ВРЕМЯ ОТЛАДКИ, затем заремарить)
		//	чистим часть дерева, !необходимую часть для текущего дерева
		/*
		for (UINT16 j=0; j<EtalonTree_Current.SizeTree; j++)
		{
			*(EtalonTree_Sort.pYNorm + j) 	 = 0.0;
			*(EtalonTree_Sort.pYDerNorm + j) = 0.0;
			*(EtalonTree_Sort.pCode + j) 	 = 0;
			for (UINT16 k=0; k<i; k++)
				*(EtalonTree_Sort.pDeltaBit + j*i + k) = 0;
			*(EtalonTree_Sort.pE + j) 	 	 = 0;
			*(EtalonTree_Sort.pH + j) 	 	 = 0;
		}
		*/

		//	оптимизация текущего дерева
		//	- удаление строк в которых амплитуда апроксимирующей функции и её производная равны
		//	- сортировка амплитуды апроксимирующей функции по возрастанию/убыванию
		//	1. удаление строк (берём из текущего дерева и помещаем в промежуточное/рабочее дерево)
		UINT16	NewSizeTree = 0;
		for (UINT16 j=0; j<EtalonTree_Current.SizeTree; j++)
		{
			BOOL Flag = TRUE;
			for (UINT16 k=0; k<NewSizeTree; k++)
			{
 				if ( (*(EtalonTree_Current.pYNorm + j) == *(EtalonTree_Sort.pYNorm + k)) && (*(EtalonTree_Current.pYDerNorm + j) == *(EtalonTree_Sort.pYDerNorm + k)) )
					Flag = FALSE;
			}
			if ( Flag )
			{
				*(EtalonTree_Sort.pYNorm + NewSizeTree)    = *(EtalonTree_Current.pYNorm + j);
				*(EtalonTree_Sort.pYDerNorm + NewSizeTree) = *(EtalonTree_Current.pYDerNorm + j);
				*(EtalonTree_Sort.pCode + NewSizeTree)	   = *(EtalonTree_Current.pCode + j);
				for (UINT16 k=0; k<i; k++)
					*(EtalonTree_Sort.pDeltaBit + NewSizeTree*i + k) = *(EtalonTree_Current.pDeltaBit + j*EtalonTree_Current.LengthDeltaBit + k);
				*(EtalonTree_Sort.pE + NewSizeTree)	   	   = *(EtalonTree_Current.pE + j);
				*(EtalonTree_Sort.pH + NewSizeTree)	   	   = *(EtalonTree_Current.pH + j);
				NewSizeTree++;
			}
		}//for (UINT16 j=0; j<EtalonTree_Current.SizeTree; j++)
		
		//	Результирующий размер дерева
		(m_pEtalonTree+i)->SizeTree = NewSizeTree;

		//	частичная чистка рабочего дерева (НУЖНО НА ВРЕМЯ ОТЛАДКИ, затем заремарить)
		/*
		for (UINT16 j=0; j<NewSizeTree; j++)
			*(EtalonTree_Current.pYNorm + j) = 0.0;
		*/

		//	2. сортировка строк (берём из промежуточного/рабочего дерева и помещаем в текущее дерево)
		UINT16	IndxMin;
		for (UINT16 j=0; j<NewSizeTree; j++)
		{
			float 	ValMin = 0.75;
			for (UINT16 k=0; k<NewSizeTree; k++)
			{
				if ( ValMin > *(EtalonTree_Sort.pYNorm + k) )
				{
					ValMin = *(EtalonTree_Sort.pYNorm + k);
					IndxMin = k;
				}
			}
			*(EtalonTree_Current.pYNorm + j) 	= *(EtalonTree_Sort.pYNorm + IndxMin);
			*(EtalonTree_Current.pYDerNorm + j) = *(EtalonTree_Sort.pYDerNorm + IndxMin);
			*(EtalonTree_Current.pCode + j)	    = *(EtalonTree_Sort.pCode + IndxMin);
			for (UINT16 k=0; k<i; k++)
				*(EtalonTree_Current.pDeltaBit + j*i + k) = *(EtalonTree_Sort.pDeltaBit + IndxMin*i + k);
			*(EtalonTree_Current.pE + j)	    = *(EtalonTree_Sort.pE + IndxMin);
			*(EtalonTree_Current.pH + j)	    = *(EtalonTree_Sort.pH + IndxMin);
			*(EtalonTree_Sort.pYNorm + IndxMin) = 0.75;
		}//for (UINT16 j=0; j<NewSizeTree; j++)
		
	}//for (UINT16 i=STEP_AVERAGE_MIN; i<(STEP_AVERAGE_MAX+1); i++)
}


UINT16 nC=0;
BOOL	CDeltaCodec::Proc(INT16* nIn,INT16* nOut)
{

nC++;
if ( nC == 103 )
	NOP;

	if 		( m_nState == 0 )
	{// 1й сэмпл
		m_nState++;
		m_nIn[1] 	  = *nIn;
		m_nY  	 	  = *nIn;
		*nOut    	  = m_nY;
// !!! ForSee
StateSee=0;
m_nN = STEP_AVERAGE_MIN;
m_Correction = 0;			
// !!! ForSee
	}
 	else if ( m_nState == 1 )
	{// 2й сэмпл
		m_nState++;
		m_nIn[0] 	  = m_nIn[1];
		m_nIn[1] 	  = *nIn;
		m_nYDer 	  = m_nIn[1] - m_nIn[0];
		*nOut	 	  = m_nYDer;
		m_nN 		  = STEP_AVERAGE_MIN;
// !!! ForSee
StateSee=1;		
// !!! ForSee
	}
	else
	{// последующие сэмплы (после 1го и 2го)
		m_nIn[0] 	  = m_nIn[1];
		m_nIn[1] 	  = *nIn;
		m_nA		  = m_nN*m_nN * m_nError;
		m_nYDerProgn  = m_nIn[1] - m_nIn[0];
		m_fYNorm 	  = (float)(m_nIn[0] - m_nY - m_nYDer) / m_nA;
		m_fYDerNorm   = (float)(m_nYDerProgn - m_nYDer) / m_nA;
		m_fErrorNorm  = (float)m_nError / m_nA;


//		if ( (std::fabs(m_fYNorm)) > 0.5 )
//			float a = std::fabs(m_fYNorm)- m_fErrorNorm;
		
		//	получить : 	Code, E, H
		if ( (std::fabs(m_fYNorm)) > 0.5 )				// оставить ПОКА!
//		if ( ( std::fabs(m_fYNorm)- m_fErrorNorm ) > 0.5 )
		{//	Расчёт для автономно кодируемого отсчёта
			CalcCodeEH_AKO(); // расчёт : Code, E, H, Correction
// deb
nCntr_Correction++;
// deb

			//	Расчитать амплитуду апроксимирующей функции и её производную
		//  m_nY 	= m_nY + m_nYDer + ((m_nA * 1.0/m_nN * 1.0/m_nN)/2)*m_E;
			m_nY 	= m_nY + m_nYDer + ( (m_nA /(m_nN * m_nN)) / 2 ) * m_E;
			m_nY   += m_Correction*m_nError;
		//  m_nYDer	= m_nYDer + (m_nA * 1.0/m_nN)*m_H;
			m_nYDer	= m_nYDer + (m_nA/m_nN)*m_H;
			*nOut	= m_nY;

			
			//	Вариант 1			
			/*
			//	Следующий шаг учащения в этом случае максимальный
			m_nN = STEP_AVERAGE_MAX;
			*/
			
			/**/
			//	Вариант 2
			//	Следующий шаг учащения увеличивается более плавно
			m_nN += m_nNB;
			if 		( m_nN < STEP_AVERAGE_MIN )
				m_nN = STEP_AVERAGE_MIN;
			else if ( m_nN > STEP_AVERAGE_MAX )
				m_nN = STEP_AVERAGE_MAX;
			/**/
		}
		else
		{//	Нормальный расчёт
			CalcCodeEH_Normal(); // расчёт : Code, E, H
			
			//	Расчитать амплитуду апроксимирующей функции и её производную
		 //m_nY 	= m_nY + m_nYDer + ((m_nA * 1.0/m_nN * 1.0/m_nN)/2)*m_E;
			m_nY 	= m_nY + m_nYDer + ( (m_nA /(m_nN * m_nN)) / 2 ) * m_E;
		 //m_nYDer	= m_nYDer + (m_nA * 1.0/m_nN)*m_H;
			m_nYDer	= m_nYDer + (m_nA/m_nN)*m_H;
			*nOut	= m_nY;
	
			//	Расчёт следующего шага учащения
			/*
			//	Вариант 1
			float fN;
			fN = (std::fabs(m_H))/m_nN;
			//if 	( (fN >= 3.0/5.0) && (fN <= 1.0) )
			if 		( (fN >= 0.6) && (fN <= 1.0) )
			{
				if ( m_nN++ > STEP_AVERAGE_MAX )
					m_nN = STEP_AVERAGE_MAX;
			}
			//else if ( (fN >  1.0/5.0) && (fN <= 3.0/5.0) )
			//	NOP;
			//else if ( (fN >= 0.0) && (fN <= 1.0/5.0) )
			else if   ( (fN >= 0.0) && (fN <= 0.2) )
			{
				if ( m_nN-- < STEP_AVERAGE_MIN )
					m_nN = STEP_AVERAGE_MIN;
			}
			*/
			
			//	Вариант 2
			/**/
			float dNormalK = (((float)m_nN - (float)m_H)/2.0) / (((float)m_nN + 1)/(2.0 * (float)m_nNB));
			if  ( dNormalK > ( 2 * m_nNB ) )
			{
				NOP;
			    ASSERT(FALSE);	
			}

			UINT16 Result;
			if(  dNormalK < m_nNB )
			{
				Result = m_nNB - (UINT16)dNormalK;
				if( ( dNormalK - (UINT16)dNormalK ) > 0 )
					Result--;
			}
			else
			{
				Result = (UINT16)dNormalK - m_nNB;
				if( ( dNormalK - (UINT16)dNormalK ) > 0 )
					Result++;
			}
			m_nN = m_nN + Result - 1;
			
			if 		( m_nN < STEP_AVERAGE_MIN )
				m_nN = STEP_AVERAGE_MIN;
			else if ( m_nN > STEP_AVERAGE_MAX )
				m_nN = STEP_AVERAGE_MAX;
			/**/
			
// !!! ForSee
m_Correction = 0;			
// !!! ForSee
		}
// !!! ForSee
StateSee=2;
// !!! ForSee
	}
	
	
// !!! ForSee			
if 		( StateSee == 0 )
{
	g_nDeCodSign[nIndxDeCodSign] = m_nY;
	g_nStep[nIndxDeCodSign] = m_nN;
	g_nCorr[nIndxDeCodSign] = m_Correction;
	nIndxDeCodSign++;
}	
else if ( StateSee != 1 )
{
	g_nDeCodSign[nIndxDeCodSign] = m_nY;
	g_nStep[nIndxDeCodSign] = m_nN;
	g_nCorr[nIndxDeCodSign] = m_Correction;
	nIndxDeCodSign++;
	if ( std::abs(m_nIn[0] - m_nY) > m_nError )
		NOP;
}	
// !!! ForSee			
	
	return TRUE;

}

void 	CDeltaCodec::CalcCodeEH_AKO()
{
	StrEtalonTree	EtalonTree = *(m_pEtalonTree + m_nN);
	UINT16 	IndxResult;
	
	//	1.	из столбца 'производная апроксимирующей функции нормированная' выбрать
	//		строку максимально близкую к 'YDerNorm'
	float 	Val  = std::fabs( *(EtalonTree.pYDerNorm + 0) - m_fYDerNorm);
	float 	ValMax;
	UINT16	Indx = 0;
	for (UINT16 i=1; i<EtalonTree.SizeTree; i++)
	{
		ValMax = std::fabs( *(EtalonTree.pYDerNorm + i) - m_fYDerNorm);
		if ( Val > ValMax )
		{
			Val = ValMax;
			Indx++;
		}
	}

	//	2.	в столбце 'производная апроксимирующей функции нормированная' посчитать
	//		количество строк с одинаковыми значениями 'производная апроксимирующей функции нормированная'
	//		и запомнить их индексы
	UINT16	AmountIndx = 0;
	Val = *(EtalonTree.pYDerNorm + Indx);
	for (UINT16 i=0; i<EtalonTree.SizeTree; i++)
	{
		if ( Val == *(EtalonTree.pYDerNorm + i) )
			*(m_pIndx + AmountIndx++) = i;
	}

	//	3.	из выбранных строк выбрать ту у которой значение 'амплитуда апроксимирующей функции нормированная'
	//		ближе всего к 'YNorm'
	IndxResult = Indx = *(m_pIndx + 0);
	Val  = std::fabs( *(EtalonTree.pYNorm + Indx) - m_fYNorm);
	for (UINT16 i=1; i<AmountIndx; i++)
	{
		Indx = *(m_pIndx + i);
		ValMax = std::fabs( *(EtalonTree.pYNorm + Indx) - m_fYNorm);
		if ( Val > ValMax )
		{
			Val = ValMax;
			IndxResult = Indx;
		}
	}
	
	//	получен индекс строки, извлечь содержимое строки для дальнейшего расчёта
	m_Code 		 = *(EtalonTree.pCode + IndxResult);
	m_E 		 = *(EtalonTree.pE 	  + IndxResult);
	m_H 		 = *(EtalonTree.pH 	  + IndxResult);
	m_Correction = INT16( ( m_fYNorm - *(EtalonTree.pYNorm + IndxResult) ) / m_fErrorNorm );
}

void 	CDeltaCodec::CalcCodeEH_Normal()
{
	StrEtalonTree	EtalonTree = *(m_pEtalonTree + m_nN);

	UINT16	IndxMinRange1  = 0;
	UINT16	IndxMaxRange1  = 0 + EtalonTree.SizeTree/2 - 1;
	UINT16	IndxMinRange2  = 0 + EtalonTree.SizeTree/2;
	UINT16	IndxMaxRange2  = 0 + EtalonTree.SizeTree - 1;
	UINT16	SizeTreeRange1 = IndxMaxRange1 - IndxMinRange1 + 1;
	UINT16	SizeTreeRange2 = IndxMaxRange2 - IndxMinRange2 + 1;

	UINT16 	IndxResult;

	for (;;)
	{
		if 		( (m_fYNorm >= *(EtalonTree.pYNorm + IndxMinRange1)) && (m_fYNorm <= *(EtalonTree.pYNorm + IndxMaxRange1)) )
		{// 1я половина
			if ( (IndxMaxRange1 - IndxMinRange1) >= 1 )
			{// ещё итерация
				IndxMaxRange1  = IndxMinRange1 + SizeTreeRange1/2 - 1;
				IndxMaxRange2  = IndxMinRange1 + SizeTreeRange1 - 1;
				IndxMinRange2  = IndxMinRange1 + SizeTreeRange1/2;
				SizeTreeRange1 = IndxMaxRange1 - IndxMinRange1 + 1;
				SizeTreeRange2 = IndxMaxRange2 - IndxMinRange2 + 1;
			}
			else // результат в 1й половине
			{//	чётко середина
				{//	\/ выбор строки амплитуды апроксимирующей функции (в методе CalcCodeEH_Normal() встречается три раза подряд)
					float ValMin = m_fYNorm - m_fErrorNorm;
					float ValMax = m_fYNorm + m_fErrorNorm;
					
					for (;;)
					{
						if ( !((*(EtalonTree.pYNorm + IndxMaxRange1) >= ValMin) && (*(EtalonTree.pYNorm + IndxMaxRange1) <= ValMax)) )
							IndxMaxRange1++;
						else
							break;
					}
				
					//	возможное смещение вверх, если строки амплитуд апроксимирующей функции равны
					UINT16 	IndxMinRange = IndxMaxRange1;
					for (;;)
					{
						if ( *(EtalonTree.pYNorm + IndxMaxRange1) == *(EtalonTree.pYNorm + (IndxMinRange-1)) )
							IndxMinRange--;
						else
							break;
					}
					
					//	возможное смещение вниз, если строки амплитуд апроксимирующей функции равны
					UINT16 	IndxMaxRange = IndxMinRange2;
					for (;;)
					{
						if ( *(EtalonTree.pYNorm + IndxMinRange2) == *(EtalonTree.pYNorm + (IndxMaxRange+1)) )
							IndxMaxRange++;
						else
							break;
					}
				
					//	выбираем строки производной апроксимирующей функции в диапазоне : IndxMinRange - IndxMaxRange
					UINT16 	IndxCurrent;
					IndxResult 	= IndxCurrent 	= IndxMinRange;
					ValMin 		= std::fabs(m_fYDerNorm - *(EtalonTree.pYDerNorm + IndxCurrent++));
					for (UINT16 i=1; i<(IndxMaxRange-IndxMinRange+1); i++)
					{
						ValMax = std::fabs(m_fYDerNorm - *(EtalonTree.pYDerNorm + IndxCurrent));
						if ( ValMin > ValMax )
						{
							ValMin 		= ValMax;
							IndxResult 	= IndxCurrent++;
						}
					}
				}//	/\ выбор строки амплитуды апроксимирующей функции (в методе CalcCodeEH_Normal() встречается три раза подряд)
				break;
			}
		}
		else if ( (m_fYNorm >= *(EtalonTree.pYNorm + IndxMinRange2)) && (m_fYNorm <= *(EtalonTree.pYNorm + IndxMaxRange2)) )
		{// 2я половина 
			if ( (IndxMaxRange2 - IndxMinRange2) >= 1 )
			{// ещё итерация
				IndxMinRange1  = IndxMinRange2;
				IndxMaxRange1  = IndxMinRange2 + SizeTreeRange2/2 - 1;
				IndxMaxRange2  = IndxMinRange2 + SizeTreeRange2 - 1;
				IndxMinRange2  = IndxMinRange2 + SizeTreeRange2/2;
				SizeTreeRange1 = IndxMaxRange1 - IndxMinRange1 + 1;
				SizeTreeRange2 = IndxMaxRange2 - IndxMinRange2 + 1;
			}
			else // результат во 2й половине
			{//	чётко середина
				{//	\/ выбор строки амплитуды апроксимирующей функции (в методе CalcCodeEH_Normal() встречается три раза подряд)
					float ValMin = m_fYNorm - m_fErrorNorm;
					float ValMax = m_fYNorm + m_fErrorNorm;
					
					for (;;)
					{
						if ( !((*(EtalonTree.pYNorm + IndxMaxRange1) >= ValMin) && (*(EtalonTree.pYNorm + IndxMaxRange1) <= ValMax)) )
							IndxMaxRange1++;
						else
							break;
					}
				
					//	возможное смещение вверх, если строки амплитуд апроксимирующей функции равны
					UINT16 	IndxMinRange = IndxMaxRange1;
					for (;;)
					{
						if ( *(EtalonTree.pYNorm + IndxMaxRange1) == *(EtalonTree.pYNorm + (IndxMinRange-1)) )
							IndxMinRange--;
						else
							break;
					}
					
					//	возможное смещение вниз, если строки амплитуд апроксимирующей функции равны
					UINT16 	IndxMaxRange = IndxMinRange2;
					for (;;)
					{
						if ( *(EtalonTree.pYNorm + IndxMinRange2) == *(EtalonTree.pYNorm + (IndxMaxRange+1)) )
							IndxMaxRange++;
						else
							break;
					}
				
					//	выбираем строки производной апроксимирующей функции в диапазоне : IndxMinRange - IndxMaxRange
					UINT16 	IndxCurrent;
					IndxResult 	= IndxCurrent 	= IndxMinRange;
					ValMin 		= std::fabs(m_fYDerNorm - *(EtalonTree.pYDerNorm + IndxCurrent++));
					for (UINT16 i=1; i<(IndxMaxRange-IndxMinRange+1); i++)
					{
						ValMax = std::fabs(m_fYDerNorm - *(EtalonTree.pYDerNorm + IndxCurrent));
						if ( ValMin > ValMax )
						{
							ValMin 		= ValMax;
							IndxResult 	= IndxCurrent++;
						}
					}
				}//	/\ выбор строки амплитуды апроксимирующей функции (в методе CalcCodeEH_Normal() встречается три раза подряд)
				break;
			}
		}
		else
		{//	чётко середина
			{//	\/ выбор строки амплитуды апроксимирующей функции (в методе CalcCodeEH_Normal() встречается три раза подряд)
				float ValMin = m_fYNorm - m_fErrorNorm;
				float ValMax = m_fYNorm + m_fErrorNorm;
				
				for (;;)
				{
					if ( !((*(EtalonTree.pYNorm + IndxMaxRange1) >= ValMin) && (*(EtalonTree.pYNorm + IndxMaxRange1) <= ValMax)) )
						IndxMaxRange1++;
					else
						break;
				}
			
				//	возможное смещение вверх, если строки амплитуд апроксимирующей функции равны
				UINT16 	IndxMinRange = IndxMaxRange1;
				for (;;)
				{
					if ( *(EtalonTree.pYNorm + IndxMaxRange1) == *(EtalonTree.pYNorm + (IndxMinRange-1)) )
						IndxMinRange--;
					else
						break;
				}
				
				//	возможное смещение вниз, если строки амплитуд апроксимирующей функции равны
				UINT16 	IndxMaxRange = IndxMinRange2;
				for (;;)
				{
					if ( *(EtalonTree.pYNorm + IndxMinRange2) == *(EtalonTree.pYNorm + (IndxMaxRange+1)) )
						IndxMaxRange++;
					else
						break;
				}
			
				//	выбираем строки производной апроксимирующей функции в диапазоне : IndxMinRange - IndxMaxRange
				UINT16 	IndxCurrent;
				IndxResult 	= IndxCurrent 	= IndxMinRange;
				ValMin 		= std::fabs(m_fYDerNorm - *(EtalonTree.pYDerNorm + IndxCurrent++));
				for (UINT16 i=1; i<(IndxMaxRange-IndxMinRange+1); i++)
				{
					ValMax = std::fabs(m_fYDerNorm - *(EtalonTree.pYDerNorm + IndxCurrent));
					if ( ValMin > ValMax )
					{
						ValMin 		= ValMax;
						IndxResult 	= IndxCurrent++;
					}
				}
			}//	/\ выбор строки амплитуды апроксимирующей функции (в методе CalcCodeEH_Normal() встречается три раза подряд)
			break;
		}
	}//for (;;)
	
	//	получен индекс строки, извлечь содержимое строки для дальнейшего расчёта
	m_Code 	= *(EtalonTree.pCode + IndxResult);
	m_E 	= *(EtalonTree.pE 	 + IndxResult);
	m_H 	= *(EtalonTree.pH 	 + IndxResult);
}
