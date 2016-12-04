/*
�����������������������������������������������������������������������������ͻ
� FILE:\CADASM\R10\ROM\CADOS\MONITOR.C      �VERS:1.1    �TIPO: MODULO C      �
�����������������������������������������������������������������������������Ķ
� AUTORE: Colombo Daniele                   �DATA: Sun  09-12-1993  13:12:27  �
�����������������������������������������������������������������������������͹
� INCLUDE: stdio.h                 -     \cadasm\r10\rom\include\conio.h      �
� \cadasm\r10\rom\include\io.h     -     \cadasm\r10\rom\include\command.h    �
�����������������������������������������������������������������������������͹
� FUNZIONI PUBBLICHE: monitor()                                               �
�����������������������������������������������������������������������������͹
� DESCRIZIONE: LOOP INFINITO DI ATTESA ED ESECUZIONE COMANDI                  �
�����������������������������������������������������������������������������ͼ
*/

#include <stdio.h>
#include  "\cadasm\r10\rom\include\conio.h"
#include  "\cadasm\r10\rom\include\io.h"
#include  "\cadasm\r10\rom\include\command.h"

/* --------------------- IMPORTAZIONI ------------------------*/

extern  VIDEO   video_desc;     /* DESCRITTORE SCHERMO                     */
extern  CMD     com;            /* DESCRITTORE EDITOR DI LINEA             */
extern  char    *edlin();
/* ----------------------- CREAZIONI -------------------------*/

/*
�����������������������������������������������������������������������������ͻ
� FUNZIONE : MONITOR                        �DATE: Sun  09-12-1993  13:17:09  �
�����������������������������������������������������������������������������Ķ
� INPUT : Puntatore a descrittore di tipo LINE                                �
�����������������������������������������������������������������������������Ķ
� OUTPUT : Non esiste uscita dalla funzione                                   �
�����������������������������������������������������������������������������Ķ
� FUNZIONI CHIAMATE : ldconv() - kbhit() - getch() - edlin() - interpr()      �
� flushbuf() - printf()                                                       �
�����������������������������������������������������������������������������Ķ
� DESCRIZIONE : Loop infinito in cui si acquisiscono i comandi e si eseguono  �
� Vengono inoltre eseguite le seguenti funzioni fisse se abilitate:           �
� ��������������������������������������������������������������������������ķ�
� �FUNZIONE  �ABILITAZIONE     �AZIONE                                       ��
� ��������������������������������������������������������������������������Ķ�
� �ldconv    �Comando load     �Carica file in S format                      ��
� ��������������������������������������������������������������������������Ľ�
�����������������������������������������������������������������������������ͼ
*/
monitor(lined)
LINE 	*lined;
{
unsigned char *cmdptr;
    if(stepflg==STEPON){
        com.function=step;
    }
    else{
        com.function=nullfunc;
        }

flushbuf(lined);
while(1)                                /* Loop monitor si esce solo con go */
    {
    do{

        do{                             /* LOOP DI SCHEDULAZIONE ATTIVITA' IN BACKGROUND */
            if(sysdesc.ldp) ldconv();   /* attivo loader se caricamento in corso */
        }while(!(kbhit()));             /* attendo carattere da tastiera */
        lined -> key=getch();           /* buffer tastiera pieno prelevo carattere */
    }while((cmdptr=edlin(lined))==TRUE);
    interpr(cmdptr,lined);              /* Interpreto ed eseguo comando */
    flushbuf(lined);
    printf("\r\n%c",video_desc.prompt);
    }
}
