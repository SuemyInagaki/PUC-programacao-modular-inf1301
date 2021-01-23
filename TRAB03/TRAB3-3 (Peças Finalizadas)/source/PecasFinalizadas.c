/*****************************************************************************************
*  $MCI Módulo de implementação: Módulo Pecas Finalizadas
*  Arquivo gerado:            PecasFinalizadas.c
*  Letras identificadoras:       PFZ
*
*  Projeto:               Disciplina INF 1301
*
*  Autor:                 sipf - Suemy Inagaki Pinheiro Fagundes
* 
*  $HA Histórico de evolução:
*  Versão  Autor    Data     Observações
*  1       sipf   09/jun/2019 início desenvolvimento
*
*       $ED Descrição do módulo
*       Define as Funções de PecasFinalizadas.
*       No início de cada partida não existe PecasFinalizadas
*
*****************************************************************************************/


#include   <malloc.h>
#include   <stdio.h>

#define PECASFINALIZADAS_OWN
#include "PecasFinalizadas.h"
#undef PECASFINALIZADAS_OWN

#include "PECA.h"

#include "LISTA.h"

/***********************************************************************
*
*  $TC Tipo de dados: PFZ Descritor da peça finalizada
*
*
***********************************************************************/

typedef struct PFZ_tagPecasFinalizadas {

	LIS_tppLista listaPecasVermelhas;
	/* Lista de peças Vermelhas finalizadas */

	LIS_tppLista listaPecasPretas;
	/* Lista de peças pretas finalizadas */

};

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: PFZ Criar lista de peças finalizadas
* 
***************************************************************************/
PFZ_tpCondRet PFZ_CriarListaPecasFinalizadas(PFZ_tpPecasFinalizadas *pPecasFinalizadas)
{

	*pPecasFinalizadas = (PFZ_tpPecasFinalizadas) malloc(sizeof(struct PFZ_tagPecasFinalizadas));//TIREI O * DE *pPecasFinalizadas = ...
	if(*pPecasFinalizadas == NULL)
		return PFZ_SemMemoria ;

	(*pPecasFinalizadas)->listaPecasVermelhas = LIS_CriarLista(PEC_DestruirPeca);
	(*pPecasFinalizadas)->listaPecasPretas = LIS_CriarLista(PEC_DestruirPeca);

	return PFZ_OK ;

} /* Fim função: PFZ Criar lista de peças finalizadas */

/***************************************************************************
*
*  Função: PFZ Inserir peça
*  
****************************************************************************/
PFZ_tpCondRet PFZ_InserirPeca(PFZ_tpPecasFinalizadas pPecasFinalizadas, tppPeca pPeca)
{
	PEC_CorDaPeca  CorPeca;

	if(pPecasFinalizadas == NULL) 
		return PFZ_NaoExisteLista;

	PEC_ObterCor(pPeca, &CorPeca);	
	
	if(CorPeca == PEC_corVermelha)
		LIS_InserirElementoAntes(pPecasFinalizadas->listaPecasVermelhas, pPeca);

	else
		LIS_InserirElementoAntes(pPecasFinalizadas->listaPecasPretas, pPeca);
	
	return PFZ_OK;

} /* Fim função: PFZ Inserir peça */

/***************************************************************************
*
*  Função: PFZ Conta peças
*  
***************************************************************************/

   PFZ_tpCondRet PFZ_ContarPecas(PFZ_tpPecasFinalizadas pPecasFinalizadas, PEC_CorDaPeca  CorPeca, int *pContagem)
{
	LIS_tppLista ListaPecas;

	if(pPecasFinalizadas == NULL) 
		return PFZ_NaoExisteLista;

	*pContagem = 0;

	if(CorPeca == PEC_corVermelha)
		ListaPecas = pPecasFinalizadas->listaPecasVermelhas;
	else 
		ListaPecas = pPecasFinalizadas->listaPecasPretas;

	IrInicioLista(ListaPecas);

	if(LIS_ObterValor(ListaPecas) != NULL)
		do
		{
			(*pContagem)++;
		} while(LIS_AvancarElementoCorrente(ListaPecas, 1) == LIS_CondRetOK);

	return PFZ_OK ;

} /* Fim função: PFZ Contar peças */

/***************************************************************************
*
*  Função: PFZ Destruir lista de peças finalizadas
*  
****************************************************************************/
PFZ_tpCondRet PFZ_DestruirListaPecasFinalizadas(PFZ_tpPecasFinalizadas *pPecasFinalizadas)
{
	if(*pPecasFinalizadas == NULL || ((*pPecasFinalizadas)->listaPecasVermelhas == NULL && (*pPecasFinalizadas)->listaPecasPretas == NULL)) 
		return PFZ_NaoExisteLista;

	if((*pPecasFinalizadas)->listaPecasVermelhas != NULL)
		LIS_DestruirLista((*pPecasFinalizadas)->listaPecasVermelhas);

	if((*pPecasFinalizadas)->listaPecasPretas != NULL)
		LIS_DestruirLista((*pPecasFinalizadas)->listaPecasPretas);

	free(*pPecasFinalizadas);
	*pPecasFinalizadas = NULL;

	return PFZ_OK ;

} /* Fim função: PFZ Destruir lista de peças finalizadas */


/********** Fim do módulo de implementação: Módulo peças finalizadas **********/
