/*
浜様様様様様様様様様様様様様様様様様様様様様冤様様様様様用様様様様様様様様様様?
? FILE:\CADASM\R10\ROM\CADOS\COMMAND.C      ?VERS:1.1    ?TIPO:MODULO C       ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳田陳陳陳陳陳珍陳陳陳陳陳陳陳陳陳陳?
? AUTORE: Colombo Daniele                   ?DATA: Sun  09-12-1993  12:34:29  ?
麺様様様様様様様様様様様様様様様様様様様様様詫様様様様様様様様様様様様様様様様?
? INCLUDE: stdio.h - stdlib.h - \cadasm\r10\rom\include\conio.h               ?
麺様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
? FUNZIONI PUBBLICHE: edlin() - refrline() - eraseline() - flushbuf()         ?
? gethist()                                                                   ?
麺様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
? DESCRIZIONE: GESTIONE LINEA COMANDI                                         ?
? Creazioni:                                                                  ?
?   - Stringhe base numerica                                                  ?
藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
*/

#include  <stdio.h>
#include  <stdlib.h>
#include  "\cadasm\r10\rom\include\conio.h"



/* --------------------- IMPORTAZIONI ------------------------*/     
extern VIDEO    video_desc;            /* DESCRITTORE SCHERMO          */
extern char     curline[MAXLENCMD];    /* Buffer comando in editing    */
extern HISTOR   history[MAXHIST];      /* Array buffer di history comando    */
extern HISTOR   *wrhist;               /* Puntatore scrittura buffer history   */
extern HISTOR   *rdhist;               /* Puntatore lettura buffer history */

/* ----------------------- CREAZIONI -------------------------*/

const char hex[3]="%x";           /* Stringa base 16 */
const char oct[3]="%o";           /* Stringa base  8 */
const char dec[3]="%d";           /* Stringa base 10 */

HISTOR *gethist();
/*
浜様様様様様様様様様様様様様様様様様様様様様冤様様様様様様様様様様様様様様様様?
? FUNZIONE : EDLIN                          ?DATE:Sun  09-12-1993  12:41:16   ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳祖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? INPUT : Puntatore a descrittore di tipo LINE                                ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? OUTPUT : TRUE se non e' stato premuto il tasto return o il puntatore al     ?
? buffer contenente la stringa in linea confermata con il tasto return        ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? FUNZIONI CHIAMATE : strlen() - wherey() - gotoxy() - putchar() - refrline() ?
? eraseline() - memclr() - strcpy() - wherex() - gethist() - clrscr()         ?
? memset()                                                                    ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? DESCRIZIONE: Gestisce  l'editor  di  linea  ricevendo  il  carattere nella  ?
? struttura di tipo LINE, aggiorna il buffer   e la riga di schermo, gestisce ?
? i seguenti comandi comandi di editing:                                      ?
? 崢陳陳陳陳陳堕陳陳陳陳陳陳賃陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳? ?
? ? TASTO     ? COMANDO      ?      AZIONE                                  ? ?
? 把陳陳陳陳陳田陳陳陳陳陳陳津陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳? ?
? ?(ctrl H)   ? BACKSPACE    ? Cancella il carattere precedente             ? ?
? ?           ? DELETE       ? Cancella il carattere corrente               ? ?
? ?           ? TAB          ? Cursore a fine linea                         ? ?
? ?(ctrl A)   ? INS/OVS      ? Toggle modo insert overstrike                ? ?
? ?(Left arr) ? LEFT ARROW   ? Cursore a sinistra di una posizione          ? ?
? ?(Right arr)? RIGHT ARROW  ? Cursore a destra di una posizione            ? ?
? ?(up   arr) ? PREV HISTORY ? Comando precedente nel buffer di history     ? ?
? ?(down  arr)? NEXT HISTORY ? Prossimo comando nel buffer di history       ? ?
? ?(ctrl V)   ? HISTORY      ? Elenco dei comandi nel buffer di history     ? ?
? ?(ctrl W)   ? CLEAR        ? Cancella lo schermo e riscrive la linea      ? ?
? ?(ctrl C)   ?  ----------  ? Non implementato (Previsto BREAK)            ? ?
? ?(ctrl R)   ? REFRESH      ? Refresh della linea                          ? ?
? ?(ctrl U)   ? ERASE        ? Cancella la linea                            ? ?
? ?(ctrl J)   ? HOME         ? Cursore a inizio riga                        ? ?
? ?(ctrl B)   ? BASE         ? Cambia base da 10 a 16 e viceversa           ? ?
? 喞陳陳陳陳陳祖陳陳陳陳陳陳珍陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳? ?
藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
*/

