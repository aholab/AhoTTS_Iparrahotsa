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

Nombre fuente................ eu_proso.cpp
Nombre paquete............... aHoTTS
Lenguaje fuente.............. C++
Estado....................... -
Dependencia Hard/OS.......... -
Codigo condicional........... -

Codificacion................. Borja Etxebarria
.............................

Version  dd/mm/aa  Autor     Proposito de la edicion
-------  --------  --------  -----------------------
1.0.5 	 21/06/11  Inaki	Modificar comportamiento etiqueta <prosody rate"1000ms"  HTTS_PROSO_VAL
1.0.4 	 12/07/10  Inaki	 Añadir celdas para modificar la prosodia desde el texto (proyecto Aritz) HTTS_PROSO_VAL
1.0.3    05/01/10  inaki     Añadir modelos de duracion y pitch para Amaia (dur_amaia, pth3_amaia)
1.0.3    20/04/09  inaki     Añadir modelos de duracion para emociones karolina (dur_emo)
1.0.2    20/10/08  inaki     Añadir modelos de duracion para emociones (dur_sad y dur_happy)(Eva)
1.0.1    08/10/01  Yon2.     default dur model Dur2.
1.0.1    08/10/01  Yon2.     default pitch model Pth2.
1.0.0    31/01/00  borja     codefreeze aHoTTS v1.0
0.0.0    24/11/97  borja     Codificacion inicial.

======================== Contenido ========================
<DOC>
Metodos principales de {{LangEU_Prosod}} que llaman a los modelos de
pitch, energia y duracion para obtener la prosodia de una frase.
</DOC>
===========================================================
*/
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
/**********************************************************/

#include <assert.h>
#include "httsmsg.h"
#include "eu_lingp.hpp"
#include "xx_uti.hpp"
#include "uti.h"
//#define DEBUG() fprintf (stderr,"file..: %s -- line..: %d\n",__FILE__,__LINE__);
#define DEBUG()

/**********************************************************/

LangEU_Prosod::LangEU_Prosod( VOID )
{
	created=FALSE;

	pth_mean=1;
	pth_dev=0.1;

	dur_mean=1;
	dur_dev=0.1;

	pow_mean=1;
	pow_dev=0.1;

	prosdbname="base.lyp";

/* seleccion de modelos por defecto. El ultimo de cada tipo
es el que se selecciona. */
#ifdef HTTS_PROSOD_EU_DUR1
	dur_model="Dur1";
#endif
#ifdef HTTS_PROSOD_EU_DUR2
	dur_model="Dur2";
#endif
#ifdef HTTS_PROSOD_EU_DURSAD
	dur_model="DurSad";
#endif
#ifdef HTTS_PROSOD_EU_DURHAPPY
	dur_model="DurHappy";
#endif
#ifdef HTTS_PROSOD_EU_DUREMO
	dur_model="DurEmo";
#endif
#ifdef HTTS_PROSOD_EU_DURAMAIA
	dur_model="DurAmaia";
#endif
#ifdef HTTS_PROSOD_EU_POW2
	pow_model="Pow2";
#endif
#ifdef HTTS_PROSOD_EU_POW1
	pow_model="Pow1";
#endif
#ifdef HTTS_PROSOD_EU_PTH1
	pth_model="Pth1";
#endif
#ifdef HTTS_PROSOD_EU_PTH2
	pth_model="Pth2";
#endif
#ifdef HTTS_PROSOD_EU_PTH3
        pth_model="Pth3";
#endif
#ifdef HTTS_PROSOD_EU_PTH3AMAIA
        pth_model="Pth3Amaia";
#endif

#ifdef HTTS_PROSOD_EU_PTH1
//	pth1_dummy_ptr=NULL;
#endif
}

/**********************************************************/

LangEU_Prosod::~LangEU_Prosod( VOID )
{
#ifdef HTTS_PROSOD_EU_PTH1
//	if (pth1_dummy_ptr) { free(pth1_dummy_ptr); pth1_dummy_ptr=NULL; }
#endif
}

/**********************************************************/

BOOL LangEU_Prosod::create( VOID )
{
#ifdef HTTS_PROSOD_EU_PTH1
//	pth1_dummy_ptr=malloc(10);
#endif

	created=TRUE;
	return TRUE;
}

/**********************************************************/

