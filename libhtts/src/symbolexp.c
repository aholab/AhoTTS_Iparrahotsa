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

Nombre fuente................ isofilt.c
Nombre paquete............... normalizador
Lenguaje fuente.............. C
Estado....................... desarrollo
Dependencia Hard/OS.......... -
Codigo condicional........... -

Codificacion................. Juan Luis Murugarren

Version  dd/mm/aa  Autor     Proposito de la edicion
-------  --------  --------  -----------------------
0.1.1	 15/05/05  Larraitz	 bikoitxa --> bikoitza
0.1.0	 16/11/02  inigos	 Adaptaci�n al castellano
0.0.3    07/04/01  Yon2.     Gradu bug.
0.0.2    06/04/01  Yon2.     Cedilla bug.
0.0.1    26/10/00  Yon2.     Archivo de cabecera y
                             metodo de acceso.
0.0.0    17/10/00  Yon2.     Codificacion inicial.

======================== Contenido ========================

Matriz de 256 elementos que filtra caracteres de la tabla
ISO 8859/Latin 1.
Los caracteres que no son de inter�s los convierte a " ".
No editar este archivo desde DOS con BC la p�gina de c�digos
es totalmente diferente.

NOTA: �No deber�a guardarse la informaci�n? (may�sculas, acentos...)

  inigos
===========================================================
*/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/**********************************************************/

#include "symbolexp.h"



/**********************************************************/

pCHAR eu_getchexp(CHAR c)
{
	void *j = &c;
	return eu_symbolexp[*((pUCHAR)j)];
}


/**********************************************************/

/**********************************************************/

pCHAR es_getchexp(CHAR c)
{
	void *j = &c;
	return es_symbolexp[*((pUCHAR)j)];
}


/**********************************************************/




/**********************************************************/

