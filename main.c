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

// Implementação do Nó
typedef struct no {
  T_Materia dado;
  float nota;
  struct no * prox;
} T_NO;

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

/**
 * @brief Inicializa uma sala de alunos.
 * 
 * Esta função inicializa uma estrutura `T_Sala`, configurando o número de alunos 
 * como -1, o que indica que a sala ainda não possui alunos cadastrados.
 * 
 * @return T_Sala Retorna uma estrutura `T_Sala` inicializada, pronta para armazenar alunos.
*/
T_Sala iniciarSala() {
  T_Sala sala;
  sala.n = -1;

  return sala;
}

/**
 * @brief Cria um novo nó para a lista encadeada.
 * 
 * Esta função aloca dinamicamente memória para um novo nó da lista encadeada. 
 * O novo nó é inicializado com o campo `prox` configurado como `NULL`, indicando 
 * que ele não aponta para nenhum outro nó.
 * 
 * @return T_NO* Retorna um ponteiro para o novo nó criado. Se a alocação falhar, 
 *               retorna `NULL`.
*/
T_NO * criarNo() {
  T_NO * no = (T_NO *) malloc(sizeof(T_NO));

  if (no) {
    no->prox = NULL;
  }

  return no;
}

/**
 * @brief Verifica se a lista de alunos está vazia.
 * 
 * Esta função verifica se a lista de alunos na sala está vazia, ou seja,
 * se o número de alunos registrado é igual a -1. Esse valor indica que 
 * não há alunos cadastrados na sala.
 * 
 * @param sala Ponteiro para a estrutura T_Sala que contém os alunos.
 * @return int Retorna 1 se a lista de alunos estiver vazia (ou seja, o número de alunos é igual a -1),
 *             e 0 caso contrário.
*/
int listaDeAlunosVazia(T_Sala * sala) {
  return (sala->n == -1);
}

/**
 * @brief Verifica se a lista de alunos está cheia.
 * 
 * Esta função verifica se o número atual de alunos na sala atingiu o valor máximo
 * permitido, retornando um valor booleano para indicar se a lista está cheia ou não.
 * 
 * @param sala Ponteiro para a estrutura T_Sala que contém os alunos.
 * @return int Retorna 1 se a lista de alunos estiver cheia (ou seja, o número de alunos é igual a MAX), 
 *             e 0 caso contrário.
*/
int listaDeAlunosCheia(T_Sala * sala) {
  return (sala->n == MAX);
}

