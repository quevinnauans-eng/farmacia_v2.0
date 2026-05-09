#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "venda.h"
#include "cliente.h"
#include "utils.h"
#include "remedio.h"

void menuCliente(Cliente **clientes, int *qtdClientes, char arquivoClientes[]){
    int opcao;
    int achou, posicao;

    do
    {
        tela();
            printf("\n\t\tMENU DE CLIENTES \n\n");

            printf("1 - Cadastrar cliente \n");
            printf("2 - Listar clientes \n");
            printf("3 - Buscar cliente por nome\n");
            printf("4 - Buscar cliente por código\n");
            printf("5 - Remover cliente\n");
            printf("6 - Atualizar dados do cliente\n");
            printf("7 - Salvar alterações\n");
            printf("0 - Voltar \n");
            linha();

            printf("\nInforme a opção desejada: ");
            scanf("%d", &opcao);

            switch (opcao)
            {
            case 1:
                cadastrarCliente(clientes, qtdClientes);
                break;
            case 2:
                listarClientes(*clientes, *qtdClientes);
                break;
            case 3:
                achou = buscarClienteNome(*clientes, *qtdClientes);
                    if(achou != -1){
                        printf("\nBusca realizada com sucesso! \n");
                        pausar();
                    }
                break;
            case 4:
                posicao = buscarClienteCodigo(*clientes, *qtdClientes);
                if(posicao != -1){
                    printf("\nPosicao do cliente do vetor: %d\n", posicao + 1);
                    linha();
                }
                else{
                    printf("\nPosição não encontrada. \n");
                }
                pausar();
                break;
            case 5:
                removerCliente(clientes, qtdClientes);
                break;
            case 6:
                atualizarCliente(*clientes, *qtdClientes);
                break;
            case 7:
                limparTela();
                salvarCliente(*clientes, arquivoClientes, *qtdClientes);
                printf("\nCliente salvo com sucesso! \n");
                pausar();
                break;
            case 0:
                limparTela();
                salvarCliente(*clientes, arquivoClientes, *qtdClientes);
                printf("\nVoltando do menu cliente ... \n");
                pausar();
                break;
            default:
                printf("\nOpção inválida. \n");
                break;
            }
    } while (opcao != 0);
}

void cadastrarCliente(Cliente **clientes, int *qtdClientes){
    int codigo, existe;
    int i;
    
    if(*clientes == NULL){
        *clientes = (Cliente *) malloc(sizeof(Cliente));

        if(*clientes == NULL){
            printf("Erro ao alocar memória. \n");
            return;
        }
    }
    else{
        Cliente *novoCliente = (Cliente *) realloc(*clientes, sizeof(Cliente) * (*qtdClientes + 1));

        if(novoCliente == NULL){
            printf("Erro ao realocar memória. \n");
            return;
        }
        *clientes = novoCliente;
    }
        tela();
            printf("\nCADASTRAR CLIENTE \n\n");
            linha();
        do{
            existe = 0;
            printf("Código: ");         
            scanf("%d", &codigo);      
            while(getchar() != '\n');                 
            
            for(i = 0; i < *qtdClientes; i++){
                if((*clientes)[i].codigo == codigo){
                    printf("\nEsse Código já existe! Tente outro.\n");
                    existe = 1;
                    break;
                }
            }
        } while (existe);
        (*clientes)[*qtdClientes].codigo = codigo;

            printf("Nome: ");
            scanf(" %[^\n]", (*clientes)[*qtdClientes].nome);
            printf("CPF:  ");
            scanf(" %[^\n]", (*clientes)[*qtdClientes].cpf);
            printf("Telefone:  ");
            scanf(" %[^\n]", (*clientes)[*qtdClientes].telefone);

        (*qtdClientes)++;
        printf("\nCliente cadastrado com sucesso! \n\n");
        pausar();
}