char *edlin(tline)
LINE 	*tline;
{
HISTOR *tptr;
register unsigned char *tmp;
register int i;
switch(tline -> key)                                                    /* Test carattere speciale per editor */
    {
    case '\b':          /* TASTO BACKSPACE */

      if(tline -> ptrchar != tline -> buffer)                           /* non e' all'inizio del buffer */
		   {
           tline -> stateflag = HISTON;
           for(tmp = tline -> ptrchar;tmp <= tline -> ptreol;++tmp)
            *(tmp-1)=*tmp;                                              /* Cancello il carattere precedente */
		   --tline -> ptreol;
		   --tline -> ptrchar;
		   refrline(tline);
		   }
      else                                                              /* Altrimenti Beep di errore */
		   putchar(BELL);
		break;

    case DELETE:      /* TASTO DELETE */
        if(tline -> ptrchar != tline -> ptreol)                         /* non e' a fine linea */
			{
            tline -> stateflag = HISTON;
            for(tmp = tline -> ptrchar;tmp <= tline -> ptreol;++tmp)
                *tmp=*(tmp+1);                                          /* cancello carattere corrente */
			--tline -> ptreol;
			refrline(tline);
			}
		break;
    case '\r':      /* TASTO RETURN */
        if (strlen(tline -> buffer) > 1) {
            if (tline -> stateflag == HISTON ) {
                strcpy(wrhist -> buffer,tline -> buffer);
                wrhist = wrhist -> next;
                memclr(wrhist -> buffer,MAXLENCMD-1);
            }
            else {
                rdhist -> prev -> next = rdhist -> next;
                rdhist -> next -> prev = rdhist -> prev;
                wrhist -> prev -> next = rdhist;
                rdhist -> prev = wrhist -> prev;
                rdhist -> next = wrhist;
                wrhist -> prev = rdhist;
            }
        }
        rdhist=wrhist;
        return(tline -> buffer);                                /* Ritorno il puntatore al buffer con il comando */
		break;
    case '\t':      /* TASTO TAB */
        tline -> ptrchar = tline -> ptreol;                     /* Posiziono il cursore a fine linea */
		gotoxy(strlen(tline -> buffer)+1,wherey());
		break;
    case CTRL('A') :    /* TASTO CTRL-A */
      tline -> mode = !(tline -> mode);                         /* Toggle ins/overstrike */
          break;
    case L_ARR:         /* TASTO LEFT ARROW */
      if(tline -> ptrchar != tline -> buffer)                   /* non e' all'inizio del buffer */
		{
        tline -> ptrchar--;                                     /* Posiziono il cursore al carattere precedente */
		gotoxy(wherex()-1,wherey());
		}
		break;
    case R_ARR:         /* TASTO RIGHT ARROW */
      if(tline -> ptrchar != tline -> ptreol)                   /* non e' alla fine del buffer */
		{
        tline -> ptrchar++;                                     /* Posiziono il cursore al carattere successivo */
		gotoxy(wherex()+1,wherey());
		}
                break;
    case U_ARR:     /* TASTO UP ARROW    */
        tline -> stateflag = HISTOFF;
        rdhist=gethist(tline,rdhist,PRV);
        break;
    case D_ARR:     /* TASTO DOWN ARROW  */
        tline -> stateflag = HISTOFF;
        rdhist=gethist(tline,rdhist,NXT);
        break;
    case CTRL('V'): /* TASTO CTRL-V */
        tptr=wrhist -> next;
        for(i=1;i<MAXHIST;++i) {
            printf("\r\n%d: %s",i,tptr -> buffer);
            tptr = tptr -> next;
        }
        printf("\r\n");
        refrline(tline);
        break;
    case CTRL('W'): /* TASTO CTRL-W */
        clrscr();                                                      /* Clear dello schermo                  */
		refrline(tline);
		break;
    case CTRL('C'): /* TASTO CTRL-C */
        break;      /* Non gestito */
    case CTRL('R'): /* TASTO CTRL-R */
        refrline(tline);                                               /* Refresh della linea                  */
		break;
    case CTRL('U'): /* TASTO CTRL-U */
        memset(tline -> buffer,NULL,MAXLENCMD-1);                      /* Azzeramento del buffer               */
        tline -> ptrchar = tline -> buffer;                            /* Reset puntatore al carattere  buffer */
        tline -> ptreol  = tline -> buffer;                            /* Reset puntatore di fine linea        */
		refrline(tline);
		break;
    case CTRL('J'): /* TASTO CTRL-J */
        tline -> ptrchar = tline -> buffer;                            /* Posiziono cursore ad inizio linea    */
		refrline(tline);
		break;
    case CTRL('B'): /* TASTO CTRL-B */
        if(tline -> base == 16)                                        /* Se la base attiva e' 16              */
			{
            tline -> base=10;                                          /* Setto base 10 attiva                 */
			strcpy(tline -> strbase,dec);
            strcpy(tline -> addmode,"%05d: ");
            strcpy(tline -> datamode,"%03d ");
            }
        else                                                           /* In caso diverso                      */
			{
            tline -> base=16;                                          /* Setto base attiva 16                 */
			strcpy(tline -> strbase,hex);
            strcpy(tline -> addmode,"%04x: ");
            strcpy(tline -> datamode,"%02x ");
            }
		printf("\n\rBASE=%d",tline -> base);
		break;
    /* Non e' un carattere di controllo */
    default:
        tline -> stateflag = HISTON;
        if(tline -> mode == OVERSTRIKE)                                /* MODO OVERSTRIKE                      */
			{
            if(tline -> ptrchar == tline -> ptreol)                    /* fine linea                           */
				{
                if(tline -> ptreol < (tline -> buffer+MAXLENCMD-1))    /* non e' al limite                     */
                    ++tline -> ptreol;                                 /* incremento fine linea                */
				else break;
				}
                *(tline -> ptrchar++) = tline -> key;                  /* Scrivo carattere e avanzo cursore    */
				putchar(tline -> key);
			}

            else                                                       /* MODO INSERT                          */
			{
            if(tline -> ptreol < (tline -> buffer+MAXLENCMD-1))        /* non e' al limite                     */
				{
                for(tmp=tline -> ptreol;tmp >= tline -> ptrchar;--tmp) /* Shift a destra di un carattere       */
                    *(tmp+1)=*tmp;                                     /* partendo dal cursore                 */

                *(tline -> ptrchar++) = tline -> key;                  /* Scrivo carattere                     */
                tline -> ptreol++;                                     /* incremento fine linea                */
				refrline(tline);
				}
			}
		   break;

		}
return(TRUE);                                                          /* non e' stato premuto il tasto return */
}
/*
浜様様様様様様様様様様様様様様様様様様様様様冤様様様様様様様様様様様様様様様様?
? FUNZIONE : REFRLINE                       ?DATE: Sun  09-12-1993  13:01:54  ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳祖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? INPUT : Puntatore a descrittore di tipo LINE                                ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? OUTPUT : Nessuno                                                            ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? FUNZIONI CHIAMATE : printf() - gotoxy() - wherey() - eraseline()            ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? DESCRIZIONE : Esegue il refresh della linea in editing                      ?
藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
*/
refrline(refline)
LINE 	*refline;
{
eraseline();
printf("%c%s",video_desc.prompt,refline -> buffer);
gotoxy((char )(refline -> ptrchar - refline -> buffer + 1),wherey());
}
/*
浜様様様様様様様様様様様様様様様様様様様様様冤様様様様様様様様様様様様様様様様?
? FUNZIONE : ERASELINE                      ?DATE: Sun  09-12-1993  13:04:38  ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳祖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? INPUT : Nessuno                                                             ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? OUTPUT : Nessuno                                                            ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? FUNZIONI CHIAMATE : gotoxy() - wherey() - memset()                          ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? DESCRIZIONE : Cancella la riga di schermo a cui e' posizionato il cursore   ?
藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
*/
eraseline()
{
gotoxy(0,wherey());
memset(video_desc.curs_add,' ',MAXCOLUMN);
}
/*
浜様様様様様様様様様様様様様様様様様様様様様冤様様様様様様様様様様様様様様様様?
? FUNZIONE : FLUSHBUF                       ?DATE:Sun  09-12-1993  13:08:26   ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳祖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? INPUT : Puntatore a descrittore di tipo LINE                                ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? OUTPUT : Nessuno                                                            ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? FUNZIONI CHIAMATE : Nessuna                                                 ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? DESCRIZIONE : Svuota il buffer di linea                                     ?
藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
*/
flushbuf(tline)
LINE *tline;
{
register char i;
tline -> buffer=curline;
tline -> ptrchar=curline;
tline -> ptreol=curline;
for(i=0;i<MAXLENCMD-1;++i)
	curline[i]=NULL;
}
/*
浜様様様様様様様様様様様様様様様様様様様様様冤様様様様様様様様様様様様様様様様?
? FUNZIONE : GETHIST                        ?DATE: Sun  10-10-1993  23:38:03  ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳祖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? INPUT : Puntatore a descrittore di tipo LINE                                ?
?         Direzione (NXT o PRV)                                               ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? OUTPUT : Puntatore al nuovo buffer di history                               ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? FUNZIONI CHIAMATE : strcpy() - strlen() - refrline()                        ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? DESCRIZIONE : Copia nel descrittore di linea il comando nel prossimo        ?
? buffer di history e ritorna il nuovo puntatore alla lista                   ?
藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
*/
HISTOR *gethist(tline,dptrh,direction)
LINE    *tline;
HISTOR  *dptrh;
unsigned char direction;
{
HISTOR  *savptr;

savptr=dptrh;

if(direction==NXT) dptrh = dptrh -> next;
else dptrh = dptrh -> prev;
if( *(dptrh -> buffer)==0) return(savptr);

strcpy(tline -> buffer,dptrh -> buffer);
tline -> ptreol  = tline -> buffer+strlen(tline -> buffer);    /* Reset puntatore di fine linea        */
tline -> ptrchar = tline -> ptreol;                            /* Reset puntatore al carattere  buffer */
refrline(tline);
return(dptrh);
}
