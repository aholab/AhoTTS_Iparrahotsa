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

Nombre fuente................ eu_abbabr.cpp
Nombre paquete............... normalizador
Lenguaje fuente.............. C++
Estado....................... desarrollo
Dependencia Hard/OS.......... -
Codigo condicional........... -

Codificacion................. inigos

Version  dd/mm/aa  Autor     Proposito de la edicion
-------  --------  --------  -----------------------
0.0.2	 20/10/08  inaki     A�adir u con di�resis
0.0.1	 29/12/06  inaxio     puntChop-en aldaketak zenbaki negatiboak identifikatzeko.
0.0.0    11/10/04  inigos     Codificacion inicial.

======================== Contenido ========================

Funciones virtuales de wordChop dependientes del idioma

===========================================================
*/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/**********************************************************/

#include "eu_t2l.hpp"
#include "chartype.h"

/**********************************************************/

/**********************************************************/

INT eu_chtype[256] = {
	/* [000] C */ CHTYPE_NULL,
	/* [001] C */ CHTYPE_NULL,
	/* [002] C */ CHTYPE_NULL,
	/* [003] C */ CHTYPE_NULL,
	/* [004] C */ CHTYPE_NULL,
	/* [005] C */ CHTYPE_NULL,
	/* [006] C */ CHTYPE_NULL,
	/* [007] C */ CHTYPE_NULL,
	/* [008] C */ CHTYPE_NULL,
	/* [009] C */ CHTYPE_DELIM,
	/* [010] C */ CHTYPE_DELIM,
	/* [011] C */ CHTYPE_NULL,
	/* [012] C */ CHTYPE_NULL,
	/* [013] C */ CHTYPE_DELIM,
	/* [014] C */ CHTYPE_NULL,
	/* [015] C */ CHTYPE_NULL,
	/* [016] C */ CHTYPE_NULL,
	/* [017] C */ CHTYPE_NULL,
	/* [018] C */ CHTYPE_NULL,
	/* [019] C */ CHTYPE_NULL,
	/* [020] C */ CHTYPE_NULL,
	/* [021] C */ CHTYPE_NULL,
	/* [022] C */ CHTYPE_NULL,
	/* [023] C */ CHTYPE_NULL,
	/* [024] C */ CHTYPE_NULL,
	/* [025] C */ CHTYPE_NULL,
	/* [026] C */ CHTYPE_NULL,
	/* [027] C */ CHTYPE_NULL,
	/* [028] C */ CHTYPE_NULL,
	/* [029] C */ CHTYPE_NULL,
	/* [030] C */ CHTYPE_NULL,
	/* [031] C */ CHTYPE_NULL,
	/* [032]   */ CHTYPE_DELIM,
	/* [033] ! */ CHTYPE_PUNTT,
	/* [034] " */ CHTYPE_PUNTT,
	/* [035] # */ CHTYPE_SYMBL,
	/* [036] $ */ CHTYPE_SYMBL,
	/* [037] % */ CHTYPE_SYMBL,
	/* [038] & */ CHTYPE_SYMBL,
	/* [039] ' */ CHTYPE_PUNTT,
	/* [040] ( */ CHTYPE_PUNTT,
	/* [041] ) */ CHTYPE_PUNTT,
	/* [042] * */ CHTYPE_SYMBL,
	/* [043] + */ CHTYPE_SYMBL,
	/* [044] , */ CHTYPE_PUNTT,
	/* [045] - */ CHTYPE_PUNTT,
	/* [046] . */ CHTYPE_PUNTT,
	/* [047] / */ CHTYPE_SYMBL,
	/* [048] 0 */ CHTYPE_DIGIT,
	/* [049] 1 */ CHTYPE_DIGIT,
	/* [050] 2 */ CHTYPE_DIGIT,
	/* [051] 3 */ CHTYPE_DIGIT,
	/* [052] 4 */ CHTYPE_DIGIT,
	/* [053] 5 */ CHTYPE_DIGIT,
	/* [054] 6 */ CHTYPE_DIGIT,
	/* [055] 7 */ CHTYPE_DIGIT,
	/* [056] 8 */ CHTYPE_DIGIT,
	/* [057] 9 */ CHTYPE_DIGIT,
	/* [058] : */ CHTYPE_PUNTT,
	/* [059] ; */ CHTYPE_PUNTT,
	/* [060] < */ CHTYPE_SYMBL,
	/* [061] = */ CHTYPE_SYMBL,
	/* [062] > */ CHTYPE_SYMBL,
	/* [063] ? */ CHTYPE_PUNTT,
	/* [064] @ */ CHTYPE_SYMBL,
	/* [065] A */ CHTYPE_LETTR,
	/* [066] B */ CHTYPE_LETTR,
	/* [067] C */ CHTYPE_LETTR,
	/* [068] D */ CHTYPE_LETTR,
	/* [069] E */ CHTYPE_LETTR,
	/* [070] F */ CHTYPE_LETTR,
	/* [071] G */ CHTYPE_LETTR,
	/* [072] H */ CHTYPE_LETTR,
	/* [073] I */ CHTYPE_LETTR,
	/* [074] J */ CHTYPE_LETTR,
	/* [075] K */ CHTYPE_LETTR,
	/* [076] L */ CHTYPE_LETTR,
	/* [077] M */ CHTYPE_LETTR,
	/* [078] N */ CHTYPE_LETTR,
	/* [079] O */ CHTYPE_LETTR,
	/* [080] P */ CHTYPE_LETTR,
	/* [081] Q */ CHTYPE_LETTR,
	/* [082] R */ CHTYPE_LETTR,
	/* [083] S */ CHTYPE_LETTR,
	/* [084] T */ CHTYPE_LETTR,
	/* [085] U */ CHTYPE_LETTR,
	/* [086] V */ CHTYPE_LETTR,
	/* [087] W */ CHTYPE_LETTR,
	/* [088] X */ CHTYPE_LETTR,
	/* [089] Y */ CHTYPE_LETTR,
	/* [090] Z */ CHTYPE_LETTR,
	/* [091] [ */ CHTYPE_SYMBL,
	/* [092] \ */ CHTYPE_SYMBL,
	/* [093] ] */ CHTYPE_SYMBL,
	/* [094] ^ */ CHTYPE_SYMBL,
	/* [095] _ */ CHTYPE_SYMBL,
	/* [096] ` */ CHTYPE_NULL,
	/* [097] a */ CHTYPE_LETTR,
	/* [098] b */ CHTYPE_LETTR,
	/* [099] c */ CHTYPE_LETTR,
	/* [100] d */ CHTYPE_LETTR,
	/* [101] e */ CHTYPE_LETTR,
	/* [102] f */ CHTYPE_LETTR,
	/* [103] g */ CHTYPE_LETTR,
	/* [104] h */ CHTYPE_LETTR,
	/* [105] i */ CHTYPE_LETTR,
	/* [106] j */ CHTYPE_LETTR,
	/* [107] k */ CHTYPE_LETTR,
	/* [108] l */ CHTYPE_LETTR,
	/* [109] m */ CHTYPE_LETTR,
	/* [110] n */ CHTYPE_LETTR,
	/* [111] o */ CHTYPE_LETTR,
	/* [112] p */ CHTYPE_LETTR,
	/* [113] q */ CHTYPE_LETTR,
	/* [114] r */ CHTYPE_LETTR,
	/* [115] s */ CHTYPE_LETTR,
	/* [116] t */ CHTYPE_LETTR,
	/* [117] u */ CHTYPE_LETTR,
	/* [118] v */ CHTYPE_LETTR,
	/* [119] w */ CHTYPE_LETTR,
	/* [120] x */ CHTYPE_LETTR,
	/* [121] y */ CHTYPE_LETTR,
	/* [122] z */ CHTYPE_LETTR,
	/* [123] { */ CHTYPE_SYMBL,
	/* [124] | */ CHTYPE_SYMBL,
	/* [125] } */ CHTYPE_SYMBL,
	/* [126] ~ */ CHTYPE_SYMBL,
	/* [127] C */ CHTYPE_NULL,
	/* [128] C */ CHTYPE_NULL,
	/* [129] C */ CHTYPE_NULL,
	/* [130] C */ CHTYPE_NULL,
	/* [131] C */ CHTYPE_NULL,
	/* [132] C */ CHTYPE_NULL,
	/* [133] C */ CHTYPE_NULL,
	/* [134] C */ CHTYPE_NULL,
	/* [135] C */ CHTYPE_NULL,
	/* [136] C */ CHTYPE_NULL,
	/* [137] C */ CHTYPE_NULL,
	/* [138] C */ CHTYPE_NULL,
	/* [139] C */ CHTYPE_NULL,
	/* [140] C */ CHTYPE_NULL,
	/* [141] C */ CHTYPE_NULL,
	/* [142] C */ CHTYPE_NULL,
	/* [143] C */ CHTYPE_NULL,
	/* [144] C */ CHTYPE_NULL,
	/* [145] C */ CHTYPE_NULL,
	/* [146] C */ CHTYPE_NULL,
	/* [147] C */ CHTYPE_NULL,
	/* [148] C */ CHTYPE_NULL,
	/* [149] C */ CHTYPE_NULL,
	/* [150] C */ CHTYPE_NULL,
	/* [151] C */ CHTYPE_NULL,
	/* [152] C */ CHTYPE_NULL,
	/* [153] C */ CHTYPE_NULL,
	/* [154] C */ CHTYPE_NULL,
	/* [155] C */ CHTYPE_NULL,
	/* [156] C */ CHTYPE_NULL,
	/* [157] C */ CHTYPE_NULL,
	/* [158] C */ CHTYPE_NULL,
	/* [159] C */ CHTYPE_NULL,
	/* [160] C */ CHTYPE_NULL,
	/* [161] � */ CHTYPE_PUNTT,
	/* [162] � */ CHTYPE_NULL,
	/* [163] � */ CHTYPE_SYMBL,
	/* [164] � */ CHTYPE_SYMBL, //i�aki --> simbolo euro
	/* [165] � */ CHTYPE_SYMBL,
	/* [166] � */ CHTYPE_NULL,
	/* [167] � */ CHTYPE_NULL,
	/* [168] � */ CHTYPE_NULL,
	/* [169] � */ CHTYPE_SYMBL,
	/* [170] � */ CHTYPE_NULL,
	/* [171] � */ CHTYPE_PUNTT,
	/* [172] � */ CHTYPE_NULL,
	/* [173] � */ CHTYPE_NULL,
	/* [174] � */ CHTYPE_NULL,
	/* [175] � */ CHTYPE_SYMBL,
	/* [176] � */ CHTYPE_SYMBL,
	/* [177] � */ CHTYPE_SYMBL,
	/* [178] � */ CHTYPE_SYMBL,
	/* [179] � */ CHTYPE_SYMBL,
	/* [180] � */ CHTYPE_NULL,
	/* [181] � */ CHTYPE_SYMBL,
	/* [182] � */ CHTYPE_NULL,
	/* [183] � */ CHTYPE_SYMBL,
	/* [184] � */ CHTYPE_NULL,
	/* [185] � */ CHTYPE_NULL,
	/* [186] � */ CHTYPE_NULL,
	/* [187] � */ CHTYPE_PUNTT,
	/* [188] � */ CHTYPE_SYMBL,
	/* [189] � */ CHTYPE_SYMBL,
	/* [190] � */ CHTYPE_SYMBL,
	/* [191] � */ CHTYPE_PUNTT,
	/* [192] � */ CHTYPE_NULL,
	/* [193] � */ CHTYPE_LETTR,
	/* [194] � */ CHTYPE_NULL,
	/* [195] � */ CHTYPE_NULL,
	/* [196] � */ CHTYPE_NULL,
	/* [197] � */ CHTYPE_NULL,
	/* [198] � */ CHTYPE_NULL,
	/* [199] � */ CHTYPE_NULL,
	/* [200] � */ CHTYPE_NULL,
	/* [201] � */ CHTYPE_LETTR,
	/* [202] � */ CHTYPE_NULL,
	/* [203] � */ CHTYPE_NULL,
	/* [204] � */ CHTYPE_NULL,
	/* [205] � */ CHTYPE_LETTR,
	/* [206] � */ CHTYPE_NULL,
	/* [207] � */ CHTYPE_NULL,
	/* [208] � */ CHTYPE_NULL,
	/* [209] � */ CHTYPE_LETTR,
	/* [210] � */ CHTYPE_NULL,
	/* [211] � */ CHTYPE_LETTR,
	/* [212] � */ CHTYPE_NULL,
	/* [213] � */ CHTYPE_NULL,
	/* [214] � */ CHTYPE_NULL,
	/* [215] � */ CHTYPE_SYMBL,
	/* [216] � */ CHTYPE_NULL,
	/* [217] � */ CHTYPE_NULL,
	/* [218] � */ CHTYPE_LETTR,
	/* [219] � */ CHTYPE_NULL,
	/* [220] � */ CHTYPE_LETTR, //inaki
	/* [221] � */ CHTYPE_NULL,
	/* [222] � */ CHTYPE_NULL,
	/* [223] � */ CHTYPE_SYMBL,
	/* [224] � */ CHTYPE_NULL,
	/* [225] � */ CHTYPE_LETTR,
	/* [226] � */ CHTYPE_NULL,
	/* [227] � */ CHTYPE_NULL,
	/* [228] � */ CHTYPE_NULL,
	/* [229] � */ CHTYPE_NULL,
	/* [230] � */ CHTYPE_NULL,
	/* [231] � */ CHTYPE_NULL,
	/* [232] � */ CHTYPE_NULL,
	/* [233] � */ CHTYPE_LETTR,
	/* [234] � */ CHTYPE_NULL,
	/* [235] � */ CHTYPE_NULL,
	/* [236] � */ CHTYPE_NULL,
	/* [237] � */ CHTYPE_LETTR,
	/* [238] � */ CHTYPE_NULL,
	/* [239] � */ CHTYPE_NULL,
	/* [240] � */ CHTYPE_NULL,
	/* [241] � */ CHTYPE_LETTR,
	/* [242] � */ CHTYPE_NULL,
	/* [243] � */ CHTYPE_LETTR,
	/* [244] � */ CHTYPE_NULL,
	/* [245] � */ CHTYPE_NULL,
	/* [246] � */ CHTYPE_NULL,
	/* [247] � */ CHTYPE_SYMBL,
	/* [248] � */ CHTYPE_NULL,
	/* [249] � */ CHTYPE_NULL,
	/* [250] � */ CHTYPE_LETTR,
	/* [251] � */ CHTYPE_NULL,
	/* [252] � */ CHTYPE_LETTR, //inaki
	/* [253] � */ CHTYPE_NULL,
	/* [254] � */ CHTYPE_NULL,
	/* [255] � */ CHTYPE_NULL
};

