#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void flush_in() {
  // Limpa o buffer do teclado
  int ch;
  do {
    ch = fgetc(stdin);
  } while (ch != EOF && ch != '\n');
}
void espera() {
  // Aguarda o usuário pressionar algum caracter(tecla enter) para prosseguir
  printf(YEL "\n\nAperte ENTER para continuar!");
  setbuf(stdin, NULL);
  getchar();
  setbuf(stdin, NULL);
}
void imprimir(struct Tcarro vetor[], int t, int logico, float v_comb) {
  // Percorre um vetor com dados de clientes e imprime um por um na tela
  for (int i = 0; i < t; i++) {
    printf(GRN "\n\nModelo do %d° carro: %s;\nAno: %d;\nCor: "
               "%s;\nCliente: %s",
           i + 1, vetor[i].modelo, vetor[i].ano, vetor[i].cor,
           vetor[i].cliente);
    if (logico == 1) {
      printf("\nQuantidade de combustível comprada: %d\nValor gasto: %.2f",
             vetor[i].comb_c, vetor[i].comb_c * v_comb);
    }
  }
}
void addcarro(int *fila, int t_fila, struct Tcarro Sfila[]) {
  /*Adiciona carros na fila de espera, perguntando o modelo, ano, cor e
   * dono/cliente do veículo*/
  int retorno = 0; // Váriavel usada para testar valores informados pelo usuário
  if (*fila <
      t_fila) { // Verifica se há espaço disponível na fila para mais um carro
    flush_in();
    printf(GRN "\nInfome o modelo do veículo: ");
    fgets(Sfila[*fila].modelo, 20, stdin);
    Sfila[*fila].modelo[strcspn(Sfila[*fila].modelo, "\n")] = 0;

    do {
      // Controla se o usuário digitou um número para o ano do modelo do veículo
      setbuf(stdin, NULL);
      system("clear");
      printf(GRN "\nInfome o modelo do veículo: %s", Sfila[*fila].modelo);
      printf(GRN "\n\nInforme o ano do modelo: ");
      retorno = scanf("%d", &Sfila[*fila].ano);
    } while (retorno == 0);

    setbuf(stdin, NULL);
    printf(GRN "\nInforme a cor do veículo: ");
    fgets(Sfila[*fila].cor, 20, stdin);
    Sfila[*fila].cor[strcspn(Sfila[*fila].cor, "\n")] = 0;

    setbuf(stdin, NULL);
    printf(GRN "\nInforme o nome do cliente: ");
    fgets(Sfila[*fila].cliente, 30, stdin);
    Sfila[*fila].cliente[strcspn(Sfila[*fila].cliente, "\n")] = 0;

    *fila =
        *fila +
        1; // Incremento da váriavel que controla a posição atual do vetor Sfila
    printf(GRN "\nCarro adicionado a fila!");
  } else {
    printf(RED "\nNão é possível adicionar mais carros, a fila está cheia!!");
  }
}