/**
 * Lista todos os alunos cadastrados na sala e suas respectivas disciplinas.
 * 
 * @param sala  Ponteiro para a estrutura `T_Sala`, que contém a lista de alunos.
 * 
 * Descrição:
 * - Verifica se a lista de alunos está vazia (`listaDeAlunosVazia(sala)`).  
 *   - Se estiver vazia, exibe uma mensagem e retorna.  
 * - Percorre todos os alunos da sala usando um loop `for` que vai de `0` até `sala->n` (última posição ocupada).  
 * - Para cada aluno, exibe o **RGM** e verifica se ele possui disciplinas cadastradas.  
 *   - Se não houver disciplinas (`cabeca == NULL`), imprime `"Nenhuma disciplina cadastrada"`.  
 *   - Caso contrário, percorre a lista encadeada de disciplinas e exibe **nome e nota**.  
 * - Exibe `"Fim da lista..."` ao final da listagem.   
*/
void listarALunos(T_Sala * sala) {
  int i = 0;
  T_NO * aux = NULL;

  if(listaDeAlunosVazia(sala)) {
    printf("Nenhum aluno cadastrado nesta sala\n");
    return;
  }

  for(i = 0; i <= sala->n; i++) {
    printf("-----------------------------------------------\n");
    printf("RGM: %d\n", sala->alunos[i].rgm);
 
    if(sala->alunos[i].cabeca == NULL) {
      printf("Nenhuma disciplina cadastrada\n");
    } else {
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

/**
 * @brief Busca um aluno pelo RGM na sala.
 * 
 * Esta função percorre a lista de alunos na sala e verifica se o RGM informado
 * corresponde ao RGM de algum aluno. Caso o aluno seja encontrado, são exibidas 
 * as informações do aluno, incluindo as matérias e suas respectivas notas. Caso contrário, 
 * é exibida uma mensagem informando que o aluno não foi encontrado.
 * 
 * @param sala Ponteiro para a estrutura T_Sala onde os alunos estão armazenados.
 * @param rgm  O RGM do aluno a ser buscado.
 */
void buscarAlunoPorRGM(T_Sala * sala, int rgm) {
  int i = 0;
  T_NO * aux = NULL;
  int encontrado = 0;

  // Verifica se a lista de alunos está vazia
  if (listaDeAlunosVazia(sala)) {
    printf("Nenhum aluno cadastrado nesta sala.\n");
    return;
  }

  // Percorre a lista de alunos
  for (i = 0; i <= sala->n; i++) {
    // Se o RGM do aluno for encontrado
    if (sala->alunos[i].rgm == rgm) {
      encontrado = 1;
      printf("Aluno encontrado: \n");
      printf("RGM: %d\n", sala->alunos[i].rgm);

      // Verifica se o aluno tem matérias cadastradas
      if (sala->alunos[i].cabeca == NULL) {
        printf("Nenhuma disciplina cadastrada.\n");
      } else {
        aux = sala->alunos[i].cabeca;
        printf("Materias: \n");
        while (aux != NULL) {
          printf("[%s - %.2f]\n", aux->dado.nome, aux->nota);
          aux = aux->prox;
        }
      }
      break;
    }
  }

  // Se não encontrou o aluno
  if (!encontrado) {
    printf("Aluno com RGM %d não encontrado.\n", rgm);
  }
}

/**
 * Desloca os elementos da lista de alunos uma posição à direita a partir de um índice específico.
 * 
 * @param sala     Ponteiro para a estrutura `T_Sala`, que contém a lista de alunos.
 * @param posicao  Índice a partir do qual os elementos serão deslocados.
 * @return         Retorna 1 se o deslocamento for bem-sucedido.
 *                 Retorna 0 se a posição for inválida.
 * 
 * Descrição:
 * - Antes de iniciar o deslocamento, a função verifica se `posicao` é válida:
 *   - `posicao < 0`: Não pode ser um índice negativo.
 *   - `posicao > sala->n`: Não pode ser maior que o número de alunos.
 *   - `posicao >= MAX`: Não pode ultrapassar o limite máximo do array.
 * - Se a posição for inválida, retorna 0 e não realiza a operação.
 * - Caso seja válida, desloca os elementos da lista uma posição à direita.
 * - O deslocamento começa da última posição ocupada (`sala->n + 1`) até `posicao + 1`.
 * - Isso cria espaço para a inserção de um novo aluno sem sobrescrever dados existentes.
 * 
 * ⚠️ Atenção:
 * - Certifique-se de que `sala->n` foi atualizado corretamente antes da chamada desta função.
 * - A função não atualiza `sala->n`, pois isso deve ser feito pela função de inserção.
 * - O array deve ter espaço disponível para evitar estouro de memória (overflow).
*/
int deslocarDireita(T_Sala * sala, int posicao) {
  int i = 0;

  if(posicao < 0 || posicao > sala->n || posicao >= MAX) {
    return 0;
  }

  for(i = sala->n + 1; i > posicao; i--) {
    sala->alunos[i] = sala->alunos[i - 1];
  }

  return 1;
}

/**
 * Insere um aluno na lista de forma ordenada pelo RGM.
 * 
 * @param sala   Ponteiro para a estrutura `T_Sala`, que contém a lista de alunos.
 * @param aluno  Estrutura `T_Aluno` contendo os dados do aluno a ser inserido.
 * @return       Retorna a posição em que o aluno foi inserido.
 *               Retorna -1 se a sala estiver cheia.
 * 
 * Descrição:
 * - Se a sala estiver cheia, a função retorna -1, indicando erro.
 * - Se a lista estiver vazia, insere o aluno na primeira posição e retorna 0.
 * - Caso contrário, percorre a lista até encontrar a posição correta para manter a ordem crescente do RGM.
 * - Se o aluno deve ser inserido no final da lista, adiciona diretamente na última posição disponível.
 * - Se precisar inserir no meio, desloca os elementos à direita antes da inserção.
 * - Atualiza o número de alunos (`sala->n`) após uma inserção bem-sucedida.
 */
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

/**
 * @brief Cadastra um aluno na sala e permite adicionar suas matérias.
 * 
 * Esta função solicita ao usuário o RGM de um novo aluno e o adiciona à 
 * lista ordenada de alunos na sala. Após isso, permite o cadastro de 
 * matérias para esse aluno, armazenando-as em uma lista encadeada.
 * 
 * @param sala Ponteiro para a estrutura T_Sala onde os alunos estão armazenados.
 * @return int Retorna 1 se o cadastro for bem-sucedido, 0 se a sala estiver cheia.
*/
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
      int rgmBusca;
      printf("Digite o RGM do aluno a ser buscado: ");
      scanf("%d", &rgmBusca);
      buscarAlunoPorRGM(sala, rgmBusca);  // Chama a função de busca
      menu(sala);
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
  menu(&minhSala);

  return 0;
}