pCHAR eu_symbolexp[256] = {
	/* [000] C */ (char *)"NoExp",
	/* [001] C */ (char *)"NoExp",
	/* [002] C */ (char *)"NoExp",
	/* [003] C */ (char *)"NoExp",
	/* [004] C */ (char *)"NoExp",
	/* [005] C */ (char *)"NoExp",
	/* [006] C */ (char *)"NoExp",
	/* [007] C */ (char *)"NoExp",
	/* [008] C */ (char *)"NoExp",
	/* [009] C */ (char *)"NoExp",
	/* [010] C */ (char *)"NoExp",
	/* [011] C */ (char *)"NoExp",
	/* [012] C */ (char *)"NoExp",
	/* [013] C */ (char *)"NoExp",
	/* [014] C */ (char *)"NoExp",
	/* [015] C */ (char *)"NoExp",
	/* [016] C */ (char *)"NoExp",
	/* [017] C */ (char *)"NoExp",
	/* [018] C */ (char *)"NoExp",
	/* [019] C */ (char *)"NoExp",
	/* [020] C */ (char *)"NoExp",
	/* [021] C */ (char *)"NoExp",
	/* [022] C */ (char *)"NoExp",
	/* [023] C */ (char *)"NoExp",
	/* [024] C */ (char *)"NoExp",
	/* [025] C */ (char *)"NoExp",
	/* [026] C */ (char *)"NoExp",
	/* [027] C */ (char *)"NoExp",
	/* [028] C */ (char *)"NoExp",
	/* [029] C */ (char *)"NoExp",
	/* [030] C */ (char *)"NoExp",
	/* [031] C */ (char *)"NoExp",
	/* [032]   */ (char *)"NoExp",
	/* [033] ! */ (char *)"harridura ikurra",
	/* [034] " */ (char *)"komatxo bikoitzak",
	/* [035] # */ (char *)"almohadilla",
	/* [036] $ */ (char *)"dolar",
	/* [037] % */ (char *)"ehuneko",
	/* [038] & */ (char *)"eta",
	/* [039] ' */ (char *)"komatxo",
	/* [040] ( */ (char *)"ireki parentesia",
	/* [041] ) */ (char *)"itxi parentesia",
	/* [042] * */ (char *)"izartxo",
	/* [043] + */ (char *)"gehiketaren ikurra",
	/* [044] , */ (char *)"koma",
	/* [045] - */ (char *)"gidoia",
	/* [046] . */ (char *)"puntu",
	/* [047] / */ (char *)"barra",
	/* [048] 0 */ (char *)"zero",
	/* [049] 1 */ (char *)"bat",
	/* [050] 2 */ (char *)"bi",
	/* [051] 3 */ (char *)"hiru",
	/* [052] 4 */ (char *)"lau",
	/* [053] 5 */ (char *)"bost",
	/* [054] 6 */ (char *)"sei",
	/* [055] 7 */ (char *)"zazpi",
	/* [056] 8 */ (char *)"zortzi",
	/* [057] 9 */ (char *)"bederatzi",
	/* [058] : */ (char *)"bi puntu",
	/* [059] ; */ (char *)"puntu eta koma",
	/* [060] < */ (char *)"txikiago",
	/* [061] = */ (char *)"berdin",
	/* [062] > */ (char *)"handiago",
	/* [063] ? */ (char *)"galdera ikurra",
	/* [064] @ */ (char *)"arroba",
	/* [065] A */ (char *)"a",
	/* [066] B */ (char *)"be",
	/* [067] C */ (char *)"ze",
	/* [068] D */ (char *)"de",
	/* [069] E */ (char *)"e",
	/* [070] F */ (char *)"efe",
	/* [071] G */ (char *)"ge",
	/* [072] H */ (char *)"hatxe",
	/* [073] I */ (char *)"i",
	/* [074] J */ (char *)"jota",
	/* [075] K */ (char *)"ka",
	/* [076] L */ (char *)"ele",
	/* [077] M */ (char *)"eme",
	/* [078] N */ (char *)"ene",
	/* [079] O */ (char *)"o",
	/* [080] P */ (char *)"pe",
	/* [081] Q */ (char *)"ku",
	/* [082] R */ (char *)"erre",
	/* [083] S */ (char *)"ese",
	/* [084] T */ (char *)"te",
	/* [085] U */ (char *)"u",
	/* [086] V */ (char *)"uve",
	/* [087] W */ (char *)"uve bikoitza",
	/* [088] X */ (char *)"ixa",
	/* [089] Y */ (char *)"i grekoa",
	/* [090] Z */ (char *)"zeta",
	/* [091] [ */ (char *)"ireki markoa",
	/* [092] \ */ (char *)"atzerantzako barra",
	/* [093] ] */ (char *)"itxi markoa",
	/* [094] ^ */ (char *)"azentu zirkunflexu",
	/* [095] _ */ (char *)"beheko gidoia",
	/* [096] ` */ (char *)"NoExp",
	/* [097] a */ (char *)"a",
	/* [098] b */ (char *)"be",
	/* [099] c */ (char *)"ze",
	/* [100] d */ (char *)"de",
	/* [101] e */ (char *)"e",
	/* [102] f */ (char *)"efe",
	/* [103] g */ (char *)"ge",
	/* [104] h */ (char *)"hatxe",
	/* [105] i */ (char *)"i",
	/* [106] j */ (char *)"jota",
	/* [107] k */ (char *)"ka",
	/* [108] l */ (char *)"ele",
	/* [109] m */ (char *)"eme",
	/* [110] n */ (char *)"ene",
	/* [111] o */ (char *)"o",
	/* [112] p */ (char *)"pe",
	/* [113] q */ (char *)"ku",
	/* [114] r */ (char *)"erre",
	/* [115] s */ (char *)"ese",
	/* [116] t */ (char *)"te",
	/* [117] u */ (char *)"u",
	/* [118] v */ (char *)"uve",
	/* [119] w */ (char *)"uve bikoitza",
	/* [120] x */ (char *)"ixa",
	/* [121] y */ (char *)"i grekoa",
	/* [122] z */ (char *)"zeta",
	/* [123] { */ (char *)"ireki giltza",
	/* [124] | */ (char *)"barra bertikala",
	/* [125] } */ (char *)"itxi giltza",
	/* [126] ~ */ (char *)"tilde",
	/* [127] C */ (char *)"NoExp",
	/* [128] C */ (char *)"NoExp",
	/* [129] C */ (char *)"NoExp",
	/* [130] C */ (char *)"NoExp",
	/* [131] C */ (char *)"NoExp",
	/* [132] C */ (char *)"NoExp",
	/* [133] C */ (char *)"NoExp",
	/* [134] C */ (char *)"NoExp",
	/* [135] C */ (char *)"NoExp",
	/* [136] C */ (char *)"NoExp",
	/* [137] C */ (char *)"NoExp",
	/* [138] C */ (char *)"NoExp",
	/* [139] C */ (char *)"NoExp",
	/* [140] C */ (char *)"NoExp",
	/* [141] C */ (char *)"NoExp",
	/* [142] C */ (char *)"NoExp",
	/* [143] C */ (char *)"NoExp",
	/* [144] C */ (char *)"NoExp",
	/* [145] C */ (char *)"NoExp",
	/* [146] C */ (char *)"NoExp",
	/* [147] C */ (char *)"NoExp",
	/* [148] C */ (char *)"NoExp",
	/* [149] C */ (char *)"NoExp",
	/* [150] C */ (char *)"NoExp",
	/* [151] C */ (char *)"NoExp",
	/* [152] C */ (char *)"NoExp",
	/* [153] C */ (char *)"NoExp",
	/* [154] C */ (char *)"NoExp",
	/* [155] C */ (char *)"NoExp",
	/* [156] C */ (char *)"NoExp",
	/* [157] C */ (char *)"NoExp",
	/* [158] C */ (char *)"NoExp",
	/* [159] C */ (char *)"NoExp",
	/* [160] C */ (char *)"NoExp",
	/* [161] � */ (char *)"hasierako harridura ikurra",
	/* [162] � */ (char *)"NoExp",
	/* [163] � */ (char *)"libera esterlina",
	/* [164] � */ (char *)"euro", //I�aki
	/* [165] � */ (char *)"yen",
	/* [166] � */ (char *)"NoExp",
	/* [167] � */ (char *)"NoExp",
	/* [168] � */ (char *)"NoExp",
	/* [169] � */ (char *)"kopirrait",
	/* [170] � */ (char *)"NoExp",
	/* [171] � */ (char *)"komatxo bikoitzak",
	/* [172] � */ (char *)"NoExp",
	/* [173] � */ (char *)"NoExp",
	/* [174] � */ (char *)"NoExp",
	/* [175] � */ (char *)"gorako gidoia",
	/* [176] � */ (char *)"gradu",
	/* [177] � */ (char *)"plus minus",
	/* [178] � */ (char *)"ber bi",
	/* [179] � */ (char *)"ber hiru",
	/* [180] � */ (char *)"NoExp",
	/* [181] � */ (char *)"nu",
	/* [182] � */ (char *)"NoExp",
	/* [183] � */ (char *)"biderketaren ikurra",
	/* [184] � */ (char *)"NoExp",
	/* [185] � */ (char *)"NoExp",
	/* [186] � */ (char *)"NoExp",
	/* [187] � */ (char *)"komatxo bikoitzak",
	/* [188] � */ (char *)"laurden bat",
	/* [189] � */ (char *)"erdi bat",
	/* [190] � */ (char *)"hiru laurden",
	/* [191] � */ (char *)"hasierako galdera ikurra",
	/* [192] � */ (char *)"NoExp",
	/* [193] � */ (char *)"a",
	/* [194] � */ (char *)"NoExp",
	/* [195] � */ (char *)"NoExp",
	/* [196] � */ (char *)"NoExp",
	/* [197] � */ (char *)"NoExp",
	/* [198] � */ (char *)"NoExp",
	/* [199] � */ (char *)"cedila",
	/* [200] � */ (char *)"NoExp",
	/* [201] � */ (char *)"e",
	/* [202] � */ (char *)"NoExp",
	/* [203] � */ (char *)"NoExp",
	/* [204] � */ (char *)"NoExp",
	/* [205] � */ (char *)"i",
	/* [206] � */ (char *)"NoExp",
	/* [207] � */ (char *)"NoExp",
	/* [208] � */ (char *)"NoExp",
	/* [209] � */ (char *)"e�e",
	/* [210] � */ (char *)"NoExp",
	/* [211] � */ (char *)"o",
	/* [212] � */ (char *)"NoExp",
	/* [213] � */ (char *)"NoExp",
	/* [214] � */ (char *)"NoExp",
	/* [215] � */ (char *)"biderketaren ikurra",
	/* [216] � */ (char *)"NoExp",
	/* [217] � */ (char *)"NoExp",
	/* [218] � */ (char *)"u",
	/* [219] � */ (char *)"NoExp",
	/* [220] � */ (char *)"NoExp",
	/* [221] � */ (char *)"NoExp",
	/* [222] � */ (char *)"NoExp",
	/* [223] � */ (char *)"beta",
	/* [224] � */ (char *)"NoExp",
	/* [225] � */ (char *)"a",
	/* [226] � */ (char *)"NoExp",
	/* [227] � */ (char *)"NoExp",
	/* [228] � */ (char *)"NoExp",
	/* [229] � */ (char *)"NoExp",
	/* [230] � */ (char *)"NoExp",
	/* [231] � */ (char *)"cedila",
	/* [232] � */ (char *)"NoExp",
	/* [233] � */ (char *)"e",
	/* [234] � */ (char *)"NoExp",
	/* [235] � */ (char *)"NoExp",
	/* [236] � */ (char *)"NoExp",
	/* [237] � */ (char *)"i",
	/* [238] � */ (char *)"NoExp",
	/* [239] � */ (char *)"NoExp",
	/* [240] � */ (char *)"NoExp",
	/* [241] � */ (char *)"e",
	/* [242] � */ (char *)"NoExp",
	/* [243] � */ (char *)"o",
	/* [244] � */ (char *)"NoExp",
	/* [245] � */ (char *)"NoExp",
	/* [246] � */ (char *)"NoExp",
	/* [247] � */ (char *)"zatiketaren ikurra",
	/* [248] � */ (char *)"NoExp",
	/* [249] � */ (char *)"NoExp",
	/* [250] � */ (char *)"u",
	/* [251] � */ (char *)"NoExp",
	/* [252] � */ (char *)"NoExp",
	/* [253] � */ (char *)"NoExp",
	/* [254] � */ (char *)"NoExp",
	/* [255] � */ (char *)"NoExp"
	};

