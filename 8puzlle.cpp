#include <iostream>
#include <cstring>
#include <algorithm> 
#include <ctime>  
#include <conio.h>

int xx = 0;
int yy = 0;

class Estados{
public:

    int tabuleiro[3][3] = {{1,2,3},{4,5,6},{8,7,0}};

    //função que retorna um objeto de Estado novo após um input
    Estados sucessao(char input){ // 0 (<-) // 1 (^) // 2 (->) // 3 (v)
        Estados novoEstado;

        memcpy(novoEstado.tabuleiro, this->tabuleiro, 3 * 3 * sizeof(int)); //copia o tabuleiro do estado atual pro novo

        int x = xx;
        int y = yy;

        switch(input){
            case 'a': y--; break; //x vai pra esquerda
            case 'w': x--; break; //y vai pra cima
            case 'd': y++; break; //x vai para direita
            case 's': x++ ; break; //y vai para baixo
        }

        if(x >= 0 && x < 3 && y >= 0 && y < 3){ //verifica se ta dentro do possível
        std::swap(novoEstado.tabuleiro[x][y], novoEstado.tabuleiro[xx][yy]); //faz a troca dos valores
        xx = x; yy = y; //atualiza as coordenadas gerais
        }

        return novoEstado;
    }

    //Função que imprime o Estado atual
    void imprimeTabuleiro() {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                std::cout << this->tabuleiro[i][j] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << "-----" << std::endl;
    }

    //Função que verifica se o Estado atual é o final e retorna true ou false
    bool checkForWin(){
        int resp[3][3] = {{1,2,3},{4,5,6},{7,8,0}}; //tabuleiro de resposta

        if(memcmp(&resp, &this->tabuleiro, sizeof(resp)) == 0){ //compara os blocos de memória para ver se são iguais
        std::cout << "Vitoria!" << std::endl;
        return true;} // Matrizes são iguais
        else{ return false;}
    }

    //Verifica se o Estado inicial é resolviveu
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

    //Cria um Estado inicial resolvivel
    void createTabuleiro(){
        
        int numbers[9] = {0,1,2,3,4,5,6,7,8};
        while(this->isSolvable() == false){

        std::srand(time(0)); 
        std::random_shuffle(numbers, numbers + 9);

        // Popula a matriz 3x3 com os números embaralhados
        int index = 0;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                this->tabuleiro[i][j] = numbers[index++];
                if (this->tabuleiro[i][j] == 0){
                    xx = i;
                    yy = j; //atualiza as coordenadas globais
                }
            }
        }
        }
    }
};

class Game{
public:

    void startGame(){

        Estados novoJogo;
        novoJogo.createTabuleiro();
        novoJogo.imprimeTabuleiro();

        char input_teclado;

        while(novoJogo.checkForWin() == false){
            do {
            input_teclado = _getch();
            if (input_teclado != 'w' && input_teclado != 'a' && input_teclado != 's' && input_teclado != 'd') {
            std::cout << "Entrada invalida" << std::endl;
            }
            }while (input_teclado != 'w' && input_teclado != 'a' && input_teclado != 's' && input_teclado != 'd');
            
            //empilha o estado atual
            novoJogo = novoJogo.sucessao(input_teclado); 
            novoJogo.imprimeTabuleiro();
        }
    }
};

int main(){

    Game newGame;
    newGame.startGame();

    return 0;
}