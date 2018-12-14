#ifndef __ASSEMBLYUTILITYH_H__
#define __ASSEMBLYUTILITYH_H__

#include "Task.h"

BYTE kInPortByte(WORD wPort);
void kOutPortByte(WORD wPort, BYTE bData);
void kLoadGDTR(QWORD qwGDTRAddress);
void kLoadTR(WORD wTSSSegmentOffset);
void kLoadIDTR(QWORD qwIDTRAddress);
void kEnableInterrupt(void);
void kDisableInterrupt(void);
QWORD kReadRFLAGS(void);
QWORD kReadTSC(void);
void kSwitchContext(CONTEXT *pstCurrentContext, CONTEXT *pstNextContext);
void kHlt(void);
BOOL kTestAndSet(volatile BYTE *pbDestination, BYTE bCompare, BYTE bSource);

#endif /*__ASSEMBLYUTILITYH_H__*/
