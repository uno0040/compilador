#include <iostream>
#include <fstream>
#include <string>

std::string lerProximaPalavra(std::ifstream &arquivo) {
    std::string palavra;
    if (arquivo >> palavra) {
        return palavra;
    } else {
        return ""; // Retorna uma string vazia se não houver mais palavras
    }
}

int main() {
    std::ifstream arquivo("oi.txt"); // Abra o arquivo para leitura
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo!" << std::endl;
        return 1;
    }

    std::string palavra;
    while (!(palavra = lerProximaPalavra(arquivo)).empty()) {
        std::cout << "Palavra lida: " << palavra << std::endl;
    }

    arquivo.close(); // Feche o arquivo após terminar a leitura
    return 0;
}
