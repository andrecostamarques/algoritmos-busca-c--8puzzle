#include <iostream>
#include <cstring>
#include <vector>

int xx = 2;
int yy = 1;

class Estados{
public:
    int tabuleiro[3][3] = {{1,2,3},{4,5,6},{7,0,8}}; //tabuleiro do Estado, movimenta o 0

    Estados sucessao(int input){ // 0 (<-) // 1 (^) // 2 (->) // 3 (v)
        Estados novoEstado;

        memcpy(novoEstado.tabuleiro, this->tabuleiro, 3 * 3 * sizeof(int));

        int x = xx;
        int y = yy;

        switch(input){
            case 0: y--; break; //x vai pra esquerda
            case 1: x--; break; //y vai pra cima
            case 2: y++; break; //x vai para direita
            case 3: x++ ; break; //y vai para baixo
        }

        if(x >= 0 && x < 3 && y >= 0 && y < 3){ //verifica se ta dentro do possível
        std::swap(novoEstado.tabuleiro[x][y], novoEstado.tabuleiro[xx][yy]); //faz a troca dos valores
        xx = x; yy = y; //atualiza as coordenadas gerais
        }

        return novoEstado;
    }

    void imprimeTabuleiro() {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                std::cout << this->tabuleiro[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    bool checkForWin(){
        int resp[3][3] = {{1,2,3},{4,5,6},{7,8,0}}; //tabuleiro de resposta

        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (this->tabuleiro[i][j] != resp[i][j]) {
                    return false; // Matrizes são diferentes
                }
            }
        }
        std::cout << "Vitoria!" << std::endl;
        return true; // Matrizes são iguais
    }
};

int main(){

    Estados novoJogo;
    novoJogo = novoJogo.sucessao(2);
    novoJogo.checkForWin();

    return 0;
}