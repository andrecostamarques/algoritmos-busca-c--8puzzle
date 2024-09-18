#include <iostream>
#include <cstring>
#include <algorithm> 
#include <ctime>  
#include <conio.h>
#include <locale.h> 
#include <windows.h>

int xx = 0;
int yy = 0;

class Estados{
public:
    int tabuleiro[3][3] = {{1,2,3},{4,5,6},{8,7,0}};

    //função que retorna um objeto de Estado novo após um input
    Estados sucessao(char input){ // a (<-) // w (^) // d (->) // s (v)
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
        std::cout << "\033[2J\033[1;1H";
        std::cout << "INITIAL STATE" << std::endl;
        novoJogo.createTabuleiro();
        novoJogo.imprimeTabuleiro();

        std::cout << "Choose an option!\n[1] PLAY\n[2] ALGORITHM" << std::endl;
        std::cout << "\n>> ";
        
        char input_teclado;
        std::cin >> input_teclado;

        switch (input_teclado) {
            case '1':
                std::cout << "\033[2J\033[1;1H";
                novoJogo.imprimeTabuleiro();
                while(novoJogo.checkForWin() == false){
                    do {
                        std::cout << "You have to move zero using WASD" << std::endl;
                        std::cout << ">> ";
                        input_teclado = _getch();
                        std::cout << input_teclado;
                        std::cout << "\n-----\n";
                        if (input_teclado != 'w' && input_teclado != 'a' && input_teclado != 's' && input_teclado != 'd') {
                            std::cout << "INVALID INPUT!" << std::endl;
                        }
                    } while (input_teclado != 'w' && input_teclado != 'a' && input_teclado != 's' && input_teclado != 'd');
                    
                    novoJogo = novoJogo.sucessao(input_teclado);
                    novoJogo.imprimeTabuleiro();
                }
                break;
            case '2':
                std::cout << "\033[2J\033[1;1H";
                //novoJogo.imprimeTabuleiro();
                std::cout << "Choose the algorithm\n[1] A*\n[2] BSF\n[3] DFS" << std::endl;
                std::cout << "\n>> ";

                char algoritmo;
                std::cin >> algoritmo;
                break;
        }
        
    }
};

int main()
{
    Game newGame;
    newGame.startGame();

    return 0;
}
