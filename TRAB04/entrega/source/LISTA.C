/***************************************************************************
*  $MCI Módulo de implementação: LIS  Lista duplamente encadeada
*
*  Arquivo gerado:              LISTA.c
*  Letras identificadoras:      LIS
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     4       avs   01/fev/2006 criar linguagem script simbólica
*     3       avs   08/dez/2004 uniformização dos exemplos
*     2       avs   07/jul/2003 unificação de todos os módulos em um só projeto
*     1       avs   16/abr/2003 início desenvolvimento
*
***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>

#define LISTA_OWN
#include "LISTA.h"
#undef LISTA_OWN

#ifdef _DEBUG
#include "CESPDIN.H"
#include "CONTA.H"
#endif 

/***********************************************************************
*
*  $TC Tipo de dados: LIS Elemento da lista
*
*
***********************************************************************/

   typedef struct tagElemLista {

         void * pValor ;
               /* Ponteiro para o valor contido no elemento */

         struct tagElemLista * pAnt ;
               /* Ponteiro para o elemento predecessor */

         struct tagElemLista * pProx ;
               /* Ponteiro para o elemento sucessor */

      #ifdef _DEBUG
         
         char tipo;
         
      #endif

   } tpElemLista ;

/***********************************************************************
*
*  $TC Tipo de dados: LIS Descritor da cabeça de lista
*
*
***********************************************************************/

   typedef struct LIS_tagLista {

         tpElemLista * pOrigemLista ;
               /* Ponteiro para a origem da lista */

         tpElemLista * pFimLista ;
               /* Ponteiro para o final da lista */

         tpElemLista * pElemCorr ;
               /* Ponteiro para o elemento corrente da lista */

         int numElem ;
               /* Número de elementos da lista */

         void ( * ExcluirValor ) ( void * pValor ) ;
               /* Ponteiro para a função de destruição do valor contido em um elemento */

      #ifdef _DEBUG

         char tipo;

      #endif


   } LIS_tpLista ;

/***** Protótipos das funções encapuladas no módulo *****/
#ifdef _DEBUG
   static const char* PONTEIRO_LIXO = "lixolixolixolixolixolixolixolix";
   static const char TIPO_LIXO = 0xff;
#endif

   static void LiberarElemento( LIS_tppLista   pLista ,
                                tpElemLista  * pElem   ) ;

   static tpElemLista * CriarElemento( LIS_tppLista pLista ,
                                       void *       pValor  ) ;

   static void LimparCabeca( LIS_tppLista pLista ) ;

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: LIS  &Criar lista
*  ****/

   LIS_tppLista LIS_CriarLista(
             void   ( * ExcluirValor ) ( void * pDado ) )
   {

      LIS_tpLista * pLista = NULL ;

      pLista = ( LIS_tpLista * ) malloc( sizeof( LIS_tpLista )) ;
      if ( pLista == NULL )
      {
         return NULL ;
      } /* if */

      LimparCabeca( pLista ) ;

      pLista->ExcluirValor = ExcluirValor ;

   #ifdef _DEBUG
     pLista->tipo = LIS_TipoEspacoCabeca;
     CED_DefinirTipoEspaco(pLista, LIS_TipoEspacoCabeca);
   #endif

      return pLista ;

   } /* Fim função: LIS  &Criar lista */

/***************************************************************************
*
*  Função: LIS  &Destruir lista
*  ****/

   void LIS_DestruirLista( LIS_tppLista pLista )
   {

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      LIS_EsvaziarLista( pLista ) ;

      free( pLista ) ;

   } /* Fim função: LIS  &Destruir lista */

/***************************************************************************
*
*  Função: LIS  &Esvaziar lista
*  ****/

   void LIS_EsvaziarLista( LIS_tppLista pLista )
   {

      tpElemLista * pElem ;
      tpElemLista * pProx ;

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      pElem = pLista->pOrigemLista ;
      while ( pElem != NULL )
      {
         pProx = pElem->pProx ;
         LiberarElemento( pLista , pElem ) ;
         pElem = pProx ;
      } /* while */

      LimparCabeca( pLista ) ;

   } /* Fim função: LIS  &Esvaziar lista */

