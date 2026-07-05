#include "controller_heuristica.h"

#include "../../services/gerenciador_fuzzy/gerenciador_fuzzy.h"

#include <stddef.h>
#include <stdlib.h>

#define LADO_DA_CONSTRUCAO_NENHUM 0
#define LADO_DA_CONSTRUCAO_ANTES_DA_DATA 1
#define LADO_DA_CONSTRUCAO_DEPOIS_DA_DATA 2

static void liberarVetoresDaConstrucao(Boolean *tarefasAlocadas,IdentificadorDeTarefa *sequenciaAntesDaData,IdentificadorDeTarefa *sequenciaDepoisDaData) {
    if(tarefasAlocadas != NULL) {
        free(tarefasAlocadas);
    }

    if(sequenciaAntesDaData != NULL) {
        free(sequenciaAntesDaData);
    }

    if(sequenciaDepoisDaData != NULL) {
        free(sequenciaDepoisDaData);
    }
}

static Boolean inicializarVetoresDaConstrucao(QuantidadeDeTarefas quantidadeDeTarefas,Boolean **tarefasAlocadas,IdentificadorDeTarefa **sequenciaAntesDaData,IdentificadorDeTarefa **sequenciaDepoisDaData) {
    QuantidadeDeTarefas indice;

    if(quantidadeDeTarefas == 0) {
        return FALSO;
    }

    else if(tarefasAlocadas == NULL) {
        return FALSO;
    }

    else if(sequenciaAntesDaData == NULL) {
        return FALSO;
    }

    else if(sequenciaDepoisDaData == NULL) {
        return FALSO;
    }

    (*tarefasAlocadas) = NULL;
    (*sequenciaAntesDaData) = NULL;
    (*sequenciaDepoisDaData) = NULL;

    (*tarefasAlocadas) = (Boolean *) malloc(sizeof(Boolean) * quantidadeDeTarefas);
    (*sequenciaAntesDaData) = (IdentificadorDeTarefa *) malloc(sizeof(IdentificadorDeTarefa) * quantidadeDeTarefas);
    (*sequenciaDepoisDaData) = (IdentificadorDeTarefa *) malloc(sizeof(IdentificadorDeTarefa) * quantidadeDeTarefas);

    if((*tarefasAlocadas) == NULL) {
        liberarVetoresDaConstrucao((*tarefasAlocadas),(*sequenciaAntesDaData),(*sequenciaDepoisDaData));

        return FALSO;
    }

    else if((*sequenciaAntesDaData) == NULL) {
        liberarVetoresDaConstrucao((*tarefasAlocadas),(*sequenciaAntesDaData),(*sequenciaDepoisDaData));

        return FALSO;
    }

    else if((*sequenciaDepoisDaData) == NULL) {
        liberarVetoresDaConstrucao((*tarefasAlocadas),(*sequenciaAntesDaData),(*sequenciaDepoisDaData));

        return FALSO;
    }

    for(indice = 0; indice < quantidadeDeTarefas; indice++) {
        (*tarefasAlocadas)[indice] = FALSO;
        (*sequenciaAntesDaData)[indice] = 0;
        (*sequenciaDepoisDaData)[indice] = 0;
    }

    return VERDADEIRO;
}

static Boolean heuristicaEhAceitaPeloController(const Heuristica *heuristica) {
    if(heuristicaEhValida(heuristica) == FALSO) {
        return FALSO;
    }

    else if((*heuristica).identificadorDaHeuristica != IDENTIFICADOR_HEURISTICA_CONSTRUTIVA_FUZZY) {
        return FALSO;
    }

    return VERDADEIRO;
}

