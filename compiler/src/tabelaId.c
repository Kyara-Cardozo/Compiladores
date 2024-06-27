#include <stdlib.h>
#include <string.h>
#include "Funcaux.h"
#include "tabelaId.h"

void InicializarTabelaId() {
    tabelaId.tabSize = 0;
}

int BuscaIdTabela(char NomeId[]) {
    int i;
    for (i = 0; i < tabelaId.tabSize; i++) {
        if (!(strcmp(NomeId, tabelaId.id[i].NomeId))) return i;
    }
    return -1;
}

int InsertIdTable(char NomeId[], bool is_const, int escopo, enum TOKEN_CAT cat) {
    int i;
    if (tabelaId.tabSize == ID_TAB_TAMANHO_MAXIMO) exibirErro("ID Stack Overflow!");
    i = tabelaId.tabSize;
    strcpy(tabelaId.id[i].NomeId, NomeId);
    tabelaId.id[i].endereco = i;
    tabelaId.tabSize++;
    return i;
}

void setZombie(char NomeId[], bool estado) {
    int i = BuscaIdTabela(NomeId);
    tabelaId.id[i].zombie = estado;
}
