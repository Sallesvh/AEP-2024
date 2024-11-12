#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <locale.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#define MAX 100

void cor(int color);
void criptografarSenha(char senha[15]);
bool validarSenha(char senha[15]);
void menuPrincipal();
void adicionarUsuario();
void removerUsuario();
void modificarUsuario();
void listarUsuarios();


int main() {
  setlocale(LC_ALL, "Portuguese");
  menuPrincipal();
  return 0;
}

void cor(int color) {
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void criptografarSenha(char senha[15]) {
  for (int i = 0; senha[i]; i++) {
    if (senha[i] >= 'a' && senha[i] <= 'z') {
      senha[i] = 'a' + ('z' - senha[i]); 
    } else if (senha[i] >= 'A' && senha[i] <= 'Z') {
      senha[i] = 'A' + ('Z' - senha[i]);  
    }
  }
}

bool validarSenha(char senha[15]) {
  bool v1 = false, v2 = false, v3 = false, v4 = false, v5 = false;
  int comprimento = strlen(senha);

  if (comprimento >= 8 && comprimento <= 12) v1 = true;

  for (int i = 0; i < comprimento; i++) {
    if (senha[i] >= 'a' && senha[i] <= 'z') v2 = true;
    if (senha[i] >= 'A' && senha[i] <= 'Z') v3 = true;
    if (senha[i] >= '0' && senha[i] <= '9') v5 = true;
    if ((senha[i] >= 32 && senha[i] <= 47) || 
        (senha[i] >= 58 && senha[i] <= 64) ||
        (senha[i] >= 91 && senha[i] <= 96) || 
        (senha[i] >= 123 && senha[i] <= 126)) {
      v4 = true;
    }
  }
  return v1 && v2 && v3 && v4 && v5;
}

void adicionarUsuario() {
  char usuario[15], senha[15];
  FILE *arquivo;

  system("cls");
  cor(13); 
  printf("Adicionar usuário\n");
  printf("-------------\n");
  cor(6); 
  printf("Usuário: ");
  cor(15); 
  scanf("%s", usuario);

  while (true) {
    cor(6);
    printf("\nSenha: ");
    cor(15);
    scanf("%s", senha);
    if (validarSenha(senha)) {
      break;
    } else {
      cor(4); 
      printf("\n- SENHA INCORRETA -");
      printf("\n- 8 a 12 caracteres");
      printf("\n- Deve ter maiúscula");
      printf("\b - Deve ter minúscula");
      printf("\n- Deve ter número");
      printf("\n- Deve ter caractere especial\n");
    }
  }

  criptografarSenha(usuario);
  criptografarSenha(senha);

  arquivo = fopen("usuariosNovo.txt", "a");
  if (arquivo == NULL) {
    cor(4);
    printf("Erro ao abrir o arquivo!\n");
    return;
  }
  
  fprintf(arquivo, "Usuário: %s\nSenha: %s\n\n", usuario, senha);
  fclose(arquivo);
  cor(2); 
  printf("\nUsuário adicionado com sucesso!\n");

  printf("\nPara voltar ao menu, pressione qualquer tecla...");
  getch();
}

void listarUsuarios() {
  char linha[100];
  FILE *arquivo;

  system("cls");
  cor(13);
  printf("Lista de usuários\n");

  arquivo = fopen("usuariosNovo.txt", "r");
  if (arquivo == NULL) {
    cor(4);
    printf("Nenhum usuário encontrado!\n");
    printf("\nPara voltar ao menu, pressione qualquer tecla...");
    getch();
    return;
  }

  cor(6);
  printf("Usuários criptografados:\n");
  printf("------------------------------\n");

  while (fgets(linha, 100, arquivo) != NULL) {
    printf("%s", linha);
  }

  fclose(arquivo);
  printf("\n\nPara voltar ao menu, pressione qualquer tecla...");
  getch();
}

void removerUsuario() {
  char usuario[15], usuarioArquivo[15], senhaArquivo[15];
  bool usuarioEncontrado = false;

  FILE *arquivo = fopen("usuariosNovo.txt", "r");
  FILE *temp = fopen("tempNovo.txt", "w");

  if (arquivo == NULL || temp == NULL) {
    cor(4);
    printf("Erro ao abrir o arquivo!\n");
    return;
  }

  system("cls");
  cor(13);
  printf("Remover usuário\n");
  printf("-------------\n");
  cor(6);
  printf("Digite o usuário que deseja remover: ");
  cor(15);
  scanf("%s", usuario);

  criptografarSenha(usuario);

  while (fscanf(arquivo, "Usuário: %s\nSenha: %s\n\n", usuarioArquivo, senhaArquivo) != EOF) {
    if (strcmp(usuarioArquivo, usuario) == 0) {
      usuarioEncontrado = true;
      cor(2);
      printf("\nUsuário removido com sucesso!\n");
    } else {
      fprintf(temp, "Usuário: %s\nSenha: %s\n\n", usuarioArquivo, senhaArquivo);
    }
  }

  fclose(arquivo);
  fclose(temp);

  remove("usuariosNovo.txt");
  rename("tempNovo.txt", "usuariosNovo.txt");

  if (!usuarioEncontrado) {
    cor(4);
    printf("\nUsuário não encontrado.\n");
  }

  printf("\nPara voltar ao menu, pressione qualquer tecla...");
  getch();
}

void modificarUsuario() {
  char usuario[15], novoUsuario[15], novaSenha[15];
  char usuarioArquivo[15], senhaArquivo[15];
  bool usuarioEncontrado = false;

  FILE *arquivo = fopen("usuariosNovo.txt", "r");
  FILE *temp = fopen("tempNovo.txt", "w");

  if (arquivo == NULL || temp == NULL) {
    cor(4);
    printf("Erro ao abrir o arquivo!\n");
    return;
  }

  system("cls");
  cor(13);
  printf("Alterar usuário\n");
  printf("-------------\n");
  cor(6);
  printf("Digite o usuário que deseja alterar: ");
  cor(15);
  scanf("%s", usuario);

  criptografarSenha(usuario);

  while (fscanf(arquivo, "Usuário: %s\nSenha: %s\n\n", usuarioArquivo, senhaArquivo) != EOF) {
    if (strcmp(usuarioArquivo, usuario) == 0) {
      usuarioEncontrado = true;

      cor(6);
      printf("\nUsuário encontrado!\n");
      printf("Insira o novo usuário: ");
      cor(15);
      scanf("%s", novoUsuario);

      while (true) {
        cor(6);
        printf("\nInsira a nova senha: ");
        cor(15);
        scanf("%s", novaSenha);
        if (validarSenha(novaSenha)) {
          break;
        } else {
          cor(4);
          printf("\n- Senha Inválida -");
          printf("\n- 8 a 12 caracteres");
          printf("\n- Deve ter maiúscula e minúscula");
          printf("\n- Deve ter número");
          printf("\n- Deve ter caractere especial\n");
        }
      }

      criptografarSenha(novoUsuario);
      criptografarSenha(novaSenha);

      fprintf(temp, "Usuário: %s\nSenha: %s\n\n", novoUsuario, novaSenha);
      cor(2);
      printf("\nUsuário e senha atualizados com sucesso!\n");
    } else {
      fprintf(temp, "Usuário: %s\nSenha: %s\n\n", usuarioArquivo, senhaArquivo);
    }
  }

  fclose(arquivo);
  fclose(temp);

  remove("usuariosNovo.txt");
  rename("tempNovo.txt", "usuariosNovo.txt");

  if (!usuarioEncontrado) {
    cor(4);
    printf("\nUsuário não encontrado.\n");
  }

  printf("\nPara voltar ao menu, pressione qualquer tecla...");
  getch();
}

void menuPrincipal() {
  int opcao;

  do {
    system("cls");
    cor(13);
    printf("-=-=-=-MENU-=-=-=- \n");
    cor(6);
    printf("1 - Adicionar usuário\n");
    printf("2 - Remover usuário\n");
    printf("3 - Alterar usuário\n");
    printf("4 - Lista de usuários\n");
    printf("5 - Sair\n");
    cor(13);
    printf("-------------------------------\n");
    cor(15);
    printf("Opção: ");
    scanf("%d", &opcao);

    switch(opcao) {
      case 1: 
        adicionarUsuario();
        break;
      case 2: 
        removerUsuario();
        break;
      case 3: 
        modificarUsuario();
        break;
      case 4: 
        listarUsuarios();
        break;
      case 5: 
        printf("\nSaindo...");
        break;
    }
  } while (opcao != 5);
}
