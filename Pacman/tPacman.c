#ifndef TPACMAN_H_
#define TPACMAN_H_

#include "tPacman.h"
#include "tPosicao.h"
#include "tMovimento.h"
#include "tMapa.h"
#include "constantes.h"

typedef struct tPacman{
    /* Posição atual do pacman (linha,coluna) */
    tPosicao* posicaoAtual;

    /* Estado de vida do pacman: vivo ou morto */
    int estaVivo;

    /* Estatísticas para quando o pacman se move para baixo */
    int nMovimentosBaixo;
    int nFrutasComidasBaixo;
    int nColisoesParedeBaixo;

    /* Estatísticas para quando o pacman se move para cima */
    int nMovimentosCima;
    int nFrutasComidasCima;
    int nColisoesParedeCima;

    /* Estatísticas para quando o pacman se move para a esquerda */
    int nMovimentosEsquerda;
    int nFrutasComidasEsquerda;
    int nColisoesParedeEsquerda;

    /* Estatísticas para quando o pacman se move para a direita */
    int nMovimentosDireita;
    int nFrutasComidasDireita;
    int nColisoesParedeDireita;

    /* Histórico de movimentos significativos do pacman */
    int nMovimentosSignificativos;
    tMovimento** historicoDeMovimentosSignificativos;

    /* Trilha gerada pelos passos do pacman. */
    int nLinhasTrilha;
    int nColunasTrilha;
    int** trilha;
} tPacman;

/**
 * Cria o pacman dinamicamente
 * \param posicao Ponteiro para tPosicao
 */
tPacman* CriaPacman(tPosicao* posicao){
    tPacman * pacman = (tPacman *) malloc(sizeof(tPacman));

    pacman->posicaoAtual = ClonaPosicao(posicao);
    pacman->estaVivo =1;
    
    pacman->nColisoesParedeBaixo =0;
    pacman->nColisoesParedeCima =0;
    pacman->nColisoesParedeDireita =0;
    pacman->nColisoesParedeEsquerda =0;

    pacman->nFrutasComidasBaixo =0;
    pacman->nFrutasComidasCima =0;
    pacman->nFrutasComidasDireita =0;
    pacman->nFrutasComidasEsquerda =0;

    pacman->nMovimentosBaixo =0;
    pacman->nMovimentosCima =0;
    pacman->nMovimentosDireita =0;
    pacman->nMovimentosEsquerda =0;

    pacman->nMovimentosSignificativos =0;
    pacman->historicoDeMovimentosSignificativos = (tMovimento **) malloc(sizeof(tMovimento*));

    pacman->nLinhasTrilha =0;
    pacman->nColunasTrilha =0;
    

    return pacman;

}

/**
 * Clona o pacman dinamicamente, construtor de cópia
 * \param pacman pacman
 */
tPacman* ClonaPacman(tPacman* pacman){
    tPacman * pacmanClone = (tPacman *) malloc(sizeof(tPacman));

    pacmanClone->posicaoAtual = ClonaPosicao(ObtemPosicaoPacman(pacman));
    pacmanClone->estaVivo =pacman->estaVivo;
    
    pacmanClone->nColisoesParedeBaixo =pacman->nColisoesParedeBaixo;
    pacmanClone->nColisoesParedeCima =pacman->nColisoesParedeCima;
    pacmanClone->nColisoesParedeDireita =pacman->nColisoesParedeDireita;
    pacmanClone->nColisoesParedeEsquerda =pacman->nColisoesParedeEsquerda;

    pacmanClone->nFrutasComidasBaixo =pacman->nFrutasComidasBaixo;
    pacmanClone->nFrutasComidasCima =pacman->nFrutasComidasCima;
    pacmanClone->nFrutasComidasDireita =pacman->nFrutasComidasDireita;
    pacmanClone->nFrutasComidasEsquerda =pacman->nFrutasComidasEsquerda;

    pacmanClone->nMovimentosBaixo =pacman->nMovimentosBaixo;
    pacmanClone->nMovimentosCima =pacman->nMovimentosCima;
    pacmanClone->nMovimentosDireita =pacman->nMovimentosDireita;
    pacmanClone->nMovimentosEsquerda =pacman->nMovimentosEsquerda;

    pacmanClone->nMovimentosSignificativos =pacman->nMovimentosSignificativos;
    // Copiar historico de movimentos significativos
    pacmanClone->historicoDeMovimentosSignificativos = ClonaHistoricoDeMovimentosSignificativosPacman(pacman);

    // Copiar trilha
    ClonaTrilhaPacman(pacmanClone,pacman);

    return pacmanClone;
}

