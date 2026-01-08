#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>

#define ADMIN_SENHA "ue@2022"

// # TODO: Iniciar a eleição e validar se NCand e NElei > 0

typedef struct {
  char cargo[11];
  char nome[50];
  int sigla;
  char partido[12];
  int votos;
} Candidato;

// estrutura para o voto:
typedef struct {
  char cargoescolha[11];
  int siglaescolha;
  char nomeeleitor[51];
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
  setlocale(LC_ALL,"portuguese");
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
    printf("[3] - Gerar Relatório\n");
    printf("[4] - Sair\n");
    printf("Opção: ");
    scanf("%d", &opcao);

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
      if (NCand <= 0) {
        printf("Candidados não foram cadastrados!\n");
        sleep();
        break;
      }

      if (NElei <= 0) {
        printf("A quantidade de eleitores não foi definida!\n");
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
      printf("Opção inválida!\n");
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
  for (i = 0; i < NCand; i++) {
    Candidato candidato = candidatos[i];
    candidato.votos = 0;
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
  if (str == NULL || *str == '\0') {
    return false;
  }
	int i;
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
    printf("Opção: ");
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
      printf("Opção inválida!\n");
      sleep();
    }
  }
}

void listarCandidatosInterno() {
  printf("ID | %-10s | %-30s | %-12s | SIGLA\n", "CARGO", "NOME", "PARTIDO");
  printf("---|------------+--------------------------------+--------------+----"
         "---\n");
	int i;
  for (i = 0; i < NCand; i++) {
    printf("%2d | %-10s | %-30s | %-12s | %d\n", i + 1, candidatos[i].cargo,
           candidatos[i].nome, candidatos[i].partido, candidatos[i].sigla);
  }
}

