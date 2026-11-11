#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <errno.h> 

#define MAX_ACOES 100
#define TAM_TEXTO 100

typedef enum {
    STATUS_PLANEJADA,
    STATUS_REALIZADA,
    STATUS_CANCELADA
} Situacao;

typedef struct {
    int codigo;
    char escola[TAM_TEXTO];
    char tema[TAM_TEXTO];
    char dataPrevista[11];
    char publicoAlvo[TAM_TEXTO];
    char responsavel[TAM_TEXTO];
    int participantesPrevistos;
    int participantesEfetivos;
    Situacao situacao;
} Acao;

void exibirMenu() {
    printf("\n========== PSE EM ACAO ==========\n");
    printf("1 - Cadastrar acao\n");
    printf("2 - Listar acoes\n");
    printf("3 - Consultar acao\n");
    printf("4 - Atualizar situacao\n");
    printf("5 - Exibir relatorio geral\n");
    printf("0 - Sair\n");
    printf("=================================\n");
}


int lerInteiro(const char mensagem[]) {

    char entrada[100];
    char *fim;
    long valor;
    int caractere;

    while (1) {

        printf("%s", mensagem);

        if (fgets(entrada, sizeof(entrada), stdin) == NULL) {
            printf("Erro ao ler entrada.\n");
            return 0;
        }

        // Verifica se a linha ultrapassou o limite
        if (strchr(entrada, '\n') == NULL) {

            caractere = getchar();

            if (caractere != '\n' && caractere != EOF) {

                while ((caractere = getchar()) != '\n' &&
                       caractere != EOF) {
                }

                printf("Entrada muito longa! Tente novamente.\n");
                continue;
            }
        }

        errno = 0;
        valor = strtol(entrada, &fim, 10);

        if (fim == entrada) {
            printf("Entrada invalida! Digite um numero inteiro.\n");
            continue;
        }

        while (isspace((unsigned char)*fim)) {
            fim++;
        }

        if (*fim != '\0' || errno == ERANGE ||
            valor < INT_MIN || valor > INT_MAX) {

            printf("Entrada invalida! Digite um numero inteiro valido.\n");
            continue;
        }

        return (int)valor;
    }
}



void lerTexto(const char mensagem[], char *destino, int tamanho) {

    int caractere;
    int possuiLetra;

    while (1) {

        printf("%s", mensagem);

        if (fgets(destino, tamanho, stdin) == NULL) {
            printf("\nErro ao ler entrada.\n");
            exit(EXIT_FAILURE);
        }

        // Verifica se a entrada ultrapassou o limite
        if (strchr(destino, '\n') == NULL) {

            caractere = getchar();

            if (caractere != '\n' && caractere != EOF) {

                while ((caractere = getchar()) != '\n' && caractere != EOF) {
                }

                printf("Texto muito longo! Tente novamente.\n");
                continue;
            }

        } else {
            destino[strcspn(destino, "\n")] = '\0';
        }

        // Verifica se existe pelo menos uma letra
        possuiLetra = 0;

        for (int i = 0; destino[i] != '\0'; i++) {

            if (isalpha((unsigned char)destino[i])) {
                possuiLetra = 1;
                break;
            }
        }

        if (!possuiLetra) {
            printf("\nEntrada invalida! Digite um texto que contenha pelo menos uma letra.\n");
            continue;
        }

        return;
    }
}


int validarData(const char data[]){
    int dia, mes, ano;

    if (strlen(data) != 10) {
        return 0;
    }

    if (data[2] != '/' || data[5] != '/') {
        return 0;
    }

    for (int i = 0; i < 10; i++){
        if (i == 2 || i == 5) {
            continue;
        }

        if (!isdigit((unsigned char)data[i])) {
            return 0;
        }
    
    }

    dia = (data[0] - '0') * 10 + (data[1] - '0');
    mes = (data[3] - '0') * 10 + (data[4] - '0');
    ano = (data[6] - '0') * 1000 + (data[7] - '0') * 100 + (data[8] - '0') * 10 + (data[9] - '0');

    if(ano < 1 || mes < 1 || mes > 12 || dia < 1) {
        return 0;
    }

    int diasPorMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (ano % 400 == 0 || (ano % 4 == 0 && ano % 100 != 0)) {
        diasPorMes[1] = 29;
    }

    if (dia > diasPorMes[mes - 1]) {
        return 0;
    }

    return 1;
}

