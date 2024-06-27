#ifndef _ANALEX_
#define _ANALEX_

#include <stdio.h>
#include <stdbool.h>

#define LEXEME_MAX_SIZE 31
#define STRING_MAX_SIZE 100
#define COMMENT_MAX_SIZE 300

enum TOKEN_CAT {ID=0, PALAVRA_RESERVADA, SIMBOLO, ID_CONST, CONSTANTE_INT, CONSTANTE_REAL, CONSTANTE_CHAR, CONSTANTE_STRING, CONST_BOOL, COMENTARIO, FIM_EXPRESSAO, FIM_ARQUIVO};

enum SYMBOLS {ATRIBUICAO=0, ADICAO, SUBTRACAO, MULTIPLICACAO, DIVISAO, SINAL_POSITIVO, SINAL_NEGATIVO, ENDERECO,
                IGUAL, MAIOR_QUE, MENOR, MAIOR_IGUAL, MENOR_IGUAL, DIFERENTE, 
                OPERADOR_E, OPERADOR_OU, OPERADOR_NEGACAO, ABRE_PARENTESE, FECHA_PARENTESE, ABRE_COLCHETE, 
                FECHA_COLCHETE, ABRE_CHAVE, FECHA_CHAVE, VIRGULA,
                PERIOD, DOIS_PONTOS, PONTO_VIRGULA};

typedef struct {
    enum TOKEN_CAT cat;
    bool processado;
    union {
        int sy_code; // Operador
        char lexema[LEXEME_MAX_SIZE]; // ID | PALAVRA_RESERVADA
        int intVal; // CONSTANTE_INT
        float realVal; // CONSTANTE_REAL
        char charVal; // CONSTANTE_CHAR
        char string[STRING_MAX_SIZE]; // CONSTANTE_STRING
        char comment[COMMENT_MAX_SIZE]; // COMENTARIO
    };
} TOKEN;

extern int ContadorLinha;
extern TOKEN t;
extern TOKEN tkLA;
extern FILE *fd;

TOKEN AnalexTLA(FILE *fd, bool pular_fim_expressao);
TOKEN AnaliseLexica(FILE *fd, bool pular_fim_expressao);

#endif // _ANALEX_