void listarCandidatosPorCargo(char cargo[11]) {
  printf("ID | %-10s | %-30s | %-12s | SIGLA\n", "CARGO", "NOME", "PARTIDO");
  printf("---|------------+--------------------------------+--------------+----"
         "---\n");
    int i;
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
  limparTela();
  printf("\n");
  printf("=======================================\n");
  printf("          ADICIONAR CANDIDATO          \n");
  printf("=======================================\n");

  Candidato *novoCandidatos =
      (Candidato *)realloc(candidatos, (NCand + 1) * sizeof(Candidato));

  if (novoCandidatos == NULL) {
    printf("Erro critico: Memoria insuficiente para adicionar candidato!\n");
    return;
  }

  candidatos = novoCandidatos;

  Candidato novo;

  while (true) {
    int opcao = 0;
    printf("\nEscolha o Cargo:\n");
    printf("[1] - Presidente\n");
    printf("[2] - Governador\n");
    printf("[3] - Prefeito\n");
    printf("Opção: ");
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
      printf("Opção inválida!\n");
      sleep();
      limparTela();
    }
  }

  printf("\nNome do %s: ", novo.cargo);
  scanf(" %[^\n]", novo.nome);

  while (true) {
    int temp = 0;
    int status = 0;

    printf("Sigla do %s: ", novo.cargo);
    status = scanf("%d", &temp);

    if (status != 1) {
      printf("Digite um número!\n");
      limparBuffer();
      continue;
    }

    int i;
    int is_valid = 1;
    for (i = 0; i < NCand; i++) {
      if (candidatos[i].sigla == temp) {
        printf("Essa sigla já foi cadastrada!\n");
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
  scanf(" %[^\n]", novo.partido);

  novo.votos = 0;

  candidatos[NCand] = novo;
  NCand += 1;

  printf("\n[SUCESSO] Candidato adicionado com ID: %d\n", NCand);
  limparBuffer();
  sleep();
}

void removerCandidato() {
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

  int idRemover;
  printf("\nDigite o ID (1 a %d) do candidato a remover: ", NCand);
  if (scanf("%d", &idRemover) != 1 || idRemover < 1 || idRemover > NCand) {
    printf("\nID invalido!\n");
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
      ;
    getchar();
    return;
  }

  int confirmarDelecao = 0;
  printf("Deseja realmente fazer a deleção?\n");
  printf("[1] - Sim\n");
  printf("[2] - Não\n");
  printf("Opção: ");
  scanf("%d", &confirmarDelecao);
  limparBuffer();

  if (confirmarDelecao != 1) {
    printf("Deleção cancelada!");
    sleep();
    return;
  }

  int indice = idRemover - 1;
  int i;
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
      printf("Digite um número!\n");
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
  int i,j;
  for (i = 0; i < tamanho - 1; i++) {
    for (j = 0; j < tamanho - i - 1; j++) {
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
  int i;
  for (i = 0; i < NCand; i++) {
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
  for (i = 0; i < cont; i++) {
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
  int i;
  for (i = 0; i < NCand; i++)
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
  sleep();
  return;
}

void menuEleicao() {
  limparTela();
  limparVotos();

  int j, resultado, opcaoVoto, confirmacaoVoto, votoFinalizado;
  int cargoescolha;
  Eleitor *eleitor = (Eleitor *)malloc(NElei * sizeof(Eleitor));

  if (eleitor == NULL)
    return;
	int i;
  for (i = 0; i < NElei; i++) {
    votoFinalizado = 0;
    while (votoFinalizado != 1) {
      resultado = 0;
      printf("|=======================================|\n");
      printf("|               ELEIÇÃO                 |\n");
      printf("|       VOTAÇÃO DO ELEITOR %d de %d       |\n", i + 1, NElei);
      printf("|=======================================|\n");
      printf("Nome do eleitor: ");
      scanf(" %49[^\n]", eleitor[i].nomeeleitor);
      printf("[1] - Escolher candidado\n");
      printf("[2] - Votar em BRANCO\n");
      printf("[3] - Votar NULO\n");
      printf("Digite: ");
      scanf("%d", &opcaoVoto);
      switch (opcaoVoto) {
      case 1:
        printf("Cargo a ser votado:\n");
        printf("[1] - Presidente\n");
        printf("[2] - Governador\n");
        printf("[3] - Prefeito\n");
        printf("[4] - Voltar\n");
        printf("Escolha: ");
        scanf("%d", &cargoescolha);

        if (cargoescolha == 1) {
          strcpy(eleitor[i].cargoescolha, "Presidente");
        } else if (cargoescolha == 2) {
          strcpy(eleitor[i].cargoescolha, "Governador");
        } else if (cargoescolha == 3) {
          strcpy(eleitor[i].cargoescolha, "Prefeito");
        } else if (cargoescolha == 4) {
          limparTela();
          break;
        }
        do {
          printf("%s\n", eleitor->cargoescolha);
          listarCandidatosPorCargo(eleitor[i].cargoescolha);
          printf("Sigla do %s(Inteiro com 2 digitos): ",
                 eleitor[i].cargoescolha);
          scanf("%d", &eleitor[i].siglaescolha);
          printf("\n");
          for (j = 0; j < NCand; j++) {
            if (eleitor[i].siglaescolha == candidatos[j].sigla) {
              printf("CANDIDATO: %s\nPARTIDO: %s\n", candidatos[j].nome,
                     candidatos[j].partido);
              resultado = 1;
              break;
            }
          }
          if (resultado != 1) {
            printf("Não existe nenhum candidato com essa sigla!\n");
            continue;
          }
        } while (resultado != 1);
        printf("[1] - Confirmar voto.\n");
        printf("[2] - Voltar para a Escolha de Sigla.\n");
        printf("Opção: ");
        scanf("%d", &confirmacaoVoto);
        if (confirmacaoVoto == 1) {
          candidatos[j].votos++;
          printf("Voto confirmado!\n");
          votoFinalizado = 1;
          limparTela();
          break;
        } else if (confirmacaoVoto == 2) {
          limparTela();
          continue;
        }
        break;
      case 2:
        printf("[1] - Confirmar o voto em BRANCO\n");
        printf("[2] - Voltar\n");
        printf("Escolha: ");
        scanf("%d", &confirmacaoVoto);
        if (confirmacaoVoto == 1) {
          TotalBrancos++;
          printf("Voto em BRANCO confirmado!\n");
          votoFinalizado = 1;
          limparTela();
          break;
        } else if (confirmacaoVoto == 2) {
          continue;
        }
        break;
      case 3:
        printf("[1] - Confirmar ANULAÇÃO de voto\n");
        printf("[2] - Voltar\n");
        printf("Escolha: ");
        scanf("%d", &confirmacaoVoto);
        if (confirmacaoVoto == 1) {
          TotalNulos++;
          printf("Voto ANULADO!\n");
          votoFinalizado = 1;
          limparTela();
          break;
        } else if (confirmacaoVoto == 2) {
          continue;
        }
        break;
      default:
        break;
      }
    }
  }
  free(eleitor);
  printf("VOTAÇÃO ENCERRADA!\n");
}
