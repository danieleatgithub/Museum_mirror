/*
浜様様様様様様様様様様様様様様様様様様様様様冤様様様様様用様様様様様様様様様様?
? FILE:\CADASM\R10\ROM\CADOS\INTERPR.C      ?VERS:1.1    ?TIPO: MODULO C      ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳田陳陳陳陳陳珍陳陳陳陳陳陳陳陳陳陳?
? AUTORE: Colombo Daniele                   ?DATA: Sun  09-12-1993  13:37:35  ?
麺様様様様様様様様様様様様様様様様様様様様様詫様様様様様様様様様様様様様様様様?
? INCLUDE: stdio.h - string.h -            \cadasm\r10\rom\include\conio.h    ?
? \cadasm\r10\rom\include\command.h    -   \cadasm\r10\rom\include\error.h    ?
麺様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
? FUNZIONI PUBBLICHE: interpr() - nullfunc() - cmdnotld()                     ?
麺様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
? DESCRIZIONE:  Interprete ed esecutore comandi                               ?
? Creazioni di:                                                               ?
?   - Data base comandi in struttura di tipo COMDB:                           ?
塞様様様様様様様様様様様様様用様様様様様様様様様様様様様様様様様様様様様様様融?
査 ESPLICATIVO               ?           RANGE                               査
最陳陳陳陳陳陳陳陳陳陳陳陳陳津陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳超?
査 Nome del comando          ? Stringa nome comando massimo 30 caratteri     査
最陳陳陳陳陳陳陳陳陳陳陳陳陳津陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳超?
査 Tipo di parametro         ? NONE= No parametro STR= Stringa NUM= Numerico 査
最陳陳陳陳陳陳陳陳陳陳陳陳陳津陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳超?
査 Numero minimo di parametri? Numero di parametri obbligatori               査
哉様様様様様様様様様様様様様溶様様様様様様様様様様様様様様様様様様様様様様様夕?
? Per l'aggiunta di un nuovo comando e' necessario modificare il data base    ?
? creato in questo modulo, l'inizializzazione del descrittore di comando      ?
? nel modulo startup.c e l'include command.h                                  ?
藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
*/

#define  __INTERPR__
#include <stdio.h>
#include <string.h>
#include "\cadasm\r10\rom\include\conio.h"
#include "\cadasm\r10\rom\include\command.h"
#include "\cadasm\r10\rom\include\error.h"

/* --------------------- IMPORTAZIONI ------------------------*/                 

extern CMD  com;                    /* DESCRITTORE ULTIMO COMANDO   */
extern int (*entrycom[MAXCOM])();

/* --------------------- CREAZIONI ------------------------*/                           
const COMDB dbcom[MAXCOM]={
/*  Comando     p[0]  p[1]  p[2]  p[3]   p[4]  p[5]  p[6]  p[7]  p[8]  p[9]  p[10] Par. minimi */
    "LOAD",   STR,  STR,  NUM,  NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, 1,
    "WRITE",  STR,  NUM,  NUM,  NUM,  NUM,  NUM,  NUM,  NUM,  NUM,  NUM,  NUM,  3,
    "READ",   STR,  NUM,  NUM,  NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, 2,
    "RDPORT", STR,  NUM,  NUM,  NUM,  NONE, NONE, NONE, NONE, NONE, NONE, NONE, 3,
    "WRPORT", STR,  NUM,  NUM,  NUM,  NONE, NONE, NONE, NONE, NONE, NONE, NONE, 3,
    "EPROG",  STR,  NUM,  NUM,  NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, 3,
    "EBLANK", STR,  NUM,  NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, 2,
    "EVERIFY",STR,  NUM,  NUM,  NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, 3,
    "ECOPY",  STR,  NUM,  NUM,  NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, 3,
    "GO",     STR,  NUM,  NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, 1,
    "STEP",   STR,  NUM,  NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, 1,
    "BPS",    STR,  NUM,  STR,  NUM,  STR,  NUM,  STR,  NUM,  NONE, NONE, NONE, 4,
    "BPD",    STR,  NUM,  NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, 2,
    "BP",     STR,  NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, 1,
    "TPS",    STR,  NUM,  STR,  NUM,  STR,  NUM,  STR,  NUM,  NONE, NONE, NONE, 4,
    "TPD",    STR,  NUM,  NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, 2,
    "TP",     STR,  NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, 1,
    "REG",    STR,  STR,  NUM,  NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, 1,
    "COMINST",STR,  STR,  NUM,  NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, 2,
    "FILL",   STR,  NUM,  NUM,  NUM,  NONE, NONE, NONE, NONE, NONE, NONE, NONE, 4,
    "SETPORT",STR,  NUM,  STR,  STR,  NUM,  NUM,  NONE, NONE, NONE, NONE, NONE, 3,
    "VERS"   ,STR,  NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, 1, };

