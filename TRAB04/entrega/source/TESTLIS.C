/***************************************************************************
*  $MCI Módulo de implementação: TLIS Teste lista de símbolos
*
*  Arquivo gerado:              TestLIS.c
*  Letras identificadoras:      TLIS
*
*  Nome da base de software:    Arcabouçoo para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs
*           sipf - suemy inagaki pinheiro fagundes
*           jfr  - júlia afonso figueiredo rocha
*           ft   - fernando tancini
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     7       ft    01/jul/2019 comentários
*     6       jfr   01/jul/2019 algumas correções
*     5       sipf  30/jun/2019 inicio da implementação da adaptação do teste
*     4       avs   01/fev/2006 criar linguagem script simbólica
*     3       avs   08/dez/2004 uniformização dos exemplos
*     2       avs   07/jul/2003 unificação de todos os módulos em um só projeto
*     1       avs   16/abr/2003 início desenvolvimento
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"
#include    "Generico.h"
#include    "LerParm.h"
#include    "Lista.h"



#ifdef _DEBUG
  #include "CESPDIN.H"
  #include "IdTiposEspaco.def"  
#endif


static const char RESET_LISTA_CMD         [ ] = "=resetteste"     ;
static const char CRIAR_LISTA_CMD         [ ] = "=criarlista"     ;
static const char DESTRUIR_LISTA_CMD      [ ] = "=destruirlista"  ;
static const char ESVAZIAR_LISTA_CMD      [ ] = "=esvaziarlista"  ;
static const char INS_ELEM_ANTES_CMD      [ ] = "=inselemantes"   ;
static const char INS_ELEM_APOS_CMD       [ ] = "=inselemapos"    ;
static const char OBTER_VALOR_CMD         [ ] = "=obtervalorelem" ;
static const char EXC_ELEM_CMD            [ ] = "=excluirelem"    ;
static const char IR_INICIO_CMD           [ ] = "=irinicio"       ;
static const char IR_FIM_CMD              [ ] = "=irfinal"        ;
static const char AVANCAR_ELEM_CMD        [ ] = "=avancarelem"    ;


#ifdef _DEBUG
  static const char DETURPAR      [] = "=deturparlista" ; 
  static const char VERIFICAR_LISTA [] = "=verificarlista"  ;
  static const char VERIFICAR_MEM   [] = "=verificarmem"  ;
  static const char LIBERAR_TUDO    [] = "=liberartudo"   ;
#endif

#define VERDADE  1
#define FALSO 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIMENSAO_LISTA  11
#define DIMENSAO_VALOR     100




LIS_tppLista   vtListas[ DIMENSAO_LISTA] ;

/***** Protótipos das funções encapuladas no módulo *****/

   static void DestruirValor( void * pValor ) ;

   static int ValidarLista( int indList , int Modo ) ;
   
   #ifdef _DEBUG
   static int ValidarListaDebug( int ind);
   #endif

