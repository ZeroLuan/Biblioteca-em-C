#include "emprestimo.h"
#include "hora.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void data_hora();

int main() {

  int menu_principal = 0;

  int numLivros = 0;
  int numUsuarios = 0;
  int tamanhoEmprestimos = 0;

  int posicaoVetor_usuarios;
  int posicaoVetor_livros;

  Biblioteca *livros = (Biblioteca *) malloc(numLivros * sizeof(Biblioteca));

  Usuarios *usuarios = (Usuarios *) malloc(numUsuarios * sizeof(Usuarios));

  Emprestimo *emprestimos = (Emprestimo *) malloc(tamanhoEmprestimos * sizeof(Emprestimo));

  do { 

    data_hora();

    printf("\n\nEscolha Uma Opcao:\n\n");
    printf("1. Gerenciar Livros\n");
    printf("2. Gerenciar Usuarios\n");
    printf("3. Gerenciar Emprestimos\n");
    printf("4. Limpar tela\n");
    printf("10. Sair\n\n");
    scanf("%d", &menu_principal);

    switch (menu_principal) {

    case 1:

      system("cls");

      data_hora();

      do {
        printf("\n\nGerenciar Livros ->\n\n");
        printf("1. Cadastrar Novo Livro\n");
        printf("2. Editar Livro\n");
        printf("3. Excluir Livro\n");
        printf("4. Listar Todos os Livos\n");
        printf("5. Buscar Livro Por Titulo ou Autor\n");
        printf("0. <- Voltar ao Menu Anterior\n\n");
        scanf("%d", &menu_principal);

        switch (menu_principal) {

        case 1:
          system("cls");
          cadastrarLivro (&livros, &numLivros);
          system("cls");
          printf("\nLivro cadastrado !");
          break;
        case 2:
          system("cls");
          editarLivro (livros, &numLivros, &posicaoVetor_livros);
          system("cls");
          break;
        case 3:
          system("cls");
          excluirLivro (&livros, &numLivros, &posicaoVetor_livros);
          system("cls");
          break;
        case 4:
          system("cls");
          listarTodosLivros (livros, &numLivros);
          break;
        case 5:
          system("cls");
          buscaLivro (livros, &numLivros, &posicaoVetor_livros);
          break;
        case 0:
          menu_principal = 0;
          system("cls");
          break;
        default:
          printf("\nOpcao invalida. Tente novamente...");
        }

      } while (menu_principal != 0);

    break;

    case 2:

      system("cls");

      data_hora();

      do{
        printf("\n\nGerenciar Usuario ->\n\n");
        printf("1. Cadastrar Novo Usuario\n");
        printf("2. Editar Usuario\n");
        printf("3. Excluir Usuario\n");
        printf("4. Listar Todos os Usuario\n");
        printf("5. Buscar Usuario Pelo Nome ou ID\n");
        printf("0. <- Voltar ao Menu Anterior\n\n");
        scanf("%d", &menu_principal);

        switch (menu_principal) {

        case 1:
          system("cls");
          cadastrarUsuario(&usuarios, &numUsuarios);
          system("cls");
          printf("\nCadastro do Usuario concluido !");
          break;
        case 2:
          system("cls");
          editarUsuario(usuarios, &numUsuarios, &posicaoVetor_usuarios);
          break;
        case 3:
          system("cls");
          excluirUsuario(&usuarios, &numUsuarios, &posicaoVetor_usuarios);
          break;
        case 4:
          system("cls");
          listarTodosUsuarios(usuarios, &numUsuarios);
          break;
        case 5:
          system("cls");
          buscaUsuario (usuarios, &numUsuarios, &posicaoVetor_usuarios);
          break;
        case 0:
          menu_principal = 0;
          system("cls");
          break;
        default:
          printf("\nOpcao invalida. Tente novamente...");
        }

      } while (menu_principal != 0);

    break;

    case 3:

      system("cls");

      data_hora();

      do {
        printf("\n\nGerenciar Empretimos ->\n\n");
        printf("1. Registar Emprestimo\n");
        printf("2. Devolver Livro\n");
        printf("3. Verificar Livros em Atraso\n");
        printf("4. Exibir emprestimos\n");
        printf("0. <- Voltar ao Menu Anterior\n\n");
        scanf("%d", &menu_principal);

        switch (menu_principal) {

        case 1:
          system("cls");
          emprestarLivro(livros, numLivros, usuarios, numUsuarios, &emprestimos, &tamanhoEmprestimos, &posicaoVetor_usuarios, &posicaoVetor_livros);
          break;
        case 2:
          system("cls");
          devolverLivro(livros, numLivros, usuarios, numUsuarios, &emprestimos, &tamanhoEmprestimos, &posicaoVetor_usuarios, &posicaoVetor_livros);
          break;
        case 3:
          relatorioEmprestimosAtraso(&emprestimos, &tamanhoEmprestimos);
          break;
        case 4:
          system("cls");
          relatorioEmprestimos(&emprestimos, tamanhoEmprestimos);
          break;
        case 0:
          menu_principal = 0;
          system("cls");
          break;
        default:
          printf("\nOpcao invalida. Tente novamente...");
        }

      } while (menu_principal != 0);

    break;

    case 4:
      system("cls");
    break;
      
    case 10:
      printf("\nSaindo do programa...\n");
    break;
      
    default:
      printf("\nOpcao invalida. Tente novamente...");
    }

  } while (menu_principal != 10);

  system("cls");

  return 0;
}