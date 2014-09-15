#include "stdmdm.h"
#include "switches.h"

#ifdef __cplusplus
extern "C"
{

#endif /* __cplusplus */

void InitGeneratorSignals();

void GeneratorSignals16(int* Data, int	Nch, int Frame);
void GeneratorNoise16(int* Data, int	Nch, int Frame);
void GeneratorSignalsNoise16(int* nData, int nCh, int nFrame);

void GeneratorSignalsNoise32(INT32* nData, int nCh, int nFrame);


#ifdef work_fir_m02v01_on
void InitFileSignals();
void FileSignals16(int* nData, int nCh, int nFrame);
#endif//work_fir_m02v01_on


#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

