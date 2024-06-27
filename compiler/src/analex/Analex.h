#ifndef _ANALEX_ // Verifica se _ANALEX_ não foi definido anteriormente para evitar redefinições.
#define _ANALEX_ // Define _ANALEX_ para indicar que o cabeçalho foi incluído.

#include <stdio.h> // Inclui a biblioteca padrão de entrada e saída.
#include <stdbool.h> // Inclui a biblioteca padrão para o uso do tipo booleano.

#define LEXEME_MAX_SIZE 31 // Define o tamanho máximo de um lexema.
#define STRING_MAX_SIZE 100 // Define o tamanho máximo de uma string.
#define COMMENT_MAX_SIZE 300 // Define o tamanho máximo de um comentário.

enum TOKEN_CAT {ID=0, PALAVRA_RESERVADA, SIMBOLO, ID_CONST, CONSTANTE_INT, CONSTANTE_REAL, CONSTANTE_CHAR, CONSTANTE_STRING, CONST_BOOL, COMENTARIO, FIM_EXPRESSAO, FIM_ARQUIVO};
// Define uma enumeração para as categorias de tokens.

enum SYMBOLS {ATRIBUICAO=0, ADICAO, SUBTRACAO, MULTIPLICACAO, DIVISAO, SINAL_POSITIVO, SINAL_NEGATIVO, ENDERECO,
                IGUAL, MAIOR_QUE, MENOR, MAIOR_IGUAL, MENOR_IGUAL, DIFERENTE, 
                OPERADOR_E, OPERADOR_OU, OPERADOR_NEGACAO, ABRE_PARENTESE, FECHA_PARENTESE, ABRE_COLCHETE, 
                FECHA_COLCHETE, ABRE_CHAVE, FECHA_CHAVE, VIRGULA,
                PERIOD, DOIS_PONTOS, PONTO_VIRGULA};
// Define uma enumeração para os símbolos.

typedef struct {
    enum TOKEN_CAT cat; // Categoria do token.
    bool processado; // Indica se o token foi processado.
    union {
        int sy_code; // Código do operador.
        char lexema[LEXEME_MAX_SIZE]; // Lexema para ID ou PALAVRA_RESERVADA.
        int intVal; // Valor inteiro para CONSTANTE_INT.
        float realVal; // Valor real para CONSTANTE_REAL.
        char charVal; // Valor de caractere para CONSTANTE_CHAR.
        char string[STRING_MAX_SIZE]; // String para CONSTANTE_STRING.
        char comment[COMMENT_MAX_SIZE]; // Comentário para COMENTARIO.
    };
} TOKEN; // Define a estrutura de um token.

extern int ContadorLinha; // Contador de linhas do arquivo.
extern TOKEN t; // Token atual.
extern TOKEN tkLA; // Lookahead token.
extern FILE *fd; // Ponteiro para o arquivo de entrada.

TOKEN AnalexTLA(FILE *fd, bool pular_fim_expressao); // Função que realiza análise léxica com lookahead.
TOKEN AnaliseLexica(FILE *fd, bool pular_fim_expressao); // Função que realiza análise léxica.

#endif // _ANALEX_ // Finaliza a inclusão condicional.
