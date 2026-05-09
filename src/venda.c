#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "venda.h"
#include "cliente.h"
#include "utils.h"
#include "remedio.h"

void menuVendas(Remedio *estoque, int qtdRemedio, Cliente *clientes, int qtdClientes, Venda **vendas, char arquivoVendas[], int *qtdVendas){
    int op, encontrou;

    do
    {
        tela();
            printf("\n\t\tMENU DE VENDAS\n");
            linha();
            printf("\n1 - Registrar venda\n");
            printf("2 - Listar vendas\n");
            printf("3 - Buscar venda\n");
            printf("4 - Salvar vendas\n");
            printf("0 - Voltar\n");
            linha();
            printf("\nInforme a opção desejada: ");
            scanf("%d", &op);

            switch (op)
            {
            case 1:
                if(qtdClientes == 0 || qtdRemedio == 0){
                    printf("\nCadastre clientes e remédios antes de registrar venda!\n");
                    pausar();
                }
                else{
                registrarVenda(estoque, qtdRemedio, clientes, qtdClientes, vendas, qtdVendas);
                }
                break;
            case 2:
                listarVendas(*vendas, *qtdVendas);
                break;
            case 3:
                encontrou = buscarVenda(*vendas, *qtdVendas);
                if(encontrou != -1){
                    printf("\nBusca realizada com sucesso!\n");
                    printf("Posição da venda do vetor: %d\n", encontrou + 1);
                    linha();
                } else{
                    printf("\nPosição não encontrada! \n");
                }
                pausar();
                break;
            case 4:
                limparTela();
                salvarVenda(*vendas, arquivoVendas, *qtdVendas);
                printf("\nSalvando alterações ...\n");
                pausar();
                break;
            case 0:
                limparTela();
                salvarVenda(*vendas, arquivoVendas, *qtdVendas);
                printf("\nVoltando do menu vendas ...\n");
                pausar();
                break;
            default:
                limparTela();
                printf("\nOpção inválida! \n");
                pausar();
                break;
            }
    } while (op != 0);
        
}
void registrarVenda(Remedio *estoque, int qtdRemedio, Cliente *clientes, int qtdClientes, Venda **vendas, int *qtdVendas){
    int cod_cliente, cod_remedio;
    int buscarCliente, buscarRemedio;
    int continuar = 1, quantidade;
    Venda novaVenda;

    tela();
        printf("\nREGISTRAR VENDA:\n\n");

        if(qtdClientes == 0 || qtdRemedio == 0){
            printf("\nDados insuficientes para realizar uma venda.\n");
            pausar();
            return;
        }
        printf("Informe o código do cliente: ");
        scanf("%d", &cod_cliente);
        limparBuffer();

            buscarCliente = procurarIndiceCodigo(clientes, qtdClientes, cod_cliente);
            if(buscarCliente == -1){
                printf("\nCliente não foi encontrado\n");
                pausar();
                return;
            }
            novaVenda.codigoCliente = cod_cliente;
            novaVenda.codigoVenda = *qtdVendas + 1;
            novaVenda.itens = NULL;
            novaVenda.quantidadeItens = 0;

            while (continuar)
            {
                printf("Informe o código do Remédio: ");
                scanf("%d", &cod_remedio);
                limparBuffer();

                buscarRemedio = encontrarIndiceCodigo(estoque, qtdRemedio, cod_remedio);
                if(buscarRemedio == -1){
                    printf("Remédio não foi encontrado! \n");
                    pausar();
                    continue;
                }
                    printf("Informe a quantidade para venda: ");
                    scanf("%d", &quantidade);
                    limparBuffer();
                    if(quantidade <= 0){
                        printf("\nQuantidade inválida! \n");
                        pausar();
                        continue;
                    }
                        if(quantidade > estoque[buscarRemedio].quant_estoque){
                            printf("\nEstoque insuficiente! \n");
                            pausar();
                            continue;
                        }
                        ItemVenda *aux = realloc(novaVenda.itens, sizeof(ItemVenda) * (novaVenda.quantidadeItens + 1));
                            if(aux == NULL){
                                printf("\nErro ao realocar memória! \n");
                                free(novaVenda.itens);
                                pausar();
                                return;
                            }
                        novaVenda.itens = aux;
                        novaVenda.itens[novaVenda.quantidadeItens].codigoRemedio = cod_remedio;
                        novaVenda.itens[novaVenda.quantidadeItens].quantidade = quantidade;

                        novaVenda.quantidadeItens++;
                        estoque[buscarRemedio].quant_estoque -= quantidade;  

                        printf("\nDeseja adicionar mais itens (1 - Sim / 0 - Não)?   ");
                        scanf("%d", &continuar);
                        limparBuffer();
            }
        
            Venda *auxiliar = realloc(*vendas, sizeof(Venda) * (*qtdVendas + 1));
                if(auxiliar == NULL){
                    printf("\nErro ao realocar memória! \n");
                    free(novaVenda.itens);
                    pausar();
                    return;
                }
                *vendas = auxiliar;
                (*vendas)[*qtdVendas] = novaVenda;
                
                (*qtdVendas)++;

            printf("\nTotal de itens comprados = %d\n", novaVenda.quantidadeItens);
            printf("Venda realizada com sucesso! \n");
            pausar();
}

