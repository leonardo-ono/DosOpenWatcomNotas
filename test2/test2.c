#include <stdio.h>
#include <dos.h>

volatile int clock_ticks;
void (__interrupt __far *prev_int_lc) ();
#define BLIP_COUNT (5 * 18) /* 5 seconds */

typedef unsigned uint;
typedef unsigned char uchar;

#ifdef __WATCOMC__
// Define Borland C aliases:
#define getvect _dos_getvect
#define setvect _dos_setvect
#define outportb outp
#define inportb inp
#define disable _disable
#define enable _enable
#endif

unsigned char *video = (unsigned char *) 0xb8000;

float zbuffer[64000];

void __interrupt __far timer_rtn(void)
{
	++clock_ticks;
	//printf("teste !\n");
	*video = clock_ticks;
	video++;
	if ((int) video > 0xb8000 + 4000) 
	{
		video = (unsigned char *) 0xb8000;
	}	
	_chain_intr(prev_int_lc);
}

void SetPitResolutionInHz(uint ResolutionInHz)
{
  uint count;

  if (ResolutionInHz < 18 || ResolutionInHz >= 65535)
    return;

  count = (ResolutionInHz == 18) ? 0 : (uint)(1193181 / ResolutionInHz);

  disable();

  outportb(0x43, 0x34);
  outportb(0x40, (uchar)(count & 0xFF));
  outportb(0x40, (uchar)(count >> 8));

  enable();
}
	
void main()
{
	int i;
	for (i = 0; i < 64000; i++)
	{
		zbuffer[i] = i;
	}
	for (i = 0; i < 64000; i++)
	{
		printf("i = %f\n", zbuffer[i]);
	}
	
	prev_int_lc = _dos_getvect(8);
	_dos_setvect(8, timer_rtn);
	SetPitResolutionInHz(65534);
	//while (1) 
	//{
	//	printf("clock %d \n", clock_ticks);
	//}
	getchar();
	_dos_setvect(8, prev_int_lc);
}

