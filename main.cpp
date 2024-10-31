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
    int linha = 1;

    // Erro de abertura de arquivo 
    if (!Codigo_fonte.is_open()) {
        cerr << "Erro ao abrir o arquivo!" << endl;
        return 1;
    }
    TabelaDeSimbolos table; // usada para o lexico
    TabelaDeSimbolos SymbolTable; // usada para o semantico
    Token inicio;
    // Compilando o codigo fonte 
    // while (!Codigo_fonte.eof()) {
        

        // inicio = analisadorLexical(Codigo_fonte,table); 
    analisadorSintatico(Codigo_fonte,table,SymbolTable);
        
    // }
    // table.display();
    return 0;
}