#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "tokens.hpp"
#include "lexical.hpp"
#include "sintatico.hpp"

using namespace std;

int main() {
    
    string filename = "oi.txt";
    ifstream Codigo_fonte(filename);
    

    // Erro de abertura de arquivo 
    if (!Codigo_fonte.is_open()) {
        cerr << "Erro ao abrir o arquivo!" << endl;
        return 1;
    }
    TabelaDeSimbolos table;
    Token inicio;
    int cont = 0;
    // Compilando o codigo fonte 
    while (!Codigo_fonte.eof()) {
        cont++;
        inicio = analisadorLexical(Codigo_fonte,table); 
        // analisadorSintatico(inicio)
        // table.display();
    }
    cout << cont << " itens analisados :P" << endl;
    return 0;
}