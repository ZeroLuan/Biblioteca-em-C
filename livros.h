typedef struct {
  char titulos[30];
  char autores[30];
  char categorias[30];
  int codLivros;
  int quantidades;
} Biblioteca;

int buscaLivro(Biblioteca *livro, int *numLivros, int *posicaoVetor_livro);

void cadastrarLivro(Biblioteca **livro, int *numLivros);

void editarLivro(Biblioteca *livro, int *numLivros, int *posicaoVetor_livro);

void excluirLivro(Biblioteca **livro, int *numLivros, int *posicaoVetor_livro);

void listarTodosLivros(Biblioteca *livro, int *numLivros);