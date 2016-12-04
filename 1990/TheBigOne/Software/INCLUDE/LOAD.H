/*
ษอออออออออออออออออออออออออออออออออออออออออออัออออออออออออัออออออออออออออออออออป
บ FILE:c:\cadasm\r10\rom\include\load.h     ณVERS:1.1    ณTIPO: INCLUDE       บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤลฤฤฤฤฤฤฤฤฤฤฤฤมฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ AUTORE: Colombo Daniele                   ณDATA:Sun  09-12-1993  10:00:33   บ
ฬอออออออออออออออออออออออออออออออออออออออออออฯอออออออออออออออออออออออออออออออออน
บ INCLUDE:                                                                    บ
ฬอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออน
บ DESCRIZIONE: DESCRITTORI DEFINIZIONI E IMPORTAZIONE PUNTATORI PER LA        บ
บ              FUNZIONE DI CARICAMENTO                                        บ
บ Contiene:                                                                   บ
บ   - Definizioni tipi di record                                              บ
บ   - Descrittore buffer ricezione pacchetto                                  บ
บ   - Descrittore di stato del caricamento                                    บ
บ   - Descrittore di conversione pacchetto                                    บ
บ   - Importazione array e puntatori buffer di caricamento                    บ
บ                                                                             บ
ศอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ
*/

#define MAXBUF      24              /* Numero di buffer per il caricamento  */
#define SMAXLEN     74              /* Massima lunghezza S-RECORD           */

#define HEADER		'0'
#define DATA		'1'
#define SYMBOL		'6'
#define TERMINATOR	'9'

typedef	struct	{
        unsigned char   busy;       /* Flag buffer busy             */
        unsigned char   spare;      /* Spare                        */
        char            *ptchar;    /* Puntatore prossimo carattere */
        char            *buffer;    /* Puntatore inizio buffer      */
        unsigned char   packlen;    /* Contatore Byte ricevuti      */
        }LDBUF;                     /* DESCRITTORE BUFFER RX PACCHETTO */

typedef struct  {
        char            stpflag;    /* trasmitter stopped     */
        char            busycount;  /* contatore buffer pieni */
        unsigned int    ldlen;      /* Total lenght loaded    */
        unsigned char   *offset;    /* offset load            */
        char            name[20];   /* File name in load      */
        char            type[3];    /* file type              */
        unsigned int    parer;      /* Errori di parita       */
        unsigned int    gener;      /* Errori generici        */
        }LDSTAT;                    /* DESCRITTORE DI STATO CARICAMENTO */

typedef struct	{
        char            *src;    /* Puntatore alla stringa da convertire    */
        unsigned char   *dest;   /* Puntatore all'indirizzo di destinazione */
        int             lenght;  /* Numero di byte da convertire            */
        unsigned char   cksum;   /* Record checksum                         */
        }HIT_REC;                /* DESCRITTORE CONVERSIONE S RECORD        */

extern LDSTAT   loadstat;
extern LDBUF    loadbuf[MAXBUF];    /* Array di descrittori buffer di load                */
extern LDBUF    *ptbuf[MAXBUF+1];   /* Array di puntatori a descrittori buffer di load    */
extern LDBUF    **busybuf;          /* PUNTATORE a puntatore buffer corrente pieno        */
extern LDBUF    **freebuf;          /* PUNTATORE a puntatore buffer corrente vuoto        */
extern char     convhrec();         /* Funzione asm di conversione h_record               */
extern char     convhrecf();        /* Funzione asm di conversione h_record con flip byte */
extern char     cktest();           /* Funzione asm di controllo checksum                 */
