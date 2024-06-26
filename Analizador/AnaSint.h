#ifndef ANASINT_H
#define ANASINT_H

#include "Analex.h"
#include <stdbool.h>
#include <stdio.h>


extern TOKEN t;
extern FILE *fd;
extern int contLinha;

extern bool mostraArvore;
extern char TABS[200];


void PROG();            // prog ::= {DECL_LIST_VAR} {DECL_BLOCK_PROT} BLOACK_MAIN {BLOCK_DEF}
void DECL_LIST_VAR();   // DECL_LIST_VAR ::= [const] TIPO DECL_VAR { , DECL_VAR}
void DECL_BLOCK_PROT(); // DECL_BLOCK_PROT ::= block id [with [&] TIPO { [ ] } { , [&] TIPO { [ ] } }]
void BLOACK_MAIN();      // BLOACK_MAIN ::= block main {DECL_LIST_VAR} { CMD } endblock
void DECL_VAR();        // DECL_VAR ::= id {[ intcon | idconst ]} [ = (intcon | realcon | charcon | stringcon | { (intcon | realcon | charcon | stringcon) {, (intcon | realcon | charcon | stringcon) } } ) ]
void TIPO();            // TIPO ::= char | int | real | bool
void BLOCK_DEF();       // BLOCK_DEF ::= block id [with TIPO id1 { [intcon1 | idconst1] } { , TIPO id2 { [intcon2 | idconst2] } }] {DECL_LIST_VAR} { CMD } endblock
void CMD();             // CMD ::= do (id [with id1 { , id2 }] | CMD ) varying idx from EXPR1 (to | downto) EXPR2
                        //       | do (id [with id1 { , id2 }] | CMD ) while ( EXPR )
                        //       | do (id [with id1 { , id2 }] | CMD ) [for EXPR times ]
                        //       | if ( EXPR ) { CMD }{ elseif ( EXPR ) { CMD } } [ else { CMD }] endif
                        //       | while ( EXPR ) { CMD } endwhile
                        //       | ATRIB
void ATRIBUICAO();           // Atribuição
void EXPR();            // Expressão
void EXPR_SIMP();       // Expressão simples
void TERMO();           // Termo
void FATOR();           // Fator
void OPERADOR_REL();          // Operador relacional

#endif 