/**********************************************************/

/**********************************************************/

pCHAR es_symbolexp[256] = {
	/* [000] C */ (char *)"NoExp",
	/* [001] C */ (char *)"NoExp",
	/* [002] C */ (char *)"NoExp",
	/* [003] C */ (char *)"NoExp",
	/* [004] C */ (char *)"NoExp",
	/* [005] C */ (char *)"NoExp",
	/* [006] C */ (char *)"NoExp",
	/* [007] C */ (char *)"NoExp",
	/* [008] C */ (char *)"NoExp",
	/* [009] C */ (char *)"NoExp",
	/* [010] C */ (char *)"NoExp",
	/* [011] C */ (char *)"NoExp",
	/* [012] C */ (char *)"NoExp",
	/* [013] C */ (char *)"NoExp",
	/* [014] C */ (char *)"NoExp",
	/* [015] C */ (char *)"NoExp",
	/* [016] C */ (char *)"NoExp",
	/* [017] C */ (char *)"NoExp",
	/* [018] C */ (char *)"NoExp",
	/* [019] C */ (char *)"NoExp",
	/* [020] C */ (char *)"NoExp",
	/* [021] C */ (char *)"NoExp",
	/* [022] C */ (char *)"NoExp",
	/* [023] C */ (char *)"NoExp",
	/* [024] C */ (char *)"NoExp",
	/* [025] C */ (char *)"NoExp",
	/* [026] C */ (char *)"NoExp",
	/* [027] C */ (char *)"NoExp",
	/* [028] C */ (char *)"NoExp",
	/* [029] C */ (char *)"NoExp",
	/* [030] C */ (char *)"NoExp",
	/* [031] C */ (char *)"NoExp",
	/* [032]   */ (char *)"NoExp",
	/* [033] ! */ (char *)"cierra exclamaci�n",
	/* [034] " */ (char *)"comillas dobles",
	/* [035] # */ (char *)"almohadilla",
	/* [036] $ */ (char *)"dolar",
	/* [037] % */ (char *)"por ciento",
	/* [038] & */ (char *)"y",
	/* [039] ' */ (char *)"comilla",
	/* [040] ( */ (char *)"abre par�ntesis",
	/* [041] ) */ (char *)"cierra par�ntesis",
	/* [042] * */ (char *)"asterisco",
	/* [043] + */ (char *)"m�s",
	/* [044] , */ (char *)"coma",
	/* [045] - */ (char *)"gui�n",
	/* [046] . */ (char *)"punto",
	/* [047] / */ (char *)"barra",
	/* [048] 0 */ (char *)"cero",
	/* [049] 1 */ (char *)"uno",
	/* [050] 2 */ (char *)"dos",
	/* [051] 3 */ (char *)"tres",
	/* [052] 4 */ (char *)"cuatro",
	/* [053] 5 */ (char *)"cinco",
	/* [054] 6 */ (char *)"seis",
	/* [055] 7 */ (char *)"siete",
	/* [056] 8 */ (char *)"ocho",
	/* [057] 9 */ (char *)"nueve",
	/* [058] : */ (char *)"dos puntos",
	/* [059] ; */ (char *)"punto y coma",
	/* [060] < */ (char *)"menor que",
	/* [061] = */ (char *)"igual",
	/* [062] > */ (char *)"mayor que",
	/* [063] ? */ (char *)"cierra interrogaci�n",
	/* [064] @ */ (char *)"arroba",
	/* [065] A */ (char *)"a",
	/* [066] B */ (char *)"be",
	/* [067] C */ (char *)"ce",
	/* [068] D */ (char *)"de",
	/* [069] E */ (char *)"e",
	/* [070] F */ (char *)"efe",
	/* [071] G */ (char *)"ge",
	/* [072] H */ (char *)"hache",
	/* [073] I */ (char *)"i",
	/* [074] J */ (char *)"jota",
	/* [075] K */ (char *)"ca",
	/* [076] L */ (char *)"ele",
	/* [077] M */ (char *)"eme",
	/* [078] N */ (char *)"ene",
	/* [079] O */ (char *)"o",
	/* [080] P */ (char *)"pe",
	/* [081] Q */ (char *)"cu",
	/* [082] R */ (char *)"erre",
	/* [083] S */ (char *)"ese",
	/* [084] T */ (char *)"te",
	/* [085] U */ (char *)"u",
	/* [086] V */ (char *)"uve",
	/* [087] W */ (char *)"uve doble",
	/* [088] X */ (char *)"equis",
	/* [089] Y */ (char *)"i griega",
	/* [090] Z */ (char *)"ceta",
	/* [091] [ */ (char *)"abre corchete",
	/* [092] \ */ (char *)"barra invertida",
	/* [093] ] */ (char *)"cierra corchete",
	/* [094] ^ */ (char *)"acento circunflexo",
	/* [095] _ */ (char *)"gui�n bajo",
	/* [096] ` */ (char *)"NoExp",
	/* [097] a */ (char *)"a",
	/* [098] b */ (char *)"be",
	/* [099] c */ (char *)"ce",
	/* [100] d */ (char *)"de",
	/* [101] e */ (char *)"e",
	/* [102] f */ (char *)"efe",
	/* [103] g */ (char *)"ge",
	/* [104] h */ (char *)"hache",
	/* [105] i */ (char *)"i",
	/* [106] j */ (char *)"jota",
	/* [107] k */ (char *)"ca",
	/* [108] l */ (char *)"ele",
	/* [109] m */ (char *)"eme",
	/* [110] n */ (char *)"ene",
	/* [111] o */ (char *)"o",
	/* [112] p */ (char *)"pe",
	/* [113] q */ (char *)"cu",
	/* [114] r */ (char *)"erre",
	/* [115] s */ (char *)"ese",
	/* [116] t */ (char *)"te",
	/* [117] u */ (char *)"u",
	/* [118] v */ (char *)"uve",
	/* [119] w */ (char *)"uve doble",
	/* [120] x */ (char *)"equis",
	/* [121] y */ (char *)"i griega",
	/* [122] z */ (char *)"ceta",
	/* [123] { */ (char *)"abre llave",
	/* [124] | */ (char *)"barra vertical",
	/* [125] } */ (char *)"cierra llave",
	/* [126] ~ */ (char *)"tilde",
	/* [127] C */ (char *)"NoExp",
	/* [128] C */ (char *)"NoExp",
	/* [129] C */ (char *)"NoExp",
	/* [130] C */ (char *)"NoExp",
	/* [131] C */ (char *)"NoExp",
	/* [132] C */ (char *)"NoExp",
	/* [133] C */ (char *)"NoExp",
	/* [134] C */ (char *)"NoExp",
	/* [135] C */ (char *)"NoExp",
	/* [136] C */ (char *)"NoExp",
	/* [137] C */ (char *)"NoExp",
	/* [138] C */ (char *)"NoExp",
	/* [139] C */ (char *)"NoExp",
	/* [140] C */ (char *)"NoExp",
	/* [141] C */ (char *)"NoExp",
	/* [142] C */ (char *)"NoExp",
	/* [143] C */ (char *)"NoExp",
	/* [144] C */ (char *)"NoExp",
	/* [145] C */ (char *)"NoExp",
	/* [146] C */ (char *)"NoExp",
	/* [147] C */ (char *)"NoExp",
	/* [148] C */ (char *)"NoExp",
	/* [149] C */ (char *)"NoExp",
	/* [150] C */ (char *)"NoExp",
	/* [151] C */ (char *)"NoExp",
	/* [152] C */ (char *)"NoExp",
	/* [153] C */ (char *)"NoExp",
	/* [154] C */ (char *)"NoExp",
	/* [155] C */ (char *)"NoExp",
	/* [156] C */ (char *)"NoExp",
	/* [157] C */ (char *)"NoExp",
	/* [158] C */ (char *)"NoExp",
	/* [159] C */ (char *)"NoExp",
	/* [160] C */ (char *)"NoExp",
	/* [161] � */ (char *)"abre exclamaci�n",
	/* [162] � */ (char *)"NoExp",
	/* [163] � */ (char *)"libra esterlina",
	/* [164] � */ (char *)"euro", //i�aki
	/* [165] � */ (char *)"yen",
	/* [166] � */ (char *)"n�mero ordinal femenino",
	/* [167] � */ (char *)"n�mero ordinal masculino",
	/* [168] � */ (char *)"NoExp",
	/* [169] � */ (char *)"copirrait",
	/* [170] � */ (char *)"NoExp",
	/* [171] � */ (char *)"abre comillas dobles",
	/* [172] � */ (char *)"NoExp",
	/* [173] � */ (char *)"NoExp",
	/* [174] � */ (char *)"NoExp",
	/* [175] � */ (char *)"gui�n alto",
	/* [176] � */ (char *)"grado",
	/* [177] � */ (char *)"m�s menos",
	/* [178] � */ (char *)"al cuadrado",
	/* [179] � */ (char *)"al cubo",
	/* [180] � */ (char *)"NoExp",
	/* [181] � */ (char *)"nu",
	/* [182] � */ (char *)"NoExp",
	/* [183] � */ (char *)"signo de multiplicaci�n",
	/* [184] � */ (char *)"NoExp",
	/* [185] � */ (char *)"NoExp",
	/* [186] � */ (char *)"NoExp",
	/* [187] � */ (char *)"cierra comillas dobles",
	/* [188] � */ (char *)"un cuarto",
	/* [189] � */ (char *)"un medio",
	/* [190] � */ (char *)"tres cuartos",
	/* [191] � */ (char *)"abre interrogaci�n",
	/* [192] � */ (char *)"NoExp",
	/* [193] � */ (char *)"�",
	/* [194] � */ (char *)"NoExp",
	/* [195] � */ (char *)"NoExp",
	/* [196] � */ (char *)"NoExp",
	/* [197] � */ (char *)"NoExp",
	/* [198] � */ (char *)"NoExp",
	/* [199] � */ (char *)"cedilla",
	/* [200] � */ (char *)"NoExp",
	/* [201] � */ (char *)"�",
	/* [202] � */ (char *)"NoExp",
	/* [203] � */ (char *)"NoExp",
	/* [204] � */ (char *)"NoExp",
	/* [205] � */ (char *)"�",
	/* [206] � */ (char *)"NoExp",
	/* [207] � */ (char *)"NoExp",
	/* [208] � */ (char *)"NoExp",
	/* [209] � */ (char *)"e�e",
	/* [210] � */ (char *)"NoExp",
	/* [211] � */ (char *)"�",
	/* [212] � */ (char *)"NoExp",
	/* [213] � */ (char *)"NoExp",
	/* [214] � */ (char *)"NoExp",
	/* [215] � */ (char *)"signo de multiplicaci�n",
	/* [216] � */ (char *)"NoExp",
	/* [217] � */ (char *)"NoExp",
	/* [218] � */ (char *)"�",
	/* [219] � */ (char *)"NoExp",
	/* [220] � */ (char *)"�",
	/* [221] � */ (char *)"NoExp",
	/* [222] � */ (char *)"NoExp",
	/* [223] � */ (char *)"beta",
	/* [224] � */ (char *)"NoExp",
	/* [225] � */ (char *)"�",
	/* [226] � */ (char *)"NoExp",
	/* [227] � */ (char *)"NoExp",
	/* [228] � */ (char *)"NoExp",
	/* [229] � */ (char *)"NoExp",
	/* [230] � */ (char *)"NoExp",
	/* [231] � */ (char *)"cedilla",
	/* [232] � */ (char *)"NoExp",
	/* [233] � */ (char *)"�",
	/* [234] � */ (char *)"NoExp",
	/* [235] � */ (char *)"NoExp",
	/* [236] � */ (char *)"NoExp",
	/* [237] � */ (char *)"�",
	/* [238] � */ (char *)"NoExp",
	/* [239] � */ (char *)"NoExp",
	/* [240] � */ (char *)"NoExp",
	/* [241] � */ (char *)"e�e",
	/* [242] � */ (char *)"NoExp",
	/* [243] � */ (char *)"�",
	/* [244] � */ (char *)"NoExp",
	/* [245] � */ (char *)"NoExp",
	/* [246] � */ (char *)"NoExp",
	/* [247] � */ (char *)"signo de divisi�n",
	/* [248] � */ (char *)"NoExp",
	/* [249] � */ (char *)"NoExp",
	/* [250] � */ (char *)"�",
	/* [251] � */ (char *)"NoExp",
	/* [252] � */ (char *)"�",
	/* [253] � */ (char *)"NoExp",
	/* [254] � */ (char *)"NoExp",
	/* [255] � */ (char *)"NoExp"
	};

/**********************************************************/
