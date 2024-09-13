#include "usuarios.h"
#include "livros.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int buscaUsuario(Usuarios *usuario, int *numUsuarios,
                 int *posicaoVetor_usuario) {

  int buscarID = 0;
  int guardaPosicao = 0;

  printf("\nDigite o ID do usuario: ");
  scanf("%d", &buscarID);

  for (int i = 0; i < *numUsuarios; i++) {
    if (buscarID == usuario[i].ids) {

      guardaPosicao = 1;
      *posicaoVetor_usuario = i;

      printf("\nNome do User: %s, ID: %d\n", usuario[i].nomes, usuario[i].ids);

      return guardaPosicao;

    } else {

      guardaPosicao = -1;
    }
  }

  return guardaPosicao;
}

void cadastrarUsuario(Usuarios **usuario, int *numUsuarios) {

  (*numUsuarios)++;

  *usuario = (Usuarios *)realloc(*usuario, sizeof(Usuarios) * (*numUsuarios));

  if (*usuario == NULL) {
    printf("\nErro ao alocar memoria");
    exit(1);
  }

  Usuarios *novoUsuario = (Usuarios *)malloc(sizeof(Usuarios));

  if (novoUsuario == NULL) {
    printf("\nErro ao alocar memoria");
    exit(1);
  }

  printf("\nDigite o Nome do usuario: ");
  scanf(" %[^\n]s", novoUsuario->nomes);

  printf("\nDigite a ID do usuario: ");
  scanf("%d", &novoUsuario->ids);

  printf("\nDigite o Telefone do usuario: ");
  scanf(" %[^\n]s", novoUsuario->telefones);

  (*usuario)[*numUsuarios - 1] = novoUsuario[0];

  FILE *arquivo;
  arquivo = fopen("baseDadosUsuarios.txt", "a");

  if (arquivo == NULL) {
    printf("\nErro ao abrir o arquivo");
    exit(1);
  }

  fprintf(arquivo, "Nome: %s\n", novoUsuario->nomes);
  fprintf(arquivo, "ID: %d\n", novoUsuario->ids);
  fprintf(arquivo, "Telefone: %s\n", novoUsuario->telefones);
  fprintf(arquivo, "\n");

  fclose(arquivo);

  free(novoUsuario);
}

void editarUsuario(Usuarios *usuario, int *numUsuarios,
                   int *posicaoVetor_usuario) {

  int encontrarUsuario =
      buscaUsuario(usuario, numUsuarios, posicaoVetor_usuario);
  int opcao = 0;

  if (encontrarUsuario == -1) {
    printf("\nUsuario nao encontrado");
    printf("\nTente Novamente");
  } else {
    printf("\nQual informacao vai mudar ? \n\n");
    printf("1 - Nome\n");
    printf("2 - ID\n");
    printf("3 - Telefone\n");
    scanf("\n%d", &opcao);
    switch (opcao) {
    case 1:
      printf("\nDigite novo Nome: ");
      scanf(" %[^\n]s", usuario[*posicaoVetor_usuario].nomes);
      break;
    case 2:
      printf("\nDigite novo ID: ");
      scanf(" %d", &usuario[*posicaoVetor_usuario].ids);
      break;
    case 3:
      printf("\nDigite o novo Telefone: ");
      scanf(" %[^\n]s", usuario[*posicaoVetor_usuario].telefones);
      break;
    }

    FILE *arquivo;
    arquivo = fopen("baseDadosUsuarios.txt", "w");

    if (arquivo == NULL) {
      printf("\nErro ao abrir o arquivo para edicao\n");
      exit(1);
    }

    for (int i = 0; i < *numUsuarios; i++) {
      fprintf(arquivo, "Usuario: %s\n", usuario[i].nomes);
      fprintf(arquivo, "ID: %d\n", usuario[i].ids);
      fprintf(arquivo, "Telefone: %s\n", usuario[i].telefones);
      fprintf(arquivo, "\n");
    }

    fclose(arquivo);

    printf("\nInformacoes do livro atualizadas com sucesso no arquivo.\n");
  }
}

void excluirUsuario(Usuarios **usuario, int *numUsuarios, int *posicaoVetor_usuario) {
  
  int encontrarUsuario = buscaUsuario(*usuario, numUsuarios, posicaoVetor_usuario);

  if (encontrarUsuario == -1) {
    printf("\nUsuario nao encontrado\n");
    printf("Tente Novamente\n");
  } else {
    
    for (int i = *posicaoVetor_usuario; i < *numUsuarios - 1; i++) {
      (*usuario)[i] = (*usuario)[i + 1];
    }

    (*numUsuarios)--;

    *usuario = realloc(*usuario, sizeof(Usuarios) * (*numUsuarios));

    if (*usuario == NULL) {
      printf("\nErro ao realocar memoria\n");
      exit(1);
    }

    FILE *arquivo;
    arquivo = fopen("baseDadosUsuarios.txt", "w");

    if (arquivo == NULL) {
      printf("\nErro ao abrir o arquivo para edicao\n");
      exit(1);
    }

    for (int i = 0; i < *numUsuarios; i++) {
      fprintf(arquivo, "Nome: %s\n", (*usuario)[i].nomes);
      fprintf(arquivo, "IDS: %d\n", (*usuario)[i].ids);
      fprintf(arquivo, "Telefone: %s\n", (*usuario)[i].telefones);
      fprintf(arquivo, "\n");
    }

    fclose(arquivo);

    printf("\nUsuario excluido do arquivo e do vetor com sucesso.\n");
  }
}

void listarTodosUsuarios(Usuarios *usuario, int *numUsuarios) {

  for (int i = 0; i < *numUsuarios; i++) {

    printf("======================================");

    printf("\nNome do Usuario: %s\n", usuario[i].nomes);

    printf("\nNumero da ID: %d\n", usuario[i].ids);

    printf("\nTelefone: %s\n", usuario[i].telefones);

    printf("======================================\n");
  }
}