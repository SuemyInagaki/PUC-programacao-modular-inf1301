/*****************************************************************************************
*	$MCI Módulo de implementação: Módulo dado pontos
*	Arquivo gerado:		      DadoPontos.c
*	Letras identificadoras:	      DPTS
*
*	Projeto:	              Disciplina INF 1301
*
*  	Autor:                        sipf - Suemy Inagaki Pinheiro Fagundes
*
*	$HA Histórico de evolução:
*	Versão  Autor    Data     Observações
*	1       sipf   30/abr/2019 início desenvolvimento
*
*       $ED Descrição do módulo
*       Define as Funções de DadoPontos.
*	No início de cada partida não existe dado de pontos
*
*****************************************************************************************/

#include   <malloc.h>
#include   <stdio.h>

#define DadoPontos_OWN
#include "DadoPontos.h"
#undef DadoPontos_OWN


/*****************************************************************************************
*
*  $TC Tipo de dados: DPTS Descritor do dado de pontos
*
*  $ED Descrição do tipo
*     Descreve os parâmetros de um dado de pontos
*
*****************************************************************************************/
typedef struct DPTS_tpDadoPontos{
	int Ponto;
	/* Pontuação  do jogo no momento*/

	char CorPeca;
	/*Cor do jogador que pode dobrar a pontuacao do jogo*/

} DPTS_tpDadoPontos;

/*****************************************************************************************
*
*  Função: DPTS Criar Dado  Pontos
* 
*****************************************************************************************/
DPTS_CondRet DPTS_CriarDadoPontos(DPTS_DadoPCabeca *pDadoPontos){
	
	*pDadoPontos = (DPTS_DadoPCabeca) malloc(sizeof(DPTS_tpDadoPontos));
	if(pDadoPontos == NULL){
		return DPTS_FaltouMemoria ;
	} 

	(*pDadoPontos)->Ponto = 1;

	return DPTS_Feito ;
} /* Fim da função: DPTS Criar Dado Pontos */


/*****************************************************************************************
*
*  Função: DPTS Jogador Dobra Atualiza
*  
*****************************************************************************************/
DPTS_CondRet DPTS_JogadorDobraAtualiza(DPTS_DadoPCabeca pDadoPontos, char CorPeca){
	if(pDadoPontos == NULL){
		return DPTS_DadoPontosNaoExiste;
	} 

	pDadoPontos->CorPeca = CorPeca;
	return DPTS_Feito;
} /* Fim da função: DPTS Jogador Dobra Atualiza */

/*****************************************************************************************
*
*  Função: DPTS Dobrar Pontuacao Atual
*  
*****************************************************************************************/
DPTS_CondRet DPTS_DobrarPontuacaoAtual(DPTS_DadoPCabeca pDadoPontos, char CorPeca){
	if(pDadoPontos == NULL)
		return  DPTS_DadoPontosNaoExiste;

	if(pDadoPontos->CorPeca != CorPeca)
		return DPTS_JogadorNaoTemDadoPontos;

	pDadoPontos->Ponto *= 2;
	return DPTS_Feito ;
}/* Fim da função:  DPTS Dobrar Pontuacao Atual*/

/*****************************************************************************************
*
*  Função: DPTS Obter jogador Dobra Ponto
*  
*****************************************************************************************/
DPTS_CondRet DPTS_ObterJogadorDobraPonto(DPTS_DadoPCabeca pDadoPontos, char *pCorPeca){
	if(pDadoPontos == NULL)
		return DPTS_DadoPontosNaoExiste;

	if(pDadoPontos->Ponto == 1)
		return DPTS_NaoExisteJogadorComDadoPontos;

	*pCorPeca = pDadoPontos->CorPeca;
	return DPTS_Feito ;
} /* Fim da função:  DPTS Obter jogador Dobra Ponto*/

/*****************************************************************************************
*
*  Função: DPTS Obter pontuação partida
*  
*****************************************************************************************/
DPTS_CondRet DPTS_ObterPontuacaoPartida(DPTS_DadoPCabeca pDadoPontos, int *pPonto){
	if(*pDadoPontos == NULL){
		return DPTS_DadoPontosNaoExiste;
	}

	*pPonto = pDadoPontos->Ponto;
	
	return DPTS_Feito;

} /* Fim da função:  DPTS Obter pontuação partida*/

/*****************************************************************************************
*
*  Função: DPTS Destruir dado de pontos
*  
*****************************************************************************************/
DPTS_CondRet DPTS_DestruirDadoPontos(DPTS_DadoPCabeca *pDadoPontos){
	if(pDadoPontos == NULL){
		return DPTS_DadoPontosNaoExiste;
	} 

	free(*pDadoPontos);
	*pDadoPontos = NULL;

	return DPTS_Feito;

} /* Fim da função: DPTS Destruir dado de pontos */

/***************** Fim do módulo de implementação: Módulo Dado Pontos ********************/