const char *c_str[MAXSTR]={
            "\r\n%s\0",
            "\r\n%s %s\0",
            "\r\n%s %s %s\0",
            "\r\n%s %s:%x\0",
            "\r\n%s %s %s:%x\0",
            "ABORTED\0",
            "ADDRESS\0",
            "AFTER\0",
            "LOC\0",
            "REG\0",
            "AT\0",
            "AVAILABLE\0",
            "BIT\0",
            "BREAK\0",
            "CHECKSUM\0",
            "COMMAND\0",
            "COMPLETE\0",
            "CONFIGURATA\0",
            "ENOUGH\0",
            "EQCHR\0",
            "EQINT\0",
            "ERROR\0",
            "EVEN\0",
            "FOUND\0",
            "GENERIC\0",
            "LENGHT\0",
            "LOAD\0",
            "MEMORY\0",
            "NAME\0",
            "NEQCHR\0",
            "NEQINT\0",
            "NONE\0",
            "NON\0",
            "NOT\0",
            "ODD\0",
            "OFFSET\0",
            "PARITY\0",
            "POINT\0",
            "PORTA\0",
            "RAM\0",
            "READY\0",
            "REGISTER\0",
            "ROM\0",
            "SPEED\0",
            "STOP\0",
            "SYNTAX\0",
            "TRACE\0",
            "PC\0",
            "SP\0",
            "AF\0",
            "BC\0",
            "DE\0",
            "HL\0",
            "AF'\0",
            "BC'\0",
            "DE'\0",
            "HL'\0",
            "IX\0",
            "IY\0",
            "I\0",
            "IF\0"};


/* Puntatori stringhe di errore          */
char    *s1,*s2,*s3,*s21,*s31,*command,*not,*found,*syntax,*error,*enough,
    *mem_er,*aborted,*available,*load_er,*offset,*ready,*checksum,*complete,
    *lenght,*name,*parity,*generic,*parvalue[3];

/*
浜様様様様様様様様様様様様様様様様様様様様様冤様様様様様様様様様様様様様様様様?
? FUNZIONE : INTERPR                        ?DATE: Sun  09-12-1993  13:55:31  ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳祖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? INPUT : Puntatore alla stringa contenente il comando                        ?
?         Puntatore a descrittore linea in editing                            ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? OUTPUT : Nessuno                                                            ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? FUNZIONI CHIAMATE : strtok() - strupr() - strcpy() - strcmp() - sscanf()    ?
? strlen() - (entrycom[idcom]()) - printf()                                   ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? DESCRIZIONE:Ricerca il comando nel data base dei comandi, esegue il         ?
? controllo sintattico dei parametri, e converte dalla base numerica corrente.?
? Se tutti i controlli sono eseguiti con esito positivo viene linkata         ?
? dinamicamente nel descrittore dell'ultimo comando la routine trovata nel    ?
? data base, viene quindi eseguita passando il numero di argomenti            ?
? decodificati ed il puntatore al descrittore della linea in editing.         ?
? I parametri vengono passati nel array param della struttura pubblica com    ?
? se il parametro e' numerico il contiene il valore convertito                ?
? se e' una stringa contiene il puntatore alla stringa convertito             ?
? ad intero.                                                                  ?
? Se la stringa di comando e' vuota viene rieseguito l'ultimo comando.        ?
? In caso di errore viene annullata la routine corrente e stampato un         ?
? messaggio di errore.                                                        ?
藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
*/
int interpr(ascii_com,tline)
char 	*ascii_com;
LINE    *tline;
{
register char i;
int idcom,rtn;
char *format,*tmp;

i=1;
if((tmp=strtok(ascii_com," ")))
	{
	strcpy(com.name,tmp);
	strupr(com.name);
    idcom=whichcom(com.name,UPPER);
    if(idcom==RTNBAD){
		NOTFOUND;
		com.function=nullfunc;
                return(0);
		}
    com.function=entrycom[idcom];
	i=1;
    rtn=1;

    /* Acquisizione parametri */
    while(i<MAXPAR&&rtn!=EOF&&rtn!=NULL)
		{
        tmp=strtok(NULL," ");
        if(tmp){
            switch(dbcom[idcom].type[i])
                {
                case NONE:
                    rtn=EOF;
                    break;
                case NUM:
                    strupr(tmp);
                    rtn=sscanf(tmp,tline -> strbase,&com.param[i]);
                    break;
                case STR:
                    com.param[i]=(unsigned int)tmp;
                    ((int)tmp) ? (rtn=strlen(tmp)) : (rtn=NULL);
                    break;
                }
            }else rtn=NULL;
		++i;
        }
        if(i<dbcom[idcom].minpar){
            com.function=nullfunc;
            SYNERR;
        }
	}
    (*com.function)(--i,tline);
return(TRUE);
}
/*
浜様様様様様様様様様様様様様様様様様様様様様冤様様様様様様様様様様様様様様様様?
? FUNZIONE : NULLFUNC                       ?DATE: Sun  09-12-1993  14:09:20  ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳祖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? FUNZIONI CHIAMATE : Nessuna                                                 ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? DESCRIZIONE : Funzione nulla per comando nullo od illegale                  ?
藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
*/
COMMAND(nullfunc)
{
}
/*
浜様様様様様様様様様様様様様様様様様様様様様冤様様様様様様様様様様様様様様様様?
? FUNZIONE : CMDNOTLD                       ?DATE: Fri  10-01-1993  19:23:32  ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳祖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? FUNZIONI CHIAMATE : printf()                                                ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? DESCRIZIONE : Funzione nulla per comando non caricato ma previsto           ?
藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
*/
COMMAND(cmdnotld)
{
CMDNOTLD;
com.function=nullfunc;
}
/*
浜様様様様様様様様様様様様様様様様様様様様様冤様様様様様様様様様様様様様様様様?
? FUNZIONE : INISTR                         ?DATE: Thu  12-30-1993  19:53:46  ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳祖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? INPUT : Nessuno                                                             ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? OUTPUT : Nessuno                                                            ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? FUNZIONI CHIAMATE :                                                         ?
?                                                                             ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? DESCRIZIONE : Inizializzazione stringhe                                     ?
?                                                                             ?
藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
*/


