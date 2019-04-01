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
/*
(C) 2005 TSR/Aholab - ETSII/IT Bilbo (UPV/EHU)

Iturryaren izena................ eu_mrk_tf.cpp
Lenguaia ......................... C++
Egoera  ............................Erabilgarria

Kodeketa: ...............................Nora Barroso

Bertsioa  uu/hh/ee    Egilea     Oharrak
-----------------------------------------------------------
0.0.5		2014/08/25  inaki		corregir bugs
0.0.4		2013/11/29	inaki		corregir soporte para palabras en mayúsculas
0.0.3		2013/09/06	inaki		corregir alineado de los fonemas debido a un bug en el cálculo del número de puntos (separadores) en la transcripción
0.0.2		2008/10/20	inaki		corregir problema con el diccionario
0.0.1		2005/03/16	Nora		Hitzen transkripzio fonetikoa hitzegian agertu ahal izateko


======================== Edukina ===================================================
{{LangEU_PhTrans}}prozedura, transkripzio fonetikoa hiztegitik hartzen du, "tf_mrk" markarekin markaturik dauden hitzetan.

Hiztegitik hartzen den transkripzio fonetikoa itxura hau izan beharko luke:
hasiera	ize	tf_mrk	%a.s.i.e.r.a

Fonemak desberdintzeko puntu seinua erabiltzen da. Puntuaren erabilpenaren zergaitia nabaria da;
SAMPA kode zehatz batzuk 2 edo 3 grafiekin adierzten dira, hala nola; "s´", "tS", "tz", "ts", "ts´" eta "rr".
ezer	ior	 tf_mrk	%e.s´.e.rr
=================================================================================
*/


#include <string.h>
#include <math.h>

#include "chset.h"
#include "eu_lingp.hpp"
#include "uti.h"
#include "uttws.hpp"


