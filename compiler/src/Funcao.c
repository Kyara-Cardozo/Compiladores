#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compiler/src/Funcao.h"

void errorSint(int contaLinha, char caracter[])
{
    printf("\nCaracter '%s' invalido na linha: %d\n", caracter, contaLinha);
    exit(1);
}

void errorLex(int contaLinha, char caracter)
{
    char c_str[2];
    c_str[0] = caracter;
    c_str[1] = '\0';
    printf("\nCaracter '%s' invalido na linha: %d\n", c_str, contaLinha);
    exit(1);
}

void PrintNodo(char info[], int movim)
{

    if (movim == AVANCA)
    {
        printf("%s%s\n", TABS, info);
        strcat(TABS, "\t");
    }
    else if (movim == MANTEM)
    {
        printf("%s%s\n", TABS, info);
    }
    else if (movim == RETROCEDE)
    {
        TABS[strlen(TABS) - 1] = '\0';
    }
}

void PrintNodoInt(int val, int movim)
{

    if (movim == AVANCA)
    {
        printf("%s%d\n", TABS, val);
        strcat(TABS, "\t");
    }
    else if (movim == MANTEM)
    {
        printf("%s%d\n", TABS, val);
    }
    else if (movim == RETROCEDE)
    {
        TABS[strlen(TABS) - 1] = '\0';
    }
}