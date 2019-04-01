/******************************************************************************/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/

AhoTTS: A Text-To-Speech system for Basque*,
developed by Aholab Signal Processing Laboratory at the
University of the Basque Country (UPV/EHU). Its acoustic engine is based on
hts_engine' and it uses AhoCoder* as vocoder.
(Read COPYRIGHT_and_LICENSE_code.txt for more details)
--------------------------------------------------------------------------------

Linguistic processing for Basque, Vocoder (Ahocoder) and
integration by Aholab UPV/EHU.

*AhoCoder is an HNM-based vocoder for Statistical Synthesizers
http://aholab.ehu.es/ahocoder/

++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyrights:
	1997-2015  Aholab Signal Processing Laboratory, University of the Basque
	 Country (UPV/EHU)
    *2011-2015 Aholab Signal Processing Laboratory, University of the Basque
	  Country (UPV/EHU)

++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Licenses:
	GPL-3.0+
	*GPL-3.0+
	'Modified BSD (Compatible with GNU GPL)

++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

GPL-3.0+
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 .
 This package is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 .
 You should have received a copy of the GNU General Public License
 along with this program. If not, see <http://www.gnu.org/licenses/>.
 .
 On Debian systems, the complete text of the GNU General
 Public License version 3 can be found in /usr/share/common-licenses/GPL-3.

//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/******************************************************************************/
#ifndef __CHARSET_H__
#define __CHARSET_H__

/**********************************************************/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/*
Copyright: 1995 - Grupo de Voz (DAET) ETSII/IT-Bilbao

Nombre fuente................ charset.h
Nombre paquete............... Sinte
Lenguaje fuente.............. C
Estado....................... estable
Dependencia Hard/OS.......... pagina de codigos
Codigo condicional........... CHARSET_???

Codificacion................. Carlos Cruz
............................. Borja Etxebarria

Version  dd/mm/aa  Autor     Proposito de la edicion
-------  --------  --------  -----------------------
1.0.0    22/07/97  borja     revision
0.0.2    12/10/95  borja     charset minusculas. filtro char suelto...
0.0.1    14/06/95  borja     CH_??? con cast a (CHAR) 
0.0.0    06/05/95  Carlos    Codificacion inicial.

======================== Contenido ========================
Paginas de codigos soportadas:

- PC-8 Code Page 437  -------------------------> IBM437
- PC-850 Multilingual -------------------------> IBM850
- ISO 8859/1 Latin 1 / Windows 3.1 Latin 1 ----> ISOLatin1

Se definen codigos SGML para castellano, del tipo: 
CS_IBM437_atilde, CS_ISOLatin1_Etilde, etc.

Seleccion automatica en compilacion de la pagina de codigos:
Se define CHARSET al valor IBM437, IBM850, ISOLatin1...
y se define una y solo una de las constantes CHARSET_ISOLatin1 o
CHARSET_IBM437 o CHARSET_IBM850...
Tambien se definen codigos SGML para cada caracter, del 
tipo CS_ntilde para la pagina de codigos actual, y los 
mismos codigos para cadenas del tipo CS_S_ntilde.

Nota: en la pagina 437 faltan algunas vocales acentuadas
en mayusculas. Se han puesto los codigos de las minusculas.
Tener en cuenta posibles repercusiones en el programa!
===========================================================
*/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/**********************************************************/

#include "tdef.h"

/**********************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************/
/* Codigos SGML para pagina de codigos actual */

#if defined(__OS_MSDOS__)    /* para MSDOS, asumimos pagina 437 */
#define CHARSET_IBM437  1
#define CHARSET IBM437

#elif defined(__OS_WIN32_CONSOLE__)    /* para consola win95, tambien 437 */
#define CHARSET_IBM437  1
#define CHARSET IBM437

#else    /* resto de casos, (Windows, Linux, Sun, ...) ISO Latin 1 */
#define CHARSET_ISOLatin1  1
#define CHARSET ISOLatin1

#endif

/********************************************************************/
/* Codigos SGML PC-8 Code Page 437.
NOTA: A,I,O,U mayusculas no hay acentuadas. Se usan las minusculas!!  */

