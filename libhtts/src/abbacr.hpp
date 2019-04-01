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
#ifndef __ABBACR_HPP__
#define __ABBACR_HPP__

/**********************************************************/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/*
Copyright: 1998 - TSR/Aholab (DET) ETSII/IT-Bilbao

Nombre fuente................ abbacr.hpp
Nombre paquete............... normalizador
Lenguaje fuente.............. C++
Estado....................... desarrollo
Dependencia Hard/OS.......... -
Codigo condicional........... -

Codificacion................. Juan Luis Murugarren

Version  dd/mm/aa  Autor     Proposito de la edicion
-------  --------  --------  -----------------------
0.0.2    29/03/01  Yon2.     Paso al directorio principal.
0.0.1    28/03/01  Yon2.     Need More Data.
0.0.0    22/03/01  Yon2.     Codificacion inicial.

======================== Contenido ========================
	Este modulo detecta y expande abreviaturas, acronimos y
unidades reflejadas en el diccionario.

	Los patrones que presentas estas formas son heterogeneos,
pudiendo ser:
- Para abreviaturas:
	lp    zbk.
  lplp  G.b.
- Para acronimos:
	l --> Generalmente en mayusculas.
- Para unidades:
  l --> no incluyen punto al final.

Se han encontrado tambien en el diccionario actual varias
ocurrencias extra�as, que habr� que corregir en el diccionario:
PSE-EE acr -> deber�a aparecer PSE por un lado y EE por otro.
zum. acr zumardi -> abreviatura o acr�nimo? No importa.

S�lo en el caso de las unidades se tendr� en cuenta que se puede
alterar el orden:
   1 m -> metro bat.
   2 m -> bi metro.

Para decidir si se puede eliminar el punto correspondiente a un
acr�nimo o abreviatura se necesita tener en ese momento el
grupo siguiente, para ver si es una letra may�scula o min�scula.
Si este grupo siguiente no existe, se para la normalizaci�n hasta
que entren m�s datos.


Yon2.
===========================================================
*/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/**********************************************************/

/**********************************************************/

enum AbbAcrUniType	{
	AAU_UNKNOWN=0,
	AAU_ABB,
	AAU_ACR,
	AAU_UNIT,
	AAU_ABBP,
	AAU_ACRP,
	AAU_UNITP,
	AAU_NEEDMOREDATA
};

/**********************************************************/

#endif

