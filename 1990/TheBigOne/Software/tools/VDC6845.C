/*------------------------------------------------------------------------*/
/*                                                                        */
/*       PROGRAMMA PER IL  CALCOLO DEI REGISTRI DEL VIDEO CONTROLLER      */
/*                                                                        */
/*                        MOTOROLA   M C 6 8 4 5                          */
/*                                                                        */
/*------------------------------------------------------------------------*/
/* char *p  indica che p Š un puntatore ad una variabile char             */
/* p = &"sdsd" p viene fatto puntare alla stringa sdsd                    */
/*------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <dir.h>
#include "\tmp\struct68.h"

int j,                            // Troncamento valore di ingresso //
    js;                           // Valore al 5ø decimale //
short par,              // Parametro da correggere //
	i;

long int result;        // Valori double troncati //

float vbval[10];       // Array valore parametri di base //

char *strbas[10],      // Array nome parametri di base //
     *file;            // Nome file per il salvataggio //

char risp;             // Variabile di risposta (un carattere) //
char curdir[MAXPATH],      // lunghezza massima del path //
       newdir[MAXPATH];    // lunghezza massima del path //
/* ===================================================================== */
/*                                                                       */
/*  Funzione : printvar                                                  */
/*             Stampa sullo stdout le variabili ricavate dai parametri   */
/*             di base                                                   */
/*                                                                       */
/*  Input    : Nessuno                                                   */
/*  Output   : Nessuno                                                   */
/*                                                                       */
/* ===================================================================== */

void printvar ()
{

	for (i = 0; i < 10; ++i){
	    	printf ("%s %g\n",variable_video[i].name,
		variable_video[i].decimal_value);
               	};
	return;
}

/* ===================================================================== */
/*                                                                       */
/*  Funzione : printreg                                                  */
/*             Stampa sullo stdout i registri del componente MC6845      */
/*             in notazione decimale ed esadecimale                      */
/*                                                                       */
/*  Input    : Nessuno                                                   */
/*  Output   : Nessuno                                                   */
/*                                                                       */
/* ===================================================================== */
void printreg ()
{
        printf ("%s\n","Registri ...  Dec  Hex"); 
	for (i = 0; i < 10; ++i){

	printf ("%s %2d  %2x\n",register_video[i].name,
	register_video[i].value,register_video[i].value);

	};
	return;
}

/* ===================================================================== */
/*                                                                       */
/*  Funzione : savepar                                                   */
/*             Salva su file i parametri di base , le variabili ricavate */
/*             ed il valore dei registri calcolato                       */
/*                                                                       */
/*  Input    : Nome del file                                             */
/*  Output   : Su file specificato                                       */
/*                                                                       */
/* ===================================================================== */

savepar (name)

char *name;      //  Nome del file in ingresso //
{

FILE *stream;    /* Variabile stringa di nome stream riferita alla
                    struttura FILE descritta nell'include stdio.h */


current_directory(curdir);
printf("Il direttorio attuale Š %s\n", curdir);

       do {                      /* Ciclo do-while di attesa risposta
				    valida */

	printf("Vuoi cambiarlo ?");
	scanf ("%s",&risp);
	  } while (risp != 's' && risp != 'n' );

	if (risp == 's' ){                     // Richiede il nuovo path //
                change_directory();
		};




	   stream=fopen(name, "wt");   // Apre il file in scrittura di testo //

	   /* SALVA PARAMETRI DI BASE */

	   fprintf (stream,"\t%s\n",
                    "--------------------------------------------------------------");
	   fprintf (stream,"\t%s\n","PARAMETRI DI BASE");
	   fprintf (stream,"\t%s\n",
                    "--------------------------------------------------------------");
	   	for (i = 0; i < 10; ++i){
		fprintf (stream,"\t%s %g\n",strbas[i],vbval[i]);
	        };


           /* SALVA VARIABILI CALCOLATE E REGISTRI MC6845 */

	   fprintf (stream,"\t%s\n",
                    "--------------------------------------------------------------");
	   fprintf (stream,"\t%s\t %s\n","Registri ...  Dec  Hex","VARIABILI");
	   fprintf (stream,"\t%s\n",
		    "--------------------------------------------------------------");
	   	for (i = 0; i < 10; ++i){

		fprintf (stream,"\t%s %2d  %2x\t %s %g\n",
		register_video[i].name,register_video[i].value,
		register_video[i].value,variable_video[i].name,
		variable_video[i].decimal_value);
		};

	   
	   fclose (stream);             // Chiude il file //
	return;
}



