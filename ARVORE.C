/***************************************************************************
*  $MCI Módulo de implementação: Módulo árvore
*
*  Arquivo gerado:              ARVORE.C
*  Letras identificadoras:      ARV
*
*  Nome da base de software:    Exemplo de teste automatizado
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\SIMPLES.BSW
*
*  Projeto: Disciplinas INF 1628 / 1301
*  Gestor:  DI/PUC-Rio
*  Autores: avs - Arndt von Staa, ft - Fernando tancini
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*       4.00   ft    03/04/2019 Adicao das funções do T1
*       3.00   avs   28/02/2003 Uniformização da interface das funções e
*                               de todas as condições de retorno.
*       2.00   avs   03/08/2002 Eliminação de código duplicado, reestruturação
*       1.00   avs   15/08/2001 Início do desenvolvimento
*
***************************************************************************/

#include   <malloc.h>
#include   <stdio.h>

#define ARVORE_OWN
#include "ARVORE.H"
#include "LISTA.H"
#undef ARVORE_OWN

/***********************************************************************
*
*  $TC Tipo de dados: ARV Descritor do nó da árvore
*
*
*  $ED Descrição do tipo
*     Descreve a organização do nó
*
***********************************************************************/

   typedef struct tgNoArvore {

         struct tgNoArvore * pNoPai ;
               /* Ponteiro para pai
               *
               *$EED Assertivas estruturais
               *   É NULL sse o nó é raiz
               *   Se não for raiz, um de pNoEsq ou pNoDir de pNoPai do nó
               *   corrente apontam para o nó corrente */

         struct tgNoArvore * pNoEsq ;
               /* Ponteiro para filho à esquerda
               *
               *$EED Assertivas estruturais
               *   se pNoEsq do nó X != NULL então pNoPai de pNoEsq aponta para o nó X */

         struct tgNoArvore * pNoDir ;
               /* Ponteiro para filho à direita
               *
               *$EED Assertivas estruturais
               *   se pNoDir do nó X != NULL então pNoPai de pNoDir aponta para o nó X */

		 struct tgNoArvore * pCostura ;
               /* Ponteiro para proximo item costurado */

		 char Valor ;
               /* Chave do nó, para a ordem da costura */

		 LIS_tppLista linkedList ;
		       /* Lista encadeada do no*/

   } tpNoArvore ;

/***********************************************************************
*
*  $TC Tipo de dados: ARV Descritor da cabeça de uma árvore
*
*
*  $ED Descrição do tipo
*     A cabe‡a da árvore é o ponto de acesso para uma determinada árvore.
*     Por intermédio da referência para o nó corrente e do ponteiro
*     pai pode-se navegar a árvore sem necessitar de uma pilha.
*     Pode-se, inclusive, operar com a árvore em forma de co-rotina.
*
***********************************************************************/

   typedef struct tgArvore {

         tpNoArvore * pNoRaiz ;
               /* Ponteiro para a raiz da árvore */

         tpNoArvore * pNoCorr ;
               /* Ponteiro para o nó corrente da árvore */

		 tpNoArvore * pNoCostura;
		       /* Ponteiro para o nó de inicio da costura */

   } tpArvore ;

/*****  Dados encapsulados no módulo  *****/

      static tpArvore * pArvore = NULL ;
            /* Ponteiro para a cabe‡a da árvore */

/***** Protótipos das funções encapuladas no módulo *****/

   static tpNoArvore * CriarNo( char ValorParm ) ;

   static ARV_tpCondRet CriarNoRaiz( char ValorParm ) ;

   static void DestroiArvore( tpNoArvore * pNo ) ;

   static void EncontraFolhasECostura( tpNoArvore * pNo ) ;

   static void AddNoNaCosturaEmOrdem (tpNoArvore * pNo) ;

   static void DestruirValor( void * pValor );
	
   
/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: ARV Criar árvore
*  ****/

   ARV_tpCondRet ARV_CriarArvore( void )
   {

      if ( pArvore != NULL )
      {
         ARV_DestruirArvore( ) ;
      } /* if */

      pArvore = ( tpArvore * ) malloc( sizeof( tpArvore )) ;
      if ( pArvore == NULL )
      {
         return ARV_CondRetFaltouMemoria ;
      } /* if */

      pArvore->pNoRaiz = NULL ;
      pArvore->pNoCorr = NULL ;
	  pArvore->pNoCostura = NULL ;

      return ARV_CondRetOK ;

   } /* Fim função: ARV Criar árvore */

