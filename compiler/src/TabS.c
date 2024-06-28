#include "TabS.h"
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

// Função para inicializar a tabela de símbolos
void Iniciar_tabela() {
    tabela_idef.tamTab = 0; // Define o tamanho da tabela como 0, indicando que está vazia
}

// Função para imprimir a tabela de símbolos
void Imprimir_tabela() {
    // Imprime cabeçalho da tabela
    printf("\nTabela de Símbolos:\n");
    printf(".....................................................................................\n");
    printf("| %-6s | %-10s | %-10s | %-6s | %-10s | %-6s | %-8s |\n", 
           "Índice", "Lexema", "Tipo", "Escopo", "Categoria", "Zombie", "Endereço");
    printf(".....................................................................................\n");

    // Percorre a tabela e imprime cada símbolo
    for (int i = 0; i < tabela_idef.tamTab; i++) {
        printf("| %-6d | %-10s | %-10d | %-6d | %-10s | %-6d | %-8d |\n",
               i,
               tabela_idef.tabela_simb[i].lexema,
               tabela_idef.tabela_simb[i].tipo,
               tabela_idef.tabela_simb[i].escopo,
               tabela_idef.tabela_simb[i].categoria,
               tabela_idef.tabela_simb[i].zombie,
               tabela_idef.tabela_simb[i].endereco);
    }
    printf(".....................................................................................\n");
}

// Função para buscar um lexema na tabela de símbolos
int Buscar_tabela(const char lexema[]) {
    // Percorre a tabela para encontrar o lexema
    for (int i = 0; i < tabela_idef.tamTab; i++) {
        if (strcmp(tabela_idef.tabela_simb[i].lexema, lexema) == 0) {
            return i;  // Retorna o índice se encontrar o lexema
        }
    }
    return -1;  // Retorna -1 se não encontrar o lexema
}

// Função para buscar um lexema em um escopo específico
int Buscar_escopo(char lexema[], int escopo) {
    // Percorre a tabela para encontrar o lexema e o escopo
    for (int i = 0; i < tabela_idef.tamTab; i++) {
        if (strcmp(tabela_idef.tabela_simb[i].lexema, lexema) == 0 && tabela_idef.tabela_simb[i].escopo == escopo) {
            return i; // Retorna o índice se encontrar o lexema no escopo específico
        }
    }
    return -1; // Retorna -1 se não encontrar o lexema no escopo específico
}

// Função para inserir um novo símbolo na tabela de símbolos
int Insercao_tabela(char lexema[], int escopo, int tipo, char categoria[], bool zombie) {
    // Verifica se a tabela está cheia
    if (tabela_idef.tamTab >= TAM_MAX_TAB) {
        printf("[ERRO] Opa, a tabela de símbolos está cheia.\n");
        return -1;
    }

    // Verifica se o lexema já foi declarado no escopo atual
    int pos = Buscar_escopo(lexema, escopo);
    if (pos != -1) {
        printf("[ERRO] Identificador '%s' já foi declarado no escopo atual.\n", lexema);
        return -1;
    }

    // Cria um novo símbolo
    TabSimb novoSimbolo;
    strncpy(novoSimbolo.lexema, lexema, TAM_MAX_LEXEMA - 1);
    novoSimbolo.lexema[TAM_MAX_LEXEMA - 1] = '\0'; // Assegura que a string esteja terminada em null
    novoSimbolo.escopo = escopo;
    novoSimbolo.tipo = tipo;
    strncpy(novoSimbolo.categoria, categoria, TAM_CATEGORIA - 1);
    novoSimbolo.categoria[TAM_CATEGORIA - 1] = '\0'; // Assegura que a string esteja terminada em null
    novoSimbolo.zombie = zombie;
    novoSimbolo.endereco = tabela_idef.tamTab;

    // Adiciona o novo símbolo à tabela
    tabela_idef.tabela_simb[tabela_idef.tamTab++] = novoSimbolo;
    return 0;
}

// Função para remover o último símbolo inserido na tabela de símbolos
int Remover_ultimo() {
    // Verifica se há símbolos na tabela
    if (tabela_idef.tamTab > 0) {
        tabela_idef.tamTab--; // Decrementa o tamanho da tabela, efetivamente removendo o último símbolo
        return 0;
    } else {
        printf("[ERRO] Opa, a tabela de símbolos está vazia.\n");
        return -1;
    }
}
