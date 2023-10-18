#include "tRanking.h"


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


/**
 * Cria dinamicamente Uma estrutura que contem  os efeitos do comando
 * \param pacman ponteiro para tPacman
 * \param dereçao tecla do moviento
*/

tEfeitosComando* CriaEfeitosComando (tPacman *pacman,char direcao){
    tEfeitosComando* efeitos = (tEfeitosComando*) malloc(sizeof(tEfeitosComando));
    efeitos->direcao = direcao;
    COMANDO comando = DefinirComando(direcao);
    if(comando == MOV_BAIXO){
        efeitos->ColisoesParede = ObtemNumeroColisoesParedeBaixoPacman(pacman);
        efeitos->frutasPegas = ObtemNumeroFrutasComidasBaixoPacman(pacman);
        efeitos->numeroMovimentosComando = ObtemNumeroMovimentosBaixoPacman(pacman);
    }else if(comando == MOV_CIMA){
        efeitos->ColisoesParede = ObtemNumeroColisoesParedeCimaPacman(pacman);
        efeitos->frutasPegas = ObtemNumeroFrutasComidasCimaPacman(pacman);
        efeitos->numeroMovimentosComando = ObtemNumeroMovimentosCimaPacman(pacman);       
    }else if( comando == MOV_DIREITA){
        efeitos->ColisoesParede = ObtemNumeroColisoesParedeDireitaPacman(pacman);
        efeitos->frutasPegas = ObtemNumeroFrutasComidasDireitaPacman(pacman);
        efeitos->numeroMovimentosComando = ObtemNumeroMovimentosDireitaPacman(pacman);
    }else if(comando == MOV_ESQUERDA){
        efeitos->ColisoesParede = ObtemNumeroColisoesParedeEsquerdaPacman(pacman);
        efeitos->frutasPegas = ObtemNumeroFrutasComidasEsquerdaPacman(pacman);
        efeitos->numeroMovimentosComando = ObtemNumeroMovimentosEsquerdaPacman(pacman);
    }    

    return efeitos;
}



tRanking* CriaRanking(tPacman* pacman){
    tRanking * ranking = (tRanking*) malloc(sizeof(tRanking));
    ranking->tam = TAM_RANKING;
    ranking->vet = (tEfeitosComando**) malloc(sizeof(tEfeitosComando*)*4);
    ranking->vet[0] = CriaEfeitosComando(pacman,'a');
    ranking->vet[1] = CriaEfeitosComando(pacman,'w');
    ranking->vet[2] = CriaEfeitosComando(pacman,'s');
    ranking->vet[3] = CriaEfeitosComando(pacman,'d');
    return ranking;
}

tEfeitosComando* ObtemEfeitosComando(tRanking *ranking, int idx){
    return ranking->vet[idx];
}
int ObtemQtdFrutasPegas(tEfeitosComando *efeitos){
    return efeitos->frutasPegas;
}
int ObtemQtdColisoesParede(tEfeitosComando* efeitos){
    return efeitos->ColisoesParede;
}
int ObtemQtdMovimentosComando(tEfeitosComando* efeitos){
    return efeitos->numeroMovimentosComando;
}
char ObtemDirecaoComando(tEfeitosComando* efeitos){
    return efeitos->direcao;
}
int ComparaRanking(const void *a, const void *b) {
    // Converte os ponteiros genéricos de 'a' e 'b' para o tipo de dado apropriado
    const tEfeitosComando *efeitos_a = (const tEfeitosComando *)a;
    const tEfeitosComando *efeitos_b = (const tEfeitosComando *)b;

    // Comparação para ordenação decrescente
 
    if (efeitos_a->frutasPegas < efeitos_b->frutasPegas) {
        return 1;  // 'a' vem antes de 'b'
    } else if (efeitos_a->frutasPegas > efeitos_b->frutasPegas) {
        return 0;   // 'b' vem antes de 'a'
    } else {
        // Quantidade de frutas pegas iguais
        if (efeitos_a->ColisoesParede > efeitos_b->ColisoesParede) {
            return 1;  // 'a' vem antes de 'b'
        } else if (efeitos_a->ColisoesParede < efeitos_b->ColisoesParede) {
            return 0;
        }else{
            // Quantidade de Colisões na parede iguais
            if(efeitos_a->numeroMovimentosComando < efeitos_b->numeroMovimentosComando){
                return 1;
            }else if(efeitos_a->numeroMovimentosComando > efeitos_b->numeroMovimentosComando){
                return 0;
            }
        }
       
    }
}

int ObtemTamRanking(tRanking* ranking){
    return ranking->tam;
}

void OrdernaRanking(tRanking * ranking, int tam, ftpComp cmp){
  for(int i=0; i < tam-1;i++){
    for(int j=0 ; j<tam -i -1; j++){
      if(cmp(ranking->vet[j], ranking->vet[j+1]) ){
        // Trocar os ponteiros de lugar
        tEfeitosComando* temp = ranking->vet[j];
        ranking->vet[j] =ranking->vet[j+1];
        ranking->vet[j+1] = temp;
      }
    }
  }
}
void DesalocaEfeitosComando(tEfeitosComando * efeitosComando){
    free(efeitosComando);
}
void DesalocaRanking(tRanking* ranking){
    for(int i=0; i<ranking->tam){
        DesalocaEfeitosComando(ranking->vet[i]);
    }
    free(ranking->vet);
    free(ranking);
}

//(a, w, s ou d)