/***************************************************************************
*
*  Função: ARV Destruir árvore
*  ****/

   void ARV_DestruirArvore( void )
   {

      if ( pArvore != NULL )
      {
         if ( pArvore->pNoRaiz != NULL )
         {
            DestroiArvore( pArvore->pNoRaiz ) ;
         } /* if */
         free( pArvore ) ;
         pArvore = NULL ;
      } /* if */

   } /* Fim função: ARV Destruir árvore */

/***************************************************************************
*
*  Função: ARV Adicionar filho à esquerda
*  ****/

   ARV_tpCondRet ARV_InserirEsquerda( char ValorParm )
   {

      ARV_tpCondRet CondRet ;

      tpNoArvore * pCorr ;
      tpNoArvore * pNo ;

      /* Tratar vazio, esquerda */

         CondRet = CriarNoRaiz( ValorParm ) ;
         if ( CondRet != ARV_CondRetNaoCriouRaiz )
         {
            return CondRet ;
         } /* if */

      /* Criar nó à esquerda de folha */

         pCorr = pArvore->pNoCorr ;
         if ( pCorr == NULL )
         {
            return ARV_CondRetErroEstrutura ;
         } /* if */
               
         if ( pCorr->pNoEsq == NULL )
         {
            pNo = CriarNo( ValorParm ) ;
            if ( pNo == NULL )
            {
               return ARV_CondRetFaltouMemoria ;
            } /* if */
            pNo->pNoPai      = pCorr ;
            pCorr->pNoEsq    = pNo ;
            pArvore->pNoCorr = pNo ;

            return ARV_CondRetOK ;
         } /* if */

      /* Tratar não folha à esquerda */

         return ARV_CondRetNaoEhFolha ;

   } /* Fim função: ARV Adicionar filho à esquerda */

/***************************************************************************
*
*  Função: ARV Adicionar folha à esquerda
*  ****/

   ARV_tpCondRet ARV_InserirFolhaEsquerda( char ValorParm , int int1, int int2, int int3)
   {

      ARV_tpCondRet CondRet ;

      tpNoArvore * pCorr ;
      tpNoArvore * pNo ;

	  // como o modulo lista aceita apenas ponteiro de valor no metodo de iinsercao,
	  // devemos criar valores alocados na memoria...
	  int * i1 = (int *) malloc(sizeof(int));
	  int * i2 = (int *) malloc(sizeof(int));
	  int * i3 = (int *) malloc(sizeof(int));
	  *i1 = int1;
	  *i2 = int2;
	  *i3 = int2;

      /* Tratar vazio, esquerda */

         CondRet = CriarNoRaiz( ValorParm ) ;
         if ( CondRet != ARV_CondRetNaoCriouRaiz )
         {
            return CondRet ;
         } /* if */

      /* Criar nó à esquerda de folha */

         pCorr = pArvore->pNoCorr ;
         if ( pCorr == NULL )
         {
            return ARV_CondRetErroEstrutura ;
         } /* if */
               
         if ( pCorr->pNoEsq == NULL )
         {
            pNo = CriarNo( ValorParm ) ;
            if ( pNo == NULL )
            {
               return ARV_CondRetFaltouMemoria ;
            } /* if */
			pNo->pNoPai      = pCorr ;
            pCorr->pNoEsq    = pNo ;
            pArvore->pNoCorr = pNo ;
			
			pNo->linkedList = LIS_CriarLista(DestruirValor);
			if ( pNo->linkedList == NULL )
            {
               return ARV_CondRetFaltouMemoria ;
            } /* if */
			LIS_InserirElementoApos(pNo->linkedList, i1);
			LIS_InserirElementoApos(pNo->linkedList, i2);
			LIS_InserirElementoApos(pNo->linkedList, i3);

            return ARV_CondRetOK ;
         } /* if */

      /* Tratar não folha à esquerda */

         return ARV_CondRetNaoEhFolha ;

   } /* Fim função: ARV Adicionar folha à esquerda */

