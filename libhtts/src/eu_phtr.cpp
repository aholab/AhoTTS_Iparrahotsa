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
(C) 1997 TSR/Aholab - ETSII/IT Bilbao (UPV/EHU)

Nombre fuente................ eu_phtr.cpp
Nombre paquete............... aHoTTS
Lenguaje fuente.............. C++
Estado....................... -
Dependencia Hard/OS.......... -
Codigo condicional........... -

Codificacion: ............... Borja Etxebarria
............................. Inigo Salbidea
..............................Ana Armenta
..............................Nora Barroso

Version  dd/mm/aa  Autor     Comentario
-------  --------  --------  ----------
2.0.9	 09/07/13  Inaki	 Incluir declinaciones en palabras con transcripción en diccionario (tf_mrk)
2.0.8	 05/05/13  Inaki     Cambios adicionales en la transcripcion para el dialecto de iparralde
2.0.7	 23/02/12  Agustin   Cambio en la transcripcion para el dialecto de iparralde
2.0.6	 13/12/11  Inaki	 Añadir la opcion phtkatamotz para que no pronuncie como rr las palabras que empiece con r
2.0.5	 14/02/11  Inaki	 Corregir palatalización 'l' en aditz trinkoak y aditzlagunak que no comiencen por "bail"
2.0.4	 11/01/10  Inaki	 Añadir transcripción para amaia
2.0.3    20/10/08  Inaki     Añadir soporte para transcripción en diccionario (Nora)
2.0.2    03/10/07  Inaki     phtsimple (no coarticula entre palabras, no comprobado..)PHEU_dj
			     PhTSpeaker (modifica comportamiento para locutor, Karolina)
2.0.1	 27/11/06  Eva       Arreglar los problemas que introdujo Nora en la 1.0.0
2.0.0		23/02/2005	Nora	Transkripzio fonetikoaren salbuespenak hiztegitik hartuta
1.0.0		01/01/05	Nora	   Arau berriak sartu
1.0.0    31/01/00  borja     codefreeze aHoTTS v1.0
0.2.2    30/12/99  borja     eliminar keyword "s t a t i c" redundante
0.2.1    04/xx/99  Ana       completar la adaptacion al euskera
0.2.0    04/05/99  Inigos    Funcion de excepciones
0.1.0    04/05/99  Inigos    Adaptacion al euskera
0.1.0    24/11/97  Borja     Codificacion inicial (castellano)

======================== Contenido ========================
<DOC>
Metodos de {{LangEU_PhTrans}} que efectuan la transcripcion fonetica
en si. Se analizan los caracteres de cada palabra y su contexto, y se
definen los fonemas que les corresponden.

"ch2ph" coge dos inicios de lista: fonemas {u} y caracteres {senp}.
Va asignando fonemas en funcion de los caracteres que le llegen
mediante un switch.
</DOC>
===========================================================
*/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/**********************************************************/


/**********************************************************/

#include <string.h>

#include "chset.h"
#include "eu_lingp.hpp"
#include "uti.h"

/**********************************************************/
/*convierte letras a fonemas para cada grupo de
palabras entre pausas*/
#ifdef USE_TOKENIZER

