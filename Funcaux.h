#ifndef _FUNC_AUX_
#define _FUNC_AUX_

#include <stdbool.h>

enum MOVIM {A_FRENTE, PERMANECER, PARA_TRAS};

extern bool bExibirArvore;
extern char Tabulacao[200];
extern int ContadorLinha;

void exibirErro(char msg[]);
void PrintarNo(char info[], int mover);
void PrintarNoInteiro(int valor, int mover);
void ChecarToken();

#endif
