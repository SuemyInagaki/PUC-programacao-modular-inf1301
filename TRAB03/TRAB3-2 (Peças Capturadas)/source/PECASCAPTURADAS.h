#if ! defined(PECASCapturadas_)
#define PECASCapturadas_

#include "PECA.h"

#include "LISTA.h"

/***************************************************************************
 *
 *  $MCD Modulo de definicao: Módulo peças capturadas
 *
 *  Arquivo gerado:              PECASCAPTURADAS.H
 *  Letras identificadoras:      BAR
 *
 *  Nome da base de software:    Exemplo de teste automatizado
 *
 *  Projeto: INF 1301
 *  Autor: jfr     Júlia Affonso Figueiredo Rocha
 *         sipf    Suemy Inagaki Pinheiro Fagundes
 *
 *  $HA Historico de evolucao:
 *     Versao   Autor    Data       Observacoes
 *       1.00   jfr   07/06/2019  Inicio do desenvolvimento
 *       1.01   sipf  16/06/2019  Melhorias no módulo
 *
 *  $ED Descricao do modulo
 *     O módulo implementa as funcoes de existencia e manutencao da Barra de Pecas Capturadas.
 *     No início de cada partida não existe PecasCapturadas.
 *
 ***************************************************************************/
 
#if defined(PECASCapturadas_OWN)
   #define PECASCapturadas_EXT
#else
   #define PECASCapturadas_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma lista de peças Capturadas */

typedef struct BAR_tagPecasCapturadas* BAR_tpPecasCapturadas;

/***********************************************************************
*
*  $TC Tipo de dados: BAR Condicoes de retorno
*
*
***********************************************************************/

   typedef enum {

         BAR_OK = 0,
               /* Executou correto */

	 BAR_NaoExisteLista = 1,
	       /* Lista de peças Capturadas não existe */

         BAR_SemMemoria = 2,
               /* Faltou memória ao alocar dados */
	   
         BAR_CondRetVazia = 3,
               /*Não tem peças na lista*/

   } BAR_tpCondRet;


/***********************************************************************
*
*  $FC Função: BAR Criar lista de peças Capturadas
*
*  $ED Descrição da função
*     Cria uma nova lista de peças Capturadas.
*
*  $EP Parâmetros
*     $P pPecasCapturadas - ponteiro para a lista de peças Capturadas a ser criada. Passado por referência.
*
*  $FV Valor retornado
*     BAR_OK
*     BAR_SemMemoria
*
*AE:
*    Deve existir um ponteiro de BAR_tpPecasCapturadas
* AS:
*    Deve ser criada uma lista de peças capturada a ser passado para o ponteiro recebido
***********************************************************************/

   BAR_tpCondRet BAR_CriarListaPecasCapturadas(BAR_tpPecasCapturadas *pPecasCapturadas);

/***********************************************************************
*
*  $FC Função: BAR Inserir peça
*
*  $ED Descrição da função
*     Insere uma peça na lista de peças Capturadas.
*
*  $EP Parâmetros
*     $P pPecasCapturadas - ponteiro para a lista de peças Capturadas a ser utilizada.
*     $P pPeca - ponteiro para a peça a ser utilizada.
*
*  $FV Valor retornado
*     BAR_OK
*     BAR_NaoExisteLista
*     BAR_SemMemoria
 AE:
*    Deve existir um BAR_tpPecasCapturadas
*    Deve existir um ponteiro para peça do tipo tppPeca a ser inserida
* AS:
*    A lista passada pelo parâmetro deve ser atualizada com a nova peça inserida
*
***********************************************************************/

   BAR_tpCondRet BAR_InserirPeca(BAR_tpPecasCapturadas pPecasCapturadas, tppPeca pPeca);

/***********************************************************************
*
*  $FC Função: BAR Contar peças
*
*  $ED Descrição da função
*     Conta as peças de uma determinada cor na lista de peças Capturadas
*
*  $EP Parâmetros
*     $P pPecasCapturadas - ponteiro para a lista de peças Capturadas a ser utilizada.
*     $P CorPeca - cor das peças a serem contadas.
*     $P pContagem - ponteiro para o inteiro onde será armazenado o número de peças.
*
*  $FV Valor retornado
*     BAR_OK
*     BAR_NaoExisteLista
* AE:
*    Deve existir um  BAR_tpPecasCapturadas com as peças capturadas
*    Deve existir um ponteiro de inteiro para receber por referência a contagem
* AS:
*    O valor do ponteiro deve ser atualizado com a quantidade de peças da cor desejada
***********************************************************************/

   BAR_tpCondRet BAR_ContarPecas(BAR_tpPecasCapturadas pPecasCapturadas, PEC_CorDaPeca  CorPeca, int *pContagem);

/***********************************************************************
*
*  $FC Função: BAR Destruir lista de peças Capturadas
*
*  $ED Descrição da função
*     Destrói a lista de peças Capturadas.
*
*  $EP Parâmetros
*     $P pPecasCapturadas - ponteiro para a lista de peças Capturadas a ser utilizada. Passado por referência.
*
*  $FV Valor retornado
*     BAR_OK
*     BAR_NaoExisteLista
* AE:
*    Deve existir um ponteiro de BAR_tpPecasCapturadas a ser destruido
* AS:
*    O ponteiro deve ter sido destruido
***********************************************************************/

   BAR_tpCondRet BAR_DestruirListaPecasCapturadas(BAR_tpPecasCapturadas *pPecasCapturadas);
/***********************************************************************
*
*  $FC Função: BAR Remover Peca
*
*  $ED Descrição da função
*     Remove uma peca da lista.
*
*  $EP Parâmetros
*     $P pPecasCapturadas - ponteiro para a lista de peças Capturadas a ser utilizada. Passado por referência.
*     $P CorPeca - Cor da peça que deseja remover
*  $FV Valor retornado
*     BAR_OK
*     BAR_NaoExisteLista
* AE:
*    Deve existir um ponteiro de BAR_tpPecasCapturadas de onde a peca será removida
* AS:
*    Se existir peça na lista ela deve ser removida.
***********************************************************************/
   BAR_tpCondRet BAR_RemoverPeca(BAR_tpPecasCapturadas pPecasCapturadas, PEC_CorDaPeca  CorPeca);

#undef BAR_EXT

/********** Fim do módulo de definição: Módulo peças Capturadas **********/

#else
#endif
