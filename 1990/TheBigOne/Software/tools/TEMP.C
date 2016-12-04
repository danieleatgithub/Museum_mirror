#include <bios.h>
#include <conio.h>


#define COM1       0
#define COM2       1
#define DATA_READY 0x100
#define B_TRUE       1
#define B_FALSE      0

#define BAUD 0x40 // 300 baud //
#define BITS 0x06 // 2 bit di stop //
#define PARITY 0x00 // no parity        //
#define BITD 0x01 // 8 DATA BIT       //

#define SETTINGS ( BAUD | BITS | PARITY | BITD )



main()
{
char i;
while(i!=255){
i=getch();
printf("%x",i);
}
   return 0;
}
