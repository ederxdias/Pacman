#ifndef TMAPA_H_
#define TMAPA_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "tPosicao.h"
#include "tTunel.h"
#include "constantes.h"

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
    tTunel* tunel;
} tMapa;

/**
 * Cria o mapa dinamicamente
 * \param caminho caminho do arquivo com as configurações do mapa
 */
tMapa* CriaMapa(const char* caminhoConfig){
       char caminho[TAM_MAX_C] = {'\0'} ;
    // printf("%s\n", caminhoConfig);
    if(!caminhoConfig){
        printf("ERRO: O diretório de arquivos de configuração nao foi informado\n");
        exit(1);
    }
    strcat(caminho,caminhoConfig);
    strcat(caminho,"/mapa.txt");
    FILE *arquivo = fopen(caminho,"r");
    if(!arquivo){
        printf("ERRO: nao foi possível ler o arquivo /minhapasta/arquivo.txt\n");
    }
    tMapa * mapa = (tMapa *) malloc(sizeof(tMapa));
    fscanf(arquivo,"%d%*c", &mapa->nMaximoMovimentos);
    // printf("%d\n",mapa->nMaximoMovimentos);
    
    mapa->nLinhas = 0;
    mapa->nColunas = 0;
    mapa->nFrutasAtual = 0;
    char caracter='\0';
    int inicio = true;
    while( fscanf(arquivo,"%c", &caracter) == 1){
        
        if(caracter == '\n'){
            mapa->nLinhas++;
            inicio = false;
        }else if(inicio == true){
            mapa->nColunas++;
        }

        // contar frutas

        if(caracter == FRUTA){
            mapa->nFrutasAtual++;
        }
        
    }

    // retornar o ponteiro do arquivo para grid
    fseek(arquivo, 3, SEEK_SET);

    // Inicializar grid
    mapa->grid = (char **) malloc(sizeof(char*)*mapa->nLinhas);
    for(int i=0; i< mapa->nLinhas;i++){
        mapa->grid[i] = (char *) malloc(sizeof(char)*mapa->nColunas);
    }
    // Le grid
    // le de novo o inicio do arquivo
    // fscanf(arquivo,"%d", &mapa->nMaximoMovimentos);
    for(int i=0; i < mapa->nLinhas;i++){
        fscanf(arquivo,"%*c");
        for(int j=0; j< mapa->nColunas;j++){
            
            fscanf(arquivo,"%c",&mapa->grid[i][j]);
        }
    }
    // printf("%d %d \n", mapa->nLinhas, mapa->nColunas);
    // imprimir mapa

    fclose(arquivo);

    FILE *inicializacao = fopen("./saida/inicializacao.txt","w");
    if(!inicializacao){
        printf("ERRO nao foi possivel criar o arquivo ./inicializacao.txt\n");
        exit(1);
    }
    

    int tuneis1E2=1;
    int linhaAcesso1=0,colunaAcesso1=0, linhaAcesso2=0,colunaAcesso2=0;
    int posicaoLinhaInicial=0, posicaoColunaInicial=0;
    int i,j;
    for( i=0; i < mapa->nLinhas;i++){
        for( j=0; j< mapa->nColunas;j++){
            
            printf("%c", mapa->grid[i][j]);
            fprintf(inicializacao,"%c",mapa->grid[i][j]);
            if(mapa->grid[i][j]== TUNEL && tuneis1E2 ==1){
                tuneis1E2 = 2;
                linhaAcesso1 = i;
                colunaAcesso1 =j;
            }else if(mapa->grid[i][j]==TUNEL && tuneis1E2 ==2){
                linhaAcesso2 = i;
                colunaAcesso2 = j;
            }else if(mapa->grid[i][j]==PACMAN){
                posicaoLinhaInicial =i;
                posicaoColunaInicial=j;
            }
        }
        printf("\n");
        fprintf(inicializacao,"\n");
    }

    fprintf(inicializacao,"Pac-Man comecara o jogo na linha %d e coluna %d",
    posicaoLinhaInicial, posicaoColunaInicial);
    fclose(inicializacao);

    mapa->tunel = CriaTunel(linhaAcesso1,colunaAcesso1,linhaAcesso2,colunaAcesso2);
    // printf("%d\n", mapa->nFrutasAtual);

}

/**
 * Obtem a posição de um item do mapa
 * \param mapa mapa
 * \param item item a ser procurado no mapa
 */

