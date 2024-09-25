// tokens.cpp
#include "tokens.hpp"
#include <fstream>
#include <iomanip>
#include <iostream>


// Definição da função
void writeTokensToFile(const std::string& filename, std::vector<Token> tokens) {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o arquivo." << std::endl;
        return;
    }

    int tokenWidth = 20;
    int valueWidth = 25;

    file << std::left << std::setw(tokenWidth) << "Token Type"
         << std::setw(valueWidth) << "Value" << std::endl;
    file << std::string(tokenWidth + valueWidth, '-') << std::endl;

    for (const auto& tok : tokens) {
        file << std::left << std::setw(tokenWidth) << tok.lexema
             << std::setw(valueWidth) << tok.simbolo << std::endl;
    }

    file.close();
}