void listarClientes(Cliente *clientes, int qtdClientes){
	int i;

    tela();
        printf("\nLISTA DE CLIENTES CADASTRADOS\n");
        linha();
        if(qtdClientes == 0){
            limparTela();
            printf("\nNão há clientes cadastrados! \n");
            pausar();
            return;
        }
        for(i = 0; i < qtdClientes; i++){
            printf("\nCliente %d: \n", i + 1);
            printf("Código: %d\n", clientes[i].codigo);
            printf("Nome: %s \n", clientes[i].nome);
            printf("CPF: %s\n", clientes[i].cpf);
            printf("Telefone: %s\n", clientes[i].telefone);
            linha();
        }
        pausar();
}
int procurarIndiceNome(Cliente *clientes, int qtdClientes, char nome[]){
    int i;
	char nomeBusca[MAX];
    char nomeCliente[MAX];

    strcpy(nomeBusca, nome);
    removerEspacos(nomeBusca);
    paraMinusculo(nomeBusca);

    for (i = 0; i < qtdClientes; i++) {
        strcpy(nomeCliente, clientes[i].nome);
        removerEspacos(nomeCliente);
        paraMinusculo(nomeCliente);

        if (strcmp(nomeCliente, nomeBusca) == 0) {
            return i;
        }
    }
    return -1;
}
int buscarClienteNome(Cliente *clientes, int qtdClientes){
    int posicao;
    char nome[MAX];
        
	tela();
        printf("\nBUSCAR CLIENTE PELO NOME: \n");
        linha();
        if(qtdClientes == 0){
            limparTela();
            printf("\nNão há clientes cadastrados! \n");
            pausar();
            return -1;
        }
        printf("\nInforme o nome do Cliente:  ");
        scanf(" %[^\n]", nome);
        
        posicao = procurarIndiceNome(clientes, qtdClientes, nome);
        	
        	if(posicao != -1){
                printf("\n==== Cliente encontrado ====\n");

                printf("Código: %d\n", clientes[posicao].codigo);
                printf("Nome: %s\n", clientes[posicao].nome);
                printf("CPF: %s\n", clientes[posicao].cpf);
                printf("Telefone: %s\n", clientes[posicao].telefone);
                return posicao;
            }
            printf("\nCliente com nome %s não existe no cadastro! \n", nome);
            pausar();
            return -1;
}

