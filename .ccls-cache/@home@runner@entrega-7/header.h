#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define RED "\e[0;31m"

struct Tcarro {
  char modelo[20], cor[20], cliente[30];
  int ano;
};

void flush_in();
void espera();
void imprimir(struct Tcarro vetor[], int t);
void addcarro(int *fila, int t_fila, struct Tcarro Sfila[]);
void abastecimento(int *tanque, int *fila, float v_comb, int *ca_atnd,
                   struct Tcarro Sfila[], struct Tcarro Sca_atnd[]);
void relatorio(int tanque, int ca_atnd, float v_comb, struct Tcarro Sca_atnd[]);