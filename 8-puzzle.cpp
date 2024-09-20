#include <iostream>
#include <cstring>
#include <algorithm> 
#include <ctime>  
#include <conio.h>
#include <locale.h> 
#include <windows.h>
#include <iomanip>
#include <cmath>
#include <string>
#include <unordered_map>
#include <queue>
#include <stack>

int state = 0;
// Variaveis de localização do 0, são globais 

std::unordered_map<int, int> mapEstadosVisitados;
// Chave é o idEstado | valor é inutil, porém 1 é visto e 0 não
// Cada estado assim que descoberto, vai pra HashTable de descuberto com o seu idEstado, a partir disso, dá para descobrir se foi visitado em O(1)

class Estados{
public:

    int y, x;
    int tabuleiro[3][3] = {{1,2,3},{4,5,6},{8,7,0}};
    // Necessário salvar a localização do 0 no Estado atual para o histórico.
   
    // A função insere o Estado atual na HashTable e retorna um objeto de novo Estado.
    Estados sucessao(char input){ 

        Estados novoEstado;
        
        memcpy(novoEstado.tabuleiro, this->tabuleiro, 3 * 3 * sizeof(int)); 
        // Copia o tabuleiro do estado atual pro novo

        int x2 = x;
        int y2 = y;

        switch(input){
            case 'a': y2--; break; // x vai pra esquerda
            case 'w': x2--; break; // y vai pra cima
            case 'd': y2++; break; // x vai para direita
            case 's': x2++ ; break;// y vai para baixo
        }

        if(x2 >= 0 && x2 < 3 && y2 >= 0 && y2 < 3){ 
            std::swap(novoEstado.tabuleiro[x2][y2], novoEstado.tabuleiro[x][y]); 
            novoEstado.x = x2; novoEstado.y = y2; 
            // Faz a verificação da mudança do estado, atualiza o tabuleiro e as variaveis globais
        }

        //mapEstadosVisitados.insert({intflatTabuleiro(this->tabuleiro, sizeof(this->tabuleiro)), 1}); 
        // Insere o Estado atual na HashTable

        return novoEstado;
    }

    // Imprime o Estado atual
    void imprimeTabuleiro() {
        std::cout << "STATE " << state << std::endl; 
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                std::cout << this->tabuleiro[i][j] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << "-----" << std::endl;
        //verMemoria(this->tabuleiro, sizeof(this->tabuleiro));
    }

    // Verifica se o Estado é o final.
    bool checkForWin(){
        int resp[3][3] = {{1,2,3},{4,5,6},{7,8,0}}; 
        // Compara com o resultaod esperado.

        if(memcmp(&resp, &this->tabuleiro, sizeof(resp)) == 0){ 
        std::cout << "Vitoria!" << std::endl;
        return true;}
        // O bloco inteiro de memória do tabuleiro no Heap é comparado, assim, é evitado o uso de For dentro de For.
        else{ return false;}
    }

    // Verifica se o Estado inicial é solvable
    bool isSolvable(){
        int* flatPuzzle = (int*)malloc(9 * sizeof(int));
        flatTabuleiro(this->tabuleiro, flatPuzzle);
        // Um ponteiro recebe o tabuleiro dentro de um vetor

        int inversions = 0;
        for (int i = 0; i < 9 - 1; ++i) {
            for (int j = i + 1; j < 9; ++j) {
            // Ignora o zero na contagem
                if (flatPuzzle[i] && flatPuzzle[j] && flatPuzzle[i] > flatPuzzle[j]) {
                    inversions++;
                }
            }
        }
        free(flatPuzzle);
        return (inversions % 2 == 0);
    }

