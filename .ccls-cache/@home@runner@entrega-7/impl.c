#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

void flush_in() {
    int ch;
    do{
        ch = fgetc(stdin);
    }while (ch != EOF && ch != '\n');
}
void espera() {
  printf(YEL "\n\nAperte ENTER para continuar!");
  setbuf(stdin, NULL);
  getchar();
  setbuf(stdin, NULL);
}
void imprimir(struct Tcarro vetor[], int t) {
  for (int i = 0; i < t; i++) {
    printf(GRN "\n\nModelo do %d° carro: %s;\nAno: %d;\nCor: "
               "%s;\nCliente: %s",
           i + 1, vetor[i].modelo, vetor[i].ano, vetor[i].cor,
           vetor[i].cliente);
  }
}
void addcarro(int *fila, int t_fila, struct Tcarro Sfila[]) {
  if (*fila < t_fila) {
    flush_in();
    printf(GRN "\nInfome o modelo do veículo: ");
    fgets(Sfila[*fila].modelo, 20, stdin);
    Sfila[*fila].modelo[strcspn(Sfila[*fila].modelo, "\n")] = 0;
    setbuf(stdin, NULL);
    

    printf(GRN "\nInforme o ano do modelo: ");
    scanf("%d", &Sfila[*fila].ano);
    setbuf(stdin, NULL);

    printf(GRN "\nInforme a cor do veículo: ");
    fgets(Sfila[*fila].cor, 20, stdin);
    Sfila[*fila].cor[strcspn(Sfila[*fila].cor, "\n")] = 0;
    setbuf(stdin, NULL);

    printf(GRN "\nInforme o nome do cliente: ");
    fgets(Sfila[*fila].cliente, 30, stdin);
    Sfila[*fila].cliente[strcspn(Sfila[*fila].cliente, "\n")] = 0;
    setbuf(stdin, NULL);

    *fila = *fila + 1;
    printf(GRN "\nCarro adicionado a fila!");
  } else {
    printf(RED "\nNão é possível adicionar mais carros, a fila está cheia!!");
  }
}

void abastecimento(int *tanque, int *fila, float v_comb, int *ca_atnd, struct Tcarro Sfila[], struct Tcarro Sca_atnd[]) {
  int comb_v;
  if (*tanque > 0) {
    if (*fila != 0) {
        printf(GRN "Combustível disponível no tanque: %d", *tanque);
        printf(GRN "\n\nDigite a quantidade de combústivel que deseja abastecer:");
        scanf("%d", &comb_v);
        if (comb_v > *tanque || comb_v < 0) {
          do{
            system("clear");
            if(comb_v > *tanque){
              flush_in();
              printf(YEL"\nCombustível insuficiente, o tanque tem somente %d litros.", *tanque);
              printf("\nSó é possível abastecer uma quantidade menor ou igual a disponível no tanque.");
              printf("\nDigite um valor menor que o disponível no tanque ou 0 para cancelar a compra:");
              scanf("%d", &comb_v);
            }
            if(comb_v < 0){
              flush_in();
              printf(RED"Valor inválido! Digite um valor positivo:");
              scanf("%d", &comb_v);
            }
          }while(comb_v > *tanque || comb_v < 0);
          
        }
        printf(YEL "\nO valor total da compra é de: %.3f", comb_v * v_comb);
        espera();
        if(comb_v > 0){
          printf(GRN "\nPrimeiro carro da fila abastecido!!");
          strcpy(Sca_atnd[*ca_atnd].modelo, Sfila[0].modelo);
          strcpy(Sca_atnd[*ca_atnd].cor, Sfila[0].cor);
          strcpy(Sca_atnd[*ca_atnd].cliente, Sfila[0].cliente);
          Sca_atnd[*ca_atnd].ano = Sfila[0].ano;
          *ca_atnd = *ca_atnd + 1;
          Sca_atnd = (struct Tcarro *)realloc(Sca_atnd, (*ca_atnd + 1)* sizeof(struct Tcarro)); 
        }else{
          printf(YEL"\nPrimeiro carro da fila cancelou a compra!");
          }
        
        for (int i = 0; i < *fila; i++) {
          strcpy(Sfila[i].modelo, Sfila[i + 1].modelo);
          strcpy(Sfila[i].cor, Sfila[i + 1].cor);
          strcpy(Sfila[i].cliente, Sfila[i + 1].cliente);
          Sfila[i].ano = Sfila[i + 1].ano;
        }
        *tanque = *tanque - comb_v;
        *fila = *fila - 1;   
    } else {
      printf(YEL "\nNão há carros na fila para serem abastecidos!");
    }
  } else {
    printf(RED
           "\nImpossível abastecer!! O estabelecimento está sem combustível.");
    *fila = 0;
  }
}

void relatorio(int tanque, int ca_atnd, float v_comb, struct Tcarro Sca_atnd[]) {
  printf(GRN "\t\t\tRelatório de Vendas\n");
  printf("\nA quantidade de litros vendida foi:\n");
  printf("%d litros.\n", 200 - tanque);
  printf("\nO valor total arrecadado com as vendas foi:\n");
  printf("%.3f reais.\n", (200 - tanque) * v_comb);
  printf("\nA quantidade de carros atendidos foi:\n");
  printf("%d carros.\n", ca_atnd);
  imprimir(Sca_atnd, ca_atnd);
  printf("\n\nQuantidade de combustível restante no tanque:\n");
  printf("%d litros.\n", tanque);
  printf("\n\nUm arquivo com o relatório de vendas foi enviado para impressão!");
}