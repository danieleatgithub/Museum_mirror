/*
浜様様様様様様様様様様様様様様様様様様様様様冤様様様様様用様様様様様様様様様様?
? FILE:\CADASM\R10\ROM\COMMAND\MIX.C        ?VERS:1.1    ?TIPO: MODULO C      ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳田陳陳陳陳陳珍陳陳陳陳陳陳陳陳陳陳?
? AUTORE: Colombo Daniele                   ?DATA: Thu  10-28-1993  00:02:04  ?
麺様様様様様様様様様様様様様様様様様様様様様詫様様様様様様様様様様様様様様様様?
? INCLUDE: stdio.h - math.h - string.h - \cadasm\r10\rom\include\conio.h      ?
? \cadasm\r10\rom\include\io.h - \cadasm\r10\rom\include\command.h            ?
? \cadasm\r10\rom\include\error.h                                             ?
麺様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
? FUNZIONI PUBBLICHE: fill() - setport() - reg()                              ?
麺様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
? DESCRIZIONE: MODULO PER COMANDI VARI                                        ?
? FILL - SETPORT - REG                                                        ?
? Creazioni di :                                                              ?
?                                                                             ?
藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
*/
#include  <stdio.h>                        
#include  <math.h>
#include  <string.h>
#include  "\cadasm\r10\rom\include\conio.h"
#include  "\cadasm\r10\rom\include\io.h"
#include  "\cadasm\r10\rom\include\command.h"
#include  "\cadasm\r10\rom\include\error.h"

/* --------------------- IMPORTAZIONI ------------------------*/
extern CMD com;              /* DESCRITTORE ULTIMO COMANDO   */

extern char *version;
/* --------------------- CREAZIONI ------------------------*/

/*
浜様様様様様様様様様様様様様様様様様様様様様冤様様様様様様様様様様様様様様様様?
? FUNZIONE : FILL                           ?DATE: Thu  10-28-1993  00:03:14  ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳祖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? FUNZIONI CHIAMATE : memset()                                                ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? DESCRIZIONE : comando mml per riempire una zona di memoria                  ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? SINTASSI COMANDO:                                                           ?
? FILL  [address] [nbyte] [byte]: Riempie [nbyte] locazioni a partire da      ?
?         [address] con [byte] (se [byte] non specificato default=00          ?
藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
*/

       
COMMAND(filmem)
{
unsigned char byte;
byte=0;
if(numarg==4) byte=(char)com.param[3];
memset((unsigned char *)com.param[1],byte,com.param[2]);
return(TRUE);
}
/*
浜様様様様様様様様様様様様様様様様様様様様様冤様様様様様様様様様様様様様様様様?
? FUNZIONE : SETPORT                        ?DATE: Thu  10-28-1993  08:37:59  ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳祖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? FUNZIONI CHIAMATE : strupr() - atoi() - printf() - siobinit() - prsiobstat()?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? DESCRIZIONE : comando mml per modifica e visualizazzione settaggio porte I/O?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? SINTASSI COMANDO:                                                           ?
? SETPORT [Port N.] [act] [byte] [byte] [byte] ..: In riferimento alla porta  ?
? SETPORT [Port N.] Visualizza i parametri della porta attivi                 ?
? SETPORT [0] [SPEED] [PARITY] [BIT/CHAR] [STOP BIT]                          ?
?     Range:  [SPEED] 300-600] [BIT/CHAR] [STOP BIT]                          ?
藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
*/
COMMAND(setport)
{
SERTAB  *setsert;
int i,tmp,offtab;
switch(com.param[1]){
    case 0:
        if (numarg>2){
            setsert=siotab;
            strupr((char *)com.param[3]);
            tmp=serset_b.speedvalue;
            i=atoi((char *)com.param[2]);
            serset_b.speedvalue=i;
            switch(i){
                case 300:
                case 600:
                    serset_b.speed=(i/300-1);
                    break;
                case 1200:
                    serset_b.speed=2;
                    break;
                case 2400:
                    serset_b.speed=3;
                    break;
                case 4800:
                    serset_b.speed=4;
                    break;
                default:
                    serset_b.speedvalue=tmp;
                    printf("\r\nSPEED %s\r\n",error);
                    break;
                }
            switch(*(char *)com.param[3]){
                case 'O':
                    serset_b.parity=0;
                    break;
                case 'E':
                    serset_b.parity=1;
                    break;
                case 'N':
                    serset_b.parity=2;
                    break;
                }
            i=com.param[4];
            if (i>0 && i<9) serset_b.bitchr=i/8;
            i=com.param[5];
            if (i>0 && i<2) serset_b.bitstop=--i;
            if (serset_b.bitchr){
                offtab=serset_b.speed*8+6+serset_b.bitstop;
            }
            else
            {
                offtab=serset_b.speed*8+serset_b.parity*2+serset_b.bitstop;
            }
            offtab=((unsigned int)siotab+offtab*sizeof(SERTAB));
            setsert=(SERTAB *)offtab;
            siobinit(setsert);
        }
        prsiobstat(&serset_b);
        break;

    default:
        printf("PORTA NON CONFIGURATA\r\n");
        com.function=nullfunc;
        break;
    }
return(TRUE);
}
/*
浜様様様様様様様様様様様様様様様様様様様様様冤様様様様様様様様様様様様様様様様?
? FUNZIONE : REG                            ?DATE: Thu  10-28-1993  00:03:14  ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳祖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? FUNZIONI CHIAMATE :                                                         ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? DESCRIZIONE : comando mml per leggere e scrivere i registri user            ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? SINTASSI COMANDO:                                                           ?
? REG   [Register] [Value] : Se non e' specificato nessun parametro stampa    ?
?       il contenuto dei registri user altrimenti assegna al registro         ?
?       [Register] il dato [Value]                                            ?
藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
*/

       
COMMAND(reg)
{
int i,ret;
unsigned int *tmp;

    com.function=nullfunc;
    if(numarg==1){
        prregister();
    }
    else{
        i=whichword((char *)com.param[1],UPPER);
        ret=i;
        if(i>=PC_I&&i<=IY_I) uframe.ureg[URGREL(i)]=com.param[2];
        else switch(i){
            case IREG_I:
            uframe.uregif1=(unsigned char)com.param[2];
            break;
            case IF_I:
            uframe.uregif2=(unsigned char)com.param[2];
            break;
            default:
            SYNERR;
            ret=RTNBAD;
            break;
        }
    }
    return(ret);
}
/*
浜様様様様様様様様様様様様様様様様様様様様様冤様様様様様様様様様様様様様様様様?
? FUNZIONE : VERS                           ?DATE: Mon  12-27-1993  08:45:38  ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳祖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? FUNZIONI CHIAMATE :  printf()                                               ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? DESCRIZIONE : comando mml per leggere la data di generazione                ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? SINTASSI COMANDO:                                                           ?
? VERS                                                                        ?
藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
*/

       
COMMAND(vers)
{
printf("\r\n%s",(char *)&version);
com.function=nullfunc;
return(TRUE);
}
/*
浜様様様様様様様様様様様様様様様様様様様様様冤様様様様様様様様様様様様様様様様?
? FUNZIONE : PRSIOBSTAT                     ?DATE: Thu  10-28-1993  10:51:01  ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳祖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? INPUT : Puntatore a descrittore porta tipo SERSET                           ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? OUTPUT : Nessuno                                                            ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? FUNZIONI CHIAMATE : printf()                                                ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? DESCRIZIONE : Stampa il settaggio attuale della porta seriale 0             ?
?               (SIO porta B)                                                 ?
藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
*/
prsiobstat(prserset)
SERSET  *prserset;
{
printf("\r\nSPEED:%d PARITY:%s",prserset -> speedvalue,parvalue[prserset -> parity]);
printf(" BIT:%d STOP:%d\r\n",prserset -> bitchr+7, prserset -> bitstop+1);
}