VOID LangEU_Prosod::utt_prosody(UttPh & ut)
{
	assert(created);

	utt_emphasis(ut);  // calcular focos de enfasis

DEBUG()
	// calcular duraciones (ms)
#ifdef HTTS_PROSOD_EU_DUR1
	if (!strcmp(dur_model,"Dur1")) utt_dur1(ut); else
#endif
#ifdef HTTS_PROSOD_EU_DUR2
	if (!strcmp(dur_model,"Dur2")) utt_dur2(ut); else
#endif
#ifdef HTTS_PROSOD_EU_DURSAD
	if (!strcmp(dur_model,"DurSad")) utt_dur_sad(ut); else
#endif
#ifdef HTTS_PROSOD_EU_DURHAPPY
	if (!strcmp(dur_model,"DurHappy")) utt_dur_happy(ut); else
#endif
#ifdef HTTS_PROSOD_EU_DUREMO
	if (!strcmp(dur_model,"DurEmo")) utt_dur_emo(ut); else
#endif
#ifdef HTTS_PROSOD_EU_DURAMAIA
	if (!strcmp(dur_model,"DurAmaia")) utt_dur_amaia(ut); else
#endif
	htts_error("Invalid LangEU_Prosod::dur_model (%s)",(const CHAR*)dur_model);

DEBUG()

	// calcular curva de pitch
#ifdef HTTS_PROSOD_EU_PTH1
	if (!strcmp(pth_model,"Pth1")) utt_pth1(ut); else
#endif

#ifdef HTTS_PROSOD_EU_PTH2
#ifdef USE_TOKENIZER
	if (!strcmp(pth_model,"Pth2")) utt_pth2(ut); else
#else
	if (!strcmp(pth_model,"Pth2")) utt_pth1(ut); else
#endif
#endif

#ifdef HTTS_PROSOD_EU_PTH3
#ifdef USE_TOKENIZER
        if (!strcmp(pth_model,"Pth3")) utt_pth3(ut); else
#else
        if (!strcmp(pth_model,"Pth3")) utt_pth1(ut); else
#endif
#endif

#ifdef HTTS_PROSOD_EU_PTH3AMAIA
#ifdef USE_TOKENIZER
        if (!strcmp(pth_model,"Pth3Amaia")) utt_pth3_amaia(ut); else
#else
        if (!strcmp(pth_model,"Pth3")) utt_pth1(ut); else
#endif
#endif
	htts_error("Invalid LangEU_Prosod::pth_model (%s)",(const CHAR*)pth_model);

DEBUG()
	// calcular curva de energia
#ifdef HTTS_PROSOD_EU_POW1
	DEBUG()
	if (!strcmp(pow_model,"Pow1")) utt_pow1(ut); else
#endif
#ifdef HTTS_PROSOD_EU_POW2
	if (!strcmp(pow_model,"Pow2")) utt_pow2(ut); else
#endif
	htts_error("Invalid LangEU_Prosod::pow_model (%s)",(const CHAR*)pow_model);
	DEBUG()
}

/**********************************************************/

BOOL LangEU_Prosod::set( const CHAR *param, const CHAR * value )
{
	double d;
	int code = str2d(value,&d);

	if (!strcmp(param,"PthMean"))pth_mean=d;
	else if (!strcmp(param,"PthDev")) pth_dev=d;
	else if (!strcmp(param,"DurMean")) dur_mean=d;
	else if (!strcmp(param,"DurDev")) dur_dev=d;
	else if (!strcmp(param,"PowMean")) pow_mean=d?d:pow_mean;
	else if (!strcmp(param,"PthModel")&& !created) { pth_model=value; return TRUE; }
	else if (!strcmp(param,"DurModel")&& !created) { dur_model=value; return TRUE; }
	else if (!strcmp(param,"PowModel")&& !created) { pow_model=value; return TRUE; }
	#ifdef HTTS_PROSOD_EU_PTH3
		else if (!strcmp(param,"ProsDBName")/*&& !created*/) { prosdbname=value; return TRUE; }	
	#endif

#ifdef HTTS_PROSOD_EU_PTH1
//	else if (!strcmp(param,"Pth1_dummy")) {
//		if (!created) return FALSE;  // if needed
//		// do whatever
//		return TRUE;
//	}
#endif

	else return FALSE;

	if (code) htts_error("LangEU_Prosod: invalid value for %s (%s)",param,value);
	return TRUE;

	
}

/**********************************************************/

