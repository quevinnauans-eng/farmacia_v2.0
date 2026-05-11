#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "cliente.h"
#include "venda.h"
#include "utils.h"
#include "remedio.h"

void menuRemedio(Remedio **estoque, int *qtdRemedio, char nomeArquivo[]){
    int op;
    int posicao, encontrado, res;
        do
        {
        tela();
            printf("\n\t\tMENU DE REMÉDIOS \n\n");

            printf("\n1 - Cadastrar remédio \n");
            printf("2 - Listar remédios \n");
            printf("3 - Buscar remédio pelo nome \n");
            printf("4 - Buscar remédio pelo codigo \n");
            printf("5 - Remover remédio do estoque \n");
            printf("6 - Atualizar dados do remédio\n");
            printf("7 - Salvar remédio no estoque \n");
            printf("8 - Listar estoque baixo\n");
            printf("0 - Voltar\n");
            linha();

            printf("\nInforme a opção desejada:   ");
            scanf("%d", &op);

            switch (op)
            {
            case 1:
                cadastrarRemedio(estoque, qtdRemedio);
                break;
            case 2:
                listarRemedios(*estoque, *qtdRemedio);
                break;
            case 3:
                encontrado = buscarRemedioNome(*estoque, *qtdRemedio);
                if(encontrado != -1){
                    printf("\nBusca realizada com sucesso! \n");
                    pausar();
                }
                break;
            case 4:
                posicao = buscarRemedioCodigo(*estoque, *qtdRemedio);
                if(posicao != -1){
                    printf("Posição do remédio vetor: %d\n", posicao + 1);
                    linha();
                }
                else{
                    printf("\nPosição não encontrada! \n");
                }
                pausar();
                break;
            case 5:
                removerRemedio(estoque, qtdRemedio);
                break;
            case 6:
                atualizarRemedio(*estoque, *qtdRemedio);
                break;
            case 7:
            	limparTela();
                salvarRemedio(*estoque, nomeArquivo, *qtdRemedio);
                printf("\nEstoque salvo com sucesso! \n");
                pausar();
                break;
            case 8:
                res = listarEstoqueBaixo(*estoque, *qtdRemedio);
                if(res == 0){
                    printf("\nNão existe remédio abaixo do estoque informado!\n");
                    pausar();
                }
                break;
            case 0:
                limparTela();
                salvarRemedio(*estoque, nomeArquivo, *qtdRemedio);
                printf("\nSalvando alterações no estoque. \n");
                printf("\nVoltando do menu remédio ... \n");
                pausar();
                break;
            default:
                printf("\nopção inválida! \n");
                pausar();
                limparTela();
                break;
            }
        } while (op != 0);
}

int encontrarIndiceCodigo(Remedio *estoque, int qtdRemedio, int codigo){
    int i;
        for(i = 0; i < qtdRemedio; i++){
            if(estoque[i].codigo == codigo){
                return i;
            }
        }
        return -1;
}

void cadastrarRemedio(Remedio **estoque, int *qtdRemedio){
    int codigo, existe;
    int i;
    
    if(*estoque == NULL){
        *estoque = (Remedio *) malloc(sizeof(Remedio));

        if(*estoque == NULL){
            printf("Erro ao alocar memória. \n");
            return;
        }
    }
    else{
        Remedio *novoEstoque = (Remedio *) realloc(*estoque, sizeof(Remedio) * (*qtdRemedio + 1));

        if(novoEstoque == NULL){
            printf("Erro ao realocar memória. \n");
            return;
        }
        *estoque = novoEstoque;
    }
        tela();
            printf("\nCADASTRAR REMÉDIO \n\n");
            do{
            existe = 0;
            printf("Código: ");         
            scanf("%d", &codigo);      
            while(getchar() != '\n');                 
            
            for(i = 0; i < *qtdRemedio; i++){
                if((*estoque)[i].codigo == codigo){
                    printf("\nEsse Código já existe! Tente outro.\n");
                    existe = 1;
                    break;
                }
            }
        } while (existe);
        (*estoque)[*qtdRemedio].codigo = codigo;

            printf("Nome: ");
            scanf(" %[^\n]", (*estoque)[*qtdRemedio].nome);
            printf("Laboratório:  ");
            scanf(" %[^\n]", (*estoque)[*qtdRemedio].laboratorio);
            printf("Preço:  ");
            scanf("%f", &(*estoque)[*qtdRemedio].preco);
            printf("Quantidade em estoque:  ");
            scanf("%d", &(*estoque)[*qtdRemedio].quant_estoque);

        (*qtdRemedio)++;
        printf("\nRemédio cadastrado com sucesso! \n\n");
        pausar();
}
void listarRemedios(Remedio *estoque, int qtdRemedio){
	int i;
    tela();
        printf("\nLISTA DE REMÉDIOS NO ESTOQUE\n");
        linha();
        if(qtdRemedio == 0){
            limparTela();
            printf("\nEstoque Vázio! \n");
            pausar();
            return;
        }
        for(i = 0; i < qtdRemedio; i++){
            printf("\nRemédio %d: \n", i + 1);
            printf("Código do Remédio: %d\n", estoque[i].codigo);
            printf("Nome do Remédio: %s \n", estoque[i].nome);
            printf("Laboratório: %s\n", estoque[i].laboratorio);
            printf("Preço do Remédio: %.2f\n", estoque[i].preco);
            printf("Quantidade em estoque: %d\n", estoque[i].quant_estoque);
            linha();
        }
        pausar();
}

