/*
浜様様様様様様様様様様様様様様様様様様様様様冤様様様様様用様様様様様様様様様様?
? FILE:\CADASM\R10\ROM\CADOS\STARTUP.C      ?VERS:1.1    ?TIPO: MODULO C      ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳田陳陳陳陳陳珍陳陳陳陳陳陳陳陳陳陳?
? AUTORE: Colombo Daniele                   ?DATA: Sun  09-12-1993  11:32:55  ?
麺様様様様様様様様様様様様様様様様様様様様様詫様様様様様様様様様様様様様様様様?
? INCLUDE: stdio.h - string.h - stdlib.h - \cadasm\r10\rom\include\conio.h    ?
? \cadasm\r10\rom\include\command.h   -    \cadasm\r10\rom\include\io.h       ?
? \cadasm\r10\rom\include\load.h      -    \cadasm\r10\rom\include\error.h    ?
麺様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
? FUNZIONI PUBBLICHE: iniram() - iniscr() - initio() - siobinit()             ?
麺様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
? DESCRIZIONE: FUNZIONI DI INIZIALIZZAZIONE MEMORIA E PERIFERICHE DI IO       ?
? Contiene la creazione di:                                                   ?
? - Inizializzazione array stringhe di errore                                 ?
? - Tabelle di programmazione SIO                                             ?
? - Puntatori a stringhe di errore                                            ?
? - Descrittori video - stato editor di linea - ultimo comando -              ?
? - Buffer comando in editing                                                 ?
? - Carattere ricevuto da tastiera                                            ?
? - Array puntatori alle funzioni di esecuzione dei comandi                   ?
? - Array buffer di history                                                   ?
? - Puntatori di lettura e scrittura buffer di history                        ?
? - Descrittori periferiche CTC - SIO PORTA B -                               ?
? - Descrittori per caricatore                                                ?
? - Descrittori break e trace point                                           ?
? - Flag e contatore modalita step                                            ?
? - Buffer temporanei per registri di utente                                  ?
藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
*/

#define     __STARTUP__
#include  <stdio.h>      
#include  <string.h>
#include  <stdlib.h>
#include  "\cadasm\r10\rom\include\conio.h"
#include  "\cadasm\r10\rom\include\command.h"
#include  "\cadasm\r10\rom\include\io.h"
#include  "\cadasm\r10\rom\include\load.h"
#include  "\cadasm\r10\rom\include\error.h"

#define USERRAM     0xA000
#define USTACK      0xE000

/* --------------------- IMPORTAZIONI ------------------------*/                 
extern char *CRTDEF_T;     /* Tabella di default CRT controller         */
extern char *PIO_A_T;      /* Tabella di default porta A pio (tastiera) */
                           /* Puntatori routine di gestione eccezioni   */


/* --------------------- CREAZIONI ------------------------*/                           

