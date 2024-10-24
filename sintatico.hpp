#ifndef SINTATICO_HPP
#define SINTATICO_HPP

#include <iostream>
#include <fstream>
#include <string>
#include "tokens.hpp"

using namespace std;

// Declaração da classe Node
class Node {
public:
    // Dados do nó
    string data;
    string tipo;
    int escopo;
    int memoria;
    int linha;
    bool validade;
    // Ponteiro para o próximo nó
    Node* next;

    // Construtor do nó
    Node(string data, string tipo = "", int escopo = -1, int memoria = -1, int linha = 1);
};

// Declaração da classe TabelaDeSimbolos
class TabelaDeSimbolos {
    Node* head; // Cabeça da lista de nós

public:
    // Construtor da tabela
    TabelaDeSimbolos();

    // Insere um identificador no topo da pilha
    void insertAtHead(string data, string tipo = "", int escopo = -1, int memoria = -1, int linha = 1);

    // Busca pelo identificador na pilha
    Node* searchFor(string data);

    bool buscar(string data);

    // Altera o campo tipo de todas as variáveis com o nome passado
    void setVarTypes(string tipo, string var);

    // Exibe a tabela de símbolos
    void display();

    Node* pop();
};

void analisadorSintatico(ifstream &codigo_fonte, TabelaDeSimbolos& table);
void Analisa_subrotinas(Token &token, ifstream &codigo_fonte, string &lista_erros, TabelaDeSimbolos& table);
void Analisa_identificador(Token &token, ifstream &codigo_fonte, string &lista_erros, TabelaDeSimbolos& table);
void AnalisaBloco(Token &token, ifstream &codigo_fonte, string &lista_erros, TabelaDeSimbolos& table);
void Analisa_et_variaveis(Token &token, ifstream &codigo_fonte, string &lista_erros, TabelaDeSimbolos& table);
void AnalisaVariaveis(Token &token, ifstream &codigo_fonte, string &lista_erros, TabelaDeSimbolos& table);
void Analisa_comandos(Token &token, ifstream &codigo_fonte, string &lista_erros, TabelaDeSimbolos& table);
void Analisa_expressao(Token &token, ifstream &codigo_fonte, string &lista_erros, TabelaDeSimbolos& table);
void Analisa_comando_simples(Token &token, ifstream &codigo_fonte, string &lista_erros, TabelaDeSimbolos& table);
void Analisa_comandos(Token &token, ifstream &codigo_fonte, string &lista_erros, TabelaDeSimbolos& table);
void Analisa_chamada_procedimento(Token &token, ifstream &codigo_fonte, string &lista_erros, TabelaDeSimbolos& table);

#endif