int encontrarIndicePorNome(Remedio *estoque, int qtdRemedio, char nome[]) {
    int i;
	char nomeBusca[MAX];
    char nomeEstoque[MAX];

    strcpy(nomeBusca, nome);
    removerEspacos(nomeBusca);
    paraMinusculo(nomeBusca);

    for (i = 0; i < qtdRemedio; i++) {
        strcpy(nomeEstoque, estoque[i].nome);
        removerEspacos(nomeEstoque);
        paraMinusculo(nomeEstoque);

        if (strcmp(nomeEstoque, nomeBusca) == 0) {
            return i;
        }
    }
    return -1;
}

int buscarRemedioNome(Remedio *estoque, int qtdRemedio){
	int pos;
    char nome[MAX];
        
	tela();
        printf("\nBUSCAR REMÉDIO PELO NOME: \n");
        linha();
        if(qtdRemedio == 0){
            limparTela();
            printf("\nEstoque Vázio! \n");
            pausar();
            return -1;
        }
        printf("\nInforme o nome do Remédio:  ");
        scanf(" %[^\n]", nome);
        
        pos = encontrarIndicePorNome(estoque, qtdRemedio, nome);
        	
        	if(pos != -1){
                printf("\n==== Remédio encontrado ====\n");

                printf("Código do Remédio: %d\n", estoque[pos].codigo);
                printf("Nome do Remédio: %s\n", estoque[pos].nome);
                printf("Laboratório: %s\n", estoque[pos].laboratorio);
                printf("Preço do Remédio: %.2f\n", estoque[pos].preco);
                printf("Quantidade em estoque: %d\n", estoque[pos].quant_estoque);
                return pos;
            }
            printf("\nRemédio com nome %s não existe no cadastro! \n", nome);
            pausar();
            return -1;
}
int buscarRemedioCodigo(Remedio *estoque, int qtdRemedio){
    int codigo;
	int pos;    

	tela();
        printf("\nBUSCAR REMÉDIO PELO CÓDIGO: \n");
        linha();
        if(qtdRemedio == 0){
            limparTela();
            printf("\nEstoque Vázio! \n");
            pausar();
            return -1;
        }
        printf("\nInforme o Código do Remédio:  ");
        scanf("%d", &codigo);

        pos = encontrarIndiceCodigo(estoque, qtdRemedio, codigo);
            if(pos != -1){
                printf("\n==== Remédio encontrado ====\n");

                printf("Código do Remédio: %d\n", estoque[pos].codigo);
                printf("Nome do Remédio: %s\n", estoque[pos].nome);
                printf("Laboratório: %s\n", estoque[pos].laboratorio);
                printf("Preço do Remédio: %.2f\n", estoque[pos].preco);
                printf("Quantidade em estoque: %d\n", estoque[pos].quant_estoque);
                return pos;
            }
            printf("\nRemédio com Código %d não existe no cadastro! \n", codigo);
            return -1;
}
void removerRemedio(Remedio **estoque, int *qtdRemedio){
	int pos, j;
    char nome[MAX];   
	int continuar;

    if(*qtdRemedio == 0){
        limparTela();
        printf("\nEstoque Vázio! \n");
        pausar();
        return;
    }
    tela();
        printf("\nREMOVER REMÉDIO DO ESTOQUE \n");
        linha();
        printf("\nInforme o nome do Remédio: \n");
        scanf(" %[^\n]", nome);
        
		pos = encontrarIndicePorNome(*estoque, *qtdRemedio, nome);
		
			if(pos == -1){
				printf("\nRemédio não encontrado. \n");
				pausar();
				return;
			}
            printf("Remédio a ser removido: \n");
            printf("\tCódigo: %d\n\tNome: %s\n\tLaboratório: %s\n\tPreço: "
             "%.2f\n\tQuantidade: %d\n",
             (*estoque)[pos].codigo, (*estoque)[pos].nome, (*estoque)[pos].laboratorio,
             (*estoque)[pos].preco, (*estoque)[pos].quant_estoque);

             printf("\nDeseja remover o Remédio (1 - Sim / 0 Não)?  ");
             scanf("%d", &continuar);

             if(continuar){
                for(j = pos; j < (*qtdRemedio) - 1; j++){
                    (*estoque)[j] =  (*estoque)[j + 1];
                }
                Remedio *novo_estoque = (Remedio *) realloc(*estoque, sizeof(Remedio) * ((*qtdRemedio) - 1));

                if(novo_estoque != NULL || ((*qtdRemedio) - 1) == 0){
                    *estoque = novo_estoque;
                    (*qtdRemedio)--;
                    printf("\nRemovido com sucesso! \n");
                    pausar();
                }
                else{
                    limparTela();
                    printf("\nErro ao realocar estoque. \n");
                }
             }
             else{
             	printf("O Remédio não foi removido! \n");
             	pausar();
			 }
}
void atualizarRemedio(Remedio *estoque, int qtdRemedio){
    int pos, codigo;

    if(qtdRemedio == 0){
        limparTela();
        printf("\nEstoque Vázio. \n");
        pausar();
        return;
    }
    tela();
        printf("\nATUALIZAR DADOS DO REMÉDIO \n\n");
        linha();

        printf("Informe o código do remédio: ");
        scanf("%d", &codigo);

        pos = encontrarIndiceCodigo(estoque, qtdRemedio, codigo);
        if(pos == -1){
            printf("\nO Remédio não foi encontrado. \n\n");
            pausar();
            return;
        }
        printf("\n=== Dados atuais ===\n\n");
           printf("Código: %d\nNome: %s\nLaboratório: %s\nPreço: %.2f\nQuantidade: %d\n",
       estoque[pos].codigo, estoque[pos].nome, estoque[pos].laboratorio,
       estoque[pos].preco, estoque[pos].quant_estoque);
            linha();

            printf("\nAtualizar dados \n\n");
            printf("Código (não pode ser alterado): %d\n",estoque[pos].codigo);
            printf("Nome: ");
            scanf(" %[^\n]", estoque[pos].nome);
            printf("Laboratório:  ");
            scanf(" %[^\n]", estoque[pos].laboratorio);
            printf("Preço:  ");
            scanf("%f", &estoque[pos].preco);
            printf("Quantidade em estoque:  ");
            scanf("%d", &estoque[pos].quant_estoque);

        printf("\nDados do remédio atualizados com sucesso! \n");
        pausar();
}

