#include "tFantasmas.h"


int AchouFantasma(tMapa *mapa,char tipo, tPosicao * posicao){

    for(int i=0; i< ObtemNumeroLinhasMapa(mapa);i++){
        for(int j; j<ObtemNumeroColunasMapa(mapa);j++){
            tPosicao *posicaoTemp = CriaPosicao(i,j);
            AtualizaPosicao(posicao,posicaoTemp);
            if(ObtemItemMapa(mapa,posicao) == tipo){
                return 1;
            }
            DesalocaPosicao(posicaoTemp);
        }
    }
    return 0;
}

tFantasma *CriaFantasma(tPosicao *posicaoAtual ,char tipo){
    tFantasma * fantasma = (tFantasma*) malloc(sizeof(tFantasma));
    fantasma->posicaoAtual = posicaoAtual;
    fantasma->tipo = tipo;
    fantasma->passouFruta =0;
    fantasma->sentidoAtual = POSITIVO;

    return fantasma;
}

tVetFantasma *CriaVetFastama(){
    tVetFantasma *vetFantasma = (tVetFantasma*) malloc(sizeof(tVetFantasma));
    vetFantasma->tam =0;
    tFantasma **vet = (tFantasma **) malloc(sizeof(tFantasma*));
    return vetFantasma; 
}
void InseriNovoFantasmaVet(tVetFantasma *vetFantasma, tFantasma* fantasma){
    if(vetFantasma->tam){
       vetFantasma = realloc(vetFantasma,sizeof(tFantasma*)*(vetFantasma->tam+1)); 
    }
    vetFantasma->vet[vetFantasma->tam] = fantasma;
    vetFantasma->tam++;
}
void AfirmarPassouFruta(tFantasma *fantasma){
    fantasma->passouFruta =1;
}
void NegarPassouFruta(tFantasma * fantasma){
    fantasma->passouFruta =0;
}
int PassouFruta(tFantasma *fantasma){
    return fantasma->passouFruta;
}
int SentidoAtualFantasma(tFantasma *fantasma){
    return fantasma->sentidoAtual;
}

void TrocarSentidoAtualFantasma(tFantasma *fantasma){
    if(SentidoAtualFantasma(fantasma) == POSITIVO){
        fantasma->sentidoAtual = NEGATIVO;
    }else {
        fantasma->sentidoAtual = POSITIVO;
    }

}

tPosicao * AndarDireitaFantasma(tFantasma* fantasma){
    return CriaPosicao(ObtemLinhaPosicao(fantasma->posicaoAtual),ObtemColunaPosicao(fantasma->posicaoAtual)+1);
}

tPosicao * AndarEsquerdaFantasma(tFantasma* fantasma){
    return CriaPosicao(ObtemLinhaPosicao(fantasma->posicaoAtual),ObtemColunaPosicao(fantasma->posicaoAtual)-1);
}

tPosicao * AndarCimaFantasma(tFantasma* fantasma){
    return CriaPosicao(ObtemLinhaPosicao(fantasma->posicaoAtual) -1,ObtemColunaPosicao(fantasma->posicaoAtual));
}


tPosicao * AndarBaixoFantasma(tFantasma* fantasma){
    return CriaPosicao(ObtemLinhaPosicao(fantasma->posicaoAtual)+1,ObtemColunaPosicao(fantasma->posicaoAtual));
}
tPosicao * FicarParado(tFantasma* fantasma){
    return fantasma->posicaoAtual;
}



