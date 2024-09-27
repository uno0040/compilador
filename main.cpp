#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "tokens.hpp"
#include "lexical.hpp"

using namespace std;

int main() {
    string filename = "oi.txt";
    ifstream arquivo(filename);
    int c = 0;
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo!" << std::endl;
        return 1;
    }
    vector<string> teste;
    vector<string> res;
    while (!arquivo.eof()) {
        teste = analisadorLexical(arquivo);
        res.push_back(teste[0]);
        res.push_back(teste[1]);
        cout << res[c] << " " << res[c+1] << endl;
        c = c + 2;
    }

    return 0;
}