#ifdef USE_TOKENIZER
UttI LangEU_PhTrans::tf_mrk_ch2ph(UttPh & u, UttI senp)
//VOID LangEU_PhTrans::tf_mrk_ch2ph(UttPh & u, UttI senp)
{

#define SETPH(p,ph)  u.cell(p).setPhone(ph)							//Fonema bat ezartzeko
#define SETSTREUS(p) u.cell(p).setStress(USTRESS_TEXT)	//Azentua ezartzeko
#define NEXT(p)  u.charNext(p,URANGE_WORD)					//Seinalatzailea elementu bat aurreratzen da, letra mailen

	HDicDB * mydic;
	HDicRef myref;
	pCHAR exp;
	CHAR * word;
	UttI pTF,pTF2;
	CHAR * transkrip;
	INT	lengTF, lengWORD, dif, lengTFPKin, lengWORDPKin, numP;
	INT	i=0;

	mydic=new LangEU_HDicDB; //INAKI
	mydic->create(getPhTHDicName()); //INAKI
	//Hiztegian egin behar den BILAKETA
	pTF=u.charFirst(senp, URANGE_WORD);
	//mydic=u.getHDicDB(); //INAKI
	word = (char *) u.cell(pTF).getWord();
	word[0]=ISOLatin1_ToUpper(word[0]);//probamos a poner la primera letra en mayúscula
	myref = mydic->search(word, &exp);
	//if(exp == NULL){//si no la encuentra, probamos a poner La Primera letra en mayúsculas
	if(exp == NULL){//si no la encuentra, probamos a poner La Primera letra en minuscula
		word[0]=ISOLatin1_ToLower(word[0]);
		//fprintf(stderr,"Word: %s\n", word);
		myref = mydic->search(word, &exp);
		if(exp == NULL){//si no la encuentra, probamos a poner TODAS las letras en mayúsculas
			ISOLatin1_StrUpper(word);
			myref = mydic->search(word, &exp);
			if(exp == NULL){//si no la encuentra, no probamos más combinaciones de mayúsculas, minúsculas
				//fprintf(stderr,"Warning: tf_mrk_ch2ph funtzioan. Ez da hitza hiztegian aurkitzen.");
				return pTF;
			}
		}
	}
	transkrip=strdup(exp);			//Hiztegian dagoen transkripzio fonetikoaren edukina edukiko du
	//fprintf(stderr,"word=%s\texp=%s\n", word, exp);
/*EVA 2015/07/07
Como las longitudes de las transcripciones en el diccionario compilado y de texto son diferentes porque en el compilado hay un caracter LF de más, las igualo aquí
*/
//fprintf(stderr,"i=%d \n",strlen(transkrip));
	if (transkrip[strlen(transkrip)-1]==10) transkrip[strlen(transkrip)-1]='\0';
	
	//Behar diren luzeeren kalkulua
	lengTFPKin=strlen(transkrip);		//Transkripzio fonetikoaren luzeera puntuekin.
	lengTF= (INT)ceil(float(lengTFPKin/2.0));	//Transkripzio fonetikoaren luzeera.
	lengWORD=strlen(word);	//Hitzaren luzeera.
	dif=lengWORD-lengTF;		//Luzeeren desberdintasuna.

/////////////////////////////
	//lengWORDPKin=lengWORD+numP;	//Hitzaren luzeera puntu seinuak edukiko balitu.
	numP=0;
	for(pTF2=u.charFirst(senp, URANGE_WORD); pTF2 != u.charLast(senp, URANGE_WORD); pTF2=u.charNext(pTF2))
		numP++;
	lengWORDPKin=lengWORD + numP;

	//fprintf(stderr,"lengWORDPKin=%d lengWORD=%d numP=%d transkrip=%s word=%s lengTFPKin=%d dif=%d\n", lengWORDPKin, lengWORD, numP, transkrip, word, lengTFPKin, dif);
	for (i=0;i<=lengTFPKin;i++)
	{

		//if (i<lengWORDPKin) //Hitzaren luzeera (puntuekin) ez bada gainditu, seinalatzailea hurrengo grafiara seinalatuko du.
		//INAKI
//		if (i<lengWORDPKin ) //Hitzaren luzeera (puntuekin) ez bada gainditu, seinalatzailea hurrengo grafiara seinalatuko du.
		if (i<lengWORDPKin+1 && transkrip[i] != '.' ) //Hitzaren luzeera (puntuekin) ez bada gainditu, seinalatzailea hurrengo grafiara seinalatuko du.
		{
			pTF2 = NEXT(pTF);
		}
		else if(transkrip[i] != '.')//Bestela gelaxka berria sortu beharko da.
		{
			//fprintf(stderr,"\tadd_new_cell PTF=%d\n", pTF);
			pTF=u.cellAddAfter(pTF);
			//u.cell(pTF).setChar('a');
		}
		//else
			//fprintf(stderr,"\tNADA\n");
		//fprintf(stderr,"i=%d lengwordpdkin=%d lengTFPKin=%d PTF=%d\n",i, lengWORDPKin, lengTFPKin,pTF);
		char c=CS_ytilde;
		//fprintf(stderr, "\tON transkrip[i]=%c\t%s\t%c\t%d\n", transkrip[i], transkrip, c, c == transkrip[i]);

		switch (transkrip[i])
		{

			case '.' :  break;
			case 'a' :
				if (i!=(lengTFPKin-1)) //Ez bada azkeneko grafia
				{
					if (transkrip[i+1]=='.')
					{
						SETPH(pTF, PHEU_a);   break;
					}
					else if(transkrip[i+1]=='~')
					{
						SETPH(pTF, PH_aa_); i++;  break; //a~
					}
				/*	else{
						SETPH(pTF, PHEU_a);
						fprintf(stderr,"Warning: Hitzegian idatzitako transkripzioa gaizki dago3 %s.\n \t  GOGORATU: FONEMAK PUNTU SEINUAZ DESBERDINDU.", transkrip);
						break;
					}*/
				}
				SETPH(pTF, PHEU_a);   break;
			case 'e' :
				if (i!=(lengTFPKin-1)) //Ez bada azkeneko grafia
				{
					if (transkrip[i+1]=='.')
					{
						SETPH(pTF, PHEU_e);   break;
					}
					else if(transkrip[i+1]=='~')
					{
						SETPH(pTF, PH_e_);  i++; break; //e~

					}
					//else{
						//fprintf(stderr,"Warning: Hitzegian idatzitako transkripzioa gaizki dagoee.\n \t  GOGORATU: FONEMAK PUNTU SEINUAZ DESBERDINDU.");
						//SETPH(pTF, PHEU_e);
					//}
					//break;
				}
				SETPH(pTF, PHEU_e);   break;
			case 'i' : SETPH(pTF, PHEU_i);  break;
			case 'o' :
				if (i!=(lengTFPKin-1)) //Ez bada azkeneko grafia
				{
					if (transkrip[i+1]=='.')
					{
						SETPH(pTF, PHEU_o);   break;
					}
					else if(transkrip[i+1]=='~')
					{
						SETPH(pTF, PH_o_);  i++; break; //o~
					}
					//else
						//fprintf(stderr,"Warning: Hitzegian idatzitako transkripzioa gaizki dagoOOO.\n \t  GOGORATU: FONEMAK PUNTU SEINUAZ DESBERDINDU.");
					//break;
				}
				SETPH(pTF, PHEU_o);   break;
			case 'u' : SETPH(pTF, PHEU_u);  break;

			case 'j':
				if (i!=(lengTFPKin-1))
				{
					if (transkrip[i+1]=='.')
					{
						SETPH(pTF, PHEU_iaprox); 	break;
					}
					if (transkrip[i+1]!='.')
					{
						if (transkrip[i+1]!='j')
						{
							//fprintf(stderr,"Warning: Hitzegian idatzitako transkripzioa gaizki dago1.\n \t  GOGORATU: FONEMAK PUNTU SEINUAZ DESBERDINDU.");
							SETPH(pTF, PHEU_iaprox); break;
						}
						else
						{
							i++;
						//	lengWORDPKin++; //inaki
							SETPH(pTF, PHEU_jj);  break;
						}
					}
				}
				else
				{
					SETPH(pTF, PHEU_iaprox); break;
				}

			case 'w': SETPH(pTF,PHEU_uaprox); break;


			case CS_atilde:
					//if(strlen(transkrip) > i+1 && transkrip[i+1]!='.')
						lengTFPKin=lengTFPKin-1;
					if (i!=(lengTFPKin-1)) //Ez bada azkeneko grafia
					{
						if (transkrip[i+1]=='.')
						{
							SETPH(pTF, PHEU_a); SETSTREUS(pTF); break;
						}
						else if(transkrip[i+1]=='~')
						{
							SETPH(pTF, PH_aa_); SETSTREUS(pTF); lengTFPKin=lengTFPKin-1; break; //a~
						}
						//else
							//fprintf(stderr,"Warning: Hitzegian idatzitako transkripzioa gaizki dago3.\n \t  GOGORATU: FONEMAK PUNTU SEINUAZ DESBERDINDU.");
						//break;
					}
					SETPH(pTF, PHEU_a); SETSTREUS(pTF); break;
			case CS_etilde:
			//	if(strlen(transkrip) > i+1 && transkrip[i+1]!='.')
					lengTFPKin=lengTFPKin-1;
				if (i!=(lengTFPKin-1)) //Ez bada azkeneko grafia
					{
						if (transkrip[i+1]=='.')
						{
							SETPH(pTF, PHEU_e); SETSTREUS(pTF); break;
						}
						else if(transkrip[i+1]=='~')
						{
							SETPH(pTF, PH_e_); SETSTREUS(pTF); lengTFPKin=lengTFPKin-1; break; //e~
						}
						//else
							//fprintf(stderr,"Warning: Hitzegian idatzitako transkripzioa gaizki dago3.\n \t  GOGORATU: FONEMAK PUNTU SEINUAZ DESBERDINDU.");
						//break;
					}
					SETPH(pTF, PHEU_e); SETSTREUS(pTF); break;
			case CS_itilde:
				SETPH(pTF, PHEU_i);
			//	if(strlen(transkrip) > i+1 && transkrip[i+1]!='.')
					lengTFPKin=lengTFPKin-1;
				SETSTREUS(pTF); break;
			case CS_otilde:
			//	if(strlen(transkrip) > i+1 && transkrip[i+1]!='.')
					lengTFPKin=lengTFPKin-1;
				if (i!=(lengTFPKin-1)) //Ez bada azkeneko grafia
					{
						if (transkrip[i+1]=='.')
						{
							SETPH(pTF, PHEU_o); SETSTREUS(pTF); break;
						}
						else if(transkrip[i+1]=='~')
						{
							SETPH(pTF, PH_o_); SETSTREUS(pTF); lengTFPKin=lengTFPKin-1; break; //o~
						}
						//else
							//fprintf(stderr,"Warning: Hitzegian idatzitako transkripzioa gaizki dago3.\n \t  GOGORATU: FONEMAK PUNTU SEINUAZ DESBERDINDU.");
						//break;
					}
					SETPH(pTF, PHEU_o); SETSTREUS(pTF); break;
			case CS_utilde:
				SETPH(pTF, PHEU_u);
				//if(strlen(transkrip) > i+1 && transkrip[i+1]!='.')
					lengTFPKin=lengTFPKin-1;
				SETSTREUS(pTF); break;
			case CS_uuml:
				SETPH(pTF, PHEU_u);
			//	if(strlen(transkrip) > i+1 && transkrip[i+1]!='.')
					lengTFPKin=lengTFPKin-1;
				break;

		//	case CS_ytilde: SETPH(pTF, PH_y); SETSTREUS(pTF); break;

			//case CS_Ytilde: SETPH(pTF, PH_2); SETSTREUS(pTF); break;

			case '\'':
				if (i!=(lengTFPKin-1)){
					if (transkrip[i+1]=='y'){
						SETPH(pTF, PH_y); SETSTREUS(pTF); i++; break;
					}
					else if (transkrip[i+1]=='Y'){
						SETPH(pTF, PH_2); SETSTREUS(pTF); i++; break;
					}

				}

			case 'b': SETPH(pTF, PHEU_b);  break;

			case 'B': SETPH(pTF, PHEU_baprox);  break;

			case 'c': SETPH(pTF, PHEU_tt); break;

			case 'd': SETPH(pTF, PHEU_d);  break;

			case 'D': SETPH(pTF, PHEU_daprox);  break;

			case 'f': SETPH(pTF, PHEU_f);  break;

			case 'g':
				if (i!=(lengTFPKin-1))
				{
					if (transkrip[i+1]!='.')
					{
						if (transkrip[i+1]!='j')
						{
							//fprintf(stderr,"Warning: Hitzegian idatzitako transkripzioa gaizki dago2.\n \t  GOGORATU: FONEMAK PUNTU SEINUAZ DESBERDINDU.");
							SETPH(pTF, PHEU_g); break;
						}
						else
						{
							i++;
						//	lengWORDPKin++; //inaki
							SETPH(pTF, PHEU_dj); break;
						}
					}
/*EVA 2015/07/07
Si llegaba aquí como no habia else con el correspondiente break se ponia la gaproximante del siguiente case en vez de la g normal
*/
					else
					{
						SETPH(pTF, PHEU_g); break;
					}
				}
				else
				{
					SETPH(pTF, PHEU_g); break;
				}

			case 'G': SETPH(pTF, PHEU_gaprox);  break;

			case 'k': SETPH(pTF, PHEU_k);  break;

			case 'l': SETPH(pTF, PHEU_l);	break;

			case 'L': SETPH(pTF, PHEU_ll);  break;

			case 'm': SETPH(pTF, PHEU_m); 	break;

			case 'n': SETPH(pTF, PHEU_n); break;

			case 'J':
				if (i!=(lengTFPKin-1)) //Ez bada azkeneko grafia
				{
					if (transkrip[i+1]=='.')
					{
						SETPH(pTF, PHEU_ntilde);   break;
					}
					else if(transkrip[i+1]=='\\')
					{
						SETPH(pTF, PH_Jb);  i++;  break; //J
					}
					//else
						//fprintf(stderr,"Warning: Hitzegian idatzitako transkripzioa gaizki dago3.\n \t  GOGORATU: FONEMAK PUNTU SEINUAZ DESBERDINDU.");
					//break;
				}
				SETPH(pTF,PHEU_ntilde); 	break;

			case 'p': SETPH(pTF, PHEU_p); break;

			case 'R': SETPH(pTF, PH_R); break; //Inaki: Iparralde

			case 'r':
				if (i!=(lengTFPKin-2)) //Ez bada azkeneko grafia
				{
					if (transkrip[i+1]=='.')
					{
						SETPH(pTF, PHEU_r); 	break;
					}
					else if (transkrip[i+1]!='.')
					{
						if (transkrip[i+1]!='r')
						{
							//fprintf(stderr,"Warning: Hitzegian idatzitako transkripzioa gaizki dago3.\n \t  GOGORATU: FONEMAK PUNTU SEINUAZ DESBERDINDU.");
							SETPH(pTF, PHEU_r); 	break;
						}
						else
						{
							i++;
						//	lengWORDPKin++; //inaki
							SETPH(pTF, PHEU_rr);  break;
						}
					}
				}
				else //Azkenekoa baldin bada
				{
					SETPH(pTF, PHEU_r);
					break;
				}

				case 's':
					if (i!=(lengTFPKin-1)) //Ez bada azkeneko grafia
					{
						if (transkrip[i+1]=='.')
						{
							SETPH(pTF, PHEU_s); break;
						}
						else if (transkrip[i+1]=='`')
						{
								i++;
								//fprintf(stderr,"Warning: Hitzegian idatzitako transkripzioa gaizki dago4.\n \t  GOGORATU: FONEMAK PUNTU SEINUAZ DESBERDINDU.");
								SETPH(pTF, PHEU_z); break;
							}
						else
							{
								//i++;
								//lengWORDPKin++; //inaki
								SETPH(pTF, PHEU_s); 	break;
							}
					}
					else //Azkeneko grafia bada
					{
						//fprintf(stderr,"azkeneako grafia\n");
						SETPH(pTF, PHEU_s); 	break;
					}

				case 'S': SETPH(pTF,PHEU_x); break;

				case 't':
					if (i!=(lengTFPKin-1)) //Ez bada azkeneko grafia
					{
						if (transkrip[i+1]=='.')  //"." bat baldin badu "t" grafia da.
						{
							SETPH(pTF,PHEU_t); break;
						}
						else if (transkrip[i+1]!='.')  //"." ez bada
						{
							if ((transkrip[i+1]!='s') && (transkrip[i+1]!='S'))//hurrengo ez bada s edo S gaizki dago
							{
								//fprintf(stderr,"Warning: Hitzegian idatzitako transkripzioa gaizki dago5.\n \t  GOGORATU: FONEMAK PUNTU SEINUAZ DESBERDINDU.");
								SETPH(pTF,PHEU_t); break;
							}

							else if (transkrip[i+1]=='S')  //S bada
							{
								//lengTFPKin=lengTFPKin-1;
								i++;
							//	lengWORDPKin++; //inaki
								SETPH(pTF,PHEU_tx); break;
							}

							else if (transkrip[i+1]=='s')  //s bada
							{
								i++;
								//lengWORDPKin++; //inaki
								if (i!=(lengTFPKin-1))
								{
									if (transkrip[i+1]=='.')
									{
										SETPH(pTF,PHEU_ts); break;
									}
									else if (transkrip[i+1]=='`')
									{
										i++;
										//lengTFPKin=lengTFPKin-1;
									//	lengWORDPKin++; //inaki
										SETPH(pTF,PHEU_tZ); break;
									}
									else
									{
										//fprintf(stderr,"Warning: Hitzegian idatzitako transkripzioa gaizki dago6.\n \t  GOGORATU: FONEMAK PUNTU SEINUAZ DESBERDINDU.");
										SETPH(pTF,PHEU_ts); break;
									}
								}
								else //"s" azken grafia baldin bada
								{
									SETPH(pTF,PHEU_ts); break;
								}
							}	//"s"-ren bukaera
						}//"tS", "ts", edo "ts´"-ren bukaerak
					}

					else //Azkeneko grafia baldin bada
					{
						SETPH(pTF,PHEU_t); break;
					}

			case 'T': SETPH(pTF, PHEU_T); break;

			case 'x': SETPH(pTF, PHEU_j);  break;

			case 'Z': SETPH(pTF, PH_Z);  break;

			case 'z': SETPH(pTF, PH_z);  break;

			case 'h': SETPH(pTF, PH_h);  break;

			case 'y': SETPH(pTF, PH_y);  break;

			case 'Y': SETPH(pTF, PH_2);  break;

			case 'v': SETPH(pTF, PH_v);  break;

		} // switch-en bukarea

		//fprintf(stderr,"ON2\n");
		//if (i<lengWORDPKin &&transkrip[i]!='.' && pTF2 != NULL) //INAKI
		if (i<lengWORDPKin+1 &&transkrip[i]!='.' && pTF2 != NULL) //INAKI
		{
			pTF=pTF2;
		}

	}//for-en bukaera

	/* Hitzaren luzeera transkripzioarena baino luzeago baldin bada, bueltatu behar den seinalatzailea
		hitzaren azkeneko grafiara seinalatu behar du. */
	if (dif>=0)
	{
		//pTF=u.charLast(senp,URANGE_WORD);
	}
	//pTF=u.phoneLast(senp, URANGE_WORD);
	delete mydic;//INAKI
	free(transkrip);//INAKI
	//u.foutput(stderr);
return pTF;

#undef SETPH
#undef SETSTREUS
#undef NEXT
}//main-en bukaera

#endif

