/***************************************************************************
*
*  $MCI Modulo de implementacao: PEC Implementacao Peca
*
*  Arquivo gerado:              PECA.C
*  Letras identificadoras:      PEC
*
*  Nome da base de software:    Exemplo de teste automatizado
*
*  Projeto: INF 1301
*  Autor: jfr     Júlia Affonso Figueiredo Rocha
*	  sipf	  Suemy Inagaki Pinheio Fagundes
*
*  $HA Historico de evolucao:
*     Versao   Autor    Data       Observacoes
*       1.10   sipf  10/06/2019 Algumas correções 
*       1.00   jfr   01/05/2019 Inicio do desenvolvimento
*
*  $ED Descricao do modulo
*     O módulo implementa as funcoes de existencia e manutencao da Peca, bem como criacao, destrucao e consulta de cor.
*
***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <stdlib.h>

#define PECA_OWN
#include "PECA.h"
#undef PECA_OWN

/***********************************************************************
*
*  $ED Descricao do tipo
*		Descreve a estrutura de peca
***********************************************************************/

typedef struct tgPeca{

	PEC_CorDaPeca cor;

}tpPeca;

/***** Código das funcoes exportadas pelo modulo  *****/

/***************************************************************************
*
*  Funcao: PEC Criar Peca
*  ****/

PEC_tpCondRet PEC_CriarPeca(tppPeca* PECCriado, PEC_CorDaPeca CorDaNovaPeca) { 
	*PECCriado = (tppPeca)malloc(sizeof(tpPeca));

	if(PECCriado == NULL)
		return PEC_CondRetFaltouMemoria;

	(*PECCriado)->cor = CorDaNovaPeca;

	return PEC_CondRetOK;
}

/***************************************************************************
*
*  Funcao: PEC Destruir Peca
*  ****/

void PEC_DestruirPeca(tppPeca *Peca) { 
    if (*Peca == NULL) {
        return;
    } /* if */
    
	free(Peca);
    *Peca = NULL;
}

/***************************************************************************
*
*  Funcao: PEC Obter Cor
*  ****/

PEC_tpCondRet PEC_ObterCor(tppPeca Peca, char *cor) {
	if((Peca->cor != 'p') && (Peca->cor != 'v')) {
		printf("Erro ao obter a cor");
		return PEC_CondRetErro;
	}
	*cor = Peca->cor;
	return PEC_CondRetOK;
}

/*********** Fim do módulo de implementacao: Modulo Peca **************/
