#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
/*----------------------------------------------------------------------*/
/*  FUNCTION DAYINTHEWEEK - RETURN  0 IF THE DAY IS SATERDAY OR SUNDAY	*/
/*----------------------------------------------------------------------*/
int dayintheweek(int ditw){
  int ys=0, ms=0, ds=0;
  struct tm ts;
  time_t tts;
  char wday[4]={'0','0','0','0'};
  ys=ditw/10000;
  ms=(ditw-(ys*10000))/100;
  ds=ditw-((ys*10000)+(ms*100));
  ts.tm_mday = ds;
  ts.tm_mon = ms-1;
  ts.tm_year = ys-1900;
  ts.tm_hour = ts.tm_min  = ts.tm_sec  = 1;
  tts = mktime(&ts);
  strncpy(wday,ctime(&tts),3);

  if(strcmp(wday,"Sat") == 0 || strcmp(wday,"Sun") == 0)
        return 0;
  else
    return 1;
}

/*------------------------------------------------------------------*/
/* FUNCTION CONVERT_DATE - CONVERT A DATE (TM STRUCT)  TO A INTEGER */
/*------------------------------------------------------------------*/
int convert_date(struct tm *date_p){
  int buffer_i=0;
  int date_return=0;
  char buffer_c[2]="";
  char year_tmp[5],month_tmp[3],day_tmp[3];

  buffer_i =
  sprintf(year_tmp,"%d",buffer_i);
  buffer_i = date_p->tm_mon+1;
  if(buffer_i<10){
    sprintf(buffer_c,"%d",buffer_i);
    month_tmp[0]='0';
        month_tmp[1]=buffer_c[0];
        month_tmp[2]='\0';
  }
  else sprintf(month_tmp,"%d",buffer_i);

  strncpy(buffer_c,"",3);
  buffer_i = date_p->tm_mday;
  if(buffer_i<10){
    sprintf(buffer_c,"%d",buffer_i);
    day_tmp[0]='0';
        day_tmp[1]=buffer_c[0];
        day_tmp[2]='\0';
  }
  else sprintf(day_tmp,"%d",buffer_i);

  date_return=(( ((int)date_p->tm_year) +1900)*10000)+(((int)date_p->tm_mon)+1)*100+((int)date_p->tm_mday);
  return date_return;
}
/*----------------------------------------------------------------------*/
/* FUNCTION OFFICIAL_HDAYS - CALCULATE THE OFFICIAL "HOLLYDAYS" 	*/
/*----------------------------------------------------------------------*/

int official_hdays(int hdays[],int c_year){
  int sizetab=11;
  int n = 0;int a = 0;int b = 0;int c = 0;int d = 0;int e = 0;int p = 0;
  char year[4];
  struct tm date_tm;struct tm *date_tmp_p;
  time_t tps;
  long date_tmp_l = 0;
  char year_tmp[5],month_tmp[3],day_tmp[3];
  int buffer_i=0;char buffer_c[2]="";
  int test=0;
  /*  hdays[0]	- NOUVEL AN			- 1er JANVIER	*/
  /*  hdays[1]	- LUNDI DE PAQUES				*/
  /*  hdays[2]	- FETE DU TRAVAIL		- 1er MAI	*/
  /*  hdays[3]	- ASCENSION					*/
  /*  hdays[4]	- LUNDI DE PENTECOTE				*/
  /*  hdays[5]	- FETE NATIONALE		- 21  JUILLET	*/
  /*  hdays[6]	- ASSOMPTION			- 15  AOUT	*/
  /*  hdays[7]	- TOUSSAINT			- 1er NOVEMBRE	*/
  /*  hdays[8]	- ARMISTICE			- 11  NOVEMBRE	*/
  /*  hdays[9]	- NOEL				- 25  DECEMBRE	*/


  /* hdays[0]	- NOUVEL AN			- 1er JANVIER	*/
  hdays[0]=(c_year*10000)+101;


  //CALCUL DES NOMBRES DE JOURS A AJOUTER AU 31/03/C_YEAR
  n = c_year-1900;a = n%19;b = ((a*7)+1)/19;c = ((11*a)-b+4)%29;d = n/4;e = (n-c+d+31)%7;p = 25-c-e; //nb jours avant (si n?g.) ou apr?s (si pos.) le 31/03


  /* hdays[1] - LUNDI DE PAQUES*/
  date_tm.tm_year = c_year-1900;date_tm.tm_mon  = 3-1; /*janv=0, fevr=1, etc.*/date_tm.tm_mday = 31;date_tm.tm_hour = date_tm.tm_min = date_tm.tm_sec = 0;
  tps = mktime(&date_tm);date_tmp_l= tps;date_tmp_l = date_tmp_l + ((p+1)*86400);
  if(c_year == 2008)date_tmp_l = date_tmp_l + 86400;
  tps = date_tmp_l;

  date_tmp_p = localtime(&tps);
  /*printf("TEST1:%d\n", test);*/
  hdays[1]=convert_date(date_tmp_p);
  test=0;

  /* hdays[2] - FETE DU TRAVAIL	- 1er MAI*/
  hdays[2]=(c_year*10000)+501;

  /* hdays[3] - ASCENSION*/
  date_tmp_l= tps;
  date_tmp_l = date_tmp_l + ((40-2)*86400);
  tps = date_tmp_l;
  date_tmp_p = localtime(&tps);
  if(c_year == 2008) hdays[3]=20080501;
  else hdays[3]=convert_date(date_tmp_p);
  test=0;

  /* hdays[4] - LUNDI DE PENTECOTE*/
  date_tmp_l= tps;
  date_tmp_l = date_tmp_l + ((10+1)*86400);
  tps = date_tmp_l;
  date_tmp_p = localtime(&tps);
  if(c_year == 2008) hdays[4]=20080512;
  else hdays[4]=convert_date(date_tmp_p);
  test=0;

  /* hdays[5] - FETE NATIONALE - 21  JUILLET*/
  hdays[5]=(c_year*10000)+721;

  /* hdays[6] - ASSOMPTION - 15  AOUT*/
  hdays[6]=(c_year*10000)+815;

  /* hdays[7] - TOUSSAINT - 1er NOVEMBRE*/
  hdays[7]=(c_year*10000)+1101;

  /* hdays[8] - ARMISTICE - 11  NOVEMBRE*/
  hdays[8]=(c_year*10000)+1111;

  /* hdays[9] - NOEL - 25  DECEMBRE*/
  hdays[9]=(c_year*10000)+1225;

  return 0;
}

