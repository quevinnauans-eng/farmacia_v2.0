#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "cliente.h"
#include "venda.h"
#include "utils.h"
#include "remedio.h"

// FUNÇÕES AUXILIARES
void limparTela(){

    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}
void linha(){
	int i;
    for(i = 0; i < 60; i++){
        printf("_");
    }
    printf("\n");
}
void tela(){
    limparTela();
        printf("\n\t\tSISTEMA DE CONTROLE DE FARMÁCIA\n\n");
        linha();
}
void pausar(){
    printf("\nPressione ENTER para continuar ... ");
    while(getchar() != '\n');
    getchar();
}
void paraMinusculo(char str[]) {
	int i;
    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] += 32;
        }
    }
}
void removerEspacos(char str[]) {
    int i = 0, j = 0;

    while (str[i] == ' ') i++;

    for (; str[i] != '\0'; i++) {
        if (!(str[i] == ' ' && str[i+1] == ' ')) {
            str[j++] = str[i];
        }
    }
    if (j > 0 && str[j-1] == ' ') j--;

    str[j] = '\0';
}

void limparBuffer() {
    while(getchar() != '\n' && !feof(stdin));
}