static Boolean escolherProximaTarefa(const Instancia *instancia,Boolean *tarefasAlocadas,DataDeEntregaComum dataDeEntregaComum,SomaDosTemposDeProcessamento tempoJaAlocadoAntesDaData,QuantidadeDeTarefas *indiceDaTarefaEscolhida,InteiroPositivoDe8Bits *ladoEscolhido) {
    QuantidadeDeTarefas indiceDaTarefa;
    double prioridadeAntesDaData;
    double prioridadeDepoisDaData;
    double melhorPrioridade;
    Boolean existeTarefaEscolhida;
    const Tarefa *tarefa;

    if(instancia == NULL) {
        return FALSO;
    }

    else if(tarefasAlocadas == NULL) {
        return FALSO;
    }

    else if(indiceDaTarefaEscolhida == NULL) {
        return FALSO;
    }

    else if(ladoEscolhido == NULL) {
        return FALSO;
    }

    melhorPrioridade = -1.0;
    existeTarefaEscolhida = FALSO;
    (*indiceDaTarefaEscolhida) = 0;
    (*ladoEscolhido) = LADO_DA_CONSTRUCAO_NENHUM;

    for(indiceDaTarefa = 0; indiceDaTarefa < (*instancia).quantidadeDeTarefas; indiceDaTarefa++) {
        if(tarefasAlocadas[indiceDaTarefa] == VERDADEIRO) {
            continue;
        }

        tarefa = &(*instancia).tarefas[indiceDaTarefa];

        if((tempoJaAlocadoAntesDaData + (*tarefa).tempoProcessamento) <= dataDeEntregaComum) {
            if(gerenciadorFuzzyCalcularPrioridadeAntesDaDataDeEntrega(tarefa,dataDeEntregaComum,tempoJaAlocadoAntesDaData,&prioridadeAntesDaData) == FALSO) {
                return FALSO;
            }

            if(prioridadeAntesDaData > melhorPrioridade) {
                melhorPrioridade = prioridadeAntesDaData;
                existeTarefaEscolhida = VERDADEIRO;
                (*indiceDaTarefaEscolhida) = indiceDaTarefa;
                (*ladoEscolhido) = LADO_DA_CONSTRUCAO_ANTES_DA_DATA;
            }
        }

        if(gerenciadorFuzzyCalcularPrioridadeDepoisDaDataDeEntrega(tarefa,&prioridadeDepoisDaData) == FALSO) {
            return FALSO;
        }

        if(prioridadeDepoisDaData > melhorPrioridade) {
            melhorPrioridade = prioridadeDepoisDaData;
            existeTarefaEscolhida = VERDADEIRO;
            (*indiceDaTarefaEscolhida) = indiceDaTarefa;
            (*ladoEscolhido) = LADO_DA_CONSTRUCAO_DEPOIS_DA_DATA;
        }
    }

    return existeTarefaEscolhida;
}

static Boolean preencherSolucaoComSequencias(Solucao *solucao,QuantidadeDeTarefas quantidadeDeTarefas,const IdentificadorDeTarefa *sequenciaAntesDaData,QuantidadeDeTarefas quantidadeAntesDaData,const IdentificadorDeTarefa *sequenciaDepoisDaData,QuantidadeDeTarefas quantidadeDepoisDaData) {
    QuantidadeDeTarefas indice;
    QuantidadeDeTarefas posicaoDaSolucao;

    if(solucao == NULL) {
        return FALSO;
    }

    else if(sequenciaAntesDaData == NULL) {
        return FALSO;
    }

    else if(sequenciaDepoisDaData == NULL) {
        return FALSO;
    }

    if(inicializarSolucao(solucao,quantidadeDeTarefas) == FALSO) {
        return FALSO;
    }

    posicaoDaSolucao = 0;

    for(indice = 0; indice < quantidadeAntesDaData; indice++) {
        if(solucaoDefinirTarefaNaPosicao(solucao,posicaoDaSolucao,sequenciaAntesDaData[indice]) == FALSO) {
            liberarSolucao(solucao);

            return FALSO;
        }

        posicaoDaSolucao++;
    }

    for(indice = 0; indice < quantidadeDepoisDaData; indice++) {
        if(solucaoDefinirTarefaNaPosicao(solucao,posicaoDaSolucao,sequenciaDepoisDaData[indice]) == FALSO) {
            liberarSolucao(solucao);

            return FALSO;
        }

        posicaoDaSolucao++;
    }

    if(solucaoEhValida(solucao) == FALSO) {
        liberarSolucao(solucao);

        return FALSO;
    }

    return VERDADEIRO;
}

