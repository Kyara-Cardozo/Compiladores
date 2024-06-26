#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "AnaSint.c"
#include "FuncAux.c"
#include "AnaSint.h"
#include "FuncAux.h"

FILE *fd;
TOKEN tk;
char TABS[200] = "";

void Analisador_sintatico()
{
    fd = fopen("teste.dbk", "r");
    prog();
    printf("<Resultado> Expressao OK!\n");
    fclose(fd);
}

int main()
{

    printf("[========== Analise Sintatica ==========]\n");
    Analisador_sintatico();

    return 0;
}