#ifndef __COMMON_H__
#define __COMMON_H__

#include "stdmdm.h"


void sleep(UINT16 ms);
void mdmAssertX();									// ������� "ASSERT"
void out_of_store();
void StackCheckMax(UINT16& stack_max, UINT16& sysUsed_max);

// �����
U32 CLK_deltahtime(U32 tstart, U32 tend);			// ��������� ������ ����� htime
U32 CLK_deltahtime_us(U32 tstart, U32 tend);		// ��������� ������ ����� htime � ���������� � ���
U16 CLK_countspus();								// counts_per_us

void traceltime();									// ����������� ������� (s.ms)
void tracehtime();									// ����������� ������� (ms.us)
U32 traceltime_delta(U32 t_prev);


// �������� ( � ���)
void delay_us(UINT16 us);
void delay_us_test();


// �������������� (�������� ������)
//������, ����, ������� (� �������� ���������)
void Lg2Byte(const unsigned long* pSrc, BYTE* pDst, UINT16 nCount);	// Long -> BYTE
void Byte2Lg(const BYTE* pSrc, unsigned long* pDst, UINT16 nCount);	// BYTE -> Long

void w2b(const UINT16* pSrc, BYTE* pDst, UINT16 nCount);			// WORD -> BYTE
void b2w(const BYTE* pSrc, UINT16* pDst, UINT16 nCount);			// BYTE -> WORD

//������ ��� ������ �� ������
int mtype(unsigned long memaddr);



// ������� � �������� �� ���������� ��� ������ ����� ��������
U16 voltage_to_percent_cr2032(U16 voltage_mv);			// 1 ������� 3� (CR2032)
U16 voltage_to_percent_accNiMH(U16 voltage_mv);			// 1 ���. NiMH
U16 voltage_to_percent_battery(U16 voltage_mv);			// 1 ��������� (1.5�)



#endif //__COMMON_H__

