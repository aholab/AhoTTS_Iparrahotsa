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
/**********************************************************/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/*
Copyright: 1998 - TSR/Aholab (DET) ETSII/IT-Bilbao

Nombre fuente................ timehilvl.cpp
Nombre paquete............... normalizador
Lenguaje fuente.............. C++
Estado....................... desarrollo
Dependencia Hard/OS.......... -
Codigo condicional........... -

Codificacion................. Juan Luis Murugarren

Version  dd/mm/aa  Autor     Proposito de la edicion
-------  --------  --------  -----------------------
0.0.3    18/07/13  Inaki     Anadir TIME_INTERVAL (10:30-11:15) en isTime
0.0.2    04/05/01  Yon2.     Right Warning/Error info.
0.0.1    25/04/01  Yon2.     Multiling support.
0.0.0    30/11/00  Yon2.     Codificacion inicial.

======================== Contenido ========================
	Detección de hora o lapso de tiempo a alto nivel.
La función devuelve el tipo de hora para su posterior
expansión. Si no es una hora/lapso válido se devulve
TIME_UNKNOWN.

Yon2.
===========================================================
*/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/**********************************************************/



#include "stdlib.h"
#include "stdio.h"

#include "httsmsg.h"

#include "t2l.hpp"
#include "roman.h"
#include "timehilvl.hpp"

/**********************************************************/


/**********************************************************/

TimeType TextToList::isTime(CtI p)
{
	TimeType retval = TIME_UNKNOWN;
	pCHAR pattern;
	CtI q;
	CHAR separator;
	UINT num1, num2, num3, num4;
	BOOL shortF;
	BOOL timeInterval=FALSE;

#ifdef HTTS_DEBUG
        if (!ct(p).pattern) htts_error("TextToList::mustExpand() - Trying to read null Pattern.");
#endif
	//fprintf(stderr,"time pattern=%s\n", ct(p).pattern);
	if (ct(p).pattern) pattern = strdup(ct(p).pattern);
  else return retval;

	//Vemos si puede ser de tipo corto o largo.
	if (strlen(pattern) == 3) shortF = TRUE;
	else if (strlen(pattern) == 5) shortF = FALSE;
	else if (strlen(pattern) == 7 ) timeInterval = TRUE; //intervalo de tiempo
	else {
		free(pattern);
		return retval;
	}

	//Vemos si es patron de hora corta/larga.

	if (!shortF && !timeInterval)	{
		if ( 	(pattern[1] != pattern[3]) ||
			(pattern[0] != 'n') || (pattern[4] != 'n') ||
			(pattern[2] != 'n') ) {
				free(pattern);
				return retval;
		}
	}
	else if(timeInterval){
		if(strcmp(pattern,"npnpnpn")){//si no tiene el formato de intervalo de tiempo, salimos (10:30-11:15)
			free(pattern);
			return retval;
		}
	}
	else	{
		if ( 	(pattern[0] != 'n') || 	(pattern[2] != 'n') ) {
				free(pattern);
				return retval;
		}
	}


	free(pattern);


	//Chequeamos que los separadores sean válidos.
	if (!shortF && !timeInterval)	{
		q=ct.next(p);
		if (strlen(ct(q).str) != 1) return retval;
		separator = (ct(q).str)[0];
		q=ct.next(q);
		q=ct.next(q);
		if (strlen(ct(q).str) != 1) return retval;
		if (separator != (ct(q).str)[0]) return retval;
		if (separator != ':') return retval;
	}
	else if(timeInterval){ //10:30-11:15  //pattern=npnpnpn //comprobar que los "p" son ":","-" y ":"
		//fprintf(stderr,"ct(p).str=%s ct.next=%s\n", ct(p).str, ct(ct.next(p)).str);
		q=ct.next(p);
		if (strlen(ct(q).str) != 1) return retval;
		separator = (ct(q).str)[0];
		if (separator != ':') return retval;
		q=ct.next(q);
		q=ct.next(q);
	//	fprintf(stderr,"%s\n", ct(q).str);
		if (strlen(ct(q).str) != 1) return retval;
		separator = (ct(q).str)[0];
		if (separator != '-') return retval;
		q=ct.next(q);
		q=ct.next(q);
		if (strlen(ct(q).str) != 1) return retval;
		separator = (ct(q).str)[0];
		if (separator != ':') return retval;
		//fprintf(stderr,"%s\n", ct(q).str);
	}
	else	{
		q=ct.next(p);
		if (strlen(ct(q).str) != 1) return retval;
		separator = (ct(q).str)[0];
		if (separator != ':') return retval;
	}

	//Recogemos los números implicados.
	q=p;
	sscanf(ct(q).str, "%d", &num1);
	q=ct.next(q);
	q=ct.next(q);
	sscanf(ct(q).str, "%d", &num2);
	//fprintf(stderr, "num1=%d num2=%d\n", num1, num2);
	if (!shortF && !timeInterval)	{
		q=ct.next(q);
		q=ct.next(q);
		sscanf(ct(q).str, "%d", &num3);
	}
	else if(timeInterval){
		q=ct.next(q);
		q=ct.next(q);
		sscanf(ct(q).str, "%d", &num3);
		q=ct.next(q);
		q=ct.next(q);
		sscanf(ct(q).str, "%d", &num4);
		//fprintf(stderr, "num3=%d num4=%d\n", num3, num4);
	}

	//Comprobamos el rango de los números
	if (!shortF && !timeInterval)	{
		if (num2 > 59 || num3 > 59) return retval;
		else retval = TIME_LONG;
	}
	else if(timeInterval){
		if(num1 > 23 || num2 > 59 || num3 > 23 || num4 > 59) return retval;
		else retval = TIME_INTERVAL;
	}
	else	{
		if (num1 > 23 || num2 > 59) return retval;
		else retval = TIME_SHORT;
	}

	return retval;
}
/**********************************************************/