/***************************************************************************
*
*  Função: LIS  &Inserir elemento antes
*  ****/

   LIS_tpCondRet LIS_InserirElementoAntes( LIS_tppLista pLista ,
                                           void * pValor        )
   {

      tpElemLista * pElem ;

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      /* Criar elemento a inerir antes */

         pElem = CriarElemento( pLista , pValor ) ;
         if ( pElem == NULL )
         {
            return LIS_CondRetFaltouMemoria ;
         } /* if */

      /* Encadear o elemento antes do elemento corrente */

         if ( pLista->pElemCorr == NULL )
         {
            pLista->pOrigemLista = pElem ;
            pLista->pFimLista = pElem ;
         } else
         {
            if ( pLista->pElemCorr->pAnt != NULL )
            {
               pElem->pAnt  = pLista->pElemCorr->pAnt ;
               pLista->pElemCorr->pAnt->pProx = pElem ;
            } else
            {
               pLista->pOrigemLista = pElem ;
            } /* if */

            pElem->pProx = pLista->pElemCorr ;
            pLista->pElemCorr->pAnt = pElem ;
         } /* if */

         pLista->pElemCorr = pElem ;

         return LIS_CondRetOK ;

   } /* Fim função: LIS  &Inserir elemento antes */

/***************************************************************************
*
*  Função: LIS  &Inserir elemento após
*  ****/

   LIS_tpCondRet LIS_InserirElementoApos( LIS_tppLista pLista ,
                                          void * pValor        )
      
   {

      tpElemLista * pElem ;

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      /* Criar elemento a inerir após */

         pElem = CriarElemento( pLista , pValor ) ;
         if ( pElem == NULL )
         {
            return LIS_CondRetFaltouMemoria ;
         } /* if */

      /* Encadear o elemento após o elemento */

         if ( pLista->pElemCorr == NULL )
         {
            pLista->pOrigemLista = pElem ;
            pLista->pFimLista = pElem ;
         } else
         {
            if ( pLista->pElemCorr->pProx != NULL )
            {
               pElem->pProx  = pLista->pElemCorr->pProx ;
               pLista->pElemCorr->pProx->pAnt = pElem ;
            } else
            {
               pLista->pFimLista = pElem ;
            } /* if */

            pElem->pAnt = pLista->pElemCorr ;
            pLista->pElemCorr->pProx = pElem ;

         } /* if */
                  
         pLista->pElemCorr = pElem ;
                  
         return LIS_CondRetOK ;

   } /* Fim função: LIS  &Inserir elemento após */

/***************************************************************************
*
*  Função: LIS  &Excluir elemento
*  ****/

   LIS_tpCondRet LIS_ExcluirElemento( LIS_tppLista pLista )
   {

      tpElemLista * pElem ;

      #ifdef _DEBUG
         assert( pLista  != NULL ) ;
      #endif

      if ( pLista->pElemCorr == NULL )
      {
         return LIS_CondRetListaVazia ;
      } /* if */

      pElem = pLista->pElemCorr ;

      /* Desencadeia à esquerda */

         if ( pElem->pAnt != NULL )
         {
            pElem->pAnt->pProx   = pElem->pProx ;
            pLista->pElemCorr    = pElem->pAnt ;
         } else {
            pLista->pElemCorr    = pElem->pProx ;
            pLista->pOrigemLista = pLista->pElemCorr ;
         } /* if */

      /* Desencadeia à direita */

         if ( pElem->pProx != NULL )
         {
            pElem->pProx->pAnt = pElem->pAnt ;
         } else
         {
            pLista->pFimLista = pElem->pAnt ;
         } /* if */

      LiberarElemento( pLista , pElem ) ;

      return LIS_CondRetOK ;

   } /* Fim função: LIS  &Excluir elemento */

/***************************************************************************
*
*  Função: LIS  &Obter referência para o valor contido no elemento
*  ****/

   void * LIS_ObterValor( LIS_tppLista pLista )
   {

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      if ( pLista->pElemCorr == NULL )
      {
        return NULL ;
      } /* if */

      return pLista->pElemCorr->pValor ;

   } /* Fim função: LIS  &Obter referência para o valor contido no elemento */

/***************************************************************************
*
*  Função: LIS  &Ir para o elemento inicial
*  ****/

   void IrInicioLista( LIS_tppLista pLista )
   {

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      pLista->pElemCorr = pLista->pOrigemLista ;

   } /* Fim função: LIS  &Ir para o elemento inicial */

