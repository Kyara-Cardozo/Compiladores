#ifndef FUNCAO_H
#define FUNCAO_H

enum MOVIM
{
    AVANCA,
    MANTEM,
    VOLTA
};


extern char TABS[200];

void errorLex(int contaLinha, char caracter);
void errorSint(int contaLinha, char caracter[]);
void PrintNodo(char info[], int movim);
void PrintNodoInt(int val, int movim);

#endif