#include <stdio.h>

#include "model/entidades/instancia/instancia.h"
#include "model/entidades/tarefa/tarefa.h"

int main(void) {
    Instancia instancia;
    Boolean instanciaFoiInicializada;
    Boolean tarefaFoiAdicionada;
    Boolean instanciaValida;
    DataDeEntregaComum dataDeEntregaComum;

    instancia = criarInstanciaVazia();

    instanciaFoiInicializada = inicializarInstancia(
        &instancia,
        NOME_ARQUIVO_SCH10,
        (InteiroPositivoDe16Bits) 1,
        (QuantidadeDeTarefas) 3
    );

    if(instanciaFoiInicializada == FALSO) {
        printf("Erro ao inicializar instancia.\n");

        return 1;
    }

    tarefaFoiAdicionada = instanciaAdicionarTarefa(
        &instancia,
        (QuantidadeDeTarefas) 0,
        criarTarefa(
            (IdentificadorDeTarefa) 1,
            (TempoDeProcessamento) 10,
            (Penalidade) 4,
            (Penalidade) 8
        )
    );

    if(tarefaFoiAdicionada == FALSO) {
        printf("Erro ao adicionar tarefa 1.\n");
        liberarInstancia(&instancia);

        return 1;
    }

    tarefaFoiAdicionada = instanciaAdicionarTarefa(
        &instancia,
        (QuantidadeDeTarefas) 1,
        criarTarefa(
            (IdentificadorDeTarefa) 2,
            (TempoDeProcessamento) 20,
            (Penalidade) 5,
            (Penalidade) 6
        )
    );

    if(tarefaFoiAdicionada == FALSO) {
        printf("Erro ao adicionar tarefa 2.\n");
        liberarInstancia(&instancia);

        return 1;
    }

    tarefaFoiAdicionada = instanciaAdicionarTarefa(
        &instancia,
        (QuantidadeDeTarefas) 2,
        criarTarefa(
            (IdentificadorDeTarefa) 3,
            (TempoDeProcessamento) 30,
            (Penalidade) 7,
            (Penalidade) 9
        )
    );

    if(tarefaFoiAdicionada == FALSO) {
        printf("Erro ao adicionar tarefa 3.\n");
        liberarInstancia(&instancia);

        return 1;
    }

    instanciaValida = instanciaEhValida(&instancia);

    if(instanciaValida == FALSO) {
        printf("Instancia invalida.\n");
        liberarInstancia(&instancia);

        return 1;
    }

    dataDeEntregaComum = instanciaCalcularDataDeEntregaComum(&instancia,FATOR_H_06);

    printf("Instancia criada com sucesso.\n");
    printf("Arquivo de origem: %s\n",instancia.nomeDoArquivoDeOrigem);
    printf("Identificador da instancia: %u\n",(unsigned int) instancia.identificadorDaInstancia);
    printf("Quantidade de tarefas: %u\n",(unsigned int) instancia.quantidadeDeTarefas);
    printf("Soma dos tempos de processamento: %u\n",(unsigned int) instancia.somaDosTemposDeProcessamento);
    printf("Data de entrega comum com h = 0.6: %u\n",(unsigned int) dataDeEntregaComum);

    liberarInstancia(&instancia);

    return 0;
}