const SERTAB sertab_t[MAXSERTAB]={
    0x45,0x34,0x01,0x14,0x03,0x41,0x04,0xC5,0x05,0x2A,  /*  300 baud 7 bit/chr Parity:ODD  1 stop */
    0x45,0x34,0x01,0x14,0x03,0x41,0x04,0xCD,0x05,0x2A,  /*  300 baud 7 bit/chr Parity:ODD  2 stop */
    0x45,0x34,0x01,0x14,0x03,0x41,0x04,0xC7,0x05,0x2A,  /*  300 baud 7 bit/chr Parity:EVEN 1 stop */
    0x45,0x34,0x01,0x14,0x03,0x41,0x04,0xCF,0x05,0x2A,  /*  300 baud 7 bit/chr Parity:EVEN 2 stop */
    0x45,0x34,0x01,0x14,0x03,0x41,0x04,0xC4,0x05,0x2A,  /*  300 baud 7 bit/chr Parity:NONE 1 stop */
    0x45,0x34,0x01,0x14,0x03,0x41,0x04,0xCC,0x05,0x2A,  /*  300 baud 7 bit/chr Parity:NONE 2 stop */
    0x45,0x34,0x01,0x14,0x03,0xC1,0x04,0xC4,0x05,0x6A,  /*  300 baud 8 bit/chr Parity:NONE 1 stop */
    0x45,0x34,0x01,0x14,0x03,0xC1,0x04,0xCC,0x05,0x6A,  /*  300 baud 8 bit/chr Parity:NONE 2 stop */
    0x45,0x1A,0x01,0x14,0x03,0x41,0x04,0xC5,0x05,0x2A,  /*  600 baud 7 bit/chr Parity:ODD  1 stop */
    0x45,0x1A,0x01,0x14,0x03,0x41,0x04,0xCD,0x05,0x2A,  /*  600 baud 7 bit/chr Parity:ODD  2 stop */
    0x45,0x1A,0x01,0x14,0x03,0x41,0x04,0xC7,0x05,0x2A,  /*  600 baud 7 bit/chr Parity:EVEN 1 stop */
    0x45,0x1A,0x01,0x14,0x03,0x41,0x04,0xCF,0x05,0x2A,  /*  600 baud 7 bit/chr Parity:EVEN 2 stop */
    0x45,0x1A,0x01,0x14,0x03,0x41,0x04,0xC4,0x05,0x2A,  /*  600 baud 7 bit/chr Parity:NONE 1 stop */
    0x45,0x1A,0x01,0x14,0x03,0x41,0x04,0xCC,0x05,0x2A,  /*  600 baud 7 bit/chr Parity:NONE 2 stop */
    0x45,0x1A,0x01,0x14,0x03,0xC1,0x04,0xC4,0x05,0x6A,  /*  600 baud 8 bit/chr Parity:NONE 1 stop */
    0x45,0x1A,0x01,0x14,0x03,0xC1,0x04,0xCC,0x05,0x6A,  /*  600 baud 8 bit/chr Parity:NONE 2 stop */
    0x45,0x0D,0x01,0x14,0x03,0x41,0x04,0xC5,0x05,0x2A,  /* 1200 baud 7 bit/chr Parity:ODD  1 stop */
    0x45,0x0D,0x01,0x14,0x03,0x41,0x04,0xCD,0x05,0x2A,  /* 1200 baud 7 bit/chr Parity:ODD  2 stop */
    0x45,0x0D,0x01,0x14,0x03,0x41,0x04,0xC7,0x05,0x2A,  /* 1200 baud 7 bit/chr Parity:EVEN 1 stop */
    0x45,0x0D,0x01,0x14,0x03,0x41,0x04,0xCF,0x05,0x2A,  /* 1200 baud 7 bit/chr Parity:EVEN 2 stop */
    0x45,0x0D,0x01,0x14,0x03,0x41,0x04,0xC4,0x05,0x2A,  /* 1200 baud 7 bit/chr Parity:NONE 1 stop */
    0x45,0x0D,0x01,0x14,0x03,0x41,0x04,0xCC,0x05,0x2A,  /* 1200 baud 7 bit/chr Parity:NONE 2 stop */
    0x45,0x0D,0x01,0x14,0x03,0xC1,0x04,0xC4,0x05,0x6A,  /* 1200 baud 8 bit/chr Parity:NONE 1 stop */
    0x45,0x0D,0x01,0x14,0x03,0xC1,0x04,0xCC,0x05,0x6A,  /* 1200 baud 8 bit/chr Parity:NONE 2 stop */
    0x45,0x0D,0x01,0x14,0x03,0x41,0x04,0x85,0x05,0x2A,  /* 2400 baud 7 bit/chr Parity:ODD  1 stop */
    0x45,0x0D,0x01,0x14,0x03,0x41,0x04,0x8D,0x05,0x2A,  /* 2400 baud 7 bit/chr Parity:ODD  2 stop */
    0x45,0x0D,0x01,0x14,0x03,0x41,0x04,0x87,0x05,0x2A,  /* 2400 baud 7 bit/chr Parity:EVEN 1 stop */
    0x45,0x0D,0x01,0x14,0x03,0x41,0x04,0x8F,0x05,0x2A,  /* 2400 baud 7 bit/chr Parity:EVEN 2 stop */
    0x45,0x0D,0x01,0x14,0x03,0x41,0x04,0x84,0x05,0x2A,  /* 2400 baud 7 bit/chr Parity:NONE 1 stop */
    0x45,0x0D,0x01,0x14,0x03,0x41,0x04,0x8C,0x05,0x2A,  /* 2400 baud 7 bit/chr Parity:NONE 2 stop */
    0x45,0x0D,0x01,0x14,0x03,0xC1,0x04,0x84,0x05,0x6A,  /* 2400 baud 8 bit/chr Parity:NONE 1 stop */
    0x45,0x0D,0x01,0x14,0x03,0xC1,0x04,0x8C,0x05,0x6A,  /* 2400 baud 8 bit/chr Parity:NONE 2 stop */
    0x45,0x0D,0x01,0x14,0x03,0x41,0x04,0x45,0x05,0x2A,  /* 4800 baud 7 bit/chr Parity:ODD  1 stop */
    0x45,0x0D,0x01,0x14,0x03,0x41,0x04,0x4D,0x05,0x2A,  /* 4800 baud 7 bit/chr Parity:ODD  2 stop */
    0x45,0x0D,0x01,0x14,0x03,0x41,0x04,0x47,0x05,0x2A,  /* 4800 baud 7 bit/chr Parity:EVEN 1 stop */
    0x45,0x0D,0x01,0x14,0x03,0x41,0x04,0x4F,0x05,0x2A,  /* 4800 baud 7 bit/chr Parity:EVEN 2 stop */
    0x45,0x0D,0x01,0x14,0x03,0x41,0x04,0x44,0x05,0x2A,  /* 4800 baud 7 bit/chr Parity:NONE 1 stop */
    0x45,0x0D,0x01,0x14,0x03,0x41,0x04,0x4C,0x05,0x2A,  /* 4800 baud 7 bit/chr Parity:NONE 2 stop */
    0x45,0x0D,0x01,0x14,0x03,0xC1,0x04,0x44,0x05,0x6A,  /* 4800 baud 8 bit/chr Parity:NONE 1 stop */
    0x45,0x0D,0x01,0x14,0x03,0xC1,0x04,0x4C,0x05,0x6A}; /* 4800 baud 8 bit/chr Parity:NONE 2 stop */


