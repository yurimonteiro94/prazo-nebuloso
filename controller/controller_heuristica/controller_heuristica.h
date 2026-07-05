#ifndef CONTROLLER_HEURISTICA_H
#define CONTROLLER_HEURISTICA_H

#include "../../services/constantes/constantes.h"
#include "../../model/entidades/heuristica/heuristica.h"
#include "../../model/entidades/instancia/instancia.h"
#include "../../model/entidades/solucao/solucao.h"

Boolean controllerHeuristicaConstruirSolucao(const Instancia *instancia,const Heuristica *heuristica,FatorH fatorH,Solucao *solucao);

#endif