/* ===================================================================== */
/*                                                                       */
/*  Funzione : main                                                      */
/*                                                                       */
/*  Input    : Nessuno                                                   */
/*  Output   : Nessuno 							 */
/*                                                                       */
/* ===================================================================== */



main ()
{

#define LENMENU  56  /* lunghezza men— */

/* Inizializzazione Men— parametri di base */

strbas[0] ="B1 :Horizontal frequency ---------------------------->";
strbas[1] ="B2 :Vertical frequency ------------------------------>";
strbas[2] ="B3 :Minimum horizontal retrace time ----------------->";
strbas[3] ="B4 :Minimum vertical retrace time ------------------->";
strbas[4] ="B5 :Displayed characters per row--------------------->";
strbas[5] ="B6 :Displayed charactor per row --------------------->";
strbas[6] ="B7 :Num of dots in character (matrix row) ----------->";
strbas[7] ="B8 :Num of scan lines in charactor (matrix column) -->";
strbas[8] ="B9 :Num of dots between horizontal adiacents -------->";
strbas[9] ="B10:Num of scan lines between vertical adiacents ---->";


clrscr ();         /*  pulisce schermo */


gotoxy (20,2);     /* va alle coordinate x,y */
printf ("+----------------------------------+\n");
gotoxy (20,3);
printf ("| CALCOLO REGISTRI MACCHINA MC6845 |\n");
gotoxy (20,4);
printf ("+----------------------------------+\n");
gotoxy (1,6);

   for (i = 0; i < 10; ++i){     /* Ciclo di input dei parametri di base */
	puts (strbas[i]);
	gotoxy (LENMENU ,i+6);
	scanf ("%f",&vbval[i]);
	fflush(stdin);           /* azzeramento (flush) della variabile
				    in caso di  errore */
	};

   do {                          /* Ciclo do-while per la
   				    correzione dei parametri  */

       do {                      /* Ciclo do-while di attesa risposta
				    valida */

	  printf ("Tutti i parametri sono corretti (s-n)");
	  scanf ("%s",&risp);
			    
	  } while (risp != 's' && risp != 'n' );

	    if (risp == 's')     /* Uscita da 1ø ciclo do-while se
				    tutti i parametri sono corretti */
		      break;

       else {                    /* Altrimenti ciclo di attesa parametro */

             do {
		printf ("Parametro (1-10) ");
		scanf ("%d",&par);
		} while (par <= 0 || par > 11 );

	     --par;                         // Posiziona puntatore array //

	     /* Stampa Nome parametro ,Vecchio valore e richiede nuovo */

	     puts (strbas[par]);
	     gotoxy (LENMENU ,(wherey()-1));
	     printf ("Old value ");
	     printf ("%g\n",vbval[par]);
	     puts (strbas[par]);
	     gotoxy (LENMENU ,(wherey()-1));
	     printf ("New value ");
	     scanf ("%f",&vbval[par]);
	      }

      } while (risp == 'n' || risp == 'N');  /* Se ci sono altri parametri
						errati ripete il ciclo */

/*                +---------------------------------------+
		  |  INIZIO CALCOLO VARIABILI E REGISTRI  |
		  +---------------------------------------+
*/
                    /* CALCOLO FREQUENZA APPROSSIMATA DI PENNELLO VIDEO */
variable_video[0].decimal_value=(vbval[4]*(vbval[6]+vbval[8]))/
				((1/vbval[0])-vbval[2]);

                    /* CALCOLO REGISTRO R0 */
register_video[0].value = approxup((variable_video[0].decimal_value/
				(vbval[0]*(vbval[6]+vbval[8])))-1.0);

                    /* CALCOLO REGISTRO R1 */
register_video[1].value=vbval[4];

                    /* CALCOLO REGISTRO R3 */
register_video[3].value = approxup((register_video[0].value -
				register_video[1].value)/3.0);

		    /* CALCOLO REGISTRO R2 */
register_video[2].value = approxup(register_video[1].value +
				(register_video[3].value/2.0));

		    /* CALCOLO Tempo di carattere */
variable_video[1].decimal_value=(1/((register_video[0].value+1.0)*vbval[0]));

		    /* CALCOLO FREQUENZA ESATTA DI PENNELLO VIDEO */
variable_video[2].decimal_value=(vbval[6]+vbval[8])/
				variable_video[1].decimal_value;

		    /* CALCOLO scan line time */
variable_video[3].decimal_value=(register_video[0].value+1.0)*
				variable_video[1].decimal_value;

		    /* CALCOLO n */
result = 1/(vbval[1]*variable_video[3].decimal_value);
variable_video[4].decimal_value=result;

		    /* CALCOLO N */
result = variable_video[4].decimal_value/(vbval[7]+vbval[9]);
variable_video[5].decimal_value=result;

		    /* CALCOLO R */
result = ((variable_video[4].decimal_value/(vbval[7]+vbval[9])-
	 variable_video[5].decimal_value)*(vbval[7]+vbval[9]));

variable_video[6].decimal_value=result;

		    /* CALCOLO REGISTRO R4 */
register_video[4].value=variable_video[5].decimal_value-1;

		    /* CALCOLO REGISTRO R5 */
register_video[5].value=variable_video[6].decimal_value;

		    /* CALCOLO REGISTRO R6 */
register_video[6].value=vbval[5];

		    /* CALCOLO REGISTRO R7 */
register_video[7].value=(register_video[4].value+1)-
				((16-register_video[5].value)/
				(vbval[7]+vbval[9]));
if (register_video[7].value < 0) {
	printf ("%s","Valore impossibile variare B6-B8-B10");
	return;
	}

		    /* CALCOLO REGISTRO R9 */
register_video[9].value=vbval[7]+vbval[9]-1;

		    /* CALCOLO TCR */
variable_video[7].decimal_value=(vbval[7]+vbval[9])*
				variable_video[3].decimal_value;

                     /* CALCOLO THR */
variable_video[8].decimal_value=((register_video[0].value+1.0-vbval[4])*
				(vbval[6]+vbval[8]))/
				variable_video[2].decimal_value;

if (variable_video[8].decimal_value < vbval[2]) {
	printf ("%s %g","Valore fuori range durante il calcolo di THR Valore :",
			variable_video[8].decimal_value);
	return;
	}
				
		       /* CALCOLO TVR */
variable_video[9].decimal_value=(vbval[0]/vbval[1])-(vbval[5]*
				(vbval[7]+vbval[9])*
				variable_video[3].decimal_value);

if (variable_video[9].decimal_value < vbval[3]) {
	printf ("%s","Valore fuori range durante il calcolo di TVR Valore :",
		      variable_video[9].decimal_value);
	return;
	}

printvar();
printreg();


do {     // Ciclo do-while richiesta salvataggio su file //

  printf ("Salvataggio su file (s-n)");
  scanf ("%s",&risp);

  } while (risp != 's' && risp != 'n' );

     if (risp == 'n')     // Se non richiesto il salvataggio fine //
	      return;

     else {               // Altrimenti chiede il nome del file //

	   printf ("Filename EXT=.PAR ");
	   scanf ("%s",file);
	   strcat(file,".par");   // appende al nome del file l'estensione //

	   savepar (file);        // Passa il nome alla funzione di save //
	   }
   return;

}

        	