#include <stdio.h>

#include "../model/entidades/instancia/instancia.h"
#include "../model/entidades/solucao/solucao.h"
#include "../model/entidades/tarefa/tarefa.h"
#include "../services/gerenciador_de_custos/gerenciador_de_custos.h"

static Boolean prepararInstanciaDeTeste(Instancia *instancia) {
    if(inicializarInstancia(instancia,NOME_ARQUIVO_SCH10,(InteiroPositivoDe16Bits) 1,(QuantidadeDeTarefas) 3) == FALSO) {
        return FALSO;
    }

    if(instanciaAdicionarTarefa(
        instancia,
        (QuantidadeDeTarefas) 0,
        criarTarefa(
            (IdentificadorDeTarefa) 1,
            (TempoDeProcessamento) 10,
            (Penalidade) 4,
            (Penalidade) 8
        )
    ) == FALSO) {
        return FALSO;
    }

    if(instanciaAdicionarTarefa(
        instancia,
        (QuantidadeDeTarefas) 1,
        criarTarefa(
            (IdentificadorDeTarefa) 2,
            (TempoDeProcessamento) 20,
            (Penalidade) 5,
            (Penalidade) 6
        )
    ) == FALSO) {
        return FALSO;
    }

    if(instanciaAdicionarTarefa(
        instancia,
        (QuantidadeDeTarefas) 2,
        criarTarefa(
            (IdentificadorDeTarefa) 3,
            (TempoDeProcessamento) 30,
            (Penalidade) 7,
            (Penalidade) 9
        )
    ) == FALSO) {
        return FALSO;
    }

    return VERDADEIRO;
}

static Boolean prepararSolucao123(Solucao *solucao) {
    if(inicializarSolucao(solucao,(QuantidadeDeTarefas) 3) == FALSO) {
        return FALSO;
    }

    if(solucaoDefinirTarefaNaPosicao(solucao,(QuantidadeDeTarefas) 0,(IdentificadorDeTarefa) 1) == FALSO) {
        return FALSO;
    }

    if(solucaoDefinirTarefaNaPosicao(solucao,(QuantidadeDeTarefas) 1,(IdentificadorDeTarefa) 2) == FALSO) {
        return FALSO;
    }

    if(solucaoDefinirTarefaNaPosicao(solucao,(QuantidadeDeTarefas) 2,(IdentificadorDeTarefa) 3) == FALSO) {
        return FALSO;
    }

    return VERDADEIRO;
}

static Boolean prepararSolucao321(Solucao *solucao) {
    if(inicializarSolucao(solucao,(QuantidadeDeTarefas) 3) == FALSO) {
        return FALSO;
    }

    if(solucaoDefinirTarefaNaPosicao(solucao,(QuantidadeDeTarefas) 0,(IdentificadorDeTarefa) 3) == FALSO) {
        return FALSO;
    }

    if(solucaoDefinirTarefaNaPosicao(solucao,(QuantidadeDeTarefas) 1,(IdentificadorDeTarefa) 2) == FALSO) {
        return FALSO;
    }

    if(solucaoDefinirTarefaNaPosicao(solucao,(QuantidadeDeTarefas) 2,(IdentificadorDeTarefa) 1) == FALSO) {
        return FALSO;
    }

    return VERDADEIRO;
}

static int testarCalculoDeCustoDaSolucao123(void) {
    Instancia instancia;
    Solucao solucao;
    Custo custo;
    Boolean resultado;

    instancia = criarInstanciaVazia();
    solucao = criarSolucaoVazia();
    custo = 0;

    if(prepararInstanciaDeTeste(&instancia) == FALSO) {
        printf("[ERRO] Instancia de teste nao foi preparada.\n");

        return 1;
    }

    if(prepararSolucao123(&solucao) == FALSO) {
        printf("[ERRO] Solucao 1-2-3 nao foi preparada.\n");
        liberarInstancia(&instancia);

        return 1;
    }

    resultado = gerenciadorDeCustosCalcularCustoDaSolucao(
        &instancia,
        &solucao,
        (DataDeEntregaComum) 36,
        &custo
    );

    if(resultado == FALSO) {
        printf("[ERRO] Calculo de custo da solucao 1-2-3 deveria funcionar.\n");
        liberarSolucao(&solucao);
        liberarInstancia(&instancia);

        return 1;
    }

    if(custo != 350) {
        printf("[ERRO] Custo da solucao 1-2-3 deveria ser 350.\n");
        liberarSolucao(&solucao);
        liberarInstancia(&instancia);

        return 1;
    }

    liberarSolucao(&solucao);
    liberarInstancia(&instancia);

    printf("[OK] Calculo de custo da solucao 1-2-3.\n");

    return 0;
}

