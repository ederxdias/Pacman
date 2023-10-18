#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tMovimento.h"
#include "constantes.h"
#include "tPosicao.h"
#include "tPacman.h"
#include "tMapa.h"
#include "tRanking.h"
#include "tFantasmas.h"
#include <dirent.h>
#include <ctype.h>

typedef struct tMapa{
    /* Número de linhas e de colunas do mapa */
    int nLinhas, nColunas;
    /* Número atual de frutas no mapa */
    int nFrutasAtual;
    /* Número máximo permitido de movimentos do pacman no mapa */
    int nMaximoMovimentos;
    /* O grid (matriz) de informações do mapa */
    char** grid;
    /* O tunel do mapa contendo 2 acessos */
} tMapa;


COMANDO DefinirComando(char direcao){
    COMANDO comando = MOV_BAIXO;
        if(direcao == 'a'){
            comando = MOV_ESQUERDA;
        }else if(direcao == 'd'){
            comando = MOV_DIREITA;
        }else if(direcao == 's'){
            comando = MOV_BAIXO;
        }else if(direcao == 'w'){
            comando = MOV_CIMA;
        }
    return comando;
}
char DefinirDirecao(COMANDO comando, char direcao){
    if(comando == MOV_BAIXO){
        direcao = 's';
    }else if(comando == MOV_CIMA){
        direcao = 'w';
    }else if( comando == MOV_DIREITA){
        direcao = 'd'
    }else if(comando == MOV_ESQUERDA){
        direcao = 'a';
    }
}
bool EhFimJogo(tMapa * mapa,tPacman* pacman,tPosicao * posicao, FILE * saida){
    // acaba as frutas do mapa ou acaba o numero de movimentos do mapa
    if(!ObtemQuantidadeFrutasIniciaisMapa(mapa)){

        fprintf(saida,"Voce venceu!\n");
        printf("Voce venceu!\n");
        return 1;
    }
    if( ObtemNumeroAtualMovimentosPacman(pacman) > ObtemNumeroMaximoMovimentosMapa(mapa)){
        MataPacman(pacman);
    }

    if(EstaVivoPacman(pacman) == MORTO){
        fprintf(saida,"Game over!\n");
        printf("Game over!\n");
        return 1;
    }
    return 0;
}

void ImprimirMapaAtual(tMapa *mapa,FILE * saida){
    for(int i=0; i < mapa->nLinhas;i++){
        for(int j=0; j< mapa->nColunas;j++){
        tPosicao *posicao = CriaPosicao(i,j);
        printf("%c", ObtemItemMapa(mapa,posicao ));
        fprintf(saida,"%c",ObtemItemMapa(mapa,posicao ));
        DesalocaPosicao(posicao);
        }
        printf("\n");
        fprintf(saida,"\n");
    }
}

tMovimento * ObtemMovimentoPacman(tPacman * pacman, int idx){
    return pacman->historicoDeMovimentosSignificativos[idx];
}

void ImprimirResumoDaPartida(FILE * resumo, tPacman* pacman){
    for(int i=0; i< ObtemNumeroMovimentosSignificativosPacman(pacman);i++){
        char direcao = '\0';
        DefinirDirecao(ObtemComandoMovimento(ObtemMovimentoPacman(pacman,i)), direcao);
        fprintf(resumo,"Movimento %d (%c) %s\n",ObtemNumeroMovimento(ObtemMovimentoPacman(pacman,i)),direcao,ObtemAcaoMovimento(ObtemMovimentoPacman(pacman,i)));
    }
}
void ImprimirRankingDaPartida( FILE* ranking,tPacman *pacman){
    tRanking* ranking = CriaRanking(pacman);
    OrdernaRanking(ranking,ObtemTamRanking(ranking),ComparaRanking);
    for(int i=0; i< 4;i++){
        fprintf(ranking,"%c, %d, %d, %d\n",ObtemDirecaoComando(ObtemEfeitosComando(ranking,i)),ObtemQtdFrutasPegas(ObtemEfeitosComando(ranking,i)),
        ObtemQtdColisoesParede(ObtemEfeitosComando(ranking,i)), ObtemQtdMovimentosComando(ObtemEfeitosComando(ranking,i)));
    }
}

void ImprimirEstatisticasDaPartida(FILE* estatisticas, tPacman* pacman){
    fprintf(estatisticas,"Numero de movimentos: %d\n",ObtemNumeroAtualMovimentosPacman(pacman));
    fprintf(estatisticas,"Numero de movimentos sem pontuar: %d\n",ObtemNumeroMovimentosSemPontuarPacman(pacman));
    fprintf(estatisticas,"Numero de colisoes com parede: %d\n", ObtemNumeroColisoesParedePacman(pacman));
    fprintf(estatisticas,"Numero de movimentos para baixo: %d\n", ObtemNumeroMovimentosBaixoPacman(pacman));
    fprintf(estatisticas,"Numero de movimentos para cima: %d\n",ObtemNumeroMovimentosCimaPacman(pacman));
    fprintf(estatisticas,"Numero de movimentos para esquerda: %d\n",ObtemNumeroMovimentosEsquerdaPacman(pacman));
    fprintf(estatisticas,"Numero de movimentos para direita: %d\n",ObtemNumeroMovimentosDireitaPacman(pacman));
}
int ObtemNLinhasTrilha(tPacman* pacman){
    return pacman->nLinhasTrilha;
}
int ObtemNColunasTrilha(tPacman* pacman){
    return pacman->nColunasTrilha;
}

