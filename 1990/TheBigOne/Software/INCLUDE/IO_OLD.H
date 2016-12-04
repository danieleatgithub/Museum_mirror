/*
ษอออออออออออออออออออออออออออออออออออออออออออัออออออออออออัออออออออออออออออออออป
บ FILE:c:\cadasm\r10\rom\include\io_old.h   ณVERS:1.1    ณTIPO: INCLUDE       บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤลฤฤฤฤฤฤฤฤฤฤฤฤมฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ AUTORE: Colombo Daniele                   ณDATA: Sun  09-12-1993  08:57:25  บ
ฬอออออออออออออออออออออออออออออออออออออออออออฯอออออออออออออออออออออออออออออออออน
บ INCLUDE: \CADASM\R10\ROM\INCLUDE\SYS.H                                      บ
บ                                                                             บ
ฬอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออน
บ DESCRIZIONE: DEFINIZIONI E IMPORTAZIONI RELATIVE ALLE PORTE DI IO E ALLA    บ
บ              LORO GESTIONE (HW VERS 1)                                      บ
บ Contiene:                                                                   บ
บ   - Indirizzi Porte IO interno (1)                                          บ
บ   - Indici array tabella vettori di interrupt                               บ
บ   - Indici array tabella vettori di interrupt fissi                         บ
บ   - Decrittore registri e bit CTC                                           บ
บ   - Decrittore registri e bit SIO                                           บ
บ   - Importazione tabelle, funzioni di utilita' ed handler interrupt         บ
บ                                                                             บ
บ  WARNING (1):                                                               บ
บ  LE DEFINE DEVONO ESSERE SEMPRE ALLINEATE CON IL CONTENUTO DEL FILE         บ                                                                  บ
บ  IOPORT.SRC                                                                 บ
บ  PER INDIRIZZARE L'I/O INTERNO DEVE ESSERE INDIRIZZATA LA PORTA CON         บ
บ  IL BPS DEL BUS ADDRESS A ZERO, MENTRE PER L'I/O ESTERNO DEVE               บ
บ  IL BPS DEL BUS ADDRESS DEVE ESSERE DIVERSO DA ZERO                         บ
บ                                                                             บ
ศอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ
*/

#ifndef _SYS_
#include  "\cadasm\r10\rom\include\sys.h"
#endif

#define     ICR         0x003F  /* I/O CONTROL REGISTER                */
#define		DCNTL 		0x0032	/* DMA WAIT CONTROL REGISTER           */
#define     IL          0x0033  /* INTERRUPT VECTOR LOW REGISTER       */
#define		LIVECT		0x00E0	/* LOW INTERRUPT VECTOR                */
#define		PIOA_CR		0xFF82 /* Control register PIO port A         */
#define		PIOA_DR		0xFF80 /* Data register    PIO port A         */
#define		AR_6845 	0xFF60 /* Control register CRT                */
#define		DR_6845 	0xFF61 /* Data register    CRT                */
#define		SIOA_CR		0xFFC2	/* Control register SIO port A         */
#define		SIOA_DR		0xFFC0	/* Data register    SIO port A         */
#define		SIOB_CR		0xFFC3	/* Control register SIO port B         */
#define		SIOB_DR		0xFFC1	/* Data register    SIO port B         */
#define		CTCCH_0		0xFF40	/* Register         CTC channel 0      */
#define		CTCCH_1		0xFF41	/* Register         CTC channel 1      */
#define		CTCCH_2		0xFF42	/* Register         CTC channel 2      */
#define		CTCCH_3		0xFF43	/* Register         CTC channel 3      */



/* Indici vettori di interrupt	*/
#define		PIOA_I		0
#define		PIOB_I		0
#define		CTCCH0_I        4
#define		CTCCH1_I        5
#define		CTCCH2_I        6
#define		CTCCH3_I        7
#define		SIOBTXE_I       8
#define		SIOBCSE_I       9
#define		SIOBRCV_I       10
#define		SIOBSCR_I       11
#define		SIOATXE_I       12
#define		SIOACSE_I       13
#define		SIOARCV_I       14
#define		SIOASCR_I       15
/* Indici vettori di restart	*/
#define		NMI_I		0

