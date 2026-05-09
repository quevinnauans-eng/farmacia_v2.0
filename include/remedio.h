#ifndef REMEDIO_H
#define REMEDIO_H

#define MAX 100

//Estrutura Rem�dio definida

typedef struct{
    int codigo;
    char nome[MAX];
    char laboratorio[MAX];
    float preco;
    int quant_estoque;

} Remedio;

// Prototipos das Fun��es

// Fun��es essenciais do sistema
void menuRemedio(Remedio **estoque, int *qtd, char nomeArquivo[]);
void cadastrarRemedio(Remedio **estoque, int *qtdRemedio);
void listarRemedios(Remedio *estoque, int qtdRemedio);
int buscarRemedioNome(Remedio *estoque, int qtdRemedio);
int buscarRemedioCodigo(Remedio *estoque, int qtdRemedio);
void removerRemedio(Remedio **estoque, int *qtdRemedio);
void atualizarRemedio(Remedio *estoque, int qtdRemedio);
int listarEstoqueBaixo(Remedio *estoque, int qtdRemedio);
int encontrarIndicePorNome(Remedio *estoque, int qtdRemedio, char nome[]);

void salvarRemedio(Remedio estoque[], char *nomeArquivo, int qtdRemedio);
int carregarRemedio(Remedio **estoque, char *nomeArquivo);

void liberarEstoque(Remedio **estoque);
int encontrarIndiceCodigo(Remedio *estoque, int qtdRemedio, int codigo);

#endif