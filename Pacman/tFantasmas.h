#ifndef TFANTASMAS_H
#define TFANTASMAS_H
#include "tPosicao.h"
#include "tMapa.h"
#include "constantes.h"


typedef struct tFantasma{
    char tipo;
    tPosicao * posicaoAtual;
    int passouFruta;
    int sentidoAtual;
  
}tFantasma;

typedef struct tVetFatasma{
    int tam;
    tFantasma **vet;
}tVetFantasma;

tFantasma *CriaFantasma(tPosicao *posicaoAtual ,char tipo);

tVetFantasma *CriaVetFastama();

void InseriNovoFantasmaVet(tVetFantasma *vetFantasma, tFantasma* fantasma);
void AfirmarPassouFruta(tFantasma *fantasma);

void NegarPassouFruta(tFantasma * fantasma);

int PassouFruta(tFantasma *fantasma);

int SentidoAtualFantasma(tFantasma *fantasma);


void TrocarSentidoAtualFantasma(tFantasma *fantasma);


tPosicao * AndarDireitaFantasma(tFantasma* fantasma);


tPosicao * AndarEsquerdaFantasma(tFantasma* fantasma);


tPosicao * AndarCimaFantasma(tFantasma* fantasma);



tPosicao * AndarBaixoFantasma(tFantasma* fantasma);

tPosicao * FicarParado(tFantasma* fantasma);

void MoveFantasma(tMapa *mapa, tFantasma * fantasma);

void MoveVetFantasmas(tMapa *mapa, tVetFantasma *vetfantasma);

// B
// Horizontal
// Para esquerda
// P
// Vertical
// Para cima
// I
// Vertical
// Para baixo
// C
// Horizontal
// Para direita




#endif