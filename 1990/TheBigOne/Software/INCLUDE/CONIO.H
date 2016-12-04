/*
ษอออออออออออออออออออออออออออออออออออออออออออัออออออออออออัออออออออออออออออออออป
บ FILE:c:\cadasm\r10\rom\include\conio.h    ณVERS:1.1    ณTIPO: INCLUDE       บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤลฤฤฤฤฤฤฤฤฤฤฤฤมฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ AUTORE: Colombo Daniele                   ณDATA: Sun  09-12-1993  09:43:13  บ
ฬอออออออออออออออออออออออออออออออออออออออออออฯอออออออออออออออออออออออออออออออออน
บ INCLUDE: \CADASM\R10\ROM\INCLUDE\SYS.H                                      บ
บ                                                                             บ
ฬอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออน
บ DESCRIZIONE: DESCRITTORI E DEFINIZIONI DI INTERFACCIA CON SCHERMO E         บ
บ              TASTIERA                                                       บ
บ Contiene:                                                                   บ
บ   - Definizioni e descrittori video                                         บ
บ   - Descrittori linea monitor                                               บ
บ   - Descrittori Database e link comandi monitor                             บ
บ   - Importazioni funzioni di utilitita'                                     บ
บ                                                                             บ
ศอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ
*/

#ifndef _SYS_
#include  "\cadasm\r10\rom\include\sys.h"
#endif

#define BLOCK           0X00		/* Cursore tipo block */
#define NOCURSOR        0X20		/* Nessun cursore */
#define FASTBLINK       0X40		/* Cursore a blink veloce */
#define SLOWBLINK       0X60		/* Cursore a blink lento */

#define MAXLINE         25		/* Numero massimo di linee di schermo */
#define MAXCOLUMN       40		/* Numero massimo di colonne di schermo */
#define MAXVIEW         8       /* Numero di byte stampati su una linea */
#define DEBPROMPT       '>'     /* Prompt debugger */
#define OVERSTRIKE      0
#define INSERT          !OVERSTRIKE
#define HISTOFF         0       /* La linea richiamata con history non e' stata modificata */
#define HISTON          1       /* La linea richiamata con history e'     stata modificata */
#define NXT             1
#define PRV             2

#define MAXLENCMD       40      /* Lunghezza buffer comandi */
#define MAXNAME         10      /* Lunghezza massimo nome comando RIFERIMENTO ANCHE IN SYS.SRC*/
#define MAXPAR          10      /* Numero massimo parametri */
#define MAXCOM          22      /* Numero massimo comandi */
#define MAXHIST         15      /* Numero buffer di history */
#define NONE            0       /* tipo parametro   */
#define NUM             1
#define STR             2
#define LOWER           1
#define UPPER           2





#define DELETE          0x7F            /* Delete        */
#define BELL            0x7             /* Bell          */
#define U_ARR           0x11            /* Up arrow      */
#define D_ARR           0x10            /* Down arrow    */
#define L_ARR           0xF             /* Left arrow    */
#define R_ARR           0xE             /* Right arrow   */

#define home		{gotoxy(0,0)}


typedef struct{
	unsigned char cur_x;            /* posizione cursore asse x */
	unsigned char cur_y;            /* posizione cursore asse y */
    unsigned char cstyle;           /* stile cursore            */
    unsigned char prompt;           /* carattere prompt         */
    unsigned int  start_add;        /* Inizio pagina video      */
    unsigned int  curs_add;         /* puntatore cursore        */
    unsigned char saved_x;          /* save posizione    asse x */
    unsigned char saved_y;          /* save posizione    asse y */
    }VIDEO;                         /* DESCRITTORE SCHERMO      */

typedef struct{
    unsigned char   key;            /* carattere                    */
    unsigned char   mode;           /* mode insert/overstrike       */
    unsigned char   base;           /* base attiva                  */
    unsigned char   strbase[3];     /* stringa base                 */
    unsigned char   stateflag;      /* Flag di stato editor linea   */
    unsigned char   *buffer;        /* buffer di caratteri          */
	unsigned char   *ptrchar;       /* puntatore cursore nel buffer */
    unsigned char   *ptreol;        /* puntatore fine linea         */
    char            addmode[10];    /* Stringa output indirizzo     */
    char            datamode[10];   /* Stringa output byte          */
    }LINE;                          /* DESCRITTORE EDITOR DI LINEA  */

typedef struct {
    char            *name;          /* nome comando                 */
    unsigned char   type[MAXPAR+1]; /* tipo parametro               */
    unsigned char   minpar;         /* Numero minimo  di parametri  */
    }COMDB;                         /* DESCRITTORE DB COMANDI MML   */

typedef struct {
    char    name[MAXNAME];          /* Nome del comando             */
    unsigned int param[MAXPAR];     /* Parametri                    */
    int (*function)();              /* Indirizzo del comando        */
    }CMD;                           /* DESCRITTORE ULTIMO COMANDO   */

typedef struct HISTOR_T{
    char   buffer[MAXLENCMD];       /* Buffer di history comando    */
    struct HISTOR_T  *prev;           /* Precedente buffer nella lista*/
    struct HISTOR_T  *next;           /* Prossimo buffer nella lista  */
    }HISTOR;                          /* BUFFER HISTORY               */


extern  int getch();
extern  char kbhit(),rdregadd();
extern  char *strupr();
extern  unsigned char cvhex(),wherex(),wherey();
extern  void gotoxy(),clrscr(),savepos(),restorepos();

