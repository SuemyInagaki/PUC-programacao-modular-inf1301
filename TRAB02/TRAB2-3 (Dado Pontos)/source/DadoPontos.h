#if ! defined(DadoPontos_)
#define DadoPontos_

#include "PECA.h"
/*******************************************************************************************
* $MCI Módulo de definição: Módulo dado pontos
* Arquivo gerado:     DadoPontos.h
* Letras identificadoras:   DPTS
*
* Projeto:            Disciplina INF 1301
*
*   Autor:                    sipf - Suemy Inagaki Pinheiro Fagundes
*
* $HA Histórico de evolução:
* Versão  Autor    Data     Observações
* 1.03    sipf   11/05/2019  Refiz as assertivas de entrada e saída
* 1.02    sipf   10/05/2019  Refiz o código todo para mudar a estrutura de dadopontos
* 1.01    sipf   09/05/2019  Assertivas das funções adicionadas
* 1.00    sipf   30/abr/2019 Desenvolvimento
*
*       $ED Descrição do módulo
*       Define as Funções de DadoPontos.
* No início de cada partida não existe dado de pontos
*
*****************************************************************************************/

#if defined(DadoPontos_OWN)
   #define DadoPontos_EXT
#else
   #define DadoPontos_EXT extern
#endif


/************************ Declarações exportadas pelo módulo ****************************/


/* Tipo de referência para um dado de pontos*/

typedef struct DPTS_tpDadoPontos* DPTS_DadoPCabeca;

/******************************************************************************************
*
*  $TC Tipo de dados: DPTS Condicao de Retorno
*
*
****************************************************************************************/

typedef enum {
     DPTS_FaltouMemoria = -1,
          /* Faltou  memoria ao tentar alocar */

         DPTS_Feito = 0,
          /* Dado Criado corretamente */

   DPTS_DadoPontosNaoExiste = 1,
    /* Dado de pontos não existe */

   DPTS_JogadorNaoTemDadoPontos = 2,
    /* Jogador não tem dado de pontos no momento */

   DPTS_NaoExisteJogadorComDadoPontos = 3,
    /* Não existe jogador atual com dado de pontos */

 }DPTS_CondRet;


 /*****************************************************************************************
*
*  $FC Função: DPTS Criar Dado Pontos
*
*  $ED Descrição da função
*     Cria um dado de pontos.
*
*  $EP Parâmetros
*     $P pDadoPontos - Ponteiro para a cabeça de dadopontos
*
*  $FV Valor retornado
*     DPTS_Feito
*     DPTS_FaltouMemoria
*
*  Assertivas de Entrada: Deve existir um ponteiro do tipo DPTS_DadoPCabeca passado como parâmetro que 
*                         receberá o dado criado na função 
*  Assertivas de Saída: Um dado de pontos é criado e passado para o ponteiro recebido. 
*
*****************************************************************************************/

DPTS_CondRet DPTS_CriarDadoPontos(DPTS_DadoPCabeca *pDadoPontos);

/*****************************************************************************************
*
*  $FC Função: DPTS Jogador Dobra Atualiza
*
*  $ED Descrição da função
*     Atualiza o jogador que pode dobrar a pontuacao da partida.
*
*  $EP Parâmetros
*     $P pDadoPontos - ponteiro para a cabeca do tipo DPTS_DadoPCabeca
*     $P CorPeca - char que representa a cor do jogador.
*
*  $FV Valor retornado
*     DPTS _Feito
*     DPTS_DadoPontosNaoExiste
*
*  Assertivas de Entrada: - Deve ter um ponteiro para a cabeca de dado de pontos que indica a dobra.
*                         - Deve ter um char que representa a cor do jogador
*  Assertivas de Saída: A cor do jogador que pode dobrar a pontuacao é atulizada.
*
******************************************************************************************/

DPTS_CondRet DPTS_JogadorDobraAtualiza(DPTS_DadoPCabeca pDadoPontos, char CorPeca);