VOID LangEU_PhTrans::pausegr_ch2ph(UttPh & u, UttI senp)
{
//obtiene el caracter apuntado:
#define CH(p)  u.cell(p).getChar()

//escribe el fonema en el campo correspondiente del caracter apuntado por p:
#define SETPH(p,ph)  u.cell(p).setPhone(ph)

//acent£a el elemento apuntado por p:
#define SETSTREUS(p) u.cell(p).setStress(USTRESS_TEXT)

//adelanta el apuntador una posici¢n a nivel de letras:
#define NEXT(p)  u.charNext(p,URANGE_PAUSE)

//retrocede el apuntador una posici¢n a nivel de letras:
#define PREV(p)  u.charPrev(p,URANGE_PAUSE)

//adelanta el apuntador una posici¢n
#define DEL(p)  NEXT(p)
//escribe caracter
#define SETCHAR(p,ch) u.cell(p).setChar(ch)

	//int i;

	CHAR *ei = (char *)"ei";
	CHAR *aeo =(char *)"aeo";
	CHAR *aeou = (char *)"aeou";
	CHAR *aeiou = (char *)"aeiou";
	CHAR *nml = (char *)"nml";
	CHAR *nlsz = (char *)"nlsz";
	CHAR *nl = (char *)"nl";
	CHAR *mn = (char *)"mn";
	CHAR *sz = (char *)"sz";
	CHAR *sxz = (char *)"sxz";
//regla desconectada.	CHAR *ptkbdg = "ptkbdg";
	CHAR *tk =(char *)"tk";
	(void)mn;  // no se usa, asi quitamos el warning
	(void)nml;  // no se usa, asi quitamos el warning

	UttI p, p2, p3,p4,p5;
	INT ch, ch2, ch3,ch4,ch5;
	const CHAR * hitza;

	UttI wo;

	p = u.charFirst(senp, URANGE_PAUSE);
	while (p) {	//para todos las letras de un pausegr (grupo entre pausas)
		ch = CH(p);	// caracter actual
		p2 = NEXT(p);  //apuntador al caracter siguiente
		ch2 = (p2) ? CH(p2) : 0;	// caracter siguiente (0 si no hay siguiente)

 /***********Hitzaren transkripzio fonetikoa hiztegian agertzen bada**2005/03/16****************/
 		 wo=u.charFirst(p, URANGE_WORD);

 		 //fprintf(stderr,"c=%c\ttrans_fonet=%d\tTF_MRK_PROCESSED=%d\n", ch, trans_fonet_hitza(u,wo), p == wo );
 		  if (trans_fonet_hitza(u,wo) && p==wo && u.cell(p).getWord() != NULL)
		 {
			 const char *tmp;
			char decli[100];
			tmp = u.cell(p).getWord(); //word
			int len=  u.getHDicDB()->query(u.cell(p).getHDicRef(), HDIC_QUERY_MATCHLEN);
			//fprintf(stderr, "len_match=%d word=%s\n", len, tmp);
			BOOL isDec = FALSE;
			if(len > 0){
				strcpy(decli, tmp + len);
				//fprintf(stderr, "len_match=%d word=%s decli=%s\n", len, tmp, decli);
				HDicRef myhdic = u.getHDicDB()->search(decli);
				isDec = u.getHDicDB()->query(myhdic, HDIC_QUERY_EU_DEC);
			//	fprintf(stderr, "len_match=%d word=%s decli=%s isDec=%d\n", len, tmp, decli, isDec);
			}
			if(isDec)
				tf_mrk_ch2ph(u,wo); //idazteko funtzioa erabili
			else
				p=tf_mrk_ch2ph(u,wo); //idazteko funtzioa erabili
			//fprintf(stderr, "TRANSKRIBATZEN DENA:  %c\t\n",u.cell(p).getChar());
//fprintf(stderr,"isDec=%d\n", isDec);
			if (isDec){ //si es una declinación, ponemos como palabra marcada
				//Coincide en su totalidad?
			//	int len2 = u.getHDicDB()->query(myhdic, HDIC_QUERY_MATCHLEN);
				//if (len2){
				//movemos el puntero a la letra correspondiente
				int i=0;
				for(i=0; i<len; ++i)
					p=NEXT(p);
				int len_fon=1;
				UttI p_tmp;
				for(p_tmp=u.phoneFirst(p, URANGE_WORD); p_tmp != u.phoneLast(p, URANGE_WORD); p_tmp = u.phoneNext(p_tmp))
					len_fon++;
				//fprintf(stderr,"len=%d\tword_len=%d\tlen_fon=%d\n", len, strlen(tmp), len_fon);
				//mirar si el número de fonemas excede el número de carácteres, y si es así, replicar la declinación al final, añadiendo celdas nuevas
				if(len_fon > len || u.phoneLast(p, URANGE_WORD) == u.charLast(p,URANGE_WORD)){
					if(len_fon < strlen(tmp))
						len= len + strlen(tmp) - len_fon;
					for(i=len; i< strlen(tmp); i++){
						p_tmp=u.cellAddAfter(p_tmp);
						u.cell(p_tmp).setChar(u.cell(p).getChar());
						p=NEXT(p);
					}
					p=u.phoneLast(p, URANGE_WORD);
					if(u.charNext(p, URANGE_WORD) != NULL)
						p=u.charNext(p, URANGE_WORD);
				}

				//fprintf(stderr, "char1=%c\n", CH(p));

				//fprintf(stderr, "char2=%c\n", CH(p));
				//}
			}
			else{
				p=u.charLast(p, URANGE_WORD);
				//if(u.charNext(p, URANGE_WORD) != NULL)
					//	p=NULL;
			}
			ch = CH(p);	// caracter actual
			p2 = NEXT(p);  //apuntador al caracter siguiente
			ch2 = (p2) ? CH(p2) : 0;        // caracter siguiente (0 si no hay siguiente)
		//	fprintf(stderr,"ch=%c p2=%d ch2=%d isDec=%d\n", ch, p2, ch2, isDec);
			if (ch2==0 && !isDec)
			{
				break;
			}
			else
			{
				if(!isDec){
					p=p2;
					ch = CH(p);             // caracter actual
					p2 = NEXT(p);  //apuntador al caracter siguiente
					ch2 = (p2) ? CH(p2) : 0;        // caracter siguiente (0 si no hay siguiente)
				}
			}
			continue;
		}
 /********************************************************************************/



		switch (ch) {

		case 'a': SETPH(p, PHEU_a); break;

		case 'e': SETPH(p, PHEU_e); break;

		case 'i':
			 //en caso de formar parte de diptongo,seguida de n ¢ l,a su vez seguidas de
			 //vocal, la i se omite y n y l se palatalizan salvo excepciones.
			 //cuando se trata de bait+auxliar/sintetico contraido no se palataliza
			p3 = PREV(p);  ch3 = p3 ? CH(p3) : 0;//anterior a la i
			Phone ph3;
			if(p3) ph3=u.cell(p3).getPhone();
			else ph3=0;
			p4 = NEXT(p2);  ch4 = p4 ? CH(p4) : 0;//posterior a n ¢ l
			if (!u.charIsFirst(p,URANGE_WORD)&&!u.charIsLast(p, URANGE_WORD))
			{

/********************{g,k}+u+i+{n,l} Orduan i-> [j]*************************************************/
/*2005/01/31 - Nora*/
				if (!u.charIsFirst(p3,URANGE_WORD)&&(ch3=='u')&&strchr(nl, ch2))
				{
					p5 = PREV(p3);  ch5 = p5 ? CH(p5) : 0;
					if((ch5=='g')||(ch5=='k'))
					{
						SETPH(p,PHEU_iaprox);
						break;
					}
				}
/****************************************************************************************************/

				if(strchr(aeou, ph3)&&strchr(nl, ch2)&&!u.charIsLast(p2, URANGE_WORD)
				&&strchr(aeiou, ch4))
				{
					wo=u.wordThis(p, URANGE_PAUSE);
					if(trans_fonet_salb_i_0_j(u,wo)||es_verbo_trn(u,wo)||es_verbo_lgn(u,wo))
					{
						SETPH(p,PHEU_iaprox);
						break;
					}
					if(!phtiparralde)
						break;//No es iparralde nos la cargamos
					else{
						SETPH(p,PHEU_iaprox); //Sí es iparralde una i aproximante
						break;}


/*
					//excepciones a la palatalizaci¢n:
					if(es_excepcion(u,p,'i')||es_bai_aditz(u,p))
					{
						SETPH(p,PHEU_iaprox);
						break;
					}
					break;
*/

				}

			}

			//En iparralde no se palatiza, por lo tanto se lee siempre /i/ o /jj/
/********************{a,e,o,u}+i+{a,e,o,u} Orduan i-> [jj]*************************************************/
			if(!u.charIsFirst(p,URANGE_WORD)&&!u.charIsLast(p, URANGE_WORD)&&strchr(aeou,ph3)&&strchr(aeou, ch2))
			{
				if(phtiparralde)
					SETPH(p, PHEU_iaprox);
				else
					SETPH(p,PHEU_jj);
				break;
			}
/****************************************************************************************************/
			if(!u.charIsFirst(p,URANGE_WORD)&&strchr(aeou,ph3)){
				SETPH(p,PHEU_iaprox);
				break;
			}
			SETPH(p, PHEU_i); //i -> i
			break;

		case 'o': SETPH(p, PHEU_o); break;
		case 'u':
			//miro si es diptongo
			p3 = PREV(p);  ch3 = p3 ? CH(p3) : 0;
			if (strchr(aeo, ch3)&&!u.charIsLast(p3, URANGE_WORD)){
				SETPH(p,PHEU_uaprox);
				break;
			}
			if(phtiparralde && !u.charIsLast(p,URANGE_WORD) && ch2 == 'e'){ //u+e diptongo da
				SETPH(p,PHEU_uaprox);
				break;
			}
			//si no es diptongo, normal
			SETPH(p, PHEU_u); break;
		case CS_atilde: SETCHAR(p,'a');SETPH(p, PHEU_a); SETSTREUS(p); break;
		case CS_etilde: SETCHAR(p,'e');SETPH(p, PHEU_e); SETSTREUS(p); break;
		case CS_itilde: SETCHAR(p,'i');SETPH(p, PHEU_i); SETSTREUS(p); break;
		case CS_otilde: SETCHAR(p,'o');SETPH(p, PHEU_o); SETSTREUS(p); break;
		case CS_utilde: SETCHAR(p,'u');SETPH(p, PHEU_u); SETSTREUS(p); break;
		case CS_uuml:
			if(!phtiparralde){
			  SETCHAR(p,'u');
			  SETPH(p, PHEU_u);
			  break;
			  }else{
				  //SETCHAR(p,'u'); //Hay que cambiar la letra????
				 /*En iparralde es la "u" afrancesada sampa y*/
				  SETPH(p, PHEU_y);
				  break;
			  }

		case 'b':
			p3 = PREV(p);  ch3 = p3 ? CH(p3) : 0;
			if(!ch3){
				SETPH(p,PHEU_b);
				break;
			}
			//si es principio de palabra y va tras 'ez' la b se ensordece
			if (ch3&&u.charIsFirst(p,URANGE_WORD)&&(!phtsimple))
			{
				wo=u.wordPrev(p, URANGE_PAUSE); // palabra previa
				hitza = u.cell(wo).getWord();
				wo=u.wordThis(p,URANGE_PAUSE);
				if(!(strcmp(hitza,"ez")) && strcmp(pht_speaker,"Amaia")) // previa = ez
				{
					if(es_verbo_trn(u,wo)||es_verbo_lgn(u,wo))
					{
						SETPH(p,PHEU_p); // b -> p
						break;
					}
				}
			}
			if( ( (ch3=='l') && ( (ch2=='r') || (strchr(aeiou,ch2)) ) )
				|| (strchr(aeiou,ch3) && ( strchr(aeiou,ch2) || (ch2=='l') || (ch2=='r') ) ) )
			{
				SETPH(p, PHEU_baprox);
				break;
			}
			if(phtiparralde && (ch3=='r' && strchr(aeiou,ch2) )){
				SETPH(p, PHEU_baprox);
				break;
			}

			if(((ch3=='o')&&(ch2=='s'))
				||((ch3=='u')&&(ch2=='s')))
			{
				if(!phtiparralde)
					SETPH(p, PHEU_baprox);
				else
					SETPH(p, PHEU_p);
				break;
			}

			//resto de casos
			SETPH(p,PHEU_b);
			break; // b -> b;

		case 'c':
			if (!(u.charIsLast(p, URANGE_WORD)))
			{ //si no es £ltimo caracter de palabra
				//seguido de e ¢ i se pronuncia PHEU_T
				if (strchr(ei, ch2) || ch2 == CS_itilde || ch2 == CS_etilde) {
					if(!phtiparralde)
						SETPH(p, PHEU_T); // ce, ci; c -> T
					else
						SETPH(p, PHEU_z);// ce, ci; c -> s
					break;
				}
				//seguido de h se pronuncia PHEU_tx
				if (ch2 == 'h') {
					if(!phtiparralde)
						SETPH(p, PHEU_tx);
					else
						SETPH(p, PHEU_x); //c+h -> S
					break;
				}
			}
			//en el resto de los casos se pronuncia k
			SETPH(p, PHEU_k);
			break;

		case 'd':
			p3 = PREV(p);  ch3 = p3 ? CH(p3) : 0;
			//si es comienzo de palabra pero no tras pausa absoluta
			if(!(u.wordIsFirst(p, URANGE_PAUSE)) && u.charIsFirst(p, URANGE_WORD)&&(!phtsimple)&& strcmp(pht_speaker,"Karolina") && strcmp(pht_speaker,"Amaia"))
			{
				wo=u.wordPrev(p, URANGE_PAUSE);
				hitza = u.cell(wo).getWord();
				wo=u.wordThis(p,URANGE_PAUSE);
				//y si la palabra anterior es 'ez' ¢ 'bait'
				if(!(strcmp(hitza,"ez")) || !(strcmp(hitza,"bait")))
				{
					if(es_verbo_trn(u,p)||es_verbo_lgn(u,p))
					{
						SETPH(p,PHEU_t); // d -> t
						break;
					}
				}
			}

			if(!(u.charIsLast(p, URANGE_WORD))){
				if(ch2=='d')
				{
/********************hitz zehatz batetan dd -> [d]*************************************************/
				/*	if(es_excepcion(u,p,'d'))
					{
						SETPH(p,PHEU_d);
						p2=DEL(p2);
						break;
					}*/
/*********************************************************************************************/
					//si viene la graf¡a 'dd'
					if(u.charIsFirst(p, URANGE_PAUSE)||strchr(nlsz,ch3)||strchr(tk,ch3))
					{
						//y es comienzo absoluto o va precedida de n,l,s,z,t ¢ k
						if(phtiparralde)
							SETPH(p, PH_Jb); //dd -> "J\"
						else
							SETPH(p, PHEU_dj); // dd -> dj
					}
					else
					{
						//en cualquier otro caso se pronuncia PHEU_jj
						if(phtiparralde)
							SETPH(p, PH_Jb); //dd -> "J\"
						else
							SETPH(p, PHEU_jj); // dd -> jj
					}
					//nos saltamos la 2¦ d (porque su fonema ya est  procesado)
					p2=DEL(p2);
					break;
				}
			}
			//si no es ppio absoluto, y la anterior es vocal:
			if(!u.charIsFirst(p,URANGE_PAUSE)&&strchr(aeiou,ch3))
			{
				SETPH(p, PHEU_daprox);//d -> D
				break;
			}

			//en el resto de casos se pronuncia d oclusiva
			SETPH(p,PHEU_d); // d -> d
			break;

		case 'f': SETPH(p, PHEU_f); break;

		case 'g':
			//caracter anterior
			p3 = PREV(p);  ch3 = p3 ? CH(p3) : 0;
			//si no es comienzo absoluto y es comienzo de palabra cuando se trata
			//de verbo auxiliar ¢ sint‚tico precedido de ez o bait, se pronuncia k
			if(!(u.wordIsFirst(p, URANGE_PAUSE)) && u.charIsFirst(p, URANGE_WORD)&&(!phtsimple)&& strcmp(pht_speaker,"Amaia") )
			{
				//miro si la palabra anterior es 'ez' o 'bait'
				wo=u.wordPrev(p, URANGE_PAUSE);
				hitza = u.cell(wo).getWord();
				wo=u.wordThis(p,URANGE_PAUSE);
				if(!(strcmp(hitza,"ez")) || !(strcmp(hitza,"bait")))
				{
					if(es_verbo_trn(u,wo)||es_verbo_lgn(u,wo))
					{
						SETPH(p,PHEU_k); // g -> k
						break;
					}
				}
			}

			if(!u.charIsFirst(p,URANGE_PAUSE)&&(strchr(aeiou,ch3)||ch3=='l')){
				SETPH(p, PHEU_gaprox);
				break;
			}
			//en el resto de los casos se pronuncia oclusiva
			else SETPH(p, PHEU_g); // g -> G
			break;

		case 'h':
			 // saltamos la h si no es iparralde.
			 if (!phtiparralde)break;
			 else{
				 /**Transcripcion para dialecto iparralde**/
				 p3=PREV(p); ch3=p3?CH(p3):0;
				 //ch se deja como /tS/ por lo que la hache no se cambia
				 if (!(u.charIsFirst(p, URANGE_WORD)) && (ch3 == 'p' || ch3 == 'k' || ch3 == 'l' || ch3 == 'n' || ch3 == 'c' || ch3 == 't' || ch3 == 'r' ))  //desaparece la h (ekharri -> ekarri)
					break;
			    // hache de "hat" en ingles
			    SETPH(p, PHEU_h);
				break;
			}

		case 'j':
			//para ciertas excepciones se pronuncia como en castellano
			wo=u.wordThis(p, URANGE_PAUSE);
			if(!phtiparralde && trans_fonet_salb_j_0_x(u,wo)) //en Iparralde no hay excepciones con sonido de j en castellano
			{
				SETPH(p, PHEU_j); // j->x
				break;
			}
			p3 = PREV(p);  ch3 = p3 ? CH(p3) : 0;//caracter anterior

/********************{a,e,i,o,u}+j+{a,e,i,o,u} Orduan j-> [x]*************************************************/
/* Eva: 27/11/2006*/
/* Esta regla no es verdad. Muchas de las j entre vocales se pronuncian como jj: burujabe, gizajale... Solo hay que mirar
 * Lo que nos pasaron Amaia y Ziortza. No se de donde ha salido esta regla y creo que habría que desconectarla y añadir
 * en el diccionario todas las excepciones a la jj que hagan falta */

/*			if(!u.charIsFirst(p,URANGE_WORD)&&!u.charIsLast(p, URANGE_WORD)&&strchr(aeiou,ch3)&&strchr(aeiou, ch2))
			{
				SETPH(p,PHEU_j); // j->x
				break;
			}
*/
/****************************************************************************************************/

		 //si es comienzo absoluto o va precedido de n,l,s,z se pronuncia PHEU_dj
			if(u.charIsFirst(p, URANGE_PAUSE) || strchr(nlsz,ch3)|| strchr(tk,ch3))
			{
				if(phtiparralde)
					SETPH(p, PH_Jb); //j -> "J\"
				else
					SETPH(p, PHEU_dj); // j -> dj;
				break;
			}
			//en el resto de los casos
			if(phtiparralde)
				SETPH(p, PH_Jb); //j -> "J\"
			else
				SETPH(p, PHEU_jj); // j -> jj
			break;

		case 'k':
			//si es el £ltimo caracter de la palabra y la siguiente comienza por
			// p,t,k,b,d,g desaparece la k y {b,d,g}se pronuncian plosivas.
/* Ya no hacemos lo de quitar la k antes de otra oclusiva.


			if(u.charIsLast(p, URANGE_WORD)&&(!phtsimple))
			{
				if(!(u.wordIsLast(p, URANGE_PAUSE)))
				{
					if(strchr(ptkbdg,ch2))
					{
						// k -> [/]
						if(ch2=='b'){SETPH(p2,PHEU_b);p2=DEL(p2);}
						if(ch2=='d'){SETPH(p2,PHEU_d);p2=DEL(p2);}
						if(ch2=='g'){SETPH(p2,PHEU_g);p2=DEL(p2);}
						break;
					}
				}
			}
*/
			//en el resto de los casos se pronuncia k.


/********************k+k Orduan k-> [k]*************************************************/
			if(!u.charIsLast(p, URANGE_PAUSE)&&ch2=='k'&&(!phtsimple))
			{
				SETPH(p,PHEU_k);
				p2=DEL(p2);
				break;
			}
/***************************************************************************************/

			SETPH(p, PHEU_k); // k -> k
			break;

		case 'l':
			//si va en interior de palabra,precedida de 'i',y seguida de aeouPHEU_dj
			// se palataliza ,salvo si se trata de excepci¢n o
			//de expresi¢n (bait+auxiliar\sintatico) contraida
			p3 = PREV(p);  ch3 = p3 ? CH(p3) : 0;
			if (!u.charIsLast(p, URANGE_WORD) && !u.charIsFirst(p, URANGE_WORD)) //interior de palabra
			{
				if(ch3=='i' && !phtiparralde) //caracter anterior y NO es iparralde
				{
					//si no es bait+auxiliar/sintetico (caso contemplado en el case'i')
					//precedida de 'i' y seguida de vocal [aeou] se palataliza
					if (strchr(aeou, ch2))
					{
						wo=u.wordThis(p, URANGE_PAUSE);
						if(trans_fonet_salb_l_L_l(u,wo))
						{
							SETPH(p, PHEU_l); // l -> l ; no palatalizacion
							break;
						}
						///INAKI
						if (es_verbo_trn(u,wo)||es_verbo_lgn(u,wo)){
							//si la l se corresponde al siguiente inicio de palabra: "bail", no se palataliza
							const CHAR *hitza;
							hitza = u.cell(wo).getWord(); // palabra actual
							if( hitza[0] == 'b' && hitza[1] == 'a' && hitza[2] == 'i' && hitza[3] == 'l'){
								SETPH(p, PHEU_l); // l -> l ; no palatalizacion
								break;
							}
							else{
								SETPH(p,PHEU_ll);
								break;
							}
						}
						///////////////
/*
						if(es_excepcion(u,p,'l')||es_bai_aditz(u,p))
						{
							SETPH(p, PHEU_l); // l -> l ; no palatalizacion
							break;
						}
*/

/********************"filo" duten hitzetan l -> l egitea******************************************/

/*
						p4 = PREV(p3);  ch4 = p4 ? CH(p4) : 0;
						if(ch4=='f'&& ch2=='o')
						{
							SETPH(p, PHEU_l); // l -> l ; no palatalizacion
							break;
						}
*/
/*****************************************************************************PhTIparralde=************/
						SETPH(p,PHEU_ll);
						break; // siguiente vocal; l -> [L]
					}
				}
			}
			//dos 'l' seguidas dentro de la misma palabra
			if (!(u.charIsLast(p, URANGE_WORD)) && ch2 == 'l')
			{
				SETPH(p, PHEU_ll);
				p2 = DEL(p2);	// l -> ll
				break;
			}
			//en el resto de los casos
			SETPH(p, PHEU_l);  // l->l
			break;

		case 'm':
/********************m+m Orduan m-> [m]*************************************************/
			if(!u.charIsLast(p, URANGE_PAUSE)&&ch2=='m')
			{
				SETPH(p,PHEU_m);
				p2=DEL(p2);
				break;
			}
/**************************************************************************************/

			SETPH(p, PHEU_m);
			break;

		case 'n':
			//si va en interior de palabra,precedida de 'i',y seguida de vocal
			// se palataliza ,salvo si se trata de excepci¢n o
			//de expresi¢n (bait+auxiliar\sint‚tico) contraida
/*Eva 4/12/2006
 * Efectivamente la transcripción debería hacerse como indica el comentario anterior. Pero cuando Nora rehizo las reglas
 * de transcripcion eliminó la palatalizacion para todos los verbos, sean bainaiz o ginen. Como hay verbos que se
 * tienen que palatalizar, dejo la regla en que sólo se deja de palatalizar si es excepcion y he añadido en el diccionario
 * a todos los verbos bain* la etiqueta de excepcion a la palatalizacion de la n */
			p3 = PREV(p);  ch3 = p3 ? CH(p3) : 0;
			if (!(u.charIsFirst(p, URANGE_WORD)) && !(u.charIsLast(p, URANGE_WORD))) //interior de palabra
			{
				if(ch3=='i') //precedida de i
				{
					if (!(u.charIsLast(p, URANGE_WORD)) && strchr(aeiou, ch2)) // interior de palabra & sig vocal.
					{
						if (!phtiparralde){//No es iparralde
							wo=u.wordThis(p, URANGE_PAUSE);
							//Eva 4/12/2006
							//if(trans_fonet_salb_n_J_n(u,wo)||es_verbo_trn(u,wo)||es_verbo_lgn(u,wo))
							if(trans_fonet_salb_n_J_n(u,wo))
							{
								SETPH(p, PHEU_n); // n -> n ; no palatalizacion
								break;
							}


	/*
								if(es_excepcion(u,p,'n')||es_bai_aditz(u,p))
								{
									SETPH(p, PHEU_n); // n -> n ; no palatalizacion
									break;
								}
	*/
							//si no es bai+auxiliar/sintetico ni excepci¢n
							//precedida de 'i' y seguida de vocal se palataliza
							SETPH(p,PHEU_ntilde);
							break; // siguiente vocal; n -> [J]
						}else{//Si es iparralde, no se palatiza nunca
							SETPH(p,PHEU_n);
					}
				}
				//en los grupos nst y nzt de interior de palabra desaparece la n
				if(!(u.charIsLast(p, URANGE_WORD)) && strchr(sz,ch2)&&(!phtsimple) && !phtiparralde)
				// siguiente s o z
				{
					p3 = NEXT(p2); ch3 = p3 ? CH(p3) : 0;
					if(ch3=='t')//la siguiente a [sz] es 't'
						break; // [aeiou]n[sz]t -> [aeiou][sz]t
				}
			}
		}
			//INAKI: si 'n' es final de palabra, precedida de 'i' y la siguiente palabra empieza por vocal: n->J
			//Ej. orain arte
			else if(u.charIsLast(p, URANGE_WORD) && ch3=='i' && !u.charIsFirst(p3, URANGE_WORD) && !strcmp(pht_speaker,"Karolina") && !phtiparralde){
				p4 = PREV(p3);  ch4 = p4 ? CH(p4) : 0; //si la palabra acaba en "kin", no se palataliza
				if(ch4 != 'k'){
					p5 = NEXT(p2); ch5 = p5 ? CH(p5) : 0; //si la siguiente palabra empieza por 'h', miramos si la siguiente letra es vocal
					if((strchr(aeiou, ch2) && ch2!=0 )|| (ch2=='h' && strchr(aeiou, ch5) && ch5!=0)){
						SETPH(p,PHEU_ntilde);
						p5 = PREV(p4);  ch5 = p5 ? CH(p5) : 0;
						//eliminamos la i anterior si hay otra vocal antes (orain arte --> oraJ arte) (egin arte --> egiJ arte)
						if((strchr(aeiou, ch4) && ch4!=0) || (ch4 =='h' && strchr(aeiou,ch5) && ch5!=0) )
							SETPH(p3,' ');
						break; // siguiente vocal; n -> [J]
					}
				}
			}															/*********************************************************/

			//si la n precede a m,b,¢ p se pronuncia m
			p3 = NEXT(p); ch3 = p3 ? CH(p3) : 0;
			if((ch3=='b' || ch3=='p' || ch3=='m' )&&(!phtsimple))
			{
				SETPH(p, PHEU_m); // n [mbp] -> m
				break;
			}
			//en el resto de los casos se pronuncia n
			SETPH(p, PHEU_n); // n -> n
			break;

		case CS_ntilde: SETPH(p, PHEU_ntilde); break;

		case 'p':
			//al final de palabra, si la siguiente empieza con p,t,k,b,d,g,
			//y ambas palabras no est n separadas por pausa, desaparece la p.
			//en ese caso {b,d,g} plosivas
/*Ya no hacemos lo de quitar la p antes de oclusiva
			if(u.charIsLast(p, URANGE_WORD) && !(u.wordIsLast(p, URANGE_PAUSE))&& (!phtsimple))
			{
							if(strchr(ptkbdg,ch2)){
								if(ch2=='b'){SETPH(p2,PHEU_b);p2=DEL(p2);}
								if(ch2=='d'){SETPH(p2,PHEU_d);p2=DEL(p2);}
								if(ch2=='g'){SETPH(p2,PHEU_g);p2=DEL(p2);}
								break;
							}
				// p -> [/]
			}
*/
			// resto de casos se pronuncia p
			SETPH(p, PHEU_p);
			break;
		case 'q':
			//si va seguida de 'u'nos saltamos la 'u' y se pronuncia k
			//a no ser que sea 'qua' que no saltamos la u(la pronunciamos)
			if (ch2 == 'u') {
				p3 = NEXT(p2);
				ch3 = p3 ? CH(p3) : 0;	// caracter 3 (0 si no hay mas)
				if (!((ch3 == 'a')||(ch3=='o')||u.charIsLast(p2, URANGE_WORD)))
				p2 = DEL(p2);	// qu -> k excepto si qua o qu# (#=fin)
			}
			//siempre se pronuncia k
			SETPH(p, PHEU_k);
			break;	// q -> k */

		case 'r':
			//en el interior de palabra y entre vocales se pronuncia alveolar sonora
			p3 = PREV(p);  ch3 = p3 ? CH(p3) : 0;
			if (!(u.charIsFirst(p, URANGE_WORD)) && !(u.charIsLast(p, URANGE_WORD))
			 && strchr(aeiou,ch3) && strchr(aeiou, ch2)){
					SETPH(p, PHEU_r); // V+r+V -> r
					break;
			}
			if(phtkatamotz && u.charIsFirst(p, URANGE_WORD)){	//si esta activada esta opción y es inicio de palabra, r suave
				SETPH(p, PHEU_r);
				break;
			}
			//resto de casos alveolar vibrante
			if(!phtiparralde)
				SETPH(p, PHEU_rr);  // r -> rr
			else{
				//si la palabra es ur o zur y después hay pausa o la siguiente es consonante --> r -> r
				const CHAR *hitza;
				hitza = u.cell(wo).getWord(); // palabra actual
				if((!strcmp(hitza, "ur") || !strcmp(hitza, "zur")) && (u.wordIsLast(p, URANGE_PAUSE) || !(strchr(aeiou,ch2))))
					SETPH(p, PH_r);  // r -> R //Iparralde
				else
					SETPH(p, PH_R);  // r -> R //Iparralde
			}
			//si viene una segunda r no hay que procesarla
			if (ch2=='r') p2=DEL(p2); // rr -> saltamos una r
			break;

		case 's':
			/*******caso ts*******/
			//si el caracter anterior es 't', se pronuncia ts excepto al final de
			//palabra si la siguiente comienza por consonante que se pierde la t.
			//ej: akats gehiegi--->akasgeieGi
			p3 = PREV(p);  ch3 = p3 ? CH(p3) : 0;
			//si delante de la s hay una 't' y est  en la misma palabra que la 's'
			if(ch3=='t' && !(u.charIsFirst(p, URANGE_WORD)))
			{ //si la s es £ltima de palabra pero no es final de frase
				if(u.charIsLast(p, URANGE_WORD) && !u.wordIsLast(p, URANGE_PAUSE)&& (!phtsimple) && strcmp(pht_speaker,"Amaia") )
				{
					//miro si la siguiente palabra empieza por consonante
					wo=u.wordNext(p, URANGE_PAUSE);
					hitza = u.cell(wo).getWord();
					ch3=hitza[0];

					if(ch3!='h' && !(strchr(aeiou,ch3)))
					{
						//en caso afirmativo pronuncio s.
						if(phtiparralde)
							SETPH(p,PHEU_z);
						else
							SETPH(p,PHEU_s);
						break;
					}
				}
				//resto de casos pronuncio ts.
				//asigno el fonema al primer caracter de la digraf¡a(la t)
				if(phtiparralde)
					SETPH(p3, PHEU_tZ);
				else
					SETPH(p3, PHEU_ts);
				break;
			}

/********************s+s Orduan s-> [s]*************************************************/
/*2005/01/31 - Nora*/
			if(!u.charIsLast(p, URANGE_PAUSE)&&ch2=='s'&&(!phtsimple))
			{
				if(phtiparralde)
					SETPH(p,PHEU_z);
				else
					SETPH(p,PHEU_s);
				p2=DEL(p2);
				break;
			}
/**************************************************************************************/

			/*************caso s******************/
		 //si no hay t delante dentro de la misma palabra
			if(phtiparralde)
				SETPH(p, PHEU_z);
			else
				SETPH(p, PHEU_s);
			break;

		case 't':
		/**************** caso tt **********************/
			//si van dos 't' seguidas en la misma palabra se pronuncia PHEU_Q
			if(!(u.charIsLast(p, URANGE_WORD)) && ch2=='t')
			{
				SETPH(p, PHEU_tt); // tt -> Q
				p2 = DEL(p2);
				break;
			}
		/*************** t al final de palabra **************/
			//si la t va al final de palabra (no al final de frase) hay que mirar
			//si la siguiente palabra comienza por b,d,g,p,t,k --> la t desaparece
			//y b,d,g oclusivas
			if(u.charIsLast(p, URANGE_WORD) && !u.wordIsLast(p, URANGE_PAUSE)&& (!phtsimple))
			{
/*Ya no hacemos lo de quitar la t antes de oclusiva

					if(strchr(ptkbdg,ch2)) // siguiente bodega-petaka
					{
						// t -> [/]
						if(ch2=='b'){SETPH(p2,PHEU_b);p2=DEL(p2);}
						if(ch2=='d'){SETPH(p2,PHEU_d);p2=DEL(p2);}
						if(ch2=='g'){SETPH(p2,PHEU_g);p2=DEL(p2);}
						break;
					}
*/
					/********* caso lehen bait lehen ***********/
					wo=u.wordThis(p, URANGE_PAUSE);
					hitza = u.cell(wo).getWord();
					if(!strcmp(hitza,"bait")) // actual = bait
					{
						//el caso "lehen bait lehen" es una excepci¢n
						//se pronuncia lembailen
						if(!(u.wordIsFirst(p, URANGE_PAUSE)))
						{ //si al bait le sigue lehen
							wo=u.wordNext(p, URANGE_PAUSE);
							hitza = u.cell(wo).getWord(); // palabra siguiente
							if(!strcmp(hitza,"lehen"))
							{ //y si va precedido de lehen
								wo=u.wordPrev(p, URANGE_PAUSE);
								hitza = u.cell(wo).getWord(); // palabra anterior
								if(!strcmp(hitza,"lehen"))
									// lehen bait lehen  t->[/]
								break;
							}
						}
					/************ caso bait + aux/sint ************/

					//si la t corresponde a bait seguido de auxiliar o sintetico
					//que comience por n,l,z desaparece la t en los dos primeros casos
					//y se pronuncia tz en el caso de la z.

/********************bait + lgn/trn izanda *******************************************************/
/* Bai(t)naiz, bai(t)haiz, bai(t)kara, baitzara********************************************************/
/*************Aldaketak sartu ditut************************************************************/
						wo=u.wordNext(p, URANGE_PAUSE);
						hitza = u.cell(wo).getWord();
						if((hitza[0]!='z')&&(es_verbo_trn(u,wo)||es_verbo_lgn(u,wo))) break;

/**************LEHEN EGITEN ZENA***********************************************************/
/*
						//bait seguido de auxiliar o sint‚tico que comience por n
						//nos saltamos la t
						// bait + [n]adz -> bai n
						if((hitza[0]=='n')&&(es_verbo_trn(u,wo)||es_verbo_lgn(u,wo))) break;
						//bait seguido de auxiliar o sint‚tico que comience por l
						//nos saltamos la t
						// bait + [l]adz -> bai l
						if((hitza[0]=='l')&&(es_verbo_trn(u,wo)||es_verbo_lgn(u,wo))) break;
						//bait seguido de auxiliar o sint‚tico que comience por z
						//pronunciamos tz y nos saltamos la z
*/
/******************************************************************************************/


						if((hitza[0]=='z')&&(es_verbo_trn(u,wo)||es_verbo_lgn(u,wo)))
						{
							if(phtiparralde)
								SETPH(p2, PHEU_ts); // t -> tz // bait + [z]adz -> bai+[tZ]adz
							else
								SETPH(p2, PHEU_tZ); // t -> tz // bait + [z]adz -> bai+[tZ]adz
							p2=DEL(p2);//nos saltamos la z para no procesarla
							break;
						}
					}
				/*********** st + consonante *****************/
				//si la t va al final de palabra precedida de s ,y si la siguiente
				//palabra comienza por consonante, omitimos la t.
				//ejemplo:bost gizon-->bosgizon
				p3 = PREV(p);  ch3 = p3 ? CH(p3) : 0;
				if(ch3=='s' && !phtiparralde) // anterior s
				{
						wo=u.wordNext(p, URANGE_PAUSE);
						hitza = u.cell(wo).getWord(); // siguiente palabra
						ch3=hitza[0]; // comienzo siguiente palabra
						if(!strchr(aeiou,ch3)) // siguiente consonante
						 // t -> [/]
							break;
				}
			}

			//si la t no est  al final de palabra miro si va seguida de s,x,z
			//en caso afirmativo me salto la t, no la proceso porque se procesan
			//las digraf¡as ts, tx y tz en la s,x y z respectivamente
			p3 = NEXT(p);  ch3 = p3 ? CH(p3) : 0;
			if(!(u.charIsLast(p,URANGE_WORD)) && strchr(sxz,ch3)) break;// st -> s

			SETPH(p, PHEU_t); // t -> t
			break;
		case 'v':
			p3 = PREV(p);  ch3 = p3 ? CH(p3) : 0;
			if(u.charIsFirst(p,URANGE_PAUSE)||(ch3=='n'||ch3=='m'||ch3=='¤')){
				SETPH(p,PHEU_b); // v -> b
				break;
			}
			//resto de casos
			SETPH(p,PHEU_baprox);
			break; // v -> B;

		case 'w':
/********************"w", "u" bezela tratatu************************************************************/
			p3 = PREV(p);  ch3 = p3 ? CH(p3) : 0;
			if (strchr(aeo, ch3)&&!u.charIsLast(p3, URANGE_WORD)){
				SETPH(p,PHEU_uaprox); // w -> w
				break;
			}
/*************************************************************************************************/
SETPH(p, PHEU_u); break;  // w -> u


		case 'x':
		/****************** caso tx ************************/
			//si el caracter anterior es 't', se pronuncia tS excepto al final de
			//palabra si la siguiente comienza por consonante que se pierde la t.
			//ej: antx pixka--->anxpixka
			p3 = PREV(p);  ch3 = p3 ? CH(p3) : 0;

			if(ch3=='t' && !(u.charIsFirst(p, URANGE_WORD)))
			{ //si el anterior es t y est  dentro de la misma palabra
				//y si no es la £ltima palabra de la frase
				if(u.charIsLast(p, URANGE_WORD) && !(u.wordIsLast(p, URANGE_PAUSE))&& (!phtsimple) && !phtiparralde)
				{
				 //miro la siguiente palabra
					wo=u.wordNext(p, URANGE_PAUSE);
					hitza = u.cell(wo).getWord();
					ch3=hitza[0];
					//si comienza por consonante
					if( ch3!='h' && !(strchr(aeiou,ch3)))
					{
						SETPH(p,PHEU_x);
						break;
					}
				}
				SETPH(p3, PHEU_tx); // tx -> tS
				break;
			}
			/**************** caso x ********************/
			//si la x no va precedida de t se pronuncia x
			SETPH(p, PHEU_x); // x -> S
			break;

		case 'y': // como la j
			p3 = PREV(p);  ch3 = p3 ? CH(p3) : 0;

/********************"y" azkeneko garfia bada y=>[i]*************************/
			if(!u.charIsFirst(p, URANGE_PAUSE)&&!u.charIsFirst(p3, URANGE_WORD)&&!(strchr(aeiou,ch3)||ch3=='h'))
			{
				p5 = PREV(p3);  ch5 = p5 ? CH(p5) : 0;
				if(!(strchr(aeiou,ch5)||ch5=='h'))
				{
					SETPH(p, PHEU_i);
					break;
				}
			}
			if(u.charIsLast(p, URANGE_PAUSE)&&!u.charIsFirst(p, URANGE_WORD))
			{
				SETPH(p, PHEU_i);
				break;
			}

/**********************************************************************/

			//en comienzo absoluto ¢ seguida de n,l,s,z se pronuncia dj
			if(u.charIsFirst(p, URANGE_PAUSE) || strchr(nlsz,ch3)|| strchr(tk,ch3))
			{
				//fprintf(stderr, "zein daaa nlsztk eta bakarra\n");
				if(phtiparralde)
					SETPH(p, PH_Jb); //j -> "J\"
				else
					SETPH(p, PHEU_dj); // j -> dj;
				break;
			}
			//en el resto de los casos se pronuncia jj.


			else
			{
				if(phtiparralde)
					SETPH(p, PH_Jb); //j -> "J\"
				else
					SETPH(p, PHEU_jj); // y -> jj
				break;
			}
		case 'z':
			if(trans_fonet_salb_z_0_t(u,u.wordThis(p, URANGE_PAUSE))){//INAKI salbuespena z->T (ad. Zaragoza)
				SETPH(p, PHEU_T); // z -> T
				break;
			}
			/************ caso tz **************/
			p3 = PREV(p);  ch3 = p3 ? CH(p3) : 0;
			//si el caracter anterior es 't', se pronuncia tZ excepto al final de
			//palabra si la siguiente comienza por consonante que se pierde la t.
			//ej: bihotz taupadak---->bioztaupaDak
			if(ch3=='t' && !(u.charIsFirst(p, URANGE_WORD))) // anterior t
			{
				if(u.charIsLast(p, URANGE_WORD)&&!(u.wordIsLast(p, URANGE_PAUSE))&& (!phtsimple)&&strcmp(pht_speaker,"Karolina")&& strcmp(pht_speaker,"Amaia") && !phtiparralde) // no es la ultima palabra
				{
					wo=u.wordNext(p, URANGE_PAUSE);
					hitza = u.cell(wo).getWord();
					ch3=hitza[0];
					if(ch3!='h' && !strchr(aeiou,ch3))
					{
						 SETPH(p, PHEU_z); // tz + C -> z + C
						 break;
					}
				}
				//asignamos el fonema al primer caracter de la digraf¡a(la t)
				if(phtiparralde)
					SETPH(p3, PHEU_ts); // tz -> tZ
				else
					SETPH(p3, PHEU_tZ); // tz -> tZ
				break;
			}
			/*************** caso z ********************/
			//si la z no va tras t,y es la £ltima de palabra en interior de frase
			//comprobamos si se trata de 'ez'

/********************z+z Salbuespen bat baldin bada, orduan z-> [z]**********************************/
/*
			if(es_excepcion(u,p,'z'))
			{
				SETPH(p, PHEU_z); // zz->z
				p2=DEL(p2);
				break;
			}
*/
/*********************************************************************************************/

			if(!(u.wordIsLast(p, URANGE_PAUSE)) && u.charIsLast(p,URANGE_WORD)&&(!phtsimple))
			{
				wo=u.wordThis(p, URANGE_PAUSE);
				hitza = u.cell(wo).getWord(); // palabra actual
				if(!strcmp(hitza,"ez"))
				{
					wo=u.wordNext(p, URANGE_PAUSE);
					hitza = u.cell(wo).getWord();
					//si "ez"va seguido de palabra que empieza por 'n'
					if(hitza[0]=='n' && strcmp(pht_speaker,"Amaia"))
						//miro si se trata de verbo auxiliar o sintetico
						if(es_verbo_trn(u,wo)||es_verbo_lgn(u,wo)) break;
						 //en caso afirmativo se omite la z:
						 // 'ez' + [n]adz lagn    z -> [/]

					//si "ez" va seguido de palabra que empieza por 'l'
					if(hitza[0]=='l' && strcmp(pht_speaker,"Amaia"))
						//miro si se trata de verbo auxiliar o sintetico
						if(es_verbo_trn(u,wo)||es_verbo_lgn(u,wo)) break;
						//en caso afirmativo se omite la z:
						 // 'ez' + [l]adz lagn    z -> [/]

					//si "ez"va seguido de palabra que empieza por 'z'
					if(hitza[0]=='z' && strcmp(pht_speaker,"Amaia"))
					//miro si se trata de verbo auxiliar o sintetico
						if(es_verbo_trn(u,wo)||es_verbo_lgn(u,wo))
						{//en caso afirmativo la z se convierte en tz
							//y nos saltamos la siguiente z
							if(phtiparralde)
								SETPH(p2, PHEU_ts); // z -> z
							else
								SETPH(p2, PHEU_tZ); // z -> z
							p2 = DEL(p2); // 'ez' + [z]adz lagn    z + z ->[/]+[tz]
							break;
						}
				}
			}
			//en el resto de los casos pronunciamos z
			if(phtiparralde)
				SETPH(p, PHEU_s); // z -> z
			else
				SETPH(p, PHEU_z); // z -> z
			break;

		// caracteres no contemplados, los saltamos directamente
		default: p2 = DEL(p); break;
		}
		p = p2;		// siguiente caracter
	}

#undef DEL
#undef SETPH
#undef NEXT
#undef PREV
}
#else
VOID LangEU_PhTrans::pausegr_ch2ph(UttPh & u, UttI senp)
{
//obtiene el caracter apuntado:
#define CH(p)  u.cell(p).getChar()

//escribe el fonema en el campo correspondiente del caracter apuntado por p:
#define SETPH(p,ph)  u.cell(p).setPhone(ph)

//acent£a el elemento apuntado por p:
#define SETSTREUS(p) u.cell(p).setStress(USTRESS_TEXT)

//adelanta el apuntador una posici¢n a nivel de letras:
#define NEXT(p)  u.charNext(p,URANGE_PAUSE)

//retrocede el apuntador una posici¢n a nivel de letras:
#define PREV(p)  u.charPrev(p,URANGE_PAUSE)

//adelanta el apuntador una posici¢n
#define DEL(p)  NEXT(p)

	//int i;

	CHAR *ei = "ei";
	CHAR *aeo ="aeo";
	CHAR *aeou = "aeou";
	CHAR *aeiou = "aeiou";
	CHAR *nml = "nml";
	CHAR *nlsz = "nlsz";
	CHAR *nl = "nl";
	CHAR *mn = "mn";
	CHAR *sz = "sz";
	CHAR *sxz = "sxz";
	CHAR *ptkbdg = "ptkbdg";
	(void)mn;  // no se usa, asi quitamos el warning
	(void)nml;  // no se usa, asi quitamos el warning

	UttI p, p2, p3,p4;
	INT ch, ch2, ch3,ch4;
	const CHAR * hitza;

	UttI wo;

	p = u.charFirst(senp, URANGE_PAUSE);

	while (p) {	//para todos las letras de un pausegr (grupo entre pausas)
		ch = CH(p);	// caracter actual
		p2 = NEXT(p);  //apuntador al caracter siguiente
		ch2 = (p2) ? CH(p2) : 0;	// caracter siguiente (0 si no hay siguiente)

		switch (ch) {

		case 'a': SETPH(p, PHEU_a); break;

		case 'e': SETPH(p, PHEU_e); break;

		case 'i':
			 //en caso de formar parte de diptongo,seguida de n ¢ l,a su vez seguidas de
			 //vocal, la i se omite y n y l se palatalizan salvo excepciones.
			 //cuando se trata de bait+auxliar/sintetico contraido no se palataliza
			p3 = PREV(p);  ch3 = p3 ? CH(p3) : 0;//anterior a la i
			p4 = NEXT(p2);  ch4 = p4 ? CH(p4) : 0;//posterior a n ¢ l
			if (!u.charIsFirst(p,URANGE_WORD)&&!u.charIsLast(p, URANGE_WORD)){
				if(strchr(aeou, ch3)&&strchr(nl, ch2)&&!u.charIsLast(p2, URANGE_WORD)
				&&strchr(aeiou, ch4)){
					//excepciones a la palatalizaci¢n:
					if(es_excepcion(u,p,'i')||es_bai_aditz(u,p)){
						SETPH(p,PHEU_iaprox);
						break;
					}
					break;
				}
			}
			if(!u.charIsFirst(p,URANGE_WORD)&&strchr(aeou,ch3)){
				SETPH(p,PHEU_iaprox);
				break;
			}
			SETPH(p, PHEU_i); //i -> i
			break;

		case 'o': SETPH(p, PHEU_o); break;
		case 'u':
			//miro si es diptongo
			p3 = PREV(p);  ch3 = p3 ? CH(p3) : 0;
			if (strchr(aeo, ch3)&&!u.charIsLast(p3, URANGE_WORD)){
				SETPH(p,PHEU_uaprox);
				break;
			}
			//si no es diptongo, normal
			SETPH(p, PHEU_u); break;

		case CS_atilde: SETPH(p, PHEU_a); SETSTREUS(p); break;
		case CS_etilde: SETPH(p, PHEU_e); SETSTREUS(p); break;
		case CS_itilde: SETPH(p, PHEU_i); SETSTREUS(p); break;
		case CS_otilde: SETPH(p, PHEU_o); SETSTREUS(p); break;
		case CS_utilde: SETPH(p, PHEU_u); SETSTREUS(p); break;
		case CS_uuml:	SETPH(p, PHEU_u); break;

		case 'b':
			if (u.charIsFirst(p, URANGE_PHRASE)){
				SETPH(p,PHEU_b); // b -> b
				break;
			}
			//si es principio de palabra y va tras 'ez' la b se ensordece
			if (!(u.wordIsFirst(p, URANGE_PHRASE)) && u.charIsFirst(p,URANGE_WORD)/*&&(!phtsimple)*/)
			{
				wo=u.wordPrev(p, URANGE_PHRASE); // palabra previa
				hitza = u.cell(wo).getWord();
				if(!(strcmp(hitza,"ez"))) // previa = ez
				{
					if(es_aux_o_sint(u,p,'b'))
					{
						SETPH(p,PHEU_p); // b -> p
						break;
					}
				}
			}
			p3 = PREV(p);  ch3 = p3 ? CH(p3) : 0;
			if(ch3=='l'||strchr(aeiou,ch3))
			{
				SETPH(p, PHEU_baprox);
				break;
			}
			//resto de casos
			SETPH(p,PHEU_b);
			break; // b -> b;

		case 'c':
			if (!(u.charIsLast(p, URANGE_WORD)))
			{ //si no es £ltimo caracter de palabra
				//seguido de e ¢ i se pronuncia PHEU_T
				if (strchr(ei, ch2)) { SETPH(p, PHEU_T); break; } // ce, ci; c -> T
				//seguido de h se pronuncia PHEU_tx
				if (ch2 == 'h') { SETPH(p, PHEU_tx); break; }
			}
			//en el resto de los casos se pronuncia k
			SETPH(p, PHEU_k);
			break;

		case 'd':
			p3 = PREV(p);  ch3 = p3 ? CH(p3) : 0;
			//si es comienzo de palabra pero no tras pausa absoluta
			if(!(u.wordIsFirst(p, URANGE_PHRASE)) && u.charIsFirst(p, URANGE_WORD)/*&&(!phtsimple)*/)
			{
				wo=u.wordPrev(p, URANGE_PHRASE);
				hitza = u.cell(wo).getWord();
				//y si la palabra anterior es 'ez' ¢ 'bait'
				if(!(strcmp(hitza,"ez")) || !(strcmp(hitza,"bait")))
				{
					if(es_aux_o_sint(u,p,'d'))
					{
						SETPH(p,PHEU_t); // d -> t
						break;
					}
				}
			}

			if(!(u.charIsLast(p, URANGE_WORD))){
				if(ch2=='d'){
					//si viene la graf¡a 'dd'
					if(u.charIsFirst(p, URANGE_PHRASE) || strchr(nlsz,ch3)){
						//y es comienzo absoluto o va precedida de n,l,s ¢ z
						SETPH(p, PHEU_dj); // dd -> dj
					}
					else{
						//en cualquier otro caso se pronuncia PHEU_jj
						SETPH(p, PHEU_jj); // dd -> jj
					}
					//nos saltamos la 2¦ d (porque su fonema ya est  procesado)
					p2=DEL(p2);
					break;
				}
			}
			//si no es ppio absoluto, y la anterior es vocal:
			if(!u.charIsFirst(p,URANGE_PHRASE)&&strchr(aeiou,ch3))
			{
				SETPH(p, PHEU_daprox);//d -> D
				break;
			}

			//en el resto de casos se pronuncia d oclusiva
			SETPH(p,PHEU_d); // d -> d
			break;

		case 'f': SETPH(p, PHEU_f); break;

		case 'g':
			//caracter anterior
			p3 = PREV(p);  ch3 = p3 ? CH(p3) : 0;
			//si no es comienzo absoluto y es comienzo de palabra cuando se trata
			//de verbo auxiliar ¢ sint‚tico precedido de ez o bait, se pronuncia k
			if(!(u.wordIsFirst(p, URANGE_PHRASE)) && u.charIsFirst(p, URANGE_WORD)/*&&(!phtsimple)*/)
			{
				//miro si la palabra anterior es 'ez' o 'bait'
				wo=u.wordPrev(p, URANGE_PHRASE);
				hitza = u.cell(wo).getWord();
				if(!(strcmp(hitza,"ez")) || !(strcmp(hitza,"bait")))
				{
					if(es_aux_o_sint(u,p,'g'))
					{
						SETPH(p,PHEU_k); // g -> k
						break;
					}
				}
			}

			if(!u.charIsFirst(p,URANGE_PHRASE)&&(strchr(aeiou,ch3)||ch3=='l')){
				SETPH(p, PHEU_gaprox);
				break;
			}
			//en el resto de los casos se pronuncia oclusiva
			else SETPH(p, PHEU_g); // g -> G
			break;

		case 'h':
			 // saltamos la h.
			 break;

		case 'j':
			//para ciertas excepciones se pronuncia como en castellano
			if(es_excepcion(u,p,'j'))
			{
				SETPH(p, PHEU_j); // j->j
				break;
			}

			p3 = PREV(p);  ch3 = p3 ? CH(p3) : 0;//caracter anterior
		 //si es comienzo absoluto o va precedido de n,l,s,z se pronuncia PHEU_dj
			if(u.charIsFirst(p, URANGE_PHRASE) || strchr(nlsz,ch3))
			{
				SETPH(p, PHEU_dj); // j -> dj;
				break;
			}
			//en el resto de los casos
			SETPH(p, PHEU_jj); // j -> jj
			break;

		case 'k':
			//si es el £ltimo caracter de la palabra y la siguiente comienza por
			// p,t,k,b,d,g desaparece la k y {b,d,g}se pronuncian plosivas.
			if(u.charIsLast(p, URANGE_WORD)&&(!phtsimple))
			{
				if(!(u.wordIsLast(p, URANGE_PHRASE)))
				{
					if(strchr(ptkbdg,ch2))
					{
						// k -> [/]
						if(ch2=='b'){SETPH(p2,PHEU_b);p2=DEL(p2);}
						if(ch2=='d'){SETPH(p2,PHEU_d);p2=DEL(p2);}
						if(ch2=='g'){SETPH(p2,PHEU_g);p2=DEL(p2);}
						break;
					}
				}
			}
			//en el resto de los casos se pronuncia k.
			SETPH(p, PHEU_k); // k -> k
			break;

		case 'l':
			//si va en interior de palabra,precedida de 'i',y seguida de aeou
			// se palataliza ,salvo si se trata de excepci¢n o
			//de expresi¢n (bait+auxiliar\sint‚tico) contraida
			p3 = PREV(p);  ch3 = p3 ? CH(p3) : 0;
			if (!u.charIsLast(p, URANGE_WORD) && !u.charIsFirst(p, URANGE_WORD)) //interior de palabra
			{
				if(ch3=='i') //caracter anterior
				{
					//si no es bait+auxiliar/sintetico (caso contemplado en el case'i')
					//precedida de 'i' y seguida de vocal [aeou] se palataliza
					if (strchr(aeou, ch2))
					{
						if(es_excepcion(u,p,'l')||es_bai_aditz(u,p))
						{
							SETPH(p, PHEU_l); // l -> l ; no palatalizacion
							break;
						}
						SETPH(p,PHEU_ll);
						break; // siguiente vocal; l -> [L]
					}
				}
			}
			//dos 'l' seguidas dentro de la misma palabra
			if (!(u.charIsLast(p, URANGE_WORD)) && ch2 == 'l')
			{
				SETPH(p, PHEU_ll);
				p2 = DEL(p2);	// l -> ll
				break;
			}
			//en el resto de los casos
			SETPH(p, PHEU_l);  // l->l
			break;

		case 'm':
			SETPH(p, PHEU_m);
			break;

		case 'n':
			//si va en interior de palabra,precedida de 'i',y seguida de vocal
			// se palataliza ,salvo si se trata de excepci¢n o
			//de expresi¢n (bait+auxiliar\sint‚tico) contraida
			p3 = PREV(p);  ch3 = p3 ? CH(p3) : 0;
			if (!(u.charIsFirst(p, URANGE_WORD)) && !(u.charIsLast(p, URANGE_WORD))) //interior de palabra
			{
				if(ch3=='i') //precedida de i
				{
					if (!(u.charIsLast(p, URANGE_WORD)) && strchr(aeiou, ch2)) // interior de palabra & sig vocal.
					{
							if(es_excepcion(u,p,'n')||es_bai_aditz(u,p))
							{
								SETPH(p, PHEU_n); // n -> n ; no palatalizacion
								break;
							}
						//si no es bai+auxiliar/sintetico ni excepci¢n
						//precedida de 'i' y seguida de vocal se palataliza
						SETPH(p,PHEU_ntilde);
						break; // siguiente vocal; n -> [J]
					}
				}
				//en los grupos nst y nzt de interior de palabra desaparece la n
				if(!(u.charIsLast(p, URANGE_WORD)) && strchr(sz,ch2)&&(!phtsimple))
				// siguiente s o z
				{
					p3 = NEXT(p2); ch3 = p3 ? CH(p3) : 0;
					if(ch3=='t')//la siguiente a [sz] es 't'
						break; // [aeiou]n[sz]t -> [aeiou][sz]t
				}
			}
			//si la n precede a m,b,¢ p se pronuncia m
			p3 = NEXT(p); ch3 = p3 ? CH(p3) : 0;
			if(ch3=='b' || ch3=='p' || ch3=='m')
			{
				SETPH(p, PHEU_m); // n [mbp] -> m
				break;
			}
			//en el resto de los casos se pronuncia n
			SETPH(p, PHEU_n); // n -> n
			break;

		case CS_ntilde: SETPH(p, PHEU_ntilde); break;

		case 'p':
			//al final de palabra, si la siguiente empieza con p,t,k,b,d,g,
			//y ambas palabras no est n separadas por pausa, desaparece la p.
			//en ese caso {b,d,g} plosivas
			if(u.charIsLast(p, URANGE_WORD) && !(u.wordIsLast(p, URANGE_PHRASE))&& (!phtsimple))
			{
							if(strchr(ptkbdg,ch2)){
								if(ch2=='b'){SETPH(p2,PHEU_b);p2=DEL(p2);}
								if(ch2=='d'){SETPH(p2,PHEU_d);p2=DEL(p2);}
								if(ch2=='g'){SETPH(p2,PHEU_g);p2=DEL(p2);}
								break;
							}
				// p -> [/]
			}
			// resto de casos se pronuncia p
			SETPH(p, PHEU_p);
			break;
		case 'q':
			//si va seguida de 'u'nos saltamos la 'u' y se pronuncia k
			//a no ser que sea 'qua' que no saltamos la u(la pronunciamos)
			if (ch2 == 'u') {
				p3 = NEXT(p2);
				ch3 = p3 ? CH(p3) : 0;	// caracter 3 (0 si no hay mas)
				if (!((ch3 == 'a')||(ch3=='o')||u.charIsLast(p2, URANGE_WORD)))
				p2 = DEL(p2);	// qu -> k excepto si qua o qu# (#=fin)
			}
			//siempre se pronuncia k
			SETPH(p, PHEU_k);
			break;	// q -> k */

		case 'r':
			//en el interior de palabra y entre vocales se pronuncia alveolar sonora
			p3 = PREV(p);  ch3 = p3 ? CH(p3) : 0;
			if (!(u.charIsFirst(p, URANGE_WORD)) && !(u.charIsLast(p, URANGE_WORD))
			 && strchr(aeiou,ch3) && strchr(aeiou, ch2)){
					SETPH(p, PHEU_r); // V+r+V -> r
					break;
			}
			//resto de casos alveolar vibrante
			SETPH(p, PHEU_rr);  // r -> rr
			//si viene una segunda r no hay que procesarla
			if (ch2=='r') p2=DEL(p2); // rr -> saltamos una r
			break;

		case 's':
			/*******caso ts*******/
			//si el caracter anterior es 't', se pronuncia ts excepto al final de
			//palabra si la siguiente comienza por consonante que se pierde la t.
			//ej: akats gehiegi--->akasgeieGi
			p3 = PREV(p);  ch3 = p3 ? CH(p3) : 0;
			//si delante de la s hay una 't' y est  en la misma palabra que la 's'
			if(ch3=='t' && !(u.charIsFirst(p, URANGE_WORD)))
			{ //si la s es £ltima de palabra pero no es final de frase
				if(u.charIsLast(p, URANGE_WORD) && !u.wordIsLast(p, URANGE_PHRASE)&& (!phtsimple))
				{
					//miro si la siguiente palabra empieza por consonante
					wo=u.wordNext(p, URANGE_PHRASE);
					hitza = u.cell(wo).getWord();
					ch3=hitza[0];

					if(ch3!='h' && !(strchr(aeiou,ch3)))
					{
						//en caso afirmativo pronuncio s.
						if(phtiparralde)
							SETPH(p, PHEU_z);
						else
							SETPH(p,PHEU_s);
						break;
					}
				}
				//resto de casos pronuncio ts.
				//asigno el fonema al primer caracter de la digraf¡a(la t)
				if(phtiparralde)
					SETPH(p3, PHEU_tZ);
				else
					SETPH(p3, PHEU_ts);
				break;
			}

			/*************caso s******************/
		 //si no hay t delante dentro de la misma palabra
			if(phtiparralde)
				SETPH(p, PHEU_z);
			else
				SETPH(p, PHEU_s);
			break;

		case 't':
		/**************** caso tt **********************/
			//si van dos 't' seguidas en la misma palabra se pronuncia PHEU_Q
			if(!(u.charIsLast(p, URANGE_WORD)) && ch2=='t')
			{
				SETPH(p, PHEU_tt); // tt -> Q
				p2 = DEL(p2);
				break;
			}
		/*************** t al final de palabra **************/
			//si la t va al final de palabra (no al final de frase) hay que mirar
			//si la siguiente palabra comienza por b,d,g,p,t,k --> la t desaparece
			//y b,d,g oclusivas
			if(u.charIsLast(p, URANGE_WORD) && !u.wordIsLast(p, URANGE_PHRASE)&& (!phtsimple))
			{
					if(strchr(ptkbdg,ch2)) // siguiente bodega-petaka
					{
						// t -> [/]
						if(ch2=='b'){SETPH(p2,PHEU_b);p2=DEL(p2);}
						if(ch2=='d'){SETPH(p2,PHEU_d);p2=DEL(p2);}
						if(ch2=='g'){SETPH(p2,PHEU_g);p2=DEL(p2);}
						break;
					}
					/********* caso lehen bait lehen ***********/
					wo=u.wordThis(p, URANGE_PHRASE);
					hitza = u.cell(wo).getWord();
					if(!strcmp(hitza,"bait")) // actual = bait
					{
						//el caso "lehen bait lehen" es una excepci¢n
						//se pronuncia lembailen
						if(!(u.wordIsFirst(p, URANGE_PHRASE)))
						{ //si al bait le sigue lehen
							wo=u.wordNext(p, URANGE_PHRASE);
							hitza = u.cell(wo).getWord(); // palabra siguiente
							if(!strcmp(hitza,"lehen"))
							{ //y si va precedido de lehen
								wo=u.wordPrev(p, URANGE_PHRASE);
								hitza = u.cell(wo).getWord(); // palabra anterior
								if(!strcmp(hitza,"lehen"))
									// lehen bait lehen  t->[/]
								break;
							}
						}
					/************ caso bait + aux/sint ************/

					//si la t corresponde a bait seguido de auxiliar o sintetico
					//que comience por n,l,z desaparece la t en los dos primeros casos
					//y se pronuncia tz en el caso de la z.

						wo=u.wordNext(p, URANGE_PHRASE);
						//bait seguido de auxiliar o sint‚tico que comience por n
						//nos saltamos la t
						if(es_aux_o_sint(u,wo,'n')) break;// bait + [n]adz -> bai n

						//bait seguido de auxiliar o sint‚tico que comience por l
						//nos saltamos la t
						if(es_aux_o_sint(u,wo,'l')) break;// bait + [l]adz -> bai l

						//bait seguido de auxiliar o sint‚tico que comience por z
						//pronunciamos tz y nos saltamos la z
						if(es_aux_o_sint(u,wo,'z'))
						{
							if(phtiparralde)
								SETPH(p2, PHEU_ts); // t -> tz // bait + [z]adz -> bai+[tZ]adz
							else
								SETPH(p2, PHEU_tZ); // t -> tz // bait + [z]adz -> bai+[tZ]adz
							p2=DEL(p2);//nos saltamos la z para no procesarla
							break;
						}
					}
				/*********** st + consonante *****************/
				//si la t va al final de palabra precedida de s ,y si la siguiente
				//palabra comienza por consonante, omitimos la t.
				//ejemplo:bost gizon-->bosgizon
				p3 = PREV(p);  ch3 = p3 ? CH(p3) : 0;
				if(ch3=='s') // anterior s
				{
						wo=u.wordNext(p, URANGE_PHRASE);
						hitza = u.cell(wo).getWord(); // siguiente palabra
						ch3=hitza[0]; // comienzo siguiente palabra
						if(!strchr(aeiou,ch3)) // siguiente consonante
						 // t -> [/]
							break;
				}
			}

			//si la t no est  al final de palabra miro si va seguida de s,x,z
			//en caso afirmativo me salto la t, no la proceso porque se procesan
			//las digraf¡as ts, tx y tz en la s,x y z respectivamente
			p3 = NEXT(p);  ch3 = p3 ? CH(p3) : 0;
			if(!(u.charIsLast(p,URANGE_WORD)) && strchr(sxz,ch3)) break;// st -> s

			SETPH(p, PHEU_t); // t -> t
			break;
		case 'v':
			if (u.wordIsFirst(p, URANGE_PHRASE)){
				SETPH(p,PHEU_b); // v -> b
				break;
			}
			p3 = PREV(p);  ch3 = p3 ? CH(p3) : 0;
			if (!(u.charIsFirst(p, URANGE_WORD)) && (ch3=='n'||ch3=='m'||ch3=='¤'))
			{
				SETPH(p, PHEU_b);
				break; // l+v -> b
			}
			//resto de casos
			SETPH(p,PHEU_baprox);
			break; // v -> B;
/*******HAY QUE METER LAS EXCEPCIONES DE LA W***************/
		case 'w': SETPH(p, PHEU_u); break;  // w -> u

		case 'x':
		/****************** caso tx ************************/
			//si el caracter anterior es 't', se pronuncia tS excepto al final de
			//palabra si la siguiente comienza por consonante que se pierde la t.
			//ej: antx pixka--->anxpixka
			p3 = PREV(p);  ch3 = p3 ? CH(p3) : 0;

			if(ch3=='t' && !(u.charIsFirst(p, URANGE_WORD)))
			{ //si el anterior es t y est  dentro de la misma palabra
				//y si no es la £ltima palabra de la frase
				if(u.charIsLast(p, URANGE_WORD) && !(u.wordIsLast(p, URANGE_PHRASE))&& (!phtsimple))
				{
				 //miro la siguiente palabra
					wo=u.wordNext(p, URANGE_PHRASE);
					hitza = u.cell(wo).getWord();
					ch3=hitza[0];
					//si comienza por consonante
					if( ch3!='h' && !(strchr(aeiou,ch3)))
					{
						SETPH(p,PHEU_x);
						break;
					}
				}
				SETPH(p3, PHEU_tx); // tx -> tS
				break;
			}
			/**************** caso x ********************/
			//si la x no va precedida de t se pronuncia x
			SETPH(p, PHEU_x); // x -> S
			break;

		case 'y': // como la j
			p3 = PREV(p);  ch3 = p3 ? CH(p3) : 0;
			//en comienzo absoluto ¢ seguida de n,l,s,z se pronuncia dj
			if(u.charIsFirst(p, URANGE_PHRASE) || strchr(nlsz,ch3))
			{
				SETPH(p, PHEU_dj); // y -> dj
				break;
			}
			//en el resto de los casos se pronuncia jj.
			else
			{
				if(phtiparralde)
					SETPH(p, PH_Jb); //j -> "J\"
				else
					SETPH(p, PHEU_jj); // j -> jj
				break;
				break;
			}
		case 'z':
			/************ caso tz **************/
			p3 = PREV(p);  ch3 = p3 ? CH(p3) : 0;
			//si el caracter anterior es 't', se pronuncia tZ excepto al final de
			//palabra si la siguiente comienza por consonante que se pierde la t.
			//ej: bihotz taupadak---->bioztaupaDak
			if(ch3=='t' && !(u.charIsFirst(p, URANGE_WORD))) // anterior t
			{
				if(u.charIsLast(p, URANGE_WORD)&&!(u.wordIsLast(p, URANGE_PHRASE))&& (!phtsimple)) // no es la ultima palabra
				{
					wo=u.wordNext(p, URANGE_PHRASE);
					hitza = u.cell(wo).getWord();
					ch3=hitza[0];
					if(ch3!='h' && !strchr(aeiou,ch3))
					{
						if(phtiparralde)
							SETPH(p, PHEU_s); // tz + C -> z + C
						else
							SETPH(p, PHEU_z); // tz + C -> z + C
						break;
					}
				}
				//asignamos el fonema al primer caracter de la digraf¡a(la t)
				if(phtiparralde)
					SETPH(p3, PHEU_ts); // tz -> ts
				else
					SETPH(p3, PHEU_tZ); // tz -> tZ
				break;
			}
			/*************** caso z ********************/
			//si la z no va tras t,y es la £ltima de palabra en interior de frase
			//comprobamos si se trata de 'ez'
			if(!(u.wordIsLast(p, URANGE_PHRASE)) && u.charIsLast(p,URANGE_WORD)/*&&(!phtsimple)*/)
			{
				wo=u.wordThis(p, URANGE_PHRASE);
				hitza = u.cell(wo).getWord(); // palabra actual

				if(!strcmp(hitza,"ez"))
				{
					wo=u.wordNext(p, URANGE_PHRASE);
					hitza = u.cell(wo).getWord();
					//si "ez"va seguido de palabra que empieza por 'n'
					if(hitza[0]=='n')
						//miro si se trata de verbo auxiliar o sintetico
						if(es_aux_o_sint(u,wo,'n')) break;
						 //en caso afirmativo se omite la z:
						 // 'ez' + [n]adz lagn    z -> [/]

					//si "ez" va seguido de palabra que empieza por 'l'
					if(hitza[0]=='l')
						//miro si se trata de verbo auxiliar o sintetico
						if(es_aux_o_sint(u,wo,'l')) break;
						//en caso afirmativo se omite la z:
						 // 'ez' + [l]adz lagn    z -> [/]

					//si "ez"va seguido de palabra que empieza por 'z'
					if(hitza[0]=='z')
					//miro si se trata de verbo auxiliar o sintetico
						if(es_aux_o_sint(u,wo,'z'))
						{//en caso afirmativo la z se convierte en tz
							//y nos saltamos la siguiente z
							if(phtiparralde)
								SETPH(p2, PHEU_ts); // z -> z
							else
								SETPH(p2, PHEU_tZ); // z -> z
							p2 = DEL(p2); // 'ez' + [z]adz lagn    z + z ->[/]+[tz]
							break;
						}
				}
			}
			//en el resto de los casos pronunciamos z
			if(phtiparralde)
				SETPH(p, PHEU_s); // z -> z
			else
				SETPH(p, PHEU_z); // z -> z
			break;

		// caracteres no contemplados, los saltamos directamente
		default: p2 = DEL(p); break;
		}
		p = p2;		// siguiente caracter
	}

#undef DEL
#undef SETPH
#undef NEXT
#undef PREV
}
#endif
/**********************************************************/
/* esta transforma fonemas i/u en j/w en los
	 diptongos/triptongos (convierte vocales -> aproximantes).
	 Se debe de hacer una vez silabificadas las palabras */

VOID LangEU_PhTrans::iu2jw(UttPh & u)
{ /*
	UttI p;

	for (p=u.phoneFirst(); p!=0; p=u.phoneNext(p)) {
		Phone ph = u.cell(p).getPhone();

		if (((ph == PHEU_i) || (ph == PHEU_u))
				&& (u.cell(p).getStress() == USTRESS_NONE)) {	// solo si es vocal debil no acentuada

			UttI pl = u.phonePrev(p, URANGE_SYLLABLE);
			UttI pr = u.phoneNext(p, URANGE_SYLLABLE);

			Phone phl = pl ? u.cell(pl).getPhone() : 0;		// fonema anterior en silaba

			Phone phr = pr ? u.cell(pr).getPhone() : 0;		// fonema siguiente en silaba

			if (LangEU_PhUti::phIsVowel(phl) || LangEU_PhUti::phIsVowel(phr))	// si hay vocal a izqda. o dcha. de vocal debil -> aproximante

				{} //$$$$$$$				u.cell(p).setPhone((ph == PHEU_i) ? PHEU_iaprox : PHEU_uaprox);

		}
	}*/
}

/**********************************************************/