int** ObtemTrilhaPacman(tPacman* pacman){
    return pacman->trilha;
}
int ObtemCasaTrilha(int **trilha, int i, int j){
    return trilha[i][j];
}

void ImprimirTrilha(FILE* trilha,tPacman* pacman){
    for(int i=0; i< ObtemNLinhasTrilha(pacman);i++){
        for(int j=0; i< ObtemNColunasTrilha(pacman);j++){
            if(ObtemCasaTrilha(ObtemTrilhaPacman(pacman),i,j) == '#'){
                fprintf(trilha,"#");
            }else{
                fprintf(trilha,"%d", ObtemCasaTrilha(ObtemTrilhaPacman(pacman),i,j));
            }
            
        }
        fprintf(trilha,"\n");
    }
}
//   Numero de movimentos: 13
// Numero de movimentos sem pontuar: 9
// Numero de colisoes com parede: 1
// Numero de movimentos para baixo: 2
// Numero de movimentos para cima: 4
// Numero de movimentos para esquerda: 2
// Numero de movimentos para direita: 5

int main(char *argc, char *argv[]){
    // Criar Pasta saida
    if (mkdir("saida", 0777) == 0) {
        printf("Pasta criada com sucesso!\n");
    } else {
        perror("Erro ao criar a pasta");
    }

    tMapa *mapa = CriaMapa(argv[1]);
    tPacman * pacman = CriaPacman(ObtemPosicaoItemMapa(mapa,PACMAN));
    tVetFantasma *vetFantasma = CriaVetFastama();
    CriaTrilhaPacman(pacman,ObtemNumeroLinhasMapa(mapa), ObtemNumeroColunasMapa(mapa));

    //Preparar os fantasmas do mapa
    tPosicao *posicaoFantasma;
    if(AchouFantasmas)
    
    char direcao='\0';
    //iniciar comando
    COMANDO comando = MOV_BAIXO;

    // criar arquivo saida.txt
    FILE *saida = fopen("./saida/saida.txt","w");
    if(!saida){
        printf("ERRO nao foi possivel abrir arquivo ./saida.txt\n");
        exit(-1);
    }
    //criar arquivo resumo.txt
    FILE *resumo = fopen("./saida/resumo.txt","w");
    if(!resumo){
        printf("ERRO nao foi possivel abrir arquivo ./resumo.txt\n");
        exit(-1);
    }
    //criar arquivo ranking.txt
    FILE *ranking = fopen("./saida/ranking.txt","w");
    if(!ranking){
        printf("ERRO nao foi possivel abrir arquivo ./ranking.txt\n");
        exit(-1);
    }
    //criar arquivo estatisticas.txt
    FILE *estatisticas = fopen("./saida/estatisticas.txt","w");
    if(!estatisticas){
        printf("ERRO nao foi possivel abrir arquivo ./estatisticas.txt\n");
        exit(-1);
    }
    //criar arquivo trilha.txt
    FILE *trilha = fopen("./saida/trilha.txt","w");
    if(!trilha){
        printf("ERRO nao foi possivel abrir arquivo ./trilha.txt\n");
        exit(-1);
    }

    while(scanf("%c%*c", &direcao)==1){

        fprintf(saida,"Estado do jogo apos o movimento %c\n", direcao);
        printf("Estado do jogo apos o movimento %c\n", direcao);

        AtualizaTrilhaPacman(pacman);

        comando = DefinirComando(direcao);

        MovePacman(pacman,mapa,comando);

        ImprimirMapaAtual(mapa,saida);

        if(EhFimJogo(mapa,pacman,ObtemPosicaoPacman(pacman),saida)){
            // acabou o numero de jogadas
            // acabou todas as frutas do mapa
            // o pacman desaparece
            fprintf(saida,"Pontuação Final: %d\n",ObtemPontuacaoAtualPacman(pacman));
            printf("Pontuação Final: %d\n",ObtemPontuacaoAtualPacman(pacman));
        }else{
            fprintf(saida,"Pontuação: %d\n",ObtemPontuacaoAtualPacman(pacman));
            printf("Pontuação: %d\n",ObtemPontuacaoAtualPacman(pacman));
        }

    }
    ImprimirResumoDaPartida(resumo,pacman);
    ImprimirRankingDaPartida(ranking,pacman);
    ImprimirEstatisticasDaPartida(estatisticas,pacman);
    ImprimirTrilha(trilha,pacman);
    //lembrar de fechar os arquivos abertos
    fclose(resumo);
    fclose(ranking);
    fclose(estatisticas);
    fclose(trilha);
    return 0;
}
// ~/template-TP-1-etapa-1/Casos/01 caminho do arquivo
//~/template-TP-1-etapa-1/Casos/01
// fazer fantasma.h, uma estrutura de fantasma e fantasmas

// 1 passo e acertar todos os pontos h depois que é bola pra frente kkk;