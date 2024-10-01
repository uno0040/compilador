#include <iostream>
#include <fstream>
#include <string>
#include "erros.hpp"

using namespace std;

// Definindo as cores
const string RED_COLOR = "\033[31m";  // Código ANSI para vermelho
const string RESET_COLOR = "\033[0m"; // Código ANSI para resetar a cor

// Função para registrar um erro em um arquivo
void logError(const string& lista_erros, const string& erro) {
    ofstream file(lista_erros, ios::app); // Abre o arquivo para escrita (anexando no final)

    if (!file.is_open()) { // Verifica se o arquivo foi aberto corretamente
        cerr << "Erro ao abrir o arquivo de erros: " << lista_erros << endl;
        return;
    }

    file << left << erro << endl; // Escreve o erro no arquivo, alinhado à esquerda
    file.close(); // Fecha o arquivo
}

// Função para destacar uma linha em vermelho
void highlightLine(const int linha, ifstream& file) {
    string line;
    int currentLine = 0;

    while (getline(file, line)) {
        currentLine++;
        if (currentLine == linha) {
            // Muda a cor da linha para vermelho
            cout << RED_COLOR << line << RESET_COLOR << endl;
        } else {
            // Imprime a linha normalmente
            cout << line << endl;
        }
    }
}

// Função principal para processar erros
void writeErrors(const int linha, ifstream& codigo_fonte, const string& lista_erros, const string& erro) {
    // Registrar o erro
    logError(lista_erros, erro);
    // Destacar a linha referente ao erro
    highlightLine(linha, codigo_fonte);
}

// Exemplo de uso
int main() {
    int linhaDeErro = 3; // Linha que contém o erro
    string codigoFonte = "codigo_fonte.txt"; // Caminho para o arquivo de código fonte
    string listaErros = "lista_erros.txt"; // Caminho para o arquivo de lista de erros
    string erro = "Erro encontrado na linha 3"; // Mensagem de erro

    ifstream file(codigoFonte); // Abre o arquivo de código fonte

    if (!file.is_open()) {
        cerr << "Erro ao abrir o arquivo de código fonte: " << codigoFonte << endl;
        return 1; // Sai se não puder abrir o arquivo
    }

    writeErrors(linhaDeErro, file, listaErros, erro); // Chama a função

    file.close(); // Fecha o arquivo após o uso
    return 0;
}
