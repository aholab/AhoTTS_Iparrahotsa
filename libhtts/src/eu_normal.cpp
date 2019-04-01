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

Nombre fuente................ eu_normal.cpp
Nombre paquete............... normalizador
Lenguaje fuente.............. C++
Estado....................... desarrollo
Dependencia Hard/OS.......... -
Codigo condicional........... -

Codificacion................. Juan Luis Murugarren

Version  dd/mm/aa  Autor     Proposito de la edicion
-------  --------  --------  -----------------------
0.0.35	 24/09/13  Inaki	 Extender la no comprobación de pronunciable a las palabras con transcripción en el diccionario y formato "lpl" (Al-Khor)
0.0.34	 23/09/13  Inaki	 Comprobar si es Acrónimo antes de la normalizar grupos con "signos de puntuación" (IsComp), para que normalice bien siglas tipo II-HE
0.0.33	 18/07/13  Inaki	 Añadir intervalos horarios TIME_INTERVAL (10:30-11:15)
0.0.32	 09/07/13  Inaki	 Palabras con transcripción en diccionario (también declinadas) no se hacen "pronunciables"
0.0.31	 31/05/12  Inaki     Que decline bien las siglas
0.0.30	 09/03/07  inaxio    NUM_UNIT kasua gehitu da.
0.0.29   02/01/07  inaxio    NUM_RESTA eta NUM_SUMA kasuak gehitu dira.
0.0.28   29/12/06  inaxio    NUM_NEGATIVE kasua gehitu da.
0.0.27   07/07/05  Larraitz  Aldaketak isCap_cap eta isNum-eko aldaketak onartzeko
0.0.26   10/10/04  inigos    puntChop con diccionario e idioma
0.0.25   10/07/01  Yon2.     Dek bug!
0.0.24   18/06/01  Yon2.     Scape sequencies support.
0.0.23   07/05/01  Yon2.     Non dic Units.
0.0.22   07/05/01  Yon2.     Words with apost.
0.0.21   07/05/01  Yon2.     Languaje dependent filename.
0.0.20   25/04/01  Yon2.     Better Multiling support.
0.0.19   25/04/01  Yon2.     Multiling support.
0.0.18   08/04/01  Yon2.     Avoid Warnings.
0.0.17   07/04/01  Yon2.     Too Large Number.
0.0.16   30/03/01  Yon2.     spell non pron cell.
0.0.15   30/03/01  Yon2.     isPronun?
0.0.14   29/03/01  Yon2.     Percent.
0.0.13   28/03/01  Yon2.     Need More Data.
0.0.12   22/03/01  Yon2.     Abb, acr, units.
0.0.11   18/03/01  Yon2.     Roman -> more funcional.
0.0.10   03/03/01  Yon2.     Comp word expansion.
0.0.09   03/03/01  Yon2.     Not normalizable (already normalized) word declination.
0.0.08   12/02/01  Yon2.     Roman not inside date.
0.0.07   04/02/01  Yon2.     Added Heavy2 Debug Warnings to normalization cicle.
0.0.06   03/02/01  Yon2.     If group normalized -> don't check for another norm
0.0.05   15/01/01  Yon2.     Crude text list empty => don't proccess.
0.0.04   08/01/01  Yon2.     Flushing support.
0.0.03   06/01/01  Yon2.     Ultimo grupo aniadido completo?
0.0.02   04/01/01  Yon2.     Real Time normalizer!!!!!!
0.0.01   xx/12/00  Yon2.     Horas, fechas, numeros, deks, ...
0.0.00   19/11/00  Yon2.     Codificacion inicial.

======================== Contenido ========================

	Normalizador propiamente dicho.
	Versi¢n en euskara.

Yon2.

===========================================================
*/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/**********************************************************/


#include "eu_t2l.hpp"
#include "isofilt.h"

#include "string.h"

#include "httsmsg.h"



/**********************************************************/

