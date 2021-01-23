/***************************************************************************
*  $MCI Módulo de implementação: Módulo de teste específico DPTS
*
*  Arquivo gerado:              TestDadoPontos.C
*  Letras identificadoras:      TDPTS
*
*  Projeto: Disciplinas INF 1301
*  Gestor:  DI/PUC-Rio
*
*	Autores:	sipf - Suemy Inagaki Pinheiro Fagundes
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data		 Observações
*       1.00   sipf   09/05/2019       Desenvolvimento
*
*  $ED Descrição do módulo
*     Este módulo testa utilizando as funções específicas do
*     módulo de DadoPontos
*
*
*
*  $EIU Interface com o usuário pessoa
*     Comandos de teste específicos para testar o módulo peca:
*
*       =criardadopontos         chama a função  DPTS_CriarDadoPontos
*	=destruirdadopontos      chama a função  DPTS_DestruirDadoPontos
*	=jogadordobraatualiza    chama a função  DPTS_JogadorDobraAtualiza
*	=dobrarpontuacao         chama a função  DPTS_DobrarPontuacaoAtual
*	=obterjogadordobrapts    chama a função  DPTS_ObterJogadorDobraPonto
*	=obterpontuacaopartida   chama a função  DPTS_ObterPontuacaoPartida
*
***************************************************************************/


#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_ESPC.H"

#include    "GENERICO.H"
#include    "LERPARM.H"

#include    "p2.h"

/* Tabela dos nomes dos comandos de teste específicos */

#define VERMELHA  0
#define PRETA     1

#define CERTO     1
#define ERRADO    0

static const char CMD_CRIAR_LISTA_PECAS_Capturadas      [] = "=criarlistapecasCapturadas" ;
static const char CMD_INSERIR_PECA                       [] = "=inserirpeca";
static const char CMD_CONTAR_PECAS                       [] = "=contarpecas";
static const char CMD_DESTRUIR_LISTA_PECAS_Capturadas   [] = "=destruirlistapecasCapturadas";
static const char CMD_REMOVER_PECA [] = "=removerpeca";

static BAR_tpPecasCapturadas pCapturadas = NULL;


/***********************************************************************
*
*  $FC Função: TDPTS Realizar Testes Específicas para DadoPonto
*
*  $ED Descrição da função
*     Efetua os comandos de teste específicos para o módulo DadoPontos
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
        BAR_tpCondRet CondRetObtido   = BAR_OK;
        BAR_tpCondRet CondRetEsperado = BAR_SemMemoria;
                                      /* inicializa para qualquer coisa */

      /* Testar Criar Dado Pontos*/
  if(strcmp(ComandoTeste , CMD_INSERIR_PECA) == 0){
        numLidos = LER_LerParametros("i" , &CondRetEsperado);
        if(numLidos != 1)
               return TST_CondRetParm;   
        CondRetObtido = BAR_InserirPeca(pCapturadas, peca);
        return TST_CompararInt(CondRetEsperado , CondRetObtido, "Erro ao inserir pecas");
  } /* fim ativa: Testar Destruir Dado de Pontos */

	else if(strcmp(ComandoTeste , CMD_CRIAR_LISTA_PECAS_Capturadas) == 0){
        numLidos = LER_LerParametros("i", &CondRetEsperado);
	      if(numLidos != 1)
              return TST_CondRetParm;
        CondRetObtido = BAR_CriarListaPecasCapturadas(&pCapturadas);
        return TST_CompararInt(CondRetEsperado , CondRetObtido, "Erro ao criar lista de pecas Capturadas");
  } /* fim ativa: Testar Criar Dado de Pontos */

	/* Testar Destruir Dado de Pontos */

	/* Testar Atualizar jogador de dobra */
  else if(strcmp(ComandoTeste ,CMD_CONTAR_PECAS ) == 0){
        numLidos = LER_LerParametros("ii" , &CorPeca, &CondRetEsperado);
        if(numLidos != 2)
               return TST_CondRetParm; 
        CondRetObtido = BAR_ContarPecas(pCapturadas, CorPeca, &contagem);
        return TST_CompararInt(CondRetEsperado , CondRetObtido, "Erro ao contar pecas.");
  } /* fim ativa: Testar Atualizar jogador de dobra */
	
	/* Testar Dobrar pontuação da partida */
  else if(strcmp(ComandoTeste , CMD_DESTRUIR_LISTA_PECAS_Capturadas) == 0){
        numLidos = LER_LerParametros("i" , &CondRetEsperado);
        if(numLidos != 1)
               return TST_CondRetParm;
   	    CondRetObtido = BAR_DestruirListaPecasCapturadas(&pCapturadas);
        return TST_CompararInt(CondRetEsperado , CondRetObtido, "Erro ao destruir lista de pecas Capturadas");
  } /* fim ativa: Dobrar pontuação da partida */
        /* Testar Obter jogador dobra partida */
  else if(strcmp(ComandoTeste , CMD_REMOVER_PECA) == 0){
        numLidos = LER_LerParametros("i" , &CondRetEsperado);
        if(numLidos != 1)
               return TST_CondRetParm;
        CondRetObtido = BAR_RemoverPeca(pCapturadas, cor);
		return TST_CompararInt(CondRetEsperado , CondRetObtido, "Erro ao remover pecas Capturadas");
  }  
      return TST_CondRetNaoConhec;

   }/* fim função: TDPTS Realizar Testes Específicas para DadoPonto */
	
/********** Fim do módulo de implementação: TDPTS Teste dado pontos **********/
