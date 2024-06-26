#include <stdio.h>

#ifndef Analex
#define Analex
#define TAM_MAX_LEXEMA 31

// Enumeração que define as categorias possíveis para os tokens léxicos.
enum TOKEN_CAT {
  ID = 1,       // Identificador
  PR,           // Palavra reservada
  SN,           // Símbolo ou sinal
  LT,           // Cadeia de caracteres
  FIM_ARQ,      // Fim do arquivo
  FIM_EXPR,      // Fim da expressão
  CT_I,         // Constante numérica inteira
  CT_F,         // Constante numérica real
  CT_C,         // Constante caractere
  CT_NULL,      // Valor nulo
  CT_NEWLINE,   // Nova linha
  CONST_INT ,
  OP_ARIT,
  OP_LOGIC,   
  OP_RELAC
};


enum PR { // Palavras reservadas 
  MAIN = 1,
  DATA,
  CODE,
  INTERN,
  VOID,
  CHAR,
  WITH,
  INT,
  FLOAT,
  BOOL,
  IF,
  ELSE,
  WHILE,
  FOR,
  RETURN,
  DELETE,
  NEW,
  ENDBLOCK,
  BLOCK,
  VARYING,
  GETREAL,
  TO,
  DO,
  REAL,
  CONST,
  DOWNTO,
  FROM,
  ELSEIF,
  ENDIF,
  GOBACK,
  GETINT,
  GETCHAR,
  ENDWHILE,
  PUTINT,
  PUTREAL,
  PUTCHAR
};

enum SINAIS { // Sinais válidos da linguagem
  ABRE_CHAVE,
  FECHA_CHAVE,
  ABRE_COL,
  FECHA_COL,
  ABRE_PAR,
  FECHA_PAR,
  COMPARACAO,
  DESTRUTOR,
  DOISPONTOS,
  ENDERECO,
  ESCOPO,
  PONTO,
  PONTO_VIRG,
  PONTEIRO,
  VIRGULA,
  REFERENCIA,
};

enum OP_ARIT
{
  ATRIB = 1, // =
  SOMA, // +
  SUBTRACAO, // -
  DIVISAO, // /
  MULTIPLIC // *
};

enum OP_RELAC 
{
  IGUAL = 1,  // ==
  DIFERENTE, // !=
  MAIOR, // >
  MAIORIGUAL, // >=
  MENOR, // <
  MENORIGUAL // <=
};

enum OP_LOGIC 
{
  AND,   // &&
  OR,  // ||
  NEGACAO // !
};


// Definição de uma estrutura chamada TOKEN, que representa um token léxico.
typedef struct {
  // Categoria do token, representada por uma enumeração TOKEN_CAT.
  enum TOKEN_CAT cat; 
  // União de dados para armazenar diferentes tipos de informações associadas ao token.
  union {             
    // Código de identificação do token (int).
    int codigo;     
    // Índice associado ao token (int).
    int indice;       
    // Lexema (sequência de caracteres) associado ao token, com tamanho máximo definido por TAM_MAX_LEXEMA.
    char lexema[TAM_MAX_LEXEMA]; 
    // Valor inteiro associado ao token (int).
    int valInt;   
    // Valor de ponto flutuante associado ao token (float).
    float valFloat; 
    // Caractere associado ao token (char).
    char caractere; 
  };
} TOKEN; 



extern TOKEN tk;
extern FILE *fd;



TOKEN AnaLex(FILE *);

#endif