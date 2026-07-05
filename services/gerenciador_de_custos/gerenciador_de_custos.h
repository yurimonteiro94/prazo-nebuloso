#ifndef GERENCIADOR_DE_CUSTOS_H
#define GERENCIADOR_DE_CUSTOS_H

#include "../constantes/constantes.h"
#include "../../model/entidades/instancia/instancia.h"
#include "../../model/entidades/solucao/solucao.h"

Boolean gerenciadorDeCustosCalcularCustoDaSolucao(const Instancia *instancia,const Solucao *solucao,DataDeEntregaComum dataDeEntregaComum,Custo *custo);

#endif