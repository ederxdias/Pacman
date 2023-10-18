#include "tPosicao.h"

/**
 * Cria a posição dinamicamente
 * \param linha linha da posição
 * \param coluna coluna da posição
 */
tPosicao* CriaPosicao(int linha, int coluna){
    tPosicao * posicao = (tPosicao *) malloc(sizeof(tPosicao));
    posicao->linha = linha;
    posicao->coluna = coluna;
    return posicao;
}

/**
 * Clona a posição (construtor de cópia)
 * \param posicao posição
 */
tPosicao* ClonaPosicao(tPosicao* posicao){
    tPosicao * posicaoClone = (tPosicao *) malloc(sizeof(tPosicao));
    posicaoClone->linha = posicao->linha;
    posicaoClone->coluna = posicao->coluna;
    return posicaoClone;
}

/**
 * Retorna a linha da posição
 * \param posicao posição
 */
int ObtemLinhaPosicao(tPosicao* posicao){
    return posicao->linha;
}

/**
 * Retorna a coluna da posição
 * \param posicao posição
 */
int ObtemColunaPosicao(tPosicao* posicao){
    return posicao->coluna;
}

/**
 * Atualiza a posição a atual por uma nova posição
 * \param posicaoAtual posição atual
 * \param posicaoNova posição nova
 */
void AtualizaPosicao(tPosicao* posicaoAtual, tPosicao* posicaoNova){
    posicaoAtual->linha = posicaoNova->linha;
    posicaoAtual->coluna = posicaoNova->coluna;
}

/**
 * Verifica se 2 posição são iguais
 * \param posicao1 posição 1
 * \param posicao2 posição 2
 */
bool SaoIguaisPosicao(tPosicao* posicao1, tPosicao* posicao2){
    return posicao1->linha == posicao2->linha && posicao1->coluna == posicao2->coluna;
}

/**
 * Libera o espaço alocado para a estrutura tPosicao
 * 
 * \param posicao posicao
 */
void DesalocaPosicao(tPosicao* posicao){
    free(posicao);
}

