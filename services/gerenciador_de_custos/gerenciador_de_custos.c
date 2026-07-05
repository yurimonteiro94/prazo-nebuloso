#include "gerenciador_de_custos.h"

#include <stddef.h>

static const Tarefa *gerenciadorDeCustosBuscarTarefaPorIdentificador(const Instancia *instancia,IdentificadorDeTarefa identificadorDaTarefa) {
    QuantidadeDeTarefas indiceDaTarefa;

    if(instancia == NULL) {
        return NULL;
    }

    else if((*instancia).tarefas == NULL) {
        return NULL;
    }

    else if(identificadorDaTarefa == 0) {
        return NULL;
    }

    for(indiceDaTarefa = 0; indiceDaTarefa < (*instancia).quantidadeDeTarefas; indiceDaTarefa++) {
        if((*instancia).tarefas[indiceDaTarefa].identificador == identificadorDaTarefa) {
            return &(*instancia).tarefas[indiceDaTarefa];
        }
    }

    return NULL;
}

Boolean gerenciadorDeCustosCalcularCustoDaSolucao(const Instancia *instancia,const Solucao *solucao,DataDeEntregaComum dataDeEntregaComum,Custo *custo) {
    QuantidadeDeTarefas posicaoDaSolucao;
    IdentificadorDeTarefa identificadorDaTarefa;
    const Tarefa *tarefa;
    DataDeEntregaComum tempoDeConclusao;
    DataDeEntregaComum adiantamento;
    DataDeEntregaComum atraso;
    Custo custoCalculado;

    if(instanciaEhValida(instancia) == FALSO) {
        return FALSO;
    }

    else if(solucaoEhValida(solucao) == FALSO) {
        return FALSO;
    }

    else if(dataDeEntregaComum == 0) {
        return FALSO;
    }

    else if(custo == NULL) {
        return FALSO;
    }

    tempoDeConclusao = 0;
    custoCalculado = 0;

    for(posicaoDaSolucao = 0; posicaoDaSolucao < (*solucao).quantidadeDeTarefas; posicaoDaSolucao++) {
        identificadorDaTarefa = (*solucao).sequenciaDeTarefas[posicaoDaSolucao];

        tarefa = gerenciadorDeCustosBuscarTarefaPorIdentificador(instancia,identificadorDaTarefa);

        if(tarefa == NULL) {
            return FALSO;
        }

        tempoDeConclusao += (*tarefa).tempoProcessamento;

        if(tempoDeConclusao < dataDeEntregaComum) {
            adiantamento = dataDeEntregaComum - tempoDeConclusao;
            atraso = 0;
        }

        else if(tempoDeConclusao > dataDeEntregaComum) {
            adiantamento = 0;
            atraso = tempoDeConclusao - dataDeEntregaComum;
        }

        else {
            adiantamento = 0;
            atraso = 0;
        }

        custoCalculado += ((Custo) (*tarefa).penalidadeAdiantamento * (Custo) adiantamento);
        custoCalculado += ((Custo) (*tarefa).penalidadeAtraso * (Custo) atraso);
    }

    (*custo) = custoCalculado;

    return VERDADEIRO;
}