#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
//#include "Analex.c"
//#include "Funcao.c"
#include "AnaSint.h"
#include "Funcao.h"
//#include "Processandotokens.c"
#include "Processandotokens.h"

FILE *fd; 
TOKEN tk;

char Tabulacao[200] = "";

void Analisador_lexico(FILE *fd)
{
    printf("\n[.......... Inicio da Analise Lexica ..........]\n");
    processador_tokens(fd);
    printf("\n[..........Fim da Analise Lexica ..........]\n");
}

void Analisador_sintatico()
{
    // Iniciar_tabela();
    printf("\n[.......... Inicio da Analise Lexica ..........]\n");
    program();
    printf("\n[.......... Fim da Analise Lexica ..........]\n");
}

int main()
{

    fd = fopen("teste.dbk", "r");

    if (fd == NULL)
    {
        fprintf(stderr, "\nError ao abrir o arquivo.\n");
        return 1;
    }

    // Analisador_lexico(fd);
    Analisador_sintatico();

    fclose(fd);

    return 0;
}