#include"arquivo_tabela.h"
#include"nova_string.h"
#include"filtro.h"
#define PASSOUAQUI printf("%s:%d\n", __FILE__, __LINE__);

int main(void) {
    char input[1024];
    fgets(input, 1024, stdin);
    int tem_where = 1;
    char str_select[384], str_from[128], str_where[512];

    substring(input, str_select, "select ", "from");
    if (substring(input, str_from, "from ", "where")) {
        substring(input, str_where, "where ", "\0");
    } else {
        substring(input, str_from, "from ", "\0");
        tem_where = 0;
    }
    PASSOUAQUI
    int num_arquivos = contaOcorrenciasString(str_from, ", ");
    char nomes_arquivos[num_arquivos][20];
    char *tok;
    tok = strtok(str_from, ", ");
    int count = 0;
    while (tok != 0) {
        strcpy(nomes_arquivos[count], tok);
        tok = strtok(0, ", ");
        count++;
    }

    tabela *tabelas[num_arquivos];
    PASSOUAQUI
    for (int i = 0; i < num_arquivos; i++) {
        tabelas[i] = abreArquivoCriaTabela(nomes_arquivos[i]);
    }

    for (int i = 0; i < num_arquivos; i++) {
        printf("[%s]\n", tabelas[i]->nome_arquivo);
    }
    PASSOUAQUI
    int num_colunas_selecionadas = contaOcorrenciasString(str_select, ", ");
    char colunas_selecionadas[num_colunas_selecionadas][50];
    char *tok1;
    tok1 = strtok(str_select, ", ");
    int count1 = 0;
    while (tok1 != 0) {
        strcpy(colunas_selecionadas[count1], tok1);
        tok1 = strtok(0, ", ");
        count1++;
    }
    // for (int i = 0; i < num_colunas_selecionadas; i++) {
    //     printf("[%s ()]\n", colunas_selecionadas[i], indexColunaSelecionada(tabelas, num_arquivos, colunas_selecionadas[i]));
    // }

    for (int i = 0; i < num_arquivos; i++) {
        destruirTabela(tabelas[i], tabelas[i]->nlin, tabelas[i]->ncol);
        fclose(tabelas[i]->arquivo);
    }
}