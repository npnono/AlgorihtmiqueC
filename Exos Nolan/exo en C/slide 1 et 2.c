#include <stdio.h>
#include <stdlib.h>

typedef struct IntArray {
    int* pContent; // Contenu de ton tableau (valeurs)

    int iSize; // Nombre d'éléments contenus dans le tableau
    int iCapacity; // Nombre d'espaces mémoires alloués
} IntArray;

void Init(IntArray* pIntArray) {
    pIntArray->iSize = 0;
    pIntArray->iCapacity = 1;
    pIntArray->pContent = (int*)malloc(sizeof(int) * pIntArray->iCapacity);
    if (pIntArray->pContent == NULL) exit(1);
}

void Add(IntArray* pIntArray, int iValue) {

    pIntArray->iCapacity++;
    pIntArray->pContent = (int*)realloc(pIntArray->pContent, sizeof(int)* pIntArray->iCapacity);
    pIntArray->pContent[pIntArray->iSize] = iValue;
    pIntArray->iSize++;
}

void Insert(IntArray* pIntArray, int iValue, int iIndex) {
    pIntArray->iCapacity++;
    pIntArray->pContent = (int*)realloc(pIntArray->pContent, sizeof(int)* pIntArray->iCapacity);
    if (iIndex < 0 || iIndex > pIntArray->iSize) exit(1);
    for (int i = pIntArray->iCapacity; i >= iIndex; i--) {
        pIntArray->pContent[i] = pIntArray->pContent[i - 1];
    }
    pIntArray->pContent[iIndex] = iValue;
    pIntArray->iSize++;

}

void Remove(IntArray* pIntArray, int iIndex) {
    if (iIndex < 0 || iIndex > pIntArray->iSize) exit(1);
    for (int i = iIndex; i <= pIntArray->iCapacity; i++) {
        pIntArray->pContent[i] = pIntArray->pContent[i + 1];
    }
    pIntArray->iCapacity--;
    pIntArray->pContent = (int*)realloc(pIntArray->pContent, sizeof(int) * pIntArray->iCapacity);
    pIntArray->iSize--;

}

void Get(IntArray* pIntArray, int iIndex) {

    if (iIndex < 0 || iIndex > pIntArray->iSize) exit(1);
    printf("[%d] => %d\n\n la suite \n\n ", iIndex, pIntArray->pContent[iIndex]);
}

void Print(IntArray* pIntArray) {
    for (int i = 0; i < pIntArray->iSize; i++) {
        printf("[%d] => %d \n", i, pIntArray->pContent[i]);
    }
    printf("\nla suite \n\n");
}

void Destroy(IntArray* pIntArray) {
    free(pIntArray->pContent);

}




int main() {
    IntArray oArray;
    Init(&oArray);


    Add(&oArray, 2);
    Print(&oArray);

    Insert(&oArray,5,0);
    Insert(&oArray, 15, 1);
    Print(&oArray);

    Remove(&oArray,1);
    Print(&oArray);

    Get(&oArray, 1);


    Destroy(&oArray);

    return 0;
}
