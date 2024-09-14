#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm> 
#include <ctime>  

int xx = 2;
int yy = 1;

class Estados{
public:

    int tabuleiro[3][3] = {{1,2,3},{4,5,6},{8,7,0}};

    Estados sucessao(int input){ // 0 (<-) // 1 (^) // 2 (->) // 3 (v)
        Estados novoEstado;

        memcpy(novoEstado.tabuleiro, this->tabuleiro, 3 * 3 * sizeof(int)); //copia o tabuleiro do estado atual pro novo

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
        std::cout << "-----" << std::endl;
    }

    bool checkForWin(){
        int resp[3][3] = {{1,2,3},{4,5,6},{7,8,0}}; //tabuleiro de resposta

        if(memcmp(&resp, &this->tabuleiro, sizeof(resp)) == 0){ //compara os blocos de memória para ver se são iguais
        std::cout << "Vitoria!" << std::endl;
        return true;} // Matrizes são iguais
        else{ return false;}
    }

    bool isSolvable(){
        int flatPuzzle[9]; // Array para linearizar o tabuleiro
        int index = 0;

        // Transforma a matriz em um array unidimensional
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                flatPuzzle[index++] = this->tabuleiro[i][j];
            }
        }

        int inversions = 0;
        for (int i = 0; i < 9 - 1; ++i) {
            for (int j = i + 1; j < 9; ++j) {
                // Ignora o zero na contagem de inversões
                if (flatPuzzle[i] && flatPuzzle[j] && flatPuzzle[i] > flatPuzzle[j]) {
                    inversions++;
                }
            }
        }
        
        // O puzzle é solucionável se o número de inversões for par
        return (inversions % 2 == 0);
    }

    void createTabuleiro(){
        int numbers[9];
        while(this->isSolvable() == false){

        for (int i = 0; i < 9; ++i) {
            numbers[i] = i;
        }

        std::srand(time(0)); 
        std::random_shuffle(numbers, numbers + 9);

        // Popula a matriz 3x3 com os números embaralhados
        int index = 0;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                tabuleiro[i][j] = numbers[index++];
            }
        }
        }
    }
};

int main(){

    Estados novoJogo;
    novoJogo.createTabuleiro();
    novoJogo.imprimeTabuleiro();

    return 0;
}