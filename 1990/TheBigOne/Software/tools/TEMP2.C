#include <bios.h>
#include <conio.h>

#define COM1       1
#define DATA_READY 0x100
#define TRUE       1
#define FALSE      0

#define BAUD 0x40 // 300 baud //
#define BITS 0x06 // 2 bit di stop //
#define PARITY 0x00 // no parity        //
#define BITD 0x01 // 8 DATA BIT       //

#define SETTINGS ( BAUD | BITS | PARITY | BITD )

int main(void)
{
   int in, out, status, DONE = FALSE;

   bioscom(0, SETTINGS, COM1);
   cprintf("... BIOSCOM [ESC] to exit ...\n");
   while (!DONE)
   {
      status = bioscom(3, 0, COM1);
 //     printf("%x\n",status);       //
      if (status & DATA_READY)
      if ((out = bioscom(2, 0, COM1) & 0x7F) != 0)
            putch(out);
         if (kbhit())
         {
            if ((in = getch()) == '\x1B')
               DONE = TRUE;

	    cprintf("%c",in);
            bioscom(1, in, COM1);
         }
   }
   return 0;
}
