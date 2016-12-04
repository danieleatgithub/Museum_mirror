#include  <stdio.h>
#include  "\cadasm\r10\rom\include\conio.h"
#include  "\cadasm\r10\rom\include\command.h"
#include  "\cadasm\r10\rom\include\io.h"
#include  "\cadasm\r10\rom\include\epb.h"
#include  "\cadasm\r10\rom\include\error.h"

extern CMD com;
extern int (*entrycom[MAXCOM])();  /* Array di puntatori a funzione comandi   */


COMMAND(eprog)
{
int ret;
unsigned char *from,*epadd,data;
unsigned int len,size;
int result;

    ret=TRUE;
    switch(com.param[1]){
        case S_2764_D:
        case S_2764_H:
            len=0x1FFF;
            size=SZ64;
            break;
        case S_27256_D:
        case S_27256_H:
            len=0xFFFF;
            size=SZ256;
            break;
        default:
        ret=RTNBAD;
    }
    reseprom();
    from=(unsigned char *)com.param[2];
    data=*from;
    epadd=0;
    do {
        result=wreprom(epadd,data,size);
        ++from;
        ++epadd;
        data= *from;
        --len;
    }while(result==0&&len!=0);
    if(result) {
        releprom(EP_FAIL);
        ret=RTNBAD;
        printf("Failed at:%x wr %x rd %x\n\r",--epadd,*(--from),result);
    }
    printf("Programm OK\r\n");
    releprom(EP_PASS);
    com.function=nullfunc;
}






