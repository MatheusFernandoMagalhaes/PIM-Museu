#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_OBRAS 100
#define MAX_INGRESSOS 100
#define MAX_PERGUNTAS 6

struct ObraDeArte {
    int codigo;
    char titulo[100];
    char artista[100];
    char descricao[500];
    char ano[12];
};

struct Ingresso {
    int codigoObra;
    int tipo;
    int valido;
    char token[20];
};

struct Tema {
    struct ObraDeArte obras[MAX_OBRAS];
    int totalObras;
};

struct Museu {
    struct Tema temas[4];
    struct Ingresso ingressos[MAX_INGRESSOS];
    int totalIngressos;
};

struct Pesquisa {
    char pergunta[MAX_PERGUNTAS][100];
    char resposta[MAX_PERGUNTAS][100];
};

void listarObrasDoTema(struct Museu *museu, int tema) {
    printf("Lista de Obras de Arte no Museu (Tema %d):\n", tema);
    for (int i = 0; i < museu->temas[tema].totalObras; i++) {
        printf("Código: %d\n", museu->temas[tema].obras[i].codigo);
        printf("Título: %s\n", museu->temas[tema].obras[i].titulo);
        printf("Artista: %s\n", museu->temas[tema].obras[i].artista);
        printf("Descrição: %s\n", museu->temas[tema].obras[i].descricao);
        printf("Ano: %s\n", museu->temas[tema].obras[i].ano);
        printf("\n");
    }
}


void listarObras(struct Museu *museu, int tema, const struct Ingresso ingressos[], int totalIngressos) {
    printf("Lista de Obras de Arte no Museu (Tema %d):\n", tema);
    for (int i = 0; i < museu->temas[tema].totalObras; i++) {
        printf("Código: %d\n", museu->temas[tema].obras[i].codigo);
        printf("Título: %s\n", museu->temas[tema].obras[i].titulo);
        printf("Artista: %s\n", museu->temas[tema].obras[i].artista);
        printf("Descrição: %s\n", museu->temas[tema].obras[i].descricao);
        printf("Ano: %s\n", museu->temas[tema].obras[i].ano);
        printf("\n");
    }
}


void gerarToken(char *token) {
    sprintf(token, "%06d", rand() % 1000000);
}

void venderIngresso(struct Museu *museu, int codigoObra, int tipo) {
    float precoInteira = 20.0;
    float precoMeia = 10.0;
    float precoIsencao = 0.0;

    float precoTotal = 0.0;

    if (tipo == 0) {
        precoTotal = precoInteira;
    } else if (tipo == 1) {
        precoTotal = precoMeia;
    } else if (tipo == 2) {
        precoTotal = precoIsencao;
    } else {
        printf("Tipo de ingresso inválido.\n");
        return;
    }

    printf("Total a pagar: R$ %.2f\n", precoTotal);

    float pagamento;
    printf("Digite o valor do pagamento: ");
    scanf("%f", &pagamento);

    if (pagamento < precoTotal) {
        printf("Pagamento insuficiente. Ingresso não vendido.\n");
    } else {
        if (museu->totalIngressos < MAX_INGRESSOS) {
            char token[20];
            gerarToken(token);

            museu->ingressos[museu->totalIngressos].codigoObra = codigoObra;
            museu->ingressos[museu->totalIngressos].tipo = tipo;
            strncpy(museu->ingressos[museu->totalIngressos].token, token, sizeof(museu->ingressos[museu->totalIngressos].token));

            museu->ingressos[museu->totalIngressos].valido = 1;

            museu->totalIngressos++;
            printf("Ingresso vendido com sucesso. Seu token: %s\n", token);

            float troco = pagamento - precoTotal;
            if (troco > 0) {
                printf("Troco: R$ %.2f\n", troco);
            }
        } else {
            printf("O museu atingiu o limite de ingressos vendidos.\n");
        }
    }
}

void entrarNaObra(struct Museu *museu, int codigoObra, int tipo, const char *token, int *acessouObra) {
    int temaDaObra = -1;
    int i;

    for (i = 0; i < museu->totalIngressos; i++) {
        if (museu->ingressos[i].codigoObra == codigoObra && museu->ingressos[i].tipo == tipo &&
            museu->ingressos[i].valido && strcmp(museu->ingressos[i].token, token) == 0) {
            temaDaObra = codigoObra;
            break;
        }
    }

    if (temaDaObra != -1) {
        printf("Acesso concedido ao tema %d:\n", temaDaObra);
        listarObrasDoTema(museu, temaDaObra);
        museu->ingressos[i].valido = 0;
        *acessouObra = 1;
    } else {
        printf("Acesso negado. Verifique seu ingresso ou token.\n");
    }
}

