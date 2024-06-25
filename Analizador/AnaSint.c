#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "AnaLex.c"
#include "AnaLex.h"
#include "AnaSint.h"

void Consome(int esperado)
{
    if (t.cat == esperado || t.codigo == esperado)
    {
        printf("[Consome][Entrada] - Cat: %d | Cod: %d | Lex: %s | Float: %0.2f | Int: %d\n", t.cat, t.codigo, t.lexema, t.valFloat, t.valInt);
        t = AnaLex(fd);
        printf("[Consome][Saida] - Cat: %d | Cod: %d | Lex: %s | Float: %0.2f | Int: %d\n", t.cat, t.codigo, t.lexema, t.valFloat, t.valInt);
    }
    else
    {
        printf("[ERROR] - Cat: %d | Cod: %d | Lex: %s | Float: %0.2f | Int: %d\n", t.cat, t.codigo, t.lexema, t.valFloat, t.valInt);
        char errMsg[100];
        sprintf(errMsg, "Opa! Token não esperado. Esperava:  %d, Encontrei: %d", esperado, t.codigo);
        errorSint(contLinha, errMsg);
    }
}

void PROG()
{
    t = AnaLex(fd);

    printf("PROG - Cat: %d | Cod: %d | Lex: %s | Float: %0.2f | Int: %d\n", t.cat, t.codigo, t.lexema, t.valFloat, t.valInt);
    while (t.cat == PR && (t.codigo == CONST || t.codigo == INT || t.codigo == CHAR || t.codigo == REAL || t.codigo == BOOL))
    {
        DECL_LIST_VAR();
    }

    while (t.cat == PR && t.codigo == BLOCK)
    {
        printf("[DECL_BLOCK_PROT][WHILE][Entrada]\n");
        DECL_BLOCK_PROT();
        printf("[DECL_BLOCK_PROT][WHILE][Saida]\n");
    }

    if (!(t.cat == PR && t.codigo == MAIN))
    {
        errorSint(contLinha, "Esperava declaração do bloco Main.");
    }

    BLOACK_MAIN();

    while (t.cat == PR && t.codigo == BLOCK)
    {
        BLOCK_DEF();
    }

    if (t.cat != FIM_ARQ)
    {
        errorSint(contLinha, "Esperava fim do arquivo.");
    }
}

