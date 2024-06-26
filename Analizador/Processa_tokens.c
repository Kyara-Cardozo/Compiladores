#include <stdio.h>
#include "Analex.h"
#include "FuncAux.h"

void processa_tokens(FILE *fd)
{
    TOKEN tk;
    while (1)
    {
        tk = AnaLex(fd);

        switch (tk.cat)
        {
        case ID:
            printf("<ID, %s>\n", tk.lexema);
            break;
        case CT_I:
            printf("<CONST_INT, %d>\n", tk.valInt);
            break;
        case CT_F:
            printf("<CT_F, %0.2f>\n", tk.valFloat);
            break;
        case CT_C:
            printf("<CONST_CHAR, %s>\n", tk.lexema);
            break;
        case LT:
            printf("<LITERAL, %s>\n", tk.lexema);
            break;
        case FIM_EXPR:
            printf("<FIM EXPAL_RESERVESSAO>\n\n");
            break;
        case FIM_PROG:
            printf("\nFIM DO ARQUIVO\n");
            return; 
        case SN:
            switch (tk.codigo)
            {
            case VIR:
                printf("<SN, VIR>\n");
                break;
            case ABRE_PAR:
                printf("<SN, ABRE_PAR>\n");
                break;
            case FECHA_PAR:
                printf("<SN, FECHA_PAR>\n");
                break;
            case ABRE_CHAVE:
                printf("<SN, ABRE_CHAVE>\n");
                break;
            case FECHA_CHAVE:
                printf("<SN, FECHA_CHAVE>\n");
                break;
            case ABRE_COL:
                printf("<SN, ABRE_COL>\n");
                break;
            case FECHA_COL:
                printf("<SN, FECHA_COL>\n");
                break;
            case REF:
                printf("<SN, REF>\n");
                break;
            default:
                break;
            }
            break;
        case PAL_RESERV:
            switch (tk.codigo)
            {
            case MAIN:
                printf("<PAL_RESERV, main>\n");
                break;
            case BLOCK:
                printf("<PAL_RESERV, block>\n");
                break;
            case ENDBLOCK:
                printf("<PAL_RESERV, endblock>\n");
                break;
            case CONST:
                printf("<PAL_RESERV, const>\n");
                break;
            case CHAR:
                printf("<PAL_RESERV, char>\n");
                break;
            case INT:
                printf("<PAL_RESERV, int>\n");
                break;
            case REAL:
                printf("<PAL_RESERV, real>\n");
                break;
            case BOOL:
                printf("<PAL_RESERV, bool>\n");
                break;
            case WITH:
                printf("<PAL_RESERV, with>\n");
                break;
            case DO:
                printf("<PAL_RESERV, do>\n");
                break;
            case VARYING:
                printf("<PAL_RESERV, varying>\n");
                break;
            case FROM:
                printf("<PAL_RESERV, from>\n");
                break;
            case TO:
                printf("<PAL_RESERV, to>\n");
                break;
            case DOWNTO:
                printf("<PAL_RESERV, downto>\n");
                break;
            case WHILE:
                printf("<PAL_RESERV, while>\n");
                break;
            case ENDWHILE:
                printf("<PAL_RESERV, endwhile>\n");
                break;
            case FOR:
                printf("<PAL_RESERV, for>\n");
                break;
            case IF:
                printf("<PAL_RESERV, if>\n");
                break;
            case ENDIF:
                printf("<PAL_RESERV, endif>\n");
                break;
            case ELSEIF:
                printf("<PAL_RESERV, elseif>\n");
                break;
            case ELSE:
                printf("<PAL_RESERV, else>\n");
                break;
            case GOBACK:
                printf("<PAL_RESERV, goback>\n");
                break;
            case GETCHAR:
                printf("<PAL_RESERV, getchar>\n");
                break;
            case PUTINT:
                printf("<PAL_RESERV, putint>\n");
                break;
            case GETINT:
                printf("<PAL_RESERV, getint>\n");
                break;
            case GETREAL:
                printf("<PAL_RESERV, getreal>\n");
                break;
            case PUTREAL:
                printf("<PAL_RESERV, putreal>\n");
                break;
            case PUTCHAR:
                printf("<PAL_RESERV, putchar>\n");
                break;
            default:
                break;
            }
            break;
        case OP_ARIT:
            switch (tk.codigo)
            {
            case ATRIBUICAO:
                printf("<OP_ARIT, ATRIBUICAO>\n");
                break;
            case SOMA:
                printf("<OP_ARIT, SOMA>\n");
                break;
            case SUBTRACAO:
                printf("<OP_ARIT, SUBTRACAO>\n");
                break;
            case MULT:
                printf("<OP_ARIT, MULT>\n");
                break;
            case DIV:
                printf("<OP_ARIT, DIV>\n");
                break;
            default:
                break;
            }
            break;
        case OP_LOGIC:
            switch (tk.codigo)
            {
            case AND:
                printf("<OP_LOGIC, AND>\n");
                break;
            case OR:
                printf("<OP_LOGIC, OR>\n");
                break;
            case NOT:
                printf("<OP_LOGIC, NOT>\n");
                break;
            default:
                break;
            }
            break;
        case OP_RELAC:
            switch (tk.codigo)
            {
            case IGUALDADE:
                printf("<OP_RELAC, IGUAL>\n");
                break;
            case DIFERENTE:
                printf("<OP_RELAC, DIFERENTE>\n");
                break;
            case MENOR_IGUAL:
                printf("<OP_RELAC, MENOR_IGUAL>\n");
                break;
            case MAIOR_IGUAL:
                printf("<OP_RELAC, MAIOR_IGUAL>\n");
                break;
            case MENOR:
                printf("<OP_RELAC, MENOR>\n");
                break;
            case MAIOR:
                printf("<OP_RELAC, MAIOR>\n");
                break;
            default:
                break;
            }
            break;
        }
        if (tk.cat == FIM_PROG)
        {
            break;
        }
    }
}