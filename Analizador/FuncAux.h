#ifndef FUNCAUX_H
#define FUNCAUX_H

enum MOVIM
{
    AVANCA,
    MANTEM,
    RETROCEDE
};

extern char TABS[200];

void errorLex(int contLinha, char caracter);
void errorSint(int contLinha, char caracter[]);
void PrintNodo(char info[], int movim);
void PrintNodoInt(int val, int movim);

#endif