/**
 * Clona a lista historico de movimentos significativos do pacman.
 * 
 * \param pacman pacman
 */
tMovimento** ClonaHistoricoDeMovimentosSignificativosPacman(tPacman* pacman){
    tMovimento** movimentosSignificativos = (tMovimento**) malloc(sizeof(tMovimento*)*pacman->nMovimentosSignificativos);
    for(int i=0; i< pacman->historicoDeMovimentosSignificativos;i++){
        movimentosSignificativos[i] = CriaMovimento(ObtemNumeroMovimento(pacman->historicoDeMovimentosSignificativos[i]),
         ObtemComandoMovimento(pacman->historicoDeMovimentosSignificativos[i]), ObtemAcaoMovimento(pacman->historicoDeMovimentosSignificativos[i]));
    }
    return movimentosSignificativos;
}

/**
 * Retorna a posição do pacman.
 * 
 * \param pacman pacman
 */
tPosicao* ObtemPosicaoPacman(tPacman* pacman){
    return pacman->posicaoAtual;
}

/**
 * Retorna se o pacman está vivo ou morto.
 * 
 * \param pacman pacman
 */
int EstaVivoPacman(tPacman* pacman){
    return pacman->estaVivo;
}

void IncrementarMovimentosBaixoPacaman(tPacman* pacman){
    pacman->nMovimentosBaixo++;
}
void IncrementarMovimentosCimaPacaman(tPacman* pacman){
    pacman->nMovimentosCima++;
}
void IncrementarMovimentosEsquerdaPacaman(tPacman* pacman){
    pacman->nMovimentosEsquerda++;
}
void IncrementarMovimentosDireitaPacaman(tPacman* pacman){
    pacman->nMovimentosDireita++;
}

tPosicao* AndarBaixoPacman(tPacman* pacman){
    IncrementarMovimentosBaixoPacaman(pacman);
    return CriaPosicao(ObtemLinhaPosicao(ObtemPosicaoPacman(pacman))+1,ObtemColunaPosicao(ObtemPosicaoPacman(pacman)));
    
}
tPosicao* AndarCimaPacman(tPacman* pacman){
    IncrementarMovimentosCimaPacaman(pacman);
    return CriaPosicao(ObtemLinhaPosicao(ObtemPosicaoPacman(pacman))-1,ObtemColunaPosicao(ObtemPosicaoPacman(pacman)));
        
}
tPosicao* AndarEsquerdaPacman(tPacman* pacman){
    IncrementarMovimentosEsquerdaPacaman(pacman);
    return  CriaPosicao(ObtemLinhaPosicao(ObtemPosicaoPacman(pacman)),ObtemColunaPosicao(ObtemPosicaoPacman(pacman))-1);
        
}
tPosicao* AndarDireitaPacman(tPacman* pacman){
    IncrementarMovimentosDireitaPacaman(pacman);
    return CriaPosicao(ObtemLinhaPosicao(ObtemPosicaoPacman(pacman)),ObtemColunaPosicao(ObtemPosicaoPacman(pacman))+1);
        
}

void IncrementarNColisoesParedeBaixo(tPacman* pacman){
    pacman->nColisoesParedeBaixo++;
}

void IncrementarNColisoesParedeCima(tPacman* pacman){
    pacman->nColisoesParedeCima++;
}

void IncrementarNColisoesParedeEsquerda(tPacman* pacman){
    pacman->nColisoesParedeEsquerda++;
}

