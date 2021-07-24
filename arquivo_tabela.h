#ifndef __ARQUIVO_TABELA_H__
#define __ARQUIVO_TABELA_H__
#include<stdio.h>

typedef struct {
    int nlin;
    int ncol;
    char nome_arquivo[20];
    FILE *arquivo;
    char ***dados;
} tabela;

void destruirTabela (tabela *tabela_utilizada, int nlin, int ncol);

tabela *alocaDadosTabela (int nlin, int ncol);

tabela *abreArquivoCriaTabela (char *nome_arquivo);

void pegaDadosArquivo (tabela *tabela_alocada, FILE *fd);

void numLinColArquivo (char *arquivo, int *numLin, int *numcol);

#endif