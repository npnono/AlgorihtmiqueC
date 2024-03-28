#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

typedef struct String
{
    char* pContent;
    int iLength;
} String;

int GetLength(const char* str) {

    int length = 0;
    while (1)
    {
        if (str[length] == '\0') break;
        length++;
    }
   return length;
}

String Create(const char* str)
{
    String string;
    string.iLength = 1;

    string.iLength = GetLength(str);

    string.pContent = (char*)malloc(sizeof(char) * string.iLength);
    if (string.pContent == NULL) exit(1);
    
    for (int i = 0; i < string.iLength; i++) {
        string.pContent[i] = str[i];
    }

    return string;
}

void PrintString(const String* pStr)
{
    for (int i = 0; i < pStr->iLength; i++) {
        printf("%c", pStr->pContent[i]);
    }
    printf("\n");
}

String Concatenate1(const String* pStr1, const String* pStr2)
{
    String new_string;


    int iLength = pStr1->iLength + pStr2->iLength;
    new_string.pContent = (char*)realloc(pStr1->pContent, sizeof(char) * iLength);

    for (int i = 0; i < iLength; i++) {
        
    }
}

String Concatenate2(const char* str1, const char* str2)
{
    String string;
    string.iLength = GetLength(str1) + GetLength(str2) + 1;
    string.pContent = (char*)realloc(string.pContent, sizeof(char) * string.iLength);

    for (int i = 0; i < string.iLength; i++) {
        string.pContent[i] = str1[i];
    }
    
    for (int i = string.iLength - GetLength(str1) - 1; i < string.iLength; i++) {
        string.pContent[i] = str2[i - GetLength(str2)];
    }

    return string;
}

String SubString(const String* pStr1, int iStartIndex, int iLength)
{

}

String InsertString(const String* pStr1, const String* Pstr2, int iIndex)
{

}

int AreEquals(const String* pStr1, const String* pStr2)
{
    if (pStr1->iLength != pStr2->iLength) {
        printf("les string sont ne sont pas equals");
        return 0;
    }
    
    for (int i = 0; i <= pStr1->iLength; i++) {
        if (pStr1->pContent[i] != pStr2->pContent[i]) {
            printf("les string sont ne sont pas equals");
            break;
        }
    }
    return 1;
}

int TryCastToInt(const String* pStr, int* pResult)
{

}

void DestroyString(String* pStr)
{
    free(pStr->pContent);
}

int main() {
    String str1 = Create("Bonjour");

    PrintString(&str1);

    String str2 = Create("Aurevoir");

    PrintString(&str2);
    
    String str3 = Concatenate2("Bonjour", "Aurevoir");
    
    PrintString(&str3);

    AreEquals(&str1, &str2);

    /*String str4 = Concatenate1(&str1, &str2);

    PrintString(&str4);

    DestroyString(&str1);
    DestroyString(&str2);
    DestroyString(&str3);*/

    return 0;
}