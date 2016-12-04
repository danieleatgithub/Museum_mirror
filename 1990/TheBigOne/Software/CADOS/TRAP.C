/*
ษอออออออออออออออออออออออออออออออออออออออออออัออออออออออออัออออออออออออออออออออป
บ FILE:\CADASM\R10\ROM\CADOS\TRAP.C         ณVERS:1.1    ณTIPO:MODULO C       บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤลฤฤฤฤฤฤฤฤฤฤฤฤมฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ AUTORE: Colombo Daniele                   ณDATA: Sun  09-12-1993  12:34:29  บ
ฬอออออออออออออออออออออออออออออออออออออออออออฯอออออออออออออออออออออออออออออออออน
บ INCLUDE: stdio.h - stdlib.h         -     \cadasm\r10\rom\include\conio.h   บ
บ \cadasm\r10\rom\include\command.h         \cadasm\r10\rom\include\io.h      บ
บ \cadasm\r10\rom\include\error.h                                             บ
ฬอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออน
บ FUNZIONI PUBBLICHE: nmimon() - nminstep()                                   บ
ฬอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออน
บ DESCRIZIONE: GESTIONE ECCEZIONI                                             บ
บ Creazioni:                                                                  บ
บ   -                                                                         บ
ศอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ
*/
#define __TRAP__

#include  <stdio.h>
#include  <stdlib.h>
#include  "\cadasm\r10\rom\include\conio.h"
#include  "\cadasm\r10\rom\include\command.h"
#include  "\cadasm\r10\rom\include\io.h"
#include  "\cadasm\r10\rom\include\error.h"

#define    NMIMON   nmimon      /* Routine per gestione nmi monitor */

/* --------------------- IMPORTAZIONI ------------------------*/     

extern VIDEO    video_desc;     /* DESCRITTORE SCHERMO                     */
extern LINE     monline;        /* DESCRITTORE EDITOR DI LINEA             */

/* ----------------------- CREAZIONI -------------------------*/


/*
ษอออออออออออออออออออออออออออออออออออออออออออัอออออออออออออออออออออออออออออออออป
บ FUNZIONE : NMIMON                         ณDATE:Tue  12-14-1993  22:14:30   บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤมฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ FUNZIONI CHIAMATE : prregister() - monitor() - ei() - printf()              บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ DESCRIZIONE: Stampa il contenuto dei registri di utente e lancia il         บ
บ monitor                                                                     บ
ศอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ
*/

void nmimon()
{
restrap();
prregister();
ei();
printf("\r\n%c",video_desc.prompt);
sysdesc.state=ROM;
monitor(&monline);
}
/*
ษอออออออออออออออออออออออออออออออออออออออออออัอออออออออออออออออออออออออออออออออป
บ FUNZIONE : NMINSTEP                       ณDATE: Sun  12-26-1993  11:19:26  บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤมฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ FUNZIONI CHIAMATE : prregister() - goon() - ei() - printf() - monitor()     บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ DESCRIZIONE: Esegue in single step il numero richiesto di istruzioni        บ
บ lanciando al termine il monitor                                             บ
ศอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ
*/

void nminstep()
{
restrap();
prregister();           /* Stampo valore registri user */
sysdesc.state=ROM;      /* Passo in stato system */
--stepcount;            /* Decremento counter step */
if(!stepcount){
        fixvect_t[NMI_I]=NMIMON;             /* Se Counter=0 Passo in monitor */
        ei();
        printf("\r\n%c",video_desc.prompt);
        monitor(&monline);
    }
    else{                                    /* Altrimenti eseguo una ulteriore */
        sysdesc.state=RAM;                   /* istruzione in single step mode */
        stepflg=STEPON;
        settrap();
        goon();
    }

}
/*
ษอออออออออออออออออออออออออออออออออออออออออออัอออออออออออออออออออออออออออออออออป
บ FUNZIONE : NMIBREAK                       ณDATE: Tue  12-28-1993  22:43:42  บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤมฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ FUNZIONI CHIAMATE : prregister() - goon() - ei() - printf() - monitor()     บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ DESCRIZIONE: Valuta se il break point incontrato e' valido ed in caso       บ
บ affermativo lancia il monitor                                               บ
ศอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ
*/

void nmibreak()
{
    restrap();
    fixvect_t[NMI_I]=NMIMON;
    if(evaluatetrp(&bpoint[bpnum])==TRUE){
        printf("\r\nBP NUM:%d AT %4x",bpnum,bpoint[bpnum].opadd);
        prregister();
        ei();
        printf("\r\n%c",video_desc.prompt);
        sysdesc.state=ROM;
        monitor(&monline);
    }else {
        settrap();
        goon();
    }

}
/*
ษอออออออออออออออออออออออออออออออออออออออออออัอออออออออออออออออออออออออออออออออป
บ FUNZIONE : NMITRACE                       ณDATE: Tue  12-28-1993  22:43:42  บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤมฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ FUNZIONI CHIAMATE : prregister() - goon() - ei() - printf() - monitor()     บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ DESCRIZIONE: Valuta se il trace point incontrato e' valido ed in caso       บ
บ affermativo esegue il tracing                                               บ
ศอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ
*/

