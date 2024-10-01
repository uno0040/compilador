#ifndef ERROS_HPP
#define ERROS_HPP

#include <string>
#include <fstream> // Inclua a biblioteca fstream para usar ifstream
using namespace std;

// Declaração da função writeErrors
void writeErrors(const int linha, ifstream& codigo_fonte, const string& lista_erros, const string& erro);

#endif // ERROS_HPP