CtI LangEU_TextToList::normal(VOID)
{
	CtI q;
	CtI p,firstNonP, lastToNoP;
	CtI IneedData = NULL;
	BOOL needMoreData = FALSE;

	dataNeed = FALSE;



	if (lastGrpProc)
		firstNonP = ct.nextGrp(lastGrpProc);
	else
		firstNonP = ct.firstGrp();



	if (procLastGrp)
		lastToNoP = NULL;
	else
		lastToNoP = ct.lastGrp();


	for (p=firstNonP; (p!=lastToNoP) && (!needMoreData); p=ct.nextGrp(p))
	{
		if (isScapeSeq(p))
			markScapeSeq(p);

		if (ct.isNorm(p)){
			continue;
		}

		switch (isDate(p))
		{
			case DATE_BASQUE:
				p = expdateYMD(p);
				break;
			case DATE_SPANISH:
				dateFromSpanish(p);
				p = expdateYMD(p);
				break;
			case DATE_ROMAN_BASQUE:
				dateFromRoman(p);
				p = expdateYMD(p);
				break;
			case DATE_ROMAN_SPANISH:
				dateFromRoman(p);
				dateFromSpanish(p);
				p = expdateYMD(p);
				break;
			case DATE_UNKNOWN:
			default:
				break;
		}

		if (ct.isNorm(p) && mustDek(p))
			p = dekline(p);
		if (ct.isNorm(p)){
			continue;
		}
		switch(isTime(p))
		{
			case TIME_SHORT:
				p = exptimeHM(p, FALSE);
				break;
			case TIME_LONG:
				p = exptimeHMS(p);
				break;
			case TIME_INTERVAL: //inaki, intervalo horarios (10:30-11:15)
				p = exptimeHMinterval(p);
				break;
			case TIME_UNKNOWN:
			default:
				break;
		}

		if (ct.isNorm(p) && mustDek(p))
			p = dekline(p);
		if (ct.isNorm(p)){
			continue;
		}
		switch(isNum(p))
		{
			case NUM_CARD:
				p = expCard(p);
				break;
			case NUM_ORD:
				p = expOrd(p, FALSE);
				break;
			case NUM_ORD_PUNT:
				p = expOrd(p, TRUE);
				break;
			case NUM_PUNT: //Zenbaki hamartarrak irakurtzeko, osoak hamarterrekin banatzeko puntua
				p = expPunt(p, TRUE);
				break;
			case NUM_COMA: //Zenbaki hamartarrak irakurtzeko, osoak hamarterrekin banatzeko koma
				p = expPunt(p, FALSE);
 				break;
			case NUM_NEGATIVE: //inaxio
				p = expNegative(p);
				break;
			case NUM_RESTA: //inaxio
				p = expSuma(p,false);
				break;
			case NUM_SUMA: //inaxio
				p = expSuma(p,true);
				break;
			case NUM_UNIT: //inaxio
				p = expUnit(p,true);
				break;
		/*	case NUM_RESULT_SPORT: //inaki, resultados partidos
				//fprintf(stderr, "ct=%s next=%s nextNext=%s", ct.cell(p).str, ct.cell(ct.next(p)).str, ct.cell(ct.next(ct.next(p))).str);
			//	strcat(ct.cell(p).str," ");

				//ct.del(ct.next(p));
				fprintf(stderr, "ct=%s next=%s", ct.cell(p).str, ct.cell(ct.next(p)).str);
				strcpy(ct(p).pattern, "n");
				p = expCard(p);
				ct.del(ct.next(p));
				ct.setTnor(p, UTYPENOR_NUMBER);
				p=ct.next(p);
				//p=ct.next(p);
				ct.setPatternForce(p, "n");
				//p = expCard(p);
				p=expnum(p);
				ct.setTnor(p, UTYPENOR_NUMBER);
				ct.del(ct.prev(p));
				//q=ct.prev(p);
				//q=p;
			//	ct.setPatternForce(p, (char*)"l");
				//ct.setStatus(q, stat);
				//ct.setTnor(p, UTYPENOR_NUMBER);

				//q=ct.prev(q);
				//ct.delGrp(q);
				//ct.del(ct.next(p));
			//	continue;
				break;*/
			case NUM_TOO_LARGE:
				p = expandGrp(p);
				break;
			case NUM_NEEDMOREDATA:
				IneedData = p;
				needMoreData = TRUE;
				dataNeed = TRUE;
				break;
			case NUM_UNKNOWN:
			default:
				break;
		}

		if (needMoreData){
			continue;
		}
		if (ct.isNorm(p) && mustDek(p))
			p = dekline(p);

		if (ct.isNorm(p)){
			continue;
		}
		switch(isRomanN(p))
		{
			case ROMAN_ROMAN:
				p = expRoman(p, FALSE, FALSE);
				break;
			case ROMAN_ROMAN_P:
				p = expRoman(p, TRUE, FALSE);
				break;
			case ROMAN_ROMAN_PUNT:
				p = expRoman(p, FALSE, TRUE);
				break;
			case ROMAN_NEEDMOREDATA:
				IneedData = p;
				needMoreData = TRUE;
				dataNeed = TRUE;
				break;
			case ROMAN_UNKNOWN:
			default:
				break;
		}


		if (needMoreData)
			continue;
		if (ct.isNorm(p) && mustDek(p))
			p = dekline(p);
		if (ct.isNorm(p))
			continue;
///////////////////////////////////
		switch (isAbbAcrUni(p))
		{
			case AAU_ABB:
			case AAU_ACR:
				p = expAbbAcrUni(p, FALSE, FALSE );
				break;
			case AAU_UNIT:
				p = expAbbAcrUni(p, FALSE, TRUE );
				break;
			case AAU_ABBP:
			case AAU_ACRP:
				p = expAbbAcrUni(p, TRUE, FALSE );
				break;
			case AAU_UNITP:
				p = expAbbAcrUni(p, TRUE, TRUE );
				break;
			case AAU_NEEDMOREDATA:
				IneedData = p;
				needMoreData = TRUE;
				dataNeed = TRUE;
				break;
			case AAU_UNKNOWN:
			default:
				break;
		}

		if (needMoreData)
			continue;
		if (ct.isNorm(p) && mustDek(p))
			p = dekline(p);
		if (ct.isNorm(p))
			continue;

///////////////////
//INAKI
		HDicRef myref;
		myref = dic->search(ct(p).str);
		int len = dic->query(myref, HDIC_QUERY_MATCHLEN);
		int len_str = strlen(ct(p).str);
		//fprintf(stderr,"str=%s\tlen=%d\tlen_str=%d dic->query(myref,HDIC_QUERY_EU_TF_MRK)=%d\tpattern=%s\n", ct(p).str, len, len_str,dic->query(myref,HDIC_QUERY_EU_TF_MRK), ct(p).pattern);
//		if(dic->query(myref,HDIC_QUERY_EU_TF_MRK) == 1 && len == len_str && ct(p).pattern && !strcmp(ct(p).pattern, "l")){ //INAKI si está marcada como transcripción, suponemos que es pronunciable
		if(dic->query(myref,HDIC_QUERY_EU_TF_MRK) == 1 && len == 0 && ct(p).pattern && !strcmp(ct(p).pattern, "l")){ //INAKI si está marcada como transcripción, suponemos que es pronunciable
			pCHAR exp;
			myref = dic->search(ct(p).str, &exp);
			//fprintf(stderr,"Markatuta %s len=%d\texp=%s\n", ct(p).str, len, exp);
			//if (ct.isNorm(p) && mustDek(p))
			//if (mustDek(p))
				//p = dekline(p);
			continue;
		}
		else if(dic->query(myref,HDIC_QUERY_EU_TF_MRK) == 1 && ct(p).pattern && !strcmp(ct(p).pattern, "l")){ //match parcial, ver si el resto es declinación
			//fprintf(stderr,"match parcial\n");
			char decli[100];
			strcpy(decli, ct(p).str + len);
			myref = dic->search(decli);
			BOOL isDec = dic->query(myref,HDIC_QUERY_EU_DEC);
			len = dic->query(myref, HDIC_QUERY_MATCHLEN);
			int len_decli = strlen(decli);
		//	fprintf(stderr,"match parcial decli=%s len=%d len_decli=%d query_dec=%d\n", decli, len, len_decli, dic->query(myref,HDIC_QUERY_EU_DEC));
			if(isDec && len == 0){
			//	fprintf(stderr,"continua\n");
				continue;
			}
		}
		else{
			if(ct(p).pattern){
				/*if(strlen(ct(p).pattern) == 3 && !strcmp(ct(p).pattern, "lpl") && dic->query(myref,HDIC_QUERY_EU_TF_MRK) == 1){ //palabra marcada seguida de declinación p.e. Kate-rekin
					CtI q;
					char decli[100];
					q=ct.next(p);
					q=ct.next(q);
					strcpy(decli, ct(q).str);
					myref = dic->search(decli);
					BOOL isDec = dic->query(myref,HDIC_QUERY_EU_DEC);
					if(isDec){
						fprintf(stderr,"isDec\n");
						continue;
					}


				}
				else*/ if(strlen(ct(p).pattern) == 3 && !strcmp(ct(p).pattern, "lpl")){ //p.e. Al-Khor
					CtI q;
					char temp [256];
					strcpy(temp, ct(p).str);
					q=ct.next(p);
					strcat(temp, ct(q).str);
					q=ct.next(q);
					strcat(temp, ct(q).str);
					myref = dic->search(temp);
				//	fprintf(stderr,"temp=%s\n", temp);
					int len = dic->query(myref, HDIC_QUERY_MATCHLEN);
					//int len_str = strlen(ct(p).str);
					if(dic->query(myref,HDIC_QUERY_EU_TF_MRK) && len == 0) { //INAKI si está marcada como transcripción, suponemos que es pronunciable
						//fprintf(stderr,"markaturik\n");
						//copiamos todo el pattern a una sola celda
						strcpy(ct(p).pattern, "l");
						strcpy(ct(p).str, temp);
						ct.del(ct.next(p));
						ct.del(ct.next(p));
						continue;
					}
				}
				else if(strlen(ct(p).pattern) == 5 && !strcmp(ct(p).pattern, "lplpl")){ //p.e. digne-les-bains
					CtI q;
					char temp [256];
					strcpy(temp, ct(p).str);
					q=ct.next(p);
					strcat(temp, ct(q).str);
					q=ct.next(q);
					strcat(temp, ct(q).str);
					q=ct.next(q);
					strcat(temp, ct(q).str);
					q=ct.next(q);
					strcat(temp, ct(q).str);
					myref = dic->search(temp);
					//fprintf(stderr,"temp=%s\n", temp);
					int len = dic->query(myref, HDIC_QUERY_MATCHLEN);
					//int len_str = strlen(ct(p).str);
					if(dic->query(myref,HDIC_QUERY_EU_TF_MRK) && len == 0){ //INAKI si está marcada como transcripción, suponemos que es pronunciable
						//fprintf(stderr,"markaturik\n");
						strcpy(ct(p).pattern, "l");
						strcpy(ct(p).str, temp);
						ct.del(ct.next(p));
						ct.del(ct.next(p));
						ct.del(ct.next(p));
						ct.del(ct.next(p));
						continue;
					}
				}
			}

		}
		//fprintf(stderr,"sale\n");
////////////////////////////////////

		if (isComp(p))
			p = expComp(p);

		if (ct.isNorm(p) && mustDek(p))
			p = dekline(p);
		if (ct.isNorm(p))
			continue;

		if (isUnit(p))
			p = expUnit(p, FALSE);

		if (ct.isNorm(p) && mustDek(p))
			p = dekline(p);

		if (ct.isNorm(p))
			continue;

		if (isApost(p))
			p = expApost(p);

		if (ct.isNorm(p) && mustDek(p))
			p = dekline(p);

		if (ct.isNorm(p))
			continue;
		//fprintf(stderr,"sale2\n");
/*		switch (isAbbAcrUni(p)) //Inaki realizar la comprobación de Acrónimo, etc antes de IsComp para que maneje siglas con -: pe. II-HE
		{
			case AAU_ABB:
			case AAU_ACR:
				p = expAbbAcrUni(p, FALSE, FALSE );
				break;
			case AAU_UNIT:
				p = expAbbAcrUni(p, FALSE, TRUE );
				break;
			case AAU_ABBP:
			case AAU_ACRP:
				p = expAbbAcrUni(p, TRUE, FALSE );
				break;
			case AAU_UNITP:
				p = expAbbAcrUni(p, TRUE, TRUE );
				break;
			case AAU_NEEDMOREDATA:
				IneedData = p;
				needMoreData = TRUE;
				dataNeed = TRUE;
				break;
			case AAU_UNKNOWN:
			default:
				break;
		}

		if (needMoreData)
			continue;
		if (ct.isNorm(p) && mustDek(p))
			p = dekline(p);
		if (ct.isNorm(p))
			continue;*/
		switch(isPercent(p))
		{
			case PERCENT_BASQUE:
				p = expPercent( p , TRUE );
				break;
			case PERCENT_SPANISH:
				p = expPercent( p , FALSE );
				break;
			case PERCENT_NEEDMOREDATA:
				IneedData = p;
				needMoreData = TRUE;
				dataNeed = TRUE;
				break;
			case PERCENT_UNKNOWN:
			default:
				break;
		}

		if (needMoreData)
			continue;

		if (ct.isNorm(p) && mustDek(p))
			p = dekline(p);

		if (ct.isNorm(p))
			continue;

		if (mustExpand(p))
			p = expandGrp(p);

		if (ct.isNorm(p) && mustDek(p))
			p = dekline(p);
		if (ct.isNorm(p))
			continue;
		//fprintf(stderr,"sale3\n");
		if ((ct.getTnor(p) == UTYPENOR_UNKNOWN)&& (!isPuntt(p)))
		{
			//fprintf(stderr,"sale4\n");
			ct.setTnor(p, UTYPENOR_NORMAL);
			switch (isCap(p))
			{
			case 1://hitzeko letra guztiak maiuskulaz
				//inaki para que no deletree cuando todas las letras son en mayusculas
				if (ct.isNorm(p) && mustDek(p)){ p = dekline(p); }
				break;
				//if (!isPronun(p))	p = expandCell(p);
				//break;
			case 2: // hitzeko lehen letra maiuskulaz
				if (!isPronun(p)){
					//fprintf(stderr,"entra\n");
					//si tiene transcripción en el diccionario no llama a pronounce para tratar de hacerla pronunciable
					HDicRef myref;
					myref = dic->search(ct(p).str);
					int len = dic->query(myref, HDIC_QUERY_MATCHLEN);
					/*if(len==0){ //si no se ha encontrado, se pronuncia
						fprintf(stderr,"not found str=%s\n", ct(p).str);
						if(!dic->query(myref,HDIC_QUERY_EU_TF_MRK))//inaki
							p = pronounce(p);
					}
					else if (strlen(ct(p).str) == len){
						fprintf(stderr,"Totally found len=%d\n", len);
						if(!dic->query(myref,HDIC_QUERY_EU_TF_MRK))
							p = pronounce(p);
					}
					else{
						fprintf(stderr,"partially found len=%d\n", len);
						//si se ha encontrado pero parcialmente, se mira a ver si el resto es declinación, y si no lo es, se pronuncia
						char decli[100];
						strcpy(decli, ct(p).str + len);
						myref = dic->search(decli);
						BOOL isDec = dic->query(myref, HDIC_QUERY_EU_DEC);
						if(!isDec)
							p = pronounce(p);
					}*/
					if(len==0){ //si se ha encontrado
						//fprintf(stderr,"Totally found len=%d\n", len);
						if(!dic->query(myref,HDIC_QUERY_EU_TF_MRK))
							p = pronounce(p);
					//	fprintf(stderr,"not found str=%s\n", ct(p).str);
						if(!dic->query(myref,HDIC_QUERY_EU_TF_MRK))//inaki
							p = pronounce(p);
					}
					/*else if (strlen(ct(p).str) == len){
						fprintf(stderr,"Totally found len=%d\n", len);
						if(!dic->query(myref,HDIC_QUERY_EU_TF_MRK))
							p = pronounce(p);
					}*/
					else{
						//fprintf(stderr,"partially found len=%d\n", len);
						//si se ha encontrado pero parcialmente, se mira a ver si el resto es declinación, y si no lo es, se pronuncia
						char decli[100];
						strcpy(decli, ct(p).str + len);
						myref = dic->search(decli);
						BOOL isDec = dic->query(myref, HDIC_QUERY_EU_DEC);
						if(!isDec)
							p = pronounce(p);
					}
				}
				break;
			case 3: //hitzeko letrak maiuskulaz eta minuskulaz
				if (!isPronun(p))	p = expandCell(p);
				break;
			case 4: // hitzak lehen zatia maiuskulaz eta bigarrena minuskulaz
				//if (!isPronun(p))	p=mayusDekline(p); //inaki, para que decline bien todas las siglas se elimina la comprobación de que NO sea pronunciable
				p=mayusDekline(p);
				break;
			case 5: // hitzeko letra guztiak minuskulaz
				//fprintf(stderr,"denak minuskulaz str=%s\n", ct(p).str);
				if (!isPuntt(p) && !isPronun(p)){
					//si tiene transcripción en el diccionario no llama a pronounce para tratar de hacerla pronunciable
					HDicRef myref;
					//fprintf(stderr,"minuskulaz\n");
					myref = dic->search(ct(p).str);
					int len = dic->query(myref, HDIC_QUERY_MATCHLEN);
					if(len==0){ //si no se ha encontrado, se pronuncia
					//	fprintf(stderr,"not found str=%s\n", ct(p).str);
						//if(!dic->query(myref,HDIC_QUERY_EU_TF_MRK))//inaki
							p = pronounce(p);
					}
					else if (strlen(ct(p).str) == len){ //si se ha encontrado y el match es total, no se pronuncia si está marcada con transcripción
						//fprintf(stderr,"Totally found len=%d\n", len);
						if(!dic->query(myref,HDIC_QUERY_EU_TF_MRK))
							p = pronounce(p);
					}
					else{
						//fprintf(stderr,"partially found len=%d\n", len);
						//si se ha encontrado pero parcialmente, se mira a ver si el resto es declinación, y si no lo es, se pronuncia
						char decli[100];
						strcpy(decli, ct(p).str + len);
						int marcada= dic->query(myref,HDIC_QUERY_EU_TF_MRK);
						myref = dic->search(decli);
						BOOL isDec = dic->query(myref, HDIC_QUERY_EU_DEC);
						int len_decli = dic->query(myref, HDIC_QUERY_MATCHLEN);
						if(len_decli != strlen(decli))
							isDec=FALSE;
						if(!isDec || !marcada)
							p = pronounce(p);
					}
				}
				if (ct.isNorm(p) && mustDek(p)){ p = dekline(p); }
				break;
			default:
				break;
			}
		}
	}
	return needMoreData?ct.prevGrp(IneedData):(procLastGrp?ct.lastGrp():ct.prevGrp(ct.lastGrp()));
}

