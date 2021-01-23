/***************************************************************************
*  $MCI Módulo de definição: Modulo Jogo
*
*  Arquivo gerado:              JOGO.C
*  Letras identificadoras:      JOG
*
*  Projeto: Jogo Gamao
*  Autores: fbt - Fernando Baggi Tancini
*
*  $HA Histórico de evolução:
*		Versão		Autores		Data			Observações
*	  	3   		fbt	  		13/06/2019		Revisao e consertos
*	  	2   		fbt	  		12/06/2019		Criação do módulo 
*       1    		fbt	  		11/06/2019		Inicializado projeto
*
***************************************************************************/

	#include	<malloc.h>
	#include 	<stdio.h>
	#include	<stdlib.h>
	#include "TABULEIRO.H"
	#include "DADO.h"
	#include "PECASCAPTURADAS.h"
	#include "PecasFinalizadas.h"
	#include "DadoPontos.h"
	#define JOGO_OWN
	#include "JOGO.H"
	#undef JOGO_OWN

int jogo_rolando = 0;
char jogador_atual = 'p';
int pc[] = {0,0};
int pf[] = {0,0};
char qnpd = '\0';
int pt = 0;
int fd = 0;

/***** Protótipos das funções encapuladas no módulo *****/

void imprime_tabuleiro();
void iniciar_jogo();
void termina_jogo();
void perguntarYorN(char * txt, char * c);
void realizar_jogada();
void rodar_jogo();
void pergunta_movimentos(int *mov);
void finalizarPeca(char jogador);
void capturarPeca(char jogador);
int tem_peca_no_lado_interno_do_inimigo(char jogador_perderdor);
int checa_se_pode_finalizar_pecas(char jogador);

/*****  Código da funcao main  *****/

int main () {
	char c;
	printf("\n****** Jogo Gamao ******\n\n");
	while(1) {
		perguntarYorN("Comecar um jogo?", &c);
		if (c == 'y') {
			rodar_jogo();
		} else if (c == 'n') {
			printf("Bye bye! Foi legal!\n");
			break;
		}
	}
	return 0;
}


/*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
*
*  $FC Função: JOG Rodar Jogo
*
*  $ED Descrição da função
*     Roda uma partida do jogo.
*
***********************************************************************/

void rodar_jogo() {
	int pontos = 0, pontos_finais;
	iniciar_jogo();
	// 
	while(jogo_rolando) {
		realizar_jogada();
		if (jogador_atual == 'p') jogador_atual = 'v';
		else if (jogador_atual == 'v') jogador_atual = 'p';
	}
	// conta os pontos
	//Argumentação de Corretude do IF
	// AE1, vale AS para os argumentos acima e
	// - fd tem que ser verdadeiro, ou seja, diferente de zero
	if (fd) {
		pontos_finais = pt;
		// AI1:
		//   Caso a quantidade de peças finais do jogador preto seja 15 entra no if
		//   Caso contrario entra no else if
		if (pf[0] == 15) {
			printf("Jogador preto venceu!!!\n");
		} 
		// AI2:
		//   Caso a quantidade de peças finalizadas do jogador vermelho seja 15
		//   Não existe caso contrario nesse caso.
		else if (pf[1] == 15) {
			printf("Jogador vermelho venceu!!!\n");
		}
		//AI3:
		//  Caso nenhum dos jogadores tenha finalizado 15 peças
	} else {
			//AI4:  
		    //   Caso a quantidade de peças finalizadas do jogador preto seja 15
		    //   A pontuação do jogador preto é acrescido
			//   AI5: 
		    //     Caso peças finalizadas do jogador vermelho seja zero
		    //        A pontuação é acrescidaa
		    //        Caso a quantidade de peças capturadas do jogador vermelho seja maior que zero
			//				A pontuação é acrescida
		    //     Caso a quantidade de peças finalizadas do jogador vermelho seja 15:
		    //    		Caso peças finalizadas do jogador preto seja zero
		    //        		A pontuação é acrescidaa
		    //              Caso a quantidade de peças capturadas do jogador preto seja maior que zero
			//				    A pontuação é acrescida
		if (pf[0] == 15) {
			printf("Jogador preto venceu!!!\n");
			pontos++;
			if (pf[1] == 0) {
				pontos++;
				if (pc[1] > 0) {
					pontos++;
				} else if (tem_peca_no_lado_interno_do_inimigo('v')) {
					pontos++;
				}
			}
		} else if (pf[1] == 15) {
			printf("Jogador vermelho venceu!!!\n");
			pontos++;
			if (pf[0] == 0) {
				pontos++;
				if (pc[0] > 0) {
					pontos++;
				} else if (tem_peca_no_lado_interno_do_inimigo('p')) {
					pontos++;
				}
			}
		}
		pontos_finais = pontos*pt;
	}
	printf("pontos: %d\n", pontos_finais);
}
//AS:
// A pontuação dos jogadores é atualizada
// É determinado o vncedor


