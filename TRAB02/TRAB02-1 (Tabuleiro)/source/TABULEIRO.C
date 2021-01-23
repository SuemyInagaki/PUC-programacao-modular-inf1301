/***************************************************************************
*  $MCI Módulo de implementação: TAB Modulo Tabuleiro
*
*  Arquivo gerado:              TABULEIRO.c
*  Letras identificadoras:      TAB
*
*  Projeto: Jogo de Gamao
*  Autores: fbt - Fernando Baggi Tancini
*
*  $HA Histórico de evolução:
*     Versão		Autor		Data			Observações
*	  	3   		fbt	  		03/05/2019		Revisao e consertos
*	  	2   		fbt	  		02/05/2019		Criação do módulo 
*      	1    		fbt	  		01/05/2019		Inicializado projeto
*
***************************************************************************/

	#include	<malloc.h>
	#include 	<stdio.h>
	#include	<stdlib.h>
	#include "PECA.H"
	#include "LISTA.H"
	#define TABULEIRO_OWN
	#include "TABULEIRO.H"
	#undef TABULEIRO_OWN


/***********************************************************************
*
*  $TC Tipo de dados: TAB Descritor do tabuleiro
*
*
*  $ED Descrição do tipo
*     Descreve a organização do tabuleiro
*
***********************************************************************/

	typedef struct tgTabuleiro {
			LIS_tppLista listaCasas ;
					/* Ponteiro para a lista de Casas */

	} tpTabuleiro ;

/*****  Dados encapsulados no módulo  *****/

	static tpTabuleiro * tab = NULL ;
				/* Ponteiro para o tabuleiro */

/***** Protótipos das funções encapuladas no módulo *****/

	static TAB_tpCondRet ConfigPosInicial( ) ;

	static TAB_tpCondRet InserePecaCasa(  char cor, int nCasa ) ;

	static TAB_tpCondRet RemovePecaCasa( int nCasa )  ;
	
	static LIS_tppLista ObterListaCasa( int nCasa ) ;

	static void MeuDestroiLista( void * pValor );

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: TAB Criar Tabuleiro
*  ****/

	TAB_tpCondRet TAB_CriarTabuleiro( void ) 
	{
		int i ;
		LIS_tppLista casa = NULL;
		if ( tab != NULL )
		{
			TAB_DestruirTabuleiro( ) ;
		} /* if */

		tab = ( tpTabuleiro * ) malloc ( sizeof ( tpTabuleiro ) ) ;
		if ( tab == NULL )
		{
			return TAB_CondRetFaltouMemoria ;
		} /* if */
		
		tab->listaCasas = LIS_CriarLista( MeuDestroiLista ) ;
		if ( tab->listaCasas == NULL )
		{
			return TAB_CondRetFaltouMemoria ;
		} /* if */

		for ( i = 0; i < 24; i++ ) 
		{
			casa = LIS_CriarLista( PEC_DestruirPeca ) ;
			if ( casa == NULL )
			{
				return TAB_CondRetFaltouMemoria ;
			} /* if */

			LIS_InserirElementoApos( tab->listaCasas, casa ) ;
		} /* for */

		return ConfigPosInicial( ) ;
	} /* Fim função: TAB Criar Tabuleiro */

/***************************************************************************
*
*  Função: TAB Destruir Tabuleiro
*  ****/

	TAB_tpCondRet TAB_DestruirTabuleiro( void ) 
	{

		if ( tab == NULL )
		{
			return TAB_CondRetOK ;
		} /* if */

		if (tab->listaCasas !=  NULL) 
		{
			LIS_DestruirLista( tab->listaCasas ) ;
		} /* if */

		free( tab ) ;
		tab = NULL ;

		return TAB_CondRetOK;
	} /* Fim função: TAB Destruir Tabuleiro */

/***************************************************************************
*
*  Função: TAB Insere N pecas no Tabuleiro
*  ****/

	TAB_tpCondRet TAB_InsereNPecasCasa( int n, int cor, int nCasa ) 
	{
		int i ;
		TAB_tpCondRet cond ;

		if ( tab == NULL ) {
			return TAB_CondRetTabNaoExiste ;
		} /* if */
		for ( i = 0; i < n; i++ )
		{
			cond = InserePecaCasa( cor, nCasa );
			if ( cond != TAB_CondRetOK ) {
				return cond ;
			} /* if */
		} /* for */
		return TAB_CondRetOK ;
	} /* Fim função: TAB Insere N Pecas na Casa */
	

