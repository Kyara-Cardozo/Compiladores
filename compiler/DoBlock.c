#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "compiler/src/Analisador Lexico/Analex.c"
#include "compiler/src/Funcao.c"
#include "compiler/src/Analisador Sintatico/AnaSint.h"
#include "compiler/src/Funcao.h"
#include "compiler/Processandotokens.c"

FILE *fd;
TOKEN tk;

char TABS[200] = "";

void Analisador_lexico(FILE *fd)
{
    printf("\n[.......... INICIO - Analise lexica ..........]\n");
    processador_tokens(fd);
    printf("\n[..........FIM - Analise lexica ..........]\n");
}

void Analisador_sintatico()
{
    // Iniciar_tabela();
    printf("\n[.......... INICIO - Analise sintatica ..........]\n");
    prog();
    printf("\n[.......... FIM - Analise sintatica ..........]\n");
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