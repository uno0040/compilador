#ifndef SINTATICO_HPP
#define SINTATICO_HPP

#include <iostream>
#include <string>

using namespace std;

// Declaração da classe Node
class Node {
public:
    // Dados do nó
    string data;
    string tipo;
    int escopo;
    int memoria;
    // Ponteiro para o próximo nó
    Node* next;

    // Construtor do nó
    Node(string data, string tipo = "", int escopo = -1, int memoria = -1);
};

// Declaração da classe TabelaDeSimbolos
class TabelaDeSimbolos {
    Node* head; // Cabeça da lista de nós

public:
    // Construtor da tabela
    TabelaDeSimbolos();

    // Insere um identificador no topo da pilha
    void insertAtHead(string data, string tipo = "", int escopo = -1, int memoria = -1);

    // Busca pelo identificador na pilha
    Node* searchFor(string data);

    // Altera o campo tipo de todas as variáveis com o nome passado
    void setVarTypes(string tipo, string var);

    // Exibe a tabela de símbolos
    void display();
};

#endif // TABELADESIMBOLOS_HPP
