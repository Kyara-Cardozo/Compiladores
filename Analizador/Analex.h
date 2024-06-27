#include <stdio.h>
#ifndef ANALEX_H
#define ANALEX_H
#define TAM_MAX_LEXEMA 31

enum TOKEN_CAT
{
    ID = 1,       // Identificador
    PAL_RESERV,  // Palavra reservada
    SN,         //  Símbolo ou sinal
    CT_C,      // Constante caractere
    CT_F,      // Constante numérica real
    CT_I,     // Constante numérica inteira
    ID_CONST,    
    LT,         // Literal
    OP_ARIT,     
    OP_LOGIC,    
    OP_RELAC,    
    FIM_EXPR,    // Fim expressão
    FIM_PROG     // Fim arquivo
};


enum PAL_RESERV
{
    MAIN = 1, 
    BLOCK,    
    ENDBLOCK, 
    CONST,    
    CHAR,
    INT,      
    REAL,    
    BOOL,     
    WITH,     
    DO,       
    VARYING,  
    FROM,    
    TO,       
    DOWNTO,   
    WHILE,    
    ENDWHILE, 
    FOR,      
    IF,       
    ELSEIF,   
    ELSE,     
    ENDIF,    
    GOBACK,   
    GETINT,   
    GETCHAR,  
    GETREAL,  
    PUTINT,   
    PUTREAL,  
    PUTCHAR   
};

// Palavras reservadas da linguagem

enum SINAIS
{
    ABRE_PAR = 1, 
    FECHA_PAR,   
    ABRE_CHAVE,   
    FECHA_CHAVE,  
    ABRE_COL,     
    FECHA_COL,    
    VIR,      
    REF    
};
// Sinais válidos da linguagem

enum OP_ARIT
{
    ATRIBUICAO = 1, // =
    SOMA,           // +
    SUBTRACAO,      // -
    MULT,           // *
    DIV            // /
};

enum OP_RELAC
{
    IGUALDADE = 1, // ==
    DIFERENTE,     // !=
    MENOR_IGUAL,   // <=
    MAIOR_IGUAL,   // >=
    MENOR,     // <
    MAIOR      // >
};

enum OP_LOGIC
{
    AND = 1, // &&
    OR,      // ||
    NOT      // !
};


// Definição de uma estrutura chamada TOKEN, que representa um token léxico.
typedef struct
{
  // Categoria do token, representada por uma enumeração TOKEN_CAT.
    enum TOKEN_CAT cat; 
    // União de dados para armazenar diferentes tipos de informações associadas ao token.
    union
    { 
    // Código de identificação do token (int).                               
        int codigo;   
    // Índice associado ao token (int).                  
        int indice;        
    // Lexema (sequência de caracteres) associado ao token, com tamanho máximo definido por               
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