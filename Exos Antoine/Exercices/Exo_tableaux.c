/*#include <stdio.h>
#include <stdlib.h>

typedef struct IntArray {
    int* pContent; // Contenu de ton tableau (valeurs)

    int iSize; // Nombre d'éléments contenus dans le tableau
    int iCapacity; // Nombre d'espaces mémoires alloués
} IntArray;

void Init(IntArray* pIntArray) {
    pIntArray->iSize = 0;
    pIntArray->iCapacity = 1;
    pIntArray->pContent = (int*) malloc(sizeof(int) * pIntArray->iCapacity);
    if (pIntArray->pContent == NULL) exit(1);
}

void Add(IntArray* pIntArray, int iValue) {
    
    pIntArray->iCapacity++;
    pIntArray->pContent = (int*)realloc(pIntArray->pContent, sizeof(int) * pIntArray->iCapacity);
    pIntArray->pContent[pIntArray->iSize] = iValue;

    pIntArray->iSize++;
}

void Insert(IntArray* pIntArray, int iValue, int iIndex) {
    if (iIndex < 0 || iIndex > pIntArray->iSize) exit(1);

    
    pIntArray->iCapacity++;
    pIntArray->pContent = (int*)realloc(pIntArray->pContent, sizeof(int) * pIntArray->iCapacity);
    
    for (int i = pIntArray->iSize; i >= iIndex; i--)
        pIntArray->pContent[i + 1] = pIntArray->pContent[i];

    pIntArray->pContent[iIndex] = iValue;
    pIntArray->iSize++;
}

void Remove(IntArray* pIntArray, int iIndex) {
    if (iIndex < 0 || iIndex > pIntArray->iSize - 1) exit(1);

    pIntArray->iCapacity--;
    pIntArray->pContent = (int*)realloc(pIntArray->pContent, sizeof(int) * pIntArray->iCapacity);

    for (int i = iIndex; i < pIntArray->iSize; i++)
        pIntArray->pContent[i] = pIntArray->pContent[i + 1];
    
    pIntArray->iSize--;
}

int Get(IntArray* pIntArray, int iIndex) {
    if (iIndex < 0 || iIndex > pIntArray->iSize - 1) exit(1);

    printf("[%d] => %d\n",iIndex, pIntArray->pContent[iIndex]);

    return pIntArray->pContent[iIndex];
}

void Print(IntArray* pIntArray) {
    for (int i = 0; i < pIntArray->iSize; i++)
        printf("[%d] => %d\n", i, pIntArray->pContent[i]);
}

void Destroy(IntArray* pIntArray) {
    free(pIntArray->pContent);
}


int main() {
    IntArray oArray;

    printf("J'initialise\n");
    Init(&oArray);
    Print(&oArray);

    printf("J'ajoute\n");
    Add(&oArray, 2);
    Print(&oArray);

    printf("J'insère\n");
    Insert(&oArray, 3, 0);
    Print(&oArray);

    printf("Je remove\n");
    Remove(&oArray, 1);
    Print(&oArray);

    printf("Je get\n");
    Get(&oArray, 0);

    printf("Je destroye");
    Destroy(&oArray);

    return 0;
}*/