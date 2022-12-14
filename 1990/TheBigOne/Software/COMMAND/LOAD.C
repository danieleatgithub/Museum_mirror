/*
浜様様様様様様様様様様様様様様様様様様様様様冤様様様様様用様様様様様様様様様様?
? FILE:\CADASM\R10\ROM\COMMAND\LOAD.C       ?VERS:1.1    ?TIPO: MODULO C      ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳田陳陳陳陳陳珍陳陳陳陳陳陳陳陳陳陳?
? AUTORE: Colombo Daniele                   ?DATA:Sun  09-12-1993  14:19:33   ?
麺様様様様様様様様様様様様様様様様様様様様様詫様様様様様様様様様様様様様様様様?
? INCLUDE: stdio.h - stdlib.h - string.h - math.h                             ?
? \cadasm\r10\rom\include\conio.h    -     \cadasm\r10\rom\include\load.h     ?
? \cadasm\r10\rom\include\command.h  -     \cadasm\r10\rom\include\io.h       ?
? \cadasm\r10\rom\include\error.h                                             ?
麺様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
? FUNZIONI PUBBLICHE: load() - ldconv() - endpack() - endload() - gethrec()   ?
? convhrec()                                                                  ?
麺様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
? DESCRIZIONE: MODULO CARICATORE FILE IN FORMATO HITACHI                      ?
? Creazioni di:                                                               ?
?   - Descrittore stato caricatore di tipo LDSTST                             ?
?   - Descrittore di conversione S-RECORD di tipo HIT_REC                     ?
?   - Lunghezza e checksum del record                                         ?
藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
*/

#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>
#include  <math.h>
#include  "\cadasm\r10\rom\include\conio.h"
#include  "\cadasm\r10\rom\include\load.h"
#include  "\cadasm\r10\rom\include\command.h"
#include  "\cadasm\r10\rom\include\io.h"
#include  "\cadasm\r10\rom\include\error.h"


/* --------------------- IMPORTAZIONI ------------------------*/                 
extern CMD          com;

/* ---------------------- CREAZIONI --------------------------*/
HIT_REC             hrec;
unsigned char       reclen;
char                gethrec();

