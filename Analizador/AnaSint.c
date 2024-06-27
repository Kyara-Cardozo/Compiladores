#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "Analex.c"
#include "Analex.h"
#include "AnaSint.h"

void consome(int esperado)
{
    if (tk.cat == esperado || tk.codigo == esperado)
    {
        printf("[CONSOME][Entrada] - Cat: %d | Cod: %d | Lex: %s | Float: %0.2f | Int: %d\n", tk.cat, tk.codigo, tk.lexema, tk.valFloat, tk.valInt);
        tk = AnaLex(fd);
        printf("[CONSOME][Saida] - Cat: %d | Cod: %d | Lex: %s | Float: %0.2f | Int: %d\n", tk.cat, tk.codigo, tk.lexema, tk.valFloat, tk.valInt);
    }
    else
    {
        printf("[ERROR] - Cat: %d | Cod: %d | Lex: %s | Float: %0.2f | Int: %d\n", tk.cat, tk.codigo, tk.lexema, tk.valFloat, tk.valInt);
        char errMsg[100];
        sprintf(errMsg, "Token inesperado. Esperado: %d, Encontrado: %d", esperado, tk.codigo);
        errorSint(contLinha, errMsg);
    }
}

void prog()
{
    tk = AnaLex(fd);

    printf("PROG - Cat: %d | Cod: %d | Lex: %s | Float: %0.2f | Int: %d\n", tk.cat, tk.codigo, tk.lexema, tk.valFloat, tk.valInt);
    while (tk.cat == PAL_RESERV && (tk.codigo == CONST || tk.codigo == INT || tk.codigo == CHAR || tk.codigo == REAL || tk.codigo == BOOL))
    {
        decl_list_var();
    }

    while (tk.cat == PAL_RESERV && tk.codigo == BLOCK)
    {
        printf("[BLOCK][WHILE][Entrada]\n");
        decl_block_prot();
        printf("[BLOCK][WHILE][Saida]\n");
    }

    printf("PROG - Cat: %d | Cod: %d | Lex: %s | Float: %0.2f | Int: %d\n", tk.cat, tk.codigo, tk.lexema, tk.valFloat, tk.valInt);
    if (!(tk.cat == PAL_RESERV && tk.codigo == MAIN))
    {
        errorSint(contLinha, "Declaracao de bloco main esperada.");
    }

    block_main();

    while (tk.cat == PAL_RESERV && tk.codigo == BLOCK)
    {
        block_def();
    }

    if (tk.cat != FIM_PROG)
    {
        errorSint(contLinha, "Fim do Arquivo Esperado");
    }
}

void decl_list_var()
{
    printf("\nENTROU -> decl_list_var\n");

    if (tk.codigo == CONST)
    {
        consome(CONST);
    }
    tipo();
    decl_var();

    while (tk.codigo == VIR)
    {
        consome(VIR);
        decl_var();
    }

    printf("\nSAIU -> decl_list_var\n");
}

void decl_block_prot()
{
    printf("\nENTROU -> decl_block_prot\n");
    consome(BLOCK);

    if (tk.codigo != MAIN)
    {
        consome(ID);

        if (tk.codigo == WITH)
        {
            printf("[decl_block_prot][WITH][Entrada]\n\n");
            consome(WITH);

            while (true)
            {
                if (tk.cat == FIM_PROG || tk.codigo == MAIN || tk.codigo == BLOCK)
                {
                    break;
                }

                if (tk.codigo == REF)
                {
                    printf("[decl_block_prot][REF][Entrada]\n");
                    consome(REF);
                    printf("[decl_block_prot][REF][Saida]\n\n");
                }

                tipo();

                if (tk.codigo == ABRE_COL)
                {
                    printf("[decl_block_prot][ABRE_COL][Entrada]\n");
                    consome(ABRE_COL);
                    printf("[decl_block_prot][ABRE_COL][Saida]\n\n");

                    printf("[decl_block_prot][FECHA_COL][Entrada]\n");
                    consome(FECHA_COL);
                    printf("[decl_block_prot][FECHA_COL][Saida]\n\n");
                }
                if (tk.codigo == VIR)
                {
                    printf("[decl_block_prot][VIR][Entrada]\n");
                    consome(VIR);
                    printf("[decl_block_prot][VIR][Saida]\n\n");
                }
            }
            printf("[decl_block_prot][WITH][Saida]\n\n");
        }
    }

    printf("\nSAIU -> decl_block_prot\n");
}

void block_main()
{
    printf("\nENTROU -> block_main\n\n");
    consome(MAIN);

    while (tk.cat == PAL_RESERV && (tk.codigo == CONST || tk.codigo == INT || tk.codigo == CHAR || tk.codigo == REAL || tk.codigo == BOOL))
    {
        decl_list_var();
    }

    while (tk.codigo != ENDBLOCK)
    {
        cmd();
    }
    consome(ENDBLOCK);

    printf("\nSAIU -> block_main\n");
}