tPosicao* ObtemPosicaoItemMapa(tMapa* mapa, char item){
    tPosicao * posicao = CriaPosicao(0,0);
// o item so pode ser o pacman ou os fantasmas porque só tem um decada no mapa
    for(int i=0 ; i < mapa->nLinhas;i++){
        for(int j=0; j < mapa->nColunas;j++){
            if(mapa->grid[i][j] == item){
                DesalocaPosicao(posicao);
                posicao = CriaPosicao(i,j);
            }
        }
    }
    return posicao;
}

/**
 * Retorna o túnel do mapa com os 2 acessos
 * \param mapa mapa
 */
tTunel* ObtemTunelMapa(tMapa* mapa){
    return mapa->tunel;
}

/**
 * Obtem o item do mapa dada a posição
 * \param mapa mapa
 * \param posicao posicao do item a ser retornado
 */
char ObtemItemMapa(tMapa* mapa, tPosicao* posicao){
    return mapa->grid[ObtemLinhaPosicao(posicao)][ObtemColunaPosicao(posicao)];
}

/**
 * Retorna o número de linhas do mapa
 * \param mapa mapa
 */
int ObtemNumeroLinhasMapa(tMapa* mapa){
    return mapa->nLinhas;
}

/**
 * Retorna o número de colunas do mapa
 * \param mapa mapa
 */
int ObtemNumeroColunasMapa(tMapa* mapa){
    return mapa->nColunas;
}

/**
 * Retorna a quantidade de frutas iniciais do mapa
 * \param mapa mapa
 */
int ObtemQuantidadeFrutasIniciaisMapa(tMapa* mapa){
    return mapa->nFrutasAtual;
}

/**
 * Retorna o número máximo de movimentos permitidos do mapa
 * \param mapa mapa
 */
int ObtemNumeroMaximoMovimentosMapa(tMapa* mapa){
    return mapa->nMaximoMovimentos;
}

/**
 * Retorna se a posição passada como parâmetro representa uma comida no mapa
 * \param mapa mapa
 * \param posicao posicao a ser verificada
 */
bool EncontrouComidaMapa(tMapa* mapa, tPosicao* posicao){
    if(ObtemItemMapa(mapa,posicao) == FRUTA){
        return true;
    }else return false;
}

/**
 * Retorna se a posição passada como parâmetro representa uma parede no mapa
 * \param mapa mapa
 * \param posicao posicao a ser verificada
 */
bool EncontrouParedeMapa(tMapa* mapa, tPosicao* posicao){
    if(ObtemItemMapa(mapa,posicao) == PAREDE){
        return true;
    }else return false;
}

/**
 * Atualiza um item do mapa
 * \param mapa mapa
 * \param posicao posicao do item
 * \param item posicao item que vai atualizar o mapa
 */
bool AtualizaItemMapa(tMapa* mapa, tPosicao* posicao, char item){
    bool atualiza = true;
    if(ObtemLinhaPosicao(posicao)>= mapa->nLinhas || ObtemColunaPosicao(posicao)>= mapa->nColunas
    || ObtemLinhaPosicao(posicao) < 0 || ObtemColunaPosicao(posicao) < 0){
        atualiza = false;
    }
    mapa->grid[ObtemLinhaPosicao(posicao)][ObtemColunaPosicao(posicao)] = item;
    return atualiza;
}

/**
 * Verifica se o mapa possui tunel ou não
 * \param mapa mapa
 */
bool PossuiTunelMapa(tMapa* mapa){
    for(int i=0 ; i < mapa->nLinhas;i++){
        for(int j=0; j < mapa->nColunas;j++){
            if(mapa->grid[i][j] == TUNEL){
            return true;
            }
        }
    }
    return false;
}

/**
 * Retorna se o tunel foi acessado ou não
 * \param mapa mapa
 * \param posicao posicao a ser verificada
 */
bool AcessouTunelMapa(tMapa* mapa, tPosicao* posicao){
    return EntrouTunel(mapa,posicao);
}

/**
 * Entra no túnel do mapa.
 * \param mapa mapa
 * \param posicao posicao que vai entrar no túnel
 */
void EntraTunelMapa(tMapa* mapa, tPosicao* posicao){
    LevaFinalTunel(ObtemTunelMapa(mapa),posicao);
}

/**
 * Libera o espaço alocado para a estrutura tMapa
 * \param mapa mapa
 */
void DesalocaMapa(tMapa* mapa){
    for(int i=0; i< mapa->nLinhas;i++){
        free(mapa->grid[i]);
    }

    free(mapa->grid);
    DesalocaTunel(mapa->tunel);
    free(mapa);
}

#endif

