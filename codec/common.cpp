#include "__common.h"
#include "common.h"
#include <clk.h>

/*
#include <csl.h>

#if ((CHIP_5509_FAMILY + CHIP_5502_FAMILY) != 1)
	#error "Что-то плохо с типом чипа"
#endif

// !!! Во внешнюю не выносить
// подстроено осциллографом при оптимизаци -o0
// без оптимизации децл длинее
void delay_us(UINT16 us)
{
	if (!us) return;

	while(us--)
	{
		#if   (DSP_CLOCK_MHZ == 300)
			asm(" RPT #288");
		#elif (DSP_CLOCK_MHZ == 200)
			asm(" RPT #190");
		#elif (DSP_CLOCK_MHZ == 192)
			asm(" RPT #175");
		#elif (DSP_CLOCK_MHZ == 120)
			asm(" RPT #106");
		#elif (DSP_CLOCK_MHZ == 100)
			asm(" RPT #90");
		#elif (DSP_CLOCK_MHZ == 96)
				asm(" RPT #85");		// не измерялось
		#elif (DSP_CLOCK_MHZ == 60)
				asm(" RPT #45");
		#elif (DSP_CLOCK_MHZ == 48)
				asm(" RPT #40");
				
		#else
			#error "DSP_CLOCK_MHZ не определен"
		#endif
		NOP;
	}
}
*/

/*
void delay_us_test()
{
	for(;;)
	{
		asm(" BCLR XF");
		delay_us(10);
		asm(" BSET XF");
		delay_us(10);		
	}
}
*/

//#pragma CODE_SECTION(".ext_code_sdram");
void out_of_store()
{
	ASSERT(FALSE);
}


//#pragma CODE_SECTION(".ext_code_sdram");
void mdmAssertX()
{
	STOPWORD;
}


void StackCheckMax(UINT16& stack_max, UINT16& sysUsed_max)
{
/*
	TSK_Stat statBuf;
	TSK_stat( TSK_self(), &statBuf);
	if ((statBuf.used > stack_max)||(statBuf.sysUsed > sysUsed_max))
	{
		stack_max 	= statBuf.used;
		sysUsed_max = statBuf.sysUsed;
		LOG_printf(&trace, "--------------------------------------");
		LOG_printf(&trace, TSK_getname(TSK_self()));
		LOG_printf(&trace, "Новый макс. исп. стэка %d", stack_max );
		LOG_printf(&trace, "Номинал %d", statBuf.attrs.stacksize );
		LOG_printf(&trace, "Новый макс. исп. Cис стэка %d", sysUsed_max );
	}
*/	
}

//#pragma CODE_SECTION(".ext_code_sdram"); // Во внешнюю не выносить 
void sleep(UINT16 ms)
{
//	TSK_sleep(TICKS_PER_MS*ms);
}


//откуда, куда, сколько (в исходных единицах - в словах)
//#pragma CODE_SECTION(".ext_code_sdram");
void Lg2Byte(const unsigned long* pSrc, BYTE* pDst, UINT16 nCount)
{
	while (nCount--)
	{
		WORD nLo = *pSrc;
		WORD nHi = *pSrc++ >> 16;
			
		*pDst++ = nLo & 0x00ff;
		*pDst++ = nLo >> 8;

		*pDst++ = nHi & 0x00ff;
		*pDst++ = nHi >> 8;
	}
	
}


//откуда, куда, сколько (в исходных единицах - в байтах)
//#pragma CODE_SECTION(".ext_code_sdram");
void Byte2Lg(const BYTE* pSrc, unsigned long* pDst, UINT16 nCount)
{
	if (nCount%4)				// проверить кратность 4
	{
		ASSERT(FALSE);
		return;
	}


	while (nCount)
	{
		WORD aWord  = *pSrc++ & 0x00ff;
		WORD nHi0   = *pSrc++ << 8 | aWord;

		aWord  = *pSrc++ & 0x00ff;
		WORD nHi1   = *pSrc++ << 8 | aWord;

		*pDst++ = (((UINT32)nHi1) << 16) | ((UINT32)nHi0);
		nCount-=4;
	}

}


//откуда, куда, сколько (в исходных единицах - в байтах)
//#pragma CODE_SECTION(".ext_code_sdram");
void b2w(const BYTE* pSrc, UINT16* pDst, UINT16 nCount)
{
	if (nCount%2)
	{
		ASSERT(FALSE);
		return;
	}

	while (nCount)
	{
		*pDst = (*pSrc++ & 0x00ff);
		*pDst++ |= 	(*pSrc++ << 8);
		nCount-=2;
	}
	
}


