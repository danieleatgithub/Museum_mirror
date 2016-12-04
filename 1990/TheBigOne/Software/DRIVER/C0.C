/*
�����������������������������������������������������������������������������ͻ
� FILE:c:\cadasm\r10\rom\driver\c0.c        �VERS:1.1    �TIPO: MODULO C      �
�����������������������������������������������������������������������������Ķ
� AUTORE: Colombo Daniele                   �DATA:                            �
�����������������������������������������������������������������������������͹
� INCLUDE: stdio.h - stdlib.h - ctype.h - \cadasm\r10\rom\include\conio.h     �
� \cadasm\r10\rom\include\io.h                                                �
�                                                                             �
�����������������������������������������������������������������������������͹
� FUNZIONI PUBBLICHE: wherex() - wherey() - gotoxy() - clrscr() - strupr()    �
� strlwr()                                                                    �
�����������������������������������������������������������������������������͹
� DESCRIZIONE: FUNZIONI DI LIBRERIA                                           �
� Contiene le funzioni di utilita' per il video, la periferia e la            �
� manipolazione delle stringhe                                                �
�                                                                             �
�����������������������������������������������������������������������������ͼ
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
�����������������������������������������������������������������������������ͻ
� FUNZIONE : WHEREX                         �DATE: Sun  09-12-1993  10:35:36  �
�����������������������������������������������������������������������������Ķ
� INPUT : Nessuno                                                             �
�����������������������������������������������������������������������������Ķ
� OUTPUT : Posizione cursore asse X                                           �
�����������������������������������������������������������������������������Ķ
� FUNZIONI CHIAMATE : Nessuna                                                 �
�����������������������������������������������������������������������������Ķ
� DESCRIZIONE : Ritorna la posizione del cursore sull'asse X                  �
�����������������������������������������������������������������������������ͼ
*/
unsigned char wherex()
{
return(video_desc.cur_x);
}
/*
�����������������������������������������������������������������������������ͻ
� FUNZIONE : WHEREY                         �DATE: Sun  09-12-1993  10:35:36  �
�����������������������������������������������������������������������������Ķ
� INPUT : Nessuno                                                             �
�����������������������������������������������������������������������������Ķ
� OUTPUT : Posizione cursore asse Y                                           �
�����������������������������������������������������������������������������Ķ
� FUNZIONI CHIAMATE : Nessuna                                                 �
�����������������������������������������������������������������������������Ķ
� DESCRIZIONE : Ritorna la posizione del cursore sull'asse Y                  �
�����������������������������������������������������������������������������ͼ
*/
unsigned char wherey()
{
return(video_desc.cur_y);
}
/*
�����������������������������������������������������������������������������ͻ
� FUNZIONE :GOTOXY                          �DATE:Sun  09-12-1993  10:39:45   �
�����������������������������������������������������������������������������Ķ
� INPUT : Char x posizione asse X - Char y posizione asse y                   �
�����������������������������������������������������������������������������Ķ
� OUTPUT : Nessuno                                                            �
�����������������������������������������������������������������������������Ķ
� FUNZIONI CHIAMATE : crtupdate()                                             �
�����������������������������������������������������������������������������Ķ
� DESCRIZIONE : Posiziona il cursore alle coordinate specificate              �
�����������������������������������������������������������������������������ͼ
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
�����������������������������������������������������������������������������ͻ
� FUNZIONE : CLRSCR                         �DATE: Sun  09-12-1993  10:44:54  �
�����������������������������������������������������������������������������Ķ
� INPUT : Nessuno                                                             �
�����������������������������������������������������������������������������Ķ
� OUTPUT : Nessuno                                                            �
�����������������������������������������������������������������������������Ķ
� FUNZIONI CHIAMATE : memset() - gotoxy()                                     �
�����������������������������������������������������������������������������Ķ
� DESCRIZIONE : Clear dello schermo e cursore in alto a sinistra              �
�����������������������������������������������������������������������������ͼ
*/
void clrscr()
{
memset((char *)video_desc.start_add,' ',MAXLINE*(MAXCOLUMN+1));
gotoxy(0,0);
}
/*
�����������������������������������������������������������������������������ͻ
� FUNZIONE :SAVEPOS                         �DATE:Sun  09-26-1993  21:56:19   �
�����������������������������������������������������������������������������Ķ
� INPUT : Nessuno                                                             �
�����������������������������������������������������������������������������Ķ
� OUTPUT : Nessuno                                                            �
�����������������������������������������������������������������������������Ķ
� FUNZIONI CHIAMATE : Nessuna                                                 �
�����������������������������������������������������������������������������Ķ
� DESCRIZIONE : Salva la posizione corrente del cursore                       �
�����������������������������������������������������������������������������ͼ
*/
void savepos()
{
video_desc.saved_x=video_desc.cur_x;
video_desc.saved_y=video_desc.cur_y;
}
/*
�����������������������������������������������������������������������������ͻ
� FUNZIONE :RESTOREPOS                      �DATE:Sun  09-26-1993  21:56:19   �
�����������������������������������������������������������������������������Ķ
� INPUT : Nessuno                                                             �
�����������������������������������������������������������������������������Ķ
� OUTPUT : Nessuno                                                            �
�����������������������������������������������������������������������������Ķ
� FUNZIONI CHIAMATE : crtupdate()                                             �
�����������������������������������������������������������������������������Ķ
� DESCRIZIONE : Salva la posizione corrente del cursore                       �
�����������������������������������������������������������������������������ͼ
*/
void restorepos()
{
video_desc.cur_x=video_desc.saved_x;
video_desc.cur_y=video_desc.saved_y;
crt_update();
}
/*
�����������������������������������������������������������������������������ͻ
� FUNZIONE : STRUPR                         �DATE: Sun  09-12-1993  10:48:11  �
�����������������������������������������������������������������������������Ķ
� INPUT : Puntatore alla stringa da convertire                                �
�����������������������������������������������������������������������������Ķ
� OUTPUT : Puntatore alla stringa convertita                                  �
�����������������������������������������������������������������������������Ķ
� FUNZIONI CHIAMATE : toupper()                                               �
�����������������������������������������������������������������������������Ķ
� DESCRIZIONE : Converte in maiuscolo tutti i caratteri ascii della stringa   �
� sino al terminatore NULL e torna il puntatore passato alla funzione         �
�����������������������������������������������������������������������������ͼ
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
�����������������������������������������������������������������������������ͻ
� FUNZIONE : STRLWR                         �DATE: Sun  09-12-1993  10:48:11  �
�����������������������������������������������������������������������������Ķ
� INPUT : Puntatore alla stringa da convertire                                �
�����������������������������������������������������������������������������Ķ
� OUTPUT : Puntatore alla stringa convertita                                  �
�����������������������������������������������������������������������������Ķ
� FUNZIONI CHIAMATE : tolower()                                               �
�����������������������������������������������������������������������������Ķ
� DESCRIZIONE : Converte in minuscolo tutti i caratteri ascii della stringa   �
� sino al terminatore NULL e torna il puntatore passato alla funzione         �
�����������������������������������������������������������������������������ͼ
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