void adicionarObra(struct Museu *museu, int tema, int codigo, const char titulo[100], const char artista[100], const char descricao[500], const char ano[12]) {
    if (museu->temas[tema].totalObras < MAX_OBRAS) {
        museu->temas[tema].obras[museu->temas[tema].totalObras].codigo = codigo;
        strncpy(museu->temas[tema].obras[museu->temas[tema].totalObras].titulo, titulo, sizeof(museu->temas[tema].obras[museu->temas[tema].totalObras].titulo));
        strncpy(museu->temas[tema].obras[museu->temas[tema].totalObras].artista, artista, sizeof(museu->temas[tema].obras[museu->temas[tema].totalObras].artista));
        strncpy(museu->temas[tema].obras[museu->temas[tema].totalObras].descricao, descricao, sizeof(museu->temas[tema].obras[museu->temas[tema].totalObras].descricao));
        strncpy(museu->temas[tema].obras[museu->temas[tema].totalObras].ano, ano, sizeof(museu->temas[tema].obras[museu->temas[tema].totalObras].ano));

        museu->temas[tema].totalObras++;
        printf("Obra adicionada com sucesso.\n");
    } else {
        printf("O museu atingiu o limite de obras para este tema.\n");
    }
}

void fazerPesquisa(struct Pesquisa *pesquisa) {
    printf("Responda às seguintes perguntas:\n");

    for (int i = 0; i < MAX_PERGUNTAS; i++) {
        printf("Pergunta %d: %s\n", i + 1, pesquisa->pergunta[i]);
        printf("Sua resposta: ");
        scanf("%s", pesquisa->resposta[i]);
    }
    printf("Obrigado por responder às perguntas!\n");
}

