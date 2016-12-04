/*
�����������������������������������������������������������������������������ͻ
� FILE:\CADASM\R10\ROM\COMMAND\MIX.C        �VERS:1.1    �TIPO: MODULO C      �
�����������������������������������������������������������������������������Ķ
� AUTORE: Colombo Daniele                   �DATA: Thu  10-28-1993  00:02:04  �
�����������������������������������������������������������������������������͹
� INCLUDE: stdio.h - math.h - string.h - \cadasm\r10\rom\include\conio.h      �
� \cadasm\r10\rom\include\io.h - \cadasm\r10\rom\include\command.h            �
� \cadasm\r10\rom\include\error.h                                             �
�����������������������������������������������������������������������������͹
� FUNZIONI PUBBLICHE: fill() - setport() - reg()                              �
�����������������������������������������������������������������������������͹
� DESCRIZIONE: MODULO PER COMANDI VARI                                        �
� FILL - SETPORT - REG                                                        �
� Creazioni di :                                                              �
�                                                                             �
�����������������������������������������������������������������������������ͼ
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
�����������������������������������������������������������������������������ͻ
� FUNZIONE : FILL                           �DATE: Thu  10-28-1993  00:03:14  �
�����������������������������������������������������������������������������Ķ
� FUNZIONI CHIAMATE : memset()                                                �
�����������������������������������������������������������������������������Ķ
� DESCRIZIONE : comando mml per riempire una zona di memoria                  �
�����������������������������������������������������������������������������Ķ
� SINTASSI COMANDO:                                                           �
� FILL  [address] [nbyte] [byte]: Riempie [nbyte] locazioni a partire da      �
�         [address] con [byte] (se [byte] non specificato default=00          �
�����������������������������������������������������������������������������ͼ
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
�����������������������������������������������������������������������������ͻ
� FUNZIONE : SETPORT                        �DATE: Thu  10-28-1993  08:37:59  �
�����������������������������������������������������������������������������Ķ
� FUNZIONI CHIAMATE : strupr() - atoi() - printf() - siobinit() - prsiobstat()�
�����������������������������������������������������������������������������Ķ
� DESCRIZIONE : comando mml per modifica e visualizazzione settaggio porte I/O�
�����������������������������������������������������������������������������Ķ
� SINTASSI COMANDO:                                                           �
� SETPORT [Port N.] [act] [byte] [byte] [byte] ..: In riferimento alla porta  �
� SETPORT [Port N.] Visualizza i parametri della porta attivi                 �
� SETPORT [0] [SPEED] [PARITY] [BIT/CHAR] [STOP BIT]                          �
�     Range:  [SPEED] 300-600] [BIT/CHAR] [STOP BIT]                          �
�����������������������������������������������������������������������������ͼ
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
�����������������������������������������������������������������������������ͻ
� FUNZIONE : REG                            �DATE: Thu  10-28-1993  00:03:14  �
�����������������������������������������������������������������������������Ķ
� FUNZIONI CHIAMATE :                                                         �
�����������������������������������������������������������������������������Ķ
� DESCRIZIONE : comando mml per leggere e scrivere i registri user            �
�����������������������������������������������������������������������������Ķ
� SINTASSI COMANDO:                                                           �
� REG   [Register] [Value] : Se non e' specificato nessun parametro stampa    �
�       il contenuto dei registri user altrimenti assegna al registro         �
�       [Register] il dato [Value]                                            �
�����������������������������������������������������������������������������ͼ
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
�����������������������������������������������������������������������������ͻ
� FUNZIONE : VERS                           �DATE: Mon  12-27-1993  08:45:38  �
�����������������������������������������������������������������������������Ķ
� FUNZIONI CHIAMATE :  printf()                                               �
�����������������������������������������������������������������������������Ķ
� DESCRIZIONE : comando mml per leggere la data di generazione                �
�����������������������������������������������������������������������������Ķ
� SINTASSI COMANDO:                                                           �
� VERS                                                                        �
�����������������������������������������������������������������������������ͼ
*/

       
COMMAND(vers)
{
printf("\r\n%s",(char *)&version);
com.function=nullfunc;
return(TRUE);
}
/*
�����������������������������������������������������������������������������ͻ
� FUNZIONE : PRSIOBSTAT                     �DATE: Thu  10-28-1993  10:51:01  �
�����������������������������������������������������������������������������Ķ
� INPUT : Puntatore a descrittore porta tipo SERSET                           �
�����������������������������������������������������������������������������Ķ
� OUTPUT : Nessuno                                                            �
�����������������������������������������������������������������������������Ķ
� FUNZIONI CHIAMATE : printf()                                                �
�����������������������������������������������������������������������������Ķ
� DESCRIZIONE : Stampa il settaggio attuale della porta seriale 0             �
�               (SIO porta B)                                                 �
�����������������������������������������������������������������������������ͼ
*/
prsiobstat(prserset)
SERSET  *prserset;
{
printf("\r\nSPEED:%d PARITY:%s",prserset -> speedvalue,parvalue[prserset -> parity]);
printf(" BIT:%d STOP:%d\r\n",prserset -> bitchr+7, prserset -> bitstop+1);
}

/*
�����������������������������������������������������������������������������ͻ
� FUNZIONE : PRREGISTER                     �DATE: Mon  12-27-1993  09:53:45  �
�����������������������������������������������������������������������������Ķ
� INPUT : Nessuno                                                             �
�����������������������������������������������������������������������������Ķ
� OUTPUT : Nessuno                                                            �
�����������������������������������������������������������������������������Ķ
� FUNZIONI CHIAMATE :  printf() - prflagreg()                                 �
�����������������������������������������������������������������������������Ķ
� DESCRIZIONE :  Stampa i valori dei registri macchina di utente              �
�����������������������������������������������������������������������������ͼ
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
�����������������������������������������������������������������������������ͻ
� FUNZIONE : PRFLAGREG                      �DATE: Tue  12-28-1993  21:05:38  �
�����������������������������������������������������������������������������Ķ
� INPUT : Registro F in un byte unsigned                                      �
�����������������������������������������������������������������������������Ķ
� OUTPUT : Nessuno                                                            �
�����������������������������������������������������������������������������Ķ
� FUNZIONI CHIAMATE :  printf()                                               �
�����������������������������������������������������������������������������Ķ
� DESCRIZIONE :  Stampa lo stato dei flag del processore                      �
�����������������������������������������������������������������������������ͼ
*/
prflagreg(tmp)
unsigned char tmp;
{
    printf("S=%1x Z=%1x H=%1x P/V=%1x N=%1x C=%1x\n\r",((tmp&0x80)!=0),((tmp&0x40)!=0),
        ((tmp&0x10)!=0),((tmp&0x04)!=0),((tmp&0x02)!=0),((tmp&0x01)!=0));
}
