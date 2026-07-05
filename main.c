#include <stdio.h>

#include "model/entidades/tarefa/tarefa.h"

int main(void) {
    Tarefa tarefa;
    Boolean tarefaValida;

    tarefa = criarTarefa(
        (IdentificadorDeTarefa) 1,
        (TempoDeProcessamento) 20,
        (Penalidade) 4,
        (Penalidade) 5
    );

    tarefaValida = tarefaEhValida(&tarefa);

    if(tarefaValida == VERDADEIRO) {
        printf("Tarefa criada com sucesso.\n");
        printf("Identificador: %u\n",(unsigned int) tarefa.identificador);
        printf("Tempo de processamento: %u\n",(unsigned int) tarefa.tempoProcessamento);
        printf("Penalidade de adiantamento: %u\n",(unsigned int) tarefa.penalidadeAdiantamento);
        printf("Penalidade de atraso: %u\n",(unsigned int) tarefa.penalidadeAtraso);

        return 0;
    }

    printf("Erro ao validar a tarefa.\n");

    return 1;
}