#include <stdio.h>
#include <stdlib.h>

typedef struct String {
    char* pContent;

    int iLength;
} String;

int GetLength(const char* str) {
    int i;
    for (i = 0; str[i] != '\0'; i++) {
    }
    return i;
}

String Create(const char* str) {
    String string;
    string.iLength = 1;
    string.iLength += GetLength(str);
    string.pContent = (char*)malloc(string.iLength * sizeof(char));
    if (string.pContent != NULL) {
        strcpy(string.pContent, str);
    }
    return string;
}

void PrintString(const String* pStr) {
    for (int i = 0; i < (pStr->iLength); i++) {
        printf("%c ", pStr->pContent[i]);
    }
    printf("\n\n");
}


String Concatenate1(const String* pStr1, const String* pStr2)
{
    
}

String Concatenate2(const char* str1, const char* str2)
{
    String string;

    string.iLength = GetLength(str1) + GetLength(str2);
    string.iLength++;

    string.pContent = (char*)realloc(string.pContent, sizeof(char) * string.iLength);

    int count = 0;

    for (int i = 0; i < GetLength(str1); i++) {

        string.pContent[i] = str1[i];

        count++;
    }

    for (int i = 0; i < GetLength(str2); i++) {

        string.pContent[count] = str2[i];

        count++;
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
    String string;
    for(int i = 0; i < string.iLength; i++)*
        if(i)
}

int TryCastToInt(const String* pStr, int* pResult)
{

}

void DestroyString(String* pStr)
{

}

int main() {
    String str1 = Create("Bonjour");
    PrintString(&str1);

    String str2 = Create("Aurevoir");
    PrintString(&str2);

    String str3 = Concatenate2("Bonjour", "Aurevoir");
    PrintString(&str3);

    return 0;
}