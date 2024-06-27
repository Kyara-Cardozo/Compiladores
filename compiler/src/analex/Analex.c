#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Analex.h"

// Define os tamanhos máximos para lexemas, strings e números
#define TAMANHO_LEXEMA 50
#define TAMANHO_STRING 100
#define TAMANHO_NUMERO 20

// Função principal de análise léxica
TOKEN AnaliseLexica(FILE *fd, bool pular_fim_expressao) {
    static bool primeiraVez = true;  // Variável estática para controlar a primeira chamada
    bool pular = true;
    if (!pular_fim_expressao) pular = false;

    TOKEN tk;

    if (primeiraVez) {
        primeiraVez = false;
        tk = AnalexTLA(fd, pular);
        if (tk.cat == FIM_ARQUIVO)
            tkLA = tk;
        else
            tkLA = AnalexTLA(fd, pular);
        return tk;
    } else if (tkLA.cat == FIM_ARQUIVO) {
        return (tkLA);
    } else {
        tk = tkLA;
        tkLA = AnalexTLA(fd, pular);
        return tk;
    }
}

// Função auxiliar para análise de tokens
TOKEN AnalexTLA(FILE *fd, bool pular_fim_expressao) {
    int estado;

    // Declaração e inicialização de variáveis auxiliares
    char lexema[TAMANHO_LEXEMA] = "";
    int tamanhoL = 0;

    char digits[TAMANHO_NUMERO] = "";
    int tamanhoD = 0;

    char string[TAMANHO_STRING] = "";
    int sizeS = 0;

    char constChar;

    estado = 0;
    t.processado = false;
    while (true) {
        char c = fgetc(fd);  // Lê um caractere do arquivo
        switch (estado) {
            case 0:
                // Transições de estado com base no caractere lido
                if (c == ' ' || c == '\t')
                    estado = 0;
                else if (c == '\n' && pular_fim_expressao) {
                    estado = 0;
                    ContadorLinha++;
                } else if (c == '\"') {
                    estado = 34;
                } else if (c >= '0' && c <= '9') {
                    estado = 1;
                    digits[tamanhoD] = c;
                    digits[++tamanhoD] = '\0';
                } else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
                    estado = 5;
                    lexema[tamanhoL] = c;
                    lexema[++tamanhoL] = '\0';
                } else if (c == '_') {
                    estado = 6;
                    lexema[tamanhoL] = c;
                    lexema[++tamanhoL] = '\0';
                } else if (c == '|') {
                    estado = 25;
                } else if (c == '&') {
                    estado = 18;
                } else if (c == '>') {
                    estado = 22;
                } else if (c == '=') {
                    estado = 23;
                } else if (c == '<') {
                    estado = 20;
                } else if (c == '!') {
                    estado = 17;
                } else if (c == '/') {
                    estado = 8;
                } else if (c == '*') {
                    estado = 7;
                    t.cat = SIMBOLO;
                    t.sy_code = MULTIPLICACAO;
                    return t;
                } else if (c == '+') {
                    estado = 9;
                    t.cat = SIMBOLO;
                    t.sy_code = ADICAO;
                    return t;
                } else if (c == '-') {
                    estado = 10;
                    t.cat = SIMBOLO;
                    t.sy_code = SUBTRACAO;
                    return t;
                } else if (c == '(') {
                    estado = 11;
                    t.cat = SIMBOLO;
                    t.sy_code = ABRE_PARENTESE;
                    return t;
                } else if (c == ')') {
                    estado = 12;
                    t.cat = SIMBOLO;
                    t.sy_code = FECHA_PARENTESE;
                    return t;
                } else if (c == '[') {
                    estado = 13;
                    t.cat = SIMBOLO;
                    t.sy_code = ABRE_COLCHETE;
                    return t;
                } else if (c == ']') {
                    estado = 14;
                    t.cat = SIMBOLO;
                    t.sy_code = FECHA_COLCHETE;
                    return t;
                } else if (c == '{') {
                    estado = 15;
                    t.cat = SIMBOLO;
                    t.sy_code = ABRE_CHAVE;
                    return t;
                } else if (c == '}') {
                    estado = 16;
                    t.cat = SIMBOLO;
                    t.sy_code = FECHA_CHAVE;
                    return t;
                } else if (c == '\'') {
                    estado = 30;
                } else if (c == ',') {
                    estado = 50;
                    t.cat = SIMBOLO;
                    t.sy_code = VIRGULA;
                    return t;
                } else if (c == '.') {
                    estado = 51;
                    t.cat = SIMBOLO;
                    t.sy_code = PERIOD;
                    return t;
                } else if (c == ':') {
                    estado = 52;
                    t.cat = SIMBOLO;
                    t.sy_code = DOIS_PONTOS;
                    return t;
                } else if (c == ';') {
                    estado = 53;
                    t.cat = SIMBOLO;
                    t.sy_code = PONTO_VIRGULA;
                    return t;
                } else if (c == '\n') {
                    estado = 0;
                    t.cat = FIM_EXPRESSAO;
                    ContadorLinha++;
                    return t;
                } else if (c == EOF) {
                    t.cat = FIM_ARQUIVO;
                    return t;
                } else {
                    printf("Caractere invalido no ESTADO 0!");
                    exit(1);
                }
                break;
            case 34:
                if (isprint(c) != 0) {
                    estado = 35;
                    string[sizeS] = c;
                    string[++sizeS] = '\0';
                } else {
                    printf("Caractere invalido no ESTADO 34!");
                    exit(1);
                }
                break;
            case 35:
                if (isprint(c) != 0 && c != '\n' && c != '\"') {
                    estado = 35;
                    string[sizeS] = c;
                    string[++sizeS] = '\0';
                } else if (c == '\n') {
                    estado = 35;
                } else if (c == '\"') {
                    estado = 36;
                    t.cat = CONSTANTE_STRING;
                    strcpy(t.string, string);
                    return t;
                } else {
                    printf("Caractere invalido no ESTADO 35!");
                    exit(1);
                }
                break;
            case 1:
                if (c == '.') {
                    estado = 3;
                    digits[tamanhoD] = c;
                    digits[++tamanhoD] = '\0';
                } else if (c >= '0' && c <= '9') {
                    estado = 1;
                    digits[tamanhoD] = c;
                    digits[++tamanhoD] = '\0';
                } else {
                    estado = 38;
                    ungetc(c, fd);
                    t.cat = CONSTANTE_INT;
                    t.intVal = atoi(digits);
                    return t;
                }
                break;
            case 3:
                if (c >= '0' && c <= '9') {
                    estado = 4;
                    digits[tamanhoD] = c;
                    digits[++tamanhoD] = '\0';
                } else {
                    printf("Caractere invalido no ESTADO 3!");
                    exit(1);
                }
                break;
            case 4:
                if (c >= '0' && c <= '9') {
                    estado = 4;
                    digits[tamanhoD] = c;
                    digits[++tamanhoD] = '\0';
                } else {
                    estado = 37;
                    ungetc(c, fd);
                    t.cat = CONSTANTE_REAL;
                    t.realVal = atof(digits);
                    return t;
                }
                break;
            case 5:
                if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_') {
                    estado = 5;
                    lexema[tamanhoL] = c;
                    lexema[++tamanhoL] = '\0';
                } else {
                    estado = 2;
                    ungetc(c, fd);
                    t.cat = ID;
                    strcpy(t.lexema, lexema);

                    // Verifica se o lexema é uma palavra reservada
                    if ((strcmp(t.lexema, "const") == 0) || (strcmp(t.lexema, "char") == 0) || (strcmp(t.lexema, "int") == 0) ||
                        (strcmp(t.lexema, "float") == 0) || (strcmp(t.lexema, "break") == 0) || (strcmp(t.lexema, "case") == 0) ||
                        (strcmp(t.lexema, "continue") == 0) || (strcmp(t.lexema, "default") == 0) || (strcmp(t.lexema, "else") == 0) ||
                        (strcmp(t.lexema, "for") == 0) || (strcmp(t.lexema, "if") == 0) || (strcmp(t.lexema, "return") == 0) ||
                        (strcmp(t.lexema, "sizeof") == 0) || (strcmp(t.lexema, "struct") == 0) || (strcmp(t.lexema, "switch") == 0) ||
                        (strcmp(t.lexema, "void") == 0) || (strcmp(t.lexema, "while") == 0) || (strcmp(t.lexema, "print") == 0) ||
                        (strcmp(t.lexema, "scan") == 0)) {
                        t.cat = RESERVADO;
                    }
                    return t;
                }
                break;
            case 6:
                if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_') {
                    estado = 5;
                    lexema[tamanhoL] = c;
                    lexema[++tamanhoL] = '\0';
                } else {
                    printf("Caractere invalido no ESTADO 6!");
                    exit(1);
                }
                break;
            case 7:
                printf("Estado 7 alcancado!");
                exit(1);
                break;
            case 8:
                if (c == '*') {
                    estado = 41;
                } else if (c == '/') {
                    estado = 40;
                } else {
                    estado = 43;
                    ungetc(c, fd);
                    t.cat = SIMBOLO;
                    t.sy_code = DIVISAO;
                    return t;
                }
                break;
            case 9:
                printf("Estado 9 alcancado!");
                exit(1);
                break;
            case 10:
                printf("Estado 10 alcancado!");
                exit(1);
                break;
            case 11:
                printf("Estado 11 alcancado!");
                exit(1);
                break;
            case 12:
                printf("Estado 12 alcancado!");
                exit(1);
                break;
            case 13:
                printf("Estado 13 alcancado!");
                exit(1);
                break;
            case 14:
                printf("Estado 14 alcancado!");
                exit(1);
                break;
            case 15:
                printf("Estado 15 alcancado!");
                exit(1);
                break;
            case 16:
                printf("Estado 16 alcancado!");
                exit(1);
                break;
            case 17:
                if (c == '=') {
                    estado = 45;
                    t.cat = SIMBOLO;
                    t.sy_code = DIFERENTE;
                    return t;
                } else {
                    estado = 44;
                    ungetc(c, fd);
                    t.cat = SIMBOLO;
                    t.sy_code = NEGACAO;
                    return t;
                }
                break;
            case 18:
                if (c == '&') {
                    estado = 47;
                    t.cat = SIMBOLO;
                    t.sy_code = E_LOGICO;
                    return t;
                } else {
                    printf("Caractere invalido no ESTADO 18!");
                    exit(1);
                }
                break;
            case 20:
                if (c == '=') {
                    estado = 48;
                    t.cat = SIMBOLO;
                    t.sy_code = MENOR_IGUAL;
                    return t;
                } else {
                    estado = 49;
                    ungetc(c, fd);
                    t.cat = SIMBOLO;
                    t.sy_code = MENOR;
                    return t;
                }
                break;
            case 22:
                if (c == '=') {
                    estado = 48;
                    t.cat = SIMBOLO;
                    t.sy_code = MAIOR_IGUAL;
                    return t;
                } else {
                    estado = 49;
                    ungetc(c, fd);
                    t.cat = SIMBOLO;
                    t.sy_code = MAIOR;
                    return t;
                }
                break;
            case 23:
                if (c == '=') {
                    estado = 48;
                    t.cat = SIMBOLO;
                    t.sy_code = IGUAL;
                    return t;
                } else {
                    estado = 44;
                    ungetc(c, fd);
                    t.cat = SIMBOLO;
                    t.sy_code = ATRIBUICAO;
                    return t;
                }
                break;
            case 25:
                if (c == '|') {
                    estado = 46;
                    t.cat = SIMBOLO;
                    t.sy_code = OU_LOGICO;
                    return t;
                } else {
                    printf("Caractere invalido no ESTADO 25!");
                    exit(1);
                }
                break;
            case 30:
                if (isprint(c) != 0) {
                    estado = 31;
                    constChar = c;
                } else {
                    printf("Caractere invalido no ESTADO 30!");
                    exit(1);
                }
                break;
            case 31:
                if (c == '\'') {
                    estado = 32;
                    t.cat = CONSTANTE_CHAR;
                    t.charVal = constChar;
                    return t;
                } else {
                    printf("Caractere invalido no ESTADO 31!");
                    exit(1);
                }
                break;
            case 32:
                printf("Estado 32 alcancado!");
                exit(1);
                break;
            case 37:
                printf("Estado 37 alcancado!");
                exit(1);
                break;
            case 38:
                printf("Estado 38 alcancado!");
                exit(1);
                break;
            case 40:
                if (c == '\n') {
                    estado = 0;
                    ContadorLinha++;
                } else if (isprint(c) != 0) {
                    estado = 40;
                } else {
                    printf("Caractere invalido no ESTADO 40!");
                    exit(1);
                }
                break;
            case 41:
                if (c == '*') {
                    estado = 42;
                } else if (isprint(c) != 0) {
                    estado = 41;
                } else if (c == '\n') {
                    estado = 41;
                    ContadorLinha++;
                } else {
                    printf("Caractere invalido no ESTADO 41!");
                    exit(1);
                }
                break;
            case 42:
                if (c == '/') {
                    estado = 0;
                } else if (c == '*') {
                    estado = 42;
                } else if (isprint(c) != 0) {
                    estado = 41;
                } else if (c == '\n') {
                    estado = 41;
                    ContadorLinha++;
                } else {
                    printf("Caractere invalido no ESTADO 42!");
                    exit(1);
                }
                break;
            case 43:
                printf("Estado 43 alcancado!");
                exit(1);
                break;
            case 44:
                printf("Estado 44 alcancado!");
                exit(1);
                break;
            case 45:
                printf("Estado 45 alcancado!");
                exit(1);
                break;
            case 46:
                printf("Estado 46 alcancado!");
                exit(1);
                break;
            case 47:
                printf("Estado 47 alcancado!");
                exit(1);
                break;
            case 48:
                printf("Estado 48 alcancado!");
                exit(1);
                break;
            case 49:
                printf("Estado 49 alcancado!");
                exit(1);
                break;
            case 50:
                printf("Estado 50 alcancado!");
                exit(1);
                break;
            case 51:
                printf("Estado 51 alcancado!");
                exit(1);
                break;
            case 52:
                printf("Estado 52 alcancado!");
                exit(1);
                break;
            case 53:
                printf("Estado 53 alcancado!");
                exit(1);
                break;
            default:
                printf("Estado invalido!");
                exit(1);
                break;
        }
    }
}
