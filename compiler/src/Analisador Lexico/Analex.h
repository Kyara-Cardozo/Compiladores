#include <stdio.h>

// Protege a inclusão múltipla do cabeçalho
#ifndef ANALEX_H
#define ANALEX_H

// Define o tamanho máximo do lexema
#define TAM_MAX_LEXEMA 31

// Define os diferentes tipos de categorias de tokens
enum TOKEN_CAT
{
    ID = 1,      // Identificador
    PAL_RESERV,  // Palavra reservada
    SINAL,       // Sinal
    CONST_CHAR,  // Constante de caractere
    CONST_FLOAT, // Constante de ponto flutuante
    CONST_INT,   // Constante inteira
    ID_CONST,    // Identificador de constante
    LITERAL,     // Literal
    OP_ARIT,     // Operador aritmético
    OP_LOGIC,    // Operador lógico
    OP_RELAC,    // Operador relacional
    FIM_EXPR,    // Fim da expressão
    FIM_ARQ      // Fim do arquivo
};

// Define os diferentes tipos de palavras reservadas
enum PAL_RESERV
{
    MAIN = 1,
    PUTCHAR,
    GETREAL,
    ENDBLOCK,
    IF,
    CONST,
    VARYING,
    GOBACK,
    BLOCK,
    GETCHAR,
    CHAR,
    TO,
    FOR,
    ELSE,
    DOWNTO,
    PUTREAL,
    ELSEIF,
    ENDIF,
    GETINT,
    PUTINT,
    REAL,
    DO,
    ENDWHILE,
    WITH,
    FROM,
    BOOL,
    WHILE,
    INT
};

// Define os diferentes tipos de sinais
enum SINAIS
{
    ABREPAR = 1,   // (
    ABRECOL,       // [
    ABRECHAVE,     // {
    REFERENCIA,    // &
    VIRGULA,       // ,
    FECHAPAR,      // )
    FECHACOL,      // ]
    FECHACHAVE     // }
};

// Define os diferentes tipos de operadores aritméticos
enum OP_ARIT
{
    ATRIBUICAO = 1, // =
    ADICAO,         // +
    SUBTRACAO,      // -
    MULTIPLICACAO,  // *
    DIVISAO         // /
};

// Define os diferentes tipos de operadores relacionais
enum OP_RELAC
{
    IGUALDADE = 1, // ==
    DIFERENTE,     // !=
    MENOR_IGUAL,   // <=
    MAIOR_IGUAL,   // >=
    MENOR,         // <
    MAIOR          // >
};

// Define os diferentes tipos de operadores lógicos
enum OP_LOGIC
{
    AND_LOGIC = 1, // &&
    OR_LOGIC,      // ||
    NOT_LOGIC      // !
};

// Define a estrutura do token
typedef struct
{
    enum TOKEN_CAT cat; // Categoria do token
    union
    {
        int codigo;                  // Código do token
        int indice;                  // Índice do token
        char lexema[TAM_MAX_LEXEMA]; // Lexema do token
        int valInt;                  // Valor inteiro do token
        float valFloat;              // Valor de ponto flutuante do token
        char caractere;              // Caractere do token
    };
} TOKEN;

// Declaração de variáveis externas
extern TOKEN tk;
extern FILE *fd;

// Declaração da função de análise léxica
TOKEN AnaLex(FILE *);

#endif
