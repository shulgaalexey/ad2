#ifndef __STDMDMD_H__
#define __STDMDMD_H__


#include <std.h>
#include <string.h>			// memset(), memcpy() Из rts55.lib 
#include <lck.h>
#include <tsk.h>
#include <sem.h>

#include "switches.h"	// глобальные ключи проекта

/////////////////////////////////////////////////////////////////////////////////////////////////
#define MDM_MACRO_START do{
#define MDM_MACRO_END   }while(0)

#define MDM_EMPTY_STATEMENT MDM_MACRO_START MDM_MACRO_END

#define STOPWORD 	asm(" .if (.MNEMONIC)\n ESTOP_1\n .else\n ESTOP_1()\n .endif\n NOP")
#define NOP			asm("  nop;")


#define MAX(a,b) 	(a) >= (b) ? (a) : (b)
#define MIN(a,b) 	(a) >= (b) ? (b) : (a)


#define DIS_INTS	_disable_interrupts()
#define ENA_INTS	_enable_interrupts()



/////////////////////////////////////////////////////////////////////////////////////////////////
typedef long long 			LgLgInt;
typedef unsigned long long 	LgLgUns;

typedef Bool				BOOL;
typedef Byte				BYTE;


typedef unsigned int		UINT;
typedef unsigned int		UINT16;
typedef unsigned int		U16;
typedef unsigned int		u16;

typedef unsigned long 		UINT32;
typedef unsigned long 		U32;
typedef unsigned long 		u32;

typedef unsigned long long 	UINT40;
typedef unsigned long long 	U40;
typedef unsigned long long 	u40;

typedef char				CHAR;

typedef int					INT;
typedef int					INT16;
typedef int					I16;
typedef int					i16;

typedef long 				INT32;
typedef long 				I32;
typedef long 				i32;

typedef long long 			INT40;
typedef long long 			I40;
typedef long long 			i40;

typedef unsigned int		WORD;	// имеется ввиду двухбайтное слово (hi,lo)
typedef unsigned long 		DWORD;

typedef double 				DOUBLE;

typedef void*				HANDLE;
#define INVALID_HANDLE_VALUE		((HANDLE)(-1))


#ifdef __cplusplus
	struct __POSITION { };
	typedef __POSITION* POSITION;
#endif




/////////////////////////////////////////////////////////////////////////////////////////////////
#if defined(NASSERT)
	#define ASSERT(expr)	MDM_EMPTY_STATEMENT
#else
	#ifdef __cplusplus
		#include "common.h"
		#define ASSERT(expr) \
			MDM_MACRO_START \
			if (!(expr)) \
				mdmAssertX(); \
			MDM_MACRO_END
	#endif
#endif

struct iovec {
	void* 	p;
	UINT16	count;
};

/////////////////////////////////////////////////////////////////////////////////////////////////
#if defined(NASSERT)
	#define VERIFY(expr)			\
		MDM_MACRO_START				\
		expr;						\
		MDM_MACRO_END
#else 
	#ifdef __cplusplus
		#include "common.h"
		#define VERIFY(expr)			\
			MDM_MACRO_START				\
			if(!(expr))					\
				mdmAssertX();			\
			MDM_MACRO_END
	#endif
#endif


/////////////////////////////////////////////////////////////////////////////////////////////////
#include <log.h>
#ifdef __cplusplus
	extern "C" LOG_Obj trace;
#else
	extern LOG_Obj trace;
#endif


#if defined(NTRACE)
	#define TRACE(text) 			MDM_EMPTY_STATEMENT
	#define TRACE1(text,arg1) 		MDM_EMPTY_STATEMENT
	#define TRACE2(text,arg1,arg2)	MDM_EMPTY_STATEMENT
#else
	#define TRACE(text)				LOG_printf(&trace, text)
	#define TRACE1(text,arg1) 		LOG_printf(&trace, text, (arg1) )
	#define TRACE2(text,arg1,arg2) 	LOG_printf(&trace, text, (arg1), (arg2) )
#endif

#if defined(NLOG)
	#define LOG1(arg1) 				MDM_EMPTY_STATEMENT
	#define LOG2(arg1,arg2) 		MDM_EMPTY_STATEMENT
	#define LOG3(arg1,arg2,arg3)	MDM_EMPTY_STATEMENT
#else
	#ifdef __cplusplus
		extern class CMdmLog g_Log;
		#define LOG1(arg1) 				g_Log.WriteLog(arg1)
		#define LOG2(arg1,arg2) 		g_Log.WriteLog(arg1, arg2)
		#define LOG3(arg1,arg2,arg3) 	g_Log.WriteLog(arg1,arg2,arg3)
	#endif	
#endif

