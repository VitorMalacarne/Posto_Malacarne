#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define RED "\e[0;31m"

/*Tipos*/
struct Tcarro{
    char modelo[20], cor[20], cliente[30];
    int ano;
};
/*Funções*/
void espera() {
    printf(YEL"\nAperte ENTER para continuar!");
    setbuf(stdin, NULL);
    getchar();
    setbuf(stdin, NULL);
}

void addcarro(int *fila, int t_fila, struct Tcarro Sfila[10]) {
    if (*fila < t_fila) {
        printf(GRN"\nInfome o modelo do veículo: ");
        fgets(Sfila[*fila].modelo, 20, stdin);
        Sfila[*fila].modelo[strcspn(Sfila[*fila].modelo, "\n")] = 0;
        setbuf(stdin, NULL);
        
        printf(GRN"\nInforme o ano do modelo: ");
        scanf("%d", &Sfila->ano);
        setbuf(stdin, NULL);
        
        printf(GRN"\nInforme a cor do veículo: ");
        fgets(Sfila[*fila].cor, 20, stdin);
        Sfila[*fila].cor[strcspn(Sfila[*fila].cor, "\n")] = 0;
        setbuf(stdin, NULL);
        
        printf(GRN"\nInforme o nome do cliente: ");
        fgets(Sfila[*fila].cliente, 30, stdin);
        Sfila[*fila].cliente[strcspn(Sfila[*fila].cliente, "\n")] = 0;
        setbuf(stdin, NULL);
        
        *fila = *fila + 1;
        printf(GRN"Carro adicionado a fila!");
    } else {
        printf(RED"\nNão é possível adicionar mais carros, a fila está cheia!!");
    }
}

void abastecimento(int *tanque, int *fila, float v_comb, int *ca_atnd, struct Tcarro Sfila[10], struct Tcarro Sca_atnd[10]) {
    int comb_v;
    if (*tanque > 0) {
        if (*fila != 0) {
                printf(GRN"Combustível disponível no tanque: %d", *tanque);
                printf(GRN"\nDigite a quantidade de combústivel que deseja abastecer:");
                scanf("%d", &comb_v);
                if (comb_v > *tanque) {
                    printf(YEL"\nCombustível insuficiente, o tanque tem somente %d litros.", *tanque);
                    printf("\nSó é possível abastecer uma quantidade menor ou igual a disponível no tanque.");
                    espera();
                }else{
                  printf(YEL"\nO valor total da compra é de: %.3f", comb_v * v_comb);
                  espera();
                  printf(GRN"Primeiro carro da fila abastecido");
                  strcpy(Sca_atnd[*ca_atnd].modelo, Sfila[0].modelo);
                  strcpy(Sca_atnd[*ca_atnd].cor, Sfila[0].cor);
                  strcpy(Sca_atnd[*ca_atnd].cliente, Sfila[0].cliente);
                  Sca_atnd[*ca_atnd].ano = Sfila[0].ano;
                  for(int i = 0; i < *fila; i++){
                    strcpy(Sfila[i].modelo, Sfila[i+1].modelo);
                    strcpy(Sfila[i].cor, Sfila[i+1].cor);
                    strcpy(Sfila[i].cliente, Sfila[i+1].cliente);
                    Sfila[i].ano =Sfila[i+1].ano;
                  }
                  *ca_atnd = *ca_atnd + 1;
                  *tanque = *tanque - comb_v;
                  *fila = *fila - 1;
                }
        } else {
            printf(YEL"\nNão há carros na fila para serem abastecidos!");
        }
    } else {
        printf(RED"\nImpossível abastecer!! O estabelecimento está sem combustível.");
      //remover todos os carros do vetor fila
    }
}

void relatorio(int tanque, int ca_atnd, float v_comb, struct Tcarro Sca_atnd[10]){
    printf(GRN"\t\t\tRelatório de Vendas\n");
    printf("\nA quantidade de litros vendida foi:\n");
    printf("%d litros.\n", 200 - tanque);
    printf("\nO valor total arrecadado com as vendas foi:\n");
    printf("%.3f reais.\n", (200 - tanque) * v_comb);
    printf("\nA quantidade de carros atendidos foi:\n");
    printf("%d carros.\n", ca_atnd);
    for (int i = 0; i < ca_atnd; i++) {
      printf(GRN"\n\nModelo do %d° carro atendido: %s;\nAno: %d;\nCor: %s;\nCliente: %s",i+1, Sca_atnd[i].modelo, Sca_atnd[i].ano, Sca_atnd[i].cor, Sca_atnd[i].cliente);
    }
    printf("\nQuantidade de combustível restante no tanque:\n");
    printf("%d litros.\n", tanque);
    printf("\n\nUm arquivo com o relatório de vendas foi enviado para impressão");
         
}

