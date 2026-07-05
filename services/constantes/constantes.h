#ifndef CONSTANTES_H
#define CONSTANTES_H

#include <stdint.h>

typedef uint8_t Boolean;

typedef uint8_t InteiroPositivoDe8Bits;
typedef uint16_t InteiroPositivoDe16Bits;
typedef uint32_t InteiroPositivoDe32Bits;
typedef uint64_t InteiroPositivoDe64Bits;

typedef int8_t InteiroComSinalDe8Bits;
typedef int16_t InteiroComSinalDe16Bits;
typedef int32_t InteiroComSinalDe32Bits;
typedef int64_t InteiroComSinalDe64Bits;

typedef InteiroPositivoDe16Bits IdentificadorDeTarefa;
typedef InteiroPositivoDe16Bits IdentificadorDeHeuristica;
typedef InteiroPositivoDe16Bits IdentificadorDeExperimento;
typedef InteiroPositivoDe16Bits IdentificadorDeExecucao;
typedef InteiroPositivoDe16Bits QuantidadeDeTarefas;

typedef InteiroPositivoDe8Bits TempoDeProcessamento;
typedef InteiroPositivoDe8Bits Penalidade;
typedef InteiroPositivoDe8Bits FatorH;

typedef InteiroPositivoDe32Bits SomaDosTemposDeProcessamento;
typedef InteiroPositivoDe32Bits DataDeEntregaComum;
typedef InteiroPositivoDe64Bits Custo;

typedef double TempoComputacionalEmSegundos;
typedef double TempoComputacionalEmMilissegundos;

#define FALSO 0x00
#define VERDADEIRO 0x01

#define CODIGO_ERRO 0x00
#define CODIGO_SUCESSO 0x01

#define QUANTIDADE_DE_ARQUIVOS_DE_INSTANCIA 7
#define QUANTIDADE_DE_PROBLEMAS_POR_ARQUIVO 10
#define QUANTIDADE_DE_VALORES_DE_H 4
#define QUANTIDADE_TOTAL_DE_EXECUCOES 280

#define FATOR_H_02 2
#define FATOR_H_04 4
#define FATOR_H_06 6
#define FATOR_H_08 8
#define FATOR_DE_ESCALA_H 10

#define MILISSEGUNDOS_POR_SEGUNDO 1000.0

#define TAMANHO_MAXIMO_DE_LINHA 256
#define TAMANHO_MAXIMO_DE_CAMINHO 512
#define TAMANHO_MAXIMO_DE_NOME_DE_ARQUIVO 128
#define TAMANHO_MAXIMO_DE_NOME_DE_HEURISTICA 128
#define TAMANHO_MAXIMO_DE_DESCRICAO_DE_HEURISTICA 512
#define TAMANHO_MAXIMO_DE_NOME_DE_EXPERIMENTO 128
#define TAMANHO_MAXIMO_DE_DESCRICAO_DE_EXPERIMENTO 512

#define CAMINHO_DA_PASTA_DE_INSTANCIAS "instancias"
#define CAMINHO_DA_PASTA_DE_RESULTADOS "resultados"

#define NOME_ARQUIVO_SCH10 "sch10.txt"
#define NOME_ARQUIVO_SCH20 "sch20.txt"
#define NOME_ARQUIVO_SCH50 "sch50.txt"
#define NOME_ARQUIVO_SCH100 "sch100.txt"
#define NOME_ARQUIVO_SCH200 "sch200.txt"
#define NOME_ARQUIVO_SCH500 "sch500.txt"
#define NOME_ARQUIVO_SCH1000 "sch1000.txt"

#define IDENTIFICADOR_HEURISTICA_CONSTRUTIVA_FUZZY 1
#define NOME_HEURISTICA_CONSTRUTIVA_FUZZY "Heuristica Construtiva Fuzzy de Dupla Frente Temporal"
#define DESCRICAO_HEURISTICA_CONSTRUTIVA_FUZZY "Heuristica construtiva baseada em logica nebulosa para construir uma sequencia de tarefas considerando adiantamento, atraso e data comum de entrega."

#define IDENTIFICADOR_EXPERIMENTO_PADRAO 1
#define NOME_EXPERIMENTO_PADRAO "Experimento Principal"
#define DESCRICAO_EXPERIMENTO_PADRAO "Experimento com sete arquivos de instancias da OR-Library, dez problemas por arquivo e quatro valores de h."

#endif