Boolean controllerHeuristicaConstruirSolucao(const Instancia *instancia,const Heuristica *heuristica,FatorH fatorH,Solucao *solucao) {
    Boolean *tarefasAlocadas;
    IdentificadorDeTarefa *sequenciaAntesDaData;
    IdentificadorDeTarefa *sequenciaDepoisDaData;

    QuantidadeDeTarefas quantidadeDeTarefasAlocadas;
    QuantidadeDeTarefas quantidadeAntesDaData;
    QuantidadeDeTarefas quantidadeDepoisDaData;
    QuantidadeDeTarefas indiceDaTarefaEscolhida;

    InteiroPositivoDe8Bits ladoEscolhido;
    DataDeEntregaComum dataDeEntregaComum;
    SomaDosTemposDeProcessamento tempoJaAlocadoAntesDaData;

    const Tarefa *tarefaEscolhida;

    if(instanciaEhValida(instancia) == FALSO) {
        return FALSO;
    }

    else if(heuristicaEhAceitaPeloController(heuristica) == FALSO) {
        return FALSO;
    }

    else if(solucao == NULL) {
        return FALSO;
    }

    dataDeEntregaComum = instanciaCalcularDataDeEntregaComum(instancia,fatorH);

    if(dataDeEntregaComum == 0) {
        return FALSO;
    }

    tarefasAlocadas = NULL;
    sequenciaAntesDaData = NULL;
    sequenciaDepoisDaData = NULL;

    if(inicializarVetoresDaConstrucao((*instancia).quantidadeDeTarefas,&tarefasAlocadas,&sequenciaAntesDaData,&sequenciaDepoisDaData) == FALSO) {
        return FALSO;
    }

    quantidadeDeTarefasAlocadas = 0;
    quantidadeAntesDaData = 0;
    quantidadeDepoisDaData = 0;
    tempoJaAlocadoAntesDaData = 0;

    while(quantidadeDeTarefasAlocadas < (*instancia).quantidadeDeTarefas) {
        if(escolherProximaTarefa(instancia,tarefasAlocadas,dataDeEntregaComum,tempoJaAlocadoAntesDaData,&indiceDaTarefaEscolhida,&ladoEscolhido) == FALSO) {
            liberarVetoresDaConstrucao(tarefasAlocadas,sequenciaAntesDaData,sequenciaDepoisDaData);

            return FALSO;
        }

        tarefaEscolhida = &(*instancia).tarefas[indiceDaTarefaEscolhida];
        tarefasAlocadas[indiceDaTarefaEscolhida] = VERDADEIRO;

        if(ladoEscolhido == LADO_DA_CONSTRUCAO_ANTES_DA_DATA) {
            sequenciaAntesDaData[quantidadeAntesDaData] = (*tarefaEscolhida).identificador;
            quantidadeAntesDaData++;
            tempoJaAlocadoAntesDaData += (*tarefaEscolhida).tempoProcessamento;
        }

        else if(ladoEscolhido == LADO_DA_CONSTRUCAO_DEPOIS_DA_DATA) {
            sequenciaDepoisDaData[quantidadeDepoisDaData] = (*tarefaEscolhida).identificador;
            quantidadeDepoisDaData++;
        }

        else {
            liberarVetoresDaConstrucao(tarefasAlocadas,sequenciaAntesDaData,sequenciaDepoisDaData);

            return FALSO;
        }

        quantidadeDeTarefasAlocadas++;
    }

    if(preencherSolucaoComSequencias(solucao,(*instancia).quantidadeDeTarefas,sequenciaAntesDaData,quantidadeAntesDaData,sequenciaDepoisDaData,quantidadeDepoisDaData) == FALSO) {
        liberarVetoresDaConstrucao(tarefasAlocadas,sequenciaAntesDaData,sequenciaDepoisDaData);

        return FALSO;
    }

    liberarVetoresDaConstrucao(tarefasAlocadas,sequenciaAntesDaData,sequenciaDepoisDaData);

    return VERDADEIRO;
}