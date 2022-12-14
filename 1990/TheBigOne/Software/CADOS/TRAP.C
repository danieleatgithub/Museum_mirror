/*
浜様様様様様様様様様様様様様様様様様様様様様冤様様様様様用様様様様様様様様様様?
? FILE:\CADASM\R10\ROM\CADOS\TRAP.C         ?VERS:1.1    ?TIPO:MODULO C       ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳田陳陳陳陳陳珍陳陳陳陳陳陳陳陳陳陳?
? AUTORE: Colombo Daniele                   ?DATA: Sun  09-12-1993  12:34:29  ?
麺様様様様様様様様様様様様様様様様様様様様様詫様様様様様様様様様様様様様様様様?
? INCLUDE: stdio.h - stdlib.h         -     \cadasm\r10\rom\include\conio.h   ?
? \cadasm\r10\rom\include\command.h         \cadasm\r10\rom\include\io.h      ?
? \cadasm\r10\rom\include\error.h                                             ?
麺様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
? FUNZIONI PUBBLICHE: nmimon() - nminstep()                                   ?
麺様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
? DESCRIZIONE: GESTIONE ECCEZIONI                                             ?
? Creazioni:                                                                  ?
?   -                                                                         ?
藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
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
浜様様様様様様様様様様様様様様様様様様様様様冤様様様様様様様様様様様様様様様様?
? FUNZIONE : NMIMON                         ?DATE:Tue  12-14-1993  22:14:30   ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳祖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? FUNZIONI CHIAMATE : prregister() - monitor() - ei() - printf()              ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? DESCRIZIONE: Stampa il contenuto dei registri di utente e lancia il         ?
? monitor                                                                     ?
藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
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
浜様様様様様様様様様様様様様様様様様様様様様冤様様様様様様様様様様様様様様様様?
? FUNZIONE : NMINSTEP                       ?DATE: Sun  12-26-1993  11:19:26  ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳祖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? FUNZIONI CHIAMATE : prregister() - goon() - ei() - printf() - monitor()     ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? DESCRIZIONE: Esegue in single step il numero richiesto di istruzioni        ?
? lanciando al termine il monitor                                             ?
藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
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
浜様様様様様様様様様様様様様様様様様様様様様冤様様様様様様様様様様様様様様様様?
? FUNZIONE : NMIBREAK                       ?DATE: Tue  12-28-1993  22:43:42  ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳祖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? FUNZIONI CHIAMATE : prregister() - goon() - ei() - printf() - monitor()     ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? DESCRIZIONE: Valuta se il break point incontrato e' valido ed in caso       ?
? affermativo lancia il monitor                                               ?
藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
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
浜様様様様様様様様様様様様様様様様様様様様様冤様様様様様様様様様様様様様様様様?
? FUNZIONE : NMITRACE                       ?DATE: Tue  12-28-1993  22:43:42  ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳祖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? FUNZIONI CHIAMATE : prregister() - goon() - ei() - printf() - monitor()     ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? DESCRIZIONE: Valuta se il trace point incontrato e' valido ed in caso       ?
? affermativo esegue il tracing                                               ?
藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
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
浜様様様様様様様様様様様様様様様様様様様様様冤様様様様様様様様様様様様様様様様?
? FUNZIONE : RESTRAP                        ?DATE: Thu  12-30-1993  22:10:58  ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳祖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? DESCRIZIONE :                                                               ?
?                                                                             ?
藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
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
浜様様様様様様様様様様様様様様様様様様様様様冤様様様様様様様様様様様様様様様様?
? FUNZIONE : SETTRAP                        ?DATE: Thu  12-30-1993  22:10:58  ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳祖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? DESCRIZIONE :                                                               ?
?                                                                             ?
藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
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
浜様様様様様様様様様様様様様様様様様様様様様冤様様様様様様様様様様様様様様様様?
? FUNZIONE : RESETTRAP                      ?DATE: Thu  12-30-1993  22:10:58  ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳祖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? DESCRIZIONE :                                                               ?
?                                                                             ?
藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
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
浜様様様様様様様様様様様様様様様様様様様様様冤様様様様様様様様様様様様様様様様?
? FUNZIONE :EVALUATETRP                     ?DATE:                            ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳祖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? INPUT :                                                                     ?
?                                                                             ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? OUTPUT :                                                                    ?
?                                                                             ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? FUNZIONI CHIAMATE :                                                         ?
?                                                                             ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? DESCRIZIONE :                                                               ?
?                                                                             ?
?                                                                             ?
?                                                                             ?
?                                                                             ?
藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
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