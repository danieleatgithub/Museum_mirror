/*====================================================================
   Struttura che descrive i registri macchina del controllore MC6845
   Array di strutture formato di 10 record
====================================================================== */


struct  video_struct {          
	char *name;             // Nome del registro   (stringa) //
	int value;              // Valore del registro (intero) //
	} register_video[] = {  // Nome dell'array //
	"Registro R0 :",0,      // Inizializzazione dell'array di struttura //
	"Registro R1 :",0,
	"Registro R2 :",0,
	"Registro R3 :",0,
	"Registro R4 :",0,
	"Registro R5 :",0,
	"Registro R6 :",0,
	"Registro R7 :",0,
	"Registro R8 :",0,
	"Registro R9 :",0,
	};

/*====================================================================
   Struttura che descrive i parametri ricavati da quelli  di base
   e variabili usate per il calcolo dei registri MC6845
====================================================================== */

struct  video_var_struct {
	char *name;                   // Nome del parametro (stringa) //
	double  decimal_value;        // Valore decimale del parametro //
	} variable_video[] = {        // Nome dell'array //
	"Approx dot frequency -:",0,  // Inizializzazione dell'array di struttura //
	"Time character (tc) --:",0,
	"Exact dot clock ------:",0,
	"Scan line time -------:",0,
	"n --------------------:",0,
	"N --------------------:",0,
	"R --------------------:",0,
	"TCR ------------------:",0,
	"THR ------------------:",0,
	"TVR ------------------:",0,
	};
