#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 60

// Definição das estruturas
typedef struct materia {
    char nome[80];
} T_Materia;

typedef struct no {
    T_Materia dado;
    float nota;
    struct no *prox;
} T_NO;

typedef struct aluno {
    int rgm;
    T_NO *cabeca;
} T_Aluno;

typedef struct sala {
    T_Aluno alunos[MAX];
    int n;
} T_Sala;

// Função para limpar o buffer de entrada
void limpaBuffer() {
    while (getchar() != '\n');
}

// Função para verificar se a lista de alunos está vazia
int listaDeAlunosVazia(T_Sala *sala) {
    return (sala->n == -1);
}

// Função para remover um aluno pelo RGM
void removerAlunoPorRGM(T_Sala *sala, int rgm) {
    if (listaDeAlunosVazia(sala)) {
        printf("Nenhum aluno cadastrado nesta sala.\n");
        return;
    }

    int indice = -1;
    for (int i = 0; i <= sala->n; i++) {
        if (sala->alunos[i].rgm == rgm) {
            indice = i;
            break;
        }
    }

    if (indice == -1) {
        printf("Aluno com RGM %d não encontrado.\n", rgm);
        return;
    }

    // Liberar a memória das disciplinas associadas
    T_NO *atual = sala->alunos[indice].cabeca;
    while (atual != NULL) {
        T_NO *temp = atual;
        atual = atual->prox;
        free(temp);
    }

    // Remover o aluno da lista sequencial
    for (int i = indice; i < sala->n; i++) {
        sala->alunos[i] = sala->alunos[i + 1];
    }

    // Atualizar o contador de alunos
    sala->n--;

    // Se após a remoção não houver mais alunos, redefina sala->n para -1
    if (sala->n < 0) {
        sala->n = -1;
    }

    printf("Aluno com RGM %d removido com sucesso.\n", rgm);
}

