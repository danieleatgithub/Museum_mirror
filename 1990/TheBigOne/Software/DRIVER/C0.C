/*
浜様様様様様様様様様様様様様様様様様様様様様冤様様様様様用様様様様様様様様様様?
? FILE:c:\cadasm\r10\rom\driver\c0.c        ?VERS:1.1    ?TIPO: MODULO C      ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳田陳陳陳陳陳珍陳陳陳陳陳陳陳陳陳陳?
? AUTORE: Colombo Daniele                   ?DATA:                            ?
麺様様様様様様様様様様様様様様様様様様様様様詫様様様様様様様様様様様様様様様様?
? INCLUDE: stdio.h - stdlib.h - ctype.h - \cadasm\r10\rom\include\conio.h     ?
? \cadasm\r10\rom\include\io.h                                                ?
?                                                                             ?
麺様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
? FUNZIONI PUBBLICHE: wherex() - wherey() - gotoxy() - clrscr() - strupr()    ?
? strlwr()                                                                    ?
麺様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
? DESCRIZIONE: FUNZIONI DI LIBRERIA                                           ?
? Contiene le funzioni di utilita' per il video, la periferia e la            ?
? manipolazione delle stringhe                                                ?
?                                                                             ?
藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
*/

#include  <stdio.h>
#include  <stdlib.h>
#include  <ctype.h>
#include  "\cadasm\r10\rom\include\conio.h"
#include  "\cadasm\r10\rom\include\io.h"


/* --------------------- IMPORTAZIONI ------------------------*/                 
extern VIDEO video_desc;


/* ---------------------- CREAZIONI --------------------------*/
/*
浜様様様様様様様様様様様様様様様様様様様様様冤様様様様様様様様様様様様様様様様?
? FUNZIONE : WHEREX                         ?DATE: Sun  09-12-1993  10:35:36  ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳祖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? INPUT : Nessuno                                                             ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? OUTPUT : Posizione cursore asse X                                           ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? FUNZIONI CHIAMATE : Nessuna                                                 ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? DESCRIZIONE : Ritorna la posizione del cursore sull'asse X                  ?
藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
*/
unsigned char wherex()
{
return(video_desc.cur_x);
}
/*
浜様様様様様様様様様様様様様様様様様様様様様冤様様様様様様様様様様様様様様様様?
? FUNZIONE : WHEREY                         ?DATE: Sun  09-12-1993  10:35:36  ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳祖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? INPUT : Nessuno                                                             ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? OUTPUT : Posizione cursore asse Y                                           ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? FUNZIONI CHIAMATE : Nessuna                                                 ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? DESCRIZIONE : Ritorna la posizione del cursore sull'asse Y                  ?
藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
*/
unsigned char wherey()
{
return(video_desc.cur_y);
}
/*
浜様様様様様様様様様様様様様様様様様様様様様冤様様様様様様様様様様様様様様様様?
? FUNZIONE :GOTOXY                          ?DATE:Sun  09-12-1993  10:39:45   ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳祖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? INPUT : Char x posizione asse X - Char y posizione asse y                   ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? OUTPUT : Nessuno                                                            ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? FUNZIONI CHIAMATE : crtupdate()                                             ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? DESCRIZIONE : Posiziona il cursore alle coordinate specificate              ?
藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
*/
void gotoxy(x,y)
unsigned char x;
unsigned char y;
{
video_desc.cur_x=x;
video_desc.cur_y=y;
crt_update();
}
/*
浜様様様様様様様様様様様様様様様様様様様様様冤様様様様様様様様様様様様様様様様?
? FUNZIONE : CLRSCR                         ?DATE: Sun  09-12-1993  10:44:54  ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳祖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? INPUT : Nessuno                                                             ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? OUTPUT : Nessuno                                                            ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? FUNZIONI CHIAMATE : memset() - gotoxy()                                     ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? DESCRIZIONE : Clear dello schermo e cursore in alto a sinistra              ?
藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
*/
void clrscr()
{
memset((char *)video_desc.start_add,' ',MAXLINE*(MAXCOLUMN+1));
gotoxy(0,0);
}
/*
浜様様様様様様様様様様様様様様様様様様様様様冤様様様様様様様様様様様様様様様様?
? FUNZIONE :SAVEPOS                         ?DATE:Sun  09-26-1993  21:56:19   ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳祖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? INPUT : Nessuno                                                             ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? OUTPUT : Nessuno                                                            ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? FUNZIONI CHIAMATE : Nessuna                                                 ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? DESCRIZIONE : Salva la posizione corrente del cursore                       ?
藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
*/
void savepos()
{
video_desc.saved_x=video_desc.cur_x;
video_desc.saved_y=video_desc.cur_y;
}
/*
浜様様様様様様様様様様様様様様様様様様様様様冤様様様様様様様様様様様様様様様様?
? FUNZIONE :RESTOREPOS                      ?DATE:Sun  09-26-1993  21:56:19   ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳祖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? INPUT : Nessuno                                                             ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? OUTPUT : Nessuno                                                            ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? FUNZIONI CHIAMATE : crtupdate()                                             ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? DESCRIZIONE : Salva la posizione corrente del cursore                       ?
藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
*/
void restorepos()
{
video_desc.cur_x=video_desc.saved_x;
video_desc.cur_y=video_desc.saved_y;
crt_update();
}
/*
浜様様様様様様様様様様様様様様様様様様様様様冤様様様様様様様様様様様様様様様様?
? FUNZIONE : STRUPR                         ?DATE: Sun  09-12-1993  10:48:11  ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳祖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? INPUT : Puntatore alla stringa da convertire                                ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? OUTPUT : Puntatore alla stringa convertita                                  ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? FUNZIONI CHIAMATE : toupper()                                               ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? DESCRIZIONE : Converte in maiuscolo tutti i caratteri ascii della stringa   ?
? sino al terminatore NULL e torna il puntatore passato alla funzione         ?
藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
*/

char *strupr(string)
char *string;
{
char *str=string;      				      	/* Salvo il puntatore alla stringa */
do{
 *string=toupper(*string++);
 }while(*string!=NULL);					/* la stringa non e' finita */
return(str);
}
/*
浜様様様様様様様様様様様様様様様様様様様様様冤様様様様様様様様様様様様様様様様?
? FUNZIONE : STRLWR                         ?DATE: Sun  09-12-1993  10:48:11  ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳祖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? INPUT : Puntatore alla stringa da convertire                                ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? OUTPUT : Puntatore alla stringa convertita                                  ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? FUNZIONI CHIAMATE : tolower()                                               ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? DESCRIZIONE : Converte in minuscolo tutti i caratteri ascii della stringa   ?
? sino al terminatore NULL e torna il puntatore passato alla funzione         ?
藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
*/

char *strlwr(string)
char *string;
{
char *str=string;      				      	/* Salvo il puntatore alla stringa */
do{
 *string=tolower(*string++);
 }while(*string!=NULL);					/* la stringa non e' finita */
return(str);
}

