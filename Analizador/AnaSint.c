#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "AnaLex.c"
#include "AnaLex.h"
#include "AnaSint.h"

void Consome(int esperado)
{
    if (tk.cat == esperado || tk.codigo == esperado)
    {
        printf("[Consome][Entrada] - Cat: %d | Cod: %d | Lex: %s | Float: %0.2f | Int: %d\n", tk.cat, tk.codigo, tk.lexema, tk.valFloat, tk.valInt);
        tk = AnaLex(fd);
        printf("[Consome][Saida] - Cat: %d | Cod: %d | Lex: %s | Float: %0.2f | Int: %d\n", tk.cat, tk.codigo, tk.lexema, tk.valFloat, tk.valInt);
    }
    else
    {
        printf("[ERROR] - Cat: %d | Cod: %d | Lex: %s | Float: %0.2f | Int: %d\n", tk.cat, tk.codigo, tk.lexema, tk.valFloat, tk.valInt);
        char errMsg[100];
        sprintf(errMsg, "Opa! Token não esperado. Esperava:  %d, Encontrei: %d", esperado, tk.codigo);
        errorSint(contLinha, errMsg);
    }
}

void PROG()
{
    tk = AnaLex(fd);

    printf("PROG - Cat: %d | Cod: %d | Lex: %s | Float: %0.2f | Int: %d\n", tk.cat, tk.codigo, tk.lexema, tk.valFloat, tk.valInt);
    while (tk.cat == PR && (tk.codigo == CONST || tk.codigo == INT || tk.codigo == CHAR || tk.codigo == REAL || tk.codigo == BOOL))
    {
        DECL_LIST_VAR();
    }

    while (tk.cat == PR && tk.codigo == BLOCK)
    {
        printf("[DECL_BLOCK_PROT][WHILE][Entrada]\n");
        DECL_BLOCK_PROT();
        printf("[DECL_BLOCK_PROT][WHILE][Saida]\n");
    }

    if (!(tk.cat == PR && tk.codigo == MAIN))
    {
        errorSint(contLinha, "Esperava declaração do bloco Main.");
    }

    BLOACK_MAIN();

    while (tk.cat == PR && tk.codigo == BLOCK)
    {
        BLOCK_DEF();
    }

    if (tk.cat != FIM_ARQ)
    {
        errorSint(contLinha, "Esperava fim do arquivo.");
    }
}

void DECL_LIST_VAR()
{
    printf("\nENTROU -> DECL_LIST_VAR\n");

    if (tk.codigo == CONST)
    {
        Consome(CONST);
    }
    TIPO();
    DECL_VAR();

    while (tk.codigo == VIRGULA)
    {
        Consome(VIRGULA);
        DECL_VAR();
    }

    printf("\nSAIU -> DECL_LIST_VAR\n");
}

void DECL_BLOCK_PROT()
{
    printf("\nENTROU -> DECL_BLOCK_PROT\n");
    Consome(BLOCK);
    Consome(ID);

    if (tk.codigo == WITH)
    {
        printf("[DECL_BLOCK_PROT][WITH][Entrada]\n\n");
        Consome(WITH);

        while (true)
        {
            if (tk.cat == FIM_ARQ || tk.codigo == BLOCK)
            {
                break;
            }

            if (tk.codigo == REFERENCIA)
            {
                printf("[DECL_BLOCK_PROT][Referência][Entrada]\n");
                Consome(REFERENCIA);
                printf("[DECL_BLOCK_PROT][Referência][Saida]\n\n");
            }

            TIPO();

            if (tk.codigo == ABRE_COL)
            {
                printf("[DECL_BLOCK_PROT][ABRE_COL][Entrada]\n");
                Consome(ABRE_COL);
                printf("[DECL_BLOCK_PROT][ABRE_COL][Saida]\n\n");

                printf("[DECL_BLOCK_PROT][FECHA_COL][Entrada]\n");
                Consome(FECHA_COL);
                printf("[DECL_BLOCK_PROT][FECHA_COL][Saida]\n\n");
            }
            if (tk.codigo == VIRGULA)
            {
                printf("[DECL_BLOCK_PROT][Virgula][Entrada]\n");
                Consome(VIRGULA);
                printf("[DECL_BLOCK_PROT][Virgula][Saida]\n\n");
            }
        }
        printf("[DECL_BLOCK_PROT][WITH][Saida]\n\n");
    }
    printf("\nSAIU -> DECL_BLOCK_PROT\n");
}