//откуда, куда, сколько (в исходных единицах - в UINT16)
//#pragma CODE_SECTION(MSCODE_INTERNAL);
void w2b(const UINT16* pSrc, BYTE* pDst, UINT16 nCount)
{
	while (nCount)
	{
		*pDst++ = (*pSrc & 0x00ff);
		*pDst++ = ((*pSrc++)>>8 & 0x00ff);
		nCount--;
	}
}


static U16 counts_per_us = 0;

//#pragma CODE_SECTION(MSCODE_INTERNAL);
U16 CLK_countspus()
{
	if (counts_per_us == 0) 
		counts_per_us = CLK_countspms()/1000;
	return counts_per_us;
}

//#pragma CODE_SECTION(MSCODE_INTERNAL);
U32 CLK_deltahtime(U32 tstart, U32 tend)
{
	U32 dt;
	if (tend >= tstart) 
		dt = tend-tstart;
	else 
		dt = (0xffffffffUL-tstart)+tend;
	return dt;
}			
			

//#pragma CODE_SECTION(MSCODE_INTERNAL);
U32 CLK_deltahtime_us(U32 tstart, U32 tend)
{
	U32 dt = CLK_deltahtime(tstart, tend);
	return dt/CLK_countspus();
}			


//#pragma CODE_SECTION(".ext_code_sdram");
void tracehtime()
{
	U32 t = CLK_gethtime();
	t %= (CLK_countspms()*1000);	// выкинули полные сек
	U16 t_ms = t/CLK_countspms();
	U16 t_us = (t%CLK_countspms()) / CLK_countspus();
//	TRACE2("t= %3u.%03u ms", t_ms, t_us);
}

//#pragma CODE_SECTION(".ext_code_sdram");
void traceltime()
{
	U32 time_ms = CLK_getltime();
//	TRACE2("t= %3u.%03u s", (U16)(time_ms/1000), (U16)(time_ms%1000));
}

//#pragma CODE_SECTION(".ext_code_sdram");
U32 traceltime_delta(U32 t_prev)
{
	U32 time_now = CLK_getltime();
	U32 dt;
	if (time_now >= t_prev) 
		dt = time_now-t_prev;
	else 
		dt = (0xffffffffUL-t_prev)+time_now;

//	TRACE2("dt= %3u.%03u s", (U16)(dt/1000), (U16)(dt%1000));

	/*
	// vl
	U16 tt = (U16)(dt%1000);
	if ( tt > 160 )
//	if ( tt > 240 )
//	if ( tt > 90 )
		TRACE1("dt= %03u ms", tt);
	*/
	
	return time_now;
}



// возвращает тип памяти по указанному адресу
// 0=daram, 1=saram, 2=emif
// <0, ошибка
//#pragma CODE_SECTION(".ext_code_sdram");
int mtype(const unsigned long memaddr)
{
	if (memaddr < 0x60ul)								//mmrs
		return -1;

	int retval = -1;
	#if (CHIP_5509_FAMILY == 1)
		if (memaddr < 0x800000ul)	retval =  2;		//emif
		if (memaddr < 0x20000ul)	retval =  1;		//saram
		if (memaddr < 0x8000ul)		retval =  0;		//daram
	#endif

	
	#if (CHIP_5502_FAMILY == 1)
		if (memaddr < 0x7fc000ul)	retval =  2;		//emif
		if (memaddr < 0x8000ul)		retval =  0;		//daram
	#endif

	return retval;
}








/*
	Q(%) = 0,11875 * Uмв - 256.25
*/
//#pragma CODE_SECTION(".ext_code_sdram");
U16 voltage_to_percent_cr2032(U16 voltage_mv)
{
	double Q = 0.11875 * voltage_mv - 256.25;
	if (Q > 100) Q = 100;
	if (Q < 0) Q = 0;
	return (U16)Q;
}


//#pragma CODE_SECTION(".ext_code_sdram");
U16 voltage_to_percent_accNiMH(U16 voltage_mv)
{
	double Q = 0;
	if (voltage_mv > 1280)	Q = 100;
	else if (voltage_mv >= 1220) Q = 1.08332 * voltage_mv - 1286.67;
	else if (voltage_mv >= 1130) Q = 0.27776 * voltage_mv -  303.89;
	else if (voltage_mv >=  900) Q = 0.04348 * voltage_mv -   39.13;

	if (Q > 100) Q = 100;
	if (Q < 0) Q = 0;
	return (U16)Q;
}



//#pragma CODE_SECTION(".ext_code_sdram");
U16 voltage_to_percent_battery(U16 voltage_mv)
{
	double Q = 0.1583333 * voltage_mv - 137.5;
	if (Q > 100) Q = 100;
	if (Q < 0) Q = 0;
	return (U16)Q;
}






