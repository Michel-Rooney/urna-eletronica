#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ADMIN_SENHA "ue@2022"

typedef struct {
  char cargo[11];
  char nome[50];
  int sigla;
  char partido[12];
  int votos;
} Candidato;

int NCand = 0;
int NElei = 0;
int NPres = 0;
int NGove = 0;
int NPref = 0;

Candidato *candidatos = NULL;
Candidato *presidentes = NULL;
Candidato *governadores = NULL;
Candidato *prefeitos = NULL;

void limparTela();
void limparEleicao();
int menuAdm();
void criarEleicao();
void menuEleicao();

int main() {
  limparTela();
  int opcao = 0;

  while (true) {
    printf("\n");
    printf("=======================================\n");
    printf("           URNA ELETRONICA             \n");
    printf("=======================================\n");
    printf("\n");
    printf("[1] - Administração\n");
    printf("[2] - Começar Eleição\n");
    printf("[3] - Sair\n");
    printf("Opção: ");
    scanf("%d", &opcao);

    switch (opcao) {
    case 1: {
      char senha[16];
      bool voltar = 0;

      printf("\n");
      printf("Digite a senha do Administrador. ");
      printf("Digite (voltar) para voltar ao Menu.\n");

      while (true) {
        printf("\n");
        printf("Senha: ");
        scanf(" %[^\n]", senha);

        if (strcmp(senha, ADMIN_SENHA) != 0) {
          printf("Senha inválida!\n");
        } else {
          break;
        }

        if (strcmp(senha, "voltar") == 0) {
          voltar = 1;
          break;
        }
      }

      if (!voltar) {
        menuAdm();
      }

      break;
    }
    case 2: {
      printf("Começar Eleição\n");
      break;
    }
    case 3: {
      return 0;
    }
    default: {
      printf("Opção inválida!\n");
    }
    }

    limparTela();
  }

  limparEleicao();

  return 0;
}

void limparTela() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

void limparEleicao() {
  free(candidatos);
  free(presidentes);
  free(governadores);
  free(prefeitos);

  candidatos = NULL;
  presidentes = NULL;
  governadores = NULL;
  prefeitos = NULL;
}

int menuAdm() {
  int opcao = 0;

  while (true) {
    limparTela();
    printf("\n");
    printf("=======================================\n");
    printf("             ADMINISTRACAO             \n");
    printf("=======================================\n");
    printf("\n");
    printf("[1] - Criar Eleicao\n");
    printf("[2] - Voltar\n");
    printf("Opção: ");
    scanf("%d", &opcao);

    switch (opcao) {
    case 1: {
      criarEleicao();
    }
    case 2: {
      return 0;
    }
    default: {
      printf("Opção inválida!\n");
    }
    }
  }
}

void criarEleicao() {
  limparTela();
  limparEleicao();
  printf("\n");
  printf("=======================================\n");
  printf("            CRIAR ELEICAO              \n");
  printf("=======================================\n");
  printf("\n");
  printf("Quantidade de Candidatos: ");
  scanf("%d", &NCand);

  if (candidatos != NULL) {
    free(candidatos);
  }

  if (presidentes != NULL) {
    free(candidatos);
  }

  if (governadores != NULL) {
    free(candidatos);
  }

  if (prefeitos != NULL) {
    free(candidatos);
  }

  candidatos = (Candidato *)malloc(NCand * sizeof(Candidato));
  presidentes = (Candidato *)malloc(NCand * sizeof(Candidato));
  governadores = (Candidato *)malloc(NCand * sizeof(Candidato));
  prefeitos = (Candidato *)malloc(NCand * sizeof(Candidato));

  if (candidatos == NULL) {
    printf("Erro critico: Memoria insuficiente!\n");
    exit(1);
  }

  printf("Quantidade de Eleitores: ");
  scanf("%d", &NElei);

  limparTela();

  printf("\n");
  printf("=======================================\n");
  printf("        CADASTRO DE CANDIDATOS         \n");
  printf("=======================================\n");

  int i;
  for (i = 0; i < NCand; i++) {
    Candidato candidato;

    while (true) {
      int opcao = 0;

      printf("\n");
      printf("=======================================\n");
      printf("      Preenchendo Candidato %d de %d   \n", i + 1, NCand);
      printf("=======================================\n");
      printf("\n");

      printf("Escolha o Cargo:\n");
      printf("[1] - Presidente\n");
      printf("[2] - Governador\n");
      printf("[3] - Prefeito\n");
      printf("Opção: ");
      scanf("%d", &opcao);

      if (opcao == 1) {
        strcpy(candidato.cargo, "Presidente");
        break;
      } else if (opcao == 2) {
        strcpy(candidato.cargo, "Governador");
        break;
      } else if (opcao == 3) {
        strcpy(candidato.cargo, "Prefeito");
        break;
      } else {
        printf("Opção inválida!\n");
      }
    }

    printf("\n");

    printf("Nome do %s: ", candidato.cargo);
    scanf(" %[^\n]", candidato.nome);

    printf("Sigla do %s: ", candidato.cargo);
    scanf("%d", &candidato.sigla);

    printf("Partido do %s: ", candidato.cargo);
    scanf(" %[^\n]", candidato.partido);

    candidato.votos = 0;
    candidatos[i] = candidato;

    if (strcmp(candidato.cargo, "Presidente") == 0) {
      presidentes[i] = candidato;
      NPres += 1;
    } else if (strcmp(candidato.cargo, "Governador") == 0) {
      governadores[i] = candidato;
      NGove += 1;
    } else if (strcmp(candidato.cargo, "Prefeito") == 0) {
      prefeitos[i] = candidato;
      NPref += 1;
    }

    limparTela();
  }

  // for (i = 0; i < NCand; i++) {
  //   Candidato candidato = candidatos[i];
  //   printf("\n");
  //   printf("Cargo: %s\n", candidato.cargo);
  //   printf("Nome: %s\n", candidato.nome);
  //   printf("Sigla: %d\n", candidato.sigla);
  //   printf("Partido: %s\n", candidato.partido);
  //   printf("Votos: %d\n", candidato.votos);
  //   printf("\n");
  // }
  //
  // while (true) {
  // }
}

void menuEleicao() {}