/***************************************************************************
*
*  Função: TAB Remove N pecas no Tabuleiro
*  ****/

	TAB_tpCondRet TAB_RemoveNPecasCasa( int n, int nCasa ) 
	{
		int i, cond ;

		if ( tab == NULL ) {
			return TAB_CondRetTabNaoExiste ;
		} /* if */
		for ( i = 0; i < n; i++ )
		{
			cond = RemovePecaCasa( nCasa );
			if ( cond == TAB_CondRetCasaNaoExiste ) {
				return TAB_CondRetCasaNaoExiste ;
			} /* if */
			else if (cond == TAB_CondRetCasaVazia ) {
				return TAB_CondRetCasaVazia ;
			} /* else if */
		} /* for */
		return TAB_CondRetOK ;
	} /* Fim função: TAB Insere N Pecas na Casa */


/***************************************************************************
*
*  Função: TAB Num Peças da Casa
*  ****/

	TAB_tpCondRet TAB_NumPecasCasa( int nCasa, int * numPecas ) 
	{
		LIS_tppLista casa ;

		if ( tab == NULL ) {
			return TAB_CondRetTabNaoExiste ;
		} /* if */

		casa = ObterListaCasa ( nCasa ) ;
		if ( casa == NULL ) {
			return TAB_CondRetCasaNaoExiste ;
		} /* if */

		LIS_PegarNumElemenLista( casa, numPecas ) ;
		return TAB_CondRetOK ;
	} /* Fim função: TAB Num Peças da Casa */

/***************************************************************************
*
*  Função: TAB Cor Peças da Casa
*  ****/

	TAB_tpCondRet TAB_CorPecasCasa( int nCasa, char * cor ) 
	{
		LIS_tppLista casa ;
		tppPeca peca ;

		if ( tab == NULL ) {
			return TAB_CondRetTabNaoExiste ;
		} /* if */

		casa = ObterListaCasa ( nCasa ) ;
		if ( casa == NULL ) {
			return TAB_CondRetCasaNaoExiste ;
		} /* if */

		// TODO: peca
		peca = (tppPeca) LIS_ObterValor( casa ) ;
		if ( peca == NULL ) {
			return TAB_CondRetCasaVazia ;
		} /* if */

		PEC_ObterCor( peca, cor );
		return TAB_CondRetOK ;
	} /* Fim função: TAB Cor Peças da Casa */


/*****  Código das funções encapsuladas no módulo  *****/

/***************************************************************************
*
*  $FC Função: TAB Configura posicoes Iniciais
*
*  $ED Descrição da função
*     Cria e insere as peças nas respectivas posiçoes iniciais
*
*  $FV Valor retornado
*		- TAB_CondRetOK
*		- TAB_CondRetTabNaoExiste
*		- TAB_CondRetFaltouMemoria
*  ****/
	
	TAB_tpCondRet ConfigPosInicial( void ) 
	{
		TAB_tpCondRet cond;
		if ( tab == NULL ) {
			return TAB_CondRetTabNaoExiste ;
		} /* if */

		cond = TAB_InsereNPecasCasa( 2, PEC_corPreta, 1 ) ;
		if ( cond != TAB_CondRetOK ) {
			return cond ;
		} /* if */

		cond = TAB_InsereNPecasCasa( 5, PEC_corVermelha, 6 ) ;
		if ( cond != TAB_CondRetOK ) {
			return cond ;
		} /* if */

		cond = TAB_InsereNPecasCasa( 3, PEC_corVermelha, 8 ) ;
		if ( cond != TAB_CondRetOK ) {
			return cond ;
		} /* if */

		cond = TAB_InsereNPecasCasa( 5, PEC_corPreta, 12 ) ;
		if ( cond != TAB_CondRetOK ) {
			return cond ;
		} /* if */

		cond = TAB_InsereNPecasCasa( 5, PEC_corVermelha, 13 ) ;
		if ( cond != TAB_CondRetOK ) {
			return cond ;
		} /* if */

		cond = TAB_InsereNPecasCasa( 3, PEC_corPreta, 17 ) ;
		if ( cond != TAB_CondRetOK ) {
			return cond ;
		} /* if */

		cond = TAB_InsereNPecasCasa( 5, PEC_corPreta, 19 ) ;
		if ( cond != TAB_CondRetOK ) {
			return cond ;
		} /* if */

		cond = TAB_InsereNPecasCasa( 2, PEC_corVermelha, 24 ) ;
		if ( cond != TAB_CondRetOK ) {
			return cond ;
		} /* if */

		return TAB_CondRetOK ;
	} /* Fim função: TAB Configura posicoes Iniciais */


