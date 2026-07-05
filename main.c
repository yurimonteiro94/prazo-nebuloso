#include "controller/controller_experimento/controller_experimento.h"
#include "model/entidades/experimento/experimento.h"
#include "services/constantes/constantes.h"
#include "services/ferramentas/ferramentas.h"
#include "view/view_console/view_console.h"

int main(void) {
    Experimento experimento;
    char caminhoArquivoResultadosDeExecucoes[TAMANHO_MAXIMO_DE_CAMINHO];
    char caminhoArquivoMediasPorNH[TAMANHO_MAXIMO_DE_CAMINHO];

    viewConsoleExibirCabecalho();

    experimento = criarExperimentoPadrao();

    if(experimentoEhValido(&experimento) == FALSO) {
        viewConsoleExibirErro("Experimento padrao invalido.");

        return 1;
    }

    if(montarCaminhoComArquivo(caminhoArquivoResultadosDeExecucoes,(InteiroPositivoDe32Bits) TAMANHO_MAXIMO_DE_CAMINHO,CAMINHO_DA_PASTA_DE_RESULTADOS,NOME_ARQUIVO_RESULTADOS_EXECUCOES) == FALSO) {
        viewConsoleExibirErro("Nao foi possivel montar o caminho do arquivo de resultados de execucoes.");

        return 1;
    }

    if(montarCaminhoComArquivo(caminhoArquivoMediasPorNH,(InteiroPositivoDe32Bits) TAMANHO_MAXIMO_DE_CAMINHO,CAMINHO_DA_PASTA_DE_RESULTADOS,NOME_ARQUIVO_MEDIAS_POR_N_H) == FALSO) {
        viewConsoleExibirErro("Nao foi possivel montar o caminho do arquivo de medias por n e h.");

        return 1;
    }

    viewConsoleExibirInicioDoExperimento();

    if(controllerExperimentoExecutarExperimento(&experimento,caminhoArquivoResultadosDeExecucoes,caminhoArquivoMediasPorNH) == FALSO) {
        viewConsoleExibirFalhaDoExperimento();

        return 1;
    }

    viewConsoleExibirFimDoExperimento(caminhoArquivoResultadosDeExecucoes,caminhoArquivoMediasPorNH);

    return 0;
}