#if defined(NERROR)
	#define ERROR1(arg1) 				MDM_EMPTY_STATEMENT
	#define ERROR2(arg1,arg2) 			MDM_EMPTY_STATEMENT
	#define ERROR3(arg1,arg2,arg3)		MDM_EMPTY_STATEMENT
#else
	#ifdef __cplusplus
		extern class CMdmLogError g_ErrorLog;
		#define ERROR1(arg1) 			g_ErrorLog.WriteError(arg1)
		#define ERROR2(arg1,arg2) 		g_ErrorLog.WriteError(arg1,arg2)
		#define ERROR3(arg1,arg2,arg3)	g_ErrorLog.WriteError(arg1,arg2,arg3)
	#endif	
#endif

#define TRACEDW(text, dwA)	TRACE2(text, (UINT16)((dwA) >> 16), (UINT16)(dwA))

/////////////////////////////////////////////////////////////////////////////////////////////////
#if defined(NSTACK_CHECK)
	#define STACK_CHECK_MAX		MDM_EMPTY_STATEMENT
#else
	#ifdef __cplusplus
		#include "common.h"
		#define STACK_CHECK_MAX	\
			MDM_MACRO_START	\
			static	UINT stack_max = 0;	\
			static	UINT sysUsed_max = 0; \
			StackCheckMax(stack_max, sysUsed_max);\
			MDM_MACRO_END
	#endif	
#endif





/////////////////////////////////////////////////////////////////////////////////////////////////
// cannot be called from a SWI or HWI
// a = segid, b = "segid", где segid - число. 
// HEAP_ID_STATE(0,"DARAM");
#define HEAP_ID_STATE(a,b) \
	MDM_MACRO_START	\
	static MEM_Stat statbuf; \
	static UINT16 	mem_prev = 0xFFFF; \
	if (MEM_stat(a, &statbuf)) \
	{ \
		if (statbuf.length < mem_prev) \
		{ \
			LOG_printf(&trace, "Размер кучи "##b##" %u, осталось %u ", statbuf.size, statbuf.length); \
			mem_prev = statbuf.length; \
		} \
	} \
	else \
		LOG_printf(&trace, "ID heap invalid");\
	MDM_MACRO_END


/////////////////////////////////////////////////////////////////////////////////////////////////	
#ifdef __cplusplus
	extern "C" SEM_Obj SEM_SystemIsReadyToStart;
#endif

#define TSK_BLOCK_UNTIL_SYSTEM_READY \
	MDM_MACRO_START \
		SEM_pend(&SEM_SystemIsReadyToStart, SYS_FOREVER); \
	MDM_MACRO_END


#define PRD_RETURN_UNTIL_SYSTEM_READY \
	MDM_MACRO_START \
		if (SEM_count(&SEM_SystemIsReadyToStart) == 0) \
			return; \
	MDM_MACRO_END


#define SYSTEM_IS_READY \
	MDM_MACRO_START \
		for (UINT i=30; i>0; i--) \
			SEM_post(&SEM_SystemIsReadyToStart); \
	MDM_MACRO_END




#define HEAP_DARAM_STATE_BEGIN	MDM_EMPTY_STATEMENT
#define HEAP_DARAM_STATE_END	MDM_EMPTY_STATEMENT



/*

TMS320C55x C/C++ Data Types Range
    Type				  Size	 Representation	  Minimum		  Maximum
signed char				16 bits	ASCII			-32768			32767
char, unsigned char		16 bits	ASCII			0				65535
short, signed short 	16 bits	2s complement	-32768			32767
unsigned short			16 bits	Binary			0				65535
int, signed int			16 bits	2s complement	-32768			32767
unsigned int			16 bits	Binary			0				65535
long, signed long		32 bits	2s complement	-2147483648		2147483647
unsigned long			32 bits	Binary			0				4294967295
long long				40 bits	2s complement	-549755813888	549755813887
unsigned long long		40 bits	Binary			0				1099511627775
enum 					16 bits	2s complement	-32768			32767
float					32 bits	IEEE 32-bit		1.175494e-38	3.40282346e+38
double 					32 bits	IEEE 32-bit		1.175494e-38	3.40282346e+38
long double 			32 bits	IEEE 32-bit		1.175494e-38	3.40282346e+38
pointers (data) 				Binary			0
  small memory model 	16 bits									0xFFFF
  large memory model	23 bits									0x7FFFFF
pointers (function)		24 bits Binary			0				0xFFFFFF


<std.h>
....
#elif defined(_55_) || defined(_28_)
typedef void *Arg;
....

typedef Int (*Fxn)();

typedef double Float;


#ifndef TRUE
#define FALSE ((Bool)0)
#define TRUE  ((Bool)1)
#endif


*/



#endif //__STDMDMD_H__