    // Cria um Estado inicial soluvel
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
                    this->x = i;
                    this->y = j; 
                    // Atualizam as coordenadas globais
                }
            }
        }
        }
    }

    // Retorna void, recebe um ponteiro para o inicio do tabuleiro e o tamanho do tabuleiro.
    // Printa o tabuleiro no formato de array.
    void flatTabuleiro(void* ptr) {
    unsigned char* bytePtr = static_cast<unsigned char*>(ptr); 
    // Hack para poder ver o valor do numero (char tem exatamente 1 byte (2 hexa))

    for (size_t i = 0; i < (3 * 3 * sizeof(int)); i += 4) { // Pegar 1 byte e pular 3
        std::cout << (int)bytePtr[i] << " " ; // Byte é transformado de char (1 byte) para int (4 byte)
    }
    std::cout << std::endl; 
    }

    // Retorna void, recebe um ponteiro para o inicio do tabuleiro, o tamanho do tabuleiro, e o ponteiro para um vetor, esse vetor será modificado com a matriz flated.
    void flatTabuleiro(void* ptr, int* ptrVetor) {
    unsigned char* bytePtr = static_cast<unsigned char*>(ptr); 
    for (size_t i = 0; i < (3 * 3 * sizeof(int)); i += 4) {  
        ptrVetor[i/4] = (int)bytePtr[i]; //Salva no vetor os números da matriz.
    }
    }

    // Retorna um numero inteiro concatenado com todos os valores da matriz, recebe um ponteiro para o inicio do tabuleiro e o tamanho do tabuleiro.
    // Retorna o ID para a HashTable
    int intflatTabuleiro(void* ptr) { 
    unsigned char* bytePtr = static_cast<unsigned char*>(ptr); 
    std::string temp;
    for (size_t i = 0; i <(3 * 3 * sizeof(int)); i += 4) {  
        temp.append(std::to_string((int)bytePtr[i])); // Transforma em String para concatenar de maneira mais facil
    }
    int concat = std::stoi(temp); // Transforma de string para Int.
    return concat;
    }

//     void verMemoria(void* ptr, size_t tamanho) { // So para debuggar quando tiver usando memória
//     unsigned char* bytePtr = static_cast<unsigned char*>(ptr);

//     for (size_t i = 0; i < tamanho; ++i) {
//         std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)bytePtr[i] << " ";
//     }
//     std::cout << std::dec << std::endl;  // Volta para o formato decimal
// }


};
class Solver{
public:
    std::queue<Estados> filaVisita;
    std::stack<Estados> pilhaVisita;
    std::stack<int> pilhaInt;
    Estados atual;

    Solver(Estados estadoRaiz){
        atual = estadoRaiz;
    }

    void printMatriz(int numero) {
    // Converte o idEstado para uma matriz e a printa

    std::string numStr = std::to_string(numero);

    while (numStr.length() < 9) {
        numStr.insert(numStr.begin(), '0');  // Adiciona '0' no início da string se precisar
    }
    
    // Imprimir o número em formato de matriz 3x3
    for (int i = 0; i < 9; i++) {
        std::cout << numStr[i] << " ";
        
        // Quebrar a linha após cada 3 elementos
        if ((i + 1) % 3 == 0) {
            std::cout << std::endl;
        }
    }
}

};

class Astar : public Solver{

};

class BFS : public Solver{
public:
    std::string str = "wdas";
    BFS(Estados estadoRaiz) : Solver(estadoRaiz) {
    }
    // Retona o Estado final, recebe o Estado Raiz (PAI) e passa pelo algoritmo BFS.
    Estados solve(){
        filaVisita.push(this->atual);   
        mapEstadosVisitados.insert({this->atual.intflatTabuleiro(this->atual.tabuleiro), 1}); // Adiciona o estado PAI no Mapa de lidos com o valor 1.

        // Enquanto a fila não estiver vazia
        while(!filaVisita.empty()){
            auto u = filaVisita.front(); filaVisita.pop(); // Tira o próximo item da fila
            if(u.checkForWin() == false){   // Se o proximo item NÃO for a vitória
            for(int i = 0; i < 4; i++){
            Estados filho= u.sucessao(str[i]); // Pega o filho dele
            // Se o filho dele não tiver sido visto, continue
            if(mapEstadosVisitados.count(filho.intflatTabuleiro(filho.tabuleiro)) == 0){ 
                filaVisita.push(filho); // Empilha o filho para analisar depois
                mapEstadosVisitados.insert({filho.intflatTabuleiro(filho.tabuleiro), u.intflatTabuleiro(u.tabuleiro)}); 
                // Adiciona o estado atual no Mapa de lidos e adiciona o id do pai no valor, assim é possível reconstruir o caminho
                ++state;
            } // Else, proximo filho
            }
        }else{return u;} // Retorna o estado de vitória.
    }
    }

