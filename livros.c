#include "livros.h"
#include "usuarios.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int buscaLivro(Biblioteca *livro, int *numLivros, int *posicaoVetor_livro) {

  char tituloBuscarLivro[100];
  int guardaPosicao = 0;

  printf("\nDigite o titulo do livro: ");
  scanf(" %[^\n]s", tituloBuscarLivro);

  for (int i = 0; i < *numLivros; i++) {
    if (strcmp(tituloBuscarLivro, livro[i].titulos) == 0) {

      guardaPosicao = 1;
      *posicaoVetor_livro = i;

      printf("\nTitulo da obra: %s, ID: %d\n", livro[i].titulos, livro[i].codLivros);

      return guardaPosicao;

    } else {
      guardaPosicao = -1;
    }
  }
  return guardaPosicao;
}

void cadastrarLivro(Biblioteca **livro, int *numLivros) {

  (*numLivros)++;

  *livro = (Biblioteca *) realloc(*livro, sizeof(Biblioteca) * (*numLivros));

  if (*livro == NULL) {
    printf("\nErro ao alocar memoria");
    exit(1);
  }

  Biblioteca *novoLivro = (Biblioteca *) malloc(sizeof(Biblioteca));

  if (novoLivro == NULL) {
    printf("\nErro ao alocar memoria");
    exit(1);
  }

  printf("\nDigite o Titulo do livro: ");
  scanf(" %[^\n]s", novoLivro->titulos);

  printf("\nDigite o Autor do livro: ");
  scanf(" %[^\n]s", novoLivro->autores);

  printf("\nDigite o Codigo do livro: ");
  scanf("%d", &novoLivro->codLivros);

  printf("\nDigite a Categoria do livro: ");
  scanf(" %[^\n]s", novoLivro->categorias);

  printf("\nDigite a Quantidade do livro: ");
  scanf("%d", &novoLivro->quantidades);

  (*livro)[*numLivros - 1] = novoLivro[0];

  FILE *arquivo;
  arquivo = fopen("baseDadosLivros.txt", "a");

  if (arquivo == NULL) {
    printf("\nErro ao abrir o arquivo");
    exit(1);
  }

  fprintf(arquivo, "Titulo: %s\n", novoLivro->titulos);
  fprintf(arquivo, "Autor: %s\n", novoLivro->autores);
  fprintf(arquivo, "Codigo: %d\n", novoLivro->codLivros);
  fprintf(arquivo, "Categoria: %s\n", novoLivro->categorias);
  fprintf(arquivo, "Quantidade: %d\n", novoLivro->quantidades);
  fprintf(arquivo, "\n");

  fclose(arquivo);

  free(novoLivro);
}

void editarLivro(Biblioteca *livro, int *numLivros, int *posicaoVetor_livro) {

  int encontrarLivro = buscaLivro(livro, numLivros, posicaoVetor_livro);
  int opcao = 0;

  if (encontrarLivro == -1) {
    printf("\nLivro nao encontrado\n");
    printf("Tente Novamente\n");
  } else {
    printf("\nQual informacao vai mudar ? \n\n");
    printf("1 - Titulo\n");
    printf("2 - Autor\n");
    printf("3 - Categoria\n");
    printf("4 - Codigo\n");
    printf("5 - Quantidade\n");
    scanf("%d", &opcao);

    switch (opcao) {
    case 1:
      printf("\nDigite novo Titulo do livro: ");
      scanf(" %[^\n]s", livro[*posicaoVetor_livro].titulos);
      break;
    case 2:
      printf("\nDigite novo Autor do livro: ");
      scanf(" %[^\n]s", livro[*posicaoVetor_livro].autores);
      break;
    case 3:
      printf("\nDigite uma nova Categoria do livro: ");
      scanf(" %[^\n]s", livro[*posicaoVetor_livro].categorias);
      break;
    case 4:
      printf("\nDigite o novo Codigo do livro: ");
      scanf("%d", &livro[*posicaoVetor_livro].codLivros);
      break;
    case 5:
      printf("\nDigite uma nova Quantidade do livro: ");
      scanf("%d", &livro[*posicaoVetor_livro].quantidades);
      break;
    default:
      printf("\nOpcao invalida\n");
      return;
    }

    FILE *arquivo;
    arquivo = fopen("baseDadosLivros.txt", "w");

    if (arquivo == NULL) {
      printf("\nErro ao abrir o arquivo para edicao\n");
      exit(1);
    }

    for (int i = 0; i < *numLivros; i++) {
      fprintf(arquivo, "Titulo: %s\n", livro[i].titulos);
      fprintf(arquivo, "Autor: %s\n", livro[i].autores);
      fprintf(arquivo, "Codigo: %d\n", livro[i].codLivros);
      fprintf(arquivo, "Categoria: %s\n", livro[i].categorias);
      fprintf(arquivo, "Quantidade: %d\n", livro[i].quantidades);
      fprintf(arquivo, "\n");
    }

    fclose(arquivo);

    printf("\nInformacoes do livro atualizadas com sucesso no arquivo.\n");
  }
}

void excluirLivro(Biblioteca **livro, int *numLivros, int *posicaoVetor_livro) {

  int encontrarLivro = buscaLivro(*livro, numLivros, posicaoVetor_livro);

  if (encontrarLivro == -1) {
    printf("\nLivro nao encontrado\n");    
    printf("Tente Novamente\n");
  } else {
    
    for(int i = *posicaoVetor_livro; i < *numLivros - 1; i++) {
      (*livro)[i] = (*livro)[i + 1];
    }

    (*numLivros)--;

    *livro = realloc(*livro, sizeof(Biblioteca) * (*numLivros));

    if (*livro == NULL) {
      printf("\nErro ao realocar memoria\n");
      exit(1);
    }

    FILE *arquivo;
    arquivo = fopen("baseDadosLivros.txt", "w");

    if (arquivo == NULL) {
      printf("\nErro ao abrir o arquivo para edicao\n");
      exit(1);
    }

    for (int i = 0; i < *numLivros; i++) {
      fprintf(arquivo, "Titulo: %s\n", (*livro)[i].titulos);
      fprintf(arquivo, "Autor: %s\n", (*livro)[i].autores);
      fprintf(arquivo, "Codigo: %d\n", (*livro)[i].codLivros);
      fprintf(arquivo, "Categoria: %s\n", (*livro)[i].categorias);
      fprintf(arquivo, "Quantidade: %d\n", (*livro)[i].quantidades);
      fprintf(arquivo, "\n");
    }

    fclose(arquivo);

    printf("\nLivro excluido do arquivo e do vetor com sucesso.\n");
  }
}

void listarTodosLivros(Biblioteca *livro, int *numLivros) {

  for (int i = 0; i < *numLivros; i++) {

    printf("======================================");

    printf("\nTutulo do Livro: %s\n", livro[i].titulos);

    printf("\nAutor do Livro: %s\n", livro[i].autores);

    printf("\nCategoria do Livro: %s\n", livro[i].categorias);

    printf("\nCodigo do Livro: %d\n", livro[i].codLivros);

    printf("\nQuantidade do Livro: %d\n", livro[i].quantidades);

    printf("======================================\n");
  }
}