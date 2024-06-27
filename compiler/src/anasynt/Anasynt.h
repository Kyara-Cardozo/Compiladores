#ifndef _ANASYNT_
#define _ANASYNT_

#include <stdio.h>
#include <stdlib.h>
#include "../analex/Analex.h"


extern TOKEN t;
extern TOKEN tkLA;
extern FILE *fd;
extern int ContadorLinha;

extern bool bExibirArvore;
extern char Tabulacao[200];

void Aplicacao();
void Decl_list_var();
void Decl_block_prot();
void Block_main();
void Decl_var();
void Tipo();
void Block_def();
void Cmd();
void Atrib();
void Expressao();
void Expr_simp();
void Termo();
void Fator();
void Op_rel();

#endif