    void reconstrucao(Estados final){
        // Não retorna nada, printa o caminho utilizado para chegar lá.

        int estadoID = final.intflatTabuleiro(final.tabuleiro); // Vai retornar o Pai dele

        while(estadoID != 1){       
            // Acessa o mapa Hash e pega os PAIS do caminho que geraram o resultado final
            int aux = mapEstadosVisitados[estadoID];
            pilhaInt.push(aux);
            estadoID = aux;
        }

        std::cout << "Quantidade de passos: " << pilhaInt.size() << std::endl; 
        std::cout << "\nPressione ENTER para proximo passo." << std::endl;

        pilhaInt.top();
        while(!pilhaInt.empty() ){
            estadoID = pilhaInt.top(); pilhaInt.pop();
            getchar();
            std::cout << "-----" << std::endl;
            printMatriz(estadoID);

        }
    }
};

class DFS : public Solver{

};


class Game{
public:

    void startGame(){
        Estados novoJogo;
        //std::cout << "\033[2J\033[1;1H";
        novoJogo.createTabuleiro();
        novoJogo.imprimeTabuleiro();

        std::cout << "Choose an option!\n[1] PLAY\n[2] ALGORITHM" << std::endl;
        std::cout << "\n>> ";
        
        char input_teclado;
        std::cin >> input_teclado;

        switch (input_teclado) {
            case '1':
                //std::cout << "\033[2J\033[1;1H";
                novoJogo.imprimeTabuleiro();
                while(novoJogo.checkForWin() == false){
                    do {
                        std::cout << "You have to move zero using WASD" << std::endl;
                        std::cout << ">> ";
                        input_teclado = _getch();
                        std::cout << input_teclado;
                        std::cout << "\n-----\n";
                        if (input_teclado != 'w' && input_teclado != 'a' && input_teclado != 's' && input_teclado != 'd' && input_teclado != 27) {
                            std::cout << "INVALID INPUT!" << std::endl;
                        }if(input_teclado == 27){
                            exit(0);
                        }
                    } while (input_teclado != 'w' && input_teclado != 'a' && input_teclado != 's' && input_teclado != 'd');
                    
                    novoJogo = novoJogo.sucessao(input_teclado);
                    novoJogo.imprimeTabuleiro();
                }
                break;
            case '2':
                //std::cout << "\033[2J\033[1;1H";
                //novoJogo.imprimeTabuleiro();
                std::cout << "Choose the algorithm\n[1] A*\n[2] BSF\n[3] DFS" << std::endl;
                std::cout << "\n>> ";

                int input_teclado2;
                std::cin >> input_teclado2;
                
                if(input_teclado2 == 1){
                    std::cout << "\n Ainda precisa implementar." << std::endl;
                    exit(0);
                }

                if(input_teclado2 == 2){
                    std::cout << "\nExecutando..." << std::endl;
                    BFS solver(novoJogo); // Cria o objetivo de Solver
                    Estados resolvido = solver.solve(); // Recebe o estado resolvido
                    resolvido.imprimeTabuleiro();
                    solver.reconstrucao(resolvido); // Reconstroi os passos.
                }

                if(input_teclado2 == 3){
                    std::cout << "\n Ainda precisa implementar." << std::endl;
                    exit(0);
                }

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