/***************************************************************************
*
*  Função: ARV Adicionar filho à direita
*  ****/

   ARV_tpCondRet ARV_InserirDireita( char ValorParm )
   {

      ARV_tpCondRet CondRet ;

      tpNoArvore * pCorr ;
      tpNoArvore * pNo ;

      /* Tratar vazio, direita */

         CondRet = CriarNoRaiz( ValorParm ) ;
         if ( CondRet != ARV_CondRetNaoCriouRaiz )
         {
            return CondRet ;
         } /* if */

      /* Criar nó à direita de folha */

         pCorr = pArvore->pNoCorr ;
         if ( pCorr == NULL )
         {
            return ARV_CondRetErroEstrutura ;
         } /* if */

         if ( pCorr->pNoDir == NULL )
         {
            pNo = CriarNo( ValorParm ) ;
            if ( pNo == NULL )
            {
               return ARV_CondRetFaltouMemoria ;
            } /* if */
            pNo->pNoPai      = pCorr ;
            pCorr->pNoDir    = pNo ;
            pArvore->pNoCorr = pNo ;

            return ARV_CondRetOK ;
         } /* if */

      /* Tratar não folha à direita */

         return ARV_CondRetNaoEhFolha ;

   } /* Fim função: ARV Adicionar filho à direita */

/***************************************************************************
*
*  Função: ARV Adicionar folha à direita
*  ****/

 ARV_tpCondRet ARV_InserirFolhaDireita( char ValorParm , int int1, int int2, int int3)
   {

      ARV_tpCondRet CondRet ;

      tpNoArvore * pCorr ;
      tpNoArvore * pNo ;

	  // como o modulo lista aceita apenas ponteiro de valor no metodo de iinsercao,
	  // devemos criar valores alocados na memoria...
	  int * i1 = (int *) malloc(sizeof(int));
	  int * i2 = (int *) malloc(sizeof(int));
	  int * i3 = (int *) malloc(sizeof(int));
	  *i1 = int1;
	  *i2 = int2;
	  *i3 = int2;

      /* Tratar vazio, direita */

         CondRet = CriarNoRaiz( ValorParm ) ;
         if ( CondRet != ARV_CondRetNaoCriouRaiz )
         {
            return CondRet ;
         } /* if */

      /* Criar nó à direita de folha */

         pCorr = pArvore->pNoCorr ;
         if ( pCorr == NULL )
         {
            return ARV_CondRetErroEstrutura ;
         } /* if */

         if ( pCorr->pNoDir == NULL )
         {
            pNo = CriarNo( ValorParm ) ;
            if ( pNo == NULL )
            {
               return ARV_CondRetFaltouMemoria ;
            } /* if */
            pNo->pNoPai      = pCorr ;
            pCorr->pNoDir    = pNo ;
            pArvore->pNoCorr = pNo ;
			
			pNo->linkedList = LIS_CriarLista(DestruirValor);
			if ( pNo->linkedList == NULL )
            {
               return ARV_CondRetFaltouMemoria ;
            } /* if */
			LIS_InserirElementoApos(pNo->linkedList, i1);
			LIS_InserirElementoApos(pNo->linkedList, i2);
			LIS_InserirElementoApos(pNo->linkedList, i3);

            return ARV_CondRetOK ;
         } /* if */

      /* Tratar não folha à direita */

         return ARV_CondRetNaoEhFolha ;

   } /* Fim função: ARV Adicionar folha à direita */

/***************************************************************************
*
*  Função: ARV Costurar os nós folhas em ordem alfabetica
*  ****/

   ARV_tpCondRet ARV_CosturarFolhas( void )
   {
		
		if ( pArvore == NULL )
		{
			return ARV_CondRetArvoreNaoExiste ;
		} /* if */

		if ( pArvore->pNoCorr == NULL )
		{
			return ARV_CondRetArvoreVazia ;
		} /* if */
		pArvore->pNoCostura = NULL;
		EncontraFolhasECostura(pArvore->pNoRaiz);
      
		return ARV_CondRetOK ;

   } /* Fim função: ARV Costurar os nós folhas em ordem alfabetica */

