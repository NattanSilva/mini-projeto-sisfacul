/**
 * @brief Remove um aluno da sala pelo RGM.
 * 
 * Esta função procura o aluno com o RGM informado. Se encontrado:
 * - Libera todas as matérias (lista encadeada) desse aluno.
 * - Remove o aluno da lista sequencial (vetor).
 * - Atualiza a quantidade total de alunos na sala.
 * 
 * @param sala Ponteiro para a estrutura T_Sala.
 * @param rgm  RGM do aluno a ser removido.
 * @return int 1 se remover com sucesso, 0 se não encontrar.
*/
int removerAlunoPorRGM(T_Sala * sala, int rgm) {
  if (listaDeAlunosVazia(sala)) {
    printf("Nenhum aluno cadastrado.\n");
    return 0;
  }

  int i, j;
  for (i = 0; i <= sala->n; i++) {
    if (sala->alunos[i].rgm == rgm) {
      // Libera lista encadeada de matérias
      T_NO * atual = sala->alunos[i].cabeca;
      T_NO * temp;
      while (atual != NULL) {
        temp = atual;
        atual = atual->prox;
        free(temp); // libera cada nó
      }

      // Desloca os alunos à esquerda (remove o aluno do vetor)
      for (j = i; j < sala->n; j++) {
        sala->alunos[j] = sala->alunos[j + 1];
      }

      sala->n--; // atualiza o número de alunos
      printf("Aluno com RGM %d removido com sucesso!\n", rgm);
      return 1;
    }
  }

  printf("Aluno com RGM %d não encontrado.\n", rgm);
  return 0;
}
