#if ! defined( PECA_ )
#define PECA_

/***************************************************************************
*
*  $MCD Modulo de definicao: Modulo Peca
*
*  Arquivo gerado:              PECA.H
*  Letras identificadoras:      PEC
*
*  Nome da base de software:    Exemplo de teste automatizado
*
*  Projeto: INF 1301
*  Autor: jfr     Júlia Affonso Figueiredo Rocha
*         sipf    Suemy Inagaki Pinheiro Fagundes
*
*  $HA Historico de evolucao:
*     Versao   Autor    Data       Observacoes
*       1.10   sipf  10/06/2019 Algumas correções
*       1.01   jfr   05/05/2019 Revisao e melhorias no módulo
*       1.00   jfr   01/05/2019 Inicio do desenvolvimento
*
*  $ED Descricao do modulo
*     O módulo implementa as funcoes de existencia e manutencao da Peca, bem como criacao, destrucao e consulta de cor.
*
***************************************************************************/

#if defined( PECA_OWN )
   #define PECA_EXT
#else
   #define PECA_EXT extern
#endif

typedef struct tgPeca * tppPeca;

/***********************************************************************
*
*  $TC Tipo de dados: MAT Condicoes de retorno
*
***********************************************************************/

   typedef enum {

         PEC_CondRetOK = 0 ,
               /* Executou correto */
       
         PEC_CondRetErro = 1 ,
                /* Erro ao obter dado da struct */

         PEC_CondRetFaltouMemoria = 2
               /* Faltou memoria ao alocar dados */

   } PEC_tpCondRet ;

   typedef enum {

          PEC_corPreta = 'p' ,
                /* Peca de cor preta */

          PEC_corVermelha = 'v'
                /* Peca de cor vermelha */

   } PEC_CorDaPeca ;

/***********************************************************************
*
*  $FC Funcao: PEC Criar Peca
*
*  $ED Descricao da funcao
*	  Cria uma nova peca
*
*  $EP Parametros:
*
*   $P PECCriado - é o ponteiro para a nova peca criada
*   $P CorDaNovaPeca - é o char da cor da nova peca criada
*
*
*  $FV Valor retonado
*     - Pec_CondRetOK
*     - Pec_CondRetFaltouMemoria
*  Assertivas de Entrada: Deve existir um ponteiro para a peça a ser criada
*  Assertivas de Saída:   Uma peça criada deve ser retornada pelo ponteiro recebido
*                         no parâmetro
*
***********************************************************************/
  PEC_tpCondRet PEC_CriarPeca(tppPeca * PECCriado, PEC_CorDaPeca CorDaNovaPeca);
/***********************************************************************
*
*  $FC Funcao: PEC Destruir Peca
*
*  $ED Descricao da funcao
*	  Destroi uma peca
*
*  $EP Parametros:
*
*   $P Peca - a peca que será destruida
*
*   Assertivas de Entrada: Deve existir uma peça a ser destruída
*   Assertivas de Saída:   O ponteiro da peça que foi destruida aponta para NULL
*
***********************************************************************/
  void PEC_DestruirPeca(tppPeca *Peca);
/***********************************************************************
*
*  $FC Funcao: PEC Obter Cor
*
*  $ED Descricao da funcao
*	  Obtem cor de uma peca
*
*  $EP Parametros:
*
*   $P Peca - a peca da qual sera obtida a cor
*   $P cor - é o ponteiro para um char que contem a da cor da peca
*
*
*  $FV Valor retonado
*     PEC_CondRetOK
*     PEC_CondRetFaltouMemoria
*
*   Assertivas de Entrada: Deve existir um ponteiro que receberá a peça
*   Assertivas de Saída:   A cor da peça obtida deve ser passada para p ponteiro
***********************************************************************/
PEC_tpCondRet PEC_ObterCor(tppPeca Peca, char *cor);
/*************************************************************************/

/********** Fim do módulo de definição: Módulo PECA **********/

#else
#endif
