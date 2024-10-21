#include <iostream>
#include <string>
#include "sintatico.hpp"

using namespace std;

// Implementação do construtor da classe Node
Node::Node(string data, string tipo, int escopo, int memoria, int linha)
{
    this->data = data;
    this->tipo = tipo;
    this->escopo = escopo;
    this->memoria = memoria;
    this->linha = linha;
    this->next = nullptr;
}

// Implementação do construtor da classe TabelaDeSimbolos
TabelaDeSimbolos::TabelaDeSimbolos() {
    head = nullptr; // Inicializa a cabeça como nullptr
}

// Implementação da função insertAtHead
void TabelaDeSimbolos::insertAtHead(string data, string tipo, int escopo, int memoria, int linha) {
    Node* newNode = new Node(data, tipo, escopo, memoria, linha);
    
    if (head == nullptr) {
        head = newNode;
        return;
    }

    newNode->next = head;
    head = newNode;
    // cout << "[" <<data << "] lido" << endl; 
}

bool TabelaDeSimbolos::buscar(string data) {
    Node* temp = head;
    while (temp != nullptr) {
        if (temp->data == data)
            return true;
        temp = temp->next;
    }

    return false; // Retorna nullptr se não for encontrado
}

// Implementação da função searchFor
Node* TabelaDeSimbolos::searchFor(string data) {
    Node* temp = head;

    while (temp != nullptr) {
        if (temp->data == data)
            return temp;
        temp = temp->next;
    }

    return nullptr; // Retorna nullptr se não for encontrado
}

// Implementação da função setVarTypes
void TabelaDeSimbolos::setVarTypes(string tipo, string var) {
    Node* temp = head;

    while (temp != nullptr) {
        if (temp->data == var)
            temp->tipo = tipo;
        temp = temp->next;
    }
}

// Implementação da função display
void TabelaDeSimbolos::display() {
    Node* temp = head;
    int tam = 0;
    if (head == nullptr) {
        cout << "Tabela vazia." << endl;
        return;
    }

    while (temp != nullptr) {
        cout << "Identificador: " << temp->data << ", Tipo: " << temp->tipo << endl;
        temp = temp->next;
        tam++;
    }
    cout << tam << " itens na tabela de simbolos." << endl;
}
/// @brief Retira o item no topo da Tabela de Simbolos
/// @return Node
Node* TabelaDeSimbolos::pop() {
    if (head == nullptr) {
        return nullptr;
    }
    Node* temp = head;
    head = head->next;
    return temp;
}   