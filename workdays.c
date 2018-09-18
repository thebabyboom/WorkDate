#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*----------------------------------------------------------------------*/
/*  FUNCTION DAYINTHEWEEK - RETURN  0 IF THE DAY IS SATERDAY OR SUNDAY	*/
/*----------------------------------------------------------------------*/
int dayintheweek(int ditw){
  int ys, ms, ds;
  struct tm ts;
  time_t tts;
  char wday[4];
  ys=ditw/10000;
  ms=ditw-(ditw/100);
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
  char year[5];
  struct tm date_tm;struct tm *date_tmp_p;
  time_t tps;
  long date_tmp_l = 0;
  char year_tmp[5],month_tmp[3],day_tmp[3];
  int buffer_i=0;char buffer_c[2]="";
  int test=0;
  /* hdays[0]	- NOUVEL AN			- 1er JANVIER	*/
  /* hdays[1]	- LUNDI DE PAQUES				*/
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
  if(c_year == 2008) hdays[3]=21000101;
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

/*----------------------------------------------------------------------*/
/*			WORDAYS FUNCTION				*/
/*----------------------------------------------------------------------*/

int workdays(char *enddate, char *startdate)
{
  struct tm ts, te;
  time_t tts, tte;
  unsigned int ys, ms, ds, ye, me, de;
  int days = 0, wdays = 0, d, e, i, difd = 0, dife = 0;
  int startint=0;
  int endint=0;
  int hdays[10];
  int sizetab=11, nb_hdays, c_year;
  int ditw=0;

  sscanf(startdate,"%d-%d-%d",&ys,&ms,&ds); /* split de la date d?but en 3 var. */
  sscanf(enddate,"%d-%d-%d",&ye,&me,&de);   /* split de la date fin en 3 var. */
  startint=(ys*10000)+(ms*100)+ds;
  endint=(ye*10000)+(me*100)+de;
  ts.tm_mday = ds;
  ts.tm_mon = ms-1;
  ts.tm_year = ys-1900;
  ts.tm_hour = ts.tm_min  = ts.tm_sec  = 1;
  te.tm_mday = de;
  te.tm_mon = me-1;
  te.tm_year = ye-1900;
  te.tm_hour = 2; te.tm_min  = te.tm_sec  = 1;
  tts = mktime(&ts);
  tte = mktime(&te);
  days = (int)(difftime(tte,tts)/60/60/24);
  d = ts.tm_wday;
  e = te.tm_wday;
  if (d == 0 || d == 6) 
    difd=1;
  if (e == 0 || e == 6)
    dife=-1;
  for (i = 0; i < days; i++) {
    if (d != 0 && d != 6)
      wdays++;
    d++;
    if (d > 6) d = 0;
  }
  wdays=wdays+difd+dife;

  nb_hdays = 0;
  for(c_year=ys; c_year <=ye;  c_year++){
   official_hdays(hdays,c_year);
   i=0;

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
  wdays = wdays - nb_hdays;
  return wdays;
}
