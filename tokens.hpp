#ifndef TOKENS_HPP
#define TOKENS_HPP

#include <string>
#include <vector>

struct Token {
    std::string lexema; 
    std::string simbolo; 
};

void writeTokensToFile(const std::string& filename, std::vector<Token> tokens);
// std::vector<std::string> analisadorLexical(std::ifstream &file);

#endif