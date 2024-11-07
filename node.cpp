#include <iostream>
#include <string>
#include "sintatico.hpp"

using namespace std;

// Implementação do construtor da classe Node
Node::Node(string data, string tipo, bool escopo, int memoria)
{
    this->data = data;
    this->tipo = tipo;
    this->escopo = escopo;
    this->memoria = memoria;
    this->next = nullptr;
}

// Implementação do construtor da classe TabelaDeSimbolos
TabelaDeSimbolos::TabelaDeSimbolos() {
    head = nullptr; // Inicializa a cabeça como nullptr
}

// Implementação da função insertAtHead
void TabelaDeSimbolos::insertAtHead(string data, string tipo, bool escopo, int memoria) {
    Node* newNode = new Node(data, tipo, escopo, memoria);
    
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

// Insere tipos nas variáveis da tabela
void TabelaDeSimbolos::insereTipoVar(string tipo) {
    Node* temp = head;
    temp = temp->next;
    while (temp != nullptr && temp->tipo == "variavel") {
        temp->tipo = tipo;
        temp = temp->next;
    }
}

// Busca se há mais de uma váriavel com este lexema na tabela de símbolos    
// Retorna true se for encontrada, false se não for.
bool TabelaDeSimbolos::buscarDuplicataVar(string lexema) {

    int contador = 0;
    Node* temp = head;

    while (temp != nullptr) {
        if (temp->data == lexema && temp->tipo == "variavel")
            contador++;
        if (contador >= 2)
            return true;
        temp = temp->next;
    }
    return false;
}

// Busca se há mais de uma variável ou função com este lexema na tabela de símbolos    
bool TabelaDeSimbolos::buscarDeclVarFunc(string lexema) {

    Node* temp = head;

    while (temp != nullptr) {
        if (temp->data == lexema && (temp->tipo == "variavel" || temp->tipo == "funcao")) // ALTERAR ESTE IF
            return true;
        temp = temp->next;
    }
    return false;
}

// Busca se a variável foi declarada na tabela
bool TabelaDeSimbolos::buscarDeclVar(string lexema) {

    Node* temp = head;

    while (temp != nullptr) {
        if (temp->data == lexema && temp->tipo == "variavel")
            return true;
        temp = temp->next;
    }
    return false;
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