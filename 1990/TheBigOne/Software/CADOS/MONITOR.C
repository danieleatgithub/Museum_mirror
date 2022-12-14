/*
浜様様様様様様様様様様様様様様様様様様様様様冤様様様様様用様様様様様様様様様様?
? FILE:\CADASM\R10\ROM\CADOS\MONITOR.C      ?VERS:1.1    ?TIPO: MODULO C      ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳田陳陳陳陳陳珍陳陳陳陳陳陳陳陳陳陳?
? AUTORE: Colombo Daniele                   ?DATA: Sun  09-12-1993  13:12:27  ?
麺様様様様様様様様様様様様様様様様様様様様様詫様様様様様様様様様様様様様様様様?
? INCLUDE: stdio.h                 -     \cadasm\r10\rom\include\conio.h      ?
? \cadasm\r10\rom\include\io.h     -     \cadasm\r10\rom\include\command.h    ?
麺様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
? FUNZIONI PUBBLICHE: monitor()                                               ?
麺様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
? DESCRIZIONE: LOOP INFINITO DI ATTESA ED ESECUZIONE COMANDI                  ?
藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
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
浜様様様様様様様様様様様様様様様様様様様様様冤様様様様様様様様様様様様様様様様?
? FUNZIONE : MONITOR                        ?DATE: Sun  09-12-1993  13:17:09  ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳祖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? INPUT : Puntatore a descrittore di tipo LINE                                ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? OUTPUT : Non esiste uscita dalla funzione                                   ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? FUNZIONI CHIAMATE : ldconv() - kbhit() - getch() - edlin() - interpr()      ?
? flushbuf() - printf()                                                       ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? DESCRIZIONE : Loop infinito in cui si acquisiscono i comandi e si eseguono  ?
? Vengono inoltre eseguite le seguenti funzioni fisse se abilitate:           ?
? 崢陳陳陳陳賃陳陳陳陳陳陳陳陳賃陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳跳?
? ?FUNZIONE  ?ABILITAZIONE     ?AZIONE                                       査
? 把陳陳陳陳津陳陳陳陳陳陳陳陳津陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳超?
? ?ldconv    ?Comando load     ?Carica file in S format                      査
? 喞陳陳陳陳珍陳陳陳陳陳陳陳陳珍陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳捗?
藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
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