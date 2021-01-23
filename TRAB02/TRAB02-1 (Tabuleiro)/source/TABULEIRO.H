#if ! defined( TABULEIRO_ )
#define TABULEIRO_

/***************************************************************************
*
*  $MCD Módulo de definição: Modulo Tabuleiro
*
*  Arquivo gerado:              TABULEIRO.H
*  Letras identificadoras:      TAB
*
*  Projeto: Jogo Gamao
*  Autores: fbt - Fernando Baggi Tancini
*
*  $HA Histórico de evolução:
*		Versão		Autores		Data			Observações
*	  	3   		fbt	  		03/05/2019		Revisao e consertos
*	  	2   		fbt	  		02/05/2019		Criação do módulo 
*       	1    		fbt	  		01/05/2019		Inicializado projeto
*
*  $ED Descrição do módulo
*			O modulo tem como objetivo prover a estutura de dados 
*			para o tabuleiro usando listas encadeadas e promover tambem 
*			as funcoes nescessarias para realizar o jogo.
*
***************************************************************************/

#if defined( TABULEIRO_OWN )
   #define TABULEIRO_EXT
#else
   #define TABULEIRO_EXT extern
#endif

/***********************************************************************
*
*  $TC Tipo de dados: TAB Condições de retorno
*
*
***********************************************************************/

   typedef enum {

         TAB_CondRetOK,
               /* Executou correto */

         TAB_CondRetTabNaoExiste,
               /* Tabuleiro não existe */

         TAB_CondRetCasaNaoExiste,
               /* Casa fornecida não existe */

         TAB_CondRetCasaVazia,
               /* A casa está vazia*/

		 TAB_CondRetFaltouMemoria
               /* Faltou memória ao alocar dados */

   } TAB_tpCondRet ;


/***********************************************************************
*
*	$FC Função: TAB Criar tabuleiro
*
*  $ED Descrição da função
*		Cria um novo tabuleiro com 24 casas e as pecas
*		posicionadas nas respectivas posicoes iniciais.
*		E sobescreve (apaga) outro tabuleiro anterior
*		se houvesse.
*
*	$FV Valores de retorno:
*		- TAB_CondRetOK
*		- TAB_CondRetFaltouMemoria
*   Assertivas de Entrada: Não existe assertivas de entrada para essa função
*   Assertiva de Saída:    Um tabuleiro é criado
*
*************************************************************************/

   TAB_tpCondRet TAB_CriarTabuleiro( void ) ;


/*************************************************************************
*
*	$FC Função: TAB Destruir Tabuleiro
*
*  $ED Descrição da função
*		Destroi o tabuleiro e todas estruturas adjacentes em cascata
*		caso estas existam.
*
*	 $FV Valores de retorno:
*		- TAB_CondRetOK
*  Assertivas de Entrada: Um tabuleiro a ser destruído deve existir
*  Asertivas de Saída:    O tabuleiro foi destruido
*************************************************************************/

   TAB_tpCondRet TAB_DestruirTabuleiro( void ) ;


/***************************************************************************
*
*	$FC Função: TAB Insere N Peças na Casa
*
*  $ED Descrição da função
*     Insere n peças da cor informada na casa informada
*	
*	 $EP Parâmetros:
*     $P n - é o número da peças a se inserir
*     $P cor - é a cor da peça a ser inserida
*     $P nCasa - é o número da casa
*
*	 $FV Valores de retorno:
*		- TAB_CondRetOK
*		- TAB_CondRetTabNaoExiste
*		- TAB_CondRetFaltouMemoria
*		- TAB_CondRetCasaNaoExiste
*   Assertivas de Entrada: A peça a ser inserida deve existir
*                          Deve-se saber a cor da peça e o numero da casa a inserir
*   Assertivas de Saída:   A peça foi inserida na casa do tabuleiro
*************************************************************************/

	TAB_tpCondRet TAB_InsereNPecasCasa( int n, int cor, int nCasa ) ;


/*************************************************************************
*
*	$FC Função: TAB Remove N Peças da Casa
*
*  $ED Descrição da função
*     Remove n peças da casa informada, caso haja alguma
*	
*	$EP Parâmetros:
*     $P nCasa - é o número da casa
*
*	$FV Valores de retorno:
*		- TAB_CondRetOK
*		- TAB_CondRetTabNaoExiste
*		- TAB_CondRetCasaVazia
*		- TAB_CondRetCasaNaoExiste
*
*   Assertivas de Entrada: Deve existir uma peça na casa de onde quer remover
*   Assertivas de Saída:   Uma peça é removida da casa recebida como parâmetro
*************************************************************************/

   TAB_tpCondRet TAB_RemoveNPecasCasa( int n, int nCasa ) ;


/*************************************************************************
*
*	$FC Função: TAB Num Peças da Casa
*
*  $EP Parâmetros
*     $P casa - é o número da casa escolhida para ver a quantidade de pecas
*     $P numPecas - É o parámetro que receberá o número de peças
*
*	$FV Valores de retorno:
*		- TAB_CondRetOK
*		- TAB_CondRetTabNaoExiste
*		- TAB_CondRetCasaNaoExiste
*
*   Assertivas de Entrada: Deve existir um ponteiro que receberá a quantidade de peças
*   Assertivas de Saída:   O numero de peças na casa é passado para o ponteiro.
*************************************************************************/

   TAB_tpCondRet TAB_NumPecasCasa( int nCasa, int * numPecas ) ;


/*************************************************************************
*
*	$FC Função: TAB Cor Peças da Casa
*
*  $EP Parâmetros
*     $P casa - é o número da casa escolhida para ver a cor das peças
*     $P cor - É o parámetro que receberá a cor das peças da casa escolhida.
*
*	$FV Valores de retorno:
*		- TAB_CondRetOK
*		- TAB_CondRetTabNaoExiste
*		- TAB_CondRetCasaVazia
*		- TAB_CondRetCasaNaoExiste
*
*   Assertivas de Entrada: Deve existir um ponteiro para receber a cor da peça
*   Assertivas de Saída: A cor da peça é passada para o ponteiro
*************************************************************************/

   TAB_tpCondRet TAB_CorPecasCasa( int nCasa, char * cor ) ;

#undef TABULEIRO_EXT

/********** Fim do módulo de definição: Módulo Tabuleiro **********/

#else
#endif
