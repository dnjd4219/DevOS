/**
 *  file    Main.c
 *  date    2009/01/02
 *  author  kkamagui
 *          Copyright(c)2008 All rights reserved by kkamagui
 *  brief   C 언어로 작성된 커널의 엔트리 포인트 파일
 */

#include "Types.h"
#include "Keyboard.h"
#include "Descriptor.h"
#include "PIC.h"
#include "Console.h"
#include "ConsoleShell.h"
#include "Task.h"
#include "PIT.h"

// 함수 선언
void kPrintString( int iX, int iY, const char* pcString );

/**
 *  아래 함수는 C 언어 커널의 시작 부분임
 */
void Main( void )
{
	int iCursorX, iCursorY;

	kInitializeConsole(0, 10);
	kPrintf("Switch To IA-32e Mode Success~!!\n");
	kPrintf("IA-32e C Language Kernel Start..............[Pass]\n");
	kPrintf("Initialize Console...........................[Pass]\n");

	kGetCursor(&iCursorX, &iCursorY);
	kPrintf("GET Initialize And Switch For IA-32e Mode...[    ]");
	kInitializeGDTTableAndTSS();
	kLoadGDTR(GDTR_STARTADDRESS);
	kSetCursor(45, iCursorY++);
	kPrintf("Pass\n");

	kPrintf("TSS Segment Load............................[    ]");
	kLoadTR(GDT_TSSSEGMENT);
	kSetCursor(45, iCursorY++);
	kPrintf("Pass\n");

	kPrintf("IDT Initialize...............................[    ]");
	kInitializeIDTTables();
	kLoadIDTR(IDTR_STARTADDRESS);
	kSetCursor(45, iCursorY++);
	kPrintf("Pass\n");

	kPrintf("Total RAM Size Check.........................[    ]");
	kCheckTotalRAMSize();
	kSetCursor(45, iCursorY++);
	kPrintf("Pass], Size = %d MB\n", kGetTotalRAMSize());

	kPrintf("TCB Pool And Scheduler Initialize...........[Pass]\n");
	iCursorY++;
	kInitializeScheduler();

	kInitializePIT(MSTOCOUNT(1), 1);

	kPrintf("Keyboard Activate And Queue Initialize......[    ]");

	if(kInitializeKeyboard() == TRUE){
		kSetCursor(45, iCursorY++);
		kPrintf("Pass\n");
		kChangeKeyboardLED(FALSE, FALSE, FALSE);
	}
	else{
		kSetCursor(45, iCursorY++);
		kPrintf("Fail\n");
		while(1);
	}

	kPrintf("PIC Controller And Interrupt Initialize.....[    ]");
	kInitializePIC();
	kMaskPICInterrupt(0);
	kEnableInterrupt();
	kSetCursor(45, iCursorY++);
	kPrintf("Pass\n");

	kStartConsoleShell();

}
void kPrintString( int iX, int iY, const char* pcString )
{
    CHARACTER* pstScreen = ( CHARACTER* ) 0xB8000;
    int i;

    // X, Y 좌표를 이용해서 문자열을 출력할 어드레스를 계산
    pstScreen += ( iY * 80 ) + iX;

    // NULL이 나올 때까지 문자열 출력
    for( i = 0 ; pcString[ i ] != 0 ; i++ )
    {
        pstScreen[ i ].bCharactor = pcString[ i ];
    }
}
