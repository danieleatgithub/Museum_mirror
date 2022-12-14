/*
浜様様様様様様様様様様様様様様様様様様様様様冤様様様様様用様様様様様様様様様様?
? FILE:\CADASM\R10\ROM\CADOS\P.C            ?VERS:1.1    ?TIPO: MODULO C      ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳田陳陳陳陳陳珍陳陳陳陳陳陳陳陳陳陳?
? AUTORE: Colombo Daniele                   ?DATA: Sun  09-12-1993  11:25:43  ?
麺様様様様様様様様様様様様様様様様様様様様様詫様様様様様様様様様様様様様様様様?
? INCLUDE: \cadasm\r10\rom\include\conio.h  - \cadasm\r10\rom\include\error.h ?
麺様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
? FUNZIONI PUBBLICHE: main()                                                  ?
麺様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
? DESCRIZIONE: MODULO DI PARTENZA                                             ?
? Creazioni di:                                                               ?
? - Descrittore di stato del sistema                                          ?
? - Descrittore del frame di utente                                           ?
? - Marca tempo                                                               ?
藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
*/

#define     _MAIN_
#include  <stdio.h>
#include  "\cadasm\r10\rom\include\conio.h"
#include  "\cadasm\r10\rom\include\error.h"


/* --------------------- IMPORTAZIONI ------------------------*/

extern LINE     monline;    /* DESCRITTORE EDITOR DI LINEA             */
extern VIDEO    video_desc; /* DESCRITTORE SCHERMO                     */

/* ----------------------- CREAZIONI -------------------------*/

struct	STATE{
		unsigned state:1;		/* Stato macchina 0=S 1=U */
		unsigned ldp:1;			/* Load in progress =1	  */
		unsigned bbusy:1;		/* Rx current buffer busy */
		unsigned spare:5;
		unsigned char chspare;
		unsigned int ldlen;		/* Total lenght loaded	  */
        } sysdesc;              /* DESCRITTORE DI SISTEMA */


unsigned int timmark;              /* Marca tempo            */
/*
浜様様様様様様様様様様様様様様様様様様様様様冤様様様様様様様様様様様様様様様様?
? FUNZIONE : MAIN()                         ?DATE: Sun  09-12-1993  11:30:08  ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳祖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? INPUT : Nessuno                                                             ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? OUTPUT : Nessuno                                                            ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? FUNZIONI CHIAMATE : iniram() - iniscr() - initio() - ei() - monitor()       ?
? inibreak() - clrscr() - printf() - vers()                                   ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? DESCRIZIONE : PARTENZA DEL SISTEMA                                          ?
藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
*/
main()
{
iniram();
inistr();
iniscr();
initio();
inibreak();
ei();
clrscr();
printf("SISTEMA DI SVILUPPO CAD_V4");
vers(1,&monline);
putchar(video_desc.prompt);
monitor(&monline);
}
