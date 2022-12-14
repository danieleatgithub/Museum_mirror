/*
浜様様様様様様様様様様様様様様様様様様様様様冤様様様様様用様様様様様様様様様様?
? FILE:\CADASM\R10\ROM\COMMAND\DEBUG.C      ?VERS:1.1    ?TIPO: MODULO C      ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳田陳陳陳陳陳珍陳陳陳陳陳陳陳陳陳陳?
? AUTORE: Colombo Daniele                   ?DATA: Fri  12-24-1993  21:50:50  ?
麺様様様様様様様様様様様様様様様様様様様様様詫様様様様様様様様様様様様様様様様?
? INCLUDE: stdio.h -                    \cadasm\r10\rom\include\conio.h       ?
? \cadasm\r10\rom\include\io.h -        \cadasm\r10\rom\include\command.h     ?
? \cadasm\r10\rom\include\error.h                                             ?
麺様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
? FUNZIONI PUBBLICHE: go() - step()                                           ?
麺様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
? DESCRIZIONE: MODULO PER FUNZIONI DI DEBUGGING                               ?
? Creazioni di :                                                              ?
?                                                                             ?
藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
*/
#include  <stdio.h>                        
#include  "\cadasm\r10\rom\include\conio.h"
#include  "\cadasm\r10\rom\include\io.h"
#include  "\cadasm\r10\rom\include\command.h"
#include  "\cadasm\r10\rom\include\error.h"

/* --------------------- IMPORTAZIONI ------------------------*/

extern CMD com;              /* DESCRITTORE ULTIMO COMANDO   */

/* --------------------- CREAZIONI ------------------------*/

/*
浜様様様様様様様様様様様様様様様様様様様様様冤様様様様様様様様様様様様様様様様?
? FUNZIONE : GO                             ?DATE: Thu  10-28-1993  00:03:14  ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳祖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? FUNZIONI CHIAMATE : goon()                                                  ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? DESCRIZIONE : comando mml per eseguire un programma di utente               ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? SINTASSI COMANDO:                                                           ?
? GO  [Address] : Lancia in esecuzione il programma di utente a partire       ?
?       dall'indirizzo [Address] se specificato altrimenti parte              ?
?       dall'indirizzo memorizzato nel PC di utente                           ?
藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
*/

       
COMMAND(go)
{
    com.function=nullfunc;
    stepflg=STEPOFF;            /* Disattivo modalita' single step */
    resettrap();
    if(numarg>1)  uframe.ureg[URGREL(PC_I)]=com.param[1];  /* Se PC specificato lo aggiorno */
    goon();                     /* Lancio in esecuzione il programma USER */
}