void BLOACK_MAIN()
{
    printf("\nENTROU -> BLOACK_MAIN\n\n");
    Consome(BLOCK);
    Consome(MAIN);

    while (tk.cat == PR && (tk.codigo == CONST || tk.codigo == INT || tk.codigo == CHAR || tk.codigo == REAL || tk.codigo == BOOL))
    {
        DECL_LIST_VAR();
    }

    while (tk.codigo != ENDBLOCK)
     {
    }
    Consome(ENDBLOCK);

    printf("\nSAIU -> BLOACK_MAIN\n");
}

void BLOCK_DEF()
{
    printf("\nENTROU -> BLOCK_DEF\n");
    Consome(BLOCK);
    Consome(ID);

    if (tk.codigo == WITH)
    {
        Consome(WITH);
        TIPO();
        Consome(ID);

        if (tk.codigo == ABRE_COL)
        {
            Consome(ABRE_COL);
            if (tk.cat == CONST_INT || tk.cat == CONST_INT)
            {
                Consome(tk.cat);
            }
            Consome(FECHA_COL);
        }

        while (tk.codigo == VIRGULA)
        {
            Consome(VIRGULA);
            TIPO();
            Consome(ID);
            if (tk.codigo == ABRE_COL)
            {
                Consome(ABRE_COL);
                if (tk.cat == CONST_INT || tk.cat == CONST_INT)
                {
                    Consome(tk.cat);
                }
                Consome(FECHA_COL);
            }
        }
    }

    while (tk.cat == PR && (tk.codigo == CONST || tk.codigo == INT || tk.codigo == CHAR || tk.codigo == REAL || tk.codigo == BOOL))
    {
        DECL_LIST_VAR();
    }

    while (tk.codigo != ENDBLOCK)
    {
        CMD();
    }
    Consome(ENDBLOCK);
    printf("\nSAIU -> BLOCK_DEF\n");
}

void TIPO()
{
    printf("\nENTROU -> TIPO\n");

    if (tk.codigo == CHAR || tk.codigo == INT || tk.codigo == REAL || tk.codigo == BOOL)
    {
        printf("[TIPO][COD][Entrada]\n\n");
        Consome(tk.codigo);
    }
    else
    {
        printf("[TIPO][ERROR][Entrada]\n\n");
        errorSint(contLinha, "Opa! Tipo invalido. ");
    }
    printf("\nSAIU -> TIPO\n");
}

void DECL_VAR()
{
    printf("\nENTROU -> DECL_VAR\n");
    Consome(ID);

    if (tk.codigo == ABRE_COL)
    {
        printf("[DECL_VAR][ABRE_COL][Entrada]\n\n");

        Consome(ABRE_COL);
        if (tk.cat == CONST_INT || tk.cat == CONST_INT)
        {
            printf("[DECL_VAR][CONST_INT][Entrada]\n\n");
            Consome(tk.cat);
        }
        Consome(FECHA_COL);
    }

    if (tk.codigo == ATRIB)
    {
        printf("[DECL_VAR][ATRIB][Entrada]\n\n");
        Consome(ATRIB);
        if (tk.cat == CONST_INT || tk.cat == CT_F || tk.cat == CT_C || tk.cat == LT)
        {
            printf("[DECL_VAR][ATRIB][CAT][Entrada]\n\n");
            Consome(tk.cat);
        }
        else if (tk.codigo == ABRE_CHAVE)
        {
            printf("[DECL_VAR][ATRIB][ABRE_CHAVE][Entrada]\n\n");
            Consome(ABRE_CHAVE);
            do
            {
                if (tk.cat == CONST_INT || tk.cat == CT_F || tk.cat == CT_C || tk.cat == LT)
                {
                    Consome(tk.cat);
                }
                if (tk.codigo == VIRGULA)
                {
                    Consome(VIRGULA);
                }
                else
                {
                    break;
                }
            } while (true);
            Consome(FECHA_CHAVE);
        }
        else
        {
            printf("[DECL_VAR][ATRIB][ERRO][Entrada]\n\n");
            errorSint(contLinha, "Valor esperado após '='.");
        }
        printf("[DECL_VAR][ATRIB][Saida] - Cat: %d | Cod: %d | Lex: %s | Float: %0.2f | Int: %d\n", tk.cat, tk.codigo, tk.lexema, tk.valFloat, tk.valInt);
    }
    printf("\nSAIU -> DECL_VAR\n");
}

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "AnaLex.c"
#include "AnaLex.h"
#include "AnaSint.h"

