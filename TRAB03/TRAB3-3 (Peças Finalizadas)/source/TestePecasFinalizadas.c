/***************************************************************************
*  $MCI Módulo de implementação: Módulo de teste específico DPTS
*
*  Arquivo gerado:              TestePecasFinalizadas.C
*  Letras identificadoras:      TPFZ
*
*  Projeto: Disciplinas INF 1301
*  Gestor:  DI/PUC-Rio
*
*	Autores:	sipf - Suemy Inagaki Pinheiro Fagundes
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data		 Observações
*       1.00   sipf   09/06/2019       Desenvolvimento
*
*  $ED Descrição do módulo
*     Este módulo testa utilizando as funções específicas do
*     módulo de PecasFinalizadas
*
*
*
***************************************************************************/


#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_ESPC.H"

#include    "GENERICO.H"
#include    "LERPARM.H"

#include    "PecasFinalizadas.h"

/* Tabela dos nomes dos comandos de teste específicos */

#define VERMELHA  0
#define PRETA     1

#define CERTO     1
#define ERRADO    0

static const char CMD_CRIAR_LISTA_PECAS_FINALIZADAS      [] = "=criarlistapecasfinalizadas" ;
static const char CMD_INSERIR_PECA                       [] = "inserirpeca";
static const char CMD_CONTAR_PECAS                       [] = "=contarpecas";
static const char CMD_DESTRUIR_LISTA_PECAS_FINALIZADAS   [] = "=destruirlistapecasfinalizadas";

static PFZ_tpPecasFinalizadas pfinalizadas = NULL;


/***********************************************************************
*
*  $FC Função: TDPTS Realizar Testes Específicas para PecasFinalizadas
*
*  $ED Descrição da função
*     Efetua os comandos de teste específicos para o módulo PecasFinalizadas
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
	 
	      int     numLidos     = -1,
                  contagem     = -1,
                  valEsp       = -1;
        PEC_CorDaPeca CorPeca;
        tppPeca peca;
		PEC_CorDaPeca cor = PEC_corVermelha;
		PEC_tpCondRet ret = PEC_CriarPeca(&(peca),cor);
        //TST_tpCondRet CondRetTesteEsperado;
        PFZ_tpCondRet CondRetObtido   = PFZ_OK;
        PFZ_tpCondRet CondRetEsperado = PFZ_SemMemoria;
                                      /* inicializa para qualquer coisa */

      /* Testar Criar Lista de Pecas Finalizadas*/

	if(strcmp(ComandoTeste , CMD_CRIAR_LISTA_PECAS_FINALIZADAS) == 0){
        numLidos = LER_LerParametros("i", &CondRetEsperado);
	      if(numLidos != 1)
              return TST_CondRetParm;
        CondRetObtido = PFZ_CriarListaPecasFinalizadas(&pfinalizadas);
        return TST_CompararInt(CondRetEsperado , CondRetObtido, "Erro ao criar lista de pecas finalizadas");
  } /* fim ativa: Testar Criar Lista de Pecas Finalizadas */

	/* Testar Inserir Pecas */
  else if(strcmp(ComandoTeste , CMD_INSERIR_PECA) == 0){
        numLidos = LER_LerParametros("i" , &CondRetEsperado);
        if(numLidos != 1)
               return TST_CondRetParm;   
	      CondRetObtido = PFZ_InserirPeca(pfinalizadas, peca);
        return TST_CompararInt(CondRetEsperado , CondRetObtido, "Erro ao inserir pecas");
  } /* fim ativa: Testar Inserir pecas */

	/* Testar Contar Peca */
  else if(strcmp(ComandoTeste ,CMD_CONTAR_PECAS ) == 0){
        numLidos = LER_LerParametros("ii" , &CorPeca, &CondRetEsperado);
        if(numLidos != 2)
               return TST_CondRetParm; 
        CondRetObtido = PFZ_ContarPecas(pfinalizadas, CorPeca, &contagem);
        return TST_CompararInt(CondRetEsperado , CondRetObtido, "Erro ao contar pecas.");
  } /* fim ativa: Testar Contar Peca */
	
	/* Testar Destruir Lista de Pecas */
  else if(strcmp(ComandoTeste , CMD_DESTRUIR_LISTA_PECAS_FINALIZADAS) == 0){
        numLidos = LER_LerParametros("i" , &CondRetEsperado);
        if(numLidos != 1)
               return TST_CondRetParm;
   	    CondRetObtido = PFZ_DestruirListaPecasFinalizadas(&pfinalizadas);
        return TST_CompararInt(CondRetEsperado , CondRetObtido, "Erro ao destruir lista de pecas finalizadas");
  } /* fim ativa: Destruir Lista de Pecas */  
      return TST_CondRetNaoConhec;

   }/* fim função: TDPTS Realizar Testes Específicas para PecasFinalizadas */
	
/********** Fim do módulo de implementação: TPFZ Teste de Pecas Finalizadas **********/