void MoveFantasma(tMapa *mapa, tFantasma * fantasma){
    tPosicao *proximaPosicao;
     AtualizaItemMapa(mapa,fantasma->posicaoAtual,VAZIO);
    if(fantasma->tipo == 'B'){

        if(SentidoAtualFantasma == POSITIVO){
            proximaPosicao = AndarEsquerdaFantasma(fantasma);
        }else{
            proximaPosicao = AndarDireitaFantasma(fantasma);
        }

        // Verifica se o fantasma passou por uma fruta e restaura ela caso sim
        if(PassouFruta(fantasma)){
            AtualizaItemMapa(mapa,fantasma->posicaoAtual,FRUTA);
            NegarPassouFruta(fantasma);
        }

        // Verficar tipo da proxima posicao do mapa
        if(ObtemItemMapa(mapa,proximaPosicao) == FRUTA){

            AfirmarPassouFruta(fantasma);

        }else if(ObtemItemMapa(mapa,proximaPosicao)==PAREDE){

            TrocarSentidoAtualFantasma(fantasma);

            if(SentidoAtualFantasma(fantasma)== POSITIVO){
                proximaPosicao = AndarEsquerdaFantasma(fantasma);
            }else{
                proximaPosicao = AndarDireitaFantasma(fantasma);
            }         
            // verificar que depois de encontrar a parede e mudar de sentido o fantasma encontra uma fruta
            if(ObtemItemMapa(mapa,proximaPosicao) ==FRUTA){
                AfirmarPassouFruta(fantasma);
            }
            //Verificar se o fantasma esta preso entre duas paredes
            if(ObtemItemMapa(mapa,proximaPosicao) ==PAREDE){
                proximaPosicao = FicarParado(fantasma);               
            }
        }
        //Atualizar posicao do fantasma no mapa
        AtualizaPosicao(fantasma->posicaoAtual,proximaPosicao);
        AtualizaItemMapa(mapa,fantasma->posicaoAtual,fantasma->tipo);
        

    }else if(fantasma->tipo == 'C'){

        if(SentidoAtualFantasma == POSITIVO){
            proximaPosicao = AndarDireitaFantasma(fantasma);
        }else{
            proximaPosicao = AndarEsquerdaFantasma(fantasma);
        }

        // Verifica se o fantasma passou por uma fruta e restaura ela caso sim
        if(PassouFruta(fantasma)){
            AtualizaItemMapa(mapa,fantasma->posicaoAtual,FRUTA);
            NegarPassouFruta(fantasma);
        }
  
        // Verficar tipo da proxima posicao do mapa
        if(ObtemItemMapa(mapa,proximaPosicao) == FRUTA){

            AfirmarPassouFruta(fantasma);

        }else if(ObtemItemMapa(mapa,proximaPosicao)==PAREDE){

            TrocarSentidoAtualFantasma(fantasma);

            if(SentidoAtualFantasma(fantasma)== POSITIVO){
                proximaPosicao = AndarDireitaFantasma(fantasma);
            }else{
                proximaPosicao = AndarEsquerdaFantasma(fantasma);
            }

            // verificar que depois de encontrar a parede e mudar de sentido o fantasma encontra uma fruta
            if(ObtemItemMapa(mapa,proximaPosicao) ==FRUTA){
                AfirmarPassouFruta(fantasma);
            }
            //Verificar se o fantasma esta preso entre duas paredes
            if(ObtemItemMapa(mapa,proximaPosicao) ==PAREDE){
                proximaPosicao = FicarParado(fantasma);
            }
        }
        //Atualizar posicao do fantasma no mapa
        AtualizaPosicao(fantasma->posicaoAtual,proximaPosicao);
        AtualizaItemMapa(mapa,fantasma->posicaoAtual,fantasma->tipo);

    }else if(fantasma->tipo == 'P'){

        if(SentidoAtualFantasma == POSITIVO){
            proximaPosicao = AndarCimaFantasma(fantasma);
        }else{
            proximaPosicao = AndarBaixoFantasma(fantasma);
        }

        // Verifica se o fantasma passou por uma fruta e restaura ela caso sim
        if(PassouFruta(fantasma)){
            AtualizaItemMapa(mapa,fantasma->posicaoAtual,FRUTA);
            NegarPassouFruta(fantasma);
        }

        // Verficar tipo da proxima posicao do mapa      
        if(ObtemItemMapa(mapa,proximaPosicao) == FRUTA){

            AfirmarPassouFruta(fantasma);

        }else if(ObtemItemMapa(mapa,proximaPosicao)==PAREDE){

            TrocarSentidoAtualFantasma(fantasma);

            if(SentidoAtualFantasma(fantasma)== POSITIVO){
                proximaPosicao = AndarCimaFantasma(fantasma);
            }else{
                proximaPosicao = AndarBaixoFantasma(fantasma);
            }  
            
            // verificar que depois de encontrar a parede e mudar de sentido o fantasma encontra uma fruta
            if(ObtemItemMapa(mapa,proximaPosicao) ==FRUTA){
                AfirmarPassouFruta(fantasma);
            }
            //Verificar se o fantasma esta preso entre duas paredes
            if(ObtemItemMapa(mapa,proximaPosicao) ==PAREDE){
                proximaPosicao = FicarParado(fantasma);
            }
        }
        //Atualizar posicao do fantasma no mapa
        AtualizaPosicao(fantasma->posicaoAtual,proximaPosicao);
        AtualizaItemMapa(mapa,fantasma->posicaoAtual,fantasma->tipo);

    }else if(fantasma->tipo == 'I'){

        if(SentidoAtualFantasma == POSITIVO){
            proximaPosicao = AndarBaixoFantasma(fantasma);
        }else{
            proximaPosicao = AndarCimaFantasma(fantasma);
        }

        // Verifica se o fantasma passou por uma fruta e restaura ela caso sim
        if(PassouFruta(fantasma)){
            AtualizaItemMapa(mapa,fantasma->posicaoAtual,FRUTA);
            NegarPassouFruta(fantasma);
        }
          
        // Verficar tipo da proxima posicao do mapa    
        if(ObtemItemMapa(mapa,proximaPosicao) == FRUTA){

            AfirmarPassouFruta(fantasma);

        }else if(ObtemItemMapa(mapa,proximaPosicao)==PAREDE){

            TrocarSentidoAtualFantasma(fantasma);

            if(SentidoAtualFantasma(fantasma)== POSITIVO){
                proximaPosicao = AndarBaixoFantasma(fantasma);
            }else{
                proximaPosicao = AndarCimaFantasma(fantasma);
            }

            // verificar que depois de encontrar a parede e mudar de sentido o fantasma encontra uma fruta
            if(ObtemItemMapa(mapa,proximaPosicao) ==FRUTA){
                AfirmarPassouFruta(fantasma);
            }
            //Verificar se o fantasma esta preso entre duas paredes
            if(ObtemItemMapa(mapa,proximaPosicao) ==PAREDE){
                proximaPosicao = FicarParado(fantasma);
            }
        }
    }
    AtualizaPosicao(fantasma->posicaoAtual, proximaPosicao);
    AtualizaItemMapa(mapa,fantasma->posicaoAtual,fantasma->tipo);
    DesalocaPosicao(proximaPosicao);
}

void MoveVetFantasmas(tMapa *mapa, tVetFantasma *vetfantasma){
    for(int i=0; i<vetfantasma->tam;i++){
        MoveFantasma(mapa,vetfantasma->vet[i]);
    }
}
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


