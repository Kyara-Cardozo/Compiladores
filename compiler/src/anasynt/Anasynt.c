#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../analex/Analex.h"
#include "../Funcaux.h"
#include "../tabelaId.h"
#include "Anasynt.h"

// Variáveis globais
bool is_const; // Variável para indicar se uma declaração é de constante
int escopo; // Variável para indicar o escopo atual
enum TOKEN_CAT idCat; // Variável para armazenar a categoria do identificador

// Função principal de análise da aplicação
void Aplicacao() {
    // Processa declarações de variáveis globais
    while (t.cat == PALAVRA_RESERVADA && ((strcmp(t.lexema, "const") == 0) || (strcmp(t.lexema, "char") == 0) ||
                                 (strcmp(t.lexema, "int") == 0) || (strcmp(t.lexema, "real") == 0) ||
                                 (strcmp(t.lexema, "bool") == 0))) {
        escopo = 0; // Define o escopo como global
        Decl_list_var(); // Processa lista de declarações de variáveis
        if (t.processado)
            t = AnaliseLexica(fd, true); // Avança para o próximo token
    }

    if (t.processado)
        t = AnaliseLexica(fd, true); // Avança para o próximo token se o atual foi processado

    // Processa protótipos de blocos
    while ((t.cat == PALAVRA_RESERVADA && (strcmp(t.lexema, "block") == 0)) && tkLA.cat == ID) {
        Decl_block_prot(); // Declara protótipo de bloco
        if (t.processado)
            t = AnaliseLexica(fd, true); // Avança para o próximo token
    }

    escopo = 1; // Define o escopo como local
    Block_main(); // Processa o bloco principal

    if (t.processado)
        t = AnaliseLexica(fd, true); // Avança para o próximo token se o atual foi processado

    // Processa definições de blocos
    while (t.cat == PALAVRA_RESERVADA && (strcmp(t.lexema, "block") == 0)) {
        escopo = 2; // Define o escopo como um bloco
        Block_def(); // Processa definição de bloco
        if (t.processado)
            t = AnaliseLexica(fd, true); // Avança para o próximo token
    }
}

// Função para processar lista de declarações de variáveis
void Decl_list_var() {
    if (strcmp(t.lexema, "const") == 0) {
        is_const = true; // Define a declaração como constante
        t.processado = true;
        Tipo(); // Processa o tipo da variável
    } else {
        Tipo(); // Processa o tipo da variável
    }

    if (t.processado)
        t = AnaliseLexica(fd, true); // Avança para o próximo token

    Decl_var(); // Processa a declaração da variável

    if (t.processado)
        t = AnaliseLexica(fd, true); // Avança para o próximo token

    // Processa múltiplas declarações separadas por vírgula
    while (t.cat == SIMBOLO && t.sy_code == VIRGULA) {
        t.processado = true;
        t = AnaliseLexica(fd, true); // Avança para o próximo token
        Decl_var(); // Processa a próxima declaração de variável
        if (t.processado)
            t = AnaliseLexica(fd, true); // Avança para o próximo token
    }
    is_const = false; // Reseta a flag de constante
    escopo = 0; // Reseta o escopo
    idCat = 0; // Reseta a categoria do identificador
}

// Função para processar o tipo da variável
void Tipo() {
    if (t.processado)
        t = AnaliseLexica(fd, true); // Avança para o próximo token

    // Verifica se o token atual é um tipo válido
    if (t.cat != PALAVRA_RESERVADA || ((strcmp(t.lexema, "char") != 0) && (strcmp(t.lexema, "int") != 0) &&
                              (strcmp(t.lexema, "real") != 0) && (strcmp(t.lexema, "bool") != 0))) {
        exibirErro("Tipo faltando!"); // Exibe erro se o tipo não for válido
    } else {
        // Define a categoria do identificador com base no tipo
        if (strcmp(t.lexema, "char") == 0) {
            idCat = CONSTANTE_CHAR;
        } else if (strcmp(t.lexema, "int") == 0) {
            if (is_const) {
                idCat = ID_CONST;
            } else {
                idCat = CONSTANTE_INT;
            }
        } else if (strcmp(t.lexema, "real") == 0) {
            idCat = CONSTANTE_REAL;
        } else if (strcmp(t.lexema, "bool") == 0) {
            idCat = CONST_BOOL;
        }
        t.processado = true;
    }
}

