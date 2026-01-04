#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> // Adicionado para funcionar o relatorio

#define ADMIN_SENHA "ue@2022"

typedef struct {
  char cargo[11];
  char nome[50];
  int sigla;
  char partido[12];
  int votos;
} Candidato;

int NCand = 0;
int NElei = 0; // Quantidade de eleitores prevista
int TotalBrancos = 0;
int TotalNulos = 0;

Candidato *candidatos = NULL;

// Protótipos
void limparTela();
void limparEleicao();
int menuAdm();
void criarEleicao();
void menuEleicao(); // Essa função precisa ser implementada para votar
void ordenarPorVotos(Candidato *vetor, int tamanho);
void processarCategoria(char *categoria, FILE *arq);
void gerarRelatorioFinal();

int main() {
  limparTela();
  int opcao = 0;

  while (true) {
    printf("\n");
    printf("=======================================\n");
    printf("           URNA ELETRONICA             \n");
    printf("=======================================\n");
    printf("\n");
    printf("[1] - Administracao\n");
    printf("[2] - Comecar Eleicao\n"); // Vai para a votação
    printf("[3] - Sair\n");
    printf("Opcao: ");
    scanf("%d", &opcao);

    switch (opcao) {
    case 1: {
      char senha[16];
      bool voltar = 0;
      printf("\nDigite a senha do Administrador ou (voltar).\n");

      while (true) {
        printf("Senha: ");
        scanf(" %[^\n]", senha);

        if (strcmp(senha, ADMIN_SENHA) == 0) {
          break;
        } else if (strcmp(senha, "voltar") == 0) {
          voltar = 1;
          break;
        } else {
          printf("Senha invalida!\n");
        }
      }

      if (!voltar) {
        menuAdm();
      }
      break;
    }
    case 2: {
      if (candidatos == NULL) {
          printf("\nERRO: Nenhuma eleicao foi criada ainda!\n");
          printf("Va em Administracao -> Criar Eleicao primeiro.\n");
          getchar(); getchar(); // Pausa
      } else {
          menuEleicao(); // Chama a função de votação (que está vazia no seu código original)
      }
      break;
    }
    case 3: {
      limparEleicao();
      return 0;
    }
    default: {
      printf("Opcao invalida!\n");
    }
    }
    limparTela();
  }
<<<<<<< HEAD
=======

  limparEleicao();

>>>>>>> 743dd8ae8fa7b0c74796bffadd351a1df1368508
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
<<<<<<< HEAD
  if (candidatos != NULL) {
    free(candidatos);
    candidatos = NULL;
  }
  // Removemos os arrays redundantes daqui
=======
  free(candidatos);
  free(presidentes);
  free(governadores);
  free(prefeitos);

  candidatos = NULL;
  presidentes = NULL;
  governadores = NULL;
  prefeitos = NULL;
>>>>>>> 743dd8ae8fa7b0c74796bffadd351a1df1368508
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
    printf("[1] - Criar Nova Eleicao\n");
    printf("[2] - Gerar Relatorio (Fim da Eleicao)\n");
    printf("[3] - Voltar\n");
    printf("Opcao: ");
    scanf("%d", &opcao);

    switch (opcao) {
    case 1:
      criarEleicao();
      break; // Faltava esse break
    case 2:
        if (candidatos == NULL) {
            printf("\nNao ha dados para gerar relatorio.\n");
            getchar(); getchar();
        } else {
            gerarRelatorioFinal();
        }
        break;
    case 3:
      return 0;
    default:
      printf("Opcao invalida!\n");
      break;
    }
  }
}

void criarEleicao() {
  limparTela();
<<<<<<< HEAD
  limparEleicao(); // Limpa memória anterior se houver

=======
  limparEleicao();
>>>>>>> 743dd8ae8fa7b0c74796bffadd351a1df1368508
  printf("\n");
  printf("=======================================\n");
  printf("            CRIAR ELEICAO              \n");
  printf("=======================================\n");
  
  printf("Quantidade de Candidatos: ");
  scanf("%d", &NCand);

  candidatos = (Candidato *)malloc(NCand * sizeof(Candidato));

  if (candidatos == NULL) {
    printf("Erro critico: Memoria insuficiente!\n");
    exit(1);
  }

  printf("Quantidade de Eleitores Aptos: ");
  scanf("%d", &NElei);

  limparTela();

  for (int i = 0; i < NCand; i++) {
    Candidato candidato;
    int opcao = 0;

    while (true) {
      limparTela();
      printf("\nPreenchendo Candidato %d de %d\n", i + 1, NCand);
      printf("-------------------------------\n");
      printf("[1] - Presidente\n");
      printf("[2] - Governador\n");
      printf("[3] - Prefeito\n");
      printf("Cargo: ");
      scanf("%d", &opcao);

      if (opcao == 1) { strcpy(candidato.cargo, "Presidente"); break; }
      else if (opcao == 2) { strcpy(candidato.cargo, "Governador"); break; }
      else if (opcao == 3) { strcpy(candidato.cargo, "Prefeito"); break; }
      else { printf("Opcao invalida!\n"); }
    }

    printf("Nome: ");
    scanf(" %[^\n]", candidato.nome);

    printf("Sigla/Numero: ");
    scanf("%d", &candidato.sigla);

    printf("Partido: ");
    scanf(" %[^\n]", candidato.partido);

    candidato.votos = 0;
<<<<<<< HEAD
    candidatos[i] = candidato; // Salva no vetor principal
  }
  
  printf("\nCadastro concluido! Pressione ENTER.");
  getchar(); getchar();
=======
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
>>>>>>> 743dd8ae8fa7b0c74796bffadd351a1df1368508
}