/**********************************************************/


/**********************************************************/

INT LangEU_TextToList::ct2nt(const CHAR *str, BOOL flush)
{
  INT retval = 0;
  pCHAR ibuffer=NULL;
  CtI lastGrp;

  if (!flush) {
    ibuffer = strdup(str);

    if (ibuffer) retval = strlen(ibuffer);
    else return 0;

    buff_fltr(ibuffer);

#ifdef HEAVY_DEBUG
    htts_warn("EU Input Buffer: [%s]", ibuffer);
#endif


// Parser EML
// Dentro se llama a preChop

	lastGrp = parserEmo (ibuffer, FALSE);

	if (ct.empty()) {
      free(ibuffer);
      return retval;
    }

    if (!ct(ct.lastGrp()).pattern) procLastGrp = FALSE;
    else procLastGrp = TRUE;
    free(ibuffer);
  }

  else
  {
	lastGrp = parserEmo (ibuffer, TRUE);
  }



#ifdef HEAVY_DEBUG2
       htts_warn("EU Ct2nt: Pre norm cicle.");
#endif

  if ((procLastGrp?ct.lastGrp():ct.prevGrp(ct.lastGrp())) != lastGrpProc)  {

#ifdef HEAVY_DEBUG2
       htts_warn("EU Ct2nt: inside norm cicle.");
#endif

    puntChop(dic);

#ifdef HEAVY_DEBUG2
       htts_warn("EU Ct2nt: postPuntChop.");
#endif

    dekChop();

#ifdef HEAVY_DEBUG2
       htts_warn("EU Ct2nt: PostDekChop.");
#endif
       lastGrpProc = normal();

#ifdef HEAVY_DEBUG2
       htts_warn("EU Ct2nt: PostNormal.");
#endif

  }
#ifdef HEAVY_DEBUG2
  htts_warn("EU Ct2nt: Post norm cicle.");
#endif

  return retval;
}

/**********************************************************/


/**********************************************************/

INT LangEU_TextToList::ct2nt(BOOL flush)
{
  return flush?ct2nt("", flush):0;
}

/**********************************************************/


