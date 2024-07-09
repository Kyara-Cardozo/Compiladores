#ifndef ANASINT_H
#define ANASINT_H

#include "Analex.h"
#include <stdbool.h>
#include <stdio.h>


extern TOKEN tk;
extern FILE *fd;
extern int contaLinha;
extern int escopoAtual;

extern bool mostraArvore;
extern char Tabulacao[200];

// Funções do analisador sintático
void program();            // prog ::= {decl_list_var} {decl_block_prot} block_main {block_def}
void decl_list_var();   // decl_list_var ::= [const] tipo decl_var { , decl_var}
void decl_block_prot(); // decl_block_prot ::= block id [with [&] tipo { [ ] } { , [&] tipo { [ ] } }]
void block_main();      // block_main ::= block main {decl_list_var} { cmd } endblock
void decl_var();        // decl_var ::= id {[ intcon | idconst ]} [ = (intcon | realcon | charcon | stringcon | { (intcon | realcon | charcon | stringcon) {, (intcon | realcon | charcon | stringcon) } } ) ]
void tipo();            // tipo ::= char | int | real | bool
void block_def();       // block_def ::= block id [with tipo id1 { [intcon1 | idconst1] } { , tipo id2 { [intcon2 | idconst2] } }] {decl_list_var} { cmd } endblock
void cmd();             // cmd ::= do (id [with id1 { , id2 }] | cmd ) varying idx from expr1 (to | downto) expr2
                        //       | do (id [with id1 { , id2 }] | cmd ) while ( expr )
                        //       | do (id [with id1 { , id2 }] | cmd ) [for expr times ]
                        //       | if ( expr ) { cmd }{ elseif ( expr ) { cmd } } [ else { cmd }] endif
                        //       | while ( expr ) { cmd } endwhile
                        //       | atrib
void atrib();           // Atribuição
void expr();            // Expressão
void expr_simp();       // Expressão simples
void termo();           // Termo
void fator();           // Fator
void op_rel();          // Operador relacional

#endif 