/*
ษอออออออออออออออออออออออออออออออออออออออออออัออออออออออออัออออออออออออออออออออป
บ FILE:c:\cadasm\r10\rom\include\command.h  ณVERS:1.1    ณTIPO: INCLUDE       บ
วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤลฤฤฤฤฤฤฤฤฤฤฤฤมฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
บ AUTORE: Colombo Daniele                   ณDATA: Sun  09-12-1993 08:52:47   บ
ฬอออออออออออออออออออออออออออออออออออออออออออฯอออออออออออออออออออออออออออออออออน
บ INCLUDE:  NONE                                                              บ
ฬอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออน
บ FUNZIONI PUBBLICHE: nullfunc() - load() - write() - read() - rdport()       บ
บ cmdnotld() - go() - filmem() - setport()                                    บ
ฬอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออน
บ DESCRIZIONE: Include per l'importazione di tutte le funzioni corrispondenti บ
บ ai comandi del debugger                                                     บ
บ                                                                             บ
ศอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ
*/
#define NOTINST     0xC9

extern int nullfunc(),load(),write(),read(),rdport(),cmdnotld(),go(),goon(),
    step(),reg(),filmem(),setport(),wrport(),vers(),bpset(),bpdel(),bpprint(),
    tpset(),tpdel(),tpprint(),cominst(),install();
