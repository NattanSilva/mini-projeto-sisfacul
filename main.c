#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 60

// Implementação de tipos de dados
typedef struct materia {
  char nome[80];
} T_Materia;

// Implemtação do Nó
typedef struct no {
  T_Materia dado;
  float nota;
  struct no * prox;
}T_NO;

typedef struct aluno {
  int rgm;
  T_NO * cabeca;
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

// Função responsável por criar um novo Nó
T_NO * criarNo() {
  T_NO * no = (T_NO *) malloc(sizeof(T_NO));

  if (no) {
    no->prox = NULL;
  }

  return no;
}

int listaDeAlunosVazia(T_Sala * sala) {
  return (sala->n == -1);
}

int listaDeAlunosCheia(T_Sala * sala) {
  return (sala->n == MAX);
}


void listarALunos(T_Sala * sala) {
  int i = 0;
  T_NO * aux = NULL;

  if(listaDeAlunosVazia(sala)) {
    printf("Nenhum aluno cadastrado nesta sala\n");
    return;
  }

  for(i = 0; i < sala->n + 1; i++) {
    printf("-----------------------------------------------\n");
    printf("RGM: %d\n", sala->alunos[i].rgm);
 
    if(sala->alunos[i].cabeca == NULL) {
      printf("Nenhuma disciplina cadastrada\n");
    }else {
      aux = sala->alunos[i].cabeca;
      printf("Materias\n");
      while (aux != NULL) {
       printf("[%s - %.2f]\n", aux->dado.nome, aux->nota);
       aux = aux->prox;
      }
    }
    
    printf("-----------------------------------------------\n");
  }

  printf("Fim da lista...\n");

  return;
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
      listarALunos(sala);
      menu(sala);
      break;
    case 3:
      printf("Busca de alunos\n");
      break;
    case 4:
      printf("Remocao de alunos\n");
      break;
    case 5:
      printf("Obrigado por user nosso sistema!\n");
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
  T_Materia novaMateria;
  T_NO * novoNo;

  novoNo = criarNo();

  strcpy(novaMateria.nome, "Matematica");
  novoNo->dado = novaMateria;
  novoNo->nota = 7.0;

  minhSala = iniciarSala();
  minhSala.n = 2;
  minhSala.alunos[0].rgm = 1;
  minhSala.alunos[0].cabeca = novoNo;
  minhSala.alunos[1].rgm = 2;
  minhSala.alunos[2].rgm = 3;
  menu(&minhSala);

  return 0;
}