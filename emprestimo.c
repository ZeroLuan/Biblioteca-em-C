#include "emprestimo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void emprestarLivro(Biblioteca *livro, int numLivros, Usuarios *usuario, int numUsuarios, Emprestimo **emprestimo, int *tamanhoEmprestimos, int *posicaoVetor_usuario, int *posicaoVetor_livro) {

  int sair;

  int acharCodigoUsuario = buscaUsuario(usuario, &numUsuarios, posicaoVetor_usuario);

  if (acharCodigoUsuario == -1) {
    do {
      printf("\nUsuario nao encontrado\n");
      printf("\nPara sair digite: 0, para tentar novamente aperte: 1 \n\n");
      scanf("%d", &sair);

      if (sair == 0) {
        printf("Erro ao achar código de usuário");
        return;
      } else if (sair == 1) {
        acharCodigoUsuario = buscaUsuario(usuario, &numUsuarios, posicaoVetor_usuario);
      }

    } while (acharCodigoUsuario == -1);
  }

  int acharCodigoLivro = buscaLivro(livro, &numLivros, posicaoVetor_livro);

  if (acharCodigoLivro == -1) {
    do {
      printf("\nLivro nao encontrado\n");
      printf("\nPara sair digite: 0, para tentar novamente aperte: 1 \n\n");
      scanf("%d", &sair);

      if (sair == 0) {
        printf("Erro ao achar código de livro");
        return;
      } else if (sair == 1) {
        acharCodigoLivro = buscaLivro(livro, &numLivros, posicaoVetor_livro);
      }

    } while (acharCodigoLivro == -1);
  }

  //----------

  (*tamanhoEmprestimos)++;

  *emprestimo = (Emprestimo *)realloc(*emprestimo, sizeof(Emprestimo) * (*tamanhoEmprestimos));

  if (*emprestimo == NULL) {
    printf("\nErro ao alocar memoria");
    exit(1);
  }

  Emprestimo *dados_temp = (Emprestimo *)malloc(sizeof(Emprestimo));

  if (dados_temp == NULL) {
    printf("\nErro ao alocar memoria");
    exit(1);
  }

  printf("\nDigite a data de emprestimo: ");
  scanf(" %[^\n]s", dados_temp->data_emprestimo);

  printf("\nDigite a data de devolucao: ");
  scanf(" %[^\n]s", dados_temp->data_devolucao);

  (*emprestimo)[*tamanhoEmprestimos - 1].id_usuario = usuario[*posicaoVetor_usuario].ids;
  (*emprestimo)[*tamanhoEmprestimos - 1].codigo_livro = livro[*posicaoVetor_livro].codLivros;
  strcpy((*emprestimo)[*tamanhoEmprestimos - 1].data_emprestimo, dados_temp->data_emprestimo);
  strcpy((*emprestimo)[*tamanhoEmprestimos - 1].data_devolucao, dados_temp->data_devolucao);
  (*emprestimo)[*tamanhoEmprestimos - 1].quantidade_emprestada = 1;

  livro[*posicaoVetor_livro].quantidades--;

  free(dados_temp);

  FILE *arquivoLivros;
  arquivoLivros = fopen("baseDadosLivros.txt", "w");

  if (arquivoLivros == NULL) {
    printf("\nErro ao abrir o arquivo para edicao\n");
    exit(1);
  }

  for (int i = 0; i < numLivros; i++) {
    fprintf(arquivoLivros, "Titulo: %s\n", livro[i].titulos);
    fprintf(arquivoLivros, "Autor: %s\n", livro[i].autores);
    fprintf(arquivoLivros, "Codigo: %d\n", livro[i].codLivros);
    fprintf(arquivoLivros, "Categoria: %s\n", livro[i].categorias);
    fprintf(arquivoLivros, "Quantidade: %d\n", livro[i].quantidades);
    fprintf(arquivoLivros, "\n");
  }

  fclose(arquivoLivros);

  FILE *arquivoEmprestimos;
  arquivoEmprestimos = fopen("baseDadosEmprestimos.txt", "a");

  if (arquivoEmprestimos == NULL) {
    printf("\nErro ao abrir o arquivo de emprestimos\n");
    exit(1);
  }

  fprintf(arquivoEmprestimos, "ID Usuario: %d\n",(*emprestimo)[*tamanhoEmprestimos - 1].id_usuario);
  fprintf(arquivoEmprestimos, "Codigo Livro: %d\n",(*emprestimo)[*tamanhoEmprestimos - 1].codigo_livro);
  fprintf(arquivoEmprestimos, "Data Emprestimo: %s\n",(*emprestimo)[*tamanhoEmprestimos - 1].data_emprestimo);
  fprintf(arquivoEmprestimos, "Data Devolucao: %s\n",(*emprestimo)[*tamanhoEmprestimos - 1].data_devolucao);
  fprintf(arquivoEmprestimos, "Qtd Emprestada: %d\n",(*emprestimo)[*tamanhoEmprestimos - 1].quantidade_emprestada);
  fprintf(arquivoEmprestimos, "\n");

  fclose(arquivoEmprestimos);

  //-----------

  printf("\n======================================\n");
  printf("\nLivro emprestado com sucesso !");
  printf("\n\nAtual quantidade desse livro na biblioteca: %d", livro[*posicaoVetor_livro].quantidades);
  printf("\n\nContador de emprestimos: %d", *tamanhoEmprestimos);
  printf("\n\nQtd emprestada do user ID: %d / QTD: %d\n", (*emprestimo)[*tamanhoEmprestimos - 1].id_usuario,
         (*emprestimo)[*tamanhoEmprestimos - 1].quantidade_emprestada);
  printf("\n======================================\n");
}

