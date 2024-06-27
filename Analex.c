#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Analex.h"

#define TAMANHO_LEXEMA 50
#define TAMANHO_STRING 100
#define TAMANHO_NUMERO 20

TOKEN AnaliseLexica(FILE *fd, bool pular_fim_expressao) {
    static bool primeiraVez = true;
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

TOKEN AnalexTLA(FILE *fd, bool pular_fim_expressao) {
    int estado;

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
        char c = fgetc(fd);
        switch (estado) {
            case 0:
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

    if ((strcmp(t.lexema, "const") == 0) || (strcmp(t.lexema, "char") == 0) || (strcmp(t.lexema, "int") == 0) ||
        (strcmp(t.lexema, "float") == 0) || (strcmp(t.lexema, "real") == 0) || (strcmp(t.lexema, "bool") == 0) ||
        (strcmp(t.lexema, "true") == 0) || (strcmp(t.lexema, "false") == 0) || (strcmp(t.lexema, "block") == 0) ||
        (strcmp(t.lexema, "with") == 0) || (strcmp(t.lexema, "main") == 0) || (strcmp(t.lexema, "do") == 0) ||
        (strcmp(t.lexema, "while") == 0) || (strcmp(t.lexema, "endblock") == 0) || (strcmp(t.lexema, "varying") == 0) ||
        (strcmp(t.lexema, "from") == 0) || (strcmp(t.lexema, "to") == 0) || (strcmp(t.lexema, "downto") == 0) ||
        (strcmp(t.lexema, "for") == 0) || (strcmp(t.lexema, "times") == 0) || (strcmp(t.lexema, "if") == 0) ||
        (strcmp(t.lexema, "elseif") == 0) || (strcmp(t.lexema, "else") == 0) || (strcmp(t.lexema, "endif") == 0) ||
        (strcmp(t.lexema, "endwhile") == 0) || (strcmp(t.lexema, "goback") == 0) || (strcmp(t.lexema, "getint") == 0) ||
        (strcmp(t.lexema, "getreal") == 0) || (strcmp(t.lexema, "getchar") == 0) || (strcmp(t.lexema, "putint") == 0) ||
        (strcmp(t.lexema, "putreal") == 0) || (strcmp(t.lexema, "putchar") == 0)) {
        
        t.cat = PALAVRA_RESERVADA;
    }

    return t;
}

        break;
    case 6:
        if (c == '_') {
            estado = 6;
            lexema[tamanhoL] = c;
            lexema[++tamanhoL] = '\0';
        } else if (c >= 'a' && c <= 'z') {
            estado = 5;
            lexema[tamanhoL] = c;
            lexema[++tamanhoL] = '\0';
        } else {
            printf("Caractere invalido no ESTADO 6!");
            exit(1);
        }
        break;
    case 25:
        if (c == '|') {
            estado = 26;
            t.cat = SIMBOLO;
            t.sy_code = OPERADOR_OU;
            return t;
        } else {
            printf("Caractere invalido no ESTADO 25!");
            exit(1);
        }
        break;
    case 18:
        if (c == '&') {
            estado = 24;
            t.cat = SIMBOLO;
            t.sy_code = OPERADOR_E;
            return t;
        } else {
            estado = 39;
            ungetc(c, fd);
            t.cat = SIMBOLO;
            t.sy_code = ENDERECO;
            return t;
        }
        break;
    case 22:
        if (c == '=') {
            estado = 43;
            t.cat = SIMBOLO;
            t.sy_code = MAIOR_IGUAL;
            return t;
        } else {
            estado = 40;
            ungetc(c, fd);
            t.cat = SIMBOLO;
            t.sy_code = MAIOR_QUE;
            return t;
        }
        break;
    case 23:
        if (c == '=') {
            estado = 45;
            t.cat = SIMBOLO;
            t.sy_code = IGUAL;
            return t;
        } else {
            estado = 46;
            ungetc(c, fd);
            t.cat = SIMBOLO;
            t.sy_code = ATRIBUICAO;
            return t;
        }
        break;
    case 20:
        if (c == '=') {
            estado = 44;
            t.cat = SIMBOLO;
            t.sy_code = MENOR_IGUAL;
            return t;
        } else {
            estado = 42;
            ungetc(c, fd);
            t.cat = SIMBOLO;
            t.sy_code = MENOR;
            return t;
        }
        break;
    case 17:
        if (c == '=') {
            estado = 21;
            t.cat = SIMBOLO;
            t.sy_code = DIFERENTE;
            return t;
        } else {
            estado = 41;
            ungetc(c, fd);
            t.cat = SIMBOLO;
            t.sy_code = OPERADOR_NEGACAO;
            return t;
        }
        break;
    case 8:
        if (c == '/') {
            estado = 27;
        } else {
            estado = 19;
            ungetc(c, fd);
            t.cat = SIMBOLO;
            t.sy_code = DIVISAO;
            return t;
        }
        break;
    case 27:
        if (c == '\n') {
            estado = 28;
            t.cat = COMENTARIO;
            strcpy(t.comment, string);
            return t;
        } else {
            estado = 27;
            string[sizeS] = c;
            string[++sizeS] = '\0';
        }
        break;
    case 30:
        if (c == '\\') {
            estado = 31;
        } else if (isprint(c) != 0 && c != '\'') {
            estado = 29;
            constChar = c;
        } else {
            printf("Caractere invalido no ESTADO 30!");
            exit(1);
        }
        break;
    case 29:
        if (c == '\'') {
            estado = 47;
            t.cat = CONSTANTE_CHAR;
            t.charVal = constChar;
            return t;
        } else {
            printf("Caractere invalido no ESTADO 29!");
            exit(1);
        }
        break;
    case 31:
        if (c == 'n') {
            estado = 32;
            constChar = '\n';
        } else if (c == '0') {
            estado = 33;
            constChar = '\0';
        } else {
            printf("Caractere invalido no ESTADO 31!");
            exit(1);
        }
        break;
    case 32:
        if (c == '\'') {
            estado = 48;
            t.cat = CONSTANTE_CHAR;
            t.charVal = constChar;
            return t;
        } else {
            printf("Caractere invalido no ESTADO 32!");
            exit(1);
        }
        break;
    case 33:
        if (c == '\'') {
            estado = 49;
            t.cat = CONSTANTE_CHAR;
            t.charVal = constChar;
            return t;
        } else {
            printf("Caractere invalido no ESTADO 33!");
            exit(1);
        }
        break;
    }
  }
}