void IncrementarNColisoesParedeDireita(tPacman* pacman){
    pacman->nColisoesParedeDireita++;
}
void IncrementarNFrutasComidasBaixo(tPacman* pacman){
    pacman->nFrutasComidasBaixo++;
}
void IncrementarNFrutasComidasCima(tPacman* pacman){
    pacman->nFrutasComidasCima++;
}
void IncrementarNFrutasComidasEsquerda(tPacman* pacman){
    pacman->nFrutasComidasEsquerda++;
}
void IncrementarNFrutasComidasDireita(tPacman* pacman){
    pacman->nFrutasComidasDireita++;
}
void  DecrescerNFrutasAtualMapa(tMapa *mapa){
    mapa->nFrutasAtual--;
}
/**
 * Função que irá mover o pacman no mapa, atualizando sua posição.
 * 
 * \param pacman pacman
 * \param mapa o mapa que contem o pacman
 * \param comando o comando para onde irá o pacman
 */
void MovePacman(tPacman* pacman, tMapa* mapa, COMANDO comando){

    tPosicao * proximaPosicao = ClonaPosicao(ObtemPosicaoPacman(pacman)); 
    
    //Definir proxima posição e incrementar nMovimentos
    if(comando == MOV_BAIXO){
        proximaPosicao = AndarBaixoPacman(pacman);
    }else if(comando == MOV_CIMA){
        proximaPosicao = AndarCimaPacman(pacman);
    }else if( comando == MOV_DIREITA){
        proximaPosicao = AndarDireitaPacman(pacman);
    }else if(comando == MOV_ESQUERDA){
        proximaPosicao = AndarEsquerdaPacman(pacman);
    }

    //Prencher a posicao atual do pacman com espaco
    AtualizaItemMapa(mapa,ObtemPosicaoPacman(pacman), VAZIO);

    if(EncontrouParedeMapa(mapa,ObtemPosicaoPacman(pacman))){
        if(comando == MOV_BAIXO){
            IncrementarNColisoesParedeBaixo(pacman);
        }else if(comando == MOV_CIMA){
            IncrementarNColisoesParedeCima(pacman);
        }else if( comando == MOV_DIREITA){
            IncrementarNColisoesParedeDireita(pacman);
        }else if(comando == MOV_ESQUERDA){
            IncrementarNColisoesParedeEsquerda(pacman);
        }
        // Como ele encontrou a parede a proxima posição será a atual e a posicao passada dele nao sera vazia
        DesalocaPosicao(proximaPosicao);
        proximaPosicao = ClonaPosicao(ObtemPosicaoPacman(pacman));
        InsereNovoMovimentoSignificativoPacman(pacman,comando,"colidiu com a parede");

    }else if(EncontrouComidaMapa(mapa, ObtemPosicaoPacman(pacman))){
        // ganha um ponto
        if(comando == MOV_BAIXO){
            IncrementarNFrutasComidasBaixo(pacman);
        }else if(comando == MOV_CIMA){
            IncrementarNFrutasComidasCima(pacman);
        }else if( comando == MOV_DIREITA){
            IncrementarNFrutasComidasDireita(pacman);    
        }else if(comando == MOV_ESQUERDA){
            IncrementarNFrutasComidasEsquerda(pacman);
        }
                
        InsereNovoMovimentoSignificativoPacman(pacman,comando,"pegou comida");
        DecrescerNFrutasAtualMapa(mapa);

    }else if(AcessouTunelMapa(mapa,proximaPosicao) && PossuiTunelMapa(mapa)){
    // aparece no outro tunel ocupando seu lugar

        // se a posicao passada é um tunel
        if(EntrouTunel(ObtemTunelMapa(mapa), ObtemPosicaoPacman(pacman))){
            AtualizaItemMapa(mapa,ObtemPosicaoPacman(pacman),TUNEL);
        }
        // atualiza a posicao do pacman para o segundo tunel
        EntraTunelMapa(mapa,proximaPosicao);

    }else if(ObtemItemMapa(mapa,proximaPosicao) == VAZIO){
        //nao faz nada
    }else{
        // EncontraFantasma fim de jogo
        MataPacman(pacman);
        InsereNovoMovimentoSignificativoPacman(pacman,comando,"fim de jogo por enconstar em um fantasma");
        }

    AtualizaPosicao(ObtemPosicaoPacman(pacman),proximaPosicao);  
    AtualizaItemMapa(mapa,ObtemPosicaoPacman(pacman),PACMAN);
    DesalocaPosicao(proximaPosicao);

}