/***********************************************************************
*
*  $FC Função: ARV Mostra a Costura
*
****/

	ARV_tpCondRet ARV_MostraCostura () {

		tpNoArvore * noAnterior = pArvore->pNoCostura;


		if ( pArvore == NULL )
		{
			return ARV_CondRetArvoreNaoExiste ;
		} /* if */

		if ( pArvore->pNoCorr == NULL )
		{
			return ARV_CondRetArvoreVazia ;
		} /* if */

		while (1) {
			if (noAnterior == NULL) {
				return ARV_CondRetOK ;
			} else {
				printf("\n%c", noAnterior->Valor);
				noAnterior = noAnterior->pCostura;
			}
		}
		
	} /* Fim função: ARV Mostra a Costura */

/***************************************************************************
*
*  Função: ARV Ir para nó pai
*  ****/

   ARV_tpCondRet ARV_IrPai( void )
   {

      if ( pArvore == NULL )
      {
         return ARV_CondRetArvoreNaoExiste ;
      } /* if */
      if ( pArvore->pNoCorr == NULL )
      {
         return ARV_CondRetArvoreVazia ;
      } /* if */

      if ( pArvore->pNoCorr->pNoPai != NULL )
      {
         pArvore->pNoCorr = pArvore->pNoCorr->pNoPai ;
         return ARV_CondRetOK ;
      } else {
         return ARV_CondRetNohEhRaiz ;
      } /* if */

   } /* Fim função: ARV Ir para nó pai */

/***************************************************************************
*
*  Função: ARV Ir para nó à esquerda
*  ****/

   ARV_tpCondRet ARV_IrNoEsquerda( void )
   {

      if ( pArvore == NULL )
      {
         return ARV_CondRetArvoreNaoExiste ;
      } /* if */

      if ( pArvore->pNoCorr == NULL )
      {
         return ARV_CondRetArvoreVazia ;
      } /* if */

      if ( pArvore->pNoCorr->pNoEsq == NULL )
      {
         return ARV_CondRetNaoPossuiFilho ;
      } /* if */

      pArvore->pNoCorr = pArvore->pNoCorr->pNoEsq ;
      return ARV_CondRetOK ;

   } /* Fim função: ARV Ir para nó à esquerda */

/***************************************************************************
*
*  Função: ARV Ir para nó à direita
*  ****/

   ARV_tpCondRet ARV_IrNoDireita( void )
   {

      if ( pArvore == NULL )
      {
         return ARV_CondRetArvoreNaoExiste ;
      } /* if */

      if ( pArvore->pNoCorr == NULL )
      {
         return ARV_CondRetArvoreVazia ;
      } /* if */

      if ( pArvore->pNoCorr->pNoDir == NULL )
      {
         return ARV_CondRetNaoPossuiFilho ;
      } /* if */

      pArvore->pNoCorr = pArvore->pNoCorr->pNoDir ;
      return ARV_CondRetOK ;

   } /* Fim função: ARV Ir para nó à direita */

/***************************************************************************
*
*  Função: ARV Obter valor corrente
*  ****/

   ARV_tpCondRet ARV_ObterValorCorr( char * ValorParm )
   {

      if ( pArvore == NULL )
      {
         return ARV_CondRetArvoreNaoExiste ;
      } /* if */
      if ( pArvore->pNoCorr == NULL )
      {
         return ARV_CondRetArvoreVazia ;
      } /* if */
      * ValorParm = pArvore->pNoCorr->Valor ;

      return ARV_CondRetOK ;

   } /* Fim função: ARV Obter valor corrente */


/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: ARV Criar nó da árvore
*
*  $FV Valor retornado
*     Ponteiro para o nó criado.
*     Será NULL caso a memória tenha se esgotado.
*     Os ponteiros do nó criado estarão nulos e o valor é igual ao do
*     parâmetro.
*
***********************************************************************/

   tpNoArvore * CriarNo( char ValorParm )
   {

      tpNoArvore * pNo ;

      pNo = ( tpNoArvore * ) malloc( sizeof( tpNoArvore )) ;
      if ( pNo == NULL )
      {
         return NULL ;
      } /* if */

      pNo->pNoPai = NULL ;
      pNo->pNoEsq = NULL ;
      pNo->pNoDir = NULL ;
      pNo->Valor  = ValorParm ;
	  pNo->pCostura = NULL;
	  pNo->linkedList = NULL;
      return pNo ;

   } /* Fim função: ARV Criar nó da árvore */


