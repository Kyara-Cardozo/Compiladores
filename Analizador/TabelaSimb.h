#ifndef TABELASIMB
#define TABELAIM

#include <stdio.h>
#include <stdlib.h>
#include "Analex.h"
#include <stdbool.h>

#define TAM_MAX_TAB 100
#define TAM_CATEGORIA 3 
typedef
    struct 
    {

        char lexema[TAM_MAX_LEXEMA];
        int tipo;
        int escopo;
        char categoria[TAM_CATEGORIA];
        bool zombie;
        //int endereco;

    }TabSimb;
    
typedef
    struct 
        {
            int tamTab;
            TabSimb tabela_simb[TAM_MAX_TAB];
        }  TabIdef;
    
extern TabIdef tabela_idef;
extern TOKEN t;

void Iniciar_tabela();
int Busca_tabela(char lexema[]);
int Busca_escopo(char lexema[],int escopo);
int Inserir_tabela(char lexema[],int escopo,int tipo, char categoria[TAM_CATEGORIA],bool zombie);
int Remove_ultimo();
#endif