/***********************************************************************
*
*  $FC Função: JOG Realizar Jogada
*
*  $ED Descrição da função
*     Permite a realizacao de uma jogada por parte do jogador corrente.
*
***********************************************************************/

void realizar_jogada() {
	int dado1, dado2, mov[4];
	printf("\n\n ~~~ Inicio de jogada ~~~ \n");
	if (jogador_atual == 'p') {
		printf("Vez do jogador preto\n");
	} else if (jogador_atual == 'v') {
		printf("Vez do jogador vermelho.\n");
	}
	printf("Responda qualquer coisa para jogar o dado 1!\n");
	fflush(stdin);
	scanf_s(" ");
	DAD_Jogar(&dado1);
	printf("Responda qualquer coisa para jogar o dado 2!\n");
	fflush(stdin);
	scanf_s(" ");
	DAD_Jogar(&dado2);
	printf("Valores dos dados: %d e %d\n", dado1, dado2);
	mov[0] = dado1;
	mov[1] = dado2;
	mov[2] = 0; mov[3] = 0;
	if (dado1 == dado2) { mov[2] = dado1; mov[3] = dado2; }
	// Argumentação de Corretude de Repetição
	// Vale AE
	// A lista mov tem pelo menos um elemento diferente de zero
	while (mov[0] != 0 || mov[1] != 0 || mov[2] != 0 || mov[3] != 0) {
		imprime_tabuleiro();
		pergunta_movimentos(mov);
		if (pf[0] == 15 || pf[1] == 15) {
			jogo_rolando = 0;
			break;
		}
	}
	// Se existe ainda algum movimento em mov (mov[i] != 0 para algum i de 0 a 3)
	// Entao
	// 	  (mov[0] != 0 || mov[1] != 0 || mov[2] != 0 || mov[3] != 0)
	//    e entra no loop novamente
	// Senao
	//	  mov[i] == 0 para qualquer i de 0 a 3
	// FimSe
	if (!fd) {
		// acabou a jogada, entao imprime tabuleiro atualizado
		printf("Tabuleiro apos a jogada:\n");
		imprime_tabuleiro();
	}
}

/***********************************************************************
*
*  $FC Função: JOG Pergunta Movimento
*
*  $ED Descrição da função
*		Permite que o usuario faca input de movimentos, para realizar
*		as jogadas desejadas pelo mesmo.
*
*  $EP Parâmetros
*		mov - array com os movimentos possiveis.
*
***********************************************************************/