#define CS_IBM437_atilde '\240'
#define CS_IBM437_etilde '\202'
#define CS_IBM437_itilde '\241'
#define CS_IBM437_otilde '\242'
#define CS_IBM437_utilde '\243'
#define CS_IBM437_uuml   '\201'
#define CS_IBM437_ntilde '\244'
#define CS_IBM437_Atilde '\240'
#define CS_IBM437_Etilde '\334'
#define CS_IBM437_Itilde '\241'
#define CS_IBM437_Otilde '\242'
#define CS_IBM437_Utilde '\243'
#define CS_IBM437_Uuml   '\232'
#define CS_IBM437_Ntilde '\245'
#define CS_IBM437_iexcl  '\255'
#define CS_IBM437_iquest '\250'
#define CS_IBM437_ordf   '\246'
#define CS_IBM437_ordm   '\247'
#define CS_IBM437_deg    '\370'

#define CS_S_IBM437_atilde "\240"
#define CS_S_IBM437_etilde "\202"
#define CS_S_IBM437_itilde "\241"
#define CS_S_IBM437_otilde "\242"
#define CS_S_IBM437_utilde "\243"
#define CS_S_IBM437_uuml   "\201"
#define CS_S_IBM437_ntilde "\244"
#define CS_S_IBM437_Atilde "\240"
#define CS_S_IBM437_Etilde "\334"
#define CS_S_IBM437_Itilde "\241"
#define CS_S_IBM437_Otilde "\242"
#define CS_S_IBM437_Utilde "\243"
#define CS_S_IBM437_Uuml   "\232"
#define CS_S_IBM437_Ntilde "\245"
#define CS_S_IBM437_iexcl  "\255"
#define CS_S_IBM437_iquest "\250"
#define CS_S_IBM437_ordf   "\246"
#define CS_S_IBM437_ordm   "\247"
#define CS_S_IBM437_deg    "\370"


#ifdef CHARSET_IBM437
#define CS_atilde CS_IBM437_atilde
#define CS_etilde CS_IBM437_etilde
#define CS_itilde CS_IBM437_itilde
#define CS_otilde CS_IBM437_otilde
#define CS_utilde CS_IBM437_utilde
#define CS_uuml   CS_IBM437_uuml  
#define CS_ntilde CS_IBM437_ntilde
#define CS_Atilde CS_IBM437_Atilde
#define CS_Etilde CS_IBM437_Etilde
#define CS_Itilde CS_IBM437_Itilde
#define CS_Otilde CS_IBM437_Otilde
#define CS_Utilde CS_IBM437_Utilde
#define CS_Uuml   CS_IBM437_Uuml  
#define CS_Ntilde CS_IBM437_Ntilde
#define CS_iexcl  CS_IBM437_iexcl 
#define CS_iquest CS_IBM437_iquest
#define CS_ordf   CS_IBM437_ordf  
#define CS_ordm   CS_IBM437_ordm  
#define CS_deg    CS_IBM437_deg   

#define CS_S_atilde CS_S_IBM437_atilde
#define CS_S_etilde CS_S_IBM437_etilde
#define CS_S_itilde CS_S_IBM437_itilde
#define CS_S_otilde CS_S_IBM437_otilde
#define CS_S_utilde CS_S_IBM437_utilde
#define CS_S_uuml   CS_S_IBM437_uuml  
#define CS_S_ntilde CS_S_IBM437_ntilde
#define CS_S_Atilde CS_S_IBM437_Atilde
#define CS_S_Etilde CS_S_IBM437_Etilde
#define CS_S_Itilde CS_S_IBM437_Itilde
#define CS_S_Otilde CS_S_IBM437_Otilde
#define CS_S_Utilde CS_S_IBM437_Utilde
#define CS_S_Uuml   CS_S_IBM437_Uuml  
#define CS_S_Ntilde CS_S_IBM437_Ntilde
#define CS_S_iexcl  CS_S_IBM437_iexcl 
#define CS_S_iquest CS_S_IBM437_iquest
#define CS_S_ordf   CS_S_IBM437_ordf  
#define CS_S_ordm   CS_S_IBM437_ordm  
#define CS_S_deg    CS_S_IBM437_deg   
#endif

/********************************************************************/
/* Codigos SGML ISO 8859/1 Latin 1 /  Windows 3.1 Latin 1  */

#define CS_ISOLatin1_atilde '\341'
#define CS_ISOLatin1_etilde '\351'
#define CS_ISOLatin1_itilde '\355'
#define CS_ISOLatin1_otilde '\363'
#define CS_ISOLatin1_utilde '\372'
#define CS_ISOLatin1_uuml   '\374'
#define CS_ISOLatin1_ntilde '\361'
#define CS_ISOLatin1_Atilde '\301'
#define CS_ISOLatin1_Etilde '\311'
#define CS_ISOLatin1_Itilde '\315'
#define CS_ISOLatin1_Otilde '\323'
#define CS_ISOLatin1_Utilde '\332'
#define CS_ISOLatin1_Uuml   '\334'
#define CS_ISOLatin1_Ntilde '\321'
#define CS_ISOLatin1_iexcl  '\241'
#define CS_ISOLatin1_iquest '\277'
#define CS_ISOLatin1_ordf   '\252'
#define CS_ISOLatin1_ordm   '\272'
#define CS_ISOLatin1_deg    '\260'
//iparralde
#define CS_ISOLatin1_ytilde '\253'
#define CS_ISOLatin1_Ytilde '\221'