/*****************************************************************************************
*
*  $FC Função: DPTS Dobrar pontuação Atual
*
*  $ED Descrição da função
*     Dobra o valor da pontuação da partida.
*
*  $EP Parâmetros
*     $P pDadoPontos - ponteiro para a cabeca de dado de pontos.
*     $P CorPeca - char que representa a cor do jogador.
*
*  $FV Valor retornado
*     DPTS_Feito
*     DPTS_DadoPontosNaoExiste
*     DPTS_JogadorNaoTemDadoPontos
*
*  Assertivas de Entrada: - Deve ter um ponteiro para a cabeca de dado de pontos que sera utilizado;
*  Assertivas de Saída:   - Se dado pontos não existir ou cor da peça não for igual a cor que pode
*                           dobrar a pontuação o ponteiro pDadoPontos não é atualizado
*                         - Caso contrário, a pontuação é dobrada e o ponteiro é atualizado
******************************************************************************************/

DPTS_CondRet DPTS_DobrarPontuacaoAtual(DPTS_DadoPCabeca pDadoPontos, char CorPeca);

/*****************************************************************************************
*
*  $FC Função: DPTS Obter jogador Dobra Ponto
*
*  $ED Descrição da função
*     Obtém o jogador que pode dobrar a pontuacao da partida.
*
*  $EP Parâmetros
*     $P pDadoPontos - ponteiro para a cabeca dado de pontos.
*     $P pCorPeca - ponteiro que vai obter por referencia a cor do jogador que pode dobrar a pontuacao da partida.
*
*  $FV Valor retornado
*     DPTS_Feito
*     DPTS_DadoPontosNaoExiste
*     DPTS_NaoExisteJogadorComDadoPontos
*
*  Assertivas de Entrada:  - Deve ter um ponteiro para a cabeca dado de pontos
*                            que ser ́a analisado
*                          - Deve ter um ponteiro de char que ser ́a atualizado com a cor do jogador
*                            possuidor do dado de pontos.
*
*  Assertivas de Saída:   - Se dado pontos não tiver possuidor no momento, o ponteiro não será
*                           atualizado.
*                         - Caso contrário, o ponteiro é atualizado com a cor correta
*
******************************************************************************************/

DPTS_CondRet DPTS_ObterJogadorDobraPonto(DPTS_DadoPCabeca pDadoPontos, char *pCorPeca);

/*****************************************************************************************
*
*  $FC Função: DPTS Obter Pontuação Partida
*
*  $ED Descrição da função
*     Obtém a pontuação atual da partida
*
*  $EP Parâmetros
*     $P pDadoPontos - variavel cabeca dado de pontos de onde a pontuacao vai ser obtida.
*     $P pPonto - Ponteiro que vai obter por referencia a pontuacao atual da partida.
*
*  $FV Valor retornado
*     DPTS_Feito
*     DPTS_DadoPontosNaoExiste
*  
*  Assertivas de Entrada: - Deve ter uma cabeca para dado de pontos;
*                         - Deve ter um ponteiro para receber a  pontuação da partida.
*  Assertivas de Saída:   - Se dado de pontos existir, a pontuação será obtida e o valor do ponteiro
*                           pPonto será atualizado.
******************************************************************************************/

DPTS_CondRet DPTS_ObterPontuacaoPartida(DPTS_DadoPCabeca pDadoPontos, int *pPonto);

/*****************************************************************************************
*
*  $FC Função: DPT Destruir dado de pontos
*
*  $ED Descrição da função
*     Destrói a peça.
*
*  $EP Parâmetros
*     $P pDadoPontos - ponteiro para o a cabeca do dado de pontos a ser destruido
*
*  $FV Valor retornado
*     DPTS_Feito
*     DPTS_DadoPontosNaoExiste
*  Assertivas de Entrada:  - Deve ter um ponteiro para a cabeca do dado de pontos que será destruído
*  Assertivas de Saída:    - O dado de pontos foi destruído e ponteiro aponta para NULL.
*******************************************************************************************/

DPTS_CondRet DPTS_DestruirDadoPontos(DPTS_DadoPCabeca *pDadoPontos);
#undef DadoPontos_EXT

/***************** Fim do módulo de definição: Módulo Dado Pontos **********************/
#else
#endif
