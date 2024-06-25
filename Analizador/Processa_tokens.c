#include <stdio.h>
#include "AnaLex.h"
//#include "FuncAuxDoBlock.h"

void processa_tokens(FILE *fd)
{
    TOKEN t;
    while (1)
    {
        t = AnaLex(fd);

        switch (t.cat)
        {
        case ID:
            printf("<ID, %s>\n", t.lexema);
            break;
        case CONST_INT:
            printf("<CONST_INT, %d>\n", t.valInt);
            break;
        case CT_F:
            printf("<CT_F, %0.2f>\n", t.valFloat);
            break;
        case CT_C:
            printf("<CONST_CHAR, %s>\n", t.lexema);
            break;
        case LT:
            printf("<LITERAL, %s>\n", t.lexema);
            break;
        case FIM_EXPR:
            printf("<FIM EXPRESSAO>\n\n");
            break;
        case FIM_ARQ:
            printf("\nFIM DO ARQUIVO\n");
            return; 
        case SN:
            switch (t.codigo)
            {
            case VIRGULA:
                printf("<SN, VIRGULA>\n");
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
            case REFERENCIA:
                printf("<SN, REFERENCIA>\n");
                break;
            default:
                break;
            }
            break;
        case PR:
            switch (t.codigo)
            {
            case MAIN:
                printf("<PR, main>\n");
                break;
            case BLOCK:
                printf("<PR, block>\n");
                break;
            case ENDBLOCK:
                printf("<PR, endblock>\n");
                break;
            case CONST:
                printf("<PR, const>\n");
                break;
            case CHAR:
                printf("<PR, char>\n");
                break;
            case INT:
                printf("<PR, int>\n");
                break;
            case REAL:
                printf("<PR, real>\n");
                break;
            case BOOL:
                printf("<PR, bool>\n");
                break;
            case WITH:
                printf("<PR, with>\n");
                break;
            case DO:
                printf("<PR, do>\n");
                break;
            case VARYING:
                printf("<PR, varying>\n");
                break;
            case FROM:
                printf("<PR, from>\n");
                break;
            case TO:
                printf("<PR, to>\n");
                break;
            case DOWNTO:
                printf("<PR, downto>\n");
                break;
            case WHILE:
                printf("<PR, while>\n");
                break;
            case ENDWHILE:
                printf("<PR, endwhile>\n");
                break;
            case FOR:
                printf("<PR, for>\n");
                break;
            case IF:
                printf("<PR, if>\n");
                break;
            case ENDIF:
                printf("<PR, endif>\n");
                break;
            case ELSEIF:
                printf("<PR, elseif>\n");
                break;
            case ELSE:
                printf("<PR, else>\n");
                break;
            case GOBACK:
                printf("<PR, goback>\n");
                break;
            case GETCHAR:
                printf("<PR, getchar>\n");
                break;
            case PUTINT:
                printf("<PR, putint>\n");
                break;
            case GETINT:
                printf("<PR, getint>\n");
                break;
            case GETREAL:
                printf("<PR, getreal>\n");
                break;
            case PUTREAL:
                printf("<PR, putreal>\n");
                break;
            case PUTCHAR:
                printf("<PR, putchar>\n");
                break;
            default:
                break;
            }
            break;
        case OP_ARIT:
            switch (t.codigo)
            {
            case ATRIB:
                printf("<OP_ARIT, ATRIB>\n");
                break;
            case SOMA:
                printf("<OP_ARIT, SOMA>\n");
                break;
            case SUBTRACAO:
                printf("<OP_ARIT, SUBTRACAO>\n");
                break;
            case MULTIPLIC:
                printf("<OP_ARIT, MULTIPLIC>\n");
                break;
            case DIVISAO:
                printf("<OP_ARIT, DIVISAO>\n");
                break;
            default:
                break;
            }
            break;
        case OP_LOGIC:
            switch (t.codigo)
            {
            case AND_LOGIC:
                printf("<OP_LOGIC, AND_LOGIC>\n");
                break;
            case OR_LOGIC:
                printf("<OP_LOGIC, OR_LOGIC>\n");
                break;
            case NOT_LOGIC:
                printf("<OP_LOGIC, NOT_LOGIC>\n");
                break;
            default:
                break;
            }
            break;
        case OP_RELAC:
            switch (t.codigo)
            {
            case IGUAL:
                printf("<OP_RELAC, IGUAL>\n");
                break;
            case DIFERENTE:
                printf("<OP_RELAC, DIFERENTE>\n");
                break;
            case MENORIGUAL:
                printf("<OP_RELAC, MENORIGUAL>\n");
                break;
            case MAIORIGUAL:
                printf("<OP_RELAC, MAIORIGUAL>\n");
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
        if (t.cat == FIM_ARQ)
        {
            break;
        }
    }
}