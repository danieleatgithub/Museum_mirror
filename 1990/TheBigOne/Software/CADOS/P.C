/*
ษอออออออออออออออออออออออออออออออออออออออออออัออออออออออออัออออออออออออออออออออป
บ FILE:\CADASM\R10\ROM\CADOS\P.C            ณVERS:1.1    ณTIPO: MODULO C      บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤลฤฤฤฤฤฤฤฤฤฤฤฤมฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ AUTORE: Colombo Daniele                   ณDATA: Sun  09-12-1993  11:25:43  บ
ฬอออออออออออออออออออออออออออออออออออออออออออฯอออออออออออออออออออออออออออออออออน
บ INCLUDE: \cadasm\r10\rom\include\conio.h  - \cadasm\r10\rom\include\error.h บ
ฬอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออน
บ FUNZIONI PUBBLICHE: main()                                                  บ
ฬอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออน
บ DESCRIZIONE: MODULO DI PARTENZA                                             บ
บ Creazioni di:                                                               บ
บ - Descrittore di stato del sistema                                          บ
บ - Descrittore del frame di utente                                           บ
บ - Marca tempo                                                               บ
ศอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ
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
ษอออออออออออออออออออออออออออออออออออออออออออัอออออออออออออออออออออออออออออออออป
บ FUNZIONE : MAIN()                         ณDATE: Sun  09-12-1993  11:30:08  บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤมฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ INPUT : Nessuno                                                             บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ OUTPUT : Nessuno                                                            บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ FUNZIONI CHIAMATE : iniram() - iniscr() - initio() - ei() - monitor()       บ
บ inibreak() - clrscr() - printf() - vers()                                   บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ DESCRIZIONE : PARTENZA DEL SISTEMA                                          บ
ศอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ
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