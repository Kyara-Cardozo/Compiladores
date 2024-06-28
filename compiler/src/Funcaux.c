#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Analisador Lexico/Analex.h"
#include "Funcaux.h"

TOKEN t;
TOKEN tkLA;
int ContadorLinha;
char Tabulacao[200];

void exibirErro(char msg[]) {
    printf("LINHA %d: %s\n", ContadorLinha, msg);
    exit(1);
}

void PrintarNo(char info[], int mover) {
    if (mover == A_FRENTE) {
        printf("%s%s\n", Tabulacao, info);
        strcat(Tabulacao, "\t");
    } else if (mover == PERMANECER) {
        printf("%s%s\n", Tabulacao, info);
    } else if (mover == PARA_TRAS) {
        Tabulacao[strlen(Tabulacao) - 1] = '\0';
    }
}

void PrintarNoInteiro(int valor, int mover) {
    if (mover == A_FRENTE) {
        printf("%s%d\n", Tabulacao, valor);
        strcat(Tabulacao, "\t");
    } else if (mover == PERMANECER) {
        printf("%s%d\n", Tabulacao, valor);
    } else if (mover == PARA_TRAS) {
        Tabulacao[strlen(Tabulacao) - 1] = '\0';
    }
}

void ChecarToken() {
    printf("CHECK LINHA %d: ", ContadorLinha);
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
        case CONSTANTE_INT: printf("<CONSTANTE_INT, %d> ", t.intVal); break;
        case CONSTANTE_REAL: printf("<CONSTANTE_REAL, %f> ", t.realVal); break;
        case CONSTANTE_CHAR: printf("<CONSTANTE_CHAR, %c> ", t.charVal); break;
        case CONSTANTE_STRING: printf("<CONSTANTE_STRING, %s> ", t.string); break;
        case COMENTARIO: printf("<COMENTARIO, %s> ", t.comment); break;
        case FIM_EXPRESSAO: printf("<FIM_EXPRESSAO, %d>\n", 0);
                    printf("LINHA %d: ", ContadorLinha);
                    break;
        case FIM_ARQUIVO: printf(" <FIM DO ARQUIVO>\n"); break;
    }

    switch (tkLA.cat) {
        case ID: 
            printf(" <LA_ID, %s> ", tkLA.lexema);
            break;
        case PALAVRA_RESERVADA:
            printf(" <LA_RES_WORD, %s> ", tkLA.lexema);
            break;
        case SIMBOLO:
            switch (tkLA.sy_code) {
                case ATRIBUICAO: printf(" <LA_SYMBOL, ATRIBUICAO> "); break;
                case ADICAO: printf(" <LA_SYMBOL, ADICAO> "); break;
                case SUBTRACAO: printf(" <LA_SYMBOL, SUBTRACAO> "); break;
                case MULTIPLICACAO: printf(" <LA_SYMBOL, MULTIPLICACAO> "); break;
                case DIVISAO: printf(" <LA_SYMBOL, DIVISAO> "); break;
                case ENDERECO: printf(" <LA_SYMBOL, ENDERECO> "); break;
                case IGUAL: printf(" <LA_SYMBOL, IGUAL> "); break;
                case MAIOR_QUE: printf(" <LA_SYMBOL, MAIOR_QUE> "); break;
                case MENOR: printf(" <LA_SYMBOL, MENOR> "); break;
                case MAIOR_IGUAL: printf(" <LA_SYMBOL, MAIOR_IGUAL> "); break;
                case MENOR_IGUAL: printf(" <LA_SYMBOL, MENOR_IGUAL> "); break;
                case DIFERENTE: printf(" <LA_SYMBOL, DIFERENTE> "); break;
                case OPERADOR_E: printf(" <LA_SYMBOL, OPERADOR_E> "); break;
                case OPERADOR_OU: printf(" <LA_SYMBOL, OPERADOR_OU> "); break;
                case OPERADOR_NEGACAO: printf(" <LA_SYMBOL, OPERADOR_NEGACAO> "); break;
                case ABRE_PARENTESE: printf(" <LA_SYMBOL, ABRE_PARENTESE> "); break;
                case FECHA_PARENTESE: printf(" <LA_SYMBOL, FECHA_PARENTESE> "); break;
                case ABRE_COLCHETE: printf(" <LA_SYMBOL, ABRE_COLCHETE> "); break;
                case FECHA_COLCHETE: printf(" <LA_SYMBOL, FECHA_COLCHETE> "); break;
                case ABRE_CHAVE: printf(" <LA_SYMBOL, ABRE_CHAVE> "); break;
                case FECHA_CHAVE: printf(" <LA_SYMBOL, FECHA_CHAVE> "); break;
            }
            break;
        case CONSTANTE_INT: printf(" <LA_CONST_INT, %d> ", tkLA.intVal); break;
        case CONSTANTE_REAL: printf(" <LA_CONST_REAL, %f> ", tkLA.realVal); break;
        case CONSTANTE_CHAR: printf(" <LA_CONST_CHAR, %c> ", tkLA.charVal); break;
        case CONSTANTE_STRING: printf(" <LA_CONST_STR, %s> ", tkLA.string); break;
        case COMENTARIO: printf(" <LA_COMMENT, %s> ", tkLA.comment); break;
        case FIM_EXPRESSAO: printf(" <LA_END_OF_EXP, %d>\n", 0);
                    printf("LINHA %d: ", ContadorLinha);
                    break;
        case FIM_ARQUIVO: printf("  <Fim do arquivo>\n"); break;
    }
}