static int testarCalculoDeCustoDaSolucao321(void) {
    Instancia instancia;
    Solucao solucao;
    Custo custo;
    Boolean resultado;

    instancia = criarInstanciaVazia();
    solucao = criarSolucaoVazia();
    custo = 0;

    if(prepararInstanciaDeTeste(&instancia) == FALSO) {
        printf("[ERRO] Instancia de teste nao foi preparada.\n");

        return 1;
    }

    if(prepararSolucao321(&solucao) == FALSO) {
        printf("[ERRO] Solucao 3-2-1 nao foi preparada.\n");
        liberarInstancia(&instancia);

        return 1;
    }

    resultado = gerenciadorDeCustosCalcularCustoDaSolucao(
        &instancia,
        &solucao,
        (DataDeEntregaComum) 36,
        &custo
    );

    if(resultado == FALSO) {
        printf("[ERRO] Calculo de custo da solucao 3-2-1 deveria funcionar.\n");
        liberarSolucao(&solucao);
        liberarInstancia(&instancia);

        return 1;
    }

    if(custo != 318) {
        printf("[ERRO] Custo da solucao 3-2-1 deveria ser 318.\n");
        liberarSolucao(&solucao);
        liberarInstancia(&instancia);

        return 1;
    }

    liberarSolucao(&solucao);
    liberarInstancia(&instancia);

    printf("[OK] Calculo de custo da solucao 3-2-1.\n");

    return 0;
}

static int testarCustoZeroQuandoTodasConcluemEmD(void) {
    Instancia instancia;
    Solucao solucao;
    Custo custo;
    Boolean resultado;

    instancia = criarInstanciaVazia();
    solucao = criarSolucaoVazia();
    custo = 999;

    inicializarInstancia(&instancia,NOME_ARQUIVO_SCH10,(InteiroPositivoDe16Bits) 1,(QuantidadeDeTarefas) 1);

    instanciaAdicionarTarefa(
        &instancia,
        (QuantidadeDeTarefas) 0,
        criarTarefa(
            (IdentificadorDeTarefa) 1,
            (TempoDeProcessamento) 10,
            (Penalidade) 4,
            (Penalidade) 8
        )
    );

    inicializarSolucao(&solucao,(QuantidadeDeTarefas) 1);
    solucaoDefinirTarefaNaPosicao(&solucao,(QuantidadeDeTarefas) 0,(IdentificadorDeTarefa) 1);

    resultado = gerenciadorDeCustosCalcularCustoDaSolucao(
        &instancia,
        &solucao,
        (DataDeEntregaComum) 10,
        &custo
    );

    if(resultado == FALSO) {
        printf("[ERRO] Calculo de custo zero deveria funcionar.\n");
        liberarSolucao(&solucao);
        liberarInstancia(&instancia);

        return 1;
    }

    if(custo != 0) {
        printf("[ERRO] Custo deveria ser zero quando a tarefa conclui exatamente em d.\n");
        liberarSolucao(&solucao);
        liberarInstancia(&instancia);

        return 1;
    }

    liberarSolucao(&solucao);
    liberarInstancia(&instancia);

    printf("[OK] Custo zero quando conclui exatamente em d.\n");

    return 0;
}

static int testarInstanciaNulaInvalida(void) {
    Solucao solucao;
    Custo custo;

    solucao = criarSolucaoVazia();
    custo = 0;

    inicializarSolucao(&solucao,(QuantidadeDeTarefas) 1);
    solucaoDefinirTarefaNaPosicao(&solucao,(QuantidadeDeTarefas) 0,(IdentificadorDeTarefa) 1);

    if(gerenciadorDeCustosCalcularCustoDaSolucao(NULL,&solucao,(DataDeEntregaComum) 10,&custo) != FALSO) {
        printf("[ERRO] Instancia NULL deveria falhar.\n");
        liberarSolucao(&solucao);

        return 1;
    }

    liberarSolucao(&solucao);

    printf("[OK] Instancia nula invalida no gerenciador de custos.\n");

    return 0;
}

