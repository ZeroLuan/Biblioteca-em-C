typedef struct {
  char nomes[30];
  int ids;
  char telefones[30];
} Usuarios;

int buscaUsuario (Usuarios *usuario, int *numUsuarios, int *posicaoVetor_usuario);

void cadastrarUsuario(Usuarios **usuario, int *numUsuarios);

void editarUsuario(Usuarios *usuario, int *numUsuarios, int *posicaoVetor_usuario);

void excluirUsuario(Usuarios **usuario, int *numUsuarios, int *posicaoVetor_usuario);

void listarTodosUsuarios(Usuarios *usuario, int *numUsuarios);
