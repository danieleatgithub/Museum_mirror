/*
浜様様様様様様様様様様様様様様様様様様様様様冤様様様様様用様様様様様様様様様様?
? FILE:\CADASM\R10\ROM\COMMAND\WRITE.C      ?VERS:1.1    ?TIPO: MODULO C      ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳田陳陳陳陳陳珍陳陳陳陳陳陳陳陳陳陳?
? AUTORE: Colombo Daniele                   ?DATA: Thu  10-07-1993  20:03:38  ?
麺様様様様様様様様様様様様様様様様様様様様様詫様様様様様様様様様様様様様様様様?
? INCLUDE: stdio.h - \cadasm\r10\rom\include\conio.h                          ?
? \cadasm\r10\rom\include\command.h - \cadasm\r10\rom\include\error.h         ?
麺様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
? FUNZIONI PUBBLICHE: write() - wrport()                                      ?
麺様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
? DESCRIZIONE: MODULO PER COMANDI DI LETTURA                                  ?
? Creazioni di :                                                              ?
?                                                                             ?
?                                                                             ?
?                                                                             ?
藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
*/
#include  <stdio.h>                        
#include  "\cadasm\r10\rom\include\conio.h"
#include  "\cadasm\r10\rom\include\error.h"
#include  "\cadasm\r10\rom\include\command.h"

/* --------------------- IMPORTAZIONI ------------------------*/
extern CMD com;              /* DESCRITTORE ULTIMO COMANDO   */

/* --------------------- CREAZIONI ------------------------*/

/*
浜様様様様様様様様様様様様様様様様様様様様様冤様様様様様様様様様様様様様様様様?
? FUNZIONE : WRITE                          ?DATE: Thu  10-07-1993  20:10:22  ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳祖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? FUNZIONI CHIAMATE : Nessuna                                                 ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? DESCRIZIONE : comando mml per la scrittura in memoria                       ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? SINTASSI COMANDO:                                                           ?
? WRITE [address] [byte] [byte] ... : Scrive a partire dall'indirizzo         ?
?  [address] tutti i [byte] (massimo MAXPAR)                                  ?
藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
*/

COMMAND(write)
{
register char i;
unsigned char *ptrwrite;
ptrwrite=(unsigned char *)com.param[1];
for(i=2; i< numarg ; ++i, ++ptrwrite)
    *ptrwrite = (unsigned char)com.param[i];

com.function=nullfunc;
for(i=1;i<MAXPAR;++i) com.param[i]=NULL;
return(TRUE);
}
/*
浜様様様様様様様様様様様様様様様様様様様様様冤様様様様様様様様様様様様様様様様?
? FUNZIONE : WRPORT                         ?DATE: Thu  10-07-1993  20:15:58  ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳祖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? FUNZIONI CHIAMATE : wrregadd()- writeb()                                    ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? DESCRIZIONE : comando mml per la scrittura di una porta                     ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? SINTASSI COMANDO:                                                           ?
? WRPORT [address] [byte]    : Scrive alla porta di indirizzo [address]       ?
?                              un [byte]                                      ?
? WRPORT [address] [byte] [Intreg] : Scrive alla porta di indirizzo [address] ?
? al registro interno [Intreg] un [byte]                                      ?
藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
*/

COMMAND(wrport)
{
unsigned char tmp;

if(numarg>2) wrregadd((unsigned char)com.param[2],com.param[3],com.param[2]);
else {
     tmp=(unsigned char)com.param[2];
     writeb(&tmp,1,com.param[1]);
    }
com.function=nullfunc;
return(TRUE);
}