/***********************************************************************
*
*  $FC Função: ARV Criar nó raiz da árvore
*
*  $FV Valor retornado
*     ARV_CondRetOK
*     ARV_CondRetFaltouMemoria
*     ARV_CondRetNaoCriouRaiz
*
***********************************************************************/

   ARV_tpCondRet CriarNoRaiz( char ValorParm )
   {

      ARV_tpCondRet CondRet ;
      tpNoArvore * pNo ;

      if ( pArvore == NULL )
      {
         CondRet = ARV_CriarArvore( ) ;

         if ( CondRet != ARV_CondRetOK )
         {
            return CondRet ;
         } /* if */
      } /* if */

      if ( pArvore->pNoRaiz == NULL )
      {
         pNo = CriarNo( ValorParm ) ;
         if ( pNo == NULL )
         {
            return ARV_CondRetFaltouMemoria ;
         } /* if */
         pArvore->pNoRaiz = pNo ;
         pArvore->pNoCorr = pNo ;

         return ARV_CondRetOK ;
      } /* if */

      return ARV_CondRetNaoCriouRaiz ;

   } /* Fim função: ARV Criar nó raiz da árvore */


/***********************************************************************
*
*  $FC Função: ARV Destruir a estrutura da árvore
*
*  $EAE Assertivas de entradas esperadas
*     pNoArvore != NULL
*
***********************************************************************/

   void DestroiArvore( tpNoArvore * pNo )
   {

      if ( pNo->pNoEsq != NULL )
      {
         DestroiArvore( pNo->pNoEsq ) ;
      } /* if */

      if ( pNo->pNoDir != NULL )
      {
         DestroiArvore( pNo->pNoDir ) ;
      } /* if */

	  if (pNo->linkedList != NULL) {
		  LIS_DestruirLista(pNo->linkedList);
	  }
      free( pNo );

   } /* Fim função: ARV Destruir a estrutura da árvore */

/***********************************************************************
*
*  $FC Função: ARV Encontra as folhas e manda para a costura
*
***********************************************************************/

	void EncontraFolhasECostura (tpNoArvore * pNo) {
		if (pNo != NULL) {
			EncontraFolhasECostura (pNo->pNoEsq);
			if (pNo->pNoEsq == NULL && pNo->pNoDir == NULL) {
				// eh folha
				AddNoNaCosturaEmOrdem (pNo);
			}
			EncontraFolhasECostura (pNo->pNoDir);
		}
	} /* Fim função: ARV Encontra as folhas e manda para a costura */

/***********************************************************************
*
*  $FC Função: ARV Insere na lista de costura em ordem
*
***********************************************************************/

	void AddNoNaCosturaEmOrdem (tpNoArvore * pNo) {
		tpNoArvore * current;
		tpNoArvore * aux;
		if (pArvore->pNoCostura == NULL) {
			// ainda nao comecou a costura
			pArvore->pNoCostura = pNo;
			pNo->pCostura = NULL;
		} else {
			// ja esta costurando
			current = pArvore->pNoCostura;
			if (pNo->Valor < current->Valor) {
				// no no a ser inserido vai antes do no inicial
				pArvore->pNoCostura = pNo;
				pNo->pCostura = current;
			} else {
				// no a ser inserido ficara no meio ou no final da lista
				while (current->pCostura != NULL) {
					// ainda esta no meio da lista
					if (pNo->Valor < current->pCostura->Valor) {
						// eh pra ficar depois do current e antes do seu atual sucessor
						aux = current->pCostura;
						current->pCostura = pNo;
						pNo->pCostura = aux;
						return; // sai do programa, pois no ja foi inserido
					}
					current = current->pCostura;
				}
				// chegou ao final da lista de costura
				current->pCostura = pNo;
				pNo->pCostura = NULL;
			}
		}
		
	} /* Fim função: ARV Insere na lista de costura em ordem */

/***********************************************************************
*
*  $FC Função: TLIS - Destruir valor (nescessaria p/ criar lista)
*
***********************************************************************/

   void DestruirValor( void * pValor )
   {

      free( pValor ) ;

   } /* Fim função: TLIS -Destruir valor */

/********** Fim do módulo de implementação: Módulo árvore **********/

