#ifndef LEXICAL_HPP
#define LEXICAL_HPP

#include <string>
#include <vector>
#include "sintatico.hpp"

using namespace std;



// void writeTokensToFile(const std::string& filename, std::vector<Token> tokens);
Token analisadorLexical(ifstream &file,TabelaDeSimbolos& table);

#endif