void listarVendas(Venda *vendas, int qtdVendas){
    int i;
    int j;

    tela();
        printf("\nLISTA DE VENDAS: \n");
        linha();
        if(qtdVendas == 0){
            printf("\nNenhuma venda cadastrada! \n");
            pausar();
            return;
        }
            for(i = 0; i < qtdVendas; i++){
                printf("\nVenda: %d\n", i + 1);
                printf("Código: %d\n", vendas[i].codigoVenda);
                printf("Código do cliente: %d\n", vendas[i].codigoCliente);
                printf("Total de itens: %d\n", vendas[i].quantidadeItens);
            
            for(j = 0; j < vendas[i].quantidadeItens; j++){
                printf("Código do Remédio: %d | Quantidade: %d\n", vendas[i].itens[j].codigoRemedio,
                vendas[i].itens[j].quantidade);
            }
        }
        pausar();
}

int buscarIndiceCodigo(Venda *vendas, int qtdVendas, int codigo){
    int i;

        for(i = 0; i < qtdVendas; i++){
            if(vendas[i].codigoVenda == codigo){
                return i;
            }
        }
        return -1;
}
int buscarVenda(Venda *vendas, int qtdVendas){
    int cod;
    int pos;

    tela();
        printf("\nBUSCAR CÓDIGO DA VENDA\n\n");
        linha();

        if(qtdVendas == 0){
            printf("\nNenhuma venda cadastrada.\n");
            pausar();
            return -1;
        }
        printf("\nInforme o código da venda: ");
        scanf("%d", &cod);
        limparBuffer();

        pos = buscarIndiceCodigo(vendas, qtdVendas, cod);
            if(pos != -1){
            printf("\n=== Venda encontrada ===\n");
            printf("Código: %d\n", vendas[pos].codigoVenda);
            printf("Código do Cliente: %d\n", vendas[pos].codigoCliente);
            printf("Itens: \n");
            
            for(int i = 0; i < vendas[pos].quantidadeItens; i++){
                printf("Remédio: %d | Quantidade: %d\n", vendas[pos].itens[i].codigoRemedio, vendas[pos].itens[i].quantidade);
            }
            return pos;
            }
        printf("\nVenda não encontrada! \n");
        pausar();
        return -1;
}
void salvarVenda(Venda vendas[], char *arquivoVendas, int qtdVendas){
    int i, j;

    FILE *arquivo = fopen(arquivoVendas, "w");
        if(arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
        for (i = 0; i < qtdVendas; i++) {
            fprintf(arquivo, "%d;%d;%d\n", vendas[i].codigoVenda,
            vendas[i].codigoCliente, vendas[i].quantidadeItens);
        
        for(j = 0; j < vendas[i].quantidadeItens; j++){
            fprintf(arquivo, "%d;%d\n", vendas[i].itens[j].codigoRemedio,
            vendas[i].itens[j].quantidade);
        }
    }
  fclose(arquivo);
}

int carregarVenda(Venda **vendas, char *arquivoVendas){
    int i, quant = 0;
    Venda aux;

    FILE *arquivo = fopen(arquivoVendas, "r");
        if(arquivo == NULL){
            printf("Erro ao abrir arquivo.\n");
            return 0;
        }
        while (fscanf(arquivo, "%d;%d;%d\n", &aux.codigoVenda,
        &aux.codigoCliente, &aux.quantidadeItens) == 3)
        {
        Venda *nova_venda = realloc(*vendas, sizeof(Venda) * (quant + 1));
        if(nova_venda == NULL){
            printf("\nErro ao realocar memória! \n");
            fclose(arquivo);
            return quant;
        }
        *vendas = nova_venda;
        (*vendas)[quant] = aux;
        (*vendas)[quant].itens = malloc(sizeof(ItemVenda) * aux.quantidadeItens);

        for(i = 0; i < aux.quantidadeItens; i++){
            fscanf(arquivo, "%d;%d\n", &(*vendas)[quant].itens[i].codigoRemedio,
            &(*vendas)[quant].itens[i].quantidade);
        }
        quant++;
        }
        fclose(arquivo);
        return quant;
}

void liberarVendas(Venda **vendas, int qtdVendas){
    int i;

    for(i = 0; i < qtdVendas; i++){
        free((*vendas)[i].itens);
    }
        free(*vendas);
        *vendas = NULL;
}