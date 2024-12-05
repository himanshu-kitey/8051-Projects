#include <reg51.h>
#include "_types.h"
#include "_delay_ms.h"

sbit R0=P2^0;
sbit R1=P2^1;
sbit R2=P2^2;
sbit R3=P2^3;
sbit C0=P2^4;
sbit C1=P2^5;
sbit C2=P2^6;
sbit C3=P2^7;

const _U8 keypad_data[4][4]={'7','8','9','A',
                           '4','5','6','B',
                           '1','2','3','C',
                           '*','0','#','D'};

_U8 keypad(_U8 z)
{
	
	_U8 r,c;
	R0=R1=R2=R3=0;
	C0=C1=C2=C3=1;
	while(C0&&C1&&C2&&C3)
		if(z==' ') return z;
	
	R0=0; R1=R2=R3=1;
	if(!(C0&&C1&&C2&&C3))
	{
		r=0;
		goto NEXT;
	}
	R1=0; R0=1;
	if(!(C0&&C1&&C2&&C3))
	{
		r=1;
		goto NEXT;
	}
	R2=0; R1=1;
	if(!(C0&&C1&&C2&&C3))
	{
		r=2;
		goto NEXT;
	}
	R3=0; R2=1;
	if(!(C0&&C1&&C2&&C3))
	{
		r=3;
		goto NEXT;
	}
	NEXT:
	if(C0==0) c=0;
	else if(C1==0) c=1;
	else if(C2==0) c=2;
	else if(C3==0) c=3;
	while(!(C0&&C1&&C2&&C3))
	if(z==' ') return keypad_data[r][c];		
	return keypad_data[r][c];
}