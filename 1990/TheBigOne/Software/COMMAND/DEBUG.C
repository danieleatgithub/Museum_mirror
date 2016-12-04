/*
ษอออออออออออออออออออออออออออออออออออออออออออัออออออออออออัออออออออออออออออออออป
บ FILE:\CADASM\R10\ROM\COMMAND\DEBUG.C      ณVERS:1.1    ณTIPO: MODULO C      บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤลฤฤฤฤฤฤฤฤฤฤฤฤมฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ AUTORE: Colombo Daniele                   ณDATA: Fri  12-24-1993  21:50:50  บ
ฬอออออออออออออออออออออออออออออออออออออออออออฯอออออออออออออออออออออออออออออออออน
บ INCLUDE: stdio.h -                    \cadasm\r10\rom\include\conio.h       บ
บ \cadasm\r10\rom\include\io.h -        \cadasm\r10\rom\include\command.h     บ
บ \cadasm\r10\rom\include\error.h                                             บ
ฬอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออน
บ FUNZIONI PUBBLICHE: go() - step()                                           บ
ฬอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออน
บ DESCRIZIONE: MODULO PER FUNZIONI DI DEBUGGING                               บ
บ Creazioni di :                                                              บ
บ                                                                             บ
ศอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ
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
ษอออออออออออออออออออออออออออออออออออออออออออัอออออออออออออออออออออออออออออออออป
บ FUNZIONE : GO                             ณDATE: Thu  10-28-1993  00:03:14  บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤมฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ FUNZIONI CHIAMATE : goon()                                                  บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ DESCRIZIONE : comando mml per eseguire un programma di utente               บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ SINTASSI COMANDO:                                                           บ
บ GO  [Address] : Lancia in esecuzione il programma di utente a partire       บ
บ       dall'indirizzo [Address] se specificato altrimenti parte              บ
บ       dall'indirizzo memorizzato nel PC di utente                           บ
ศอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ
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
ษอออออออออออออออออออออออออออออออออออออออออออัอออออออออออออออออออออออออออออออออป
บ FUNZIONE : STEP                           ณDATE: Thu  10-28-1993  00:03:14  บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤมฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ FUNZIONI CHIAMATE : goon()                                                  บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ DESCRIZIONE : comando mml che esegue una istruzione alla volta stampando    บ
บ ad ogni istruzione il valore dei registri macchina                          บ
บ In modalita' step i BREAK POINT ed i TRACE POINT non sono attivi            บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ SINTASSI COMANDO:                                                           บ
บ STEP  [N. iter] : Esegue una istruzione alla volta per [N. iter] volte      บ
บ        il default vale 1                                                    บ
ศอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ
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
ษอออออออออออออออออออออออออออออออออออออออออออัอออออออออออออออออออออออออออออออออป
บ FUNZIONE : BPS                            ณDATE: Tue  12-28-1993  21:10:03  บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤมฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ FUNZIONI CHIAMATE :                                                         บ
บ                                                                             บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ DESCRIZIONE : comando mml che attiva un break point                         บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ SINTASSI COMANDO:                                                           บ
บ BPS [Num] AT [Address.1] [Cond.1] [Address.2] [Cond.2] [Value]              บ
บ    -[Num] : Numero del break point Range [0:2]                              บ
บ    -[Address.1]: Indirizzo del break point Range [0:65535]                  บ
บ    -[Cond.1]: Condizione numero uno se non specificata il break point e'    บ
บ               incondizionato                                                บ
บ               <ANDLOC> Condizionato al valore contenuto nella locazione     บ
บ               specificata                                                   บ
บ               <ANDREG> Condizionato al valore contenuto nel registro        บ
บ               specificato                                                   บ
บ               <AFTER>  Condizionato ad un numero specificato intercettazioneบ
บ               del break point                                               บ
บ    -[Address.2]: Se la condizione e:                                        บ
บ               <ANDLOC> Indirizzo della locazione a cui e' condizionato      บ
บ               il break point                                                บ
บ               <ANDREG> Va assegnato un valore qualunqe, non significativo   บ
บ               <AFTER>  Numero di intercettazioni del break point prima di   บ
บ               validarlo Range [0:65535]                                     บ
บ    -[Cond.2]: Tipo di dato da intercettare                                  บ
บ               <EQC> Dato da intercettare su 8 bit                           บ
บ               <EQI> Dato da intercettare su 16 bit                          บ
บ               <Nome registro> Registro da intercettare                      บ
บ               Range [HL - BC - DE - A - IX - IY]                            บ
บ    -[Value]:  Valore per validare la Cond.2                                 บ
บ                                                                             บ
บ ESEMPI:                                                                     บ
บ                                                                             บ
บ  BPS 1 AT 9010                                                              บ
บ  BPS 1 AT 9010 LOC 3010 EQI 12AB                                            บ
บ  BPS 1 AT 9010 LOC 3010 EQC AB                                              บ
บ  BPS 1 AT 9010 REG 0 HL AB12                                                บ
บ  BPS 1 AT 9010 AFTER 400                                                    บ
บ                                                                             บ
ศอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ
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
ษอออออออออออออออออออออออออออออออออออออออออออัอออออออออออออออออออออออออออออออออป
บ FUNZIONE : BPD                            ณDATE: Tue  12-28-1993  21:10:03  บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤมฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ FUNZIONI CHIAMATE :                                                         บ
บ                                                                             บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ DESCRIZIONE : comando mml che disattiva un break point                      บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ SINTASSI COMANDO:                                                           บ
บ BPD [Num]                                                                   บ
บ    -[Num] : Numero del break point Range [0:2]                              บ
บ                                                                             บ
ศอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ
*/
COMMAND(bpdel)
{
    com.function=nullfunc;
    flushtrp(&bpoint[com.param[1]]);
    return(TRUE);
}
/*
ษอออออออออออออออออออออออออออออออออออออออออออัอออออออออออออออออออออออออออออออออป
บ FUNZIONE : BPPRINT                        ณDATE: Tue  12-28-1993  21:10:03  บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤมฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ FUNZIONI CHIAMATE :                                                         บ
บ                                                                             บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ DESCRIZIONE : comando mml che visualizza tutti i break point                บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ SINTASSI COMANDO:                                                           บ
บ BP                                                                          บ
บ                                                                             บ
ศอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ
*/
COMMAND(bpprint)
{
int i;
    com.function=nullfunc;
    for(i=0;i<3;++i) prtrp(BREAK_I,i,&bpoint[i]);
    return(TRUE);
}
/*
ษอออออออออออออออออออออออออออออออออออออออออออัอออออออออออออออออออออออออออออออออป
บ FUNZIONE : TPSET                          ณDATE: Tue  12-28-1993  21:10:03  บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤมฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ FUNZIONI CHIAMATE :                                                         บ
บ                                                                             บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ DESCRIZIONE : comando mml che attiva un break point                         บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ SINTASSI COMANDO:                                                           บ
บ TPS [Num] AT [Address.1] [Cond.1] [Address.2] [Cond.2] [Value]              บ
บ    -[Num] : Numero del trace point Range [0:2]                              บ
บ    -[Address.1]: Indirizzo del trace point Range [0:65535]                  บ
บ    -[Cond.1]: Condizione numero uno se non specificata il trace point e'    บ
บ               incondizionato                                                บ
บ               <ANDLOC> Condizionato al valore contenuto nella locazione     บ
บ               specificata                                                   บ
บ               <ANDREG> Condizionato al valore contenuto nel registro        บ
บ               specificato                                                   บ
บ               <AFTER>  Condizionato ad un numero specificato intercettazioneบ
บ               del trace point                                               บ
บ    -[Address.2]: Se la condizione e:                                        บ
บ               <ANDLOC> Indirizzo della locazione a cui e' condizionato      บ
บ               il trace point                                                บ
บ               <ANDREG> Va assegnato un valore qualunqe, non significativo   บ
บ               <AFTER>  Numero di intercettazioni del trace point prima di   บ
บ               validarlo Range [0:65535]                                     บ
บ    -[Cond.2]: Tipo di dato da intercettare                                  บ
บ               <EQC> Dato da intercettare su 8 bit                           บ
บ               <EQI> Dato da intercettare su 16 bit                          บ
บ               <Nome registro> Registro da intercettare                      บ
บ               Range [HL - BC - DE - A - IX - IY]                            บ
บ    -[Value]:  Valore per validare la Cond.2                                 บ
บ                                                                             บ
บ ESEMPI:                                                                     บ
บ                                                                             บ
บ  TPS 1 AT 9010                                                              บ
บ  TPS 1 AT 9010 LOC 3010 EQI 12AB                                            บ
บ  TPS 1 AT 9010 LOC 3010 EQC AB                                              บ
บ  TPS 1 AT 9010 REG 0 HL AB12                                                บ
บ  TPS 1 AT 9010 AFTER 400                                                    บ
บ                                                                             บ
ศอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ
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
ษอออออออออออออออออออออออออออออออออออออออออออัอออออออออออออออออออออออออออออออออป
บ FUNZIONE : TPD                            ณDATE: Tue  12-28-1993  21:10:03  บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤมฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ FUNZIONI CHIAMATE :                                                         บ
บ                                                                             บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ DESCRIZIONE : comando mml che disattiva un trace point                      บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ SINTASSI COMANDO:                                                           บ
บ TPD [Num]                                                                   บ
บ    -[Num] : Numero del trace point Range [0:2]                              บ
บ                                                                             บ
ศอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ
*/
COMMAND(tpdel)
{
    com.function=nullfunc;
    flushtrp(&tpoint[com.param[1]]);
    return(TRUE);
}
/*
ษอออออออออออออออออออออออออออออออออออออออออออัอออออออออออออออออออออออออออออออออป
บ FUNZIONE : TPPRINT                        ณDATE: Tue  12-28-1993  21:10:03  บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤมฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ FUNZIONI CHIAMATE :                                                         บ
บ                                                                             บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ DESCRIZIONE : comando mml che visualizza tutti i trace point                บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ SINTASSI COMANDO:                                                           บ
บ TP                                                                          บ
บ                                                                             บ
ศอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ
*/
COMMAND(tpprint)
{
int i;
    com.function=nullfunc;
    for(i=0;i<3;++i) prtrp(TRACE_I,i,&tpoint[i]);
    return(TRUE);
}
/*
ษอออออออออออออออออออออออออออออออออออออออออออัอออออออออออออออออออออออออออออออออป
บ FUNZIONE : ANALYSECOND                    ณDATE:                            บ
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
ษอออออออออออออออออออออออออออออออออออออออออออัอออออออออออออออออออออออออออออออออป
บ FUNZIONE : ANALYSECOND2                   ณDATE:                            บ
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
ษอออออออออออออออออออออออออออออออออออออออออออัอออออออออออออออออออออออออออออออออป
บ FUNZIONE : FLUSHTRP                       ณDATE:                            บ
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
flushtrp(trpd)
TRPDESC *trpd;
{
    memclr((char *)trpd,sizeof(TRPDESC));
}
/*
ษอออออออออออออออออออออออออออออออออออออออออออัอออออออออออออออออออออออออออออออออป
บ FUNZIONE : PRTRP                          ณDATE:                            บ
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
ษอออออออออออออออออออออออออออออออออออออออออออัอออออออออออออออออออออออออออออออออป
บ FUNZIONE :DECODETRP                       ณDATE:                            บ
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