int procurarIndiceCodigo(Cliente *clientes, int qtdClientes, int codigo){
    int i;
        for(i = 0; i < qtdClientes; i++){
            if(clientes[i].codigo == codigo){
                return i;
            }
        }
        return -1;
}
int buscarClienteCodigo(Cliente *clientes, int qtdClientes){
    int codigo;
    int encontrar;

     tela();
        printf("\nBUSCAR CLIENTE PELO CÓDIGO: \n");
        linha();
    if(qtdClientes == 0){
        limparTela();
        printf("\nNão há clientes cadastrados. \n");
        pausar();
        return -1;
    }
        printf("\nInforme o código do cliente: ");
        scanf("%d", &codigo);

            encontrar = procurarIndiceCodigo(clientes, qtdClientes, codigo);
            if(encontrar != -1){
                printf("\n === Cliente encontrado === \n");

                printf("Código: %d\n", clientes[encontrar].codigo);
                printf("Nome: %s\n", clientes[encontrar].nome);
                printf("CPF: %s\n", clientes[encontrar].cpf);
                printf("Telefone: %s\n", clientes[encontrar].telefone);
                return encontrar;
            }
            
            printf("\nCliente com código %d não existe no cadastro! \n", codigo);
            pausar();
            return -1;
}
void removerCliente(Cliente **clientes, int *qtdClientes){
    int pos, j;
    char nome[MAX];   
	int continuar;

    tela();
        printf("\nREMOVER CLIENTE DO SISTEMA \n");
        linha();

    if(*qtdClientes == 0){
        limparTela();
        printf("\nNão há cliente cadastrado! \n");
        pausar();
        return;
    }
        printf("\nInforme o nome do Cliente: \n");
        scanf(" %[^\n]", nome);
        
		pos = procurarIndiceNome(*clientes, *qtdClientes, nome);
			if(pos == -1){
				printf("\nCliente não encontrado. \n");
				pausar();
				return;
			}
            printf("Cliente a ser removido: \n");
            printf("\tCódigo: %d\n\tNome: %s\n\tCPF: %s\n\tTelefone: %s\n",
             (*clientes)[pos].codigo, (*clientes)[pos].nome, (*clientes)[pos].cpf,
             (*clientes)[pos].telefone);

             printf("\nDeseja remover o Cliente (1 - Sim / 0 Não)?  ");
             scanf("%d", &continuar);

             if(continuar){
                for(j = pos; j < (*qtdClientes) - 1; j++){
                    (*clientes)[j] =  (*clientes)[j + 1];
                }
                Cliente *novo_cliente = (Cliente *) realloc(*clientes, sizeof(Cliente) * ((*qtdClientes) - 1));

                if(novo_cliente != NULL || ((*qtdClientes) - 1) == 0){
                    *clientes = novo_cliente;
                    (*qtdClientes)--;
                    printf("\nRemovido com sucesso! \n");
                    pausar();
                }
                else{
                    limparTela();
                    printf("\nErro ao realocar. \n");
                }
             }
             else{
             	printf("O Cliente não foi removido! \n");
             	pausar();
			 }
}
void atualizarCliente(Cliente *clientes, int qtdClientes){
    int codigo, busca;

    tela();
        printf("\nATUALIZAR DADOS DO CLIENTE: \n");
        linha();

        if(qtdClientes == 0){
            limparTela();
            printf("\nNão há cliente cadastrado! \n");
            pausar();
            return;
        }
        printf("\nInforme o código: ");
        scanf("%d", &codigo);

        busca = procurarIndiceCodigo(clientes, qtdClientes, codigo);
            if(busca == -1){
                printf("\nCliente não foi encontrado! \n");
                pausar();
                return;
            }
            printf("=== Dados atuais ===\n");

            printf("Código: %d\nNome: %s\nCPF: %s\nTelefone: %s\n",
            clientes[busca].codigo, clientes[busca].nome, clientes[busca].cpf,
            clientes[busca].telefone);
                linha();

            printf("\nAtualizar dados \n\n");
            printf("Código (não pode ser alterado): %d\n",clientes[busca].codigo);
            printf("Nome: ");
            scanf(" %[^\n]", clientes[busca].nome);
            printf("Telefone:  ");
            scanf(" %[^\n]", clientes[busca].telefone);

        printf("\nDados do cliente atualizados com sucesso! \n");
        pausar();
}

void liberarClientes(Cliente **clientes){
    free(*clientes);
    *clientes = NULL;
}

void salvarCliente(Cliente clientes[], char *arquivoCliente, int qtdCliente) {
  int i;
  FILE *arquivo = fopen(arquivoCliente, "w");
  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo.\n");
    return;
  }

  for (i = 0; i < qtdCliente; i++) {
    fprintf(arquivo, "%d;%s;%s;%s\n", clientes[i].codigo,
            clientes[i].nome, clientes[i].cpf, clientes[i].telefone);
  }

  fclose(arquivo);
}

int carregarCliente(Cliente **clientes, char *arquivoCliente) {
   int quant = 0;
   Cliente aux;

  FILE *arquivo = fopen(arquivoCliente, "r");
  if (arquivo == NULL) {
    printf("Arquivo de estoque não encontrado.\n");
    return 0;
  }
  while (fscanf(arquivo, "%d;%[^;];%[^;];%[^\n]\n",
                &aux.codigo,
                aux.nome, 
                aux.cpf,
                aux.telefone) == 4){
            
            Cliente *temp = realloc(*clientes, sizeof(Cliente) * (quant + 1));
            if(temp == NULL){
                printf("Erro ao alocar memória. \n");
                fclose(arquivo);
                return quant;
            }
            *clientes = temp;
            (*clientes)[quant] = aux;
    quant++;
  }
  fclose(arquivo);
  return quant;
}