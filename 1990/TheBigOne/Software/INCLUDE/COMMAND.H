/*
�����������������������������������������������������������������������������ͻ
� FILE:c:\cadasm\r10\rom\include\command.h  �VERS:1.1    �TIPO: INCLUDE       �
�����������������������������������������������������������������������������Ķ
� AUTORE: Colombo Daniele                   �DATA: Sun  09-12-1993 08:52:47   �
�����������������������������������������������������������������������������͹
� INCLUDE:  NONE                                                              �
�����������������������������������������������������������������������������͹
� FUNZIONI PUBBLICHE: nullfunc() - load() - write() - read() - rdport()       �
� cmdnotld() - go() - filmem() - setport()                                    �
�����������������������������������������������������������������������������͹
� DESCRIZIONE: Include per l'importazione di tutte le funzioni corrispondenti �
� ai comandi del debugger                                                     �
�                                                                             �
�����������������������������������������������������������������������������ͼ
*/
#define NOTINST     0xC9

extern int nullfunc(),load(),write(),read(),rdport(),cmdnotld(),go(),goon(),
    step(),reg(),filmem(),setport(),wrport(),vers(),bpset(),bpdel(),bpprint(),
    tpset(),tpdel(),tpprint(),cominst(),install();
