#ifndef TOKENS_HPP
#define TOKENS_HPP

#include <string>
#include <vector>

using namespace std;


// Estrutura basica de um token 

struct Token {
    string lexema; 
    string simbolo; 
    int linha;
};

// Deixa publico a função que vai escrever a lista de tokens 
void writeTokensToFile(const string& filename, const Token& tokens);



#endif