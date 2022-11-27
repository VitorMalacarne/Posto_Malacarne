#include "header.h"
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  setlocale(LC_ALL, "Portuguese");
  printf(GRN "\t\tGerenciador de Postos de Combustíveis - Por Vitor Malacarne\n");
  printf("\tEste programa auxilia o gerenciamento de pequenos postos de combustíveis.\n");
  printf("\tEle ajuda a controlar o estoque de combustível, as finanças do estabelecimento\ne a gerenciar o atendimento aos clientes.\n");
  espera();

  // Variáveis
  float v_comb; // Valor do combustível
  int t_fila, fila = 0, ca_atnd = 0, opcao, tanque = 200, retorno, ret;
  /*Tamanho da fila suportada, varíavel de controle da posição
   * do vetore Sfila , quantos carros foram atendidos, seleção da opção do menu principal,
   * capacidade do tanque de combustíveis, variável para controle de dados de
   * entrada, controle do processo de abastecimento*/
  char op_rel;          // Seleção da opção no menu relatório
  struct Tcarro *Sfila; /* Vetores do tipo Tcarro que armazenam informações deveículos que estão na fila de espera*/
  Sca_atnd *ini_ca_atnd;//Ponteiro inicial da lista de carros atendidos
  Sca_atnd *prox_ca_atnd;//Ponteiro que aponta para o elemento atual da lista de carros atendidos

  /*Seção Inicial que pede que o usuário adicione o valor do combustível e o
   * tamanho da fila que o estabelecimento suporta e verifica se os valores são
   * válidos*/
  do {
    retorno = 0;
    system("clear");
    printf(GRN "\nPor favor, insira o valor do cumbustível(Obs: Use ponto para casas decimais):");
    retorno = scanf("%f", &v_comb);
    if (v_comb <= 0 || retorno == 0) {
      flush_in();
      if (retorno == 0) {
        printf(RED "\nValor do combustível inválido, digite um número!");
      } else {
        printf(RED "\nValor do combustível inválido! Insira um valor positivo e difernete de 0.");
      }
      espera();
    }
  } while (v_comb <= 0 || retorno == 0);
  do {
    system("clear");
    retorno = 0;
    printf(GRN "\nPor favor, insira o tamanho da fila que o estabelecimento suporta:");
    retorno = scanf("%d", &t_fila);
    if (t_fila <= 0 || retorno == 0) {
      flush_in();
      if (retorno == 0) {
        printf(RED "\nValor inválido, digite um número!");
      } else {
        printf(RED "\nTamanho da fila inserido inválido! Digite um valor positivo e diferente de zero.");
      }
      espera();
    }
  } while (t_fila <= 0 || retorno == 0);
  flush_in();
  system("clear");

  // Alocação e limpeza de espaço de memória para os vetores que armazenam os
  // dados dos clientes
  Sfila = (struct Tcarro *)malloc(t_fila * sizeof(struct Tcarro));
  ini_ca_atnd = (Sca_atnd *)malloc(sizeof(Sca_atnd));
  if (Sfila == NULL || ini_ca_atnd == NULL) {
    exit(1);
  }
  prox_ca_atnd = ini_ca_atnd;

  do {
    /*Menu principal onde o usúario escolhe qual a próxima ação do programa*/
    retorno = 0;
    system("clear");
    printf(GRN "\t\t\t\t\t\t\tMenu\n");
    printf(GRN "\n\nSelecione a ação que deseja realizar digitando o número correspondete e pressionando a tecla Enter.\n\n");
    printf("\t1 - Adicionar um carro na fila;\n");
    printf("\t2 - Abastecimento;\n");
    printf("\t3 - Exibir carros na fila de espera;\n");
    printf("\t4 - Relatórios;\n");
    printf("\t5 - Encerrar o programa.\n");
    printf("Digite a opção desejada:");
    retorno = scanf("%d", &opcao);
    system("clear");

    if (retorno != 0) {
      switch (opcao) {
      case 1:
        // Chama a função que adiciona um carro na fila
        addcarro(&fila, t_fila, Sfila);
        espera();
        break;
      case 2:
        // Chama a função de abastecimento
        ret = abastecimento(&tanque, &fila, v_comb, Sfila, prox_ca_atnd);
        if (ret == 1) {
          prox_ca_atnd->proximo = (Sca_atnd *)malloc(sizeof(Sca_atnd));
          prox_ca_atnd = prox_ca_atnd->proximo;
          ca_atnd++;
        }
        espera();
        break;
      case 3:
        // Mostra os carros que estão na fila de espera
        if (fila > 0) {
          printf(GRN "\nFila de espera: %d carros.", fila);
          imprimir(Sfila, fila);
        } else {
          printf(YEL "\nNão há carros na fila de espera!");
        }
        espera();
        break;
      case 4:
        /*Menu de relatórios onde o usúario pode ver o histórico dos
         * atendimentos realizados*/
        do {
          system("clear");
          printf(GRN "\t\t\tRelatórios:\n");
          printf(GRN"\tSelecione uma opção digitando a letra correspondente\ne pressionando a tecla Enter:\n");
          printf("a - Quantidade de litros vendida;\n");
          printf("b - Valor total arrecadado com as vendas;\n");
          printf("c - Quantidade de carros atendidos;\n");
          printf("d - Quantidade de combustível restante no tanque;\n");
          printf("e - Gerar arquivo para impressão (com todas as informações de A, B, C e D);\n");
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
            printL(prox_ca_atnd, ini_ca_atnd, v_comb);
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
            // Chama a função que gera um arquivo .txt com todos os dados do relatório
            relatorio(tanque, ca_atnd, v_comb, prox_ca_atnd, ini_ca_atnd);
            flush_in();
            espera();
            break;
          case 'f':
            printf(YEL "Voltar ao menu principal!");
            flush_in();
            espera();
            break;
          default:
            printf(RED "\nOpção Inválida!! Por favor, selecione uma opção disponível!\n");
            flush_in();
            espera();
          }
        } while (op_rel != 'f');
        break;
      case 5:
        // Encerra o programa e gera um arquivo com relatórios.
        printf(YEL "Programa encerrado!");
        relatorio(tanque, ca_atnd, v_comb, prox_ca_atnd, ini_ca_atnd);
        exit(0);
        break;
      default:
        printf(RED"Valor Inválido!!! Por favor, digite um valor válido(1 até 5).");
        espera();
      }
    } else {
      flush_in();
      printf(RED "\nDigite apenas números ao invés de letras!");
      espera();
    }
    system("clear");
  } while (opcao != 5);
  return 0;
}