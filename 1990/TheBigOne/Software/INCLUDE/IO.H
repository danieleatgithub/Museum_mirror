/*
ษอออออออออออออออออออออออออออออออออออออออออออัออออออออออออัออออออออออออออออออออป
บ FILE:c:\cadasm\r10\rom\include\io.h       ณVERS:1.1    ณTIPO: INCLUDE       บ
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
บ  LE DEFINE DEVONO ESSERE SEMPRE ALLINEATE CON IL CONTENUTO DEL FILE         บ
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

#define		ICR    		0x003F	/* I/O CONTROL REGISTER                */
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
#define		SIOBTXE_I       0
#define		SIOBCSE_I       1
#define		SIOBRCV_I       2
#define		SIOBSCR_I       3
#define		SIOATXE_I       4
#define		SIOACSE_I       5
#define		SIOARCV_I       6
#define		SIOASCR_I       7
#define		CTCCH0_I        8
#define		CTCCH1_I        9
#define		CTCCH2_I        10
#define		CTCCH3_I        11
#define		PIOA_I		12
#define		PIOB_I		13

/* Indici vettori di restart	*/
#define		NMI_I		0

#define     MAXSERTAB     40 /* Massimo numero tabelle */

/* DEFINE BREK */
#define     STEPON      191
#define     STEPOFF     255

#define     BP0_RST08   0xCF
#define     BP1_RST10   0xD7
#define     BP2_RST18   0xDF
#define     TP0_RST20   0xE7
#define     TP1_RST28   0xEF
#define     TP2_RST30   0xF7

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
        unsigned int  ureg[12];    /* Program counter user   */
                                   /* User stack pointer     */
                                   /* User register AF       */
                                   /* User register BC       */
                                   /* User register DE       */
                                   /* User register HL       */
                                   /* User register AF1      */
                                   /* User register DE1      */
                                   /* User register BC1      */
                                   /* User register HL1      */
                                   /* User register IX       */
                                   /* User register IY       */
        unsigned char uregif1;     /* User flip flop iff1    */
        unsigned char uregif2;     /* User flip flop iff2    */
        }USERFR;                   /* FRAME UTENTE           */

typedef struct {
        unsigned char       *opadd;     /* Off 0                 */
        unsigned char       opdata;     /* Off 2                 */
        int                 cond1;      /* Off 3                 */
        union {
            unsigned int    counter;
            unsigned char   *ptrchr;
            int             *ptrint;
        }datstat;                       /* Off 5        Statico  */
        union {
            unsigned int    counter;
            unsigned char   *ptrchr;
            int             *ptrint;
        }datdyn;                        /* Off 7        dinamico */
        int                 cond2;      /* Off 9                 */
        int                 value;      /* Off 11                */
    }TRPDESC;                           /* SZ  13                */


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

typedef struct {
    unsigned char rnum;
    unsigned char vector;
    }SIOVECT;

typedef struct {
    unsigned char rnum;
    unsigned char value;
    }SIOCMD;

typedef struct {
    int     speed;
    int     speedvalue;
    int     parity;
    int     bitchr;
    int     bitstop;
    }SERSET;

typedef struct {
    unsigned char ctccnt;
    unsigned char ctconst;
    unsigned char siointct;
    unsigned char siointctval;
    unsigned char siorxcnt;
    unsigned char siorxcntval;
    unsigned char siocnt;
    unsigned char siocntval;
    unsigned char siotxct;
    unsigned char siotxctval;
    }SERTAB;

extern int di();                   /* disable interrupt */
extern int ei();			       /* enableinterrupt */
extern int (*intvect_t[128])();                /* Tabella vettori di interrupt  (array di puntatori a funzione)  */
extern int (*fixvect_t[7])();                  /* Tabella di linking vettori restart e NMI                       */ 

extern int  UIE(),URSTI(),IHPIOA(),TXMON(),RXMON(),SPECINT();
extern int  IH_TXLDP(),IH_RXLDP(),IH_ERRLDP(),NMIROM();

#ifndef __TRAP__
extern int  NMIMON(),NMINSTEP(),NMIBREAK();
#endif


#ifndef __STARTUP__
extern unsigned char   stepflg;        /* Flag modo step (FF=step 0=normal)   */
extern unsigned char   stepcount;      /* Step counter                        */

extern TRPDESC         bpoint[3];
extern TRPDESC         tpoint[3];
extern char            bpnum;          /* Numero del break point scattato */
extern char            tpnum;          /* Numero del trace point scattato */

extern  USERFR uframe;
extern  SERTAB *siotab;      /* Puntatore a tabelle settaggio can ser   */
extern  SERSET  serset_b;

extern  SIOVECT         siointvect;
extern  SIOCMD          siocmd_b;

extern  SIOSTAT         siostat_b;
extern  SIOERR          sioerr_b;
extern  SIORDVEC        siordvec_b;
#endif
