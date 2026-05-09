// Main.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "remedio.h"
#include "cliente.h"
#include "venda.h"
#include "utils.h"
#include <locale.h>

int main(){
    setlocale(LC_ALL,"portuguese");
    int op;
    Remedio *estoque = NULL;
    int qtd = 0;
    char nomeArquivo[] = "data/remedio.txt";
    qtd = carregarRemedio(&estoque, nomeArquivo);

    Cliente *clientes = NULL;
    int qtd_clientes = 0;
    char arquivoClientes[] = "data/cliente.txt";
    qtd_clientes = carregarCliente(&clientes, arquivoClientes);

    Venda *vendas = NULL;
    int qtd_vendas = 0;
    char arquivoVendas[] = "data/venda.txt";
    qtd_vendas = carregarVenda(&vendas, arquivoVendas);

    do{
        tela();
            printf("\n\t\tMENU PRINCIPAL \n\n");
           
            printf("1 - Gerenciar Remédios \n");
            printf("2 - Gerenciar Clientes\n");
            printf("3 - Gerenciar Vendas\n");
            printf("0 - Sair \n");
            linha();
            printf("\nInforme a opção desejada: ");
            scanf("%d", &op);

            switch (op)
            {
            case 1:
                menuRemedio(&estoque, &qtd, nomeArquivo);
                break;
            case 2:
                menuCliente(&clientes, &qtd_clientes, arquivoClientes);
                break;
            case 3:
                menuVendas(estoque, qtd, clientes, qtd_clientes, &vendas, arquivoVendas, &qtd_vendas);
                break;
            case 0:
                limparTela();
                printf("\nSaindo do sistema ... \n");
                break;
            default:
                printf("\nOpção inválida. \n");
                pausar();
                limparTela();
                break;
            }
    } while (op != 0);
    
        liberarEstoque(&estoque);
        liberarClientes(&clientes);
        liberarVendas(&vendas, qtd_vendas);
        
    pausar();
    return 0;
}