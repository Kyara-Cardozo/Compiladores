#include <stdio.h>
#include "compiler/src/Analisador Lexico/Analex.h"
#include "compiler/src/Analisador Lexico/Analex.h"

void processador_tokens(FILE *fd)
{
    TOKEN tk;
    while (1)
    {
        tk = Analex(fd);

        switch (tk.cat)
        {
        case ID:
            printf("<ID, %s>\n", tk.lexema);
            break;
        case CONST_INT:
            printf("<CONST_INT, %d>\n", tk.valInt);
            break;
        case CONST_FLOAT:
            printf("<CONST_FLOAT, %0.2f>\n", tk.valFloat);
            break;
        case CONST_CHAR:
            printf("<CONST_CHAR, %s>\n", tk.lexema);
            break;
        case LITERAL:
            printf("<LITERAL, %s>\n", tk.lexema);
            break;
        case FIM_EXPR:
            printf("<FIM EXPRESSAO>\n\n");
            break;
        case FIM_ARQ:
            printf("\nFIM DO ARQUIVO\n");
            return; 
        case ID_CONST: printf("\nID_CONST"); break;;
        case SINAL:
            switch (tk.codigo)
            {
            case VIRGULA:
                printf("<SN, VIRGULA>\n");
                break;
            case ABREPAR:
                printf("<SN, ABREPAR>\n");
                break;
            case FECHAPAR:
                printf("<SN, FECHAPAR>\n");
                break;
            case ABRECHAVE:
                printf("<SN, ABRECHAVE>\n");
                break;
            case FECHACHAVE:
                printf("<SN, FECHACHAVE>\n");
                break;
            case ABRECOL:
                printf("<SN, ABRECOL>\n");
                break;
            case FECHACOL:
                printf("<SN, FECHACOL>\n");
                break;
            case REFERENCIA:
                printf("<SN, REFERENCIA>\n");
                break;
            default:
                break;
            }
            break;
        case PAL_RESERV:
            switch (tk.codigo)
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
            switch (tk.codigo)
            {
            case ATRIBUICAO:
                printf("<OP_ARIT, ATRIBUICAO>\n");
                break;
            case ADICAO:
                printf("<OP_ARIT, ADICAO>\n");
                break;
            case SUBTRACAO:
                printf("<OP_ARIT, SUBTRACAO>\n");
                break;
            case MULTIPLICACAO:
                printf("<OP_ARIT, MULTIPLICACAO>\n");
                break;
            case DIVISAO:
                printf("<OP_ARIT, DIVISAO>\n");
                break;
            default:
                break;
            }
            break;
        case OP_LOGIC:
            switch (tk.codigo)
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
            switch (tk.codigo)
            {
            case IGUALDADE:
                printf("<OP_RELAC, IGUALDADE>\n");
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
        if (tk.cat == FIM_ARQ)
        {
            break;
        }
    }
}