void devolverLivro(Biblioteca *livro, int numLivros, Usuarios *usuario, int numUsuarios, Emprestimo **emprestimo, int *tamanhoEmprestimos, int *posicaoVetor_usuario, int *posicaoVetor_livro) {

  int sair;

  int acharCodigoUsuario = buscaUsuario(usuario, &numUsuarios, posicaoVetor_usuario);

  int acharTituloLivro = buscaLivro(livro, &numLivros, posicaoVetor_livro);

  if (acharCodigoUsuario == -1 && acharTituloLivro == -1) {
    printf("\nUsuario e livro não encontrados\n");
    printf("\nTente Novamente\n");
    return;
  }

  if ((*emprestimo)[*posicaoVetor_usuario].quantidade_emprestada > 0) {

    livro[*posicaoVetor_livro].quantidades++;
    (*emprestimo)[*posicaoVetor_usuario].quantidade_emprestada--;

    for (int i = *posicaoVetor_usuario; i < *tamanhoEmprestimos - 1; i++) {
      (*emprestimo)[i] = (*emprestimo)[i + 1];
    }

    (*tamanhoEmprestimos)--;

    FILE *arquivoLivros;
    arquivoLivros = fopen("baseDadosEmpresimo.txt", "w");

    if (arquivoLivros == NULL) {
      printf("\nErro ao abrir o arquivo para edicao\n");
      exit(1);
    }

    for (int i = 0; i < numLivros; i++) {
      fprintf(arquivoLivros, "Titulo: %s\n", livro[i].titulos);
      fprintf(arquivoLivros, "Autor: %s\n", livro[i].autores);
      fprintf(arquivoLivros, "Codigo: %d\n", livro[i].codLivros);
      fprintf(arquivoLivros, "Categoria: %s\n", livro[i].categorias);
      fprintf(arquivoLivros, "Quantidade: %d\n", livro[i].quantidades);
      fprintf(arquivoLivros, "\n");
    }

    fclose(arquivoLivros);

    FILE *arquivoEmprestimos;
    arquivoEmprestimos = fopen("baseDadosEmprestimo.txt", "w");

    if (arquivoEmprestimos == NULL) {
      printf("\nErro ao abrir o arquivo de emprestimos\n");
      exit(1);
    }

    for (int i = 0; i < *tamanhoEmprestimos; i++) {
      fprintf(arquivoEmprestimos, "ID Usuario: %d\n", (*emprestimo)[i].id_usuario);
      fprintf(arquivoEmprestimos, "Codigo Livro: %d\n", (*emprestimo)[i].codigo_livro);
      fprintf(arquivoEmprestimos, "Data Emprestimo: %s\n", (*emprestimo)[i].data_emprestimo);
      fprintf(arquivoEmprestimos, "Data Devolucao: %s\n", (*emprestimo)[i].data_devolucao);
      fprintf(arquivoEmprestimos, "Quantidade Emprestada: %d\n", (*emprestimo)[i].quantidade_emprestada);
      fprintf(arquivoEmprestimos, "\n");
    }

    fclose(arquivoEmprestimos);

    printf("\n======================================\n");
    printf("\nLivro devolvido com sucesso !");
    printf("\n\nAtual quantidade desse livro na biblioteca: %d", livro[*posicaoVetor_livro].quantidades);
    printf("\n\nContador de emprestimos: %d", *tamanhoEmprestimos);
    printf("\n\nQuantidade emprestada do user ID: %d / QTD: %d\n", (*emprestimo)[*posicaoVetor_usuario].id_usuario, (*emprestimo)[*posicaoVetor_usuario].quantidade_emprestada);
    printf("\n======================================\n");
  } else {
    printf("\nO usuario nao possui emprestimos deste livro.\n");
  }
}

void relatorioEmprestimosAtraso(Emprestimo **emprestimos, int *tamanhoEmprestimos) {

}


void relatorioEmprestimos(Emprestimo **emprestimo, int tamanhoEmprestimos) {

  for (int i = 0; i < tamanhoEmprestimos; i++) {
    printf("======================================");
    printf("\nId Usuario: %d\n", emprestimo[i]->id_usuario);
    printf("\nCodigo livro: %d\n", emprestimo[i]->codigo_livro);
    printf("\nData de emprestimo: %s\n", emprestimo[i]->data_emprestimo);
    printf("\nData devolucao: %s\n", emprestimo[i]->data_devolucao);
    printf("\nQuantidade emprestado do user ID: %d / QTD: %d\n", emprestimo[i]->id_usuario, emprestimo[i]->quantidade_emprestada);
    printf("======================================\n");
  }
}