/***************************************************************************
*
*  Função: LIS  &Ir para o elemento final
*  ****/

   void IrFinalLista( LIS_tppLista pLista )
   {

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      pLista->pElemCorr = pLista->pFimLista ;

   } /* Fim função: LIS  &Ir para o elemento final */

/***************************************************************************
*
*  Função: LIS  &Avançar elemento
*  ****/

   LIS_tpCondRet LIS_AvancarElementoCorrente( LIS_tppLista pLista ,
                                              int numElem )
   {

      int i ;

      tpElemLista * pElem ;

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      /* Tratar lista vazia */

         if ( pLista->pElemCorr == NULL )
         {

            return LIS_CondRetListaVazia ;

         } /* fim ativa: Tratar lista vazia */

      /* Tratar avançar para frente */

         if ( numElem > 0 )
         {

            pElem = pLista->pElemCorr ;
            for( i = numElem ; i > 0 ; i-- )
            {
               if ( pElem == NULL )
               {
                  break ;
               } /* if */
               pElem    = pElem->pProx ;
            } /* for */

            if ( pElem != NULL )
            {
               pLista->pElemCorr = pElem ;
               return LIS_CondRetOK ;
            } /* if */

            pLista->pElemCorr = pLista->pFimLista ;
            return LIS_CondRetFimLista ;

         } /* fim ativa: Tratar avançar para frente */

      /* Tratar avançar para trás */

         else if ( numElem < 0 )
         {

            pElem = pLista->pElemCorr ;
            for( i = numElem ; i < 0 ; i++ )
            {
               if ( pElem == NULL )
               {
                  break ;
               } /* if */
               pElem    = pElem->pAnt ;
            } /* for */

            if ( pElem != NULL )
            {
               pLista->pElemCorr = pElem ;
               return LIS_CondRetOK ;
            } /* if */

            pLista->pElemCorr = pLista->pOrigemLista ;
            return LIS_CondRetFimLista ;

         } /* fim ativa: Tratar avançar para trás */

      /* Tratar não avançar */

         return LIS_CondRetOK ;

   } /* Fim função: LIS  &Avançar elemento */

/***************************************************************************
*
*  Função: LIS  &Procurar elemento contendo valor
*  ****/

   LIS_tpCondRet LIS_ProcurarValor( LIS_tppLista pLista ,
                                    void * pValor        )
   {

      tpElemLista * pElem ;

      #ifdef _DEBUG
         assert( pLista  != NULL ) ;
      #endif

      if ( pLista->pElemCorr == NULL )
      {
         return LIS_CondRetListaVazia ;
      } /* if */

      for ( pElem  = pLista->pElemCorr ;
            pElem != NULL ;
            pElem  = pElem->pProx )
      {
         if ( pElem->pValor == pValor )
         {
            pLista->pElemCorr = pElem ;
            return LIS_CondRetOK ;
         } /* if */
      } /* for */

      return LIS_CondRetNaoAchou ;

   } /* Fim função: LIS  &Procurar elemento contendo valor */


/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: LIS  -Liberar elemento da lista
*
*  $ED Descrição da função
*     Elimina os espaços apontados pelo valor do elemento e o
*     próprio elemento.
*
***********************************************************************/

   void LiberarElemento( LIS_tppLista   pLista ,
                         tpElemLista  * pElem   )
   {

      if ( ( pLista->ExcluirValor != NULL )
        && ( pElem->pValor != NULL        ))
      {
         pLista->ExcluirValor( pElem->pValor ) ;
      } /* if */

      free( pElem ) ;

      pLista->numElem-- ;

   } /* Fim função: LIS  -Liberar elemento da lista */


/***********************************************************************
*
*  $FC Função: LIS  -Criar o elemento
*
***********************************************************************/

   tpElemLista * CriarElemento( LIS_tppLista pLista ,
                                void *       pValor  )
   {

      tpElemLista * pElem ;

      pElem = ( tpElemLista * ) malloc( sizeof( tpElemLista )) ;
      if ( pElem == NULL )
      {
         return NULL ;
      } /* if */

      pElem->pValor = pValor ;
      pElem->pAnt   = NULL  ;
      pElem->pProx  = NULL  ;

      pLista->numElem ++ ;

      return pElem ;

   } /* Fim função: LIS  -Criar o elemento */


