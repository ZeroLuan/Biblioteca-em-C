#include "livros.h"
#include "usuarios.h"

typedef struct {
  int id_usuario;
  int codigo_livro;
  char data_emprestimo[11];
  char data_devolucao[11];
  int quantidade_emprestada;
  int multas;
} Emprestimo;

void emprestarLivro(Biblioteca *livro, int numLivros, Usuarios *usuario, int numUsuarios, Emprestimo **emprestimo, int *tamanhoEmprestimos, int *posicaoVetor_usuario, int *posicaoVetor_livro);

void devolverLivro(Biblioteca *livro, int numLivros, Usuarios *usuario, int numUsuarios, Emprestimo **emprestimo, int *tamanhoEmprestimos, int *posicaoVetor_usuario, int *posicaoVetor_livro);

void relatorioEmprestimosAtraso(Emprestimo **emprestimos, int *tamanhoEmprestimos);

void relatorioEmprestimos(Emprestimo **emprestimo, int tamanhoEmprestimos);