void pergunta_movimentos(int *mov) {
	int casa_origem, qnt_casas, casa_dest, n, indice_movimento, esta_saindo_da_barra = 0;
	char c;
	if (jogador_atual != qnpd && pt <= 64) {
		printf("Vc pode dobrar os pontos. Para isso, digite \"0, 0\".\n");
	}
	if (jogador_atual == 'p') {
		if (pc[0] > 0) {
			printf("Vc tem peca(s) capturadas e deve movimenta-las primeiro. Para isso, digite \"-1\" na <casa_origem>.\n");
		}
	} else if (jogador_atual == 'v') {
		if (pc[1] > 0) {
			printf("Vc tem peca(s) capturadas e deve movimenta-las primeiro. Para isso, digite \"-1\" na <casa_origem>.\n");
		}
	}
	printf("Obs: Se vc perceber que nao pode se movimentar, digite \"100, 100\".\n");
	printf("Vc tem os movimentos possiveis: %d, %d, %d, %d\n", mov[0], mov[1], mov[2], mov[3]);
	printf("Faca um movimento por vez: <casa_origem>, <qtd_casas_a_andar>\n");
	while(1) {
		fflush(stdin);
		if (scanf_s("%d, %d", &casa_origem, &qnt_casas) != 2) {
			printf("Formato do movimento invalido. Use: <casa_origem>, <qtd_casas_a_andar>\n");
		} else {
			if (jogador_atual != qnpd && pt <= 64) {
				if (casa_origem == 0 && qnt_casas == 0) {
					// dobra pontos (pergunta)
					if (jogador_atual == 'p') {
						perguntarYorN("Jogador Vermelho, vc aceita a dobra?",&c);
					} else if (jogador_atual == 'v') {
						perguntarYorN("Jogador Preto, vc aceita a dobra?",&c);
					}
					if (c == 'y') {
						pt = pt*2;
						qnpd = jogador_atual;
						printf("Pontuacao dobrada para: %d\n", pt);
						printf("Agora faca sua jogada.\n");
						continue;
					} else if (c == 'n') {
						printf("Fim do jogo entao.\n");
						if (jogador_atual == 'p') {
							pf[0] = 15;
						} else if (jogador_atual == 'v') {
							pf[1] = 15;
						}
						fd = 1;
						break;
					}
				}
			}
			if (casa_origem == 100 && qnt_casas == 100) {
				mov[0] = 0;
				mov[1] = 0;
				mov[2] = 0;
				mov[3] = 0;
				break;
			}
			if (jogador_atual == 'p') {
				if (pc[0] > 0) {
					if (casa_origem != -1) {
						printf("Vc tem peca(s) capturadas e deve movimenta-las primeiro. Para isso, digite \"-1\" na <casa_origem>.\n");
						continue;						
					} else {
						esta_saindo_da_barra = 1;
					}
				}
			} else if (jogador_atual == 'v') {
				if (pc[1] > 0) {
					if (casa_origem != -1) {
						printf("Vc tem peca(s) capturadas e deve movimenta-las primeiro. Para isso, digite \"-1\" na <casa_origem>.\n");
						continue;						
					} else {
						esta_saindo_da_barra = 1;
					}
				}
			}
			if ((casa_origem < 1 || casa_origem > 24) && !esta_saindo_da_barra) {
				printf("Casa de origem nao exitente. Tem que ser entre [1...24]\n");
				continue;
			}
			TAB_CorPecasCasa(casa_origem, &c);
			if (c != jogador_atual && !esta_saindo_da_barra) {
				TAB_NumPecasCasa(casa_origem, &n);
				if (n != 0) {
					printf("Casa de origem nao eh sua. Tente outra coisa.\n");
				} else {
					printf("Sem pecas suas na casa de origem. Tente outra coisa.\n");
				}
				continue;
			}
			if (qnt_casas == mov[0]) indice_movimento = 0;
			else if (qnt_casas == mov[1]) indice_movimento = 1;
			else if (qnt_casas == mov[2]) indice_movimento = 2;
			else if (qnt_casas == mov[3]) indice_movimento = 3;
			else {
				printf("Quantidade de casa nao permitida. Use o valor de um dos seus movimentos possiveis.\n");
				printf("Vc tem os movimentos possiveis: %d, %d, %d, %d\n", mov[0], mov[1], mov[2], mov[3]);
				continue;
			}
			// agora faz o movimento mesmo, dependendo da cor do jogador
			if (jogador_atual == 'p') {
				if (esta_saindo_da_barra) {
					casa_dest = 0 + qnt_casas;
				} else {
					casa_dest = casa_origem + qnt_casas;
				}
				if (casa_dest > 24) {
					if (checa_se_pode_finalizar_pecas(jogador_atual)) {
						TAB_RemoveNPecasCasa(1, casa_origem);
						mov[indice_movimento] = 0;
						pf[0]++;
						break;
					} else {
						printf("Vc tem que trazer todas pecas para as casas [19,24] para finaliza-las. Tente outra coisa.\n");
						continue;
					}
				}
			} else if (jogador_atual == 'v') {
				if (esta_saindo_da_barra) {
					casa_dest = 25 - qnt_casas;										
				} else {
					casa_dest = casa_origem - qnt_casas;					
				}
				if (casa_dest < 1) {
					if (checa_se_pode_finalizar_pecas(jogador_atual)) {
						TAB_RemoveNPecasCasa(1, casa_origem);
						mov[indice_movimento] = 0;
						pf[1]++;
						break;
					} else {
						printf("Vc tem que trazer todas pecas para as casas [1,6] para finaliza-las. Tente outra coisa.\n");
						continue;
					}
				}
			}
			TAB_NumPecasCasa(casa_dest, &n);
			if (n == 0) {
				if (esta_saindo_da_barra) {
					if (jogador_atual == 'p') {
						pc[0]--;
					} else if (jogador_atual == 'v') {
						pc[1]--;
					}
					TAB_InsereNPecasCasa(1, jogador_atual, casa_dest);
					mov[indice_movimento] = 0;
					esta_saindo_da_barra = 0;
				} else {
					TAB_RemoveNPecasCasa(1, casa_origem);
					TAB_InsereNPecasCasa(1, jogador_atual, casa_dest);
					mov[indice_movimento] = 0;
				}
				break;
			}
			TAB_CorPecasCasa(casa_dest, &c);
			if (c == jogador_atual) {
				if (esta_saindo_da_barra) {
					if (jogador_atual == 'p') {
						pc[0]--;
					} else if (jogador_atual == 'v') {
						pc[1]--;
					}
					TAB_InsereNPecasCasa(1, jogador_atual, casa_dest);
					mov[indice_movimento] = 0;
					esta_saindo_da_barra = 0;
				} else {
					TAB_RemoveNPecasCasa(1, casa_origem);
					TAB_InsereNPecasCasa(1, jogador_atual, casa_dest);
					mov[indice_movimento] = 0;
				}
				break;
			} else {
				// eh casa do otro jogador
				if (n == 1) {
					// captura
					if (esta_saindo_da_barra) {
						if (jogador_atual == 'p') {
							pc[0]--;
						} else if (jogador_atual == 'v') {
							pc[1]--;
						}
						TAB_RemoveNPecasCasa(1, casa_dest);
						if (jogador_atual == 'p') {
							pc[1]++;
						} else if (jogador_atual == 'v') {
							pc[0]++;
						}
						// move 
						TAB_RemoveNPecasCasa(1, casa_origem);
						TAB_InsereNPecasCasa(1, jogador_atual, casa_dest);
						mov[indice_movimento] = 0;
					} else {
						TAB_RemoveNPecasCasa(1, casa_dest);
						if (jogador_atual == 'p') {
							pc[1]++;
						} else if (jogador_atual == 'v') {
							pc[0]++;
						}
						// move 
						TAB_RemoveNPecasCasa(1, casa_origem);
						TAB_InsereNPecasCasa(1, jogador_atual, casa_dest);
						mov[indice_movimento] = 0;
					}
					break;
				} else {
					printf("Casa de destino eh do outro jogador. Tente outra coisa.\n");
					continue;
				}
			}
		}
	}
}