int main() {
    int respondeuPesquisa = 0;
    int acessouObra = 0;
    struct Museu museu;
    for (int i = 0; i < 4; i++) {
        museu.temas[i].totalObras = 0;
    }

    museu.totalIngressos = 0;

    adicionarObra(&museu, 0, 1, "Abaporu", "Tarsila do Amaral", "Abaporu é uma das pinturas mais icônicas do modernismo brasileiro. Tarsila do Amaral a criou em 1928, como presente de aniversário para o escritor Oswald de Andrade, seu marido. A obra retrata uma figura humana estilizada de proporções exageradas, deitada em um ambiente onírico. Ela simboliza a fusão das culturas indígenas e europeias, um tema recorrente na Semana Moderna.", "1928");
    adicionarObra(&museu, 0, 2, "O Homem Amarelo", "Anita Malfatti", "O Homem Amarelo é uma das obras mais famosas de Anita Malfatti, exibida na Semana de Arte Moderna de 1922. A pintura retrata um homem com a pele de um tom amarelo e expressão melancólica. A obra foi considerada escandalosa na época, mas também foi um dos primeiros exemplos do expressionismo no Brasil.", "1915");
    adicionarObra(&museu, 0, 3, "Manifesto Antropófago", "Oswald de Andrade", "Embora não seja uma obra de arte visual, o Manifesto Antropófago de Oswald de Andrade é uma peça fundamental do movimento modernista no Brasil. O manifesto defende a ideia de devorar a cultura estrangeira, assimilando-a e transformando-a em algo genuinamente brasileiro. Essa obra teórica influenciou profundamente a arte e a literatura modernistas no país.", "1915");
    adicionarObra(&museu, 1, 1, "O Pai da Aviação Brasileira", "Santos Dumont", "Esta discussão abordaria a vida e as realizações de Alberto Santos Dumont como pioneiro da aviação no Brasil e no mundo. Explore seus experimentos, invenções e seu papel fundamental na história da aviação.", "1873-1932");
    adicionarObra(&museu, 1, 2, "Os Desafios e Conquistas nos Céus", "Santos Dumont", "Neste tema, você pode analisar as diversas aeronaves que Santos Dumont projetou e pilotou, incluindo o 14-bis (1906) e o Demoiselle (1907), e como essas inovações influenciaram o desenvolvimento da aviação.", "1906-1907");
    adicionarObra(&museu, 1, 3, "Legado e Impacto na Sociedade Moderna", "Santos Dumont", "Este tema se concentra no impacto duradouro de Santos Dumont na sociedade moderna. Discuta como suas contribuições à aviação moldaram o transporte, a exploração e a tecnologia, além de sua influência na cultura brasileira e internacional.", "1906-1907");
    adicionarObra(&museu, 2, 1, "Preparativos e Expectativas Olímpicas", "Paris 2024", "Neste tema, você pode discutir os preparativos em andamento para os Jogos Olímpicos de Paris em 2024, incluindo a infraestrutura, instalações esportivas, questões de logística e as expectativas tanto dos organizadores quanto dos atletas e espectadores.", "2024");
    adicionarObra(&museu, 2, 2, "Sustentabilidade nos Jogos Olímpicos de Paris 2024", "Paris 2024", " Este tema aborda os esforços de Paris 2024 para tornar os Jogos mais sustentáveis, com foco em questões ambientais, econômicas e sociais. Você pode discutir as iniciativas de sustentabilidade, como o uso de energias renováveis, transporte público eficiente e iniciativas de reciclagem.", "2024");
    adicionarObra(&museu, 2, 3, "Legado dos Jogos Olímpicos de Paris 2024", "Paris 2024", "Explore como os Jogos Olímpicos de Paris 2024 podem deixar um legado duradouro para a cidade, o país e o movimento olímpico global. Discuta como as Olimpíadas podem impactar o turismo, o esporte, a cultura e a economia de Paris e da França no longo prazo.", "2024");

    int opcao;
    int temaSelecionado = 0;
    char token[20];

    struct Pesquisa pesquisa;
    strcpy(pesquisa.pergunta[0], "Qual o seu nome?");
    strcpy(pesquisa.pergunta[1], "Qual o seu sexo?");
    strcpy(pesquisa.pergunta[2], "Qual sua idade?");
    strcpy(pesquisa.pergunta[3], "De 0 a 10, o quanto você gostou das obras?");
    strcpy(pesquisa.pergunta[4], "De 0 a 10, o quanto você recomendaria o nosso museu a um amigo?");
    strcpy(pesquisa.pergunta[5], "Você visitaria o museu novamente?");

    do {
        printf("Museu de Arte\n");
        printf("Temas:\n");
        printf("0. 100 anos da Semana de Arte Moderna\n");
        printf("1. 150 anos de Santos Dumont\n");
        printf("2. Jogos Olímpicos de Paris 2024\n");
        printf("3. Inteligência Artificial\n");
        printf("4. Sair\n");
        printf("Escolha um tema ou saia: ");
        scanf("%d", &temaSelecionado);

        if (temaSelecionado >= 0 && temaSelecionado < 4) {
            do {
                printf("Tema selecionado: %d\n", temaSelecionado);
                printf("1. Listar obras\n");
                printf("2. Comprar ingresso\n");
                printf("3. Acessar obra\n");
                printf("4. Responder à pesquisa (depois de acessar uma obra)\n");
                printf("5. Voltar ao menu principal\n");
                printf("Escolha uma opção: ");
                scanf("%d", &opcao);

                switch (opcao) {
                    case 1:
                        listarObras(&museu, temaSelecionado, museu.ingressos, museu.totalIngressos);
                        break;
                    case 2:
                        int codigoObra;
                        int tipo;
                        printf("Digite o código da obra: ");
                        scanf("%d", &codigoObra);
                        printf("Escolha o tipo de ingresso:\n");
                        printf("0. Inteira (R$20.00)\n");
                        printf("1. Meia (R$10.00)\n");
                        printf("2. Isenção (gratuito)\n");
                        printf("Escolha o tipo de ingresso: ");
                        scanf("%d", &tipo);
                        venderIngresso(&museu, codigoObra, tipo);
                        acessouObra = 1;
                        break;
                    case 3:
                        if (acessouObra) {
                            printf("Digite o código da obra: ");
                            scanf("%d", &codigoObra);
                            printf("Digite o tipo de ingresso: ");
                            scanf("%d", &tipo);
                            printf("Digite o token: ");
                            scanf("%s", token);
                            entrarNaObra(&museu, codigoObra, tipo, token, &acessouObra);
                        } else {
                            printf("Por favor, acesse uma obra antes de responder à pesquisa.\n");
                        }
                        break;
                    case 4:
                        if (acessouObra) {
                            fazerPesquisa(&pesquisa);
                            respondeuPesquisa = 1;
                        } else {
                            printf("Por favor, acesse uma obra antes de responder à pesquisa.\n");
                        }
                        break;
                    case 5:
                        break;
                    default:
                        printf("Opção inválida.\n");
                }
            } while (opcao != 5);
        } else if (temaSelecionado != 4) {
            printf("Tema inválido. Escolha um tema válido ou saia.\n");
        }
    } while (temaSelecionado != 4);

    return 0;
}
