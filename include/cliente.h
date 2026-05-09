#ifndef CLIENTE_H
#define CLIENTE_H

#define MAX 100

typedef struct{
    int codigo;
    char nome[MAX];
    char cpf[20];
    char telefone[20];

} Cliente;

void menuCliente(Cliente **clientes, int *qtdClientes, char arquivoClientes[]);
void cadastrarCliente(Cliente **clientes, int *qtdClientes);
void listarClientes(Cliente *clientes, int qtdClientes);
int buscarClienteNome(Cliente *clientes, int qtdClientes);
int buscarClienteCodigo(Cliente *clientes, int qtdClientes);
void removerCliente(Cliente **clientes, int *qtdClientes);
void atualizarCliente(Cliente *clientes, int qtdClientes);
void liberarClientes(Cliente **clientes);

void salvarCliente(Cliente clientes[], char *arquivoClientes, int qtdClientes);
int carregarCliente(Cliente **clientes, char *arquivoClientes);

// Funções de busca de indice
int procurarIndiceNome(Cliente *clientes, int qtdClientes, char nome[]);
int procurarIndiceCodigo(Cliente *clientes, int qtdClientes, int codigo);

#endif