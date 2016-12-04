/*
�����������������������������������������������������������������������������ͻ
� FILE:\CADASM\R10\ROM\COMMAND\WRITE.C      �VERS:1.1    �TIPO: MODULO C      �
�����������������������������������������������������������������������������Ķ
� AUTORE: Colombo Daniele                   �DATA: Thu  10-07-1993  20:03:38  �
�����������������������������������������������������������������������������͹
� INCLUDE: stdio.h - \cadasm\r10\rom\include\conio.h                          �
� \cadasm\r10\rom\include\command.h - \cadasm\r10\rom\include\error.h         �
�����������������������������������������������������������������������������͹
� FUNZIONI PUBBLICHE: write() - wrport()                                      �
�����������������������������������������������������������������������������͹
� DESCRIZIONE: MODULO PER COMANDI DI LETTURA                                  �
� Creazioni di :                                                              �
�                                                                             �
�                                                                             �
�                                                                             �
�����������������������������������������������������������������������������ͼ
*/
#include  <stdio.h>                        
#include  "\cadasm\r10\rom\include\conio.h"
#include  "\cadasm\r10\rom\include\error.h"
#include  "\cadasm\r10\rom\include\command.h"

/* --------------------- IMPORTAZIONI ------------------------*/
extern CMD com;              /* DESCRITTORE ULTIMO COMANDO   */

/* --------------------- CREAZIONI ------------------------*/

/*
�����������������������������������������������������������������������������ͻ
� FUNZIONE : WRITE                          �DATE: Thu  10-07-1993  20:10:22  �
�����������������������������������������������������������������������������Ķ
� FUNZIONI CHIAMATE : Nessuna                                                 �
�����������������������������������������������������������������������������Ķ
� DESCRIZIONE : comando mml per la scrittura in memoria                       �
�����������������������������������������������������������������������������Ķ
� SINTASSI COMANDO:                                                           �
� WRITE [address] [byte] [byte] ... : Scrive a partire dall'indirizzo         �
�  [address] tutti i [byte] (massimo MAXPAR)                                  �
�����������������������������������������������������������������������������ͼ
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
�����������������������������������������������������������������������������ͻ
� FUNZIONE : WRPORT                         �DATE: Thu  10-07-1993  20:15:58  �
�����������������������������������������������������������������������������Ķ
� FUNZIONI CHIAMATE : wrregadd()- writeb()                                    �
�����������������������������������������������������������������������������Ķ
� DESCRIZIONE : comando mml per la scrittura di una porta                     �
�����������������������������������������������������������������������������Ķ
� SINTASSI COMANDO:                                                           �
� WRPORT [address] [byte]    : Scrive alla porta di indirizzo [address]       �
�                              un [byte]                                      �
� WRPORT [address] [byte] [Intreg] : Scrive alla porta di indirizzo [address] �
� al registro interno [Intreg] un [byte]                                      �
�����������������������������������������������������������������������������ͼ
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