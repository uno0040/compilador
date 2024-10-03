#include "tokens.hpp"
#include <fstream>
#include <iomanip>
#include <iostream>

using namespace std;

// -------------------- 
//  lista de tokens 
//    A lista de tokens vai possuir o formato : Lexema Simbolo
// --------------------

// Supondo que a estrutura Token esteja definida em tokens.hpp
// struct Token {
//     string lexema;
//     string simbolo;
// };

void writeTokensToFile(const string& filename, const Token& token) {
    // Abre o arquivo no modo de append
    ofstream file(filename, ios::app);

    if (!file.is_open()) {
        cerr << "Erro ao abrir o arquivo." << endl;
        return;
    }

    // Definimos o tamanho de largura em caracteres 
    int tokenWidth = 20;
    int valueWidth = 25;

    // Se o arquivo está vazio, escrevemos o cabeçalho
    file.seekp(0, ios::end);  // Vai para o final do arquivo
    if (file.tellp() == 0) {  // Verifica se o arquivo está vazio
        file << left << setw(tokenWidth) << "Lexema" << setw(valueWidth) << "Simbolo" << endl;
        file << string(tokenWidth + valueWidth, '-') << endl;
    }

    // Escrevemos o token no arquivo 
    file << left << setw(tokenWidth) << token.lexema
         << setw(valueWidth) << token.simbolo << endl;

    file.close();
}

