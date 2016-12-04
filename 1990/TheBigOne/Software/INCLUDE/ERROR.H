/*
ษอออออออออออออออออออออออออออออออออออออออออออัออออออออออออัออออออออออออออออออออป
บ FILE:c:\cadasm\r10\rom\include\error.h    ณVERS:1.1    ณTIPO: INCLUDE       บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤลฤฤฤฤฤฤฤฤฤฤฤฤมฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ AUTORE: Colombo Daniele                   ณDATA: Sun  09-12-1993  10:14:13  บ
ฬอออออออออออออออออออออออออออออออออออออออออออฯอออออออออออออออออออออออออออออออออน
บ INCLUDE: \CADASM\R10\ROM\INCLUDE\SYS.H                                      บ
ฬอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออน
บ DESCRIZIONE: GESTIONE ERRORI                                                บ
บ Contiene:                                                                   บ
บ   - Puntatori alle stringhe di errore                                       บ
บ   - Macro stampa errori                                                     บ
บ                                                                             บ
ศอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ
*/

#ifndef _SYS_
#include  "\cadasm\r10\rom\include\sys.h"
#endif

#ifndef __INTERPR__
/* Puntatori stringhe di errore 		*/
extern  char    *s1,*s2,*s3,*s21,*s31,*command,*not,*found,*syntax,*error,*enough,
        *mem_er,*aborted,*available,*load_er,*offset,*ready,*checksum,*complete,
        *lenght,*name,*parity,*generic,*parvalue[3];
#endif

#define		NOTFOUND	printf(s3,command,not,found)
#define		SYNERR		printf(s2,syntax,error)
#define		NOTMEM		printf(s3,not,enough,mem_er)
#define		MEMAVAL		printf(s21,available,mem_er,*AVAIL_)
#define		LDABTD		printf(s2,load_er,aborted)
#define		LDRDY		printf(s31,load_er,ready,offset,loadstat.offset)
#define     LDCKERR(x)  printf(s31,load_er,checksum,error,x)
#define     LDEND       printf(s2,load_er,complete)
#define     CMDNOTLD    printf(s3,command,not,load_er)



#define S1_I              0
#define S2_I              1
#define S3_I              2
#define S21_I             3
#define S31_I             4
#define ABORTED_I         5
#define ADDRESS_I         6
#define AFTER_I           7
#define ANDLOC_I          8
#define ANDREG_I          9
#define AT_I              10
#define AVAILABLE_I       11
#define BIT_I             12
#define BREAK_I           13
#define CHECKSUM_I        14
#define COMMAND_I         15
#define COMPLETE_I        16
#define CONFIGURATA_I     17
#define ENOUGH_I          18
#define EQCHR_I           19
#define EQINT_I           20
#define ERROR_I           21
#define EVEN_I            22
#define FOUND_I           23
#define GENERIC_I         24
#define LENGHT_I          25
#define LOAD_ER_I         26
#define MEM_ER_I          27
#define NAME_I            28
#define NEQCHR_I          29
#define NEQINT_I          30
#define NONE_I            31
#define NON_I             32
#define NOT_I             33
#define ODD_I             34
#define OFFSET_I          35
#define PARITY_I          36
#define POINT_I           37
#define PORTA_I           38
#define RAM_I             39
#define READY_I           40
#define REGISTER_I        41
#define ROM_I             42
#define SPEED_I           43
#define STOP_I            44
#define SYNTAX_I          45
#define TRACE_I           46
#define PC_I              47
#define SP_I              48
#define AF_I              49
#define BC_I              50
#define DE_I              51
#define HL_I              52
#define AF1_I             53
#define BC1_I             54
#define DE1_I             55
#define HL1_I             56
#define IX_I              57
#define IY_I              58
#define IREG_I            59
#define IF_I              60

#define MAXSTR            61       /* Massimo numero stringhe di errore    */
#define URGREL(x)         (x-PC_I)
#define URGABS(x)         (x+PC_I)