void block_def()
{
    printf("\nENTROU -> block_def\n");
    consome(BLOCK);
    consome(ID);

    if (tk.codigo == WITH)
    {
        consome(WITH);
        tipo();
        consome(ID);

        if (tk.codigo == ABRE_COL)
        {
            consome(ABRE_COL);
            if (tk.cat == CT_I || tk.cat == ID_CONST)
            {
                consome(tk.cat);
            }
            consome(FECHA_COL);
        }

        while (tk.codigo == VIR)
        {
            consome(VIR);
            tipo();
            consome(ID);
            if (tk.codigo == ABRE_COL)
            {
                consome(ABRE_COL);
                if (tk.cat == CT_I || tk.cat == ID_CONST)
                {
                    consome(tk.cat);
                }
                consome(FECHA_COL);
            }
        }
    }

    while (tk.cat == PAL_RESERV && (tk.codigo == CONST || tk.codigo == INT || tk.codigo == CHAR || tk.codigo == REAL || tk.codigo == BOOL))
    {
        decl_list_var();
    }

    while (tk.codigo != ENDBLOCK)
    {
        cmd();
        printf("<Resultado> Expressao OK!\n");
    }
    consome(ENDBLOCK);
    printf("\nSAIU -> block_def\n");
}

void tipo()
{
    printf("\nENTROU -> tipo\n");

    if (tk.codigo == CHAR || tk.codigo == INT || tk.codigo == REAL || tk.codigo == BOOL)
    {
        printf("[tipo][COD][Entrada]\n\n");
        consome(tk.codigo);
    }
    else
    {
        printf("[tipo][ERROR][Entrada]\n\n");
        errorSint(contLinha, "Tipo invalido");
    }
    printf("\nSAIU -> tipo\n");
}

void decl_var()
{
    printf("\nENTROU -> decl_var\n");
    consome(ID);

    while (tk.codigo == ABRE_COL)
    {
        printf("[decl_var][ABRE_COL][Entrada]\n\n");

        consome(ABRE_COL);
        if (tk.cat == CT_I || tk.cat == ID)
        {
            printf("[decl_var][CT_I][Entrada]\n\n");
            consome(tk.cat);
        }
        consome(FECHA_COL);
    }

    if (tk.codigo == ATRIBUICAO)
    {
        printf("[decl_var][ATRIBUICAO][Entrada]\n\n");
        consome(ATRIBUICAO);
        if (tk.cat == CT_I || tk.cat == CT_F || tk.cat == CT_C || tk.cat == LT)
        {
            printf("[decl_var][ATRIBUICAO][CAT][Entrada]\n\n");
            consome(tk.cat);
        }
        else if (tk.codigo == ABRE_CHAVE)
        {
            printf("[decl_var][ATRIBUICAO][ABRE_CHAVE][Entrada]\n\n");
            consome(ABRE_CHAVE);
            do
            {
                if (tk.cat == CT_I || tk.cat == CT_F || tk.cat == CT_C || tk.cat == LT)
                {
                    consome(tk.cat);
                }
                if (tk.codigo == VIR)
                {
                    consome(VIR);
                }
                else
                {
                    break;
                }
            } while (true);
            consome(FECHA_CHAVE);
        }
        else
        {
            printf("[decl_var][ATRIBUICAO][ERRO][Entrada]\n\n");
            errorSint(contLinha, "Valor esperado após '='.");
        }
        printf("[decl_var][ATRIBUICAO][Saida] - Cat: %d | Cod: %d | Lex: %s | Float: %0.2f | Int: %d\n", tk.cat, tk.codigo, tk.lexema, tk.valFloat, tk.valInt);
    }
    printf("\nSAIU -> decl_var\n");
}

void atrib()
{
    consome(ID);
    while (tk.codigo == ABRE_COL)
    {
        consome(ABRE_COL);
        expr();
        consome(FECHA_COL);
    }
    consome(ATRIBUICAO);
    expr();
}

void expr()
{
    printf("\nENTROU -> expr\n");
    expr_simp();
    if (tk.cat == OP_RELAC && (tk.codigo == IGUALDADE || tk.codigo == DIFERENTE || tk.codigo == MENOR_IGUAL ||
                               tk.codigo == MENOR || tk.codigo == MAIOR_IGUAL || tk.codigo == MAIOR))
    {
        op_rel();
        expr_simp();
    }
    printf("\nSAIU -> expr\n");
}

void expr_simp()
{
    printf("\nENTROU -> expr_simp\n");
    if (tk.codigo == SOMA || tk.codigo == SUBTRACAO)
    {
        consome(tk.codigo);
    }
    termo();

    if ((tk.codigo == SOMA || tk.codigo == SUBTRACAO || tk.codigo == OR))
    {
        consome(tk.codigo);
        termo();
    }

    printf("\nSAIU -> expr_simp\n");
}

void termo()
{
    printf("\nENTROU -> termo\n");
    if (tk.cat != FIM_PROG)
    {

        fator();
        while (tk.codigo == MULT || tk.codigo == DIV || tk.codigo == AND)
        {
            consome(tk.codigo);
            fator();
        }
    }
    printf("\nSAIU -> termo\n");
}

