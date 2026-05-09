#ifndef VENDA_H
#define VENDA_H
#include "cliente.h"
#include "remedio.h"

typedef struct {
   int codigoRemedio;
   int quantidade;
} ItemVenda;

typedef struct {
   int codigoVenda;
   int codigoCliente;
   ItemVenda *itens;      
   int quantidadeItens;  
} Venda;

void menuVendas(Remedio *estoque, int qtdRemedio, Cliente *clientes, int qtdClientes, Venda **vendas, char arquivoVendas[], int *qtdVendas);
void registrarVenda(Remedio *estoque, int qtdRemedio, Cliente *clientes, int qtdClientes, Venda **vendas, int *qtdVendas);
void listarVendas(Venda *vendas, int qtdVendas);
int buscarVenda(Venda *vendas, int qtdVendas);
int buscarIndiceCodigo(Venda *vendas, int qtdVendas, int codigo);
void liberarVendas(Venda **vendas, int qtdVendas);

void salvarVenda(Venda vendas[], char *arquivoVendas, int qtdVendas);
int carregarVenda(Venda **vendas, char *arquivoVendas);

#endif