void exibirSituacao(Situacao situacao) {
    switch (situacao) {
        case STATUS_PLANEJADA:
            printf("Planejada");
            break;
        case STATUS_REALIZADA:
            printf("Realizada");
            break;
        case STATUS_CANCELADA:
            printf("Cancelada");
            break;
        default:
            printf("Situacao desconhecida");
    }
}

void listarAcoes(Acao acoes[], int totalAcoes) {
    if (totalAcoes == 0) {
        printf("\nNenhuma acao cadastrada.\n");
        return;
    }

    printf("\n========== ACOES CADASTRADAS ==========\n");
    for (int i = 0; i < totalAcoes; i++) {
        printf("Codigo: %d\n", acoes[i].codigo);
        printf("Escola: %s\n", acoes[i].escola);
        printf("Tema: %s\n", acoes[i].tema);
        printf("Data Prevista: %s\n", acoes[i].dataPrevista);
        printf("Publico Alvo: %s\n", acoes[i].publicoAlvo);
        printf("Responsavel: %s\n", acoes[i].responsavel);

        printf("Participantes Previstos: %d\n", acoes[i].participantesPrevistos);

        printf("Participantes Efetivos: %d\n", acoes[i].participantesEfetivos);

        printf("Situacao: ");
        exibirSituacao(acoes[i].situacao);

        printf("\n-----------------------------------\n");
    }
}


void consultarAcao(Acao acoes[], int totalAcoes) {
    int opcao;
    int encontrou = 0;
    int codigoBusca;
    char termoBusca[TAM_TEXTO];

    if (totalAcoes == 0) {
        printf("\nNenhuma acao cadastrada para consultar.\n");
        return;
    }

    printf("\n========== CONSULTAR ACAO ==========\n");
    printf("1 - Consultar por codigo\n");
    printf("2 - Consultar por escola\n");
    printf("3 - Consultar por tema\n");

    opcao = lerInteiro("Escolha uma opcao: ");

    switch (opcao) {

        case 1:
            codigoBusca = lerInteiro("Digite o codigo da acao: ");

            for (int i = 0; i < totalAcoes; i++) {
                if (acoes[i].codigo == codigoBusca) {
                    encontrou = 1;

                    printf("\nAcao encontrada!\n");
                    printf("Codigo: %d\n", acoes[i].codigo);
                    printf("Escola: %s\n", acoes[i].escola);
                    printf("Tema: %s\n", acoes[i].tema);
                    printf("Data prevista: %s\n", acoes[i].dataPrevista);
                    printf("Publico-alvo: %s\n", acoes[i].publicoAlvo);
                    printf("Responsavel: %s\n", acoes[i].responsavel);
                    printf("Participantes previstos: %d\n", acoes[i].participantesPrevistos);
                    printf("Participantes efetivos: %d\n", acoes[i].participantesEfetivos);
                    printf("Situacao: ");
                    exibirSituacao(acoes[i].situacao);
                    printf("\n");
                    break;
                }
            }
            break;

        case 2:
            lerTexto("Digite o nome ou parte do nome da escola: ",
                     termoBusca, TAM_TEXTO);

            for (int i = 0; i < totalAcoes; i++) {
                if (strstr(acoes[i].escola, termoBusca) != NULL) {
                    encontrou = 1;

                    printf("\nCodigo: %d | Escola: %s | Tema: %s\n",
                           acoes[i].codigo,
                           acoes[i].escola,
                           acoes[i].tema);
                }
            }
            break;

        case 3:
            lerTexto("Digite o tema ou parte do tema: ",
                     termoBusca, TAM_TEXTO);

            for (int i = 0; i < totalAcoes; i++) {
                if (strstr(acoes[i].tema, termoBusca) != NULL) {
                    encontrou = 1;

                    printf("\nCodigo: %d | Escola: %s | Tema: %s\n",
                           acoes[i].codigo,
                           acoes[i].escola,
                           acoes[i].tema);
                }
            }
            break;

        default:
            printf("\nOpcao de consulta invalida!\n");
            return;
    }

    if (!encontrou) {
        printf("\nNenhuma acao encontrada com os dados informados.\n");
    }
}


