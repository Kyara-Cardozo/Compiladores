#ifndef _ID_TABLE_
#define _ID_TABLE_

#include <stdlib.h>
#include <stdio.h>
#include "../Analisador Lexico/Analex.h"



#define ID_TAB_TAMANHO_MAXIMO 200

typedef struct {
    char NomeId[LEXEME_MAX_SIZE];
    int endereco;
    bool is_const;
    bool zombie;
    int escopo;
    enum TOKEN_CAT cat;
    union {
        char charVal;
        int intVal;
        float realVal;
        bool boolVal;
    };
} ID_REG;

typedef struct {
    ID_REG id[ID_TAB_TAMANHO_MAXIMO];
    int tabSize;
} TABELA_ID;

extern TOKEN t;
extern TABELA_ID tabelaId;

void InicializarTabelaId();
int BuscaIdTabela(char []);
int InsertIdTable(char [], bool is_const, int escopo, enum TOKEN_CAT cat);

#endif // _ID_TABLE_
