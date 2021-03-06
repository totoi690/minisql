#include"arquivo_tabela.h"
#include"filtro.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NUMCARACT (256)

tabela *alocaDadosTabela (int nlin, int ncol) {
    // CRIA UMA TABELA VAZIA
    tabela *dados_alocados = malloc (sizeof(tabela) * 1);
       if (dados_alocados == NULL){
            exit(-1);
        }
    dados_alocados -> dados = malloc (sizeof(char **) * nlin);
       if (dados_alocados -> dados == NULL){
            exit(-1);
        }
    for (int i = 0; i < nlin; i++){
        dados_alocados -> dados[i] = malloc (sizeof(char *) * ncol);
           if (dados_alocados -> dados[i] == NULL){
                exit(-1);
            }
        for (int j = 0; j < ncol; j++){
            dados_alocados -> dados[i][j] = malloc(sizeof(char) *  NUMCARACT);
        }
    }
    dados_alocados->nlin = nlin;
    dados_alocados->ncol = ncol;
    return dados_alocados;
}


void destruirTabela (tabela *tabela_utilizada, int nlin, int ncol){
    // DESALOCA A TABELA
    for (int i = 0; i < nlin; i++){
        for(int j = 0; j < ncol; j++){
            free(tabela_utilizada -> dados[i][j]);
        }
        free(tabela_utilizada -> dados[i]);
    }
    free(tabela_utilizada -> dados);
    free(tabela_utilizada);
}


tabela *abreArquivoCriaTabela (char *nome_arquivo) {
    // COLOCA INFORAMAÇÕES COMO NOME DO ARQUIVO E NUM LINHAS E NUM COLUNAS NA STRUCT
    int nlin, ncol;
    char extensao[] = ".tsv";
    char arquivo_atual[strlen(nome_arquivo) + strlen(extensao) + 1];
    int ext_cont = 0;
    for (int i = 0; i < strlen(nome_arquivo) + strlen(extensao) + 1; i++) {
        if (i < strlen(nome_arquivo)) {
            arquivo_atual[i] = nome_arquivo[i];
        } else {
            arquivo_atual[i] = extensao[ext_cont];
            ext_cont++;
        }
    }
    numLinColArquivo(arquivo_atual, &nlin, &ncol);
    FILE *fd;
    fd = fopen(arquivo_atual, "r");
    if (fd == NULL) {
        fprintf(stderr, "Erro ao abrir o %s\n", arquivo_atual);
        exit (-1);
    }
    tabela *tabela_arquivo;
    tabela_arquivo = alocaDadosTabela(nlin, ncol);
    pegaDadosArquivo(tabela_arquivo, fd);
    tabela_arquivo->arquivo = fd;
    strcpy(tabela_arquivo->nome_arquivo, nome_arquivo);
    return tabela_arquivo;
}


void pegaDadosArquivo (tabela *tabela_alocada, FILE *fd) {
    // COLOCA DADOS DE UM ARQUIVO EM UMA TABELA
    int i = 0;
    int j = 0;
    int k = 0;
    int fimlinha = 0;
    while(!feof(fd)){
        while(!fimlinha && !feof(fd)){
            do {
                tabela_alocada -> dados[i][j][k] = fgetc(fd);
                k++;
            } while(tabela_alocada -> dados[i][j][k - 1] != '\t' && tabela_alocada -> dados[i][j][k-1] != '\n' && !feof(fd));
            if (tabela_alocada -> dados[i][j][k - 1] == '\n'){
                fimlinha = 1;
            }
            tabela_alocada -> dados[i][j][k - 1] = '\0';
            k = 0;
            j++;
        }
        j = 0;
        i++;
        fimlinha = 0;
    }
}


void numLinColArquivo (char *arquivo, int *numLin, int *numcol){
    // LE UM ARQUIVO PARA PEGAR SUAS DIMENSOES (N. LINHAS E N. COLUNAS)
    char copia_arquivo[strlen(arquivo) + 1];
    strcpy(copia_arquivo, arquivo);
    FILE *fdlc;
    fdlc = fopen(copia_arquivo, "r");
    if (fdlc == NULL) {
        fprintf(stderr, "ERRO AO ABRIR %s\n", copia_arquivo);
        exit(-1);
    }
    char c;
    int lin = 0;
    int col = 0;
    int passou = 0;
    while(!feof(fdlc)){
        c = fgetc(fdlc);
        if(!passou && (c == '\t' || c == '\n')){
            col++;
        }

        if (c == '\n'){
            lin++;
            passou = 1;
        }
    }
    
    *numLin = lin + 1;
    *numcol = col;
    fclose(fdlc);
}

void liberarMallocsTam3 (char ***matriz_string, int tamanho_linha, int tamanho_coluna){
    // LIBERA MALLOC DE DIMENSAO 3
    for (int i = 0; i < tamanho_linha; i++){
        for (int j = 0; j < tamanho_coluna; j++){
            free(matriz_string[i][j]);
        }
        free(matriz_string[i]);
    }
    free(matriz_string);
}

void liberarMallocsTam2 (char **lista_string, int tamanho) {
    // LIBERA MALLOC DE DIMENSAO 2
    for (int i = 0; i < tamanho; i++) {
        free(lista_string[i]);
    }
    free(lista_string);
}