/***************************************************************************
*  $MCI Módulo de implementação: Módulo de teste específico
*
*  Arquivo gerado:              TESTTAB.C
*  Letras identificadoras:      TTAB
*
*  Nome da base de software:    Exemplo de teste automatizado
*
*  Projeto: Disciplinas INF 1301
*  Gestor:  DI/PUC-Rio
*  Autores: fbt - Fernando Baggi Tancini
*
*  $HA Histórico de evolução:
*		Versão		Autor		Data     Observações
*		1.0			fbt			06/05	 Criacao
*
*  $ED Descrição do módulo
*     Este modulo contém as funções específicas para o teste do
*     módulo tabuleiro. Ilustra como redigir um interpretador de comandos
*     de teste específicos utilizando o arcabouço de teste para C.
*
*  $EIU Interface com o usuário pessoa
*     Comandos de teste específicos para testar o módulo tabuleiro:
*
*     =criar					- chama a função TAB_CriarTabuleiro( )-
*     =dest						- chama a função TAB_DestruirTabuleiro( )
*     =ins <int1> <int2> <char>	- chama a função 
*									TAB_InsereNPecasCasa(<int2>, <char>, <int1>)
*									sendo os parametros: casa, quantidade de pecas, cor
*									respectivamente
*     =rem <int1> <int2>		- chama a função 
*									TAB_RemoveNPecasCasa(<int1>, <int2>)
*									sendo os parametros: casa, quantidade de pecas
*									respectivamente
*     =nump <int1> <int2>		- chama a função TAB_NumPecasCasa( ) passado a casa <int1>
*									como parametro e compara com <int2>
*     =corp	<int> <char>		- chama a função TAB_CorPecasCasa( ) passando a casa <int>
*									como parametro e compara com <char>
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>

#include    "TST_ESPC.H"
#include    "GENERICO.H"
#include    "LERPARM.H"

#include    "TABULEIRO.H"

/* Tabela dos nomes dos comandos de teste específicos */

#define     CRIAR_TAB_CMD       "=criar"
#define     DEST_TAB_CMD		"=dest"
#define     INS_CMD				"=ins"
#define     REM_CMD				"=rem"
#define     NUM_PECAS_CMD       "=nump"
#define     COR_PECAS_CMD       "=corp"



/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TARV Efetuar operações de teste específicas para árvore
*
*  $ED Descrição da função
*     Efetua os diversos comandos de teste específicos para o módulo
*     árvore sendo testado.
*
*  $EP Parâmetros
*     $P ComandoTeste - String contendo o comando
*
*  $FV Valor retornado
*     Ver TST_tpCondRet definido em TST_ESPC.H
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

      TAB_tpCondRet CondRetObtido   = TAB_CondRetOK ;
      TAB_tpCondRet CondRetEsperada = TAB_CondRetFaltouMemoria ;
                                      /* inicializa para qualquer coisa */

      char ValorEsperado = '?'  ;
      char ValorObtido   = '!'  ;
      char ValorDado     = '\0' ;

      int  NumLidos = -1 ;

      /* Testar TAB Criar Tabuleiro */

         if ( strcmp( ComandoTeste , CRIAR_TAB_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "i" ,
                               &CondRetEsperada ) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = TAB_CriarTabuleiro( ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao criar tabuleiro." );

         } /* fim ativa: Testar TAB Criar Tabuleiro */

      /* Testar TAB Destruir Tabuleiro */

         else if ( strcmp( ComandoTeste , DEST_TAB_CMD ) == 0 )
         {

			TAB_DestruirTabuleiro( ) ;

            return TST_CondRetOK ;

         } /* fim ativa: Testar TAB Destruir Tabuleiro */

      /* Testar TAB Insere N Peças na Casa */

         else if ( strcmp( ComandoTeste , INS_CMD ) == 0 )
         {
			int n, casa;
			char cor;
            NumLidos = LER_LerParametros( "iici" ,
                               &casa, &n, &cor, &CondRetEsperada ) ;
            if ( NumLidos != 4 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = TAB_InsereNPecasCasa( n, cor, casa ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao inserir pecas numa casa." );

         } /* fim ativa: Testar TAB Insere N Peças na Casa */

       /* Testar TAB Remove N Peças na Casa */

         else if ( strcmp( ComandoTeste , REM_CMD ) == 0 )
		 {
			int n, casa;
            NumLidos = LER_LerParametros( "iii" ,
                               &casa, &n, &CondRetEsperada ) ;
            if ( NumLidos != 3 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = TAB_RemoveNPecasCasa( n, casa ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao remover pecas de uma casa" );

         } /* fim ativa: Testar TAB Remove N Peças na Casa */

      /* Testar TAB Num Peças da Casa */

         else if ( strcmp( ComandoTeste , NUM_PECAS_CMD ) == 0 )
         {
			int casa, n, nEsperado;
			TST_tpCondRet ret;
            NumLidos = LER_LerParametros( "ii" ,
                               &casa, &nEsperado ) ;
            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = TAB_NumPecasCasa(casa, &n) ;
			
            ret = TST_CompararInt( TAB_CondRetOK , CondRetObtido ,
                                    "Retorno errado ao obter numero de pecas na casa." );

			if (ret != TST_CondRetOK)
			{
				return ret;
			} /* if */

            return TST_CompararInt( nEsperado , n ,
                                     "Numero de pecas esperado e retornado diferentes." ) ;

         } /* fim ativa: Testar TAB Num Peças da Casa */

      /* Testar TAB Cor Peças da Casa */

         else if ( strcmp( ComandoTeste , COR_PECAS_CMD ) == 0 )
         {
			int casa;
			char corEsperada, cor;
			TST_tpCondRet ret;
            NumLidos = LER_LerParametros( "ic" ,
                               &casa, &corEsperada ) ;
            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = TAB_CorPecasCasa( casa, &cor ) ;

            ret = TST_CompararInt( TAB_CondRetOK , CondRetObtido ,
                                    "Retorno errado ao obter a cor das pecas da casa." );

			if (ret != TST_CondRetOK)
			{
				return ret;
			} /* if */

            return TST_CompararChar( corEsperada , cor ,
                                     "Cor das pecas esperado e retornado diferentes." ) ;

         } /* fim ativa: Testar TAB Cor Peças da Casa */

      return TST_CondRetNaoConhec ;

   } /* Fim função: TARV Efetuar operações de teste específicas para árvore */

/********** Fim do módulo de implementação: Módulo de teste específico **********/