USERFR  uframe;                 /* FRAME UTENTE                            */
VIDEO   video_desc;             /* DESCRITTORE SCHERMO                     */
LINE    monline;                /* DESCRITTORE EDITOR DI LINEA             */
CMD     com;                    /* DESCRITTORE ULTIMO COMANDO              */
char    curline[MAXLENCMD];     /* Buffer comando in editing               */
char    keychar;                /* Carattere ricevuto da tastiera          */
int     (*entrycom[MAXCOM])();  /* Array di puntatori a funzione comandi   */
HISTOR  history[MAXHIST];       /* Array buffer di history comando         */
HISTOR  *wrhist;                /* Puntatore lettura buffer history        */
HISTOR  *rdhist;                /* Puntatore scrittura buffer history      */
SERTAB  *siotab;                /* Puntatore a tabelle settaggio can ser   */
SERSET  serset_b;               /* Descrittore porta seriale B SIO         */

unsigned char   ctc0vect;       /* Vettore interrupt CTC canale 0          */
unsigned char   ctc1vect;       /* Vettore interrupt CTC canale 1          */
unsigned char   ctc2vect;       /* Vettore interrupt CTC canale 2          */
unsigned char   ctc3vect;       /* Vettore interrupt CTC canale 3          */

SIOVECT         siointvect;     /* Vettore interrupt SIO                   */
SIOCMD          siocmd;         /* Command register SIO                    */
SIOSTAT         siostat_b;      /* Status register porta B                 */
SIOERR          sioerr_b;       /* Error register porta B                  */
SIORDVEC        siordvec_b;     /* Read vector register porta B            */

LDSTAT      loadstat;           /* Descrittore stato caricamento       */
LDBUF       loadbuf[MAXBUF];    /* Array di descrittori buffer di load */
LDBUF       *ptbuf[MAXBUF+1];   /* Array di puntatori a descrittori buffer di load */
LDBUF       **busybuf;          /* Puntatore buffer corrente pieno     */
LDBUF       **freebuf;          /* Puntatore buffer corrente vuoto     */


TRPDESC     bpoint[3];
TRPDESC     tpoint[3];
char            bpnum;          /* Numero del break point scattato */
char            tpnum;          /* Numero del trace point scattato */