void fator()
{
    printf("\nENTROU -> fator\n");
    if (tk.cat == ID)
    {
        consome(ID);
        while (tk.codigo == ABRE_COL)
        {
            consome(ABRE_COL);
            expr();
            consome(FECHA_COL);
        }
    }
    else if (tk.cat == CT_I)
    {
        consome(CT_I);
    }
    else if (tk.cat == CT_F)
    {
        consome(CT_F);
    }
    else if (tk.cat == CT_C)
    {
        consome(CT_C);
    }
    else if (tk.codigo == ABRE_PAR)
    {
        consome(ABRE_PAR);
        expr();
        consome(FECHA_PAR);
    }
    else if (tk.codigo == NOT)
    {
        consome(NOT);
        fator();
    }
    printf("\nSAIU -> fator\n");
}

void op_rel()
{
    printf("\nENTROU -> op_rel\n");
    if (tk.codigo == IGUALDADE || tk.codigo == DIFERENTE || tk.codigo == MENOR_IGUAL ||
        tk.codigo == MENOR || tk.codigo == MAIOR_IGUAL || tk.codigo == MAIOR)
    {
        consome(tk.codigo);
    }
    else
    {
        errorSint(contLinha, "Operador relacional esperado");
    }
    printf("\nSAIU -> op_rel\n");
}

void cmd()
{
    if (tk.cat == PAL_RESERV)
    {
        switch (tk.codigo)
        {
        case DO:
            consome(DO);
            if (tk.cat == ID)
            {
                consome(ID);
                if (tk.codigo == WITH)
                {
                    consome(WITH);
                    consome(ID);
                    while (tk.codigo == VIR)
                    {
                        consome(VIR);
                        consome(ID);
                    }
                }
                if (tk.codigo == VARYING)
                {
                    consome(VARYING);
                    consome(ID);
                    consome(FROM);
                    expr();
                    if (tk.codigo == TO)
                    {
                        consome(TO);
                    }
                    else if (tk.codigo == DOWNTO)
                    {
                        consome(DOWNTO);
                    }
                    else
                    {
                        errorSint(contLinha, "Esperado 'to' ou 'downto'");
                    }
                    expr();
                }
                else if (tk.codigo == WHILE)
                {
                    consome(WHILE);
                    consome(ABRE_PAR);
                    expr();
                    consome(FECHA_PAR);
                }
                else if (tk.codigo == FOR)
                {
                    consome(FOR);
                    expr();
                }
            }
            else
            {
                cmd();
                if (tk.codigo == VARYING)
                {
                    consome(VARYING);
                    consome(ID);
                    consome(FROM);
                    expr();
                    if (tk.codigo == TO)
                    {
                        consome(TO);
                    }
                    else if (tk.codigo == DOWNTO)
                    {
                        consome(DOWNTO);
                    }
                    else
                    {
                        errorSint(contLinha, "Esperado 'to' ou 'downto'");
                    }
                    expr();
                }
                else if (tk.codigo == WHILE)
                {
                    consome(WHILE);
                    consome(ABRE_PAR);
                    expr();
                    consome(FECHA_PAR);
                }
                else if (tk.codigo == FOR)
                {
                    consome(FOR);
                    expr();
                }
            }
            break;

        case IF:
            consome(IF);
            consome(ABRE_PAR);
            expr();
            consome(FECHA_PAR);
            consome(ABRE_CHAVE);
            cmd();
            consome(FECHA_CHAVE);
            while (tk.codigo == ELSEIF)
            {
                consome(ELSEIF);
                consome(ABRE_PAR);
                expr();
                consome(FECHA_PAR);
                consome(ABRE_CHAVE);
                cmd();
                consome(FECHA_CHAVE);
            }
            if (tk.codigo == ELSE)
            {
                consome(ELSE);
                consome(ABRE_CHAVE);
                cmd();
                consome(FECHA_CHAVE);
            }
            consome(ENDIF);
            break;

        case WHILE:
            consome(WHILE);
            consome(ABRE_PAR);
            expr();
            consome(FECHA_PAR);
            consome(ABRE_CHAVE);
            cmd();
            consome(FECHA_CHAVE);
            consome(ENDWHILE);
            break;

        case GOBACK:
            consome(GOBACK);
            break;

        case GETINT:
            consome(GETINT);
            consome(ID);
            break;

        case GETREAL:
            consome(GETREAL);
            consome(ID);
            break;

        case GETCHAR:
            consome(GETCHAR);
            consome(ID);
            break;

        case PUTINT:
            consome(PUTINT);
            consome(ID);
            break;

        case PUTREAL:
            consome(PUTREAL);
            consome(ID);
            break;

        case PUTCHAR:
            consome(PUTCHAR);
            consome(ID);
            break;

        default:
            errorSint(contLinha, "Comando inválido.");
        }
    }
    else if (tk.cat == ID)
    {
        atrib();
    }
    else if (tk.cat != FIM_PROG)
    {
        errorSint(contLinha, "Comando inválido.");
    }
}