/*
浜様様様様様様様様様様様様様様様様様様様様様冤様様様様様様様様様様様様様様様様?
? FUNZIONE : LOAD                           ?DATE: Sun  09-12-1993  14:29:51  ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳祖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? FUNZIONI CHIAMATE : malloc() - printf() - ei() - di() - strupr() - endload()?
? strcmp() - zalloc() - free()                                                ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? DESCRIZIONE:comando mml load alloca memoria per buffer di ricezione stringhe?
? nella parte bassa dello stack attiva il flag di load in progress e linka    ?
? le routine di interrupt per il caricamento                                  ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? SINTASSI COMANDO:                                                           ?
? LOAD      : Si predispone per il caricamento di un file in formato S-RECORD ?
? LOAD STOP : Ferma il caricamento in corso                                   ?
? LOAD REL [offset]: Carica un file in formato S-RECORD aggiungendo           ?
?                    all'indirizzo l'offset specificato                       ?
藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
*/
COMMAND(load)
{
register char i;
char *tmp;
com.function=nullfunc;

if(numarg>=2)
	{
    tmp=strupr((char *)com.param[1]);
	if(!strcmp(tmp,"STOP"))
		{
		endload();
        LDABTD;
        return(RTNBAD);
		}
    if(!strcmp(tmp,"STAT"))
        {
        prldstat();
        return(TRUE);
        }
    }

if(sysdesc.ldp==NO)
	{
    loadstat.offset=0;
    if(numarg==3&& !strcmp(tmp,"REL")) loadstat.offset=(char *)com.param[2];

    for(i=0;i<MAXBUF;++i)
		{
		if(!(loadbuf[i].buffer=zalloc(SMAXLEN)))
			{
			NOTMEM;
            for(--i;i>=0;--i) free(loadbuf[i].buffer);
            return(RTNBAD);
			break;
			}
			else loadbuf[i].ptchar=loadbuf[i].buffer;
		}

	sysdesc.ldp=YES;				/* set load in progress */
    loadstat.stpflag=0;
    loadstat.busycount=0;
    loadstat.ldlen=0;
    loadstat.parer=0;
    loadstat.gener=0;
    memclr(loadstat.name,sizeof(loadstat.name));
    memclr(loadstat.type,sizeof(loadstat.type));
    di();
	intvect_t[SIOBTXE_I]=IH_TXLDP;          /* link routine interrupt per loader */
	intvect_t[SIOBRCV_I]=IH_RXLDP;
	intvect_t[SIOBSCR_I]=IH_ERRLDP;
	ei();
    LDRDY;
	return(TRUE);
	}
}
/*
浜様様様様様様様様様様様様様様様様様様様様様冤様様様様様様様様様様様様様様様様?
? FUNZIONE : LDCONV                         ?DATE: Sun  09-12-1993  14:38:34  ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳祖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? INPUT : Nessuno                                                             ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? OUTPUT : Nessuno                                                            ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? FUNZIONI CHIAMATE : gethrec() - abs() - xon()                               ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? DESCRIZIONE:funzione di conversione dei record riempiti ad interrupt, se il ?
? numero di descrittori liberi e' superiore ai due terzi viene inviato un     ?
? "XON" riattivare il trasmettitore.                                          ?
藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
*/
ldconv()
{
register char i;
register int tmp;

if(LDbsy(busybuf))              /*  Test se il buffer di scarico corrente e' pieno  */
 {
                  /* Acquisisco il record in formato Hitachi S-Record */
    if( (i=gethrec(LDbuf(busybuf))) && i!=TERMINATOR )
    {
        LDCKERR(i);
        siores(SIOB_CR);
        endload();
    }

    LDptc(busybuf) = LDbuf(busybuf);    /* Reset puntatore di carico         */
    LDpkl(busybuf)=0;                   /* Azzero lunghezza                  */
    --loadstat.busycount;               /* Decremento contatore buffer pieni */
    LDbsy(busybuf)=NO;                  /* Libero il descrittore             */
    ++busybuf;                          /* Prossimo buffer di scarico        */
    if(*busybuf==NULL) busybuf = ptbuf; /* Test ricircolo                    */

    if(loadstat.busycount<MAXBUF/3&& loadstat.stpflag) /* Test se occupati meno dei due terzi e caricamento sospeso */
    {
        xon(SIOB_DR);           /* Riattivo il trasmettitore   */
        loadstat.stpflag=NO;    /* Reset flag di stato sospeso */
    }
    if(i==TERMINATOR)
    {
        endload();
        LDEND;
    }
 }

}
/*
浜様様様様様様様様様様様様様様様様様様様様様冤様様様様様様様様様様様様様様様様?
? FUNZIONE : ENDPACK                        ?DATE: Sun  09-12-1993  14:42:42  ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳祖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? INPUT : Nessuno                                                             ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? OUTPUT : Nessuno                                                            ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? FUNZIONI CHIAMATE : abs() - xoff() - printf()                               ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? DESCRIZIONE:Viene chiamata all'interno dell'interrupt di ricezione quando   ?
? viene letto il carattere CR (0D). La routine setta il flag di descrittore   ?
? pieno aggiorna la lunghezza incrementa il puntatore al prossimo descrittore ?
? libero e ferma il trasmettitore se sono occupati piu' della meta' dei       ?
? descrittori allocati.                                                       ?
藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
*/
endpack()
{
register int tmp;
LDbsy(freebuf)=YES;                 /* Setto il flag di descrittore pieno */
LDpkl(freebuf) -=2;                 /* ???????????????????                */
++loadstat.busycount;               /* Incremento contatore buffer pieni  */
++freebuf;                          /* Prossimo buffer di carico          */
if(*freebuf==NULL) freebuf = ptbuf; /* Test ricircolo                     */

if(loadstat.busycount>MAXBUF/2) /* Se i buffer pieni sono piu' della meta' del massimo */
	{
    xoff(SIOB_DR);          /* Sospendo il trasmettitore */
    loadstat.stpflag=YES;   /* Set flag di stato sospeso */
	}

}
/*
浜様様様様様様様様様様様様様様様様様様様様様冤様様様様様様様様様様様様様様様様?
? FUNZIONE : ENDLOAD                        ?DATE:Sun  09-12-1993  14:47:41   ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳祖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? INPUT : Nessuno                                                             ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? OUTPUT : Nessuno                                                            ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? FUNZIONI CHIAMATE : xoff() - di() - ei() - free()                           ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? DESCRIZIONE : Chiude il caricamento                                         ?
藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
*/
endload()
{
register int i;
xoff();
sysdesc.ldp=NO;				/* reset load in progress */
di();
intvect_t[SIOBTXE_I]=TXMON;
intvect_t[SIOBRCV_I]=RXMON;
intvect_t[SIOBSCR_I]=SPECINT;
ei();
for(i=MAXBUF-1;i>=0;--i) free(loadbuf[i].buffer);
}
/*
浜様様様様様様様様様様様様様様様様様様様様様冤様様様様様様様様様様様様様様様様?
? FUNZIONE : GETHREC                        ?DATE:Sun  09-12-1993  14:50:14   ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳祖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? INPUT : Puntatore alla stringa da convertire                                ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? OUTPUT : Nessuno                                                            ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? FUNZIONI CHIAMATE : convhrec() - printf()                                   ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? DESCRIZIONE : Conversione hitachi record                                    ?
藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
*/

