/*
浜様様様様様様様様様様様様様様様様様様様様様冤様様様様様用様様様様様様様様様様?
? FILE:\CADASM\R10\ROM\COMMAND\READ.C       ?VERS:1.1    ?TIPO: MODULO C      ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳田陳陳陳陳陳珍陳陳陳陳陳陳陳陳陳陳?
? AUTORE: Colombo Daniele                   ?DATA: Sun  09-26-1993  10:31:13  ?
麺様様様様様様様様様様様様様様様様様様様様様詫様様様様様様様様様様様様様様様様?
? INCLUDE: stdio.h - \cadasm\r10\rom\include\conio.h                          ?
麺様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
? FUNZIONI PUBBLICHE: read() - rdport()                                       ?
麺様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
? DESCRIZIONE: MODULO PER COMANDI DI LETTURA                                  ?
? Creazioni di :                                                              ?
?                                                                             ?
藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
*/
#include  <stdio.h>                        
#include  "\cadasm\r10\rom\include\conio.h"

#define     ADDPRINT    5
#define     ASCPOS      (MAXVIEW*3)+ADDPRINT+2

/* --------------------- IMPORTAZIONI ------------------------*/
extern CMD com;              /* DESCRITTORE ULTIMO COMANDO   */

/* --------------------- CREAZIONI ------------------------*/

unsigned int prline();

/*
浜様様様様様様様様様様様様様様様様様様様様様冤様様様様様様様様様様様様様様様様?
? FUNZIONE : READ                           ?DATE: Sun  09-26-1993  10:43:18  ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳祖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? FUNZIONI CHIAMATE : printf() - prline()                                     ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? DESCRIZIONE : comando mml per la lettura in memoria, legge il numero di     ?
? byte richiesto arrotondato a otto                                           ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? SINTASSI COMANDO:                                                           ?
? READ  [address] [numbyte]  : Legge [numbyte] a partire dall'indirizzo       ?
?                              [address]                                      ?
藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
*/
       
COMMAND(read)
{
unsigned int nline;
nline=com.param[2]/MAXVIEW+1;       /* Numero di linee da stampare */
printf("\n\r");
do{
    com.param[1]=prline((unsigned char *)com.param[1],tline); /* stampo una linea */
    --nline;
}while(nline);                    /* continuo se ci sono ancora altre linee */
return(TRUE);
}
/*
浜様様様様様様様様様様様様様様様様様様様様様冤様様様様様様様様様様様様様様様様?
? FUNZIONE : RDPORT                         ?DATE: Sun  09-26-1993  22:29:49  ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳祖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? FUNZIONI CHIAMATE : printf() - rdregadd() - readb() - putchar()             ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? DESCRIZIONE : comando mml per la lettura di una porta                       ?
?                                                                             ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? SINTASSI COMANDO:                                                           ?
? RDPORT [address] [niter]   : Legge [niter] volte il dato sulla porta        ?
?                              [address]                                      ?
? RDPORT [address] [niter] [Intreg] : Legge [niter] volte il dato sul         ?
? registro interno [Intreg] della porta [Address]                             ?
藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
*/

COMMAND(rdport)
{
register int i;
char tmp;

i=com.param[2];
printf("/r/n");
for(;i;--i)                                 /* Loop di niter letture  */
{
    printf("PORT:");
    printf(tline -> addmode,com.param[1]);  /* Stampa indirizzo porta */
    printf(" VALUE:");
    if(numarg>2) tmp= rdregadd(com.param[1],(unsigned char)com.param[3]);
    else  readb(tmp,1,com.param[1]);

    printf(tline -> datamode,tmp);          /* Stampa byte            */
    if(tmp< 31 || tmp > 127) tmp='.';                    /* Se il byte e' < spazio codifico acii in un . */
    putchar('[');
    putchar(tmp);
    printf("]\n\r");                        /* Stampo la codifica ascii */
}
return(TRUE);
}
/*
浜様様様様様様様様様様様様様様様様様様様様様冤様様様様様様様様様様様様様様様様?
? FUNZIONE : PRLINE                         ?DATE: Sun  09-26-1993  13:08:27  ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳祖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? INPUT : Puntatore al primo byte dei sedici da stampare e descrittore linea  ?
?         di editing                                                          ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? OUTPUT : Puntatore al prossimo carattere castato ad intero                  ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? FUNZIONI CHIAMATE : printf() - gotoxy() - wherey() - savepos()              ?
? restorepos()                                                                ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? DESCRIZIONE : Stampa su una linea il valore degli 8 byte dall'indirizzo     ?
? passato nella base corrente ed il corrispondente carattere ascii e torna    ?
? a capo                                                                      ?
藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
*/
unsigned int prline(address,tline)
unsigned char *address;
LINE *tline;
{
register char i;
int asciipos;
char tmp;

asciipos=ASCPOS;
printf(tline -> addmode,address);               /* Stampa indirizzo */
for(i=0 ; i<MAXVIEW ;++i,++address)             /* loop di stampa incremento puntatore e contatore */
    {
        printf(tline -> datamode,*address);     /* Stampa byte */
        if(tline -> base == 16)
        {
            savepos();
            gotoxy(asciipos,wherey());       /* Se attiva base 16 */
            if(*address > 31 && *address < 128) tmp=*address;
            else tmp='.';                       /* Se il byte e' < spazio codifico acii in un . */
            putchar(tmp);                       /* Stampo la codifica ascii */
            restorepos();                       /* Riposiziono il cursore */
            ++asciipos;
        }
    }
printf("\n\r");
return((unsigned int)address);
}