int abastecimento(int *tanque, int *fila, float v_comb, int *ca_atnd,
                  struct Tcarro Sfila[], struct Tcarro Sca_atnd[]) {
  /*Função que realiza o abastecimento dos veículos, reposicionando-os nos
   * vetores que armazenam suas informações e salvando dados de abastecimento*/
  int comb_v, retorno = 0;
  float total;
  if (*tanque > 0) {  // Verifica se há combustível disponível
    if (*fila != 0) { // Verifica se há carros na fila de espera
      printf(GRN
             "Combustível disponível no tanque: %d \nValor do combustível %.2f",
             *tanque, v_comb);
      printf(YEL "\n\nAtenção: para calncelar a compra, digite 0(zero)!!");
      printf(GRN "\nDigite a quantidade de combústivel que deseja abastecer:");
      retorno = scanf("%d", &comb_v);
      if (comb_v > *tanque || comb_v < 0 ||
          retorno == 0) { /*Verifica se o valor que o úsuario pretende abastecer
                             não está disponível ou é inválido*/
        do {
          system("clear");
          if (comb_v > *tanque) {
            /*Se o combustível requerido é maior que o disponível no tanque
             * pede-se ao usuário para informar um novo valor ou cancelar a
             * compra*/
            flush_in();
            printf(
                YEL
                "\nCombustível insuficiente, o tanque tem somente %d litros.",
                *tanque);
            printf("\nSó é possível abastecer uma quantidade menor ou igual a "
                   "disponível no tanque.");
            printf("\nDigite um valor menor que o disponível no tanque ou 0 "
                   "para cancelar a compra:");
            retorno = scanf("%d", &comb_v);
          }
          if (comb_v < 0 || retorno == 0) {
            flush_in();
            if (retorno == 0) {
              printf(RED
                     "Valor inválido! Digite um número ao invés de uma letra:");
            } else {
              printf(RED "Valor inválido! Digite um valor positivo:");
            }
            retorno = scanf("%d", &comb_v);
          }
        } while (comb_v > *tanque || comb_v < 0 || retorno == 0);
      }
      if (comb_v > 0) {
        total = comb_v * v_comb;
        printf(YEL "\nO valor total da compra é de: %.3f", total);
				return 1;
        espera();
        /*Se for informado uma quantidade de combustível válida, é realizado o
         * abastecimento, adicionando as informações do primeiro carro da fila
         * de espera no vetor que armazena os dados dos carros
         * atendidos(Sca_atnd)*/
        printf(GRN "\nPrimeiro carro da fila abastecido!!");
        strcpy(Sca_atnd[*ca_atnd].modelo, Sfila[0].modelo);
        strcpy(Sca_atnd[*ca_atnd].cor, Sfila[0].cor);
        strcpy(Sca_atnd[*ca_atnd].cliente, Sfila[0].cliente);
        Sca_atnd[*ca_atnd].ano = Sfila[0].ano;
        Sca_atnd[*ca_atnd].comb_c = comb_v;
        *ca_atnd = *ca_atnd + 1;
        Sca_atnd = (struct Tcarro *)realloc(
            Sca_atnd, (*ca_atnd + 1) * sizeof(struct Tcarro *));
        // Realoca, aumenta o espaço de memória para o vetor de carros
        // atendidos(Sca_atnd)
      } else {
        printf(YEL "\nPrimeiro carro da fila cancelou a compra!");
				return 0;
      }

      for (int i = 0; i < *fila; i++) {
        // Copia as informações do veículo da posição i+1 para a posição i,
        // removendo o primeiro carro da fila de espera e reorganizando a fila
        strcpy(Sfila[i].modelo, Sfila[i + 1].modelo);
        strcpy(Sfila[i].cor, Sfila[i + 1].cor);
        strcpy(Sfila[i].cliente, Sfila[i + 1].cliente);
        Sfila[i].ano = Sfila[i + 1].ano;
      }
      *tanque = *tanque - comb_v;
      *fila = *fila - 1;
    } else {
      printf(YEL "\nNão há carros na fila para serem abastecidos!");
			return 0;
    }
  } else {
    printf(RED
           "\nImpossível abastecer!! O estabelecimento está sem combustível.");
		return 0;
    *fila = 0; /*Se não há mais combustível, possiciona a varíavel contole da
                  posição do vetor Sfila na possição 0, "limpando" o vetor*/
  }
}

void relatorio(int tanque, int ca_atnd, float v_comb, struct Tcarro vetor[],
               int logico) {
  // Cria um arquivo .txt com todas as informações das vendas
  FILE *file; // Cria um ponteiro do tipo FILE("arquivo")
  file = fopen("Relatório.txt", "w"); // Cria um arquivo
  fprintf(file, "\t\t\tRelatório de Vendas\n");
  fprintf(file, "\nA quantidade de litros vendida foi:\n");
  fprintf(file, "%d litros.\n", 200 - tanque);
  fprintf(file, "\nO valor total arrecadado com as vendas foi:\n");
  fprintf(file, "%.3f reais.\n", (200 - tanque) * v_comb);
  fprintf(file, "\nA quantidade de carros atendidos foi:\n");
  fprintf(file, "%d carros.\n", ca_atnd);
  for (int i = 0; i < ca_atnd; i++) {
    fprintf(file,
            "\n\nModelo do %d° carro: %s;\nAno: %d;\nCor: "
            "%s;\nCliente: %s",
            i + 1, vetor[i].modelo, vetor[i].ano, vetor[i].cor,
            vetor[i].cliente);
    fprintf(file, "\nQuantidade de combustível comprada: %d\nValor gasto: %.2f",
            vetor[i].comb_c, vetor[i].comb_c * v_comb);
  }
  fprintf(file, "\n\nQuantidade de combustível restante no tanque:\n");
  fprintf(file, "%d litros.\n", tanque);
  fclose(file); // Fecha o arquivo
  if (logico == 1) {
    printf(GRN "\n\nUm arquivo com o relatório completo de vendas foi criado "
               "no diretório do programa!");
  }
}