void liberarEstoque(Remedio **estoque){
    free(*estoque);
    *estoque = NULL;
    printf("\nMemória liberada com sucesso! \n\n");
}

void salvarRemedio(Remedio estoque[], char *nomeArquivo, int qtdRemedio) {
  int i;
  FILE *arquivo = fopen(nomeArquivo, "w");
  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo de estoque.\n");
    return;
  }

  for (i = 0; i < qtdRemedio; i++) {
    fprintf(arquivo, "%d;%s;%s;%.2f;%d\n", estoque[i].codigo,
            estoque[i].nome, estoque[i].laboratorio, estoque[i].preco,
            estoque[i].quant_estoque);
  }

  fclose(arquivo);
}

int carregarRemedio(Remedio **estoque, char *nomeArquivo) {
   int quant = 0;
   Remedio aux;

  FILE *arquivo = fopen(nomeArquivo, "r");
  if (arquivo == NULL) {
    printf("Arquivo de estoque não encontrado.\n");
    return 0;
  }
  while (fscanf(arquivo, "%d;%[^;];%[^;];%f;%d\n",
                &aux.codigo,
                aux.nome, 
                aux.laboratorio,
                &aux.preco,
                &aux.quant_estoque) == 5){
            
            Remedio *temp = realloc(*estoque, sizeof(Remedio) * (quant + 1));
            if(temp == NULL){
                printf("Erro ao realocar memória. \n");
                fclose(arquivo);
                return quant;
            }
            *estoque = temp;
            (*estoque)[quant] = aux;
    quant++;
  }
  fclose(arquivo);
  return quant;
}

/*
Função extra
Descrição: Lista todos os remédios cadastrados no estoque com valor abaixo de 
uma quantidade informada pelo o usuário
*/
int listarEstoqueBaixo(Remedio *estoque, int qtdRemedio){
    int i, limite;

    tela();
        printf("\nLISTA DE REMÉDIOS COM ESTOQUE BAIXO: \n");
        linha();
        if(qtdRemedio == 0){
            limparTela();
            printf("\nEstoque Vázio! \n");
            pausar();
            return 0;
        }
        printf("\nInforme o limite de estoque: ");
        scanf("%d", &limite);
            for(i = 0; i < qtdRemedio; i++){
                if(estoque[i].quant_estoque <= limite){
                    printf("\nCódigo: %d\n", estoque[i].codigo);
                    printf("Nome: %s\n", estoque[i].nome);
                    printf("Quantidade: %d\n", estoque[i].quant_estoque);
                    linha();
                }
                else{
                    return 0;
                }
            }
        pausar();
        return 1;
}