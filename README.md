# Prazo Nebuloso

Projeto em C puro para estudo de heuristicas construtivas aplicadas ao problema de sequenciamento de tarefas em uma unica maquina com data comum de entrega.

A proposta principal e uma heuristica construtiva baseada em logica nebulosa.

## Organizacao

- model: camada de dados do projeto.
- model/entidades: entidades principais do problema.
- model/dao: acesso aos dados das instancias e resultados.
- services: modulos auxiliares com funcoes de proposito geral.
- controller: coordenacao dos experimentos e da heuristica.
- view: exibicao de mensagens no console.

## Entidades

- Tarefa.
- Instancia.
- Solucao.
- Heuristica.
- Experimento.
- ResultadoDeExecucao.

## Services

- constantes.
- ferramentas.
- gerenciador_de_arquivos.
- gerenciador_fuzzy.
- gerenciador_de_custos.
- gerenciador_de_tempo.