#define CS_S_ISOLatin1_atilde "\341"
#define CS_S_ISOLatin1_etilde "\351"
#define CS_S_ISOLatin1_itilde "\355"
#define CS_S_ISOLatin1_otilde "\363"
#define CS_S_ISOLatin1_utilde "\372"
#define CS_S_ISOLatin1_uuml   "\374"
#define CS_S_ISOLatin1_ntilde "\361"
#define CS_S_ISOLatin1_Atilde "\301"
#define CS_S_ISOLatin1_Etilde "\311"
#define CS_S_ISOLatin1_Itilde "\315"
#define CS_S_ISOLatin1_Otilde "\323"
#define CS_S_ISOLatin1_Utilde "\332"
#define CS_S_ISOLatin1_Uuml   "\334"
#define CS_S_ISOLatin1_Ntilde "\321"
#define CS_S_ISOLatin1_iexcl  "\241"
#define CS_S_ISOLatin1_iquest "\277"
#define CS_S_ISOLatin1_ordf   "\252"
#define CS_S_ISOLatin1_ordm   "\272"
#define CS_S_ISOLatin1_deg    "\260"


#ifdef CHARSET_ISOLatin1
#define CS_atilde CS_ISOLatin1_atilde
#define CS_etilde CS_ISOLatin1_etilde
#define CS_itilde CS_ISOLatin1_itilde
#define CS_otilde CS_ISOLatin1_otilde
#define CS_utilde CS_ISOLatin1_utilde
#define CS_uuml   CS_ISOLatin1_uuml  
#define CS_ntilde CS_ISOLatin1_ntilde
#define CS_Atilde CS_ISOLatin1_Atilde
#define CS_Etilde CS_ISOLatin1_Etilde
#define CS_Itilde CS_ISOLatin1_Itilde
#define CS_Otilde CS_ISOLatin1_Otilde
#define CS_Utilde CS_ISOLatin1_Utilde
#define CS_Uuml   CS_ISOLatin1_Uuml  
#define CS_Ntilde CS_ISOLatin1_Ntilde
#define CS_iexcl  CS_ISOLatin1_iexcl 
#define CS_iquest CS_ISOLatin1_iquest
#define CS_ordf   CS_ISOLatin1_ordf  
#define CS_ordm   CS_ISOLatin1_ordm  
#define CS_deg    CS_ISOLatin1_deg   

//Iparralde
#define CS_ytilde CS_ISOLatin1_ytilde
#define CS_Ytilde CS_ISOLatin1_Ytilde

#define CS_S_atilde CS_S_ISOLatin1_atilde
#define CS_S_etilde CS_S_ISOLatin1_etilde
#define CS_S_itilde CS_S_ISOLatin1_itilde
#define CS_S_otilde CS_S_ISOLatin1_otilde
#define CS_S_utilde CS_S_ISOLatin1_utilde
#define CS_S_uuml   CS_S_ISOLatin1_uuml  
#define CS_S_ntilde CS_S_ISOLatin1_ntilde
#define CS_S_Atilde CS_S_ISOLatin1_Atilde
#define CS_S_Etilde CS_S_ISOLatin1_Etilde
#define CS_S_Itilde CS_S_ISOLatin1_Itilde
#define CS_S_Otilde CS_S_ISOLatin1_Otilde
#define CS_S_Utilde CS_S_ISOLatin1_Utilde
#define CS_S_Uuml   CS_S_ISOLatin1_Uuml  
#define CS_S_Ntilde CS_S_ISOLatin1_Ntilde
#define CS_S_iexcl  CS_S_ISOLatin1_iexcl 
#define CS_S_iquest CS_S_ISOLatin1_iquest
#define CS_S_ordf   CS_S_ISOLatin1_ordf  
#define CS_S_ordm   CS_S_ISOLatin1_ordm  
#define CS_S_deg    CS_S_ISOLatin1_deg   
#endif

/********************************************************************/
/* Codigos SGML PC-850 Multilingual ---> CHARSET_IBM850 */