/*
浜様様様様様様様様様様様様様様様様様様様様様冤様様様様様様様様様様様様様様様様?
? FUNZIONE : STEP                           ?DATE: Thu  10-28-1993  00:03:14  ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳祖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? FUNZIONI CHIAMATE : goon()                                                  ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? DESCRIZIONE : comando mml che esegue una istruzione alla volta stampando    ?
? ad ogni istruzione il valore dei registri macchina                          ?
? In modalita' step i BREAK POINT ed i TRACE POINT non sono attivi            ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? SINTASSI COMANDO:                                                           ?
? STEP  [N. iter] : Esegue una istruzione alla volta per [N. iter] volte      ?
?        il default vale 1                                                    ?
藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
*/

       
COMMAND(step)
{
 stepcount=0;
 stepflg=STEPON;       /* Setta il modo step */
    if(numarg>1&&com.param[1]>0) {      /* Se il numero di single step e' > 0 */
        stepcount=com.param[1];         /* Setto lo step counter ed eseguo il link */
        fixvect_t[NMI_I]=NMINSTEP;      /* alla routine di gestione del NMI quella di */
                                        /* gestione del single step multiplo */
    }
 goon();                                /* Lancia il programma USER con l'ultimo PC */
}
/*
浜様様様様様様様様様様様様様様様様様様様様様冤様様様様様様様様様様様様様様様様?
? FUNZIONE : BPS                            ?DATE: Tue  12-28-1993  21:10:03  ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳祖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? FUNZIONI CHIAMATE :                                                         ?
?                                                                             ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? DESCRIZIONE : comando mml che attiva un break point                         ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? SINTASSI COMANDO:                                                           ?
? BPS [Num] AT [Address.1] [Cond.1] [Address.2] [Cond.2] [Value]              ?
?    -[Num] : Numero del break point Range [0:2]                              ?
?    -[Address.1]: Indirizzo del break point Range [0:65535]                  ?
?    -[Cond.1]: Condizione numero uno se non specificata il break point e'    ?
?               incondizionato                                                ?
?               <ANDLOC> Condizionato al valore contenuto nella locazione     ?
?               specificata                                                   ?
?               <ANDREG> Condizionato al valore contenuto nel registro        ?
?               specificato                                                   ?
?               <AFTER>  Condizionato ad un numero specificato intercettazione?
?               del break point                                               ?
?    -[Address.2]: Se la condizione e:                                        ?
?               <ANDLOC> Indirizzo della locazione a cui e' condizionato      ?
?               il break point                                                ?
?               <ANDREG> Va assegnato un valore qualunqe, non significativo   ?
?               <AFTER>  Numero di intercettazioni del break point prima di   ?
?               validarlo Range [0:65535]                                     ?
?    -[Cond.2]: Tipo di dato da intercettare                                  ?
?               <EQC> Dato da intercettare su 8 bit                           ?
?               <EQI> Dato da intercettare su 16 bit                          ?
?               <Nome registro> Registro da intercettare                      ?
?               Range [HL - BC - DE - A - IX - IY]                            ?
?    -[Value]:  Valore per validare la Cond.2                                 ?
?                                                                             ?
? ESEMPI:                                                                     ?
?                                                                             ?
?  BPS 1 AT 9010                                                              ?
?  BPS 1 AT 9010 LOC 3010 EQI 12AB                                            ?
?  BPS 1 AT 9010 LOC 3010 EQC AB                                              ?
?  BPS 1 AT 9010 REG 0 HL AB12                                                ?
?  BPS 1 AT 9010 AFTER 400                                                    ?
?                                                                             ?
藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
*/
COMMAND(bpset)
{
int ret;
    com.function=nullfunc;
    ret=RTNBAD;
    if(com.param[1]<3) ret=decodetrp(numarg,&com,&bpoint[com.param[1]]);
    return(ret);
}
/*
浜様様様様様様様様様様様様様様様様様様様様様冤様様様様様様様様様様様様様様様様?
? FUNZIONE : BPD                            ?DATE: Tue  12-28-1993  21:10:03  ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳祖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? FUNZIONI CHIAMATE :                                                         ?
?                                                                             ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? DESCRIZIONE : comando mml che disattiva un break point                      ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? SINTASSI COMANDO:                                                           ?
? BPD [Num]                                                                   ?
?    -[Num] : Numero del break point Range [0:2]                              ?
?                                                                             ?
藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
*/
COMMAND(bpdel)
{
    com.function=nullfunc;
    flushtrp(&bpoint[com.param[1]]);
    return(TRUE);
}
/*
浜様様様様様様様様様様様様様様様様様様様様様冤様様様様様様様様様様様様様様様様?
? FUNZIONE : BPPRINT                        ?DATE: Tue  12-28-1993  21:10:03  ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳祖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? FUNZIONI CHIAMATE :                                                         ?
?                                                                             ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? DESCRIZIONE : comando mml che visualizza tutti i break point                ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? SINTASSI COMANDO:                                                           ?
? BP                                                                          ?
?                                                                             ?
藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
*/
COMMAND(bpprint)
{
int i;
    com.function=nullfunc;
    for(i=0;i<3;++i) prtrp(BREAK_I,i,&bpoint[i]);
    return(TRUE);
}
/*
浜様様様様様様様様様様様様様様様様様様様様様冤様様様様様様様様様様様様様様様様?
? FUNZIONE : TPSET                          ?DATE: Tue  12-28-1993  21:10:03  ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳祖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? FUNZIONI CHIAMATE :                                                         ?
?                                                                             ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? DESCRIZIONE : comando mml che attiva un break point                         ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? SINTASSI COMANDO:                                                           ?
? TPS [Num] AT [Address.1] [Cond.1] [Address.2] [Cond.2] [Value]              ?
?    -[Num] : Numero del trace point Range [0:2]                              ?
?    -[Address.1]: Indirizzo del trace point Range [0:65535]                  ?
?    -[Cond.1]: Condizione numero uno se non specificata il trace point e'    ?
?               incondizionato                                                ?
?               <ANDLOC> Condizionato al valore contenuto nella locazione     ?
?               specificata                                                   ?
?               <ANDREG> Condizionato al valore contenuto nel registro        ?
?               specificato                                                   ?
?               <AFTER>  Condizionato ad un numero specificato intercettazione?
?               del trace point                                               ?
?    -[Address.2]: Se la condizione e:                                        ?
?               <ANDLOC> Indirizzo della locazione a cui e' condizionato      ?
?               il trace point                                                ?
?               <ANDREG> Va assegnato un valore qualunqe, non significativo   ?
?               <AFTER>  Numero di intercettazioni del trace point prima di   ?
?               validarlo Range [0:65535]                                     ?
?    -[Cond.2]: Tipo di dato da intercettare                                  ?
?               <EQC> Dato da intercettare su 8 bit                           ?
?               <EQI> Dato da intercettare su 16 bit                          ?
?               <Nome registro> Registro da intercettare                      ?
?               Range [HL - BC - DE - A - IX - IY]                            ?
?    -[Value]:  Valore per validare la Cond.2                                 ?
?                                                                             ?
? ESEMPI:                                                                     ?
?                                                                             ?
?  TPS 1 AT 9010                                                              ?
?  TPS 1 AT 9010 LOC 3010 EQI 12AB                                            ?
?  TPS 1 AT 9010 LOC 3010 EQC AB                                              ?
?  TPS 1 AT 9010 REG 0 HL AB12                                                ?
?  TPS 1 AT 9010 AFTER 400                                                    ?
?                                                                             ?
藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
*/
COMMAND(tpset)
{
int ret;
    com.function=nullfunc;
    ret=RTNBAD;
    if(com.param[1]<3) ret=decodetrp(numarg,&com,&tpoint[com.param[1]]);
    return(ret);
}
/*
浜様様様様様様様様様様様様様様様様様様様様様冤様様様様様様様様様様様様様様様様?
? FUNZIONE : TPD                            ?DATE: Tue  12-28-1993  21:10:03  ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳祖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? FUNZIONI CHIAMATE :                                                         ?
?                                                                             ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? DESCRIZIONE : comando mml che disattiva un trace point                      ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? SINTASSI COMANDO:                                                           ?
? TPD [Num]                                                                   ?
?    -[Num] : Numero del trace point Range [0:2]                              ?
?                                                                             ?
藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
*/
COMMAND(tpdel)
{
    com.function=nullfunc;
    flushtrp(&tpoint[com.param[1]]);
    return(TRUE);
}
/*
浜様様様様様様様様様様様様様様様様様様様様様冤様様様様様様様様様様様様様様様様?
? FUNZIONE : TPPRINT                        ?DATE: Tue  12-28-1993  21:10:03  ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳祖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? FUNZIONI CHIAMATE :                                                         ?
?                                                                             ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? DESCRIZIONE : comando mml che visualizza tutti i trace point                ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? SINTASSI COMANDO:                                                           ?
? TP                                                                          ?
?                                                                             ?
藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
*/
COMMAND(tpprint)
{
int i;
    com.function=nullfunc;
    for(i=0;i<3;++i) prtrp(TRACE_I,i,&tpoint[i]);
    return(TRUE);
}
/*
浜様様様様様様様様様様様様様様様様様様様様様冤様様様様様様様様様様様様様様様様?
? FUNZIONE : ANALYSECOND                    ?DATE:                            ?
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
analaysecond(lnarg,comdesc,trpd)
int     lnarg;
CMD     *comdesc;
TRPDESC *trpd;
{
int ret;
    ret=TRUE;
    if(lnarg>4){
        trpd -> cond1=whichword((char *)comdesc -> param[4],UPPER);
        switch(trpd -> cond1){
            case ANDREG_I:
            case ANDLOC_I:
            ret=analaysecond2(lnarg,comdesc,trpd);
            break;
            case AFTER_I:
            trpd -> datstat.counter=comdesc -> param[5];
            ret=AFTER_I;
            break;
            default:
            ret=RTNBAD;
            break;
        }
    }
    return(ret);
}
/*
浜様様様様様様様様様様様様様様様様様様様様様冤様様様様様様様様様様様様様様様様?
? FUNZIONE : ANALYSECOND2                   ?DATE:                            ?
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
analaysecond2(lnarg,comdesc,trpd)
int     lnarg;
CMD     *comdesc;
TRPDESC *trpd;
{
int ret;
    ret=RTNBAD;
    if(lnarg>6){
        trpd -> cond2=whichword((char *)comdesc -> param[6],UPPER);
        ret=trpd -> cond2;
        switch(trpd -> cond2){
            case EQINT_I:
            case NEQINT_I:
            trpd -> datstat.ptrint=(int *)comdesc -> param[6];
            break;
            case EQCHR_I:
            case NEQCHR_I:
            trpd -> datstat.ptrchr=(unsigned char *)comdesc -> param[6];
            break;
            default:
            if(trpd -> cond2<AF_I||trpd -> cond2>IY_I) ret=RTNBAD;
            break;
        }
        trpd -> value=comdesc -> param[7];
    }
    return(ret);
}
/*
浜様様様様様様様様様様様様様様様様様様様様様冤様様様様様様様様様様様様様様様様?
? FUNZIONE : FLUSHTRP                       ?DATE:                            ?
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
flushtrp(trpd)
TRPDESC *trpd;
{
    memclr((char *)trpd,sizeof(TRPDESC));
}
/*
浜様様様様様様様様様様様様様様様様様様様様様冤様様様様様様様様様様様様様様様様?
? FUNZIONE : PRTRP                          ?DATE:                            ?
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
prtrp(trp,trpnum,trpd)
int trp;
int trpnum;
TRPDESC *trpd;
{
    printf("\r\n");
    if(trp==BREAK_I) outmessage(BREAK_I);
    else outmessage(TRACE_I);
    printf(" N%d ",trpnum);
    if(trpd -> opadd) {
        printf("%04x ",trpd -> opadd);
        switch(trpd -> cond1){
            case NONE:
            break;
            case AFTER_I:
            outmessage(AFTER_I);
            printf(" %u NOW IS %u ",trpd -> datstat.counter,trpd -> datdyn.counter);
            break;
            default:
            outmessage(trpd -> cond1);
            if(trpd -> datstat.ptrint)  printf(" %04x ",trpd -> datstat.ptrint);
            else putchar(' ');
            outmessage(trpd -> cond2);
            printf(" %x",trpd -> value);
            break;
        }
    }else printf("NOT ACT");
}

/*
浜様様様様様様様様様様様様様様様様様様様様様冤様様様様様様様様様様様様様様様様?
? FUNZIONE :DECODETRP                       ?DATE:                            ?
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
decodetrp(lnarg,comdesc,trpd)
int     lnarg;
CMD     *comdesc;
TRPDESC *trpd;
{
int ret,i;
unsigned char *tmp;
    ret=TRUE;
    com.function=nullfunc;
    tmp=(unsigned char *)comdesc -> param[3];
    for(i=0;i<3;++i){
        if ( tmp == bpoint[i].opadd || tmp == tpoint[i].opadd ) ret=RTNBAD;
    }
    if (ret == TRUE) {
        trpd -> opadd=tmp;
        ret=analaysecond(lnarg,comdesc,trpd);
    }
    if(ret==RTNBAD){
        flushtrp(trpd);
    }
    return(ret);
}