// Função para processar declaração de variável
void Decl_var() {
    if (t.processado)
        t = AnaliseLexica(fd, true); // Avança para o próximo token

    if (t.cat != ID) {
        exibirErro("ID faltando!"); // Exibe erro se o identificador estiver faltando
    } else {
        // Insere o identificador na tabela de símbolos se ainda não existir
        if (BuscaIdTabela(t.lexema) < 0) {
            InsertIdTable(t.lexema, is_const, escopo, idCat);
        } else {
            exibirErro("ID duplicado!"); // Exibe erro se o identificador já existir
        }
        t.processado = true;
        t = AnaliseLexica(fd, true); // Avança para o próximo token
    }

    // Processa declaração de arrays
    while (t.cat == SIMBOLO && t.sy_code == ABRE_COLCHETE) {
        t.processado = true;
        t = AnaliseLexica(fd, true); // Avança para o próximo token

        if (t.cat != CONSTANTE_INT && t.cat != ID && idCat != ID_CONST) {
            exibirErro("Comprimento faltando!"); // Exibe erro se o comprimento do array estiver faltando
        } else {
            t.processado = true;
            t = AnaliseLexica(fd, true); // Avança para o próximo token
        }

        if (t.cat != SIMBOLO || t.sy_code != FECHA_COLCHETE) {
            exibirErro("Faltando colchete fechado!"); // Exibe erro se o colchete de fechamento estiver faltando
        } else {
            t.processado = true;
            t = AnaliseLexica(fd, true); // Avança para o próximo token
        }
    }

    // Processa inicialização de variável
    if (t.cat == SIMBOLO && t.sy_code == ATRIBUICAO) {
        t.processado = true;
        t = AnaliseLexica(fd, true); // Avança para o próximo token

        // Verifica se o valor inicial é válido
        if (t.cat == CONSTANTE_INT || t.cat == CONSTANTE_REAL || t.cat == CONSTANTE_CHAR || t.cat == CONSTANTE_STRING) {
            t.processado = true;
            t = AnaliseLexica(fd, true); // Avança para o próximo token
        } else if (t.cat == SIMBOLO && t.sy_code == ABRE_CHAVE) {
            t.processado = true;
            t = AnaliseLexica(fd, true); // Avança para o próximo token

            if (t.cat != CONSTANTE_INT && t.cat != CONSTANTE_REAL && t.cat != CONSTANTE_CHAR && t.cat != CONSTANTE_STRING) {
                exibirErro("Valor faltando!"); // Exibe erro se o valor inicial estiver faltando
            } else {
                t.processado = true;
                t = AnaliseLexica(fd, true); // Avança para o próximo token
            }

            // Processa múltiplos valores iniciais separados por vírgula
            while (t.cat == SIMBOLO && t.sy_code == VIRGULA) {
                t.processado = true;
                t = AnaliseLexica(fd, true); // Avança para o próximo token

                if (t.cat != CONSTANTE_INT && t.cat != CONSTANTE_REAL && t.cat != CONSTANTE_CHAR && t.cat != CONSTANTE_STRING) {
                    exibirErro("Valor após vírgula faltando!"); // Exibe erro se um valor após a vírgula estiver faltando
                } else {
                    t.processado = true;
                    t = AnaliseLexica(fd, true); // Avança para o próximo token
                }
            }

            if (t.cat != SIMBOLO || t.sy_code != FECHA_CHAVE) {
                exibirErro("Faltando chave fechada!"); // Exibe erro se a chave de fechamento estiver faltando
            } else {
                t.processado = true;
                t = AnaliseLexica(fd, true); // Avança para o próximo token
            }
        } else {
            exibirErro("Lado direito da atribuicao faltando!"); // Exibe erro se o lado direito da atribuição estiver faltando
        }
    }
}

// Função para exibir erros de análise
void exibirErro(char* msg) {
    fprintf(stderr, "Erro: %s\n", msg); // Exibe a mensagem de erro
    exit(1); // Encerra a execução do programa
}
