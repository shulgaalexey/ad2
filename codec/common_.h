#ifndef __COMMON_H__
#define __COMMON_H__

#include "stdmdm.h"


void sleep(UINT16 ms);
void mdmAssertX();									// ������� "ASSERT"
void out_of_store();
void StackCheckMax(UINT16& stack_max, UINT16& sysUsed_max);
void tracehtime();									// ����������� �������


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


#endif //__COMMON_H__