//parte do eduardo abaixo

void ordenarPorVotos(Candidato *vetor, int tamanho) {
    Candidato temp;
    for (int i = 0; i < tamanho - 1; i++) {
        for (int j = 0; j < tamanho - i - 1; j++) {
            if (vetor[j].votos < vetor[j + 1].votos) {
                temp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temp;
            }
        }
    }
}

void processarCategoria(char *categoria, FILE *arq) {
    // Cria vetor temporário
    Candidato *tempLista = (Candidato *)malloc(NCand * sizeof(Candidato));
    int cont = 0;
    int votosValidosCategoria = 0;

    // Filtra do vetor principal GLOBAL
    for (int i = 0; i < NCand; i++) {
        if (strcmp(candidatos[i].cargo, categoria) == 0) {
            tempLista[cont] = candidatos[i];
            votosValidosCategoria += candidatos[i].votos;
            cont++;
        }
    }

    ordenarPorVotos(tempLista, cont);

    printf("\n\t--- RESULTADO PARA %s ---\n", categoria);
    fprintf(arq, "\n--- RESULTADO PARA %s ---\n", categoria);
    
    printf("\t%-20s | %-10s | %s | %s\n", "CANDIDATO", "PARTIDO", "VOTOS", "% VALIDOS");
    fprintf(arq, "%-20s | %-10s | %s | %s\n", "CANDIDATO", "PARTIDO", "VOTOS", "% VALIDOS");
    
    for (int i = 0; i < cont; i++) {
        float porcentagem = 0.0;
        if (votosValidosCategoria > 0) {
            porcentagem = ((float)tempLista[i].votos / votosValidosCategoria) * 100;
        }
        printf("\t%-20s | %-10s | %05d | %05.2f%%\n", 
               tempLista[i].nome, tempLista[i].partido, tempLista[i].votos, porcentagem);
        fprintf(arq, "%-20s | %-10s | %05d | %05.2f%%\n", 
               tempLista[i].nome, tempLista[i].partido, tempLista[i].votos, porcentagem);
    }

    if (cont > 0) {
        printf("\tVENCEDOR: %s\n", tempLista[0].nome);
        fprintf(arq, "VENCEDOR: %s\n", tempLista[0].nome);
    } else {
        printf("\t(Nenhum candidato)\n");
        fprintf(arq, "(Nenhum candidato)\n");
    }

    free(tempLista);
}

void gerarRelatorioFinal() {
    limparTela();
    
    FILE *arq = fopen("boletim_urna.txt", "w");
    if (arq == NULL) {
        printf("ERRO ao criar arquivo!\n");
        getchar(); getchar();
        return;
    }

    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char dataStr[64];
    strftime(dataStr, sizeof(dataStr), "%d/%m/%Y as %H:%M:%S", tm);

    printf("\n\t=== RELATORIO ===\n\tData: %s\n", dataStr);
    fprintf(arq, "=== RELATORIO ===\nData: %s\n", dataStr);

    processarCategoria("Presidente", arq);
    processarCategoria("Governador", arq);
    processarCategoria("Prefeito", arq);

    // Totais
    int totalVotosNominais = 0;
    for(int i=0; i<NCand; i++) totalVotosNominais += candidatos[i].votos;
    int totalGeral = totalVotosNominais + TotalBrancos + TotalNulos;

    printf("\n\t--- ESTATISTICAS ---\n");
    printf("\tVotos Validos: %d\n\tBrancos: %d\n\tNulos: %d\n\tTOTAL: %d\n", 
           totalVotosNominais, TotalBrancos, TotalNulos, totalGeral);
    
    fprintf(arq, "\n--- ESTATISTICAS ---\n");
    fprintf(arq, "Votos Validos: %d\nBrancos: %d\nNulos: %d\nTOTAL: %d\n", 
            totalVotosNominais, TotalBrancos, TotalNulos, totalGeral);

    fclose(arq);
    printf("\n\tArquivo 'boletim_urna.txt' gerado com sucesso!\n");
    printf("\tPressione ENTER...");
    getchar(); getchar();
}