#define CS_IBM850_atilde '\240'
#define CS_IBM850_etilde '\202'
#define CS_IBM850_itilde '\241'
#define CS_IBM850_otilde '\242'
#define CS_IBM850_utilde '\243'
#define CS_IBM850_uuml   '\201'
#define CS_IBM850_ntilde '\244'
#define CS_IBM850_Atilde '\265'
#define CS_IBM850_Etilde '\334'
#define CS_IBM850_Itilde '\326'
#define CS_IBM850_Otilde '\340'
#define CS_IBM850_Utilde '\351'
#define CS_IBM850_Uuml   '\232'
#define CS_IBM850_Ntilde '\245'
#define CS_IBM850_iexcl  '\255'
#define CS_IBM850_iquest '\250'
#define CS_IBM850_ordf   '\246'
#define CS_IBM850_ordm   '\247'
#define CS_IBM850_deg    '\370'

#define CS_S_IBM850_atilde "\240"
#define CS_S_IBM850_etilde "\202"
#define CS_S_IBM850_itilde "\241"
#define CS_S_IBM850_otilde "\242"
#define CS_S_IBM850_utilde "\243"
#define CS_S_IBM850_uuml   "\201"
#define CS_S_IBM850_ntilde "\244"
#define CS_S_IBM850_Atilde "\265"
#define CS_S_IBM850_Etilde "\334"
#define CS_S_IBM850_Itilde "\326"
#define CS_S_IBM850_Otilde "\340"
#define CS_S_IBM850_Utilde "\351"
#define CS_S_IBM850_Uuml   "\232"
#define CS_S_IBM850_Ntilde "\245"
#define CS_S_IBM850_iexcl  "\255"
#define CS_S_IBM850_iquest "\250"
#define CS_S_IBM850_ordf   "\246"
#define CS_S_IBM850_ordm   "\247"
#define CS_S_IBM850_deg    "\370"


#ifdef CHARSET_IBM850
#define CS_atilde CS_IBM850_atilde
#define CS_etilde CS_IBM850_etilde
#define CS_itilde CS_IBM850_itilde
#define CS_otilde CS_IBM850_otilde
#define CS_utilde CS_IBM850_utilde
#define CS_uuml   CS_IBM850_uuml  
#define CS_ntilde CS_IBM850_ntilde
#define CS_Atilde CS_IBM850_Atilde
#define CS_Etilde CS_IBM850_Etilde
#define CS_Itilde CS_IBM850_Itilde
#define CS_Otilde CS_IBM850_Otilde
#define CS_Utilde CS_IBM850_Utilde
#define CS_Uuml   CS_IBM850_Uuml  
#define CS_Ntilde CS_IBM850_Ntilde
#define CS_iexcl  CS_IBM850_iexcl 
#define CS_iquest CS_IBM850_iquest
#define CS_ordf   CS_IBM850_ordf  
#define CS_ordm   CS_IBM850_ordm  
#define CS_deg    CS_IBM850_deg   

#define CS_S_atilde CS_S_IBM850_atilde
#define CS_S_etilde CS_S_IBM850_etilde
#define CS_S_itilde CS_S_IBM850_itilde
#define CS_S_otilde CS_S_IBM850_otilde
#define CS_S_utilde CS_S_IBM850_utilde
#define CS_S_uuml   CS_S_IBM850_uuml  
#define CS_S_ntilde CS_S_IBM850_ntilde
#define CS_S_Atilde CS_S_IBM850_Atilde
#define CS_S_Etilde CS_S_IBM850_Etilde
#define CS_S_Itilde CS_S_IBM850_Itilde
#define CS_S_Otilde CS_S_IBM850_Otilde
#define CS_S_Utilde CS_S_IBM850_Utilde
#define CS_S_Uuml   CS_S_IBM850_Uuml  
#define CS_S_Ntilde CS_S_IBM850_Ntilde
#define CS_S_iexcl  CS_S_IBM850_iexcl 
#define CS_S_iquest CS_S_IBM850_iquest
#define CS_S_ordf   CS_S_IBM850_ordf  
#define CS_S_ordm   CS_S_IBM850_ordm  
#define CS_S_deg    CS_S_IBM850_deg   
#endif

/******************************************************************/

CHAR charset_toupper( CHAR ch );
CHAR charset_tolower( CHAR ch );
CHAR *charset_strupper( CHAR * str );
CHAR *charset_strlower( CHAR * str );

/******************************************************************/

#ifdef __cplusplus
}  /* extern "C" */
#endif

/******************************************************************/

#endif