void Consome(int esperado)
{
    if (tk.cat == esperado || tk.codigo == esperado)
    {
        printf("Consome entrada - Cat: %d | Cod: %d | Lex: %s | Float: %0.2f | Int: %d\n", tk.cat, tk.codigo, tk.lexema, tk.valFloat, tk.valInt);
        tk = AnaLex(fd);
        printf("Consome saida - Cat: %d | Cod: %d | Lex: %s | Float: %0.2f | Int: %d\n", tk.cat, tk.codigo, tk.lexema, tk.valFloat, tk.valInt);
    }
    else
    {
        printf("Cat: %d | Cod: %d | Lex: %s | Float: %0.2f | Int: %d\n", tk.cat, tk.codigo, tk.lexema, tk.valFloat, tk.valInt);
        char errMsg[100];
        sprintf(errMsg, "Opa! Token não esperado. Esperava:  %d, Encontrei: %d", esperado, tk.codigo);
        errorSint(contLinha, errMsg);
    }
}

void PROG()
{
    tk = AnaLex(fd);

    printf("PROG - Cat: %d | Cod: %d | Lex: %s | Float: %0.2f | Int: %d\n", tk.cat, tk.codigo, tk.lexema, tk.valFloat, tk.valInt);
    while (tk.cat == PR && (tk.codigo == CONST || tk.codigo == INT || tk.codigo == CHAR || tk.codigo == REAL || tk.codigo == BOOL))
    {
        printf("\nENTROU -> DECL_LIST_VAR\n");
        DECL_LIST_VAR();
    }

    while (tk.cat == PR && tk.codigo == BLOCK)
    {
        printf("\nENTROU -> DECL_BLOCK_PROT\n");
        DECL_BLOCK_PROT();
    }

    if (!(tk.cat == PR && tk.codigo == MAIN))
    {
        errorSint(contLinha, "Esperava declaração do bloco Main.");
    }

    BLOACK_MAIN();

    while (tk.cat == PR && tk.codigo == BLOCK)
    {
        BLOCK_DEF();
    }

    if (tk.cat != FIM_ARQ)
    {
        errorSint(contLinha, "Esperava fim do arquivo.");
    }
}

void DECL_LIST_VAR()
{
    if (tk.codigo == CONST)
    {
        Consome(CONST);
    }
    TIPO();
    DECL_VAR();

    while (tk.codigo == VIRGULA)
    {
        Consome(VIRGULA);
        DECL_VAR();
    }
}

void DECL_BLOCK_PROT()
{
    Consome(BLOCK);
    Consome(ID);

    if (tk.codigo == WITH)
    {
        Consome(WITH);

        do
        {
            Consome(REFERENCIA);
            TIPO();
            if (tk.codigo == ABRE_COL)
            {
                Consome(ABRE_COL);
                Consome(FECHA_COL);
            }
            if (tk.codigo == VIRGULA)
            {
                Consome(VIRGULA);
            }
            else
            {
                break;
            }
        } while (true);
    }
}

void BLOACK_MAIN()
{
    printf("\nENTROU -> BLOACK_MAIN\n");
    Consome(BLOCK);
    Consome(MAIN);

    while (tk.cat == PR && (tk.codigo == CONST || tk.codigo == INT || tk.codigo == CHAR || tk.codigo == REAL || tk.codigo == BOOL))
    {
        DECL_LIST_VAR();
    }

    while (tk.codigo != ENDBLOCK)
    {
        break;
        // CMD();
    }
    Consome(ENDBLOCK);
}

void BLOCK_DEF()
{
    Consome(BLOCK);
    Consome(ID);

    if (tk.codigo == WITH)
    {
        Consome(WITH);
        TIPO();
        Consome(ID);

        if (tk.codigo == ABRE_COL)
        {
            Consome(ABRE_COL);
            if (tk.cat == CONST_INT || tk.cat == CONST_INT)
            {
                Consome(tk.cat);
            }
            Consome(FECHA_COL);
        }

        while (tk.codigo == VIRGULA)
        {
            Consome(VIRGULA);
            TIPO();
            Consome(ID);
            if (tk.codigo == ABRE_COL)
            {
                Consome(ABRE_COL);
                if (tk.cat == CONST_INT || tk.cat == CONST_INT)
                {
                    Consome(tk.cat);
                }
                Consome(FECHA_COL);
            }
        }
    }

    while (tk.cat == PR && (tk.codigo == CONST || tk.codigo == INT || tk.codigo == CHAR || tk.codigo == REAL || tk.codigo == BOOL))
    {
        DECL_LIST_VAR();
    }

    while (tk.codigo != ENDBLOCK)
    {
        break;
        // CMD();
    }
    Consome(ENDBLOCK);
}