/***********************************************************************
*
*  $FC Função: JOG Checa se pode finalizar pecas
*
*  $ED Descrição da função
*		Verifica se todas as pecas de certo jogador estao na area certa do tabuleiro para se finalziar pecas
*
*  $EP Parâmetros
*		jogador - jogador em questao, para ver se ele tem pecas no lugar certo para finalizar pecas
*
***********************************************************************/

int checa_se_pode_finalizar_pecas (char jogador) {
	int i, n; char c;
	if (jogador == 'p') {
		for (i = 1; i <= 18; i++) {
			TAB_CorPecasCasa(i, &c);
			if (c =='p') {
				TAB_NumPecasCasa(i, &n);
				if (n > 0) {
					return 0;
				}
			}
		}
	} else if (jogador == 'v') {
		for (i = 7; i <= 24; i++) {
			TAB_CorPecasCasa(i, &c);
			if (c =='v') {
				TAB_NumPecasCasa(i, &n);
				if (n > 0) {
					return 0;
				}
			}
		}
	}
	return 1;
}

/***********************************************************************
*
*  $FC Função: JOG Tem Peca no Lado Interno do Inimigo
*
*  $ED Descrição da função
*		Verifica se ha pecas de um tal jogador no lado interno do inimigo.
*
*  $EP Parâmetros
*		jogador_perderdor - jogador que perdeu o jogo e que sera analisado se ha pecas
*							dele no lado interno do adversario
*
***********************************************************************/

int tem_peca_no_lado_interno_do_inimigo(char jogador_perderdor) {
	int i, n; char c;
	if (jogador_perderdor == 'p') {
		for (i = 1; i <= 6; i++) {
			TAB_CorPecasCasa(i, &c);
			if (c =='p') {
				TAB_NumPecasCasa(i, &n);
				if (n > 0) {
					return 1;
				}
			}
		}
	} else if (jogador_perderdor == 'v') {
		for (i = 19; i <= 24; i++) {
			TAB_CorPecasCasa(i, &c);
			if (c =='v') {
				TAB_NumPecasCasa(i, &n);
				if (n > 0) {
					return 1;
				}
			}
		}
	}
	return 0;
}