char gethrec(pthrec)
char 	*pthrec;
{
unsigned char *ldtmpadd;

if(*pthrec++=='S')                            /* Controllo che sia un S-RECORD */
	{
	switch(*pthrec++)
		{
		case DATA:
            hrec.src=pthrec;    /* conversione lunghezza record */
            hrec.dest=&reclen;
			hrec.lenght=1;
			hrec.cksum=0;
            convhrec(&hrec);

            hrec.dest=(unsigned char *)&ldtmpadd;   /* conversione load address  e salvo in tmp */
            convhrecf(&hrec);

            hrec.dest=ADDOFF(ldtmpadd,loadstat.offset);     /* Setto la destinazione letta da record */
            hrec.lenght=reclen-3;                   /* Tolgo dalla lunghezza due byte di     */
                                                    /* indirizzo ed uno di cheksum           */
            convhrec(&hrec);

            return(cktest(&hrec));
            break;
        case SYMBOL:
            break;
        case HEADER:
			hrec.src=pthrec;
			hrec.dest=&reclen;
			hrec.lenght=1;
			hrec.cksum=0;
			convhrec(&hrec);
			hrec.dest=NULL;
			hrec.lenght=2;
			convhrec(&hrec);
			hrec.dest=loadstat.name;
			hrec.lenght=reclen-6;
			convhrec(&hrec);
			loadstat.name[reclen-6]=NULL;
			hrec.dest=loadstat.type;
			hrec.lenght=3;
			convhrec(&hrec);
			loadstat.type[3]=NULL;
            return(cktest(&hrec));
			break;
        case TERMINATOR:
            return(TERMINATOR);

		}

	}
return(TRUE);
}
/*
浜様様様様様様様様様様様様様様様様様様様様様冤様様様様様様様様様様様様様様様様?
? FUNZIONE : PRLDSTAT                       ?DATE: Wed  10-27-1993  23:36:54  ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳祖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? INPUT : Nessuno                                                             ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? OUTPUT : Nessuno                                                            ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? FUNZIONI CHIAMATE : printf()                                                ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? DESCRIZIONE : Stampa lo stato del caricamento (errori, numero di byte       ?
? caricati, offset, numero di buffer occupati)                                ?
?                                                                             ?
藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
*/
prldstat()
{
printf("\r\n");
printf("%s:%s\t%s:%x\r\n",name,loadstat.name,offset,loadstat.offset);
printf("%s:%x\r\n",lenght,loadstat.ldlen);
printf("BUSYBUFF:%d\r\n",loadstat.busycount);
printf("%s %s:%d\t%s %s:%d\r\n",parity,error,loadstat.parer,generic,error,loadstat.gener);
}
