#ifndef __ARQUIVO_TABELA_H__
#define __ARQUIVO_TABELA_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void imprimirTabelaResultado (tabela **tabelas, char *colunas_selecionadas[], int num_arquivos, int num_colunas);

void liberarMallocsTam3 (char ***matriz_string, int tamanho_linha, int tamanho_coluna);

void liberarMallocsTam2 (char **lista_string, int tamanho);

#endif