void TIPO()
{
    printf("\nENTROU -> TIPO\n");
    printf("Tipo entrada - Cat: %d | Cod: %d | Lex: %s | Float: %0.2f | Int: %d\n", tk.cat, tk.codigo, tk.lexema, tk.valFloat, tk.valInt);

    if (tk.codigo == CHAR || tk.codigo == INT || tk.codigo == REAL || tk.codigo == BOOL)
    {
        printf("Tipo Dentro - Cat: %d | Cod: %d | Lex: %s | Float: %0.2f | Int: %d\n", tk.cat, tk.codigo, tk.lexema, tk.valFloat, tk.valInt);
        Consome(tk.codigo);
    }
    else
    {
        errorSint(contLinha, "Opa! Tipo invalido. ");
    }
}

void DECL_VAR()
{
    printf("\nENTROU -> DECL_VAR\n");
    printf("DECL_VAR Entrada - Cat: %d | Cod: %d | Lex: %s | Float: %0.2f | Int: %d\n", tk.cat, tk.codigo, tk.lexema, tk.valFloat, tk.valInt);
    Consome(ID);

    if (tk.codigo == ABRE_COL)
    {
        Consome(ABRE_COL);
        if (tk.cat == CONST_INT || tk.cat == CONST_INT)
        {
            Consome(tk.cat);
        }
        Consome(FECHA_COL);
    }

    if (tk.codigo == ATRIB)
    {
        printf("ATRIB Entrada - Cat: %d | Cod: %d | Lex: %s | Float: %0.2f | Int: %d\n", tk.cat, tk.codigo, tk.lexema, tk.valFloat, tk.valInt);
        Consome(ATRIB);
        if (tk.cat == CONST_INT || tk.cat == CT_F || tk.cat == CT_C || tk.cat == LT)
        {
            printf("CONSTANTES Entrada - Cat: %d | Cod: %d | Lex: %s | Float: %0.2f | Int: %d\n", tk.cat, tk.codigo, tk.lexema, tk.valFloat, tk.valInt);
            Consome(tk.cat);
        }
        else if (tk.codigo == ABRE_CHAVE)
        {
            Consome(ABRE_CHAVE);
            do
            {
                if (tk.cat == CONST_INT || tk.cat == CT_F || tk.cat == CT_C || tk.cat == LT)
                {
                    Consome(tk.cat);
                }
                if (tk.codigo == VIRGULA)
                {
                    Consome(VIRGULA);
                }
                else
                {
                    break;
                }
            } while (true);
            Consome(FECHA_CHAVE);
        }
        else
        {
            errorSint(contLinha, "Valor esperado após '='.");
        }
        printf("ATRIB Saida - Cat: %d | Cod: %d | Lex: %s | Float: %0.2f | Int: %d\n", tk.cat, tk.codigo, tk.lexema, tk.valFloat, tk.valInt);
    }
}

void ATRIB()
{
    Consome(ID);
    while (tk.codigo == ABRE_COL)
    {
        Consome(ABRE_COL);
        EXPR();
        Consome(FECHA_COL);
    }
    Consome(ATRIB);
    EXPR();
}

void EXPR()
{
    EXPR_SIMP();
    if (tk.codigo == IGUAL || tk.codigo == DIFERENTE || tk.codigo == MENORIGUAL ||
        tk.codigo == MENOR || tk.codigo == MAIORIGUAL || tk.codigo == MAIOR)
    {
        OPERADOR_REL();
        EXPR_SIMP();
    }
}

void EXPR_SIMP()
{
    if (tk.codigo == SOMA || tk.codigo == SUBTRACAO)
    {
        Consome(tk.codigo);
    }
    TERMO();
    while (tk.codigo == SOMA || tk.codigo == SUBTRACAO || tk.codigo == OR_LOGIC)
    {
        Consome(tk.codigo);
        TERMO();
    }
}

void TERMO()
{
    FATOR();
    while (tk.codigo == MULTIPLIC || tk.codigo == DIVISAO || tk.codigo == AND_LOGIC)
    {
        Consome(tk.codigo);
        FATOR();
    }
}

void FATOR()
{
    if (tk.cat == ID)
    {
        Consome(ID);
        while (tk.codigo == ABRE_COL)
        {
            Consome(ABRE_COL);
            EXPR();
            Consome(FECHA_COL);
        }
    }
    else if (tk.cat == CONST_INT)
    {
        Consome(CONST_INT);
    }
    else if (tk.cat == CT_F)
    {
        Consome(CT_F);
    }
    else if (tk.cat == CT_C)
    {
        Consome(CT_C);
    }
    else if (tk.codigo == ABRE_PAR)
    {
        Consome(ABRE_PAR);
        EXPR();
        Consome(FECHA_PAR);
    }
    else if (tk.codigo == NOT_LOGIC)
    {
        Consome(NOT_LOGIC);
        FATOR();
    }
    else
    {
        errorSint(contLinha, "Fator invalido");
    }
}

