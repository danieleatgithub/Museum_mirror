/*
浜様様様様様様様様様様様様様様様様様様様様様冤様様様様様用様様様様様様様様様様?
? FILE:c:\cadasm\r10\rom\include\command.h  ?VERS:1.1    ?TIPO: INCLUDE       ?
把陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳田陳陳陳陳陳珍陳陳陳陳陳陳陳陳陳陳?
? AUTORE: Colombo Daniele                   ?DATA: Sun  09-12-1993 08:52:47   ?
麺様様様様様様様様様様様様様様様様様様様様様詫様様様様様様様様様様様様様様様様?
? INCLUDE:  NONE                                                              ?
麺様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
? FUNZIONI PUBBLICHE: nullfunc() - load() - write() - read() - rdport()       ?
? cmdnotld() - go() - filmem() - setport()                                    ?
麺様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
? DESCRIZIONE: Include per l'importazione di tutte le funzioni corrispondenti ?
? ai comandi del debugger                                                     ?
?                                                                             ?
藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様?
*/
#define NOTINST     0xC9

extern int nullfunc(),load(),write(),read(),rdport(),cmdnotld(),go(),goon(),
    step(),reg(),filmem(),setport(),wrport(),vers(),bpset(),bpdel(),bpprint(),
    tpset(),tpdel(),tpprint(),cominst(),install();