static int testarSolucaoNulaInvalida(void) {
    Instancia instancia;
    Custo custo;

    instancia = criarInstanciaVazia();
    custo = 0;

    prepararInstanciaDeTeste(&instancia);

    if(gerenciadorDeCustosCalcularCustoDaSolucao(&instancia,NULL,(DataDeEntregaComum) 36,&custo) != FALSO) {
        printf("[ERRO] Solucao NULL deveria falhar.\n");
        liberarInstancia(&instancia);

        return 1;
    }

    liberarInstancia(&instancia);

    printf("[OK] Solucao nula invalida no gerenciador de custos.\n");

    return 0;
}

static int testarDataDeEntregaZeroInvalida(void) {
    Instancia instancia;
    Solucao solucao;
    Custo custo;

    instancia = criarInstanciaVazia();
    solucao = criarSolucaoVazia();
    custo = 0;

    prepararInstanciaDeTeste(&instancia);
    prepararSolucao123(&solucao);

    if(gerenciadorDeCustosCalcularCustoDaSolucao(&instancia,&solucao,(DataDeEntregaComum) 0,&custo) != FALSO) {
        printf("[ERRO] Data de entrega comum zero deveria falhar.\n");
        liberarSolucao(&solucao);
        liberarInstancia(&instancia);

        return 1;
    }

    liberarSolucao(&solucao);
    liberarInstancia(&instancia);

    printf("[OK] Data de entrega zero invalida no gerenciador de custos.\n");

    return 0;
}

static int testarPonteiroDeCustoNuloInvalido(void) {
    Instancia instancia;
    Solucao solucao;

    instancia = criarInstanciaVazia();
    solucao = criarSolucaoVazia();

    prepararInstanciaDeTeste(&instancia);
    prepararSolucao123(&solucao);

    if(gerenciadorDeCustosCalcularCustoDaSolucao(&instancia,&solucao,(DataDeEntregaComum) 36,NULL) != FALSO) {
        printf("[ERRO] Ponteiro de custo NULL deveria falhar.\n");
        liberarSolucao(&solucao);
        liberarInstancia(&instancia);

        return 1;
    }

    liberarSolucao(&solucao);
    liberarInstancia(&instancia);

    printf("[OK] Ponteiro de custo nulo invalido no gerenciador de custos.\n");

    return 0;
}

static int testarSolucaoIncompletaInvalida(void) {
    Instancia instancia;
    Solucao solucao;
    Custo custo;

    instancia = criarInstanciaVazia();
    solucao = criarSolucaoVazia();
    custo = 0;

    prepararInstanciaDeTeste(&instancia);

    inicializarSolucao(&solucao,(QuantidadeDeTarefas) 3);
    solucaoDefinirTarefaNaPosicao(&solucao,(QuantidadeDeTarefas) 0,(IdentificadorDeTarefa) 1);
    solucaoDefinirTarefaNaPosicao(&solucao,(QuantidadeDeTarefas) 1,(IdentificadorDeTarefa) 2);

    if(gerenciadorDeCustosCalcularCustoDaSolucao(&instancia,&solucao,(DataDeEntregaComum) 36,&custo) != FALSO) {
        printf("[ERRO] Solucao incompleta deveria falhar.\n");
        liberarSolucao(&solucao);
        liberarInstancia(&instancia);

        return 1;
    }

    liberarSolucao(&solucao);
    liberarInstancia(&instancia);

    printf("[OK] Solucao incompleta invalida no gerenciador de custos.\n");

    return 0;
}

int main(void) {
    int quantidadeDeErros;

    quantidadeDeErros = 0;

    printf("Executando testes do GerenciadorDeCustos...\n\n");

    quantidadeDeErros += testarCalculoDeCustoDaSolucao123();
    quantidadeDeErros += testarCalculoDeCustoDaSolucao321();
    quantidadeDeErros += testarCustoZeroQuandoTodasConcluemEmD();
    quantidadeDeErros += testarInstanciaNulaInvalida();
    quantidadeDeErros += testarSolucaoNulaInvalida();
    quantidadeDeErros += testarDataDeEntregaZeroInvalida();
    quantidadeDeErros += testarPonteiroDeCustoNuloInvalido();
    quantidadeDeErros += testarSolucaoIncompletaInvalida();

    printf("\n");

    if(quantidadeDeErros == 0) {
        printf("Todos os testes do GerenciadorDeCustos passaram.\n");

        return 0;
    }

    printf("Quantidade de erros nos testes do GerenciadorDeCustos: %d\n",quantidadeDeErros);

    return 1;
}