/***********************************************************************
*
*  $FC Função: LIS  -Limpar a cabeça da lista
*
***********************************************************************/

   void LimparCabeca( LIS_tppLista pLista )
   {

      pLista->pOrigemLista = NULL ;
      pLista->pFimLista = NULL ;
      pLista->pElemCorr = NULL ;
      pLista->numElem   = 0 ;

   } /* Fim função: LIS  -Limpar a cabeça da lista */

#ifdef _DEBUG

/***********************************************************************
*
*  $FC Fun��o: LIS  -Verificar Lista
*
***********************************************************************/

   int LIS_VerificarLista(LIS_tppLista Lista){
      int falhas = 0;
      int flag_ver_invertido = 0;
      int n_elementos = 0;
      tpElemLista* Elemento;
      int iterator, num_alocados;

      if(Lista == NULL){
         CNT_CONTAR("LIS_ListaNaoExiste");
         falhas++;
         return falhas;
      }
      if(Lista->pElemCorr == NULL ){
         CNT_CONTAR("LIS_CorrenteNULL");
         falhas++;
      }
      if(Lista->pOrigemLista == NULL){
         CNT_CONTAR("LIS_OrigemNULL");
         falhas++;
         flag_ver_invertido = 1;
      }
      if(Lista->pFimLista == NULL){
         CNT_CONTAR("LIS_FimNULL");
         falhas++;
         flag_ver_invertido = 0;
      }
   
      CED_MarcarTodosEspacosInativos();
      CED_MarcarEspacoAtivo(Lista);

      for(Elemento = Lista->pOrigemLista; Elemento != NULL && Elemento != (tpElemLista*) PONTEIRO_LIXO;  Elemento = Elemento->pProx){
         CED_MarcarEspacoAtivo(Elemento);
         n_elementos++;
               
         if(Elemento->pValor == NULL){
            CNT_CONTAR("LIS_ConteudoNULL");
            falhas++;
         }
         else{
            CED_MarcarEspacoAtivo(Elemento->pValor);
            CNT_CONTAR("VALIDANDO_CAMPO_VALOR");

         }
         if(CED_ObterTipoEspaco(Elemento) != Elemento->tipo){
            CNT_CONTAR("LIS_TipoNoDiferente");
            falhas++;
         }
               
         if(Elemento->pProx == (tpElemLista*)PONTEIRO_LIXO){
            CNT_CONTAR("LIS_ProxElementoLIXO");
            flag_ver_invertido = 1;
            falhas++;
         }
         if(Elemento->pAnt == (tpElemLista*)PONTEIRO_LIXO){
            CNT_CONTAR("LIS_AntElementoLIXO");
            falhas++;
         }

         if(Elemento != Lista->pFimLista && Elemento->pProx == NULL){
            flag_ver_invertido = 1;
            CNT_CONTAR("LIS_ProxElementoNULL");
            falhas++;
         } 
         if(Elemento != Lista->pOrigemLista && Elemento->pAnt == NULL){
            flag_ver_invertido = 1;
            CNT_CONTAR("LIS_AntElementoNULL");
            falhas++;
         }
      }
      if(flag_ver_invertido){
         for (Elemento = Lista->pFimLista; Elemento != NULL && Elemento != (tpElemLista*) PONTEIRO_LIXO;  Elemento = Elemento->pAnt){
            if(!CED_EhEspacoAtivo(Elemento)){
               CED_MarcarEspacoAtivo(Elemento);
               n_elementos++;
               if(Elemento->pValor == NULL){
                  CNT_CONTAR("ILIS_ConteudoNULL");
                  falhas++;
               }
               else{
                  CED_MarcarEspacoAtivo(Elemento->pValor);
                  CNT_CONTAR("IVALIDANDO_CAMPO_VALOR");

               }
               if(CED_ObterTipoEspaco(Elemento) != Elemento->tipo){
                  CNT_CONTAR("ILIS_TipoNoDiferente");
                  falhas++;
               }
               
               if(Elemento->pProx == (tpElemLista*)PONTEIRO_LIXO){
                  CNT_CONTAR("ILIS_ProxElementoLIXO");
                  falhas++;
               }
               if(Elemento->pAnt == (tpElemLista*)PONTEIRO_LIXO){
                  CNT_CONTAR("ILIS_AntElementoLIXO");
                  falhas++;
               } 

               if(Elemento != Lista->pFimLista && Elemento->pProx == NULL){
                  CNT_CONTAR("ILIS_ProxElementoNULL");
                  falhas++;
               } 
               if(Elemento != Lista->pOrigemLista && Elemento->pAnt == NULL){
                  flag_ver_invertido = 1;
                  CNT_CONTAR("ILIS_AntElementoNULL");
                  falhas++;
               }
            }
         }
      }

      num_alocados = CED_ObterNumeroEspacosAlocados();
      CED_InicializarIteradorEspacos();
      for(iterator = 0 ; iterator < num_alocados ; iterator++){
         void* pointer = CED_ObterPonteiroEspacoCorrente();
         int ativo = CED_EhEspacoAtivo(pointer);
         CNT_CONTAR("VERIFICANDO_ESPACOS_ALOCADOS");
         if(!ativo){
            CNT_CONTAR("LIS_VazamentoMemoria");
            falhas++;
         }
         CED_AvancarProximoEspaco();
      }
      if(n_elementos != Lista->numElem){
         CNT_CONTAR("LIS_NumeroErradoDeElementos");
         falhas++;
      }

      CNT_CONTAR("LIS_ListaVerificada");
      return falhas; 
   }

