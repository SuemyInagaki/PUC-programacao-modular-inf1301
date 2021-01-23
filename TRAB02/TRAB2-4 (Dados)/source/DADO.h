#if ! defined( DADO_ )
#define DADO_
/***************************************************************************
*
*  $MCD Modulo de definicao: Modulo Dado
*
*  Arquivo gerado:              Dado.H
*  Letras identificadoras:      DAD
*
*  Nome da base de software:    Exemplo de teste automatizado
*
*  Projeto: INF 1301
*  Autor: jfr     Júlia Affonso Figueiredo Rocha
*
*
*  $HA Historico de evolucao:
*     Versao   Autor    Data       Observacoes
*       1.01   jfr   05/05/2019 Revisao e melhorias no módulo
*       1.00   jfr   01/05/2019 Inicio do desenvolvimento
*
*  $ED Descricao do modulo
*     O módulo implementa as funcoes para a geracao de resultado de um dado de seis lados.
*
***************************************************************************/

#if defined( DADO_OWN )
   #define DADO_EXT
#else
   #define DADO_EXT extern
#endif

/***********************************************************************
*
*  $TC Tipo de dados: DAD Condicoes de retorno
*
***********************************************************************/

   typedef enum {

         DAD_CondRetOK = 0 ,
               /* Executou correto */

         DAD_CondRetFaltouMemoria = 1
               /* Faltou memÛria ao alocar dados */

   } DAD_tpCondRet ;

/***********************************************************************
*
*  $FC Funcao: DAD Jogar Dado
*
*  $ED Descricao da Funcao
*	  Retorna um numero de 1 a 6 que representa o valor tirado no dado lançado.
*
*  $EP Parametros:
*
*   $P Numero - é o ponteiro para um int que conterá o valor do dado
*
*  $FV Valor retonado
*     - DAD_CondRetOK
*     - DAD_CondRetFaltouMemoria
*  Assertivas de Entrada: - Deve existir um ponteiro para um número
*  Assertivas de Saída:   - O número do dado deve ser passado por referência
*                           ao ponteiro recebido
***********************************************************************/

DAD_tpCondRet DAD_Jogar(int *Numero) ;

#undef DADO_EXT

/*************** Fim do modulo de definicao: Modulo Dado ****************/

#else
#endif