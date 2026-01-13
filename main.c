#include <ctype.h>
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

typedef struct {
  char nomeeleitor[50];
} Eleitor;

int NCand = 0;
int NElei = 0;
int TotalBrancos = 0;
int TotalNulos = 0;

Candidato *candidatos = NULL;

void limparTela();
void limparEleicao();
void limparVotos();
void sleep();
void limparBuffer();
void menuAdm();
void listarCandidatosInterno();
void listarCandidatos();
void adicionarCandidato();
void removerCandidato();
void definirEleitores();
void criarEleicao();
void menuEleicao();
void ordenarPorVotos(Candidato *vetor, int tamanho);
void processarCategoria(char *categoria, FILE *arq);
void gerarRelatorioFinal();

int main() {
  int opcao = 0;
  int status = 0;

  while (true) {
    limparTela();
    printf("\n");
    printf("=======================================\n");
    printf("           URNA ELETRONICA             \n");
    printf("=======================================\n");
    printf("\n");
    printf("[1] - Administracao\n");
    printf("[2] - Comecar Eleicao\n");
    printf("[3] - Gerar Relatorio\n");
    printf("[4] - Sair\n");
    printf("Opcao: ");
    status = scanf("%d", &opcao);

    if (status != 1) {
      printf("Digite um numero!\n");
      limparBuffer();
      sleep();
      continue;
    }

    limparBuffer();

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
          printf("Senha invalida!\n");
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
      if (NCand <= 0) {
        printf("Candidados nao foram cadastrados!\n");
        sleep();
        break;
      }

      if (NElei <= 0) {
        printf("A quantidade de eleitores nao foi definida!\n");
        sleep();
        break;
      }

      menuEleicao();
      break;
    }
    case 3: {
      gerarRelatorioFinal();
      break;
    }
    case 4: {
      limparEleicao();
      return 0;
    }
    default: {
      printf("Opcao invalida!\n");
      sleep();
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

  candidatos = NULL;
}

void limparVotos() {
  int i;

  TotalBrancos = 0;
  TotalNulos = 0;

  for (i = 0; i < NCand; i++) {
    candidatos[i].votos = 0;
  }
}

void limparBuffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

void sleep() {
  printf("\n[Pressione qualquer tecla para voltar]\n");
  getchar();
}

bool is_string_numeric(const char *str) {
  int i;

  if (str == NULL || *str == '\0') {
    return false;
  }

  for (i = 0; str[i] != '\0'; i++) {

    if (!isdigit((unsigned char)str[i])) {
      return false;
    }
  }

  return true;
}

void menuAdm() {
  int opcao = 0;
  while (true) {
    limparTela();
    printf("\n");
    printf("=======================================\n");
    printf("        GERENCIAR CANDIDATOS           \n");
    printf("=======================================\n");
    printf("\n");
    printf("[1] - Listar Candidatos\n");
    printf("[2] - Adicionar Candidato\n");
    printf("[3] - Remover Candidato\n");
    printf("[4] - Definir a quantidade de Eleitores\n");
    printf("[5] - Voltar\n");
    printf("Opcao: ");
    scanf("%d", &opcao);

    limparBuffer();

    switch (opcao) {
    case 1:
      listarCandidatos();
      break;
    case 2:
      adicionarCandidato();
      break;
    case 3:
      removerCandidato();
      break;
    case 4:
      definirEleitores();
      break;
    case 5:
      return;
    default:
      printf("Opcao invalida!\n");
      sleep();
    }
  }
}

void listarCandidatosInterno() {
  int i;
  printf("ID | %-10s | %-30s | %-12s | SIGLA\n", "CARGO", "NOME", "PARTIDO");
  printf("---|------------+--------------------------------+--------------+----"
         "---\n");
  for (i = 0; i < NCand; i++) {
    printf("%2d | %-10s | %-30s | %-12s | %d\n", i + 1, candidatos[i].cargo,
           candidatos[i].nome, candidatos[i].partido, candidatos[i].sigla);
  }
}

void listarCandidatosPorCargo(char cargo[11]) {
  int i;
  printf("ID | %-10s | %-30s | %-12s | SIGLA\n", "CARGO", "NOME", "PARTIDO");
  printf("---|------------+--------------------------------+--------------+----"
         "---\n");
  for (i = 0; i < NCand; i++) {
    if (strcmp(candidatos[i].cargo, cargo) == 0) {
      printf("%2d | %-10s | %-30s | %-12s | %d\n", i + 1, candidatos[i].cargo,
             candidatos[i].nome, candidatos[i].partido, candidatos[i].sigla);
    }
  }
}

void listarCandidatos() {
  limparTela();
  printf("\n");
  printf("=======================================\n");
  printf("          LISTA DE CANDIDATOS          \n");
  printf("=======================================\n");

  if (NCand == 0) {
    printf("\nNao ha candidatos cadastrados.\n");
  } else {
    listarCandidatosInterno();
  }

  sleep();
}

void adicionarCandidato() {
  int opcao = 0;
  Candidato *novoCandidatos =
      (Candidato *)realloc(candidatos, (NCand + 1) * sizeof(Candidato));

  Candidato novo;

  limparTela();

  printf("\n");
  printf("=======================================\n");
  printf("          ADICIONAR CANDIDATO          \n");
  printf("=======================================\n");
  if (novoCandidatos == NULL) {
    printf("Erro critico: Memoria insuficiente para adicionar candidato!\n");
    return;
  }
  candidatos = novoCandidatos;

  while (true) {
    opcao = 0;
    printf("\nEscolha o Cargo:\n");
    printf("[1] - Presidente\n");
    printf("[2] - Governador\n");
    printf("[3] - Prefeito\n");
    printf("Opcao: ");
    scanf("%d", &opcao);

    limparBuffer();

    if (opcao == 1) {
      strcpy(novo.cargo, "Presidente");
      break;
    } else if (opcao == 2) {
      strcpy(novo.cargo, "Governador");
      break;
    } else if (opcao == 3) {
      strcpy(novo.cargo, "Prefeito");
      break;
    } else {
      printf("Opcao invalida!\n");
      sleep();
      limparTela();
    }
  }

  printf("\nNome do %s: ", novo.cargo);
  scanf(" %50[^\n]", novo.nome);

  while (true) {
    int i;
    int temp = 0;
    int status = 0;
    int is_valid = 1;

    printf("Sigla do %s: ", novo.cargo);
    status = scanf("%d", &temp);

    if (status != 1) {
      printf("Digite um numero!\n");
      limparBuffer();
      continue;
    }

    if (temp < 0) {
      printf("A sigla precisa ser um valor positivo!");
      continue;
    }

    is_valid = 1;
    for (i = 0; i < NCand; i++) {
      if (candidatos[i].sigla == temp) {
        printf("Essa sigla ja foi cadastrada!\n");
        is_valid = 0;
      }
    }

    if (!is_valid) {
      continue;
    }

    novo.sigla = temp;
    break;
  }

  limparBuffer();

  printf("Partido do %s: ", novo.cargo);
  scanf(" %11[^\n]", novo.partido);

  novo.votos = 0;

  candidatos[NCand] = novo;
  NCand += 1;

  printf("\n[SUCESSO] Candidato adicionado com ID: %d\n", NCand);
  limparBuffer();
  sleep();
}

void removerCandidato() {
  int i;
  int c;
  int idRemover;
  int confirmarDelecao = 0;
  int indice;

  limparTela();
  printf("\n");
  printf("=======================================\n");
  printf("           REMOVER CANDIDATO           \n");
  printf("=======================================\n");

  if (NCand == 0) {
    printf("\nNao ha candidatos cadastrados para remover.\n");
    getchar();
    return;
  }

  listarCandidatosInterno();

  printf("\nDigite o ID (1 a %d) do candidato a remover: ", NCand);
  if (scanf("%d", &idRemover) != 1 || idRemover < 1 || idRemover > NCand) {
    printf("\nID invalido!\n");
    while ((c = getchar()) != '\n' && c != EOF)
      ;
    getchar();
    return;
  }

  printf("Deseja realmente fazer a delecao?\n");
  printf("[1] - Sim\n");
  printf("[2] - Nao\n");
  printf("Opcao: ");
  scanf("%d", &confirmarDelecao);
  limparBuffer();

  if (confirmarDelecao != 1) {
    printf("Delecao cancelada!");
    sleep();
    return;
  }

  indice = idRemover - 1;
  for (i = indice; i < NCand - 1; i++) {
    candidatos[i] = candidatos[i + 1];
  }

  NCand -= 1;

  if (NCand > 0) {
    Candidato *novoCandidatos =
        (Candidato *)realloc(candidatos, NCand * sizeof(Candidato));

    if (novoCandidatos == NULL) {
      printf(
          "\nAVISO: Falha ao otimizar memoria, mas candidato foi removido.\n");
    } else {
      candidatos = novoCandidatos;
    }
  } else {
    free(candidatos);
    candidatos = NULL;
  }

  printf("\n[SUCESSO] Candidato ID %d removido.\n", idRemover);
  sleep();
}

void definirEleitores() {
  limparTela();
  printf("\n");
  printf("=======================================\n");
  printf("                ELEITORES              \n");
  printf("=======================================\n");
  printf("\n");

  while (true) {
    int temp = 0;
    int status = 0;

    printf("Quantidade de Eleitores: ");
    status = scanf("%d", &temp);

    if (status != 1) {
      printf("Digite um numero!\n");
      limparBuffer();
      continue;
    }

    NElei = temp;
    break;
  }

  printf("\n");
  printf("Quantidade de eleitores adicionada com sucesso!");
  limparBuffer();
  sleep();
  return;
}

void ordenarPorVotos(Candidato *vetor, int tamanho) {
  Candidato temp;
  int i, j;
  for (i = 0; i < tamanho - 1; i++) {
    for (j = 0; j < tamanho - i - 1; j++) {
      if (vetor[j].votos < vetor[j + 1].votos) {
        temp = vetor[j];
        vetor[j] = vetor[j + 1];
        vetor[j + 1] = temp;
      }
    }
  }
}

void processarCategoria(char *categoria, FILE *arq) {
  Candidato *tempLista = (Candidato *)malloc(NCand * sizeof(Candidato));
  int cont = 0;
  int votosValidos = 0;

  int i;
  for (i = 0; i < NCand; i++) {
    if (strcmp(candidatos[i].cargo, categoria) == 0) {
      tempLista[cont] = candidatos[i];
      votosValidos += candidatos[i].votos;
      cont++;
    }
  }

  ordenarPorVotos(tempLista, cont);

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

  for (i = 0; i < cont; i++) {
    float porcentagem = 0.0;
    if (votosValidos > 0) {
      porcentagem = ((float)tempLista[i].votos / votosValidos) * 100;
    }

    printf("\t%-30s | %-10s | %05d    | %05.2f%%\n", tempLista[i].nome,
           tempLista[i].partido, tempLista[i].votos, porcentagem);

    fprintf(arq, "%-30s | %-10s | %05d    | %05.2f%%\n", tempLista[i].nome,
            tempLista[i].partido, tempLista[i].votos, porcentagem);
  }

  if (cont > 0) {
    printf("\tVENCEDOR ELEITO: %s\n", tempLista[0].nome);
    fprintf(arq, "VENCEDOR ELEITO: %s\n", tempLista[0].nome);
  } else {
    printf("\t(Nenhum candidato concorreu a este cargo)\n");
    fprintf(arq, "(Nenhum candidato concorreu a este cargo)\n");
  }

  free(tempLista);
}

void gerarRelatorioFinal() {
  int i;
  int totalVotosNominais = 0;
  int totalGeral = totalVotosNominais + TotalBrancos + TotalNulos;
  time_t t = time(NULL);
  struct tm *tm = localtime(&t);
  char dataStr[64];
  FILE *arq = fopen("boletim_urna.txt", "w");

  limparTela();

  if (arq == NULL) {
    printf("ERRO: Nao foi possivel criar o arquivo de relatorio!\n");
    return;
  }

  strftime(dataStr, sizeof(dataStr), "%d/%m/%Y as %H:%M:%S", tm);

  printf("\n");
  printf("\t=========================================\n");
  printf("\t      RELATORIO OFICIAL DA ELEICAO       \n");
  printf("\t      Gerado em: %s              \n", dataStr);
  printf("\t=========================================\n");

  fprintf(arq, "=========================================\n");
  fprintf(arq, "      RELATORIO OFICIAL DA ELEICAO       \n");
  fprintf(arq, "      Gerado em: %s              \n", dataStr);
  fprintf(arq, "=========================================\n");

  processarCategoria("Presidente", arq);
  processarCategoria("Governador", arq);
  processarCategoria("Prefeito", arq);

  for (i = 0; i < NCand; i++)
    totalVotosNominais += candidatos[i].votos;

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

  printf("\n\t[SUCESSO] O arquivo 'boletim_urna.txt' foi gerado.\n");
  sleep();
  return;
}

void menuEleicao() {
  int encontrou = 0;
  int indiceCandidato = -1;
  int siglaDigitada;
  int i, j, c, opcaoVoto, confirmacaoVoto;
  char *cargos[] = {"Presidente", "Governador", "Prefeito"};
  Eleitor *eleitoresLog = (Eleitor *)malloc(NElei * sizeof(Eleitor));

  limparTela();
  limparVotos();

  if (eleitoresLog == NULL)
    return;

  for (i = 0; i < NElei; i++) {
    limparTela();
    printf("=======================================\n");
    printf("               ELEICAO                 \n");
    printf("       IDENTIFICAcaO DO ELEITOR        \n");
    printf("            Eleitor %d de %d           \n", i + 1, NElei);
    printf("=======================================\n");
    printf("Nome do eleitor: ");
    scanf(" %50[^\n]", eleitoresLog[i].nomeeleitor);
    limparBuffer();

    for (c = 0; c < 3; c++) {
      int votoConfirmadoCargo = 0;
      while (!votoConfirmadoCargo) {
        limparTela();
        printf("ELEITOR: %s\n", eleitoresLog[i].nomeeleitor);
        printf("VOTACAO PARA: %s\n", cargos[c]);
        printf("---------------------------------------\n");
        printf("[1] - Escolher Candidato\n");
        printf("[2] - Voto em BRANCO\n");
        printf("[3] - Voto NULO\n");
        printf("Escolha: ");

        if (scanf("%d", &opcaoVoto) != 1) {
          printf("Entrada invalida! Digite um numero.\n");
          limparBuffer();
          sleep();
          continue;
        }
        limparBuffer();

        if (opcaoVoto == 1) {
          encontrou = 0;
          limparTela();
          printf("--- LISTA DE CANDIDATOS (%s) ---\n", cargos[c]);
          listarCandidatosPorCargo(cargos[c]);
          printf("\nDigite a Sigla (ou 0 para voltar): ");

          if (scanf("%d", &siglaDigitada) != 1) {
            printf("Sigla invalida!\n");
            limparBuffer();
            sleep();
            continue;
          }
          limparBuffer();

          if (siglaDigitada == 0)
            continue;

          indiceCandidato = -1;
          for (j = 0; j < NCand; j++) {
            if (strcmp(candidatos[j].cargo, cargos[c]) == 0 &&
                candidatos[j].sigla == siglaDigitada) {
              indiceCandidato = j;
              encontrou = 1;
              break;
            }
          }

          if (encontrou) {
            printf("\nCANDIDATO: %s\nPARTIDO: %s\n",
                   candidatos[indiceCandidato].nome,
                   candidatos[indiceCandidato].partido);
            printf("\n[1] Confirmar | [2] Corrigir: ");
            scanf("%d", &confirmacaoVoto);
            limparBuffer();
            if (confirmacaoVoto == 1) {
              candidatos[indiceCandidato].votos++;
              votoConfirmadoCargo = 1;
            }
          } else {
            printf("\nCandidato nao encontrado para este cargo!\n");
            sleep();
          }

        } else if (opcaoVoto == 2) {
          printf("\nConfirmar voto em BRANCO para %s?\n[1] Sim | [2] Nao: ",
                 cargos[c]);
          scanf("%d", &confirmacaoVoto);
          limparBuffer();
          if (confirmacaoVoto == 1) {
            TotalBrancos++;
            votoConfirmadoCargo = 1;
          }
        } else if (opcaoVoto == 3) {
          printf("\nConfirmar voto NULO para %s?\n[1] Sim | [2] Nao: ",
                 cargos[c]);
          scanf("%d", &confirmacaoVoto);
          limparBuffer();
          if (confirmacaoVoto == 1) {
            TotalNulos++;
            votoConfirmadoCargo = 1;
          }
        } else {
          printf("Opcao invalida!\n");
          sleep();
        }
      }
    }
    printf("\n>>> Voto finalizado com sucesso para todos os cargos! <<<\n");
    sleep();
  }
  free(eleitoresLog);
  printf("\nVOTACAO ENCERRADA!\n");
  sleep();
}
