/*
ษอออออออออออออออออออออออออออออออออออออออออออัออออออออออออัออออออออออออออออออออป
บ FILE:\CADASM\R10\ROM\CADOS\MONITOR.C      ณVERS:1.1    ณTIPO: MODULO C      บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤลฤฤฤฤฤฤฤฤฤฤฤฤมฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ AUTORE: Colombo Daniele                   ณDATA: Sun  09-12-1993  13:12:27  บ
ฬอออออออออออออออออออออออออออออออออออออออออออฯอออออออออออออออออออออออออออออออออน
บ INCLUDE: stdio.h                 -     \cadasm\r10\rom\include\conio.h      บ
บ \cadasm\r10\rom\include\io.h     -     \cadasm\r10\rom\include\command.h    บ
ฬอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออน
บ FUNZIONI PUBBLICHE: monitor()                                               บ
ฬอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออน
บ DESCRIZIONE: LOOP INFINITO DI ATTESA ED ESECUZIONE COMANDI                  บ
ศอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ
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
ษอออออออออออออออออออออออออออออออออออออออออออัอออออออออออออออออออออออออออออออออป
บ FUNZIONE : MONITOR                        ณDATE: Sun  09-12-1993  13:17:09  บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤมฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ INPUT : Puntatore a descrittore di tipo LINE                                บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ OUTPUT : Non esiste uscita dalla funzione                                   บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ FUNZIONI CHIAMATE : ldconv() - kbhit() - getch() - edlin() - interpr()      บ
บ flushbuf() - printf()                                                       บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ DESCRIZIONE : Loop infinito in cui si acquisiscono i comandi e si eseguono  บ
บ Vengono inoltre eseguite le seguenti funzioni fisse se abilitate:           บ
บ ึฤฤฤฤฤฤฤฤฤฤยฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤยฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤทบ
บ บFUNZIONE  ณABILITAZIONE     ณAZIONE                                       บบ
บ วฤฤฤฤฤฤฤฤฤฤลฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤลฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถบ
บ บldconv    ณComando load     ณCarica file in S format                      บบ
บ ำฤฤฤฤฤฤฤฤฤฤมฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤมฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฝบ
ศอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ
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