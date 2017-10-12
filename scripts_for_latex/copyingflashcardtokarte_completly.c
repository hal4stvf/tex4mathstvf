#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 10000
#define M 10000
#define TEXTEMPLATE "basicKarteTemplate.tex"


int atenddocument(FILE** pK){
  char c = 'a';
  if(fgetc(*pK) != EOF){
    return 1;
  }else{
    fseek(*pK,-1l,SEEK_CUR);
    return 0;
  }
}

int main(int argc, char** argv){

  FILE *pF = fopen(argv[1], "r");
  FILE *pK = fopen(argv[2], "w");
  FILE *pC = fopen(TEXTEMPLATE, "r");
  int i = 0;
  int j = 238;
  char c;
  char buff1[M];
  char *pHelpString;

printf("%s ",argv[1]);
printf("%s\n",argv[2]);

// COPYING TEXTEMPLATE TO ARGV[2]
  while((c = fgetc(pC)) != EOF){
    fprintf(pK,"%c",c);
  }


  (argc > 3)? sscanf(argv[3],"%d",&j):(j=238);

  while(i < j){
    printf("%d\n",i);
    if(atenddocument(&pK)) break;
// // Geht bis zum nächsten Eintrag
  if(i == 0){
    while(strcmp(fgets(buff1,N,pF),"\\cardfrontfoot{Körper}\n"));
  }else{
    // printf("%d",i);
    fgets(buff1,N,pF);
    // printf("%s",buff1);
    fgets(buff1,N,pF);
    // printf("%s",buff1);
  }
// // Kopiert das Kommentar{Kapitel}
    pHelpString = buff1;
    fprintf(pK,"\\kommentar{\\scriptsize ");
    while(*(pHelpString++) != '{');
    while(*(pHelpString++) != '\n'){
      fprintf(pK,"%c", *(pHelpString-1));
    }
    fprintf(pK,"\n");
// ersetzt nun \begin{flashcard} mit \begin{karte}
    fgets(buff1,N,pF);
    fprintf(pK,"\\begin{karte}");
    for(pHelpString = buff1; *(pHelpString) != '['; pHelpString++);
    for(;*(pHelpString) != '\n';pHelpString++){
      if((*(pHelpString+1) == '\n') && (*(pHelpString) != '}')){
        printf("%s\n",buff1);
      }
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
  printf("%s",buff1);
  // if(!strcmp(buff1,"\\end{document}\n")){
  //   printf("HUHRUHRUA\n\n");
  // }
}
  ENDE:
  fprintf(pK,"\\end{document}");
  return 0;
}