int main(void) {
    setlocale(LC_ALL,"");
    printf(GRN"\t\tGerenciador de Postos de Combustíveis - Por Vitor Malacarne\n");
    printf("\tEste programa auxilia o gerenciamento de pequenos postos de combustíveis.\n");
    printf("\tEle ajuda a controlar o estoque de combustível, as finanças do estabelecimento\ne a gerenciar o atendimento aos clientes.\n");
    espera();

    /*Variáveis*/
    float v_comb;
    int t_fila, fila = 0, opcao, tanque = 200, ca_atnd = 0;
    char op_rel;
    struct Tcarro Sfila[10], Sca_atnd[10];
    /*Variáveis*/

    /*Seção Inicial que pede que o usuário adicione o valor do combustível e o tamanho da fila que o estabelecimento suporta*/
    do {
        system("clear");
        printf(GRN"\nPor favor, insira o valor do cumbustível(Obs: Use ponto para casas decimais):");
        scanf("%f", &v_comb);
        if (v_comb <= 0) {
            printf(RED"\nValor do combustível inválido! Insira um valor positivo e não nulo.");
            espera();
        }
    } while (v_comb <= 0);
    do {
        system("clear");
        printf(GRN"\nPor favor, insira o tamanho da fila que o estabelecimento suporta:");
        scanf("%d", &t_fila);
        if (t_fila <= 0) {
            printf(RED"\nTamanho da fila inserido inválido! Digite um valor positivo e não nulo.");
            espera();
        }
    } while (t_fila <= 0);
    setbuf(stdin, NULL);
    system("clear");

    /*Menu principal onde o usúario escolhe qual a próxima ação do programa*/
    do {
        printf(GRN"\t\t\t\t\t\t\tMenu\n");
        printf(GRN"\n\nSelecione a ação que deseja realizar digitando o número correspondete e pressionando a tecla Enter.\n\n");
        printf("\t1 - Adicionar um carro na fila;\n");
        printf("\t2 - Abastecimento;\n");
        printf("\t3 - Exibir carros na fila de espera;\n");
        printf("\t4 - Relatórios;\n");
        printf("\t5 - Encerrar o programa.\n");
        printf("Opção selecionada:");
        setbuf(stdin, NULL);
        scanf("%d", &opcao);
        system("clear");
        setbuf(stdin, NULL);

        switch (opcao) {
            case 1:
                addcarro(&fila, t_fila, Sfila);
                break;
            case 2:
                abastecimento(&tanque, &fila, v_comb, &ca_atnd, Sfila, Sca_atnd);
                break;
            case 3:
                if (fila > 0) {
                    printf(GRN"\nFila de espera: %d carros.", fila);
                    for (int i = 0; i < fila; i++) {
                        printf(GRN"\n\nModelo do %d° carro: %s;\nAno: %d;\nCor: %s;\nCliente: %s",i+1, Sfila[i].modelo, Sfila[i].ano, Sfila[i].cor, Sfila[i].cliente);
                    }
                }else{
                    printf(YEL"\nNão há carros na fila de espera!");
                }
                break;
            case 4:
                /*Menu de relatórios, usuário seleciona o que deseja fazer*/
                do {

                    printf(GRN"\t\t\tRelatórios:\n");
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
                            printf(GRN"A quantidade de litros vendida foi:\n");
                            printf("%d litros.\n", 200 - tanque);
                            break;
                        case 'b':
                            printf(GRN"O valor total arrecadado com as vendas foi:\n");
                            printf("%.3f reais.\n", (200 - tanque) * v_comb);
                            break;
                        case 'c':
                            printf(GRN"A quantidade de carros atendidos foi:\n");
                            printf("%d carros.\n", ca_atnd);
                            for (int i = 0; i < ca_atnd; i++) {
                              printf(GRN"\n\nModelo do %d° carro atendido: %s;\nAno: %d;\nCor: %s;\nCliente: %s",i+1, Sca_atnd[i].modelo, Sca_atnd[i].ano, Sca_atnd[i].cor, Sca_atnd[i].cliente);
                            }
                            break;
                        case 'd':
                            printf(GRN"Quantidade de combustível restante no tanque:\n");
                            printf("%d litros.\n", tanque);
                            break;
                        case 'e':
                            relatorio(tanque, ca_atnd, v_comb, Sca_atnd);
                            break;
                        case 'f':
                            printf(YEL"Voltar ao menu principal!");
                            break;
                        default:
                            printf(RED"\nOpção Inválida!! Por favor, selecione uma opção disponível!\n");
                    }
                    espera();

                } while (op_rel != 'f');
                break;
            case 5:
                printf(YEL"Programa encerrado!");
                exit(0);
                break;
            default:
                printf(RED"Valor Inválido!!!");
                printf(RED"Por favor, digite um valor válido(1 até 5)");
        }
        espera();
        system("clear");
    } while (opcao != 5);
    return 0;

}