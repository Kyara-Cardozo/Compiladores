#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "src/analex/Analex.h"
#include "src/analex/Analex.c"
#include "src/anasynt/Anasynt.h"
#include "src/anasynt/Anasynt.c"
#include "src/Funcaux.h"
#include "src/Funcaux.c"
#include "src/tabelaId.h"
#include "src/tabelaId.c"

FILE *fd;
TOKEN t;
TOKEN tkLA;
TABELA_ID tabelaId;
int ContadorLinha;
bool bExibirArvore;
char Tabulacao[200];

void ExecutarAnalisadorLexico() {
    fd = fopen("/Users/kyaracardozo/Compiladores/compiler/expression.txt", "r");
    if (fd == NULL) {
        printf("Arquivo não encontrado!\n");
        return;
    }

    printf("LINHA %d: ", ContadorLinha);
    while (true) {
        t = AnaliseLexica(fd, false);
        switch (t.cat) {
            case ID:
                printf("<ID, %s> ", t.lexema);
                break;
            case PALAVRA_RESERVADA:
                printf("<PALAVRA_RESERVADA, %s> ", t.lexema);
                break;
            case SIMBOLO:
                switch (t.sy_code) {
                    case ATRIBUICAO: printf("<SIMBOLO, ATRIBUICAO> "); break;
                    case ADICAO: printf("<SIMBOLO, ADICAO> "); break;
                    case SUBTRACAO: printf("<SIMBOLO, SUBTRACAO> "); break;
                    case MULTIPLICACAO: printf("<SIMBOLO, MULTIPLICACAO> "); break;
                    case DIVISAO: printf("<SIMBOLO, DIVISAO> "); break;
                    case ENDERECO: printf("<SIMBOLO, ENDERECO> "); break;
                    case IGUAL: printf("<SIMBOLO, IGUAL> "); break;
                    case MAIOR_QUE: printf("<SIMBOLO, MAIOR_QUE> "); break;
                    case MENOR: printf("<SIMBOLO, MENOR> "); break;
                    case MAIOR_IGUAL: printf("<SIMBOLO, MAIOR_IGUAL> "); break;
                    case MENOR_IGUAL: printf("<SIMBOLO, MENOR_IGUAL> "); break;
                    case DIFERENTE: printf("<SIMBOLO, DIFERENTE> "); break;
                    case OPERADOR_E: printf("<SIMBOLO, OPERADOR_E> "); break;
                    case OPERADOR_OU: printf("<SIMBOLO, OPERADOR_OU> "); break;
                    case OPERADOR_NEGACAO: printf("<SIMBOLO, OPERADOR_NEGACAO> "); break;
                    case ABRE_PARENTESE: printf("<SIMBOLO, ABRE_PARENTESE> "); break;
                    case FECHA_PARENTESE: printf("<SIMBOLO, FECHA_PARENTESE> "); break;
                    case ABRE_COLCHETE: printf("<SIMBOLO, ABRE_COLCHETE> "); break;
                    case FECHA_COLCHETE: printf("<SIMBOLO, FECHA_COLCHETE> "); break;
                    case ABRE_CHAVE: printf("<SIMBOLO, ABRE_CHAVE> "); break;
                    case FECHA_CHAVE: printf("<SIMBOLO, FECHA_CHAVE> "); break;
                }
                break;
            case CONSTANTE_INT:
                printf("<CONSTANTE_INT, %d> ", t.intVal);
                break;
            case CONSTANTE_REAL:
                printf("<CONSTANTE_REAL, %f> ", t.realVal);
                break;
            case CONSTANTE_CHAR:
                printf("<CONSTANTE_CHAR, %c> ", t.charVal);
                break;
            case CONSTANTE_STRING:
                printf("<CONSTANTE_STRING, %s> ", t.string);
                break;
            case COMENTARIO:
                printf("<COMENTARIO, %s> ", t.comment);
                break;
            case FIM_EXPRESSAO:
                printf("<FIM_EXPRESSAO, %d>\n", 0);
                printf("LINHA %d: ", ContadorLinha);
                break;
            case FIM_ARQUIVO:
                printf(" <FIM DO ARQUIVO>\n");
                break;
        }
        if (t.cat == FIM_ARQUIVO) break;
    }
    fclose(fd);
}

void ExecutarAnaliseSintatica() {
    fd = fopen("/Users/kyaracardozo/Compiladores/compiler/expression.txt", "r");
    if (fd == NULL) {
        exibirErro("Arquivo não encontrado!");
    }

    InicializarTabelaId();

    while (true) {
        t = AnaliseLexica(fd, true);
        if (t.cat == FIM_ARQUIVO) {
            printf("\nFim do arquivo!\n");
            break;
        }
        Aplicacao();
        if (t.cat == FIM_ARQUIVO) {
            printf("\nLINHA %d: Fim de analise sintatica!!\n\n", ContadorLinha - 1);
        } else {
            exibirErro("Erro de sintaxe!");
        }
    }
    fclose(fd);
}

int main(int argc, char **argv) {
    ContadorLinha = 1;
    if (argc < 2) {
        exibirErro("Nenhum argumento passado!\n\t Use  'lexico' ou 'sintatico'!");
    } else if (strcmp(argv[1], "lexico") == 0) {
        printf("\n\n[Analise Lexica---------------]\n");
        ExecutarAnalisadorLexico();
    } else if (strcmp(argv[1], "sintatico") == 0) {
        bExibirArvore = false;
        printf("\n\n[Analise Sintatica-------------]\n");
        ExecutarAnaliseSintatica();
    } else {
        exibirErro("Argumento invalido!\n\t Use 'lexico' ou 'sintatico'!");
    }
}