/*
浜様様様様様様様様様様様様様様様様様様様様様冤様様様様様様様様様様様様様様様様?
? FUNZIONE : PRREGISTER                     ?DATE: Mon  12-27-1993  09:53:45  ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳祖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? INPUT : Nessuno                                                             ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? OUTPUT : Nessuno                                                            ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? FUNZIONI CHIAMATE :  printf() - prflagreg()                                 ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? DESCRIZIONE :  Stampa i valori dei registri macchina di utente              ?
藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
*/

prregister()
{
    printf("\r\n");
    if(sysdesc.state==ROM) printf("SYS");
    else printf("USR");
    printf(" PC=%04x SP=%04x",uframe.ureg[URGREL(PC_I)],uframe.ureg[URGREL(SP_I)]);
    printf(" I=%02x IFF=%1x\n\r",uframe.uregif1,uframe.uregif2);
    printf("IX =%04x IY =%04x\r\n",uframe.ureg[URGREL(IX_I)],uframe.ureg[URGREL(IY_I)]);
    prflagreg((unsigned char)uframe.ureg[URGREL(AF_I)]);
    printf("AF=%02x ",(unsigned char)(uframe.ureg[URGREL(AF_I)]>>8));
    printf("BC=%04x DE=%04x",uframe.ureg[URGREL(BC_I)],uframe.ureg[URGREL(DE_I)]);
    printf(" HL=%04x\r\n",uframe.ureg[URGREL(HL_I)]);
    printf("________ALT SET REG_____\r\n");
    prflagreg((unsigned char)uframe.ureg[URGREL(AF1_I)]);
    printf("AF=%02x ",(unsigned char)(uframe.ureg[URGREL(AF1_I)]>>8));
    printf("BC=%04x DE=%04x",uframe.ureg[URGREL(BC1_I)],uframe.ureg[URGREL(DE1_I)]);
    printf(" HL=%04x\r\n",uframe.ureg[URGREL(HL1_I)]);
}
/*
浜様様様様様様様様様様様様様様様様様様様様様冤様様様様様様様様様様様様様様様様?
? FUNZIONE : PRFLAGREG                      ?DATE: Tue  12-28-1993  21:05:38  ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳祖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? INPUT : Registro F in un byte unsigned                                      ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? OUTPUT : Nessuno                                                            ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? FUNZIONI CHIAMATE :  printf()                                               ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? DESCRIZIONE :  Stampa lo stato dei flag del processore                      ?
藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
*/
prflagreg(tmp)
unsigned char tmp;
{
    printf("S=%1x Z=%1x H=%1x P/V=%1x N=%1x C=%1x\n\r",((tmp&0x80)!=0),((tmp&0x40)!=0),
        ((tmp&0x10)!=0),((tmp&0x04)!=0),((tmp&0x02)!=0),((tmp&0x01)!=0));
}
