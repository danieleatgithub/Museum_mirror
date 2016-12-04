/*
ษอออออออออออออออออออออออออออออออออออออออออออัออออออออออออัออออออออออออออออออออป
บ FILE:\CADASM\R10\ROM\COMMAND\LOAD.C       ณVERS:1.1    ณTIPO: MODULO C      บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤลฤฤฤฤฤฤฤฤฤฤฤฤมฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ AUTORE: Colombo Daniele                   ณDATA:Sun  09-12-1993  14:19:33   บ
ฬอออออออออออออออออออออออออออออออออออออออออออฯอออออออออออออออออออออออออออออออออน
บ INCLUDE: stdio.h - stdlib.h - string.h - math.h                             บ
บ \cadasm\r10\rom\include\conio.h    -     \cadasm\r10\rom\include\load.h     บ
บ \cadasm\r10\rom\include\command.h  -     \cadasm\r10\rom\include\io.h       บ
บ \cadasm\r10\rom\include\error.h                                             บ
ฬอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออน
บ FUNZIONI PUBBLICHE: load() - ldconv() - endpack() - endload() - gethrec()   บ
บ convhrec()                                                                  บ
ฬอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออน
บ DESCRIZIONE: MODULO CARICATORE FILE IN FORMATO HITACHI                      บ
บ Creazioni di:                                                               บ
บ   - Descrittore stato caricatore di tipo LDSTST                             บ
บ   - Descrittore di conversione S-RECORD di tipo HIT_REC                     บ
บ   - Lunghezza e checksum del record                                         บ
ศอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ
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
ษอออออออออออออออออออออออออออออออออออออออออออัอออออออออออออออออออออออออออออออออป
บ FUNZIONE : LOAD                           ณDATE: Sun  09-12-1993  14:29:51  บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤมฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ FUNZIONI CHIAMATE : malloc() - printf() - ei() - di() - strupr() - endload()บ
บ strcmp() - zalloc() - free()                                                บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ DESCRIZIONE:comando mml load alloca memoria per buffer di ricezione stringheบ
บ nella parte bassa dello stack attiva il flag di load in progress e linka    บ
บ le routine di interrupt per il caricamento                                  บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ SINTASSI COMANDO:                                                           บ
บ LOAD      : Si predispone per il caricamento di un file in formato S-RECORD บ
บ LOAD STOP : Ferma il caricamento in corso                                   บ
บ LOAD REL [offset]: Carica un file in formato S-RECORD aggiungendo           บ
บ                    all'indirizzo l'offset specificato                       บ
ศอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ
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
ษอออออออออออออออออออออออออออออออออออออออออออัอออออออออออออออออออออออออออออออออป
บ FUNZIONE : LDCONV                         ณDATE: Sun  09-12-1993  14:38:34  บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤมฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ INPUT : Nessuno                                                             บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ OUTPUT : Nessuno                                                            บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ FUNZIONI CHIAMATE : gethrec() - abs() - xon()                               บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ DESCRIZIONE:funzione di conversione dei record riempiti ad interrupt, se il บ
บ numero di descrittori liberi e' superiore ai due terzi viene inviato un     บ
บ "XON" riattivare il trasmettitore.                                          บ
ศอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ
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
ษอออออออออออออออออออออออออออออออออออออออออออัอออออออออออออออออออออออออออออออออป
บ FUNZIONE : ENDPACK                        ณDATE: Sun  09-12-1993  14:42:42  บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤมฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ INPUT : Nessuno                                                             บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ OUTPUT : Nessuno                                                            บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ FUNZIONI CHIAMATE : abs() - xoff() - printf()                               บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ DESCRIZIONE:Viene chiamata all'interno dell'interrupt di ricezione quando   บ
บ viene letto il carattere CR (0D). La routine setta il flag di descrittore   บ
บ pieno aggiorna la lunghezza incrementa il puntatore al prossimo descrittore บ
บ libero e ferma il trasmettitore se sono occupati piu' della meta' dei       บ
บ descrittori allocati.                                                       บ
ศอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ
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
ษอออออออออออออออออออออออออออออออออออออออออออัอออออออออออออออออออออออออออออออออป
บ FUNZIONE : ENDLOAD                        ณDATE:Sun  09-12-1993  14:47:41   บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤมฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ INPUT : Nessuno                                                             บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ OUTPUT : Nessuno                                                            บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ FUNZIONI CHIAMATE : xoff() - di() - ei() - free()                           บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ DESCRIZIONE : Chiude il caricamento                                         บ
ศอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ
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
ษอออออออออออออออออออออออออออออออออออออออออออัอออออออออออออออออออออออออออออออออป
บ FUNZIONE : GETHREC                        ณDATE:Sun  09-12-1993  14:50:14   บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤมฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ INPUT : Puntatore alla stringa da convertire                                บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ OUTPUT : Nessuno                                                            บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ FUNZIONI CHIAMATE : convhrec() - printf()                                   บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ DESCRIZIONE : Conversione hitachi record                                    บ
ศอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ
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
ษอออออออออออออออออออออออออออออออออออออออออออัอออออออออออออออออออออออออออออออออป
บ FUNZIONE : PRLDSTAT                       ณDATE: Wed  10-27-1993  23:36:54  บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤมฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ INPUT : Nessuno                                                             บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ OUTPUT : Nessuno                                                            บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ FUNZIONI CHIAMATE : printf()                                                บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ DESCRIZIONE : Stampa lo stato del caricamento (errori, numero di byte       บ
บ caricati, offset, numero di buffer occupati)                                บ
บ                                                                             บ
ศอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ
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