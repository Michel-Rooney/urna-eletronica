#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
int TotalBrancos = 0;
int TotalNulos = 0;

Candidato *candidatos = NULL;
Candidato *presidentes = NULL;
Candidato *governadores = NULL;
Candidato *prefeitos = NULL;

void limparTela();
void limparEleicao();
int menuAdm();
void criarEleicao();
void menuEleicao();
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
      menuEleicao();

      if (NCand > 0) {
        gerarRelatorioFinal();
      }
      break;
    }
    case 3: {
      limparEleicao();
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
  if (candidatos)
    free(candidatos);
  if (presidentes)
    free(presidentes);
  if (governadores)
    free(governadores);
  if (prefeitos)
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
      break;
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

  candidatos = (Candidato *)malloc(NCand * sizeof(Candidato));
  presidentes = (Candidato *)malloc(NCand * sizeof(Candidato));
  governadores = (Candidato *)malloc(NCand * sizeof(Candidato));
  prefeitos = (Candidato *)malloc(NCand * sizeof(Candidato));

  if (candidatos == NULL || presidentes == NULL || governadores == NULL ||
      prefeitos == NULL) {
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

  limparTela();
}

void ordenarPorVotos(Candidato *vetor, int tamanho) {
  Candidato temp;
  for (int i = 0; i < tamanho - 1; i++) {
    for (int j = 0; j < tamanho - i - 1; j++) {
      // Sinal '<' ordena do Maior para o Menor
      if (vetor[j].votos < vetor[j + 1].votos) {
        temp = vetor[j];
        vetor[j] = vetor[j + 1];
        vetor[j + 1] = temp;
      }
    }
  }
}

// Função inteligente que filtra, ordena, mostra na tela e salva no arquivo
void processarCategoria(char *categoria, FILE *arq) {
  // 1. Cria um vetor temporário apenas para essa categoria
  Candidato *tempLista = (Candidato *)malloc(NCand * sizeof(Candidato));
  int cont = 0;
  int votosValidos = 0;

  // 2. Filtra do vetor principal (Global)
  for (int i = 0; i < NCand; i++) {
    if (strcmp(candidatos[i].cargo, categoria) == 0) {
      tempLista[cont] = candidatos[i];
      votosValidos += candidatos[i].votos;
      cont++;
    }
  }

  // 3. Ordena esse grupo específico
  ordenarPorVotos(tempLista, cont);

  // 4. Exibe Cabeçalhos (Tela + Arquivo)
  printf("\n\t--- RESULTADO PARA %s ---\n", categoria);
  fprintf(arq, "\n--- RESULTADO PARA %s ---\n", categoria);

  printf("\t%-30s | %-10s | %-8s | %s\n", "CANDIDATO", "PARTIDO", "VOTOS",
         "% VALIDOS");
  fprintf(arq, "%-30s | %-10s | %-8s | %s\n", "CANDIDATO", "PARTIDO", "VOTOS",
          "% VALIDOS");

  printf(
      "\t-------------------------------+------------+----------+----------\n");
  fprintf(
      arq,
      "-------------------------------+------------+----------+----------\n");

  // 5. Loop de Impressão
  for (int i = 0; i < cont; i++) {
    float porcentagem = 0.0;
    if (votosValidos > 0) {
      porcentagem = ((float)tempLista[i].votos / votosValidos) * 100;
    }

    // Tela
    printf("\t%-30s | %-10s | %05d    | %05.2f%%\n", tempLista[i].nome,
           tempLista[i].partido, tempLista[i].votos, porcentagem);

    // Arquivo
    fprintf(arq, "%-30s | %-10s | %05d    | %05.2f%%\n", tempLista[i].nome,
            tempLista[i].partido, tempLista[i].votos, porcentagem);
  }

  // Declara o Vencedor da categoria
  if (cont > 0) {
    printf("\tVENCEDOR ELEITO: %s\n", tempLista[0].nome);
    fprintf(arq, "VENCEDOR ELEITO: %s\n", tempLista[0].nome);
  } else {
    printf("\t(Nenhum candidato concorreu a este cargo)\n");
    fprintf(arq, "(Nenhum candidato concorreu a este cargo)\n");
  }

  free(tempLista); // Libera a memória temporária
}

void gerarRelatorioFinal() {
  limparTela();

  // Abre arquivo para escrita ("w" = write/sobrescrever)
  FILE *arq = fopen("boletim_urna.txt", "w");
  if (arq == NULL) {
    printf("ERRO: Nao foi possivel criar o arquivo de relatorio!\n");
    return;
  }

  // Pega hora atual
  time_t t = time(NULL);
  struct tm *tm = localtime(&t);
  char dataStr[64];
  strftime(dataStr, sizeof(dataStr), "%d/%m/%Y as %H:%M:%S", tm);

  // Cabeçalho Principal
  printf("\n");
  printf("\t=========================================\n");
  printf("\t      RELATORIO OFICIAL DA ELEICAO       \n");
  printf("\t      Gerado em: %s              \n", dataStr);
  printf("\t=========================================\n");

  fprintf(arq, "=========================================\n");
  fprintf(arq, "      RELATORIO OFICIAL DA ELEICAO       \n");
  fprintf(arq, "      Gerado em: %s              \n", dataStr);
  fprintf(arq, "=========================================\n");

  // Chama o processamento para cada cargo
  processarCategoria("Presidente", arq);
  processarCategoria("Governador", arq);
  processarCategoria("Prefeito", arq);

  // Cálculos Gerais
  int totalVotosNominais = 0;
  for (int i = 0; i < NCand; i++)
    totalVotosNominais += candidatos[i].votos;

  int totalGeral = totalVotosNominais + TotalBrancos + TotalNulos;

  // Rodapé Estatístico
  printf("\n\t=========================================\n");
  printf("\tESTATISTICAS GERAIS\n");
  printf("\tTotal de Eleitores Aptos:  %d\n", NElei);
  printf("\tComparecimento Total:      %d\n", totalGeral);
  printf("\tVotos Validos (Nominais):  %d\n", totalVotosNominais);
  printf("\tVotos Brancos:             %d\n", TotalBrancos);
  printf("\tVotos Nulos:               %d\n", TotalNulos);
  printf("\t=========================================\n");

  fprintf(arq, "\n=========================================\n");
  fprintf(arq, "ESTATISTICAS GERAIS\n");
  fprintf(arq, "Total de Eleitores Aptos:  %d\n", NElei);
  fprintf(arq, "Comparecimento Total:      %d\n", totalGeral);
  fprintf(arq, "Votos Validos (Nominais):  %d\n", totalVotosNominais);
  fprintf(arq, "Votos Brancos:             %d\n", TotalBrancos);
  fprintf(arq, "Votos Nulos:               %d\n", TotalNulos);
  fprintf(arq, "=========================================\n");

  fclose(arq); // Fecha e salva o arquivo

  printf("\n\t[SUCESSO] O arquivo 'boletim_urna.txt' foi gerado.\n");
  getchar(); // Pausa

  int opcao = 0;

  while (true) {
    printf("[1] - Voltar\n");
    printf("Opção: ");
    scanf("%d", &opcao);

    switch (opcao) {
    case 1: {
      return;
    }
    default: {
      printf("Opção inválida!\n");
    }
    }
  }
}

void menuEleicao() {
  // Implementação futura da votação
}
