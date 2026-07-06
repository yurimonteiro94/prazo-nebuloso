#include "gerenciador_de_custos.h"

#include <stddef.h>

static Boolean gerenciadorDeCustosParametrosSaoValidos(const Instancia *instancia,const Solucao *solucao) {
    if(instancia == NULL) {
        return FALSO;
    }

    if(solucao == NULL) {
        return FALSO;
    }

    if((*instancia).tarefas == NULL) {
        return FALSO;
    }

    if((*solucao).sequenciaDeTarefas == NULL) {
        return FALSO;
    }

    if((*instancia).quantidadeDeTarefas == 0) {
        return FALSO;
    }

    if((*solucao).quantidadeDeTarefasAlocadas == 0) {
        return FALSO;
    }

    if((*solucao).quantidadeDeTarefasAlocadas != (*instancia).quantidadeDeTarefas) {
        return FALSO;
    }

    return VERDADEIRO;
}

static const Tarefa *gerenciadorDeCustosBuscarTarefaPorIdentificador(const Instancia *instancia,IdentificadorDeTarefa identificadorDaTarefa) {
    QuantidadeDeTarefas indiceDaTarefa;

    if(instancia == NULL) {
        return NULL;
    }

    if((*instancia).tarefas == NULL) {
        return NULL;
    }

    for(indiceDaTarefa = 0;indiceDaTarefa < (*instancia).quantidadeDeTarefas;indiceDaTarefa++) {
        if((*instancia).tarefas[indiceDaTarefa].identificador == identificadorDaTarefa) {
            return &((*instancia).tarefas[indiceDaTarefa]);
        }
    }

    return NULL;
}

Boolean gerenciadorDeCustosCalcularCustoDaSolucaoComInstanteInicial(const Instancia *instancia,const Solucao *solucao,DataDeEntregaComum dataDeEntregaComum,InteiroPositivoDe32Bits instanteInicial,Custo *custo) {
    QuantidadeDeTarefas indiceDaSequencia;
    IdentificadorDeTarefa identificadorDaTarefa;
    const Tarefa *tarefa;
    InteiroPositivoDe32Bits instanteAtual;
    InteiroPositivoDe32Bits adiantamento;
    InteiroPositivoDe32Bits atraso;
    Custo custoTotal;

    if(custo == NULL) {
        return FALSO;
    }

    (*custo) = 0;

    if(gerenciadorDeCustosParametrosSaoValidos(instancia,solucao) == FALSO) {
        return FALSO;
    }

    instanteAtual = instanteInicial;
    custoTotal = 0;

    for(indiceDaSequencia = 0;indiceDaSequencia < (*solucao).quantidadeDeTarefasAlocadas;indiceDaSequencia++) {
        identificadorDaTarefa = (*solucao).sequenciaDeTarefas[indiceDaSequencia];
        tarefa = gerenciadorDeCustosBuscarTarefaPorIdentificador(instancia,identificadorDaTarefa);

        if(tarefa == NULL) {
            return FALSO;
        }

        instanteAtual += (*tarefa).tempoProcessamento;

        if(instanteAtual < dataDeEntregaComum) {
            adiantamento = dataDeEntregaComum - instanteAtual;
            custoTotal += ((Custo) (*tarefa).penalidadeAdiantamento) * ((Custo) adiantamento);
        }

        if(instanteAtual > dataDeEntregaComum) {
            atraso = instanteAtual - dataDeEntregaComum;
            custoTotal += ((Custo) (*tarefa).penalidadeAtraso) * ((Custo) atraso);
        }
    }

    (*custo) = custoTotal;

    return VERDADEIRO;
}

Boolean gerenciadorDeCustosEncontrarMelhorInstanteInicialDaSolucao(const Instancia *instancia,const Solucao *solucao,DataDeEntregaComum dataDeEntregaComum,InteiroPositivoDe32Bits *melhorInstanteInicial) {
    InteiroPositivoDe32Bits instanteInicial;
    InteiroPositivoDe32Bits melhorInstanteInicialAtual;
    Custo custoAtual;
    Custo melhorCusto;

    if(melhorInstanteInicial == NULL) {
        return FALSO;
    }

    (*melhorInstanteInicial) = 0;

    if(gerenciadorDeCustosParametrosSaoValidos(instancia,solucao) == FALSO) {
        return FALSO;
    }

    melhorInstanteInicialAtual = 0;

    if(gerenciadorDeCustosCalcularCustoDaSolucaoComInstanteInicial(instancia,solucao,dataDeEntregaComum,0,&melhorCusto) == FALSO) {
        return FALSO;
    }

    for(instanteInicial = 1;instanteInicial <= dataDeEntregaComum;instanteInicial++) {
        if(gerenciadorDeCustosCalcularCustoDaSolucaoComInstanteInicial(instancia,solucao,dataDeEntregaComum,instanteInicial,&custoAtual) == FALSO) {
            return FALSO;
        }

        if(custoAtual < melhorCusto) {
            melhorCusto = custoAtual;
            melhorInstanteInicialAtual = instanteInicial;
        }
    }

    (*melhorInstanteInicial) = melhorInstanteInicialAtual;

    return VERDADEIRO;
}

Boolean gerenciadorDeCustosCalcularCustoDaSolucao(const Instancia *instancia,const Solucao *solucao,DataDeEntregaComum dataDeEntregaComum,Custo *custo) {
    InteiroPositivoDe32Bits melhorInstanteInicial;

    if(custo == NULL) {
        return FALSO;
    }

    (*custo) = 0;

    if(gerenciadorDeCustosParametrosSaoValidos(instancia,solucao) == FALSO) {
        return FALSO;
    }

    if(gerenciadorDeCustosEncontrarMelhorInstanteInicialDaSolucao(instancia,solucao,dataDeEntregaComum,&melhorInstanteInicial) == FALSO) {
        return FALSO;
    }

    return gerenciadorDeCustosCalcularCustoDaSolucaoComInstanteInicial(instancia,solucao,dataDeEntregaComum,melhorInstanteInicial,custo);
}