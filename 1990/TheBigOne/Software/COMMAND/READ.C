/*
ษอออออออออออออออออออออออออออออออออออออออออออัออออออออออออัออออออออออออออออออออป
บ FILE:\CADASM\R10\ROM\COMMAND\READ.C       ณVERS:1.1    ณTIPO: MODULO C      บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤลฤฤฤฤฤฤฤฤฤฤฤฤมฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ AUTORE: Colombo Daniele                   ณDATA: Sun  09-26-1993  10:31:13  บ
ฬอออออออออออออออออออออออออออออออออออออออออออฯอออออออออออออออออออออออออออออออออน
บ INCLUDE: stdio.h - \cadasm\r10\rom\include\conio.h                          บ
ฬอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออน
บ FUNZIONI PUBBLICHE: read() - rdport()                                       บ
ฬอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออน
บ DESCRIZIONE: MODULO PER COMANDI DI LETTURA                                  บ
บ Creazioni di :                                                              บ
บ                                                                             บ
ศอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ
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
ษอออออออออออออออออออออออออออออออออออออออออออัอออออออออออออออออออออออออออออออออป
บ FUNZIONE : READ                           ณDATE: Sun  09-26-1993  10:43:18  บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤมฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ FUNZIONI CHIAMATE : printf() - prline()                                     บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ DESCRIZIONE : comando mml per la lettura in memoria, legge il numero di     บ
บ byte richiesto arrotondato a otto                                           บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ SINTASSI COMANDO:                                                           บ
บ READ  [address] [numbyte]  : Legge [numbyte] a partire dall'indirizzo       บ
บ                              [address]                                      บ
ศอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ
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
ษอออออออออออออออออออออออออออออออออออออออออออัอออออออออออออออออออออออออออออออออป
บ FUNZIONE : RDPORT                         ณDATE: Sun  09-26-1993  22:29:49  บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤมฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ FUNZIONI CHIAMATE : printf() - rdregadd() - readb() - putchar()             บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ DESCRIZIONE : comando mml per la lettura di una porta                       บ
บ                                                                             บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ SINTASSI COMANDO:                                                           บ
บ RDPORT [address] [niter]   : Legge [niter] volte il dato sulla porta        บ
บ                              [address]                                      บ
บ RDPORT [address] [niter] [Intreg] : Legge [niter] volte il dato sul         บ
บ registro interno [Intreg] della porta [Address]                             บ
ศอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ
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
ษอออออออออออออออออออออออออออออออออออออออออออัอออออออออออออออออออออออออออออออออป
บ FUNZIONE : PRLINE                         ณDATE: Sun  09-26-1993  13:08:27  บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤมฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ INPUT : Puntatore al primo byte dei sedici da stampare e descrittore linea  บ
บ         di editing                                                          บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ OUTPUT : Puntatore al prossimo carattere castato ad intero                  บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ FUNZIONI CHIAMATE : printf() - gotoxy() - wherey() - savepos()              บ
บ restorepos()                                                                บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ DESCRIZIONE : Stampa su una linea il valore degli 8 byte dall'indirizzo     บ
บ passato nella base corrente ed il corrispondente carattere ascii e torna    บ
บ a capo                                                                      บ
ศอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ
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