#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define RED "\e[0;31m"

/*Funções*/
void espera() {
    setbuf(stdin, NULL);
    getchar();
    setbuf(stdin, NULL);
}

void addcarro(int *fila, int t_fila) {
    if (*fila < t_fila) {
        *fila = *fila + 1;
        printf(GRN"Carro adicionado!");
    } else {
        printf(RED"\nNão é possível adicionar mais carros, a fila está cheia!!");
    }
}

void abastecimento(int *tanque, int *fila, float v_comb, int *ca_atnd) {
    int comb_v;
    if (*tanque > 0) {
        if (*fila != 0) {
            do {
                printf(GRN"\nDigite a quantidade de combústivel que deseja abastecer:");
                scanf("%d", &comb_v);
                if (comb_v > *tanque) {
                    printf(YEL"\nCombustível insuficiente, o tanque tem somente %d litros.", *tanque);
                    printf("\nSó é possível abastecer uma quantidade menor ou igual a disponível no tanque.");
                    espera();
                }
            } while (comb_v > *tanque);

            printf(YEL"\nO valor total da compra é de: %.3f", comb_v * v_comb);
            espera();
            printf(GRN"Primeiro carro da fila abastecido");
            *ca_atnd = *ca_atnd + 1;
            *tanque = *tanque - comb_v;
            *fila = *fila - 1;

        } else {
            printf(YEL"\nNão há carros na fila para serem abastecidos!");
        }
    } else {
        printf(RED"\nImpossível abastecer!! O estabelecimento está sem combustível.");
    }
}

void relatorio(int tanque, int ca_atnd, float v_comb){
    char op_print;
    printf(GRN"\t\t\tRelatório de Vendas\n");
    printf("\nA quantidade de litros vendida foi:\n");
    printf("%d litros.\n", 200 - tanque);
    printf("\nO valor total arrecadado com as vendas foi:\n");
    printf("%.3f reais.\n", (200 - tanque) * v_comb);
    printf("\nA quantidade de carros atendidos foi:\n");
    printf("%d carros.\n", ca_atnd);
    printf("\nQuantidade de combustível restante no tanque:\n");
    printf("%d litros.\n", tanque);
    printf("\n\n\nDejesa imprimir o arquivo (S para sim, N para não):");
    setbuf(stdin, NULL);
    scanf("%c", &op_print);
    if(op_print == 'S'){
        printf(GRN"\nArquivo com relatório completo foi enviado para a impressão!\n");
    }else{
        printf(YEL"\nVoltar ao menu relatórios.");
    }       
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
                addcarro(&fila, t_fila);
                break;
            case 2:
                abastecimento(&tanque, &fila, v_comb, &ca_atnd);
                break;
            case 3:
                printf(GRN"Fila de espera: %d carros.", fila);
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
                            break;
                        case 'd':
                            printf(GRN"Quantidade de combustível restante no tanque:\n");
                            printf("%d litros.\n", tanque);
                            break;
                        case 'e':
                            relatorio(tanque, ca_atnd, v_comb);
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
