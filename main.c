#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX 60

void limpaBuffer() {
  while (getchar() != '\n');
}

// Implementação de matéria
typedef struct materia {
  char nome[80];
} T_Materia;

// Implemtação do Nó
typedef struct no {
  T_Materia dado;
  float nota;
  struct no * prox;
}T_NO;

// Implementação de Aluno
typedef struct aluno {
  int rgm;
  T_NO * cabeca;
} T_Aluno;

// Implementação de Sala
typedef struct sala {
  T_Aluno alunos[MAX];
  int n;
} T_Sala;

// Função responsável por iniciar a sala
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

// Verifica se a lista de alunos esta vazia
int listaDeAlunosVazia(T_Sala * sala) {
  return (sala->n == -1);
}
// Verifica se a lista de alunos esta cheia
int listaDeAlunosCheia(T_Sala * sala) {
  return (sala->n == MAX);
}

// Implementação das função de listagem de alunos e matérias
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

// Função responsável por deslocar os elementos da lista de alunos 1 posição à direita
int deslocarDireita(T_Sala * sala, int posicao) {
  int i = 0;

  for(i = sala->n + 1; i > posicao; i--) {
    sala->alunos[i] = sala->alunos[i - 1];
  }

  return 1;
}

// Função responsável por inserir um aluno na lista de alunos de forma ordenada pelo RGM
int insercaoOrdenadaDeAluno(T_Sala * sala, T_Aluno aluno) {
  int posicaoParaInserir = 0;

  if (listaDeAlunosCheia(sala)) {
    return -1;
  }

  if(listaDeAlunosVazia(sala)) {
    sala->alunos[posicaoParaInserir] = aluno;
    (sala->n)++;
    return posicaoParaInserir;
  }

  while ((posicaoParaInserir <= sala->n) && (sala->alunos[posicaoParaInserir].rgm < aluno.rgm)) {
    posicaoParaInserir++;
  }

  if (posicaoParaInserir == sala->n) {
    sala->alunos[posicaoParaInserir + 1] = aluno;
    (sala->n)++;
    return posicaoParaInserir + 1;
  }

  deslocarDireita(sala, posicaoParaInserir);
  sala->alunos[posicaoParaInserir] = aluno;
  (sala->n)++;
  return posicaoParaInserir;
}

// Função responsável por cadastrar um aluno e suas matérias na sala
int cadastrarAlunoEMaterias(T_Sala * sala) {
  T_Aluno novoAluno;
  T_Materia novaMateria;
  T_NO * novoNo;
  float notaMateria = 0.0;
  int opcaoAluno = 0, opcaoMateria = 0;

  if(listaDeAlunosCheia(sala)) {
    printf("Sala cheia\n");
    return 0;
  }

  do {
    printf("Digite o RGM do aluno: ");
    scanf("%d", &novoAluno.rgm);
    novoAluno.cabeca = NULL;
    limpaBuffer();

    int respostaAluno = insercaoOrdenadaDeAluno(sala, novoAluno);

    if(respostaAluno < 0) {
      printf("ERRO - Sala cheia\n");
      return 0;
    }

    do {
      printf("Digite o nome da materia: ");
      scanf("%[^\n]", novaMateria.nome);
      limpaBuffer();
      printf("Digite a nota da materia: "); 
      scanf("%f", &notaMateria);
      limpaBuffer();

      novoNo = criarNo();
      novoNo->dado = novaMateria;
      novoNo->nota = notaMateria;

      if(sala->alunos[respostaAluno].cabeca == NULL) {
        sala->alunos[respostaAluno].cabeca = novoNo;
      } else {
        T_NO * aux = sala->alunos[respostaAluno].cabeca;
        
        // Busca pelo ultimo nó com o valor do proximo no igual a NULL
        while (aux->prox != NULL) {
          aux = aux->prox;
        }

        aux->prox = novoNo;
      }
  
      printf("Mais disciplina? [1 para Sim / 0 para Nao]: ");
      scanf("%d", &opcaoMateria);
      limpaBuffer();
    } while(opcaoMateria);
    


    printf("Mais aluno? [1 para Sim / 0 para Nao]: ");
    scanf("%d", &opcaoAluno);
    limpaBuffer();
    
  } while(opcaoAluno);

  return 1;
  
}

void menu(T_Sala * sala) {
  int opcao = 0;

  printf("-------------------Menu------------------------\n");
  printf("1 - Inserir alunos\n");
  printf("2 - Listar dados dos alunos\n");
  printf("3 - Buscar aluno pelo RGM\n");
  printf("4 - Remover aluno pelo RGM\n");
  printf("5 - Sair\n");
  printf("Digite a opcao desejada [1-5]: ");
  scanf("%d", &opcao);
  limpaBuffer();

  switch (opcao) {
    case 1:
      printf("-----------------------------------------------\n");
      cadastrarAlunoEMaterias(sala);
      menu(sala);
      break;
    case 2:
      printf("-----------------------------------------------\n");
      printf("Listagem de alunos\n");
      listarALunos(sala);
      menu(sala);
      break;
    case 3:
      printf("-----------------------------------------------\n");
      printf("Busca de alunos\n");
      break;
    case 4:
      printf("-----------------------------------------------\n");
      printf("Remocao de alunos\n");
      break;
    case 5:
      printf("-----------------------------------------------\n");
      printf("Obrigado por usar nosso sistema!\n");
      printf("Saindo...\n");
      return;
    default:
      printf("-----------------------------------------------\n");
      printf("* Erro - Opcao invalida *\n");
      menu(sala);
      break;
  }
  
  return;
}

int main() {
  T_Sala minhSala;
  minhSala = iniciarSala();
  // T_Materia novaMateria;
  // T_NO * novoNo;

  // novoNo = criarNo();

  // strcpy(novaMateria.nome, "Matematica");
  // novoNo->dado = novaMateria;
  // novoNo->nota = 7.0;
  // minhSala.n = 2;
  // minhSala.alunos[0].rgm = 1;
  // minhSala.alunos[0].cabeca = novoNo;
  // minhSala.alunos[1].rgm = 2;
  // minhSala.alunos[2].rgm = 3;
  menu(&minhSala);

  return 0;
}