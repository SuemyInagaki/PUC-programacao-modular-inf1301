/***************************************************************************
*
*  $MCI Modulo de implementacao: PEC Implementacao Dado
*
*  Arquivo gerado:              PECA.C
*  Letras identificadoras:      PEC
*
*  Nome da base de software:    Exemplo de teste automatizado
*
*  Projeto: INF 1301
*  Autor: jfr     Júlia Affonso Figueiredo Rocha

*
*  $HA Historico de evolucao:
*     Versao   Autor    Data       Observacoes
*       1.00   jfr   01/05/2019 Inicio do desenvolvimento
*
*  $ED Descricao do modulo
*     O módulo implementa as funcoes do dado para obter o resultado de um dado lancado.
*
***************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define DADO_OWN
#include "DADO.h"
#undef DADO_OWN

/***************************************************************************

/*****  Codigo das funcoes exportadas pelo modulo  *****/

/***************************************************************************
*
*  Funcao: DAD  Jogar o dado (gera numero randomico de 1 a 6)
*  ****/

DAD_tpCondRet DAD_Jogar(int *Numero) {
    srand((unsigned) time(NULL));
    *Numero = (rand() % 6) + 1;
	return DAD_CondRetOK;
}

/*********** Fim do modulo de implementacao: Modulo Dado **************/
