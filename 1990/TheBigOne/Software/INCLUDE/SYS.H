/*
ษอออออออออออออออออออออออออออออออออออออออออออัออออออออออออัออออออออออออออออออออป
บ FILE:c:\cadasm\r10\rom\include\sys.h      ณVERS:1.1    ณTIPO: INCLUDE       บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤลฤฤฤฤฤฤฤฤฤฤฤฤมฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ AUTORE: Colombo Daniele                   ณDATA: Sun  09-12-1993  09:51:50  บ
ฬอออออออออออออออออออออออออออออออออออออออออออฯอออออออออออออออออออออออออออออออออน
บ INCLUDE:                                                                    บ
ฬอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออน
บ DESCRIZIONE: DESCRITTORI E DEFINIZIONI DI SISTEMA                           บ
บ Contiene:                                                                   บ
บ   - Definizione Variabili ed indirizzi di sistema                           บ
บ   - Macro accesso a campi descrittori                                       บ
บ   - Importazione Descrittore di sistema                                     บ
บ                                                                             บ
ศอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ
*/

#ifndef _SYS_

#define const		static
#define void        int

#define STRT_ADD        0X6000		/* Indirizzo memoria video */
#define CUR_ADD         STRT_ADD	

#define	TRUE 		0
#define FALSE		!TRUE
#define YES		1
#define NO 		0
#define ROM		0
#define RAM		1
#define RTNBAD  -1


\* Macro di testata per i comandi compatibile con la chiamata eseguita *\
\* dall'interprete *\

#define COMMAND(a)  a(numarg,tline) char numarg; LINE *tline;


#define CTRL(X)             (X-0x40)              /* control carattere                */
                                                  /* spiazza di OFFSET dalla BASE     */
#define ADDOFF(BASE,OFFSET) ((unsigned char *)((unsigned int)BASE+(unsigned int)OFFSET))
#define INIDESC(j,x,y)      {x.rnum=j;*(((char *)&x)+1)=y;}
#define LDbsy(x)            (*x) -> busy
#define LDptc(x)            (*x) -> ptchar
#define LDbuf(x)            (*x) -> buffer
#define LDpkl(x)            (*x) -> packlen


#define _SYS_

#ifndef _MAIN_
extern struct	STATE{
		unsigned state:1;		/* Stato macchina 0=S 1=U */
		unsigned ldp:1;			/* Load in progress =1	  */
		unsigned spare:6;
		unsigned char chspare;
        } sysdesc;              /* Descrittore di sistema */
extern unsigned int timmark;    /* Marca tempo            */
#endif
extern	int *AVAIL_;
#endif
