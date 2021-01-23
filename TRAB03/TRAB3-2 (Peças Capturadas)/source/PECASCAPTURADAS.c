/***************************************************************************
*  $MCI Módulo de implementação: Módulo peças capturadas
*
*  Arquivo gerado:              PECASCAPTURADAS.C
*  Letras identificadoras:      BAR
*
*  Nome da base de software:    Exemplo de teste automatizado
*
*  Projeto: INF 1301
*  Autor: jfr     Júlia Affonso Figueiredo Rocha
*
*  $HA Historico de evolucao:
*     Versao   Autor    Data       Observacoes
*       1.00   jfr   07/06/2019  Inicio do desenvolvimento
*		1.01   sipf  16/06/2019  Melhorias no módulo
*
*  $ED Descricao do modulo
*     O módulo implementa as funcoes de existencia e manutencao da Barra de Pecas Capturadas.
*     No início de cada partida não existe PecasCapturadas.
*
***************************************************************************/

#include   <malloc.h>
#include   <stdio.h>

#define PECASCapturadas_OWN
#include "PECASCAPTURADAS.h"
#undef PECASCapturadas_OWN

/***********************************************************************
*
*  $TC Tipo de dados: BAR Descritor da peça capturada
*
*
***********************************************************************/

typedef struct BAR_tagPecasCapturadas {

    LIS_tppLista listaPecasVermelhas;
    /* Lista de peças Vermelhas Capturadas */

    LIS_tppLista listaPecasPretas;
    /* Lista de peças pretas Capturadas */

};

/*****  Dados encapsulados no módulo  *****/

/***** Protótipos das funções encapsuladas no módulo *****/

void LiberarPeca(void *pPeca);

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: BAR Criar lista de peças Capturadas
* 
***************************************************************************/
BAR_tpCondRet BAR_CriarListaPecasCapturadas(BAR_tpPecasCapturadas *pPecasCapturadas)
{

    *pPecasCapturadas = (BAR_tpPecasCapturadas) malloc(sizeof(struct BAR_tagPecasCapturadas));
    if(*pPecasCapturadas == NULL)
        return BAR_SemMemoria ;

    (*pPecasCapturadas)->listaPecasVermelhas = LIS_CriarLista(LiberarPeca);
    (*pPecasCapturadas)->listaPecasPretas = LIS_CriarLista(LiberarPeca);

    return BAR_OK ;

} /* Fim função: BAR Criar lista de peças Capturadas */

/***************************************************************************
*
*  Função: BAR Inserir peça
*  
****************************************************************************/
BAR_tpCondRet BAR_InserirPeca(BAR_tpPecasCapturadas pPecasCapturadas, tppPeca pPeca)
{
    PEC_CorDaPeca  CorPeca;

    if(pPecasCapturadas == NULL) 
        return BAR_NaoExisteLista;

    PEC_ObterCor(pPeca, &CorPeca);  
    
    if(CorPeca == PEC_corVermelha)
        LIS_InserirElementoAntes(pPecasCapturadas->listaPecasVermelhas, pPeca);

    else
        LIS_InserirElementoAntes(pPecasCapturadas->listaPecasPretas, pPeca);
    
    return BAR_OK;

} /* Fim função: BAR Inserir peça */

/***************************************************************************
*
*  Função: BAR Conta peças
*  
***************************************************************************/

   BAR_tpCondRet BAR_ContarPecas(BAR_tpPecasCapturadas pPecasCapturadas, PEC_CorDaPeca  CorPeca, int *pContagem)
{
    LIS_tppLista ListaPecas;

    if(pPecasCapturadas == NULL) 
        return BAR_NaoExisteLista;

    *pContagem = 0;

    if(CorPeca == PEC_corVermelha)
        ListaPecas = pPecasCapturadas->listaPecasVermelhas;
    else 
        ListaPecas = pPecasCapturadas->listaPecasPretas;

    IrInicioLista(ListaPecas);

    if(LIS_ObterValor(ListaPecas) != NULL)
        do
        {
            (*pContagem)++;
        } while(LIS_AvancarElementoCorrente(ListaPecas, 1) == LIS_CondRetOK);

    return BAR_OK ;

} /* Fim função: BAR Contar peças */

/***************************************************************************
*
*  Função: BAR Destruir lista de peças Capturadas
*  
****************************************************************************/
BAR_tpCondRet BAR_DestruirListaPecasCapturadas(BAR_tpPecasCapturadas *pPecasCapturadas)
{
    if(*pPecasCapturadas == NULL || ((*pPecasCapturadas)->listaPecasVermelhas == NULL && (*pPecasCapturadas)->listaPecasPretas == NULL)) 
        return BAR_NaoExisteLista;

    if((*pPecasCapturadas)->listaPecasVermelhas != NULL)
        LIS_DestruirLista((*pPecasCapturadas)->listaPecasVermelhas);

    if((*pPecasCapturadas)->listaPecasPretas != NULL)
        LIS_DestruirLista((*pPecasCapturadas)->listaPecasPretas);

    free(*pPecasCapturadas);
    *pPecasCapturadas = NULL;

    return BAR_OK ;

} /* Fim função: BAR Destruir lista de peças Capturadas */


BAR_tpCondRet BAR_RemoverPeca(BAR_tpPecasCapturadas pPecasCapturadas, PEC_CorDaPeca  CorPeca) {

if (CorPeca == PEC_corPreta)
{
    if (pPecasCapturadas->listaPecasPretas == NULL) {
        return BAR_CondRetVazia;
    }
    if(LIS_ExcluirElemento(pPecasCapturadas->listaPecasPretas) != LIS_CondRetOK) {
    return BAR_SemMemoria;
    }
}
else{

    if (pPecasCapturadas->listaPecasVermelhas == NULL) {
        return BAR_CondRetVazia;
    }

    if(LIS_ExcluirElemento(pPecasCapturadas->listaPecasPretas) != LIS_CondRetOK) {
    
        return BAR_SemMemoria;
    }
}
return BAR_OK;
}

/*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
*
*  $FC Função: Libera peça
*
*  $ED Descrição da função
*     Libera uma peça.
*
***********************************************************************/
void LiberarPeca(tppPeca *pPeca)
{
    PEC_DestruirPeca(&(*pPeca));
}

/********** Fim do módulo de implementação: Módulo peças Capturadas **********/
