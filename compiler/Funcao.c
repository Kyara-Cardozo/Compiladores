#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Funcao.h"

// Função para reportar um erro sintático
void errorSint(int contaLinha, char caracter[]) {
    // Imprime mensagem de erro com o caractere inválido e a linha onde o erro ocorreu
    printf("\nCaracter '%s' invalido na linha: %d\n", caracter, contaLinha);
    // Encerra o programa com código de erro
    exit(1);
}

// Função para reportar um erro léxico
void errorLex(int contaLinha, char caracter) {
    // Converte o caractere inválido para uma string
    char c_str[2];
    c_str[0] = caracter;
    c_str[1] = '\0';
    // Imprime mensagem de erro com o caractere inválido e a linha onde o erro ocorreu
    printf("\nCaracter '%s' invalido na linha: %d\n", c_str, contaLinha);
    // Encerra o programa com código de erro
    exit(1);
}

// Variável global para armazenar a indentação atual
char TABS[256] = "";

// Função para imprimir informações de um nodo
void PrintNodo(char info[], int movim) {
    // Se o movimento for AVANCA, imprime a informação e adiciona uma tabulação
    if (movim == AVANCA) {
        printf("%s%s\n", TABS, info);
        strcat(TABS, "\t");
    }
    // Se o movimento for MANTEM, apenas imprime a informação com a tabulação atual
    else if (movim == MANTEM) {
        printf("%s%s\n", TABS, info);
    }
    // Se o movimento for VOLTA, remove uma tabulação
    else if (movim == VOLTA) {
        TABS[strlen(TABS) - 1] = '\0';
    }
}

// Função para imprimir valores inteiros de um nodo
void PrintNodoInt(int val, int movim) {
    // Se o movimento for AVANCA, imprime o valor e adiciona uma tabulação
    if (movim == AVANCA) {
        printf("%s%d\n", TABS, val);
        strcat(TABS, "\t");
    }
    // Se o movimento for MANTEM, apenas imprime o valor com a tabulação atual
    else if (movim == MANTEM) {
        printf("%s%d\n", TABS, val);
    }
    // Se o movimento for VOLTA, remove uma tabulação
    else if (movim == VOLTA) {
        TABS[strlen(TABS) - 1] = '\0';
    }
}
