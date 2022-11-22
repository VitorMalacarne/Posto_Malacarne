#include "header.h"
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  setlocale(LC_ALL, "");
  printf(GRN
         "\t\tGerenciador de Postos de Combustíveis - Por Vitor Malacarne\n");
  printf("\tEste programa auxilia o gerenciamento de pequenos postos de "
         "combustíveis.\n");
  printf("\tEle ajuda a controlar o estoque de combustível, as finanças do "
         "estabelecimento\ne a gerenciar o atendimento aos clientes.\n");
  espera();

  /*Variáveis*/
  float v_comb;
  int t_fila, fila = 0, opcao, tanque = 200, ca_atnd = 0;
  char op_rel;
  struct Tcarro *Sfila, *Sca_atnd;
  /*Variáveis*/

  /*Seção Inicial que pede que o usuário adicione o valor do combustível e o
   * tamanho da fila que o estabelecimento suporta*/
  do {
    system("clear");
    printf(GRN "\nPor favor, insira o valor do cumbustível(Obs: Use ponto para "
               "casas decimais):");
    scanf("%f", &v_comb);
    if (v_comb <= 0) {
      printf(RED "\nValor do combustível inválido! Insira um valor positivo e "
                 "não nulo.");
      espera();
    }
  } while (v_comb <= 0);
  do {
    system("clear");
    printf(
        GRN
        "\nPor favor, insira o tamanho da fila que o estabelecimento suporta:");
    scanf("%d", &t_fila);
    if (t_fila <= 0) {
      printf(RED "\nTamanho da fila inserido inválido! Digite um valor "
                 "positivo e não nulo.");
      espera();
    }
  } while (t_fila <= 0);
  flush_in();
  system("clear");
  Sfila = (struct Tcarro *)calloc(t_fila, sizeof(struct Tcarro));
  Sca_atnd = (struct Tcarro *)calloc(1, sizeof(struct Tcarro));
  /*Menu principal onde o usúario escolhe qual a próxima ação do programa*/
  do {
    system("clear");
    printf(GRN "\t\t\t\t\t\t\tMenu\n");
    printf(GRN "\n\nSelecione a ação que deseja realizar digitando o número "
               "correspondete e pressionando a tecla Enter.\n\n");
    printf("\t1 - Adicionar um carro na fila;\n");
    printf("\t2 - Abastecimento;\n");
    printf("\t3 - Exibir carros na fila de espera;\n");
    printf("\t4 - Relatórios;\n");
    printf("\t5 - Encerrar o programa.\n");
    printf("Opção selecionada:");
    scanf("%d", &opcao);
    system("clear");

    switch (opcao) {
    case 1:
      addcarro(&fila, t_fila, Sfila);
      break;
    case 2:
      abastecimento(&tanque, &fila, v_comb, &ca_atnd, Sfila, Sca_atnd);
      break;
    case 3:
      if (fila > 0) {
        printf(GRN "\nFila de espera: %d carros.", fila);
        imprimir(Sfila, fila);
      } else {
        printf(YEL "\nNão há carros na fila de espera!");
      }
      break;
    case 4:
      /*Menu de relatórios, usuário seleciona o que deseja fazer*/
      do {
        system("clear");
        printf(GRN "\t\t\tRelatórios:\n");
        printf(GRN "\tSelecione uma opção digitando a letra correspondente\ne "
                   "pressionando a tecla Enter:\n");
        printf("a - Quantidade de litros vendida;\n");
        printf("b - Valor total arrecadado com as vendas;\n");
        printf("c - Quantidade de carros atendidos;\n");
        printf("d - Quantidade de combustível restante no tanque;\n");
        printf("e - Gerar arquivo para impressão (com todas as informações de "
               "A, B, C e D);\n");
        printf("f - voltar ao menu anterior.\n");
        printf("Opção selecionada:");
        setbuf(stdin, NULL);
        scanf(" %c", &op_rel);
        setbuf(stdin, NULL);
        system("clear");
        switch (op_rel) {
        case 'a':
          printf(GRN "A quantidade de litros vendida foi:\n");
          printf("%d litros.\n", 200 - tanque);
          flush_in();
          espera();
          break;
        case 'b':
          printf(GRN "O valor total arrecadado com as vendas foi:\n");
          printf("%.3f reais.\n", (200 - tanque) * v_comb);
          flush_in();
          espera();
          break;
        case 'c':
          printf(GRN "A quantidade de carros atendidos foi:\n");
          printf("%d carros.\n", ca_atnd);
          imprimir(Sca_atnd, ca_atnd);
          flush_in();
          espera();
          break;
        case 'd':
          printf(GRN "Quantidade de combustível restante no tanque:\n");
          printf("%d litros.\n", tanque);
          flush_in();
          espera();
          break;
        case 'e':
          relatorio(tanque, ca_atnd, v_comb, Sca_atnd);
          flush_in();
          espera();
          break;
        case 'f':
          printf(YEL "Voltar ao menu principal!");
          break;
        default:
          printf(RED "\nOpção Inválida!! Por favor, selecione uma opção "
                     "disponível!\n");
          espera();
        }
      } while (op_rel != 'f');
      break;
    case 5:
      printf(YEL "Programa encerrado!");
      exit(0);
      break;
    default:
      printf(RED "Valor Inválido!!!");
      printf(RED "Por favor, digite um valor válido(1 até 5)");
    }
    espera();
    system("clear");
  } while (opcao != 5);
  return 0;
}