# Prazo Nebuloso

Projeto desenvolvido para a disciplina PRO5826 - Estudo de Meta-heurísticas para Problemas de Produção.

O projeto implementa uma heurística construtiva em C para o problema de sequenciamento em máquina única com data comum de entrega, penalidades por adiantamento e penalidades por atraso.

## Problema tratado

Cada tarefa possui tempo de processamento, penalidade por adiantamento e penalidade por atraso.

Todas as tarefas compartilham uma mesma data comum de entrega.

Para cada tarefa i:

p_i = tempo de processamento  
alpha_i = penalidade por adiantamento  
beta_i = penalidade por atraso  
C_i = tempo de conclusão  
d = data comum de entrega  

O adiantamento e o atraso são:

E_i = max(d - C_i, 0)  
T_i = max(C_i - d, 0)  

A função objetivo é minimizar:

sum(alpha_i * E_i + beta_i * T_i)

## Instâncias

Foram utilizadas instâncias da OR-Library:

sch10.txt  
sch20.txt  
sch50.txt  
sch100.txt  
sch200.txt  
sch500.txt  
sch1000.txt  

Cada arquivo possui 10 instâncias.

Foram testados quatro valores de h:

h = 0.2  
h = 0.4  
h = 0.6  
h = 0.8  

A data comum de entrega é calculada por:

d = floor(h * somaDosTemposDeProcessamento)

Total de execuções:

7 arquivos * 10 instâncias * 4 valores de h = 280 execuções

## Heurística final

A versão final utiliza a Heurística Construtiva por Arbitragem Temporal Preditiva.

A heurística trata a máquina única como um recurso disputado por várias tarefas. Ela gera múltiplas sequências candidatas por regras diferentes, avalia todas pela função objetivo e seleciona a melhor sequência encontrada.

A versão final avalia 62 sequências candidatas por execução:

56 sequências particionadas  
6 sequências diretas  

## Deslocamento temporal

Após construir uma sequência, o algoritmo também escolhe o melhor instante inicial da programação.

Isso evita avaliar toda sequência como se ela começasse obrigatoriamente no instante zero. Esse ajuste melhora principalmente os casos com h = 0.6 e h = 0.8.

## Resultados finais

Resumo dos custos médios finais:

| n | h=0.2 | h=0.4 | h=0.6 | h=0.8 |
|---:|---:|---:|---:|---:|
| 10 | 1677.800 | 977.700 | 736.400 | 734.900 |
| 20 | 6203.100 | 3643.600 | 2837.200 | 2779.600 |
| 50 | 35644.900 | 20626.800 | 16066.400 | 16015.700 |
| 100 | 132639.500 | 78600.600 | 65415.800 | 65478.500 |
| 200 | 513112.100 | 305182.700 | 258243.200 | 258321.100 |
| 500 | 3135121.600 | 1858846.200 | 1595134.100 | 1600510.300 |
| 1000 | 12403213.500 | 7353987.300 | 6237376.100 | 6257017.400 |

Para as instâncias com 1000 tarefas, o tempo médio ficou abaixo de 0,1 segundo por execução.

## Arquivos de resultado

Ao executar o programa, são gerados:

resultados/resultados_execucoes.csv  
resultados/medias_por_n_h.csv  
resultados/comparacao_benchmark.csv  

## Compilação

Comando usado para compilar:

gcc -std=c17 -Wall -Wextra -Wpedantic -O2 main.c view\view_console\view_console.c controller\controller_benchmark\controller_benchmark.c controller\controller_experimento\controller_experimento.c controller\controller_heuristica\controller_heuristica.c model\dao\instancia_dao\instancia_dao.c model\dao\resultado_dao\resultado_dao.c model\entidades\experimento\experimento.c model\entidades\heuristica\heuristica.c model\entidades\instancia\instancia.c model\entidades\resultado_de_execucao\resultado_de_execucao.c model\entidades\solucao\solucao.c model\entidades\tarefa\tarefa.c services\ferramentas\ferramentas.c services\gerenciador_de_arquivos\gerenciador_de_arquivos.c services\gerenciador_de_custos\gerenciador_de_custos.c services\gerenciador_de_tempo\gerenciador_de_tempo.c services\gerenciador_fuzzy\gerenciador_fuzzy.c -o prazo_nebuloso.exe

## Execução

prazo_nebuloso.exe

## Conclusão

A heurística final combina construção determinística, múltiplas sequências candidatas, avaliação pela função objetivo e ajuste otimizado do instante inicial.

A abordagem gerou soluções de boa qualidade com baixo tempo computacional, mantendo o experimento completo viável.