#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "tokens.hpp"
#include "lexical.hpp"
#include "sintatico.hpp"
#include "geracao.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Uso: " << argv[0] << " <arquivo_codigo_fonte>" << endl;
        return 1;   
    }
    
    string filename = argv[1];
    ifstream Codigo_fonte(filename);
    int linha = 1;
    // Limpa ou cria se não tiver criado o arquivo saida.txt
    limpar_arquivo();
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
    analisadorSintatico(Codigo_fonte,table);
        
    // }
    // table.display();
    return 0;
}