/**********************************************************/

INT LangEU_TextToList::getchtype(CHAR c)
{
	void *j = &c;
	return eu_chtype[ *((pUCHAR)j)];
}

/**********************************************************/


/***********************************************************************/

CtI LangEU_TextToList::puntChop(HDicDB *dic)
{
	CtI p, firstNonP, lastToNoP;


  if (lastGrpProc) firstNonP = ct.nextGrp(lastGrpProc);
  else firstNonP = ct.firstGrp();

  if (procLastGrp) lastToNoP = NULL;
  else lastToNoP = ct.lastGrp();

	for(p=firstNonP; p!=lastToNoP; p=ct.nextGrp(p))	{
		//fprintf(stderr, "ct(p)=%s\tpattern=%s\n", ct(p).str, ct(p).pattern);
		if (hasLeftPuntt(ct(p).pattern))
		{
			//fprintf(stderr,"\t hasleftpuntt\n");
		//inaxio->Zenbaki negatiboen kasuan(-n)ez da patroia ezkerretik moztu behar:
			pCHAR pattern;//inaxio
			if (ct(p).pattern) pattern = strdup(ct(p).pattern);//inaxio
			if(((ct.getStr(p))[0]=='-') && (pattern[1]=='n'));//inaxio
 			else patCutLeft(p);//inaxio
		}
		if (hasRightPuntt(ct(p).pattern))
		{
			//fprintf(stderr,"\t hasrightpuntt\n");
			pCHAR temp = NULL;
			INT len, abbacr;
			HDicRef myref;
			pCHAR pattern;
			CtI q;
			UINT i;

			if (ct(p).pattern) pattern = strdup(ct(p).pattern);

			//Construimos la posible abb

			q = p;
			temp = strdup(ct.getStr(q));
			for ( i = 1; i < strlen(pattern); i++)
			{
				q=ct.next(q);
				temp = concatStr(temp, ct.getStr(q));
			}
			free(pattern); // Ya no nos hace falta.

			//La buscamos en el diccionario.
			myref = dic->search(temp);
			free(temp); //I�AKI
			len = dic->query(myref, HDIC_QUERY_MATCHLEN);
			if (!len)
			{
				abbacr = dic->query(myref, HDIC_QUERY_EU_NOR);
				if (abbacr != HDIC_ANSWER_EU_NOR_ABB)
				{
					patCutRight(p);
				}
				else // Hay que mirar si es lo �ltimo
				{
					if(!ct.nextGrp(p)) // Es el �ltimo
					{
						patCutRight(p);
						ct.setTnor(p, UTYPENOR_UNKGROUP);
					}
				}
			}
			else
			{
				patCutRight(p);
			}
		}

	}

  return procLastGrp?ct.lastGrp():ct.prevGrp(ct.lastGrp());
}

/*************************************************************************/