void OPERADOR_REL()
{
    if (tk.codigo == IGUAL || tk.codigo == DIFERENTE || tk.codigo == MENORIGUAL ||
        tk.codigo == MENOR || tk.codigo == MAIORIGUAL || tk.codigo == MAIOR)
    {
        Consome(tk.codigo);
    }
    else
    {
        errorSint(contLinha, "Operador relacional esperado");
    }
}

void CMD()
{
    if (tk.cat == PR)
    {
        switch (tk.codigo)
        {
        case DO:
            Consome(DO);
            if (tk.cat == ID)
            {
                Consome(ID);
                if (tk.codigo == WITH)
                {
                    Consome(WITH);
                    Consome(ID);
                    while (tk.codigo == VIRGULA)
                    {
                        Consome(VIRGULA);
                        Consome(ID);
                    }
                }
                if (tk.codigo == VARYING)
                {
                    Consome(VARYING);
                    Consome(ID);
                    Consome(FROM);
                    EXPR();
                    if (tk.codigo == TO)
                    {
                        Consome(TO);
                    }
                    else if (tk.codigo == DOWNTO)
                    {
                        Consome(DOWNTO);
                    }
                    else
                    {
                        errorSint(contLinha, "Esperado 'to' ou 'downto'");
                    }
                    EXPR();
                }
                else if (tk.codigo == WHILE)
                {
                    Consome(WHILE);
                    Consome(ABRE_PAR);
                    EXPR();
                    Consome(FECHA_PAR);
                }
                else if (tk.codigo == FOR)
                {
                    Consome(FOR);
                    EXPR();
                }
            }
            else
            {
                CMD();
                if (tk.codigo == VARYING)
                {
                    Consome(VARYING);
                    Consome(ID);
                    Consome(FROM);
                    EXPR();
                    if (tk.codigo == TO)
                    {
                        Consome(TO);
                    }
                    else if (tk.codigo == DOWNTO)
                    {
                        Consome(DOWNTO);
                    }
                    else
                    {
                        errorSint(contLinha, "Esperado 'to' ou 'downto'");
                    }
                    EXPR();
                }
                else if (tk.codigo == WHILE)
                {
                    Consome(WHILE);
                    Consome(ABRE_PAR);
                    EXPR();
                    Consome(FECHA_PAR);
                }
                else if (tk.codigo == FOR)
                {
                    Consome(FOR);
                    EXPR();
                }
            }
            break;

        case IF:
            Consome(IF);
            Consome(ABRE_PAR);
            EXPR();
            Consome(FECHA_PAR);
            Consome(ABRE_CHAVE);
            CMD();
            Consome(FECHA_CHAVE);
            while (tk.codigo == ELSEIF)
            {
                Consome(ELSEIF);
                Consome(ABRE_PAR);
                EXPR();
                Consome(FECHA_PAR);
                Consome(ABRE_CHAVE);
                CMD();
                Consome(FECHA_CHAVE);
            }
            if (tk.codigo == ELSE)
            {
                Consome(ELSE);
                Consome(ABRE_CHAVE);
                CMD();
                Consome(FECHA_CHAVE);
            }
            Consome(ENDIF);
            break;

        case WHILE:
            Consome(WHILE);
            Consome(ABRE_PAR);
            EXPR();
            Consome(FECHA_PAR);
            Consome(ABRE_CHAVE);
            CMD();
            Consome(FECHA_CHAVE);
            Consome(ENDWHILE);
            break;

        case GOBACK:
            Consome(GOBACK);
            break;

        case GETINT:
            Consome(GETINT);
            Consome(ID);
            break;

        case GETREAL:
            Consome(GETREAL);
            Consome(ID);
            break;

        case GETCHAR:
            Consome(GETCHAR);
            Consome(ID);
            break;

        case PUTINT:
            Consome(PUTINT);
            Consome(ID);
            break;

        case PUTREAL:
            Consome(PUTREAL);
            Consome(ID);
            break;

        case PUTCHAR:
            Consome(PUTCHAR);
            Consome(ID);
            break;

        default:
            errorSint(contLinha, "Opa! Comando inválido.");
        }
    }
    else if (tk.cat == ID)
    {
        ATRIB();
    }
    else
    {
        errorSint(contLinha, "Opa! Comando inválido.");
    }
}