/**
 * Aloca a trilha dinamicamente.
 * 
 * \param pacman pacman
 * \param nLinhas número de linhas da trilha
 * \param nColunas número de colunas da trilha
 */
void CriaTrilhaPacman(tPacman* pacman, int nLinhas, int nColunas){

    pacman->nLinhasTrilha = nLinhas;
    pacman->nColunasTrilha = nColunas;

    pacman->trilha = (int **) malloc(sizeof(int)* nLinhas);
    for(int i=0; i < nLinhas;i++){
        pacman->trilha[i] = (int *) malloc(sizeof(int)*nColunas);
    }

    for(int i=0; i<nLinhas;i++){
        for(int j=0; j<nColunas;j++){
            pacman->trilha[i][j] = '#';
        }
    }
    
}

void ClonaTrilhaPacman(tPacman *pacmanClone, tPacman* pacman){
    CriaTrilhaPacman(pacmanClone,pacman->nLinhasTrilha,pacman->nColunasTrilha);
    for(int i=0; i<pacman->nLinhasTrilha;i++){
        for(int j=0; j<pacman->nColunasTrilha;j++){
            pacmanClone->trilha[i][j] = pacman->trilha[i][j];
        }
    }
};

/**
 * Atualiza na trilha a posição por onde passou o pacman.
 * 
 * \param pacman pacman
 */
void AtualizaTrilhaPacman(tPacman* pacman){
    pacman->trilha[ObtemLinhaPosicao(ObtemPosicaoPacman(pacman))][ObtemColunaPosicao(ObtemPosicaoPacman(pacman))]=
    ObtemNumeroAtualMovimentosPacman(pacman);
}

/**
 * Salva a trilha em um arquivo.
 * 
 * \param pacman pacman
 */
void SalvaTrilhaPacman(tPacman* pacman){
    FILE * trilha = fopen("./trilha.txt","w");
    if(!trilha){
        printf("ERRO não foi possível criar o arquivo ./trilha.txt\n");
        exit(1);
    }
    for(int i=0; i<pacman->nLinhasTrilha;i++){
        for(int j=0; j<pacman->nColunasTrilha;j++){
            fprintf(trilha,"%c", pacman->trilha[i][j]);
        }
        fprintf(trilha,"\n");
    }
    fclose(trilha);
}

/**
 * Insere na lista de movimentos um novo movimento significativo.
 * 
 * \param pacman pacman
 * \param comando o comando do movimento
 * \param acao a ação do movimento
 */
void InsereNovoMovimentoSignificativoPacman(tPacman* pacman, COMANDO comando, const char* acao){
    if(pacman->nMovimentosSignificativos){
        pacman->historicoDeMovimentosSignificativos = realloc(pacman->historicoDeMovimentosSignificativos ,
        sizeof(tMovimento*)*(pacman->nMovimentosSignificativos+1));
    }
    pacman->historicoDeMovimentosSignificativos[pacman->nMovimentosSignificativos] = 
    CriaMovimento(ObtemNumeroAtualMovimentosPacman(pacman),comando,acao);
    pacman->nMovimentosSignificativos++;
}

/**
 * Seta pacman para morto.
 * 
 * \param pacman pacman
 */
void MataPacman(tPacman* pacman){
    pacman->estaVivo = MORTO;
}

/**
 * Libera o espaço alocado para a estrutura tPacman
 * 
 * \param pacman pacman
 */
void DesalocaPacman(tPacman* pacman){
    // liberar movimentos
    for(int i=0; i< pacman->nMovimentosSignificativos;i++){
        DesalocaMovimento(pacman->historicoDeMovimentosSignificativos[i]);
    }
    free(pacman->historicoDeMovimentosSignificativos);
    // liberar trilha
    for(int i=0; i< pacman->nLinhasTrilha;i++){
        free(pacman->trilha[i]);
    }
    free(pacman->trilha);

    free(pacman);

}

/**
 * Retorna o número atual de movimentos do pacman
 * 
 * \param pacman pacman
 */
int ObtemNumeroAtualMovimentosPacman(tPacman* pacman){
    return pacman->nMovimentosBaixo + pacman->nMovimentosCima + pacman->nMovimentosDireita + pacman->nMovimentosEsquerda; 
}

