# Sistema de Urna Eletrônica - Trabalho Final (2025.2)

Este repositório contém a implementação de um **Sistema de Votação e Urna Eletrônica**, desenvolvido como Trabalho Final da disciplina de **Programação Computacional** na Universidade Federal do Ceará (UFC).

O projeto foi desenvolvido estritamente seguindo o padrão **C ANSI (C89/C90)**, simulando o fluxo completo de uma eleição, desde o cadastro de candidatos até a apuração dos votos.

## 👨‍🏫 Informações da Disciplina

- **Disciplina:** Programação Computacional
- **Professor:** Fernando Rodrigues de Almeida Júnior
- **Semestre:** 2025.2

## 👥 Autores da Equipe

| Nome                                      | Matrícula |
| :---------------------------------------- | :-------: |
| **Francisco Eduardo Sampaio Moreira**     |  583753   |
| **Michel Rooney Ferreira Araújo**         |  579815   |
| **Francisco Gabriel Albuquerque Portela** |  583754   |

## 📋 Descrição do Projeto

O objetivo deste software é simular uma urna eletrônica via terminal. O sistema é dividido em dois módulos principais: **Administrativo** (configuração da eleição) e **Votação** (coleta de votos dos eleitores).

### Funcionalidades Implementadas

#### 1. Módulo Administrativo (Acesso Restrito)

- Protegido por senha de administrador: **`ue@2022`**.
- Configuração dos dados da eleição:
  - Definição do cargo disputado (Presidente, Governador ou Prefeito).
  - Definição do número de candidatos (_NCand_).
  - Definição do número de eleitores (_NElei_).
- Cadastro de Candidatos (armazenados em **Structs**):
  - Nome Completo (até 50 caracteres).
  - Número da Sigla (2 dígitos).
  - Partido (até 12 caracteres).

#### 2. Módulo de Votação

- O sistema realiza a **alocação dinâmica** de memória para registrar os votos de acordo com o número de eleitores (_NElei_).
- Estrutura do Voto:
  - Cargo votado.
  - Número do candidato escolhido.
  - Nome do eleitor.
- **Validação em Tempo Real:**
  - Ao digitar a sigla, o sistema exibe o nome do candidato.
  - Se o número não existir, o sistema alerta "Voto inválido". Caso o eleitor confirme, o voto é computado como **Nulo**.

#### 3. Módulo de Apuração

- Gera um relatório final contendo:
  - Total de votos por candidato.
  - Total de votos brancos.
  - Total de votos nulos.
  - Resultado final da eleição.

## 🛠️ Tecnologias e Conceitos Utilizados

O projeto foi escrito em **Linguagem C** respeitando o padrão ANSI (C89/C90). Foram aplicados os seguintes conceitos:

- **Structs (Registros):** Para modelagem de Candidatos e Votos.
- **Arrays (Vetores):** Para armazenamento das listas de candidatos.
- **Manipulação de Strings:** Tratamento de nomes e partidos.
- **Controle de Fluxo:** Validação de senhas e menus interativos.

## 🚀 Como Compilar e Rodar

Siga as instruções abaixo para executar o programa em sua máquina.

### Pré-requisitos

- Compilador GCC (GNU Compiler Collection).

### Compilação (Via Terminal)

Para garantir a compatibilidade com o padrão ANSI exigido, utilize as flags abaixo:

```bash
gcc main.c -o urna -ansi -Wall -pedantic
```

- `-ansi`: Força o compilador a seguir o padrão C89/C90.
- `-Wall`: Ativa todos os avisos de compilação (boa prática).
- `-pedantic`: Garante adesão estrita ao padrão ISO C.

### Execução

- **Windows:**
  ```cmd
  urna.exe
  ```
- **Linux/Mac:**
  ```bash
  ./urna
  ```

## 🖥️ Exemplo de Uso

1.  Ao iniciar, insira a senha de admin: `ue@2022`.
2.  Defina o cargo (ex: Prefeito) e a quantidade de candidatos/eleitores.
3.  Cadastre os candidatos (Ex: _Nome: Fulano, Sigla: 10, Partido: ABC_).
4.  O sistema abrirá a votação para os _N_ eleitores sequencialmente.
5.  Ao final, o relatório de vencedores será exibido na tela.

---

**Nota:** Este software é um projeto acadêmico e não possui valor legal para eleições reais.