#define		MAXSREG		9	/* Massimo numero di registri di default SIO+CTC */

/* DEFINIZIONE STRUTTURA REGISTRI CTC */
typedef struct  {
		unsigned cntr:1;
		unsigned reset:1;
		unsigned tconst:1;
		unsigned clktrg:1;
		unsigned clkedge:1;
		unsigned prescaler:1;
		unsigned countmode:1;
		unsigned inten:1;
		}CTCCNT;

typedef struct  {
		unsigned value:8;
		}CTCTCONST;

typedef struct  {
		unsigned cntr:1;
		unsigned channel:2;
		unsigned progvect:5;
		}CTCIVECT;


/* DEFINIZIONE STRUTTURA REGISTRI SIO */
#define  	RESEXTINT	2
#define  	RESCHAN		3
#define  	NXTCHEN 	4
#define  	RESIPEND	5
#define  	RESERROR	6
#define  	RETI    	7
#define  	RXIDISI 	0
#define  	RXIFRSTCHR      1
#define  	RXIACHRPV       2
#define  	RXIACHRNPV      3
#define  	BIT5CHR         0
#define  	BIT7CHR         1
#define  	BIT6CHR         2
#define  	BIT8CHR         3
#define  	BSTOP1          1
#define  	BSTOP1_2        2
#define  	BSTOP2          3
#define  	CLOCK1          0
#define  	CLOCK16         1
#define  	CLOCK32         2
#define  	CLOCK64         3

#define  	SIOWR           6
#define  	SIORR           3

typedef struct  {
		unsigned char rnum;
		unsigned intreg:3;
		unsigned command:3;
		unsigned reset:2;
		}SIOCMD;

typedef struct  {
		unsigned char rnum;
		unsigned extinten:1;
		unsigned txinten:1;
		unsigned statvect:1;
		unsigned intrx:2;
		unsigned wron:1;
		unsigned wrfun:1;
		unsigned wren:1;
		}SIOINTCT;

typedef struct  {
                unsigned char rnum;
		char intvect;
		}SIOIVECT;

typedef struct  {
		unsigned char rnum;
		unsigned rxen:1;
		unsigned syncinh:1;
		unsigned addsrmod:1;
		unsigned rxcrc:1;
		unsigned hunt:1;
		unsigned autoen:1;
		unsigned bitchr:2;
		}SIORXCNT;

typedef struct  {
		unsigned char rnum;
		unsigned paren:1;
		unsigned pareven:1;
		unsigned stopbit:2;
		unsigned syncchr:2;
		unsigned clock:2;
		}SIOCNT;

typedef struct  {
		unsigned char rnum;
		unsigned crcen:1;
		unsigned rts:1;
		unsigned crc16:1;
		unsigned txen:1;
		unsigned brk:1;
		unsigned bitchr:2;
		unsigned dtr:1;
		}SIOTXCT;

typedef struct  {
		unsigned char rnum;
		unsigned rxchrav:1;
		unsigned ipend:1;
		unsigned txbufe:1;
		unsigned dcd:1;
		unsigned hunt:1;
		unsigned cts:1;
		unsigned urun:1;
		unsigned brk:1;
		}SIOSTAT;

typedef struct  {
		unsigned char rnum;
		unsigned allsent:1;
		unsigned reschr:3;
		unsigned parer:1;
		unsigned rxovr:1;
		unsigned crcer:1;
		unsigned eoframe:1;
		}SIOERR;

typedef struct  {
		unsigned char rnum;
		unsigned reserved:1;
		unsigned inter:3;
		unsigned progvect:4;
		}SIORDVEC;

extern int di();                   /* disable interrupt */
extern int ei();			       /* enableinterrupt */
extern int (*intvect_t[128])();                /* Tabella vettori di interrupt  (array di puntatori a funzione)  */
extern int (*fixvect_t[7])();                  /* Tabella di linking vettori restart e NMI                       */ 
extern int  UIE(),URSTI(),NMIMON(),IHPIOA(),TXMON(),RXMON(),SPECINT();
extern int  IH_TXLDP(),IH_RXLDP(),IH_ERRLDP();