/**
 * Retorna o número de movimentos sem pontuar do pacman
 * 
 * \param pacman pacman
 */
int ObtemNumeroMovimentosSemPontuarPacman(tPacman* pacman){
    return ObtemNumeroAtualMovimentosPacman(pacman) - ObtemPontuacaoAtualPacman(pacman);
}

/**
 * Retorna o número de colisões com a parede do pacman
 * 
 * \param pacman pacman
 */
int ObtemNumeroColisoesParedePacman(tPacman* pacman){
    return pacman->nColisoesParedeBaixo + pacman->nColisoesParedeCima + pacman->nColisoesParedeDireita + pacman->nColisoesParedeEsquerda;
}

/**
 * Retorna o número de movimentos para baixo do pacman
 * 
 * \param pacman pacman
 */
int ObtemNumeroMovimentosBaixoPacman(tPacman* pacman){
    return pacman->nMovimentosBaixo;
};

/**
 * Retorna o número de frutas comidas para baixo pelo pacman
 * 
 * \param pacman pacman
 */
int ObtemNumeroFrutasComidasBaixoPacman(tPacman* pacman){
    return pacman->nFrutasComidasBaixo;
}

/**
 * Retorna o número de colisões com a parede para baixo
 * 
 * \param pacman pacman
 */
int ObtemNumeroColisoesParedeBaixoPacman(tPacman* pacman){
    return pacman->nColisoesParedeBaixo;
}

/**
 * Retorna o número de movimentos para baixo do pacman
 * 
 * \param pacman pacman
 */
int ObtemNumeroMovimentosCimaPacman(tPacman* pacman){
    return pacman->nMovimentosCima;
}

/**
 * Retorna o número de frutas comidas para cima pelo pacman
 * 
 * \param pacman pacman
 */
int ObtemNumeroFrutasComidasCimaPacman(tPacman* pacman){
    return pacman->nFrutasComidasCima;
}

/**
 * Retorna o número de colisões com a parede para cima
 * 
 * \param pacman pacman
 */
int ObtemNumeroColisoesParedeCimaPacman(tPacman* pacman){
    return pacman->nColisoesParedeCima;
}

/**
 * Retorna o número de movimentos para a esquerda do pacman
 * 
 * \param pacman pacman
 */
int ObtemNumeroMovimentosEsquerdaPacman(tPacman* pacman){
    return pacman->nMovimentosEsquerda;
}

/**
 * Retorna o número de frutas comidas para a esquerda pelo pacman
 * 
 * \param pacman pacman
 */
int ObtemNumeroFrutasComidasEsquerdaPacman(tPacman* pacman){
    return pacman->nFrutasComidasEsquerda;
}

/**
 * Retorna o número de colisões com a parede para esquerda
 * 
 * \param pacman pacman
 */
int ObtemNumeroColisoesParedeEsquerdaPacman(tPacman* pacman){
    return pacman->nColisoesParedeEsquerda;
}

/**
 * Retorna o número de movimentos para a direita do pacman
 * 
 * \param pacman pacman
 */
int ObtemNumeroMovimentosDireitaPacman(tPacman* pacman){
    return pacman->nMovimentosDireita;
}

/**
 * Retorna o número de frutas comidas para a direita pelo pacman
 * 
 * \param pacman pacman
 */
int ObtemNumeroFrutasComidasDireitaPacman(tPacman* pacman){
    return pacman->nFrutasComidasDireita;
}

/**
 * Retorna o número de colisões com a parede para direita
 * 
 * \param pacman pacman
 */
int ObtemNumeroColisoesParedeDireitaPacman(tPacman* pacman){
    return pacman->nColisoesParedeDireita;
}

/**
 * Retorna o número de movimentos significativos do pacman
 * 
 * \param pacman pacman
 */
int ObtemNumeroMovimentosSignificativosPacman(tPacman* pacman){
    return pacman->nMovimentosSignificativos;
}

/**
 * Retorna a pontuação atual do pacman
 * 
 * \param pacman pacman
 */
int ObtemPontuacaoAtualPacman(tPacman* pacman){
    return pacman->nFrutasComidasBaixo + pacman->nFrutasComidasCima + pacman->nFrutasComidasDireita + pacman->nFrutasComidasEsquerda;
}

#endif

