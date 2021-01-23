#if ! defined(PECASFINALIZADAS_)
#define PECASFINALIZADAS_

#include "PECA.h"

/***************************************************************************
*
*  $MCD Módulo de definição: Módulo peças finalizadas
*
*  Arquivo gerado:              PecasFinalizadas.h
*  Letras identificadoras:      PFZ
*
*  Projeto: Disciplina INF 1301
*
*  Autores: sipf - Suemy Inagaki Pinheiro Fagundes
*
*  $HA Histórico de evolução:
*     Versão       Autor          Data          Observações
*       1.00       sipf        09/jun/2019   Início do desenvolvimento
*
*  $ED Descrição do módulo
*     Este módulo implementa funções do módulo de peças finalizadas
*     Não existe peças finalizadas no inicio do programa
*
***************************************************************************/
 
#if defined(PECASFINALIZADAS_OWN)
   #define PECASFINALIZADAS_EXT
#else
   #define PECASFINALIZADAS_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma lista de peças finalizadas */

typedef struct PFZ_tagPecasFinalizadas* PFZ_tpPecasFinalizadas;

/***********************************************************************
*
*  $TC Tipo de dados: PFZ Condicoes de retorno
*
*
***********************************************************************/

   typedef enum {

         PFZ_OK = 0,
               /* Executou correto */

		   PFZ_NaoExisteLista = 1,
			   /* Lista de peças finalizadas não existe */

         PFZ_SemMemoria = 2
               /* Faltou memória */

   } PFZ_tpCondRet;


/***********************************************************************
*
*  $FC Função: PFZ Criar lista de peças finalizadas
*
*  $ED Descrição da função
*     Cria uma nova lista de peças finalizadas.
*
*  $EP Parâmetros
*     $P pPecasFinalizadas - ponteiro para a lista de peças finalizadas a ser criada. Passado por referência.
*
*  $FV Valor retornado
*     PFZ_OK
*     PFZ_SemMemoria
*
* AE:
*    Deve existir um ponteiro de PFZ_tpPecasFinalizadas
* AS:
*    Deve ser criada uma lista de peças finalizadas a ser passado para o ponteiro recebido
*
***********************************************************************/

   PFZ_tpCondRet PFZ_CriarListaPecasFinalizadas(PFZ_tpPecasFinalizadas *pPecasFinalizadas);

/***********************************************************************
*
*  $FC Função: PFZ Inserir peça
*
*  $ED Descrição da função
*     Insere uma peça na lista de peças finalizadas.
*
*  $EP Parâmetros
*     $P pPecasFinalizadas - ponteiro para a lista de peças finalizadas a ser utilizada.
*     $P pPeca - ponteiro para a peça a ser utilizada.
*
*  $FV Valor retornado
*     PFZ_OK
*     PFZ_NaoExisteLista
*	  PFZ_SemMemoria
*
* AE:
*    Deve existir um PFZ_tpPecasFinalizadas
*    Deve existir um ponteiro para peça do tipo tppPeca a ser inserida
* AS:
*    A lista passada pelo parâmetro deve ser atualizada com a nova peça inserida
*
***********************************************************************/
   PFZ_tpCondRet PFZ_InserirPeca(PFZ_tpPecasFinalizadas pPecasFinalizadas, tppPeca pPeca);
/***********************************************************************
*
*  $FC Função: PFZ Contar peças
*
*  $ED Descrição da função
*     Conta as peças de uma determinada cor na lista de peças finalizadas
*
*  $EP Parâmetros
*     $P pPecasFinalizadas - ponteiro para a lista de peças finalizadas a ser utilizada.
*     $P CorPeca - cor das peças a serem contadas.
*     $P pContagem - ponteiro para o inteiro onde será armazenado o número de peças.
*
*  $FV Valor retornado
*     PFZ_OK
*	  PFZ_NaoExisteLista
*
* AE:
*    Deve existir um  PFZ_tpPecasFinalizadas com as peças finalizadas
*    Deve existir um ponteiro de inteiro para receber por referência a contagem
* AS:
*    O valor do ponteiro deve ser atualizado com a quantidade de peças da cor desejada
*
***********************************************************************/
   PFZ_tpCondRet PFZ_ContarPecas(PFZ_tpPecasFinalizadas pPecasFinalizadas, PEC_CorDaPeca  CorPeca, int *pContagem);
/***********************************************************************
*
*  $FC Função: PFZ Destruir lista de peças finalizadas
*
*  $ED Descrição da função
*     Destrói a lista de peças finalizadas.
*
*  $EP Parâmetros
*     $P pPecasFinalizadas - ponteiro para a lista de peças finalizadas a ser utilizada. Passado por referência.
*
*  $FV Valor retornado
*     PFZ_OK
*	  PFZ_NaoExisteLista
*
*
* AE:
*    Deve existir um ponteiro de PFZ_tpPecasFinalizadas a ser destruido
* AS:
*    O ponteiro deve ter sido destruido
***********************************************************************/
   PFZ_tpCondRet PFZ_DestruirListaPecasFinalizadas(PFZ_tpPecasFinalizadas *pPecasFinalizadas);

#undef PFZ_EXT

/********** Fim do módulo de definição: Módulo peças finalizadas **********/

#else
#endif
