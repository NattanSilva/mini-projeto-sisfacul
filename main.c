#include <stdio.h>
#include <stdlib.h>
#define MAX 60

// Implementação de tipos de dados
typedef struct materia {
  char nome[80];
  float nota;
} T_Materia;

typedef struct aluno {
  int rgm;
  int n;
} T_Aluno;

typedef struct sala {
  T_Aluno alunos[MAX];
  int n;
} T_Sala;

T_Sala iniciarSala() {
  T_Sala sala;
  sala.n = -1;

  return sala;
}


void listarALunos(T_Sala * sala) {
  int i = 0, j = 0;
  for(i = 0; i < sala->n; i++) {
    printf("");
  }
}

void menu(T_Sala * sala) {
  int opcao = 0;
  printf("-------------Menu-------------\n");
  printf("1 - Inserir alunos\n");
  printf("2 - Listar dados dos alunos\n");
  printf("3 - Buscar aluno pelo RGM\n");
  printf("4 - Remover aluno pelo RGM\n");
  printf("5 - Sair\n");
  printf("Digite a opcao desejada: ");
  scanf("%d", &opcao);

  switch (opcao) {
    case 1:
      printf("Inserir alunos\n");
      break;
    case 2:
      printf("Listagem de alunos\n");
      break;
    case 3:
      printf("Busca de alunos\n");
      break;
    case 4:
      printf("Remocao de alunos\n");
      break;
    case 5:
      printf("Saindo...\n");
      break;
    default:
      printf("Opcao invalida\n");
      menu(sala);
      break;
  }

}

int main() {
  T_Sala minhSala;

  minhSala = iniciarSala();
  menu(&minhSala);

  return 0;
}