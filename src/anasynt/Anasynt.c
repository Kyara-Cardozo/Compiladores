#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../analex/Analex.h"
#include "../Funcaux.h"
#include "../tabelaId.h"
#include "Anasynt.h"

// Variáveis globais
bool is_const;
int escopo;
enum TOKEN_CAT idCat;

void Aplicacao() {
    while (t.cat == PALAVRA_RESERVADA && ((strcmp(t.lexema, "const") == 0) || (strcmp(t.lexema, "char") == 0) ||
                                 (strcmp(t.lexema, "int") == 0) || (strcmp(t.lexema, "real") == 0) ||
                                 (strcmp(t.lexema, "bool") == 0))) {
        escopo = 0;
        Decl_list_var();
        if (t.processado)
            t = AnaliseLexica(fd, true);
    }

    if (t.processado)
        t = AnaliseLexica(fd, true);
    while ((t.cat == PALAVRA_RESERVADA && (strcmp(t.lexema, "block") == 0)) && tkLA.cat == ID) {
        Decl_block_prot();
        if (t.processado)
            t = AnaliseLexica(fd, true);
    }

    escopo = 1;
    Block_main();

    if (t.processado)
        t = AnaliseLexica(fd, true);
    while (t.cat == PALAVRA_RESERVADA && (strcmp(t.lexema, "block") == 0)) {
        escopo = 2;
        Block_def();
        if (t.processado)
            t = AnaliseLexica(fd, true);
    }
}

void Decl_list_var() {
    if (strcmp(t.lexema, "const") == 0) {
        is_const = true;
        t.processado = true;
        Tipo();
    } else {
        Tipo();
    }

    if (t.processado)
        t = AnaliseLexica(fd, true);
    Decl_var();

    if (t.processado)
        t = AnaliseLexica(fd, true);
    while (t.cat == SIMBOLO && t.sy_code == VIRGULA) {
        t.processado = true;
        t = AnaliseLexica(fd, true);
        Decl_var();
        if (t.processado)
            t = AnaliseLexica(fd, true);
    }
    is_const = false;
    escopo = 0;
    idCat = 0;
}

