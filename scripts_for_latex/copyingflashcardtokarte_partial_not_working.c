#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 150
#define M 10000
#define TEXTEMPLATE "/Users/schmeckpeper/Documents/B_stud/TUHH/BSc_Technomathematik/A_Grundstudium/Mathematik/Lineare_Algebera_I/Vorlesung/Zusammenfassung/c/basicKarteTemplate.tex"



int main(int argc, char* argv[]){

  FILE *pF = fopen(argv[1], "r");
  FILE *pK = fopen(argv[2], "w");
  FILE *pC = fopen(TEXTEMPLATE, "r");
  int i = 0;
  char c;
  char buff1[M];
  char *pHelpString;

  fseek(pK,-14L,SEEK_END);

  while(i < 35){
    // printf("%d",i);
    // printf("%s",buff1);
// // Geht bis zum nächsten Eintrag
  if(i == 0){
    while(strcmp(fgets(buff1,N,pF),"\\cardfrontfoot{Körper}\n"));
  }else{
    // while(strcmp(fgets(buff1,N,pF),"\n"));
    printf("%d",i);
    fgets(buff1,N,pF);
    printf("%s",buff1);
    fgets(buff1,N,pF);
    printf("%s",buff1);
    if(!strcmp(buff1,"\\end{document}\n")){
      goto ENDE;
    }
  }
// // Kopiert das Kommentar{Kapitel}
    pHelpString = buff1;
    fprintf(pK,"\\kommentar{");
    while(*(pHelpString++) != '{');
    while(*(pHelpString++) != '}'){
      fprintf(pK,"%c", *(pHelpString-1));
    }
    fprintf(pK,"}\n");
// ersetzt nun \begin{flashcard} mit \begin{karte}
    fgets(buff1,N,pF);
    fprintf(pK,"\\begin{karte}");
    for(pHelpString = buff1; *(pHelpString) != '['; pHelpString++);
    for(;*(pHelpString) != '\n';pHelpString++){
      fprintf(pK,"%c",*pHelpString);
    }
    fprintf(pK,"%c",*(pHelpString++));
    while(strcmp(fgets(buff1,N,pF),"\\centr\n") != 0){
      fprintf(pK,"%s",buff1);
    }
    fprintf(pK,"%s",buff1);
    fprintf(pK,"\\vspace{-3.1em}\n");
    do{
      fgets(buff1,N,pF);
      fprintf(pK,"%s", buff1);
    } while(strcmp(buff1,"\\centr\n"));
    fgets(buff1,N,pF);
    fprintf(pK,"\\end{karte}\n\n");
  i++;
}
  ENDE:
  fprintf(pK,"\\end{document}");
  return 0;
}
