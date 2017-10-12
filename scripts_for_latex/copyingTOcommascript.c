#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M 100000

int main(int argc, char** argv){

  FILE* pR = fopen(argv[1],"r");
  FILE* pW = fopen(argv[2],"w");

  char c;
  char buff[M];
  char helpstr[M];
  char* pHelp = helpstr;

  for(int i = 0;i < 121 ;i++){
      // Liest bis zum ersten Eintrag und kopiert ihn in helpstr
    if(i == 0){
      while((strcmp(fgets(buff,M,pR),"\\cardfrontfoot{Körper}\n") != 0));
    }else{
      while(strncmp(fgets(buff,M,pR),"\\cardfront",5) != 0);
    }
    strcpy(helpstr,buff);
    pHelp = helpstr;
    printf("%d,%s",i,buff);
    // fprintf(pW,"%s\n\n",helpstr);
      // Stellt den pointer auf ein char nach '{'
    while((c = *(pHelp++)) != '{');
      // druckt ein  " in ankitest
    fprintf(pW,"\"");
      // druckt bis zum '}' in ankitest
    while(*(pHelp+1) != 10){
      fprintf(pW,"%c",*(pHelp++));
    }
      // druckt das ",
    fprintf(pW,"\",");

      // hol sich die nächste Zeile und stellt den Pointer richtig ein
    strcpy(helpstr,fgets(buff,M,pR));
    pHelp = helpstr;

  // druckt DEN TYP
    while(*(pHelp++) != '[');
    fprintf(pW,"\"");
    while(*(pHelp) != ']'){
      if(*pHelp == '\"'){
        fprintf(pW,"\"\"");
        pHelp++;
      }else{
        fprintf(pW,"%c", *(pHelp++));
      }
    }
    fprintf(pW,"\",");

  // Druckt den BEGRIFF
  while(*(pHelp++) != '{');
  fprintf(pW,"\"[latex]");

    while(*(pHelp+1) != 10){
      (*pHelp == '\"')? (fprintf(pW,"%c\"",*(pHelp++))):(fprintf(pW,"%c",*(pHelp++)));
      // fprintf(pW,"%c",*(pHelp++));
      if((*(pHelp+1) == 10) && (*pHelp != '}')){
        while(strcmp(fgets(buff,M,pR),"\\centr\n") != 0){
          strcpy(helpstr,buff);
          pHelp = helpstr;
          while(*(pHelp) != 10){
            (*pHelp == '\"')? (fprintf(pW,"%c\"",*(pHelp++))) :(fprintf(pW,"%c",*(pHelp++)));
          }
          fprintf(pW,"\n");
        }
        break;
      }
    }
  fprintf(pW,"[/latex]\",\"[latex]");

  // Inhalt
    if(strcmp(buff,"\\centr\n") != 0) fgets(buff,M,pR);
    while(strcmp(fgets(buff,M,pR),"\\centr\n") != 0){
      strcpy(helpstr,buff);
      pHelp = helpstr;
      while(*(pHelp) != 10){
        if( *pHelp == '\"'){
          fprintf(pW,"\"\"");
          pHelp++;
        }else{
          fprintf(pW,"%c",*(pHelp++));
        }
      }
      fprintf(pW,"\n");
    }
    fprintf(pW,"[/latex]\"\n\n");
  }
  // printf("%s",fgets(buff,M,pR));
  // printf("%s",fgets(buff,M,pR));

  // while((fgets(buff,M,pR),"\n") != 0);
}
