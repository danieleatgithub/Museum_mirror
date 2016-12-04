
#include <stdio.h>
#include <string.h>
#include <dir.h>

extern char curdir[MAXPATH],      // lunghezza massima del path //
       newdir[MAXPATH];      // lunghezza massima del path //

/* ===================================================================== */
/*                                                                       */
/*  Funzione : current_directory                                         */
/*             Restituisce il path del direttorio corrente               */
/*                                                                       */
/*  Input    : Massima lunghezza del path                                */
/*  Output   : Lunghezza massima del path                                */
/*                                                                       */
/* ===================================================================== */

char *current_directory(char *path)
{
	strcpy(path, "X:\\");      /* fill string with form of response: X:\ */
	path[0] = 'A' + getdisk();    /* replace X with current drive letter */
	getcurdir(0, path+3);  /* fill rest of string with current directory */
	return(path);
}
/* ===================================================================== */
/*                                                                       */
/*  Funzione : change _directory                                         */
/*             Richiede il nuovo path , si posiziona nel nuovo           */
/*             direttorio se esistente, altrimenti ritorna al            */
/*             precedente                                                */
/*                                                                       */
/*  Input    : Nessuno                                                   */
/*  Output   : Nessuno                                                   */
/*                                                                       */
/* ===================================================================== */


change_directory()
{
printf("Inserisci il path :");
		scanf ("%s",&newdir);
		if (chdir(newdir))          // Se ritorna diverso da zero//
			{                   // Il path non e' valido //
			perror("chdir()");  // Stampa messaggio di errore //
			   chdir(curdir);   // riposiziona sul direttorio //
			                    // corrente //
			};
			printf("Il direttorio attuale Š %s\n", curdir);
		return;
}                
/* ===================================================================== */
/*                                                                       */
/*  Funzione : approxup                                                  */
/*             Approssima all'intero maggiore                            */
/*                                                                       */
/*  Input    : Valore di tipo a doppia precisione floating point         */
/*  Output   : Valore di tipo intero                                     */
/*                                                                       */
/* ===================================================================== */


double approxup(dato)

double dato;                       // Valore di ingresso della funzione //
{
extern int j,                            // Troncamento valore di ingresso //
       js;                           // Valore al 5ø decimale //

	j = dato;
	js = ( dato - j )* 10000; // Controllo se oltre il 5ø decimale //
	if ( js != 0 )            // Š diverso da zero                 //

		  ++j;            // Se si incremento l'intero         //

	return j;                 // Ritorna l'intero approssimato     // 
}  
