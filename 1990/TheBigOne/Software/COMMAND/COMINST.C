#include  <stdio.h>                        
#include  "\cadasm\r10\rom\include\conio.h"
#include  "\cadasm\r10\rom\include\command.h"
#include  "\cadasm\r10\rom\include\io.h"
#include  "\cadasm\r10\rom\include\error.h"


extern CMD com;
extern int (*entrycom[MAXCOM])();  /* Array di puntatori a funzione comandi   */

/*
浜様様様様様様様様様様様様様様様様様様様様様冤様様様様様様様様様様様様様様様様?
? FUNZIONE : COMINST                        ?DATE: Tue  12-28-1993  21:10:03  ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳祖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? FUNZIONI CHIAMATE :                                                         ?
?                                                                             ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? DESCRIZIONE : comando mml per installare un nuovo comando                   ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? SINTASSI COMANDO:                                                           ?
? COMINST [name] [address]                                                    ?
?    -[Name]   : Nome del comando da installare                               ?
?    -[Address]: Indirizzo a cui e' allocato il comando                       ?
?                                                                             ?
藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
*/
COMMAND(cominst)
{
int ret;
int comind;
unsigned char *tmp;

com.function=nullfunc;
tmp=(unsigned char *)install;
ret=RTNBAD;
comind=whichcom((char *)com.param[1],UPPER);
if (comind == RTNBAD) {
    outmessage(COMMAND_I);
    outmessage(NOT_I);
    outmessage(FOUND_I);
}
else {
    if(*tmp==NOTINST) {
        outmessage(COMMAND_I);
        outmessage(NOT_I);
        outmessage(LOAD_ER_I);
    }
    else {
        entrycom[comind]=(int (*)())com.param[2];
        install();
        *tmp=NOTINST;
        ret=TRUE;
    }
}
return(ret);
}