const CHAR *LangEU_Prosod::get( const CHAR *param )
{
#define VALRET(x) { sprintf(buf,"%g",(double)x); buf_get=buf; return buf_get; }
	char buf[20];



	if (!strcmp(param,"PthMean")) VALRET(pth_mean);
	if (!strcmp(param,"PthDev")) VALRET(pth_dev);
	if (!strcmp(param,"DurMean")) VALRET(dur_mean);
	if (!strcmp(param,"DurDev")) VALRET(dur_dev);
	if (!strcmp(param,"PowMean")) VALRET(pow_mean);
	if (!strcmp(param,"PowDev")) VALRET(pow_dev);
	if (!strcmp(param,"PthModel")) return pth_model;
	if (!strcmp(param,"DurModel")) return dur_model;
	if (!strcmp(param,"PowModel")) return pow_model;
	if (!strcmp(param,"ProsDBName")) return prosdbname;

#ifdef HTTS_PROSOD_EU_PTH1
//	if (!strcmp(param,"Pth1_dummy")) return "dummy";
#endif

	return FALSE;
}

/**********************************************************/
#ifdef HTTS_PROSO_VAL
VOID LangEU_Prosod::utt_n_val_pitch(UttPh & ut)//Aritz Modifica el valor de pitch dependiendo del valor de la etiqueta
{
	UttI wordp,phonep;
	float val_etiq;
	float valor_pitch;
	//float valor_rate;
	//float valor_volume;
	//float valor_emphasis_dur;
	//float valor_emphasis_pot;
	double val;
	//float valor_pitch_palabra;
	int i ;
	
	for(wordp=ut.wordFirst();wordp!=0;wordp=ut.wordNext(wordp))
	{
		//fprintf(stderr,"ut.cell(wordp).val_pitch:%d\n",ut.cell(wordp).val_pitch);
		if(ut.cell(wordp).val_pitch/*||ut.cell(wordp).val_rate||ut.cell(wordp).val_volume||ut.cell(wordp).val_emphasis*/)
		{
			//fprintf(stderr,"Entro:\n");
			val_etiq=(ut.cell(wordp).val_pitch);
			val_etiq=val_etiq/100;

			//valor_pitch_palabra=ut.cell(wordp).getPth();
			for(phonep=ut.phoneFirst(wordp,URANGE_WORD);phonep!=0;phonep=ut.phoneNext(phonep,URANGE_WORD))
			{
				for(i=0;i<ut.cell(phonep).get_PthN();i++)
				{

					valor_pitch=ut.cell(phonep).get_Pth(i);
					val=(val_etiq)*(valor_pitch);
					val=valor_pitch+val;
					//ut.cell(phonep).set_PthX(0,0.25);
					ut.cell(phonep).set_Pth(i,val);
					//fprintf(stderr,"val_etiq:%f\n",val_etiq);
					//fprintf(stderr,"valor_pitch:%f\n",valor_pitch);
					//fprintf(stderr,"val:%f\n",val);
				}
			}
		}
	}
}
/******************************************************************************/
VOID LangEU_Prosod::utt_n_val_rate(UttPh & ut)//Aritz Modifica el valor de la duración dependiendo del valor de la etiqueta
{
	UttI wordp,phonep;
	float val_etiq=0;
	float valor_rate=0;
	double val=0;
	
/*	for(wordp=ut.wordFirst();wordp!=0;wordp=ut.wordNext(wordp))
	{
		if(ut.cell(wordp).val_rate)
		{
			val_etiq=(ut.cell(wordp).val_rate);
			val_etiq=val_etiq/100;

			for(phonep=ut.phoneFirst(wordp,URANGE_WORD);phonep!=0;phonep=ut.phoneNext(phonep,URANGE_WORD))
			{
				valor_rate=ut.cell(phonep).getDur();
				val=(val_etiq)*(valor_rate);
				val=valor_rate-val;
				ut.cell(phonep).setDur(val);
	//			fprintf(stderr,"val_etiq:%f\n",val_etiq);
	//			fprintf(stderr,"valor_rate:%f\n",valor_rate);
	//			fprintf(stderr,"val:%f\n",val);
			}
		}
	}*/
	//inaki : cogemos el val_rate medio de la frase y normalizamos la duracion en base a ello
	float factor_vocal=0.45, factor_con_sorda=0.2, factor_con_sonora=0.25, factor_pausas=0.1;
//      float factor_vocal=0.333, factor_con_sorda=0.333, factor_con_sonora=0.333, factor_pausas=0;
        int contador=0;
        float dur_total_predicha=0, dur_total_predicha_vocal=0, dur_total_predicha_con_sorda=0, dur_total_predicha_con_sonora=0, dur_total_predicha_pausas=0;
        for(wordp=ut.wordFirst();wordp!=0;wordp=ut.wordNext(wordp))
        {
		if(ut.cell(wordp).val_rate){
	                val_etiq += ut.cell(wordp).val_rate;
        	        for(phonep=ut.phoneFirst(wordp,URANGE_WORD); phonep!=0; phonep=ut.phoneNext(phonep,URANGE_WORD)){
                	        float dur = ut.cell(phonep).getDur();
                        	dur_total_predicha += dur;
	                        char phone = ut.cell(phonep).getPhone();
        	                if(strchr("aeioujw", phone) != NULL) //vocal
                	                dur_total_predicha_vocal += dur;
                        	else if(strchr("pkSsfxPVXCtXTQhz2Z",phone) != NULL) //consonante sorda
                                	dur_total_predicha_con_sorda += dur;
	                        else if(phone == '_') //pausa (incluye pausas intermedias y final)
        	                        dur_total_predicha_pausas += dur;
                	        else //consonante sonora
                        	        dur_total_predicha_con_sonora += dur;
                	}
	                ++contador;
		}
       	}
	if(contador <= 0)
		return;
	val_etiq /= contador;
	if( val_etiq /  dur_total_predicha < 1.3){ // si no hay que alargar mucho o hay que acortar, mantenemos factores constantes para todos los fonemas
	        factor_vocal=0.3;
        	factor_con_sorda=0.3;
	        factor_con_sonora=0.3;
        	factor_pausas=0.1;
	}

        float factor_modif_dur = (val_etiq - dur_total_predicha) / (dur_total_predicha_vocal * factor_vocal + dur_total_predicha_con_sorda * factor_con_sorda + dur_total_predicha_con_sonora * factor_con_sonora + dur_total_predicha_pausas * factor_pausas);

        //modificamos las duraciones
        for(wordp=ut.wordFirst();wordp!=0;wordp=ut.wordNext(wordp))
        {
                for(phonep=ut.phoneFirst(wordp,URANGE_WORD); phonep!=0; phonep=ut.phoneNext(phonep,URANGE_WORD)){
                        float dur = ut.cell(phonep).getDur();
                        char phone = ut.cell(phonep).getPhone();
                        if(strchr("aeioujw", phone) != NULL) //vocal
                                ut.cell(phonep).setDur( dur * ( 1  + factor_vocal * factor_modif_dur )) ;
                        else if(strchr("pkSsfxPVXCtXTQhz2Z",phone) != NULL) //consonante sorda
                                ut.cell(phonep).setDur( dur * ( 1  + factor_con_sorda * factor_modif_dur )) ;
                        else if(phone == '_') //pausa (incluye pausas intermedias y final)
                                ut.cell(phonep).setDur( dur * ( 1  + factor_pausas * factor_modif_dur )) ;
                        else
                                ut.cell(phonep).setDur( dur * ( 1  + factor_con_sonora * factor_modif_dur )) ;

                }
        }
}
/**************************************************************************************/
VOID LangEU_Prosod::utt_n_val_volume(UttPh & ut)//Aritz Modifica el valor de la potencia dependiendo del valor de la etiqueta
{
	UttI wordp,phonep;
	float val_etiq;
	float val_volume;
	double val;
	

	for(wordp=ut.wordFirst();wordp!=0;wordp=ut.wordNext(wordp))
	{
		if(ut.cell(wordp).val_volume)
		{
			val_etiq=(ut.cell(wordp).val_volume);
			val_etiq=val_etiq/100;

			for(phonep=ut.phoneFirst(wordp,URANGE_WORD);phonep!=0;phonep=ut.phoneNext(phonep,URANGE_WORD))
			{
				
					val_volume=ut.cell(phonep).getPow();
					val=(val_etiq)*(val_volume);
					val=val_volume+val;
					ut.cell(phonep).setPow(val);
					//fprintf(stderr,"val_etiq:%f\n",val_etiq);
					//fprintf(stderr,"valor_volume:%f\n",val_volume);
					//fprintf(stderr,"val:%f\n",val);
			}
		}
	}
}
/******************************************************************************/
VOID LangEU_Prosod::utt_n_val_emphasis(UttPh & ut)//Aritz Modifica el valor del pitch, el de la potencia y el de la duracion.
{
	UttI wordp,phonep;
	float val_etiq;
	float val_pot;
	float val_dur;
	float val_pitch;
	double val;
	int i;

	for(wordp=ut.wordFirst();wordp!=0;wordp=ut.wordNext(wordp))
	{
		if(ut.cell(wordp).val_emphasis)
		{
			val_etiq=(ut.cell(wordp).val_emphasis);
			val_etiq=val_etiq/100;

			for(phonep=ut.phoneFirst(wordp,URANGE_WORD);phonep!=0;phonep=ut.phoneNext(phonep,URANGE_WORD))
			{
				for(i=0;i<ut.cell(phonep).get_PthN();i++)
				{
					val_pitch=ut.cell(phonep).get_Pth(i);
					val=val_etiq*val_pitch;
					val=val_pitch+val;
					ut.cell(phonep).set_Pth(i,val);
					//fprintf(stderr,"valor_etiqueta:%f\n",val_etiq);
					//fprintf(stderr,"valor_pitch:%f\n",val_pitch);
					//fprintf(stderr,"val:%f\n",val);
				}
				val_pot=ut.cell(phonep).getPow();
				val=(val_etiq)*(val_pot);
				val=val_pot+val;
				ut.cell(phonep).setPow(val);
				//fprintf(stderr,"val_pot:%f\n",val_pot);
				//fprintf(stderr,"val:%f\n",val);
				val_dur=ut.cell(phonep).getDur();
				val=val_etiq*val_dur;
				val=val_dur+val;
				ut.cell(phonep).setDur(val);
				//fprintf(stderr,"val_etiq:%f\n",val_etiq);
				//fprintf(stderr,"val_dur:%f\n",val_dur);
				//fprintf(stderr,"val:%f\n",val);
			}
		}
	}
}
/*************************************************************************************/
VOID LangEU_Prosod:: utt_n_val_range(UttPh & ut)//aRITZ
{
	UttI phonep,wordp;
	int numpun;
	double val;
	int i=0;
	double sum,media,pitch,desv,sumcuad;
	double pitch_minimo;
	double pitch_maximo;
	float val_etiq;
	
	for(wordp=ut.wordFirst();wordp!=0;wordp=ut.wordNext(wordp))
	{
		sum=0;media=0;pitch=0;desv=0;sumcuad=0;numpun=0;pitch_minimo=10000;pitch_maximo=0;		
		if(ut.cell(wordp).val_range!=0)
		{
			
			val_etiq=ut.cell(wordp).val_range;
			val_etiq=val_etiq/100;
			

			for(phonep=ut.phoneFirst(wordp,URANGE_WORD);phonep!=0;phonep=ut.phoneNext(phonep,URANGE_WORD))
			{
				for(i=0;i<ut.cell(phonep).get_PthN();i++)
				{	
					numpun++;
					pitch=ut.cell(phonep).get_Pth(i);
					sum+=pitch;
					sumcuad+=pitch*pitch;
					if(pitch<pitch_minimo)
					{
						pitch_minimo=pitch;
					}
					if(pitch>pitch_maximo)
					{
						pitch_maximo=pitch;
					}	
				}
			}
			//fprintf(stderr,"pitch minimo:%f\n",pitch_minimo);
			media=(sum/numpun);
			//fprintf(stderr,"media:%f\n",media);
		//	desv=sqrt((numpun*sumcuad-sum*sum)/(numpun*numpun));
			fprintf(stderr,"desv1:%f\n desv2:%f\n",desv,sqrt((sumcuad/numpun-media*media)));
			//desv=desv+(desv*val_etiq);
			desv=1+ val_etiq;
			//fprintf(stderr,"desv:%f\n",desv);
			//fprintf(stderr,"palabra:%s\n",ut.cell(wordp).getWord());
			for(phonep=ut.phoneFirst(wordp,URANGE_WORD);phonep!=0;phonep=ut.phoneNext(phonep,URANGE_WORD))
			{
				for(i=0;i<ut.cell(phonep).get_PthN();i++)
				{
					fprintf(stderr,"valor:%f\n",(pitch_minimo-media)*desv+media);
					if((pitch_minimo-media)*desv+media<0)
					{
						desv=-0.75*media/(pitch_minimo-media);
					}
					pitch=media+(ut.cell(phonep).get_Pth(i)-media)*desv;
					fprintf(stderr,"pitch_ant:%f pitch_post: %f\n",ut.cell(phonep).get_Pth(i),pitch);
					ut.cell(phonep).set_Pth(i,pitch);
					
				}

			}
		}
	}
}
/*************************************************************************************/
#endif
				