void DECL_LIST_VAR()
{
    printf("\nENTROU -> DECL_LIST_VAR\n");

    if (t.codigo == CONST)
    {
        Consome(CONST);
    }
    TIPO();
    DECL_VAR();

    while (t.codigo == VIRGULA)
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

    if (t.codigo == WITH)
    {
        printf("[DECL_BLOCK_PROT][WITH][Entrada]\n\n");
        Consome(WITH);

        while (true)
        {
            if (t.cat == FIM_ARQ || t.codigo == BLOCK)
            {
                break;
            }

            if (t.codigo == REFERENCIA)
            {
                printf("[DECL_BLOCK_PROT][Referência][Entrada]\n");
                Consome(REFERENCIA);
                printf("[DECL_BLOCK_PROT][Referência][Saida]\n\n");
            }

            TIPO();

            if (t.codigo == ABRE_COL)
            {
                printf("[DECL_BLOCK_PROT][ABRE_COL][Entrada]\n");
                Consome(ABRE_COL);
                printf("[DECL_BLOCK_PROT][ABRE_COL][Saida]\n\n");

                printf("[DECL_BLOCK_PROT][FECHA_COL][Entrada]\n");
                Consome(FECHA_COL);
                printf("[DECL_BLOCK_PROT][FECHA_COL][Saida]\n\n");
            }
            if (t.codigo == VIRGULA)
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

    while (t.cat == PR && (t.codigo == CONST || t.codigo == INT || t.codigo == CHAR || t.codigo == REAL || t.codigo == BOOL))
    {
        DECL_LIST_VAR();
    }

    while (t.codigo != ENDBLOCK)
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

    if (t.codigo == WITH)
    {
        Consome(WITH);
        TIPO();
        Consome(ID);

        if (t.codigo == ABRE_COL)
        {
            Consome(ABRE_COL);
            if (t.cat == CONST_INT || t.cat == CONST_INT)
            {
                Consome(t.cat);
            }
            Consome(FECHA_COL);
        }

        while (t.codigo == VIRGULA)
        {
            Consome(VIRGULA);
            TIPO();
            Consome(ID);
            if (t.codigo == ABRE_COL)
            {
                Consome(ABRE_COL);
                if (t.cat == CONST_INT || t.cat == CONST_INT)
                {
                    Consome(t.cat);
                }
                Consome(FECHA_COL);
            }
        }
    }

    while (t.cat == PR && (t.codigo == CONST || t.codigo == INT || t.codigo == CHAR || t.codigo == REAL || t.codigo == BOOL))
    {
        DECL_LIST_VAR();
    }

    while (t.codigo != ENDBLOCK)
    {
        CMD();
    }
    Consome(ENDBLOCK);
    printf("\nSAIU -> BLOCK_DEF\n");
}

void TIPO()
{
    printf("\nENTROU -> TIPO\n");

    if (t.codigo == CHAR || t.codigo == INT || t.codigo == REAL || t.codigo == BOOL)
    {
        printf("[TIPO][COD][Entrada]\n\n");
        Consome(t.codigo);
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

    if (t.codigo == ABRE_COL)
    {
        printf("[DECL_VAR][ABRE_COL][Entrada]\n\n");

        Consome(ABRE_COL);
        if (t.cat == CONST_INT || t.cat == CONST_INT)
        {
            printf("[DECL_VAR][CONST_INT][Entrada]\n\n");
            Consome(t.cat);
        }
        Consome(FECHA_COL);
    }

    if (t.codigo == ATRIB)
    {
        printf("[DECL_VAR][ATRIB][Entrada]\n\n");
        Consome(ATRIB);
        if (t.cat == CONST_INT || t.cat == CT_F || t.cat == CT_C || t.cat == LT)
        {
            printf("[DECL_VAR][ATRIB][CAT][Entrada]\n\n");
            Consome(t.cat);
        }
        else if (t.codigo == ABRE_CHAVE)
        {
            printf("[DECL_VAR][ATRIB][ABRE_CHAVE][Entrada]\n\n");
            Consome(ABRE_CHAVE);
            do
            {
                if (t.cat == CONST_INT || t.cat == CT_F || t.cat == CT_C || t.cat == LT)
                {
                    Consome(t.cat);
                }
                if (t.codigo == VIRGULA)
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
        printf("[DECL_VAR][ATRIB][Saida] - Cat: %d | Cod: %d | Lex: %s | Float: %0.2f | Int: %d\n", t.cat, t.codigo, t.lexema, t.valFloat, t.valInt);
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
    if (t.cat == esperado || t.codigo == esperado)
    {
        printf("Consome entrada - Cat: %d | Cod: %d | Lex: %s | Float: %0.2f | Int: %d\n", t.cat, t.codigo, t.lexema, t.valFloat, t.valInt);
        t = AnaLex(fd);
        printf("Consome saida - Cat: %d | Cod: %d | Lex: %s | Float: %0.2f | Int: %d\n", t.cat, t.codigo, t.lexema, t.valFloat, t.valInt);
    }
    else
    {
        printf("Cat: %d | Cod: %d | Lex: %s | Float: %0.2f | Int: %d\n", t.cat, t.codigo, t.lexema, t.valFloat, t.valInt);
        char errMsg[100];
        sprintf(errMsg, "Opa! Token não esperado. Esperava:  %d, Encontrei: %d", esperado, t.codigo);
        errorSint(contLinha, errMsg);
    }
}

void PROG()
{
    t = AnaLex(fd);

    printf("PROG - Cat: %d | Cod: %d | Lex: %s | Float: %0.2f | Int: %d\n", t.cat, t.codigo, t.lexema, t.valFloat, t.valInt);
    while (t.cat == PR && (t.codigo == CONST || t.codigo == INT || t.codigo == CHAR || t.codigo == REAL || t.codigo == BOOL))
    {
        printf("\nENTROU -> DECL_LIST_VAR\n");
        DECL_LIST_VAR();
    }

    while (t.cat == PR && t.codigo == BLOCK)
    {
        printf("\nENTROU -> DECL_BLOCK_PROT\n");
        DECL_BLOCK_PROT();
    }

    if (!(t.cat == PR && t.codigo == MAIN))
    {
        errorSint(contLinha, "Esperava declaração do bloco Main.");
    }

    BLOACK_MAIN();

    while (t.cat == PR && t.codigo == BLOCK)
    {
        BLOCK_DEF();
    }

    if (t.cat != FIM_ARQ)
    {
        errorSint(contLinha, "Esperava fim do arquivo.");
    }
}

void DECL_LIST_VAR()
{
    if (t.codigo == CONST)
    {
        Consome(CONST);
    }
    TIPO();
    DECL_VAR();

    while (t.codigo == VIRGULA)
    {
        Consome(VIRGULA);
        DECL_VAR();
    }
}

void DECL_BLOCK_PROT()
{
    Consome(BLOCK);
    Consome(ID);

    if (t.codigo == WITH)
    {
        Consome(WITH);

        do
        {
            Consome(REFERENCIA);
            TIPO();
            if (t.codigo == ABRE_COL)
            {
                Consome(ABRE_COL);
                Consome(FECHA_COL);
            }
            if (t.codigo == VIRGULA)
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

    while (t.cat == PR && (t.codigo == CONST || t.codigo == INT || t.codigo == CHAR || t.codigo == REAL || t.codigo == BOOL))
    {
        DECL_LIST_VAR();
    }

    while (t.codigo != ENDBLOCK)
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

    if (t.codigo == WITH)
    {
        Consome(WITH);
        TIPO();
        Consome(ID);

        if (t.codigo == ABRE_COL)
        {
            Consome(ABRE_COL);
            if (t.cat == CONST_INT || t.cat == CONST_INT)
            {
                Consome(t.cat);
            }
            Consome(FECHA_COL);
        }

        while (t.codigo == VIRGULA)
        {
            Consome(VIRGULA);
            TIPO();
            Consome(ID);
            if (t.codigo == ABRE_COL)
            {
                Consome(ABRE_COL);
                if (t.cat == CONST_INT || t.cat == CONST_INT)
                {
                    Consome(t.cat);
                }
                Consome(FECHA_COL);
            }
        }
    }

    while (t.cat == PR && (t.codigo == CONST || t.codigo == INT || t.codigo == CHAR || t.codigo == REAL || t.codigo == BOOL))
    {
        DECL_LIST_VAR();
    }

    while (t.codigo != ENDBLOCK)
    {
        break;
        // CMD();
    }
    Consome(ENDBLOCK);
}

void TIPO()
{
    printf("\nENTROU -> TIPO\n");
    printf("Tipo entrada - Cat: %d | Cod: %d | Lex: %s | Float: %0.2f | Int: %d\n", t.cat, t.codigo, t.lexema, t.valFloat, t.valInt);

    if (t.codigo == CHAR || t.codigo == INT || t.codigo == REAL || t.codigo == BOOL)
    {
        printf("Tipo Dentro - Cat: %d | Cod: %d | Lex: %s | Float: %0.2f | Int: %d\n", t.cat, t.codigo, t.lexema, t.valFloat, t.valInt);
        Consome(t.codigo);
    }
    else
    {
        errorSint(contLinha, "Opa! Tipo invalido. ");
    }
}

void DECL_VAR()
{
    printf("\nENTROU -> DECL_VAR\n");
    printf("DECL_VAR Entrada - Cat: %d | Cod: %d | Lex: %s | Float: %0.2f | Int: %d\n", t.cat, t.codigo, t.lexema, t.valFloat, t.valInt);
    Consome(ID);

    if (t.codigo == ABRE_COL)
    {
        Consome(ABRE_COL);
        if (t.cat == CONST_INT || t.cat == CONST_INT)
        {
            Consome(t.cat);
        }
        Consome(FECHA_COL);
    }

    if (t.codigo == ATRIB)
    {
        printf("ATRIB Entrada - Cat: %d | Cod: %d | Lex: %s | Float: %0.2f | Int: %d\n", t.cat, t.codigo, t.lexema, t.valFloat, t.valInt);
        Consome(ATRIB);
        if (t.cat == CONST_INT || t.cat == CT_F || t.cat == CT_C || t.cat == LT)
        {
            printf("CONSTANTES Entrada - Cat: %d | Cod: %d | Lex: %s | Float: %0.2f | Int: %d\n", t.cat, t.codigo, t.lexema, t.valFloat, t.valInt);
            Consome(t.cat);
        }
        else if (t.codigo == ABRE_CHAVE)
        {
            Consome(ABRE_CHAVE);
            do
            {
                if (t.cat == CONST_INT || t.cat == CT_F || t.cat == CT_C || t.cat == LT)
                {
                    Consome(t.cat);
                }
                if (t.codigo == VIRGULA)
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
        printf("ATRIB Saida - Cat: %d | Cod: %d | Lex: %s | Float: %0.2f | Int: %d\n", t.cat, t.codigo, t.lexema, t.valFloat, t.valInt);
    }
}

void ATRIB()
{
    Consome(ID);
    while (t.codigo == ABRE_COL)
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
    if (t.codigo == IGUAL || t.codigo == DIFERENTE || t.codigo == MENORIGUAL ||
        t.codigo == MENOR || t.codigo == MAIORIGUAL || t.codigo == MAIOR)
    {
        OPERADOR_REL();
        EXPR_SIMP();
    }
}

void EXPR_SIMP()
{
    if (t.codigo == SOMA || t.codigo == SUBTRACAO)
    {
        Consome(t.codigo);
    }
    TERMO();
    while (t.codigo == SOMA || t.codigo == SUBTRACAO || t.codigo == OR_LOGIC)
    {
        Consome(t.codigo);
        TERMO();
    }
}

void TERMO()
{
    FATOR();
    while (t.codigo == MULTIPLIC || t.codigo == DIVISAO || t.codigo == AND_LOGIC)
    {
        Consome(t.codigo);
        FATOR();
    }
}

void FATOR()
{
    if (t.cat == ID)
    {
        Consome(ID);
        while (t.codigo == ABRE_COL)
        {
            Consome(ABRE_COL);
            EXPR();
            Consome(FECHA_COL);
        }
    }
    else if (t.cat == CONST_INT)
    {
        Consome(CONST_INT);
    }
    else if (t.cat == CT_F)
    {
        Consome(CT_F);
    }
    else if (t.cat == CT_C)
    {
        Consome(CT_C);
    }
    else if (t.codigo == ABRE_PAR)
    {
        Consome(ABRE_PAR);
        EXPR();
        Consome(FECHA_PAR);
    }
    else if (t.codigo == NOT_LOGIC)
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
    if (t.codigo == IGUAL || t.codigo == DIFERENTE || t.codigo == MENORIGUAL ||
        t.codigo == MENOR || t.codigo == MAIORIGUAL || t.codigo == MAIOR)
    {
        Consome(t.codigo);
    }
    else
    {
        errorSint(contLinha, "Operador relacional esperado");
    }
}

void CMD()
{
    if (t.cat == PR)
    {
        switch (t.codigo)
        {
        case DO:
            Consome(DO);
            if (t.cat == ID)
            {
                Consome(ID);
                if (t.codigo == WITH)
                {
                    Consome(WITH);
                    Consome(ID);
                    while (t.codigo == VIRGULA)
                    {
                        Consome(VIRGULA);
                        Consome(ID);
                    }
                }
                if (t.codigo == VARYING)
                {
                    Consome(VARYING);
                    Consome(ID);
                    Consome(FROM);
                    EXPR();
                    if (t.codigo == TO)
                    {
                        Consome(TO);
                    }
                    else if (t.codigo == DOWNTO)
                    {
                        Consome(DOWNTO);
                    }
                    else
                    {
                        errorSint(contLinha, "Esperado 'to' ou 'downto'");
                    }
                    EXPR();
                }
                else if (t.codigo == WHILE)
                {
                    Consome(WHILE);
                    Consome(ABRE_PAR);
                    EXPR();
                    Consome(FECHA_PAR);
                }
                else if (t.codigo == FOR)
                {
                    Consome(FOR);
                    EXPR();
                }
            }
            else
            {
                CMD();
                if (t.codigo == VARYING)
                {
                    Consome(VARYING);
                    Consome(ID);
                    Consome(FROM);
                    EXPR();
                    if (t.codigo == TO)
                    {
                        Consome(TO);
                    }
                    else if (t.codigo == DOWNTO)
                    {
                        Consome(DOWNTO);
                    }
                    else
                    {
                        errorSint(contLinha, "Esperado 'to' ou 'downto'");
                    }
                    EXPR();
                }
                else if (t.codigo == WHILE)
                {
                    Consome(WHILE);
                    Consome(ABRE_PAR);
                    EXPR();
                    Consome(FECHA_PAR);
                }
                else if (t.codigo == FOR)
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
            while (t.codigo == ELSEIF)
            {
                Consome(ELSEIF);
                Consome(ABRE_PAR);
                EXPR();
                Consome(FECHA_PAR);
                Consome(ABRE_CHAVE);
                CMD();
                Consome(FECHA_CHAVE);
            }
            if (t.codigo == ELSE)
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
    else if (t.cat == ID)
    {
        ATRIB();
    }
    else
    {
        errorSint(contLinha, "Opa! Comando inválido.");
    }
}