int workdate(int jour, char *startdate)
{
  struct tm ts, te;
  struct tm te_p;
  time_t tts, tte;
  unsigned int ys, ms, ds, ye, me, de;
  int days = 0,tdays=0, d, e, i;
  int startint=0;
  int endint=0;
  int hdays[10];
  int nb_hdays, c_year;
  int ditw=0;
	tdays=jour; //a changer en parametre
	sscanf(startdate,"%d-%d-%d",&ys,&ms,&ds); //startdate a changer en parametre
	//ds=1;//car on ajoute toujours au premier du mois
	startint=(ys*10000)+(ms*100)+ds;
  	ts.tm_mday=ds;
	ts.tm_mon = ms-1;
	ts.tm_year = ys-1900;
	ts.tm_hour = ts.tm_min  = ts.tm_sec  = 1;
	tts = mktime(&ts);

	for (i=0;i<tdays;++i)
	{
		days=i*(86400);//86400 1 jour en secondes
		tte=tts+days;//increment de la date de départ de 1 jours (en secondes)
		te_p=*localtime(&tte);//transformation des seconde en structure temps
		te.tm_mday=te_p.tm_mday;
		te.tm_mon=te_p.tm_mon;
		te.tm_year=te_p.tm_year;te.tm_hour=te.tm_min=te.tm_sec=1;
		de=te.tm_mday;me=te.tm_mon+1;ye=te.tm_year+1900;
		endint=(ye*10000)+(me*100)+de;//transformation pour la verification des jours fériés
		//d = ts.tm_wday;
		e = te_p.tm_wday;
		/* if (d == 0) {
			tdays++;
		}
    	else if(d==6){
    		tdays=tdays+2;
    	}
    	else{
    	tdays=tdays+0;
    	}
 */
 //test pour voir si on est un samedi ou un dimanche
    	if (e == 0 || e == 6){
    		tdays++;
		}
	}



   //Calcul du nombre de jours fériés entre les deux dates
    nb_hdays = 0;
  for(c_year=ys; c_year <=ye;  c_year++){
   official_hdays(hdays,c_year);

   for (i=0; i<10;i++){
   ditw=hdays[i];
   /*printf("ditw: %d\n",ditw);*/
    if(dayintheweek(ditw)){
      if((startint<=hdays[i]) && (endint>=hdays[i]))
                nb_hdays++;
    }

   }
  ditw=0;

  }
  	tte=mktime(&te);//récupération de la date de fin en secondes
  	days=(nb_hdays*86400);//transformation du nombre de jours fériés en secondes (86400 1 jour en secondes)
	tte=tte+days;//ajout du nbre de jours fériés
	te_p=*localtime(&tte);//transformation des secondes en structure temps
	int date = convert_date(&te_p);//conversion de la date en entier pour le return
	return date;
}
