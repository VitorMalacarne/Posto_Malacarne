#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define RED "\e[0;31m"

struct Tcarro {
  char modelo[20], cor[20], cliente[30];
  int ano;
};
typedef struct carro {
  char modelo[20], cor[20], cliente[30];
  int ano, comb_c;
  struct carro *proximo;
} Sca_atnd;

void flush_in();
void espera();
void imprimir(struct Tcarro vetor[], int t);
void printL(Sca_atnd *prox_ca_atnd, Sca_atnd *ini_ca_atnd, float v_comb);
void addcarro(int *fila, int t_fila, struct Tcarro Sfila[]);
int abastecimento(int *tanque, int *fila, float v_comb, struct Tcarro Sfila[], Sca_atnd *prox_ca_atnd);
void relatorio(int tanque, int ca_atnd, float v_comb, Sca_atnd *prox_ca_atnd, Sca_atnd *ini_ca_atnd);