void nmitrace()
{
    restrap();
    fixvect_t[NMI_I]=NMIMON;
    if(evaluatetrp(&tpoint[tpnum])==TRUE){
        printf("\r\nTP NUM:%d AT %4x",tpnum,tpoint[tpnum].opadd);
        prregister();
    }
    settrap();
    goon();
}
/*
ษอออออออออออออออออออออออออออออออออออออออออออัอออออออออออออออออออออออออออออออออป
บ FUNZIONE : RESTRAP                        ณDATE: Thu  12-30-1993  22:10:58  บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤมฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ DESCRIZIONE :                                                               บ
บ                                                                             บ
ศอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ
*/
restrap()
{
int i;
    for(i=0;i<3;++i){
        *bpoint[i].opadd=bpoint[i].opdata;
        *tpoint[i].opadd=tpoint[i].opdata;
    }
}
/*
ษอออออออออออออออออออออออออออออออออออออออออออัอออออออออออออออออออออออออออออออออป
บ FUNZIONE : SETTRAP                        ณDATE: Thu  12-30-1993  22:10:58  บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤมฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ DESCRIZIONE :                                                               บ
บ                                                                             บ
ศอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ
*/
settrap()
{
int i;
for(i=0;i<3;++i){
    tpoint[i].opdata=*bpoint[i].opadd;
    tpoint[i].opdata=*tpoint[i].opadd;
}
*bpoint[0].opadd=BP0_RST08;
*bpoint[1].opadd=BP1_RST10;
*bpoint[2].opadd=BP2_RST18;
*tpoint[0].opadd=TP0_RST20;
*tpoint[1].opadd=TP1_RST28;
*tpoint[2].opadd=TP2_RST30;
}
/*
ษอออออออออออออออออออออออออออออออออออออออออออัอออออออออออออออออออออออออออออออออป
บ FUNZIONE : RESETTRAP                      ณDATE: Thu  12-30-1993  22:10:58  บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤมฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ DESCRIZIONE :                                                               บ
บ                                                                             บ
ศอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ
*/
resettrap()
{
int i;
for(i=0;i<3;++i){
    bpoint[i].datdyn.counter=bpoint[i].datstat.counter;
    tpoint[i].datdyn.counter=tpoint[i].datstat.counter;
}
settrap();
}
/*
ษอออออออออออออออออออออออออออออออออออออออออออัอออออออออออออออออออออออออออออออออป
บ FUNZIONE :EVALUATETRP                     ณDATE:                            บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤมฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ INPUT :                                                                     บ
บ                                                                             บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ OUTPUT :                                                                    บ
บ                                                                             บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ FUNZIONI CHIAMATE :                                                         บ
บ                                                                             บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ DESCRIZIONE :                                                               บ
บ                                                                             บ
บ                                                                             บ
บ                                                                             บ
บ                                                                             บ
ศอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ
*/
evaluatetrp(trpd)
TRPDESC *trpd;
{
int ret;
unsigned int tmp;
    switch(trpd -> cond1){
        case NONE:
        ret=TRUE;                     /* break valido */
        break;
        case AFTER_I:
        if(--trpd -> datdyn.counter==0) {
            trpd -> datdyn.counter=trpd -> datstat.counter;
            ret=TRUE;
        }
        else ret= trpd -> datdyn.counter;
        break;
        case ANDREG_I:
        case ANDLOC_I:
        switch(trpd -> cond2){
            case EQINT_I:
            tmp=*trpd -> datstat.ptrint;
            break;
            case NEQINT_I:
            (*trpd -> datstat.ptrint!=trpd -> value) ? (ret=TRUE) : (ret=FALSE);
            break;
            case EQCHR_I:
            (*trpd -> datstat.ptrchr==(unsigned char)trpd -> value) ? (ret=TRUE) : (ret=FALSE);
            break;
            case NEQCHR_I:
            (*trpd -> datstat.ptrchr!=(unsigned char)trpd -> value) ? (ret=TRUE) : (ret=FALSE);
            break;
            case AF_I:
            ((unsigned char)(uframe.ureg[URGREL(AF_I)]>>8)==(unsigned char)trpd -> value) ? (ret=TRUE) : (ret=FALSE);
            break;
            case AF1_I:
            ((unsigned char)(uframe.ureg[URGREL(AF1_I)]>>8)==(unsigned char)trpd -> value) ? (ret=TRUE) : (ret=FALSE);
            break;
            default:
            (uframe.ureg[URGREL(trpd -> cond2)]==trpd -> value) ? (ret=TRUE) : (ret=FALSE);
            break;
        }
    }
    return(ret);
}
