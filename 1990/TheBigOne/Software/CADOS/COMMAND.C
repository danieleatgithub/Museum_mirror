/*
ษอออออออออออออออออออออออออออออออออออออออออออัออออออออออออัออออออออออออออออออออป
บ FILE:\CADASM\R10\ROM\CADOS\COMMAND.C      ณVERS:1.1    ณTIPO:MODULO C       บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤลฤฤฤฤฤฤฤฤฤฤฤฤมฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ AUTORE: Colombo Daniele                   ณDATA: Sun  09-12-1993  12:34:29  บ
ฬอออออออออออออออออออออออออออออออออออออออออออฯอออออออออออออออออออออออออออออออออน
บ INCLUDE: stdio.h - stdlib.h - \cadasm\r10\rom\include\conio.h               บ
ฬอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออน
บ FUNZIONI PUBBLICHE: edlin() - refrline() - eraseline() - flushbuf()         บ
บ gethist()                                                                   บ
ฬอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออน
บ DESCRIZIONE: GESTIONE LINEA COMANDI                                         บ
บ Creazioni:                                                                  บ
บ   - Stringhe base numerica                                                  บ
ศอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ
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
ษอออออออออออออออออออออออออออออออออออออออออออัอออออออออออออออออออออออออออออออออป
บ FUNZIONE : EDLIN                          ณDATE:Sun  09-12-1993  12:41:16   บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤมฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ INPUT : Puntatore a descrittore di tipo LINE                                บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ OUTPUT : TRUE se non e' stato premuto il tasto return o il puntatore al     บ
บ buffer contenente la stringa in linea confermata con il tasto return        บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ FUNZIONI CHIAMATE : strlen() - wherey() - gotoxy() - putchar() - refrline() บ
บ eraseline() - memclr() - strcpy() - wherex() - gethist() - clrscr()         บ
บ memset()                                                                    บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ DESCRIZIONE: Gestisce  l'editor  di  linea  ricevendo  il  carattere nella  บ
บ struttura di tipo LINE, aggiorna il buffer   e la riga di schermo, gestisce บ
บ i seguenti comandi comandi di editing:                                      บ
บ ึฤฤฤฤฤฤฤฤฤฤฤยฤฤฤฤฤฤฤฤฤฤฤฤฤฤยฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤท บ
บ บ TASTO     ณ COMANDO      ณ      AZIONE                                  บ บ
บ วฤฤฤฤฤฤฤฤฤฤฤลฤฤฤฤฤฤฤฤฤฤฤฤฤฤลฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ บ
บ บ(ctrl H)   ณ BACKSPACE    ณ Cancella il carattere precedente             บ บ
บ บ           ณ DELETE       ณ Cancella il carattere corrente               บ บ
บ บ           ณ TAB          ณ Cursore a fine linea                         บ บ
บ บ(ctrl A)   ณ INS/OVS      ณ Toggle modo insert overstrike                บ บ
บ บ(Left arr) ณ LEFT ARROW   ณ Cursore a sinistra di una posizione          บ บ
บ บ(Right arr)ณ RIGHT ARROW  ณ Cursore a destra di una posizione            บ บ
บ บ(up   arr) ณ PREV HISTORY ณ Comando precedente nel buffer di history     บ บ
บ บ(down  arr)ณ NEXT HISTORY ณ Prossimo comando nel buffer di history       บ บ
บ บ(ctrl V)   ณ HISTORY      ณ Elenco dei comandi nel buffer di history     บ บ
บ บ(ctrl W)   ณ CLEAR        ณ Cancella lo schermo e riscrive la linea      บ บ
บ บ(ctrl C)   ณ  ----------  ณ Non implementato (Previsto BREAK)            บ บ
บ บ(ctrl R)   ณ REFRESH      ณ Refresh della linea                          บ บ
บ บ(ctrl U)   ณ ERASE        ณ Cancella la linea                            บ บ
บ บ(ctrl J)   ณ HOME         ณ Cursore a inizio riga                        บ บ
บ บ(ctrl B)   ณ BASE         ณ Cambia base da 10 a 16 e viceversa           บ บ
บ ำฤฤฤฤฤฤฤฤฤฤฤมฤฤฤฤฤฤฤฤฤฤฤฤฤฤมฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฝ บ
ศอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ
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
ษอออออออออออออออออออออออออออออออออออออออออออัอออออออออออออออออออออออออออออออออป
บ FUNZIONE : REFRLINE                       ณDATE: Sun  09-12-1993  13:01:54  บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤมฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ INPUT : Puntatore a descrittore di tipo LINE                                บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ OUTPUT : Nessuno                                                            บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ FUNZIONI CHIAMATE : printf() - gotoxy() - wherey() - eraseline()            บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ DESCRIZIONE : Esegue il refresh della linea in editing                      บ
ศอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ
*/
refrline(refline)
LINE 	*refline;
{
eraseline();
printf("%c%s",video_desc.prompt,refline -> buffer);
gotoxy((char )(refline -> ptrchar - refline -> buffer + 1),wherey());
}
/*
ษอออออออออออออออออออออออออออออออออออออออออออัอออออออออออออออออออออออออออออออออป
บ FUNZIONE : ERASELINE                      ณDATE: Sun  09-12-1993  13:04:38  บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤมฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ INPUT : Nessuno                                                             บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ OUTPUT : Nessuno                                                            บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ FUNZIONI CHIAMATE : gotoxy() - wherey() - memset()                          บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ DESCRIZIONE : Cancella la riga di schermo a cui e' posizionato il cursore   บ
ศอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ
*/
eraseline()
{
gotoxy(0,wherey());
memset(video_desc.curs_add,' ',MAXCOLUMN);
}
/*
ษอออออออออออออออออออออออออออออออออออออออออออัอออออออออออออออออออออออออออออออออป
บ FUNZIONE : FLUSHBUF                       ณDATE:Sun  09-12-1993  13:08:26   บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤมฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ INPUT : Puntatore a descrittore di tipo LINE                                บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ OUTPUT : Nessuno                                                            บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ FUNZIONI CHIAMATE : Nessuna                                                 บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ DESCRIZIONE : Svuota il buffer di linea                                     บ
ศอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ
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
ษอออออออออออออออออออออออออออออออออออออออออออัอออออออออออออออออออออออออออออออออป
บ FUNZIONE : GETHIST                        ณDATE: Sun  10-10-1993  23:38:03  บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤมฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ INPUT : Puntatore a descrittore di tipo LINE                                บ
บ         Direzione (NXT o PRV)                                               บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ OUTPUT : Puntatore al nuovo buffer di history                               บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ FUNZIONI CHIAMATE : strcpy() - strlen() - refrline()                        บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ DESCRIZIONE : Copia nel descrittore di linea il comando nel prossimo        บ
บ buffer di history e ritorna il nuovo puntatore alla lista                   บ
ศอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ
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