void atualizarSituacao(Acao acoes[], int totalAcoes) {
    int codigoBusca;
    int encontrou = 0;
    int novaSituacao;
    int participantes;

    if (totalAcoes == 0) {
        printf("\nNenhuma acao cadastrada para atualizar.\n");
        return;
    }

    printf("\n========== ATUALIZAR SITUACAO ==========\n");

    codigoBusca = lerInteiro("Digite o codigo da acao: ");

    for (int i = 0; i < totalAcoes; i++) {

        if (acoes[i].codigo == codigoBusca) {
            encontrou = 1;

            printf("\nAcao encontrada: %s\n", acoes[i].tema);

            printf("\nSituacao atual: ");
            exibirSituacao(acoes[i].situacao);

            printf("\n\nEscolha a nova situacao:\n");
            printf("1 - Planejada\n");
            printf("2 - Realizada\n");
            printf("3 - Cancelada\n");

            novaSituacao = lerInteiro("Digite a opcao: ");

            switch (novaSituacao) {

                case 1:
                    acoes[i].situacao = STATUS_PLANEJADA;
                    acoes[i].participantesEfetivos = 0;
                    printf("\nSituacao atualizada para Planejada!\n");
                    break;

                case 2:
                    do {
                        participantes = lerInteiro(
                            "Digite a quantidade de participantes efetivos: ");

                        if (participantes < 0) {
                            printf("\nErro: a quantidade nao pode ser negativa!\n");
                        }

                    } while (participantes < 0);

                    acoes[i].situacao = STATUS_REALIZADA;
                    acoes[i].participantesEfetivos = participantes;

                    printf("\nAcao marcada como Realizada!\n");
                    break;

                case 3:
                    acoes[i].situacao = STATUS_CANCELADA;
                    acoes[i].participantesEfetivos = 0;
                    printf("\nAcao marcada como Cancelada!\n");
                    break;

                default:
                    printf("\nOpcao de situacao invalida!\n");
                    return;
            }

            break;
        }
    }

    if (!encontrou) {
        printf("\nNenhuma acao encontrada com esse codigo.\n");
    }
}



void exibirRelatorio(Acao acoes[], int totalAcoes) {

    int planejadas = 0;
    int realizadas = 0;
    int canceladas = 0;

    long long totalPrevistos = 0;
    long long totalEfetivos = 0;

    double percentual = 0.0;

    printf("\n========== RELATORIO GERAL ==========\n");

    if (totalAcoes == 0) {
        printf("\nNenhuma acao cadastrada.\n");
        return;
    }

    for (int i = 0; i < totalAcoes; i++) {

        switch (acoes[i].situacao) {

            case STATUS_PLANEJADA:
                planejadas++;
                break;

            case STATUS_REALIZADA:
                realizadas++;
                totalPrevistos += acoes[i].participantesPrevistos;
                totalEfetivos += acoes[i].participantesEfetivos;
                break;

            case STATUS_CANCELADA:
                canceladas++;
                break;
        }
    }

    printf("\nTotal de acoes cadastradas: %d\n", totalAcoes);
    printf("Acoes planejadas: %d\n", planejadas);
    printf("Acoes realizadas: %d\n", realizadas);
    printf("Acoes canceladas: %d\n", canceladas);

    printf("\nParticipantes previstos nas acoes realizadas: %lld\n",
           totalPrevistos);

    printf("Total de participantes efetivos: %lld\n",
           totalEfetivos);

    if (totalPrevistos > 0) {

        percentual = ((double)totalEfetivos / totalPrevistos) * 100;

        printf("Percentual de participacao: %.2f%%\n", percentual);

    } else {

        printf("Percentual de participacao: Nao disponivel.\n");
        printf("Nao ha participantes previstos em acoes realizadas.\n");
    }

    printf("\n=====================================\n");
}





int codigoJaExiste(Acao acoes[], int totalAcoes, int codigo) {

    for (int i = 0; i < totalAcoes; i++) {

        if (acoes[i].codigo == codigo) {
            return 1;
        }
    }

    return 0;
}