/***********************************************************************
*
*  $FC Fun��o: LIS  -Deturpar Lista
*
***********************************************************************/

   LIS_tpCondRet LIS_DeturparLista(LIS_tppLista Lista, LIS_ModoDeturpacao deturpardorTipo){

      if( Lista == NULL ){
         return LIS_CondRetNaoAchou;
      }

      switch(deturpardorTipo){

      case LIS_EliminarElementoCorrente:
         if(Lista->pElemCorr == NULL){
            return LIS_CondRetOK;
         }
         free(Lista->pElemCorr);
         Lista->pElemCorr = NULL;
         Lista->numElem--;
         break;

      case LIS_AtribuirNULLproxNo:
         if(Lista->pElemCorr == NULL){
            return LIS_CondRetNaoAchou;
         }
         Lista->pElemCorr->pProx = NULL;
         break;

      case LIS_AtribuirNULLantNo:
         if(Lista->pElemCorr == NULL){
            return LIS_CondRetNaoAchou;
         }
         Lista->pElemCorr->pAnt = NULL;
         break;

         case LIS_AtribuirLixoproxNo:
         if(Lista->pElemCorr == NULL){
            return LIS_CondRetNaoAchou;
         }
         Lista->pElemCorr->pProx =(tpElemLista*) PONTEIRO_LIXO;

         break;

         case LIS_AtribuirLixoantNo:
         if(Lista->pElemCorr == NULL){
            return LIS_CondRetNaoAchou;
         }
         Lista->pElemCorr->pAnt =(tpElemLista*) PONTEIRO_LIXO;
         break;

         case LIS_AtribuirNULLcontNo:
         if(Lista->pElemCorr == NULL){
            return LIS_CondRetNaoAchou;
         }
         Lista->pElemCorr->pValor = NULL;
         break;

         case LIS_AlterarTipoNo:
         if(Lista->pElemCorr == NULL){
            return LIS_CondRetNaoAchou;
         }
         Lista->pElemCorr->tipo = TIPO_LIXO;
         break;

         case LIS_DesencadearSemFree:
         if(Lista->pElemCorr == NULL){
            return LIS_CondRetNaoAchou;
         }
         if(Lista->pElemCorr->pAnt != NULL){
            Lista->pElemCorr->pAnt->pProx = Lista->pElemCorr->pProx;
         }
         else{
            Lista->pElemCorr->pProx->pAnt = NULL;
         }

         if(Lista->pElemCorr->pProx!= NULL){
            Lista->pElemCorr->pProx->pAnt = Lista->pElemCorr->pAnt;
         }
         else{
            Lista->pElemCorr->pAnt->pProx = NULL;
         }
         break;

      case LIS_AtribuirNULLcorr:
         Lista->pElemCorr = NULL;
         break;

         case LIS_AtribuirNULLorig:
         Lista->pOrigemLista = NULL;
         break;

      case LIS_MudarNelementos:
         Lista->numElem ++;
         break;

      case LIS_AtribuirNULLfim:
         Lista->pFimLista = NULL;
         break;

      default:
         return LIS_CondRetOK; 
   }
      return LIS_CondRetOK;
}
#endif


/********** Fim do m�dulo de implementa��o: LIS  Lista duplamente encadeada **********/