/***********************************************************************
*
*  $FC Função: JOG Perguntar Yes ou No
*
*  $ED Descrição da função
*		Pergunta algo ao usuario ate que seja respondido 'y' ou 'n', retornando
*		a resposta do usuario.
*
*  $EP Parâmetros
*		txt - pergunta a ser perguntada
*		c - char por onde sera retornada a resposta do usuario
*
***********************************************************************/

void perguntarYorN(char * txt, char * c) {
	*c = '\0';
	printf("%s (y/n)\n", txt);
	fflush(stdin);
	scanf_s("%1c", c);
	while(*c != 'y' && *c != 'n') {
		printf("Nao entendi, repete\n");
		fflush(stdin);
		scanf_s("%1c", c);
	}
}

/***********************************************************************
*
*  $FC Função: JOG Inicia o jogo
*
*  $ED Descrição da função
*     Inicia o jogo e realiza as configuracoes nescessarias para tal acao
*
***********************************************************************/

void iniciar_jogo() {
	jogo_rolando = 1;
	jogador_atual = 'p';
	pt = 1;
	fd = 0;
	pc[0] = 0; pc[1] = 0; pf[0] = 0; pf[1] = 0;
	TAB_CriarTabuleiro();
}

/***********************************************************************
*
*  $FC Função: JOG Termina Jogo
*
*  $ED Descrição da função
*     Termina o jogo e realiza as configuracoes nescessarias para tal acao.
*
***********************************************************************/

void termina_jogo() {
	jogo_rolando = 0;
	TAB_DestruirTabuleiro();
}
 
/***********************************************************************
*
*  $FC Função: JOG Imprime Tabuleiro
*
*  $ED Descrição da função
*     Imprime o tabuleiro de gamao do jogo na tela do terminal.
*
***********************************************************************/

void imprime_tabuleiro() {
	int i, n; 
	char c, *pretas = "pretas", *vermelhas = "vermelhas";
	printf("_________________________________________________________\n");
	printf("|\t\t\t\t\t\t\t|\n");
	for (i = 1; i <= 12; i++) {
		// 0 + i
		printf("|  ");
		TAB_NumPecasCasa(i, &n);
		TAB_CorPecasCasa(i, &c);
		if (i < 10) {
			if (n != 0) {
				if (c == 'p') {
					printf("(%d) : %d %s\t\t", i, n, pretas);
				} else if (c == 'v') {
					printf("(%d) : %d %s\t\t", i, n, vermelhas);
				} 
			} else {
				printf("(%d) : %d\t\t\t", i, 0);
			}
		} else {
			if (n != 0) {
				if (c == 'p') {
					printf("(%d): %d %s\t\t", i, n, pretas);
				} else if (c == 'v') {
					printf("(%d): %d %s\t\t", i, n, vermelhas);
				} 
			} else {
				printf("(%d): %d\t\t\t", i, 0);
			}
		}
		// 12 + i
		TAB_NumPecasCasa(12+i, &n);
		TAB_CorPecasCasa(12+i, &c);
		if (n != 0) {
			if (c == 'p') {
				printf("(%d): %d %s\t\t", 12+i, n, pretas);
			} else if (c == 'v') {
				printf("(%d): %d %s\t", 12+i, n, vermelhas);
			}
		} else {
			printf("(%d): %d\t\t\t", 12+i, 0);
		}
		// linha vertical direita
		printf("|");

		if (i == 3) {
			printf("\tPretas capturadas: %d\n", pc[0]);
		} else if (i == 4) {
			printf("\tVermelhas capturadas: %d\n", pc[1]);
		} else if (i == 6) {
			printf("\tPretas finalizadas: %d\n", pf[0]);
		} else if (i == 7) {
			printf("\tVermelhas finalizadas: %d\n", pf[1]);
		} else if (i == 9) {
			printf("\tPontuacao em disputa: %d\n", pt);
		} else {
			printf("\n");
		}
	}
	printf("|_______________________________________________________|\n");
}

/********** Fim do módulo de implementação: Módulo Jogo **********/