void Tipo() {
    if (t.processado)
        t = AnaliseLexica(fd, true);
    if (t.cat != PALAVRA_RESERVADA || ((strcmp(t.lexema, "char") != 0) && (strcmp(t.lexema, "int") != 0) &&
                              (strcmp(t.lexema, "real") != 0) && (strcmp(t.lexema, "bool") != 0))) {
        exibirErro("Tipo faltando!");
    } else {
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

void Decl_var() {
    if (t.processado)
        t = AnaliseLexica(fd, true);
    if (t.cat != ID) {
        exibirErro("ID faltando!");
    } else {
        if (BuscaIdTabela(t.lexema) < 0) {
            InsertIdTable(t.lexema, is_const, escopo, idCat);
        } else {
            exibirErro("ID duplicado!");
        }
        t.processado = true;
        t = AnaliseLexica(fd, true);
    }

    while (t.cat == SIMBOLO && t.sy_code == ABRE_COLCHETE) {
        t.processado = true;
        t = AnaliseLexica(fd, true);

        if (t.cat != CONSTANTE_INT && t.cat != ID && idCat != ID_CONST) {
            exibirErro("Comprimento faltando!");
        } else {
            t.processado = true;
            t = AnaliseLexica(fd, true);
        }

        if (t.cat != SIMBOLO || t.sy_code != FECHA_COLCHETE) {
            exibirErro("Faltando colchete fechado!");
        } else {
            t.processado = true;
            t = AnaliseLexica(fd, true);
        }
    }

    if (t.cat == SIMBOLO && t.sy_code == ATRIBUICAO) {
        t.processado = true;
        t = AnaliseLexica(fd, true);

        if (t.cat == CONSTANTE_INT || t.cat == CONSTANTE_REAL || t.cat == CONSTANTE_CHAR || t.cat == CONSTANTE_STRING) {
            t.processado = true;
            t = AnaliseLexica(fd, true);
        } else if (t.cat == SIMBOLO && t.sy_code == ABRE_CHAVE) {
            t.processado = true;
            t = AnaliseLexica(fd, true);

            if (t.cat != CONSTANTE_INT && t.cat != CONSTANTE_REAL && t.cat != CONSTANTE_CHAR && t.cat != CONSTANTE_STRING) {
                exibirErro("Valor faltando!");
            } else {
                t.processado = true;
                t = AnaliseLexica(fd, true);
            }

            while (t.cat == SIMBOLO && t.sy_code == VIRGULA) {
                t.processado = true;
                t = AnaliseLexica(fd, true);

                if (t.cat != CONSTANTE_INT && t.cat != CONSTANTE_REAL && t.cat != CONSTANTE_CHAR && t.cat != CONSTANTE_STRING) {
                    exibirErro("Valor após vírgula faltando!");
                } else {
                    t.processado = true;
                    t = AnaliseLexica(fd, true);
                }
            }

            if (t.cat != SIMBOLO || t.sy_code != FECHA_CHAVE) {
                exibirErro("Faltando chave fechada!");
            } else {
                t.processado = true;
                t = AnaliseLexica(fd, true);
            }
        } else {
            exibirErro("Lado direito da atribuicao faltando!");
        }
    }
}


void Decl_block_prot() {
    if(t.processado) t = AnaliseLexica(fd, true);
    if(strcmp(t.lexema, "block") != 0){
        exibirErro("Faltando 'block'!");
    }
    else {
        t.processado = true;
    }

    if(t.processado) t = AnaliseLexica(fd, true);
    if(t.cat != ID){
        exibirErro("Faltando ID!");
    }
    else {
        t.processado = true;
    }

    if(t.processado) t = AnaliseLexica(fd, true);
    if(strcmp(t.lexema, "with") == 0){
        t.processado = true;
        
        if(t.processado) t = AnaliseLexica(fd, true);
        if(t.cat == SIMBOLO && t.sy_code == ENDERECO){
            t.processado = true;
            Tipo();
        }
        else{
            Tipo();
        }

        if(t.processado) t = AnaliseLexica(fd, true);
        while(t.cat == SIMBOLO && t.sy_code == ABRE_COLCHETE){
            t.processado = true;
            t = AnaliseLexica(fd, true);
            if(t.cat == SIMBOLO && t.sy_code == FECHA_COLCHETE){
                t.processado = true;
            }
            else {
                exibirErro("Faltando fechar colchete!");
            }
            if(t.processado) t = AnaliseLexica(fd, true);
        }

        if(t.processado) t = AnaliseLexica(fd, true);
        while(t.cat == SIMBOLO && t.sy_code == VIRGULA){
            t.processado = true;
            t = AnaliseLexica(fd, true);
            
            if(t.cat == SIMBOLO && t.sy_code == ENDERECO){
                t.processado = true;
                Tipo();
            }
            else{
                Tipo();
            }

            if(t.processado) t = AnaliseLexica(fd, true);
            while(t.cat == SIMBOLO && t.sy_code == ABRE_COLCHETE){
                t.processado = true;
                t = AnaliseLexica(fd, true);
                
                if(t.cat == SIMBOLO && t.sy_code == FECHA_COLCHETE){
                    t.processado = true;
                }
                else {
                    exibirErro("Faltando fechar colchete!");
                }
                if(t.processado) t = AnaliseLexica(fd, true);
            }
            if(t.processado) t = AnaliseLexica(fd, true);
        }
    }
}

void Block_main(){
    if(t.processado) t = AnaliseLexica(fd, true);   
    if(t.cat != PALAVRA_RESERVADA || (strcmp(t.lexema, "block") != 0)){
        exibirErro("Faltando 'block' !");
    }
    t.processado = true;
    t = AnaliseLexica(fd, true);

    if(t.cat != PALAVRA_RESERVADA || (strcmp(t.lexema, "main") != 0)){
        exibirErro("Faltando 'main' !");
    }
    t.processado = true;
    t = AnaliseLexica(fd, true);

    while((t.cat == PALAVRA_RESERVADA && ((strcmp(t.lexema, "const") == 0) || (strcmp(t.lexema, "char") == 0) || 
                                (strcmp(t.lexema, "int") == 0) || (strcmp(t.lexema, "real") == 0) ||
                                (strcmp(t.lexema, "bool") == 0)))){
                                    Decl_list_var();
                                    if(t.processado) t = AnaliseLexica(fd, true);
                                }

    while(t.cat == ID || (t.cat == PALAVRA_RESERVADA && ((strcmp(t.lexema, "do") == 0) || (strcmp(t.lexema, "if") == 0) || (strcmp(t.lexema, "while") == 0) || 
                                (strcmp(t.lexema, "goback") == 0) || (strcmp(t.lexema, "getint") == 0) || (strcmp(t.lexema, "getreal") == 0) || 
                                (strcmp(t.lexema, "getchar") == 0) || (strcmp(t.lexema, "putint") == 0) || (strcmp(t.lexema, "putreal") == 0) || 
                                (strcmp(t.lexema, "putchar") == 0)))){
        Cmd();
        if(t.processado) t = AnaliseLexica(fd, true);
    }

    if(t.cat != PALAVRA_RESERVADA || (strcmp(t.lexema, "endblock") != 0)){
        exibirErro("Faltando 'endblock' !");
    }
    t.processado = true;
    escopo = 0;
}

void Block_def(){
    if(t.processado) t = AnaliseLexica(fd, true);
    if(t.cat != PALAVRA_RESERVADA || (strcmp(t.lexema, "block") != 0)){
        exibirErro("Faltando 'block' !");
    }
    t.processado = true;
    t = AnaliseLexica(fd, true);

    if(t.cat != ID){
        exibirErro("Faltando ID !");
    }
    t.processado = true;
    t = AnaliseLexica(fd, true);

    if(t.cat == PALAVRA_RESERVADA && (strcmp(t.lexema, "with") == 0)){
        t.processado = true;
        t = AnaliseLexica(fd, true);
        Tipo();

        if(t.processado) t = AnaliseLexica(fd, true);
        if(t.cat != ID){
            exibirErro("Faltando ID !");
        }
        t.processado = true;
        t = AnaliseLexica(fd, true);

        while(t.cat == SIMBOLO && t.sy_code == ABRE_COLCHETE){
            t.processado = true;
            t = AnaliseLexica(fd, true);
            
            if(t.cat != CONSTANTE_INT && t.cat != ID && idCat != ID_CONST){
                exibirErro("Faltando length!");
            }
            else{
                t.processado = true;
                t = AnaliseLexica(fd, true);
            }

            if(t.cat != SIMBOLO || t.sy_code != FECHA_COLCHETE){
                exibirErro("Faltando fechar colchete!");
            }
            else{
                t.processado = true;
                t = AnaliseLexica(fd, true);
            }
        }

        while(t.cat == SIMBOLO && t.sy_code == VIRGULA){
            t.processado = true;
            t = AnaliseLexica(fd, true);
            Tipo();

            if(t.processado) t = AnaliseLexica(fd, true);
            if(t.cat != ID){
                exibirErro("Faltando ID !");
            }
            t.processado = true;
            t = AnaliseLexica(fd, true);

            while(t.cat == SIMBOLO && t.sy_code == ABRE_COLCHETE){
                t.processado = true;
                t = AnaliseLexica(fd, true);
                
                if(t.cat != CONSTANTE_INT && t.cat != ID && idCat != ID_CONST){
                    exibirErro("Faltando length!");
                }
                else{
                    t.processado = true;
                    t = AnaliseLexica(fd, true);
                }

                if(t.cat != SIMBOLO || t.sy_code != FECHA_COLCHETE){
                    exibirErro("Faltando fechar colchete!");
                }
                else{
                    t.processado = true;
                    t = AnaliseLexica(fd, true);
                }
                if(t.processado) t = AnaliseLexica(fd, true);
            }
            if(t.processado) t = AnaliseLexica(fd, true);
        }

        if(t.processado) t = AnaliseLexica(fd, true);
        while(t.cat == PALAVRA_RESERVADA && ((strcmp(t.lexema, "const") == 0) || (strcmp(t.lexema, "char") == 0) || 
                                (strcmp(t.lexema, "int") == 0) || (strcmp(t.lexema, "real") == 0) ||
                                (strcmp(t.lexema, "bool") == 0))) {
                                    Decl_list_var();
                                    if(t.processado) t = AnaliseLexica(fd, true);
                                }

        if(t.processado) t = AnaliseLexica(fd, true);
        while(t.cat == ID || (t.cat == PALAVRA_RESERVADA && ((strcmp(t.lexema, "do") == 0) || (strcmp(t.lexema, "if") == 0) || (strcmp(t.lexema, "while") == 0) || 
                                    (strcmp(t.lexema, "goback") == 0) || (strcmp(t.lexema, "getint") == 0) || (strcmp(t.lexema, "getreal") == 0) || 
                                    (strcmp(t.lexema, "getchar") == 0) || (strcmp(t.lexema, "putint") == 0) || (strcmp(t.lexema, "putreal") == 0) || 
                                    (strcmp(t.lexema, "putchar") == 0)))){
            Cmd();
            if(t.processado) t = AnaliseLexica(fd, true);
        }

        if(t.processado) t = AnaliseLexica(fd, true);
        if(t.cat != PALAVRA_RESERVADA || (strcmp(t.lexema, "endblock") != 0)){
            exibirErro("Faltando 'endblock' !");
        }
        t.processado = true;
    }
    t.processado = true;
    t = AnaliseLexica(fd, true);
    escopo = 0;
}

void Cmd() {
    if (t.processado)
        t = AnaliseLexica(fd, true);

    if (t.cat == PALAVRA_RESERVADA && strcmp(t.lexema, "do") == 0) {
        t.processado = true;
        t = AnaliseLexica(fd, true);

        if (t.cat == ID) {
            t.processado = true;
            t = AnaliseLexica(fd, true);

            if (t.cat == PALAVRA_RESERVADA && strcmp(t.lexema, "with") == 0) {
                t.processado = true;
                t = AnaliseLexica(fd, true);

                if (t.cat != ID) {
                    exibirErro("Faltando ID !");
                }

                t.processado = true;
                t = AnaliseLexica(fd, true);

                while (t.cat == SIMBOLO && t.sy_code == VIRGULA) {
                    t.processado = true;
                    t = AnaliseLexica(fd, true);

                    if (t.cat != ID) {
                        exibirErro("Faltando ID !");
                    }

                    t.processado = true;
                    t = AnaliseLexica(fd, true);
                }
            }
        } else if (t.cat == ID || (t.cat == PALAVRA_RESERVADA && (strcmp(t.lexema, "do") == 0 || strcmp(t.lexema, "if") == 0 ||
                                                        strcmp(t.lexema, "while") == 0 || strcmp(t.lexema, "goback") == 0 ||
                                                        strcmp(t.lexema, "getint") == 0 || strcmp(t.lexema, "getreal") == 0 ||
                                                        strcmp(t.lexema, "getchar") == 0 || strcmp(t.lexema, "putint") == 0 ||
                                                        strcmp(t.lexema, "putreal") == 0 || strcmp(t.lexema, "putchar") == 0))) {
            Cmd();
        } else {
            exibirErro("Faltando id ou cmd !");
        }

        if (t.processado)
            t = AnaliseLexica(fd, true);

        if (t.cat == PALAVRA_RESERVADA && strcmp(t.lexema, "varying") == 0) {
            t.processado = true;
            t = AnaliseLexica(fd, true);

            if (t.cat != ID) {
                exibirErro("Faltando ID !");
            }

            t.processado = true;
            t = AnaliseLexica(fd, true);

            if (t.cat != PALAVRA_RESERVADA || strcmp(t.lexema, "from") != 0) {
                exibirErro("Faltando 'from' !");
            }

            t.processado = true;
            t = AnaliseLexica(fd, true);

            Expressao();

            if (t.processado)
                t = AnaliseLexica(fd, true);

            if (t.cat != PALAVRA_RESERVADA || (strcmp(t.lexema, "to") != 0 && strcmp(t.lexema, "downto") != 0)) {
                exibirErro("Faltando 'to' ou 'downto' !");
            }

            t.processado = true;
            t = AnaliseLexica(fd, true);
            Expressao();
        } else if (t.cat == PALAVRA_RESERVADA && strcmp(t.lexema, "while") == 0) {
            t.processado = true;
            t = AnaliseLexica(fd, true);

            if (t.cat != SIMBOLO || t.sy_code != ABRE_PARENTESE) {
                exibirErro("Faltando '(' !");
            }

            t.processado = true;
            t = AnaliseLexica(fd, true);

            Expressao();

            if (t.processado)
                t = AnaliseLexica(fd, true);

            if (t.cat != SIMBOLO || t.sy_code != FECHA_PARENTESE) {
                exibirErro("Faltando ')' !");
            }
        } else if (t.cat == PALAVRA_RESERVADA && strcmp(t.lexema, "for") == 0) {
            t.processado = true;
            t = AnaliseLexica(fd, true);

            Expressao();

            if (t.processado)
                t = AnaliseLexica(fd, true);

            if (t.cat != PALAVRA_RESERVADA || strcmp(t.lexema, "times") == 0) {
                exibirErro("Faltando 'times' !");
            }
        }
    } else if (t.cat == PALAVRA_RESERVADA && strcmp(t.lexema, "if") == 0) {
        t.processado = true;
        t = AnaliseLexica(fd, true);

        if (t.cat != SIMBOLO || t.sy_code != ABRE_PARENTESE) {
            exibirErro("Faltando '(' !");
        }

        t.processado = true;
        t = AnaliseLexica(fd, true);

        Expressao();

        if (t.processado)
            t = AnaliseLexica(fd, true);

        if (t.cat != SIMBOLO || t.sy_code != FECHA_PARENTESE) {
            exibirErro("Faltando ')' !");
        }

        t.processado = true;
        t = AnaliseLexica(fd, true);

        while (t.cat == ID || (t.cat == PALAVRA_RESERVADA && (strcmp(t.lexema, "do") == 0 || strcmp(t.lexema, "if") == 0 ||
                                                     strcmp(t.lexema, "while") == 0 || strcmp(t.lexema, "goback") == 0 ||
                                                     strcmp(t.lexema, "getint") == 0 || strcmp(t.lexema, "getreal") == 0 ||
                                                     strcmp(t.lexema, "getchar") == 0 || strcmp(t.lexema, "putint") == 0 ||
                                                     strcmp(t.lexema, "putreal") == 0 || strcmp(t.lexema, "putchar") == 0))) {
            Cmd();
            if (t.processado)
                t = AnaliseLexica(fd, true);
        }

        if (t.processado)
            t = AnaliseLexica(fd, true);

        while (t.cat == PALAVRA_RESERVADA && strcmp(t.lexema, "elseif") == 0) {
            t.processado = true;
            t = AnaliseLexica(fd, true);

            if (t.cat != SIMBOLO || t.sy_code != ABRE_PARENTESE) {
                exibirErro("Faltando '(' !");
            }

            t.processado = true;
            t = AnaliseLexica(fd, true);

            Expressao();

            if (t.processado)
                t = AnaliseLexica(fd, true);

            if (t.cat != SIMBOLO || t.sy_code != FECHA_PARENTESE) {
                exibirErro("Faltando ')' !");
            }

            t.processado = true;
            t = AnaliseLexica(fd, true);

            while (t.cat == ID || (t.cat == PALAVRA_RESERVADA && (strcmp(t.lexema, "do") == 0 || strcmp(t.lexema, "if") == 0 ||
                                                         strcmp(t.lexema, "while") == 0 || strcmp(t.lexema, "goback") == 0 ||
                                                         strcmp(t.lexema, "getint") == 0 || strcmp(t.lexema, "getreal") == 0 ||
                                                         strcmp(t.lexema, "getchar") == 0 || strcmp(t.lexema, "putint") == 0 ||
                                                         strcmp(t.lexema, "putreal") == 0 || strcmp(t.lexema, "putchar") == 0))) {
                Cmd();
                if (t.processado)
                    t = AnaliseLexica(fd, true);
            }
            if (t.processado)
                t = AnaliseLexica(fd, true);
        }

        if (t.processado)
            t = AnaliseLexica(fd, true);

        if (t.cat == PALAVRA_RESERVADA && strcmp(t.lexema, "else") == 0) {
            t.processado = true;
            t = AnaliseLexica(fd, true);

            while (t.cat == ID || (t.cat == PALAVRA_RESERVADA && (strcmp(t.lexema, "do") == 0 || strcmp(t.lexema, "if") == 0 ||
                                                         strcmp(t.lexema, "while") == 0 || strcmp(t.lexema, "goback") == 0 ||
                                                         strcmp(t.lexema, "getint") == 0 || strcmp(t.lexema, "getreal") == 0 ||
                                                         strcmp(t.lexema, "getchar") == 0 || strcmp(t.lexema, "putint") == 0 ||
                                                         strcmp(t.lexema, "putreal") == 0 || strcmp(t.lexema, "putchar") == 0))) {
                Cmd();
                if (t.processado)
                    t = AnaliseLexica(fd, true);
            }
        }

        if (t.processado)
            t = AnaliseLexica(fd, true);

        if (t.cat != PALAVRA_RESERVADA || strcmp(t.lexema, "endif") != 0) {
            exibirErro("Faltando 'endif' !");
        }

        t.processado = true;
    } else if (t.cat == PALAVRA_RESERVADA && strcmp(t.lexema, "while") == 0) {
        t.processado = true;
        t = AnaliseLexica(fd, true);

        if (t.cat != SIMBOLO || t.sy_code != ABRE_PARENTESE) {
            exibirErro("Faltando '(' !");
        }

        t.processado = true;
        t = AnaliseLexica(fd, true);

        Expressao();

        if (t.processado)
            t = AnaliseLexica(fd, true);

        if (t.cat != SIMBOLO || t.sy_code != FECHA_PARENTESE) {
            exibirErro("Faltando ')' !");
        }

        t.processado = true;
        t = AnaliseLexica(fd, true);

        while(t.cat == ID || (t.cat == PALAVRA_RESERVADA && ((strcmp(t.lexema, "do") == 0) || (strcmp(t.lexema, "if") == 0) || (strcmp(t.lexema, "while") == 0) || 
                                    (strcmp(t.lexema, "goback") == 0) || (strcmp(t.lexema, "getint") == 0) || (strcmp(t.lexema, "getreal") == 0) || 
                                    (strcmp(t.lexema, "getchar") == 0) || (strcmp(t.lexema, "putint") == 0) || (strcmp(t.lexema, "putreal") == 0) || 
                                    (strcmp(t.lexema, "putchar") == 0)))){
            Cmd();
            if(t.processado) t = AnaliseLexica(fd, true);
        }

        if (t.cat != PALAVRA_RESERVADA || strcmp(t.lexema, "endwhile") != 0) {
            exibirErro("Faltando 'endwhile' !");
        }

        t.processado = true;
    } else if (t.cat == ID) {
        Atrib();
    } else if (t.cat == PALAVRA_RESERVADA && strcmp(t.lexema, "goback") == 0) {
        t.processado = true;
    } else if (t.cat == PALAVRA_RESERVADA && (strcmp(t.lexema, "getint") == 0 || strcmp(t.lexema, "getreal") == 0 ||
                                     strcmp(t.lexema, "getchar") == 0 || strcmp(t.lexema, "putint") == 0 ||
                                     strcmp(t.lexema, "putreal") == 0 || strcmp(t.lexema, "putchar") == 0)) {
        t.processado = true;
        t = AnaliseLexica(fd, true);

        if (t.cat != ID) {
            exibirErro("Faltando ID !");
        }

        t.processado = true;
    }
}


void Expressao() {
    Expr_simp();

    if (t.processado)
        t = AnaliseLexica(fd, true);

    if (t.cat == SIMBOLO && (t.sy_code == IGUAL || t.sy_code == DIFERENTE || t.sy_code == MENOR ||
                            t.sy_code == MENOR_IGUAL || t.sy_code == MAIOR_QUE || t.sy_code == MAIOR_IGUAL)) {
        Op_rel();
        if (t.processado)
            t = AnaliseLexica(fd, true);
        Expr_simp();
    }
}

void Expr_simp() {
    if (t.processado)
        t = AnaliseLexica(fd, true);

    if (t.cat == SIMBOLO && (t.sy_code == ADICAO || t.sy_code == SUBTRACAO)) {
        t.processado = true;
    }

    if (t.processado)
        t = AnaliseLexica(fd, true);

    Termo();

    if (t.processado)
        t = AnaliseLexica(fd, true);

    while (t.cat == SIMBOLO && (t.sy_code == ADICAO || t.sy_code == SUBTRACAO || t.sy_code == OPERADOR_OU)) {
        if (t.sy_code != ADICAO && t.sy_code != SUBTRACAO && t.sy_code != OPERADOR_OU) {
            exibirErro("Símbolo inválido!");
        }
        t.processado = true;
        t = AnaliseLexica(fd, true);

        Termo();

        if (t.processado)
            t = AnaliseLexica(fd, true);
    }
}

void Termo() {
    Fator();

    if (t.processado)
        t = AnaliseLexica(fd, true);

    while (t.cat == SIMBOLO && (t.sy_code == MULTIPLICACAO || t.sy_code == DIVISAO || t.sy_code == OPERADOR_E)) {
        if (t.sy_code != MULTIPLICACAO && t.sy_code != DIVISAO && t.sy_code != OPERADOR_E) {
            exibirErro("Símbolo inválido!");
        }
        t.processado = true;
        t = AnaliseLexica(fd, true);

        Fator();

        if (t.processado)
            t = AnaliseLexica(fd, true);
    }
}

void Fator() {
    if (t.cat == ID) {
        t.processado = true;
        t = AnaliseLexica(fd, true);

        while (t.cat == SIMBOLO && t.sy_code == ABRE_COLCHETE) {
            t.processado = true;
            t = AnaliseLexica(fd, true);

            Expressao();

            if (t.processado)
                t = AnaliseLexica(fd, true);

            if (t.cat != SIMBOLO || t.sy_code != FECHA_COLCHETE) {
                exibirErro("Faltando ']' !");
            }
            t.processado = true;
            t = AnaliseLexica(fd, true);
        }
    } else if (t.cat == CONSTANTE_INT || t.cat == CONSTANTE_REAL || t.cat == CONSTANTE_CHAR) {
        t.processado = true;
    } else if (t.cat == SIMBOLO && t.sy_code == ABRE_PARENTESE) {
        t.processado = true;
        t = AnaliseLexica(fd, true);

        Expressao();

        if (t.processado)
            t = AnaliseLexica(fd, true);

        if (t.cat != SIMBOLO || t.sy_code != FECHA_PARENTESE) {
            exibirErro("Faltando ')' !");
        }
    } else if (t.cat == SIMBOLO && t.sy_code == OPERADOR_NEGACAO) {
        t.processado = true;
        t = AnaliseLexica(fd, true);
        Fator();
    }
}

void Op_rel() {
    if (t.processado)
        t = AnaliseLexica(fd, true);

    if (t.cat != SIMBOLO || (t.sy_code != IGUAL && t.sy_code != DIFERENTE && t.sy_code != MENOR &&
                            t.sy_code != MENOR_IGUAL && t.sy_code != MAIOR_QUE && t.sy_code != MAIOR_IGUAL)) {
        exibirErro("Operador inválido!");
    } else {
        t.processado = true;
    }
}

void Atrib() {

    if (t.processado)
        t = AnaliseLexica(fd, true);

    if (t.cat != ID) {
        exibirErro("ID faltando");
    }

    t.processado = true;
    t = AnaliseLexica(fd, true);

    while (t.cat == SIMBOLO && t.sy_code == ABRE_COLCHETE) {
        t.processado = true;
        t = AnaliseLexica(fd, true);

        Expressao();

        if (t.processado)
            t = AnaliseLexica(fd, true);

        if (t.cat != SIMBOLO || t.sy_code != FECHA_COLCHETE) {
            exibirErro("Faltando ']' !");
        }

        t.processado = true;
        t = AnaliseLexica(fd, true);
    }

    if (t.cat != SIMBOLO || t.sy_code != ATRIBUICAO) {
        exibirErro("Faltando '=' !");
    }

    t.processado = true;
    t = AnaliseLexica(fd, true);

    Expressao();
}