/***************************************************************************
*
*  $FC Função: TAB Insere Peca Casa
*
*  $ED Descrição da função
*     Cria e insere peças na casa indicada
*
*  $FV Valor retornado
*		- TAB_CondRetOK
*		- TAB_CondRetTabNaoExiste
*		- TAB_CondRetCasaNaoExiste
*		- TAB_CondRetFaltouMemoria
*  ****/

	TAB_tpCondRet InserePecaCasa( char cor, int nCasa ) 
	{
		LIS_tppLista casa ;
		tppPeca peca ;

		if ( tab == NULL ) {
			return TAB_CondRetTabNaoExiste ;
		} /* if */

		// TODO: cria peca e checa se teve falta de memoria

		PEC_CriarPeca(&peca, cor);
		if ( peca == NULL ) {
			return TAB_CondRetFaltouMemoria ;
		} /* if */

		casa = ObterListaCasa ( nCasa ) ;
		if ( casa == NULL ) {
			return TAB_CondRetCasaNaoExiste ; 
		} /* if */
		LIS_InserirElementoApos( casa, peca );
		return TAB_CondRetOK ;
	} /* Fim função: TAB Insere Peça na Casa */


/***************************************************************************
*
*  $FC Função: TAB Remove Peca Casa
*
*  $ED Descrição da função
*     Remove uma peça na casa informada
*
*  $FV Valor retornado
*		- TAB_CondRetOK
*		- TAB_CondRetTabNaoExiste
*		- TAB_CondRetCasaNaoExiste
*		- TAB_CondRetCasaVazia
*  ****/

	TAB_tpCondRet RemovePecaCasa( int nCasa ) 
	{
		LIS_tppLista casa ;

		if ( tab == NULL ) {
			return TAB_CondRetTabNaoExiste ;
		} /* if */

		casa = ObterListaCasa ( nCasa ) ;
		if ( casa == NULL ) {
			return TAB_CondRetCasaNaoExiste ;
		} /* if */

		if ( LIS_ExcluirElemento( casa ) == LIS_CondRetListaVazia ) {
			return TAB_CondRetCasaVazia ;
		} /* if */

		return TAB_CondRetOK ;
	} /* Fim função: TAB Remove Peça Casa */

	
/***************************************************************************
*
*  $FC Função: TAB Obter Lista Casa
*	
* $EAE Assertivas de entradas esperadas
*     tab != NULL
*	  tab->listaCasas != NULL
*
*	$EP Parâmetros:
*     $P nCasa - é o número da casa escolhida para obter a lista
*
*  $FV Valor retornado
*			Lista da casa informada
*			Será NULL caso a casa não exista na listaCasas.
*  *****/

	LIS_tppLista ObterListaCasa( int nCasa ) 
	{
		int cond;

		if ( nCasa < 1 || nCasa > 24 ) {
			return NULL ;
		} /* if */

		IrInicioLista( tab->listaCasas ) ;
		cond = LIS_AvancarElementoCorrente( tab->listaCasas , nCasa-1 ) ;
		if (cond == LIS_CondRetOK) {
			return (LIS_tppLista) LIS_ObterValor( tab->listaCasas ) ;
		} /* if */
		else {
			return NULL ;
		} /* else */
	} /* Fim função: TAB Obter Lista Casa */

/***********************************************************************
*
*  $FC Função: Meu Destroi Lista
*
*  $ED Descrição da função
*     Funcao para destruir lista que eh elemento da listaCasas
*
*  $EP Parâmetros
*     $P lista - É o ponteiro a lista que quer destruir
*
***********************************************************************/

	void MeuDestroiLista ( void * lista )
	{
		if ( lista == NULL )
		{
			return ;
		} /* if */

		LIS_DestruirLista( (LIS_tppLista) lista );

	} /* Fim função: Meu Destruir Lista */
 

/********** Fim do módulo de implementação: Módulo Tabuleiro **********/