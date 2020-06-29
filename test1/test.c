#include <stdio.h>
#include <stdlib.h>
#include <dos.h>


float test[1000000];
unsigned char *video = (unsigned char *) 0x000a0000;

void main(void)
{
	int i = 0;
	//union REGS regs;

	// test very large arrays in 32 bits :)
	
	for (i = 0; i < 1000000; i++) 
	{
		test[i] = i;
	}
	
	for (i = 0; i < 1000000; i++) 
	{
		printf("%d = %f\n", i, test[i]);
	}


	//getch();

	//regs.h.ah = 0x00;  /* function 00h = mode set */
	//regs.h.al = 0x13;  /* 256-color */
	//int386(0x10,&regs,&regs); /* do it! */	
	
	//outpw(0x60, 65);
	
	//for (i = 0; i < 320 * 200; i++) 
	//{
	//	*video = i;
	//	video++;
	//}	

	
}
