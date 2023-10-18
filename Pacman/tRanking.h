#ifndef TRANKING_H
#define TRANKING_H



#include "tMovimento.h"
#include "tPacman.h"
#include "constantes.h"
typedef struct tEfeitosComando {
    char direcao;
    int frutasPegas;
    int ColisoesParede;
    int numeroMovimentosComando;
}tEfeitosComando ;

typedef struct tRanking{
    int tam;
    /* vetor de ponteiros do tipo de dados tRanking*/
    tEfeitosComando **vet;

}tRanking;

typedef int (*ftpComp) (const void * ,const void * );

tEfeitosComando  * CriaEfeitosComando (tPacman *pacaman,char direcao);
int ObtemTamRanking(tRanking* ranking);

tRanking* CriaRanking(tPacman *pacman);

int ComparaRanking(const void *a, const void *b);

void OrdernaRanking(tRanking * ranking, int tam, ftpComp cmp);

void DesalocaRanking(tRanking *tRanking);
tEfeitosComando* ObtemEfeitosComando(tRanking *ranking, int idx);

int ObtemQtdFrutasPegas(tEfeitosComando *efeitos);

int ObtemQtdColisoesParede(tEfeitosComando* efeitos);

int ObtemQtdMovimentosComando(tEfeitosComando* efeitos);

char ObtemDirecaoComando(tEfeitosComando* efeitos);


#endif
// Gerar ranking
// O programa deverá também salvar na pasta de saída do caso de teste em questão, um arquivo, 
// denominado ranking.txt, contendo um ranking de melhores movimentos junto de características
//  desses movimentos ao fim do jogo. O melhor movimento (a, w, s ou d) é aquele que mais 
//  resultou em pegar comida. Em caso de empate usa-se o movimento que menos colidiu com a parede.
//   Como segundo critério de desempate temos o movimento utilizado mais vezes. Se nesse último
//    critério também houver empate, usa-se a ordem alfabética do caractere representando o movimento.
//     O arquivo de ranking deverá apresentar cada linha, o movimento (x), o número de comidas pegas
//      com esse movimento (#1), o número de colisões com parede (#2) e o número de movimentos do 
//      tipo realizado (#3), seguindo essa mesma ordem.
