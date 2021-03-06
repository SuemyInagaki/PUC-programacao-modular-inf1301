/***************************************************************************
*  $MCI M�dulo de implementa��o:  Teste dado 
*
*  Arquivo gerado:                TestDado.c
*  Letras identificadoras:        TSTD
*
*  Projeto:                       INF 1301

*  Autores:                       jfr J�lia Affonso Figueiredo Rocha
*
* $HA Hist�rico e evolu��o:
*   Vers�o  Autor	Data		Observa��es
*   1.00	jfr		05/05/2019  Implementa��o do teste
*
***************************************************************************
*  Comandos Espec�ficos para testar o m�dulo	Dado.c
*
*       =jogar         chama a fun��o  DAD_Jogar
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>

#include    "TST_ESPC.H"
#include    "GENERICO.H"
#include    "LERPARM.H"

#include    <malloc.h>
#include    "DADO.h"

/* Tabela dos nomes dos comandos de teste espec�ficos */

static const char CMD_JOGAR       [] = "=jogar" ;


/*****  C�digo das fun��es exportadas pelo m�dulo  *****/


/***********************************************************************
*
*  $FC Fun��o: TPEC Efetuar opera��es de teste espec�ficas para dado
*
*  $ED Descri��o da fun��o
*     Efetua os diversos comandos de teste espec�ficos para o m�dulo
*     dado sendo testado.
*
*  $EP Par�metros
*     $P ComandoTeste - String contendo o comando
*
*  $FV Valor retornado
*     Ver TST_tpCondRet definido em TST_ESPC.H
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste ) {

      DAD_tpCondRet CondRetObtido   = DAD_CondRetOK ;
      DAD_tpCondRet CondRetEsperada = DAD_CondRetFaltouMemoria ;
                                      /* inicializa para qualquer coisa */

      char ValorEsperado = '?'  ;
      char ValorObtido   = '!'  ;
      char ValorDado     = '\0' ;
	  int numero;
      int  NumLidos = -1 ;

      /* Testar DAD Jogar */

         if ( strcmp( ComandoTeste , CMD_JOGAR ) == 0 ) {

            NumLidos = LER_LerParametros( "i" ,
                               &CondRetEsperada ) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = DAD_Jogar(&numero) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao jogar dado." );

         } /* fim ativa: Testar DAD jogar dado */

      return TST_CondRetNaoConhec ;

   } /* Fim fun��o: TSTP Efetuar opera��es de teste espec�ficas para dado */

/********** Fim do m�dulo de implementa��o: M�dulo de teste espec�fico **********/