void cadastrarAcao(Acao acoes[], int *totalAcoes) {

    char entradaData[100];
    int caractere;
    int opcaoSituacao;

    if (*totalAcoes >= MAX_ACOES) {
        printf("\nLimite maximo de acoes atingido!\n");
        return;
    }

    printf("\n========== CADASTRO DE ACAO ==========\n");

    acoes[*totalAcoes].codigo = lerInteiro("Digite o codigo da acao: ");

    if (acoes[*totalAcoes].codigo <= 0) {
        printf("\nErro: o codigo deve ser um numero maior que zero!\n");
        return;
    }

    if (codigoJaExiste(acoes, *totalAcoes, acoes[*totalAcoes].codigo)) {
        printf("\nErro: ja existe uma acao com esse codigo!\n");
        return;
    }

    lerTexto("Digite o nome da escola: ",
             acoes[*totalAcoes].escola,
             TAM_TEXTO);

    lerTexto("Digite o tema da acao: ",
             acoes[*totalAcoes].tema,
             TAM_TEXTO);

    // Leitura e validacao da data
    do {
        printf("Digite a data prevista (dd/mm/aaaa): ");

        if (fgets(entradaData, sizeof(entradaData), stdin) == NULL) {
            printf("Erro ao ler a data.\n");
            return;
        }

        // Verifica se a linha foi lida completamente
        if (strchr(entradaData, '\n') == NULL) {

            while ((caractere = getchar()) != '\n' && caractere != EOF) {
            }

            printf("\nErro: Data muito longa! Tente novamente.\n");
            continue;
        }

        // Remove a quebra de linha
        entradaData[strcspn(entradaData, "\n")] = '\0';

        // Valida a data
        if (!validarData(entradaData)) {
            printf("\nErro: Data invalida! Digite no formato DD/MM/AAAA.\n");
            continue;
        }

        // Armazena a data validada
        strcpy(acoes[*totalAcoes].dataPrevista, entradaData);

    } while (!validarData(acoes[*totalAcoes].dataPrevista));

    lerTexto("Digite o publico-alvo: ",
             acoes[*totalAcoes].publicoAlvo,
             TAM_TEXTO);

    lerTexto("Digite o responsavel: ",
             acoes[*totalAcoes].responsavel,
             TAM_TEXTO);

    // Leitura da quantidade de participantes previstos
    do {
        acoes[*totalAcoes].participantesPrevistos =
            lerInteiro("Digite a quantidade de participantes previstos: ");

        if (acoes[*totalAcoes].participantesPrevistos < 0) {
            printf("\nErro: a quantidade nao pode ser negativa! Tente novamente.\n");
        }

    } while (acoes[*totalAcoes].participantesPrevistos < 0);

    // Escolha da situacao inicial
    do {
        printf("\nEscolha a situacao inicial da acao:\n");
        printf("1 - Planejada\n");
        printf("2 - Realizada\n");
        printf("3 - Cancelada\n");

        opcaoSituacao = lerInteiro("Digite a opcao: ");

        if (opcaoSituacao < 1 || opcaoSituacao > 3) {
            printf("\nOpcao invalida! Escolha entre 1 e 3.\n");
        }

    } while (opcaoSituacao < 1 || opcaoSituacao > 3);

    // Define a situacao e os participantes efetivos
    if (opcaoSituacao == 1) {

        acoes[*totalAcoes].situacao = STATUS_PLANEJADA;
        acoes[*totalAcoes].participantesEfetivos = 0;

    } else if (opcaoSituacao == 2) {

        acoes[*totalAcoes].situacao = STATUS_REALIZADA;

        do {
            acoes[*totalAcoes].participantesEfetivos =
                lerInteiro("Digite a quantidade de participantes efetivos: ");

            if (acoes[*totalAcoes].participantesEfetivos < 0) {
                printf("\nErro: a quantidade nao pode ser negativa! Tente novamente.\n");
            }

        } while (acoes[*totalAcoes].participantesEfetivos < 0);

    } else {

        acoes[*totalAcoes].situacao = STATUS_CANCELADA;
        acoes[*totalAcoes].participantesEfetivos = 0;
    }

    // Confirma o cadastro
    (*totalAcoes)++;

    printf("\nAcao cadastrada com sucesso!\n");
}


int main(void) {

    Acao acoes[MAX_ACOES];
    int totalAcoes = 0;
    int opcao;

    do {
        exibirMenu();
       opcao = lerInteiro("Escolha uma opcao: ");

        switch (opcao) {
            case 1:
                cadastrarAcao(acoes, &totalAcoes);
               break;
            case 2:
                listarAcoes(acoes, totalAcoes);
                break;

            case 3: 
                consultarAcao(acoes, totalAcoes);
                break;

            case 4:
                atualizarSituacao(acoes, totalAcoes);
                break;

            case 5:
                exibirRelatorio(acoes, totalAcoes);
                break;

            case 0: 
                printf("\nEncerrando o sistema... Ate logo!\n");
                break;
            
            default:
                printf("\nOpcao invalida! Tente novamente..\n");
        }

    } while (opcao != 0);

    return 0;
}