inistr()
{
/*陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳*/
/* Inizializzazione puntatori a stringhe di errore */
/*陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳*/
s1=         c_str[S1_I];
s2=         c_str[S2_I];
s3=         c_str[S3_I];
s21=        c_str[S21_I];
s31=        c_str[S31_I];
aborted=    c_str[ABORTED_I];
available=  c_str[AVAILABLE_I];
checksum=   c_str[CHECKSUM_I];
command=    c_str[COMMAND_I];
complete=   c_str[COMPLETE_I];
enough=     c_str[ENOUGH_I];
error=      c_str[ERROR_I];
found=      c_str[FOUND_I];
generic=    c_str[GENERIC_I];
lenght=     c_str[LENGHT_I];
load_er=    c_str[LOAD_ER_I];
mem_er=     c_str[MEM_ER_I];
name=       c_str[NAME_I];
not=        c_str[NOT_I];
offset=     c_str[OFFSET_I];
parity=     c_str[PARITY_I];
parvalue[0]=c_str[ODD_I];
parvalue[1]=c_str[EVEN_I];
parvalue[2]=c_str[NONE_I];
ready=      c_str[READY_I];
syntax=     c_str[SYNTAX_I];
}
/*
浜様様様様様様様様様様様様様様様様様様様様様冤様様様様様様様様様様様様様様様様?
? FUNZIONE : WHICHWORD                      ?DATE: Thu  12-30-1993  21:36:28  ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳祖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? INPUT : Puntatore alla stringa da cercare                                   ?
?         Modalita' di ricerca                                                ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? OUTPUT : Indice della stringa o -1 se la stringa non viene trovata          ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? FUNZIONI CHIAMATE :                                                         ?
?                                                                             ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? DESCRIZIONE :                                                               ?
?                                                                             ?
?                                                                             ?
藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
*/
int whichword(string,convmode)
char *string;
int convmode;
{
register int i;
    switch(convmode)
    {
        case UPPER:
        strupr(string);
        break;
        case LOWER:
        strlwr(string);
        break;
    }
    for(i=0;strcmp(string,c_str[i])&&i<MAXSTR;++i);
    if(i==MAXSTR) i=RTNBAD;
    return(i);
}
/*
浜様様様様様様様様様様様様様様様様様様様様様冤様様様様様様様様様様様様様様様様?
? FUNZIONE : WHICHCOM                       ?DATE: Thu  12-30-1993  21:36:28  ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳祖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? INPUT : Puntatore alla stringa da cercare  nel data base comandi            ?
?         Modalita' di ricerca                                                ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? OUTPUT : Indice del comando o -1 se il comando non viene trovato            ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? FUNZIONI CHIAMATE :                                                         ?
?                                                                             ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? DESCRIZIONE :                                                               ?
?                                                                             ?
?                                                                             ?
藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
*/
int whichcom(string,convmode)
char *string;
int convmode;
{
register int i;
    switch(convmode)
    {
        case UPPER:
        strupr(string);
        break;
        case LOWER:
        strlwr(string);
        break;
    }
    for(i=0;strcmp(string,dbcom[i].name)&&i<MAXCOM;++i);
    if(i==MAXCOM) i=RTNBAD;
    return(i);
}
/*
浜様様様様様様様様様様様様様様様様様様様様様冤様様様様様様様様様様様様様様様様?
? FUNZIONE : OUTMESSAGE                     ?DATE:                            ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳祖陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? INPUT :                                                                     ?
?                                                                             ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? OUTPUT :                                                                    ?
?                                                                             ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? FUNZIONI CHIAMATE :                                                         ?
?                                                                             ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳?
? DESCRIZIONE :                                                               ?
?                                                                             ?
?                                                                             ?
?                                                                             ?
?                                                                             ?
藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
*/
outmessage(idx)
int idx;
{
    printf("%s",c_str[idx]);
}

