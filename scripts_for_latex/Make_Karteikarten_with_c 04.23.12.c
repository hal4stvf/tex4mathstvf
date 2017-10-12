#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 1000
#define M 10000
#define ENDD fprintf(pIn,"%c%cend%cdocument%c",10,92,123,125);
#define ENDF fprintf(pIn,"%cend%cflashcard%c%c",92,123,125,10);
char bufferN[N];
char bufferM[M];

struct math_fc{
char Kapitel[N];
char Typ[N];
char Begriff[N];
char Inhalt[M];
struct math_fc *pNext;
struct math_fc *pPrev;
};
typedef struct math_fc ma2tex;

// NEWENTRY Funktion
void newentry(ma2tex** pAnfang){
  ma2tex* pHelper1 = *pAnfang;
  ma2tex* pHelper2;
  if(*pAnfang == NULL){
    if((*pAnfang = (ma2tex*)malloc(sizeof(ma2tex))) == NULL){
      printf("Nicht genügend Speicher. Sehr kritisch.");
    }
    pHelper1 = *pAnfang;
    printf("Kapitel: ");
    fgets(bufferN, N, stdin);
    strcpy(pHelper1->Kapitel, bufferN);
    printf("Typ: ");
    fgets(bufferN, N, stdin);
    strcpy(pHelper1->Typ, bufferN);
    printf("Begriff: ");
    fgets(bufferN, N, stdin);
    strcpy(pHelper1->Begriff, bufferN);
    printf("Inhalt: ");
    fgets(bufferM, M, stdin);
    strcpy(pHelper1->Inhalt, bufferM);
    pHelper1->pPrev = NULL;
    pHelper1->pNext = NULL;
    *pAnfang = pHelper1;
  }else{
    pHelper2 = *pAnfang;
    while(pHelper2->pNext != NULL){
      pHelper2 = pHelper2->pNext;
    }
    if((pHelper2->pNext = (ma2tex*)malloc(sizeof(ma2tex))) == NULL){
      printf("Nicht genügend Speicher. Sehr kritisch.");
    }
    pHelper2->pNext->pPrev = pHelper2;
    pHelper2 = pHelper2->pNext;
    printf("Kapitel:");
    fgets(bufferN, N, stdin);
    strcpy(pHelper2->Kapitel, bufferN);
    printf("Typ:");
    fgets(bufferN, N, stdin);
    strcpy(pHelper2->Typ, bufferN);
    printf("Begriff:");
    fgets(bufferN, N, stdin);
    strcpy(pHelper2->Begriff, bufferN);
    printf("Inhalt:");
    fgets(bufferM, M, stdin);
    strcpy(pHelper2->Inhalt, bufferM);
    pHelper2->pNext = NULL;
    // pHelper2->pNext->pPrev = pHelper2;
    while(pHelper2->pPrev != NULL){
      pHelper2 = pHelper2->pPrev;
    }
    *pAnfang = pHelper2;
  }
}

// PRINT To KONSOLE (auskommentiert) und IN ma2tex.txt
  void pr2co_file(ma2tex* pAnfang){
    FILE *pM2f = fopen("ma2tex.txt", "a");
    ma2tex* pHelper = pAnfang;
    for(pHelper = pAnfang; pHelper != NULL; pHelper = pHelper->pNext){
      // printf("\tKapitel: %s", pHelper->Kapitel);
      fprintf(pM2f, "%s", pHelper->Kapitel);

      // printf("\tTyp: %s ", pHelper->Typ);
      fprintf(pM2f, "%s", pHelper->Typ);

      // printf("\tBegriff: %s", pHelper->Begriff);
      fprintf(pM2f, "%s", pHelper->Begriff);

      // printf("\tInhalt: %s", pHelper->Inhalt);
      fprintf(pM2f, "%s", pHelper->Inhalt);

      fprintf(pM2f, "\n");
    }
    fclose(pM2f);
  }

// FUNKTION die alles in die TEX-DATEI kopiert
  void mat2tex(ma2tex* pAnfang, FILE *pIn){
    fseek(pIn,-14L,SEEK_END);
    for(; pAnfang != NULL; pAnfang = pAnfang -> pNext){
    fprintf(pIn,"%ccardfrontfoot{%s",92,pAnfang->Kapitel);
    fseek(pIn,-1L,SEEK_CUR);
    fprintf(pIn,"}%c",10);
    fprintf(pIn,"%cbegin{flashcard}[",92);
    fputs(pAnfang->Typ, pIn);
    fseek(pIn,-1L,SEEK_CUR);
    fprintf(pIn,"%c%c",93,123);
    fputs(pAnfang->Begriff, pIn);
    fseek(pIn,-1l,SEEK_CUR);
    fprintf(pIn,"%c%c",125,10);
    fprintf(pIn,"%ccentr%c",92,10);
    fputs(pAnfang->Inhalt, pIn);
    fprintf(pIn,"%ccentr%c",92,10);
    ENDF
    ENDD
  }
  }
// MAIN
  int main(int argc, char* argv[]){

    FILE *pOut, *pIn;
    pIn = fopen(argv[1], "r+");
    ma2tex* pAnfang;

    newentry(&pAnfang);
    // pr2co_file(pAnfang);


    /*
    [ = 91
    ] = 93
    \ = 92
    { = 123
    } = 125
    */

    mat2tex(pAnfang,pIn);

    fclose(pIn);
    free(pAnfang);
    return 0;
  }