/***********************************************************************
*
*  $FC Função: TLIS &Testar lista
*
*  $ED Descrição da fun��o
*     Podem ser criadas at� 10 listas, identificadas pelos �ndices 0 a 10
*
*     Comandos dispon�veis:
*
*     =resetteste
*           - anula o vetor de listas. Provoca vazamento de mem�ria
*     =criarlista                   indList
*     =destruirlista                indList
*     =esvaziarlista                indList
*     =inselemantes                 indList  string  CondRetEsp
*     =inselemapos                  indList  string  CondRetEsp
*     =obtervalorelem               indList  string  CondretPonteiro
*     =excluirelem                  indList  CondRetEsp
*     =irinicio                     indList
*     =irfinal                      indList
*     =avancarelem                  indList  numElem CondRetEsp
*
***********************************************************************/


   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

      int indList  = -1 ,
          CondRetEsp = -1 ,
          ValEsp = -1,
          numElem = -1,
          numLidos   = -1;
      int i ;
      TST_tpCondRet CondRet ;

      char   strDado[  DIMENSAO_VALOR ];
	  char * pDado;
	  strDado[ 0 ] = 0;

      /* Efetuar reset de teste de lista */

         if ( strcmp( ComandoTeste , RESET_LISTA_CMD ) == 0 )
         {
            for( i = 0 ; i < DIMENSAO_LISTA; i++ )
               vtListas[ i ] = NULL ;
            return TST_CondRetOK ;
         } /* fim ativa: Efetuar reset de teste de lista */

      /* Testar CriarLista */
         else if ( strcmp( ComandoTeste , CRIAR_LISTA_CMD ) == 0 )
         {
            numLidos = LER_LerParametros( "i" , &indList ) ;
           
            if ( ( numLidos != 1 ) || ( ! ValidarLista( indList , VAZIO )))
               return TST_CondRetParm ;
           
            vtListas[ indList ] = LIS_CriarLista( DestruirValor ) ;
            return TST_CompararPonteiroNulo( 1 , vtListas[ indList ] , "Erro no ponteiro da lista nova"  ) ;
         } /* fim ativa: Testar CriarLista */

     
      /* Testar Destruir lista */
         else if ( strcmp( ComandoTeste , DESTRUIR_LISTA_CMD ) == 0 )
         {
            numLidos = LER_LerParametros( "i" , &indList ) ;

            if ( ( numLidos != 1 ) || ( ! ValidarLista( indList , NAO_VAZIO )))
               return TST_CondRetParm ;

            LIS_DestruirLista( vtListas[ indList ] ) ;
            vtListas[ indList ] = NULL ;
            return TST_CondRetOK ;
         } /* fim ativa: Testar Destruir lista */

      /* Testar inserir elemento antes */

         else if ( strcmp( ComandoTeste , INS_ELEM_ANTES_CMD ) == 0 )
         {
            numLidos = LER_LerParametros( "isi" , &indList , strDado , &CondRetEsp ) ;

            if ( ( numLidos != 3 )|| ( ! ValidarLista( indList , NAO_VAZIO )) )
               return TST_CondRetParm ;
           
            pDado = ( char * ) malloc( strlen( strDado ) + 1 ) ;
           
            if ( pDado == NULL )
               return TST_CondRetMemoria ;

            strcpy( pDado , strDado ) ;

           CondRet = LIS_InserirElementoAntes( vtListas[ indList ] , pDado ) ;

            if ( CondRet != LIS_CondRetOK )
               free( pDado ) ;
            return TST_CompararInt( CondRetEsp , CondRet ,"Condição de retorno inesperada - inserir antes" ) ;

         } /* fim ativa: Testar inserir elemento antes */

      /* Testar inserir elemento apos */

         else if ( strcmp( ComandoTeste , INS_ELEM_APOS_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "isi" , &indList , strDado , &CondRetEsp ) ;

            if ( ( ! ValidarLista( indList , NAO_VAZIO )) || ( numLidos != 3 ))
               return TST_CondRetParm ;
           
            pDado = ( char * ) malloc( strlen( strDado ) + 1 ) ;
            if ( pDado == NULL )
               return TST_CondRetMemoria ;

            strcpy( pDado , strDado ) ;

            CondRet = LIS_InserirElementoApos( vtListas[ indList ] , pDado ) ;

            if ( CondRet != LIS_CondRetOK )
               free( pDado ) ;

            return TST_CompararInt( CondRetEsp , CondRet , "Condicao de retorno inesperada - inserir apos") ;
         } /* fim ativa: Testar inserir elemento apos */

      /* Testar excluir simbolo */

         else if ( strcmp( ComandoTeste , EXC_ELEM_CMD ) == 0 )
         {
             numLidos = LER_LerParametros( "ii" , &indList , &CondRetEsp ) ;

            if ( ( numLidos != 2 ) || ( ! ValidarLista( indList , NAO_VAZIO )) )
               return TST_CondRetParm ;

            return TST_CompararInt( CondRetEsp , LIS_ExcluirElemento( vtListas[ indList ] ) , "Condicao de retorno inesperada - excluir" ) ;
         } /* fim ativa: Testar excluir simbolo */

      /* Testar obter valor do elemento corrente */

         else if ( strcmp( ComandoTeste , OBTER_VALOR_CMD ) == 0 )
         {
            numLidos = LER_LerParametros( "isi" ,
                       &indList , strDado , &ValEsp ) ;

            if ( ( numLidos != 3 )|| ( ! ValidarLista( indList , NAO_VAZIO )) )
               return TST_CondRetParm ;

            pDado = ( char * ) LIS_ObterValor( vtListas[ indList ] ) ;

            if ( ValEsp == 0 )
               return TST_CompararPonteiroNulo( 0 , pDado ,"ERRO: O valor nao deveria existir." ) ;

            if ( pDado == NULL )
               return TST_CompararPonteiroNulo( 1 , pDado , "ERRO: Deveria existir dado tipo um" ) ;

            return TST_CompararString( strDado , pDado , "ERRO: O valor do elemento esta errado" ) ;

         } /* fim ativa: Testar obter valor do elemento corrente */

      /* Testar ir para o elemento inicial */

         else if ( strcmp( ComandoTeste , IR_INICIO_CMD ) == 0 )
         {
            numLidos = LER_LerParametros( "i" , &indList ) ;

            if ( ( numLidos != 1 )|| ( ! ValidarLista( indList , NAO_VAZIO )) )
               return TST_CondRetParm ;

            IrInicioLista( vtListas[ indList ] ) ;
            return TST_CondRetOK ;
         } /* fim ativa: Testar ir para o elemento inicial */

      /* LIS  &Ir para o elemento final */

         else if ( strcmp( ComandoTeste , IR_FIM_CMD ) == 0 )
         {
            numLidos = LER_LerParametros( "i" , &indList ) ;

            if ( ( numLidos != 1 ) || ( ! ValidarLista( indList , NAO_VAZIO )) )
               return TST_CondRetParm ;

            IrFinalLista( vtListas[ indList ] ) ;
            return TST_CondRetOK ;

         } /* fim ativa: LIS  &Ir para o elemento final */

      /* LIS  Avancar elemento */

         else if ( strcmp( ComandoTeste , AVANCAR_ELEM_CMD ) == 0 )
         {
            numLidos = LER_LerParametros( "iii" , &indList , &numElem ,
                                &CondRetEsp ) ;

            if ( ( numLidos != 3 )|| ( ! ValidarLista( indList , NAO_VAZIO )) )
               return TST_CondRetParm ;

            return TST_CompararInt( CondRetEsp ,
                      LIS_AvancarElementoCorrente( vtListas[ indList ] , numElem ) , "Condicao de retorno inesperada - avancar" ) ;
         } /* fim ativa: LIS  &Avan�ar elemento */

     /* Testar Esvaziar lista lista */

         else if ( strcmp( ComandoTeste , ESVAZIAR_LISTA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" ,
                               &indList ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarLista( indList , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            LIS_EsvaziarLista( vtListas[ indList ] ) ;

            return TST_CondRetOK ;

         } /* fim ativa: Testar Esvaziar lista lista */

#ifdef _DEBUG
    else if ( strcmp( ComandoTeste , DETURPAR ) == 0 ){
      LIS_tpCondRet ret_obt;
      LIS_tpCondRet ret_esp;
      LIS_ModoDeturpacao dtp_type;

      numLidos = LER_LerParametros( "iii", &indList ,&dtp_type,&ret_esp);
      if(numLidos != 3 || !ValidarListaDebug(indList)){
        return TST_CondRetParm ;
      }

      ret_obt = LIS_DeturparLista(vtListas[ indList ] , dtp_type) ;
      return TST_CompararInt(ret_esp, ret_obt, "Condicao de retorno inesperado");
    }
    else if ( strcmp( ComandoTeste, VERIFICAR_LISTA) == 0){
      int error_esp;
      int error_obt;
      numLidos = LER_LerParametros("iii", &indList, &error_esp);

      if(numLidos != 2 || !ValidarListaDebug(indList)){
        return TST_CondRetParm;
      }
      error_obt =  LIS_VerificarLista(vtListas[ indList ]);

      return TST_CompararInt(error_esp,error_obt, "ERRO: Numero de erros nao confere");
    }
    else if( strcmp ( ComandoTeste, VERIFICAR_MEM ) == 0){
      CED_ExibirTodosEspacos(CED_ExibirTodos);
      return TST_CondRetOK ;
    }

    else if( strcmp( ComandoTeste, LIBERAR_TUDO ) == 0) {
      int idx;
      int tot = CED_ObterNumeroEspacosAlocados();
      CED_InicializarIteradorEspacos();

      for(idx = 0 ; idx < tot ; idx ++){
        CED_ExcluirEspacoCorrente();
      }
      for(idx = 0 ; idx < tot ; idx ++){
        vtListas[idx] = NULL;
      }
      return TST_CondRetOK;
    }
    
#endif
      return TST_CondRetNaoConhec ;

   } /* Fim fun��o: TLIS &Testar lista */


/*****  C�digo das fun��es encapsuladas no m�dulo  *****/


/***********************************************************************
*
*  $FC Fun��o: TLIS -Destruir valor
*
***********************************************************************/

   void DestruirValor( void * pValor )
   {

      free( pValor ) ;

   } /* Fim fun��o: TLIS -Destruir valor */


/***********************************************************************
*
*  $FC Fun��o: TLIS -Validar indice de lista
*
***********************************************************************/

   int ValidarLista( int indList , int Modo )
   {

      if ( ( indList <  0 )
        || ( indList >= DIMENSAO_LISTA))
      {
         return FALSO ;
      } /* if */
         
      if ( Modo == VAZIO )
      {
         if ( vtListas[ indList ] != 0 )
         {
            return FALSO ;
         } /* if */
      } else
      {
         if ( vtListas[ indList ] == 0 )
         {
            return FALSO ;
         } /* if */
      } /* if */
         
      return VERDADE ;

   } /* Fim fun��o: TLIS -Validar indice de lista */
   
#ifdef _DEBUG

   int ValidarListaDebug( int ind){
     if( ind >= DIMENSAO_LISTA|| ind < 0 ){
       return FALSO;
     }
     return VERDADE;
   }

#endif


/********** Fim do m�dulo de implementa��o: TLIS Teste lista de s�mbolos **********/



