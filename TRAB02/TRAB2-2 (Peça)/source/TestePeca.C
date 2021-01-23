/***************************************************************************
*  $MCI Módulo de implementação:  Teste Peca
*
*  Arquivo gerado:                TestePeca.c
*  Letras identificadoras:        TSTP
*
*  Projeto:                       INF 1301

*  Autores:                       jfr Júlia Affonso Figueiredo Rocha
*
* $HA Histórico e evolução:
*   Versão  Autor	Data		Observações
*   1.00	jfr		05/05/2019  Implementação do teste
*
/ ****************************************************************************
*  Comandos Específicos para testar o módulo	Peca.c
*       =criaPeca         chama a função  PEC_CriarPeca
*		=destruirPeca	  chama a função  PEC_DestruirPeca
*		=obtemCor		  chama a função  PEC_ObterCor
*
/***************************************************************************/



#include    <string.h>
#include    <stdio.h>

#include    "TST_ESPC.H"
#include    "GENERICO.H"
#include    "LERPARM.H"
#include    "PECA.h"

/* Tabela dos nomes dos comandos de teste específicos */

static const char CMD_CRIAR_PECA       [] = "=criaPeca" ;
static const char CMD_DESTRUIR_PECA    [] = "=destruirPeca";
static const char CMD_OBTER_COR  [] = "=obtemCor";


/*****  Dados encapsulados no módulo  *****/

	static tppPeca Peca = NULL ;
				/* Ponteiro para o tabuleiro */

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TPEC Efetuar operações de teste específicas para peca
*
*  $ED Descrição da função
*     Efetua os diversos comandos de teste específicos para o módulo
*     peca sendo testado.
*
*  $EP Parâmetros
*     $P ComandoTeste - String contendo o comando
*
*  $FV Valor retornado
*     Ver TST_tpCondRet definido em TST_ESPC.H
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste ) {

      PEC_tpCondRet CondRetObtido   = PEC_CondRetOK ;
      PEC_tpCondRet CondRetEsperada = PEC_CondRetFaltouMemoria ;
                                      /* inicializa para qualquer coisa */

      char ValorEsperado = '?'  ;
      char ValorObtido   = '!'  ;
      char ValorDado     = '\0' ;
	  char corEsperada;
	  char cor;
      int  NumLidos = -1 ;

      /* Testar PEC Criar Peca */

         if ( strcmp( ComandoTeste , CMD_CRIAR_PECA ) == 0 ) {

            NumLidos = LER_LerParametros( "ci", &cor,
                               &CondRetEsperada ) ;
            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = PEC_CriarPeca(&Peca, cor) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao criar peca." );

         } /* fim ativa: Testar PEC Criar peca */

      /* Testar PEC Destruir peca */

         else if ( strcmp( ComandoTeste , CMD_DESTRUIR_PECA ) == 0 ) {

            PEC_DestruirPeca(Peca) ;

            return TST_CondRetOK ;

         } /* fim ativa: Testar PEC Destruir peca */

	  /* Testar PEC Obter Cor */

         else if ( strcmp( ComandoTeste , CMD_OBTER_COR ) == 0 ) {

			TST_tpCondRet ret;
            NumLidos = LER_LerParametros( "ci", &corEsperada,
                               &CondRetEsperada ) ;
            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = PEC_ObterCor(Peca, &cor) ;

            ret = TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao obter cor." );
			if (ret != TST_CondRetOK)
			{
				return ret;
			} /* if */
			return TST_CompararChar(corEsperada, cor,
									"Cor esperada diferente da cor retornada.");

         } /* fim ativa: Testar PEC Obter cor */

      return TST_CondRetNaoConhec ;

   } /* Fim função: TSTP Efetuar operações de teste específicas para peca */

/********** Fim do módulo de implementação: Módulo de teste específico **********/