unsigned char   stepflg;        /* Flag modo step (FF=step 0=normal)   */
unsigned char   stepcount;      /* Step counter                        */

unsigned char   atemp;          /* Variabile temporanea per registro A */
unsigned int    hltemp;         /* Variabile temporanea per registro HL*/

/*
浜様様様様様様様様様様様様様様様様様様様様様冤様様様様様様様様様様様様様様様様?
? FUNZIONE : INIRAM                         ?DATE: Sun  09-12-1993  11:49:24  ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳祖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? INPUT : Nessuno                                                             ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? OUTPUT : Nessuno                                                            ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? FUNZIONI CHIAMATE : flushbuf() - strcpy() - memclr()                        ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? DESCRIZIONE : Inizializza tabelle di interrupt e dati dinamici              ?
藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
*/
iniram()
{
register char   i;
unsigned char   *tmp;
register HISTOR *init;

timmark=0;
/*陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳*/
/* Inizializzazione tabella vettori di interrupt e restart */
/*陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳*/
for(i=0;i<=128;++i)
	intvect_t[i]=UIE;
for(i=0;i<=7;++i)
    fixvect_t[i]=URSTI;
intvect_t[PIOA_I]=IHPIOA;
fixvect_t[NMI_I]=NMIMON;
intvect_t[SIOBTXE_I]=TXMON;
intvect_t[SIOBRCV_I]=RXMON;
intvect_t[SIOBSCR_I]=SPECINT;


/*陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳*/
/* Inizializzazione dati e descrittori interfaccia mml */
/*陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳*/
sysdesc.state=ROM;
sysdesc.ldp=NO;
flushbuf(&monline);
keychar=255;
monline.mode=OVERSTRIKE;
monline.base=16;
strcpy(monline.strbase,"%x");
strcpy(monline.addmode,"%04x: ");
strcpy(monline.datamode,"%02x ");
/*陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳*/
/* Inizializzazione puntatore tabella porte seriali                     */
/*陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳*/
ctc0vect=(CTCCH0_I*2);
siocmd.rnum=0;
siocmd.value=0;
siointvect.rnum=2;
siointvect.vector=(SIOBTXE_I*2);
siotab=&sertab_t[0];
serset_b.speed=0;
serset_b.speedvalue=300;
serset_b.parity=0;
serset_b.bitchr=0;
serset_b.bitstop=0;
/*陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳*/
/* Inizializzazione data base puntatori a funzione comandi */
/*陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳*/

com.function=nullfunc;
entrycom[0]=load;           /* Comando :  LOAD          */
entrycom[1]=write;          /* Comando :  WRITE         */
entrycom[2]=read;           /* Comando :  READ          */
entrycom[3]=rdport;         /* Comando :  RDPORT        */
entrycom[4]=wrport;         /* Comando :  WRPORT        */
entrycom[5]=cmdnotld;       /* Comando :  EPROG         */
entrycom[6]=cmdnotld;       /* Comando :  EBLANK        */
entrycom[7]=cmdnotld;       /* Comando :  EVERIFY       */
entrycom[8]=cmdnotld;       /* Comando :  ECOPY         */
entrycom[9]=go;             /* Comando :  GO            */
entrycom[10]=step;          /* Comando :  STEP          */
entrycom[11]=bpset;         /* Comando :  BPS           */
entrycom[12]=bpdel;         /* Comando :  BPD           */
entrycom[13]=bpprint;       /* Comando :  BP            */
entrycom[14]=tpset;         /* Comando :  TPS           */
entrycom[15]=tpdel;         /* Comando :  TPD           */
entrycom[16]=tpprint;       /* Comando :  TP            */
entrycom[17]=reg;           /* Comando :  REG           */
entrycom[18]=cominst;       /* Comando :  COMINST       */
entrycom[19]=filmem;        /* Comando :  FILL          */
entrycom[20]=setport;       /* Comando :  SETPORT       */
entrycom[21]=vers;          /* Comando :  VERS          */

/*陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳*/
/* Inizializzazione buffer di loader */
/*陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳*/
for(i=0;i<MAXBUF;++i)
	ptbuf[i]=&loadbuf[i];
ptbuf[i]=0;				/* End of pointer */
busybuf=ptbuf;
freebuf=ptbuf;
memclr((char *)&loadstat,sizeof(LDSTAT));

/*陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳*/
/* Inizializzazione buffer di history */
/*陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳*/
i=0;
init=&history[0];
wrhist=init;
rdhist=init;
memclr(init -> buffer,MAXLENCMD-1);
init -> prev =&history[MAXHIST-1];
init -> next =&history[++i];
++init;
for(;i<MAXHIST-1;++i,++init) {
    memclr(init -> buffer,MAXLENCMD-1);
    init -> prev =&history[i-1];
    init -> next =&history[i+1];
}
memclr(init -> buffer,MAXLENCMD-1);
init -> prev =&history[i-1];
init -> next =&history[0];
/*陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳*/
/* Inizializzazione install
/*陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳*/
/*
tmp=(unsigned char *)install;
*tmp=NOTINST; */

}
/*
浜様様様様様様様様様様様様様様様様様様様様様冤様様様様様様様様様様様様様様様様?
? FUNZIONE : INISCR                         ?DATE:Sun  09-12-1993  12:25:32   ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳祖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? INPUT : Nessuno                                                             ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? OUTPUT : Nessuno                                                            ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? FUNZIONI CHIAMATE : inicrt()                                                ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? DESCRIZIONE : Inizializza descrittore video e CRT controller                ?
藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
*/
iniscr()
{
initcrt(&CRTDEF_T);
video_desc.cur_x=0;
video_desc.cur_y=0;
video_desc.cstyle=SLOWBLINK;
video_desc.prompt=DEBPROMPT;
video_desc.start_add=STRT_ADD;
video_desc.curs_add=CUR_ADD;
}
/*
浜様様様様様様様様様様様様様様様様様様様様様冤様様様様様様様様様様様様様様様様?
? FUNZIONE : INITIO                         ?DATE: Sun  09-12-1993  12:28:43  ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳祖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? INPUT : Nessuno                                                             ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? OUTPUT : Nessuno                                                            ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? FUNZIONI CHIAMATE : inpio() - siobinit()                                    ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? DESCRIZIONE : Inizializza periferiche di IO                                 ?
藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
*/
initio()
{
siobinit(siotab);
inpio_a(&PIO_A_T);
}
/*
浜様様様様様様様様様様様様様様様様様様様様様冤様様様様様様様様様様様様様様様様?
? FUNZIONE : SIOBINIT                       ?DATE: Sun  09-12-1993  12:30:36  ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳祖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? INPUT : Puntatore descrittore porta seriale tipo SERTAB                     ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? OUTPUT : Nessuno                                                            ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? FUNZIONI CHIAMATE : writeb()                                                ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? DESCRIZIONE : Inizializza porta B SIO da descrittori                        ?
藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
*/
siobinit(table)
SERTAB  *table;
{
writeb((char *)&siocmd,2,SIOB_CR);
writeb(&(table -> ctccnt),1,CTCCH_0);
writeb(&(table -> ctconst),1,CTCCH_0);
writeb(&ctc0vect,1,CTCCH_0);
writeb(&(table -> siointct),2,SIOB_CR);
writeb(&siointvect,2,SIOB_CR);
writeb(&(table -> siorxcnt),2,SIOB_CR);
writeb(&(table -> siocnt),2,SIOB_CR);
writeb(&(table -> siotxct),2,SIOB_CR);
return (0);
}
/*
浜様様様様様様様様様様様様様様様様様様様様様冤様様様様様様様様様様様様様様様様?
? FUNZIONE : INIBREAK                       ?DATE: Tue  12-28-1993  21:42:08  ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳祖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? INPUT : Nessuno                                                             ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? OUTPUT : Nessuno                                                            ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? FUNZIONI CHIAMATE : Nessuno                                                 ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? DESCRIZIONE :  Inizializza dati break point trace point e dati macchina     ?
藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
*/
inibreak()
{
int i;
stepflg=STEPOFF;
stepcount=0;
atemp=0;
hltemp=0;
uframe.ureg[URGREL(PC_I)]=USERRAM;
uframe.ureg[URGREL(SP_I)]=USTACK;
for(i=0;i<3;++i){
    flushtrp(&bpoint[i]);
    flushtrp(&tpoint[i]);
}
}
