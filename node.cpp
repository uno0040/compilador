#include <iostream>
#include <string>
#include "sintatico.hpp"

using namespace std;

// Implementação do construtor da classe Node
Node::Node(string data, string tipo, bool escopo, int memoria, int rotulo)
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
void TabelaDeSimbolos::insertAtHead(string data, string tipo, bool escopo, int memoria, int rotulo) {
    Node* newNode = new Node(data, tipo, escopo, memoria, rotulo);
    
    if (head == nullptr) {
        head = newNode;
        return;
    }

    newNode->next = head;
    head = newNode;
    // cout << "[" <<data << "] lido" << endl; 
}


Node* TabelaDeSimbolos::buscar(string data) {
    Node* temp = head;
    while (temp != nullptr) {
        if (temp->data == data)
            return temp;
        temp = temp->next;
    }

    return nullptr; // Retorna nullptr se não for encontrado
}


// Retorna true se encontrar o item buscado, false caso contrario.
// Versão simples
bool TabelaDeSimbolos::pesquisa_tabela_simples(string data) {
    Node* temp = head;

    while (temp != nullptr) {
        if (temp->data == data)
            return true;
        temp = temp->next;
    }

    return false; 
}


// Retorna a primeira declaracao do item buscado
Node* TabelaDeSimbolos::pesquisa_tabela(string data) {
    Node* temp = head;
    Node* r = nullptr;
    while (temp != nullptr) {
        if (temp->data == data)
            r = temp;
        temp = temp->next;
    }
    return r; 
}

// Insere tipos nas variáveis da tabela
void TabelaDeSimbolos::coloca_tipo_tabela(string tipo) {
    Node* temp = head;
    while (temp != nullptr && temp->tipo == "variavel") {
        temp->tipo = tipo;
        temp = temp->next;
    }
}

// Busca se há mais de uma váriavel com este lexema na tabela de símbolos    
// Retorna true se for encontrada, false se não for.
bool TabelaDeSimbolos::pesquisa_duplicvar_tabela(string lexema) {

    int contador = 0;
    Node* temp = head;

    while (temp != nullptr && temp->escopo == false) {
        if (temp->data == lexema && temp->tipo == "variavel")
            contador++;
        if (contador >= 2)
            return true;
        temp = temp->next;
    }
    return false;
}

// Busca se há mais de uma variável ou função com este lexema na tabela de símbolos    
bool TabelaDeSimbolos::pesquisa_declvarfunc_tabela(string lexema) {

    Node* temp = head;

    while (temp != nullptr) {
        if (temp->data == lexema && (temp->tipo == "variavel" || temp->tipo == "funcao" || temp->tipo == "funcao inteiro" || temp->tipo == "funcao booleana" || temp->tipo == "sbooleano" || temp->tipo == "sinteiro")) // ALTERAR ESTE IF
            return true;
        temp = temp->next;
    }
    return false;
}

// Busca se a variável foi declarada na tabela
// Retorna true se encontrar e false se não encontrar a variável na table.
bool TabelaDeSimbolos::pesquisa_declvar_tabela(string lexema) {
    // display();
    cout << "procurando: "<< lexema << endl;

    Node* temp = head;

    while (temp != nullptr) {
        if (temp->data == lexema && (temp->tipo == "variavel" || temp->tipo == "sinteiro" || temp->tipo == "sbooleano"))
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
    cout << "====================" << endl;
    while (temp != nullptr) {
        cout << "Identificador: " << temp->data << ", Tipo: " << temp->tipo << endl;
        temp = temp->next;
        tam++;
    }
    cout << "====================" << endl;
    cout << tam << " itens na tabela de simbolos." << endl;
    cout << "====================" << endl;
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

// Desempilha o escopo atual
void TabelaDeSimbolos::desempilhar_escopo() {
    while (head != nullptr && head->escopo != true) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}


// Busca se tem uma outra função declarada com este nome
bool TabelaDeSimbolos::pesquisa_declfunc_tabela(string lexema) {
    display();
    Node* temp = head;
    cout << "procurando: "<< lexema << endl;
    while (temp != nullptr) {
        if (temp->data == lexema && (temp->tipo == "funcao" || temp->tipo == "funcao inteiro" || temp->tipo == "funcao booleana"))
            return true;
        temp = temp->next;
    }
    cout << "nao achei" << endl;
    return false;
}

// Define o tipo da funcao que esta no head
void TabelaDeSimbolos::define_tipo_funcao(string tipo) {
    head->tipo = tipo;
}

int TabelaDeSimbolos::qt_var_escopo() {
    int r = 0;
    Node* temp = head;
    while (temp != nullptr && temp->escopo != true) {
        if (temp->tipo == "variavel" || temp->tipo == "sinteiro" || temp->tipo == "sbooleano")
            r++;
        temp = temp->next;
    }
    return r;
}

int TabelaDeSimbolos::qt_var_total() {
    int r = 0;
    Node* temp = head;
    while (temp != nullptr) {
        if (temp->tipo == "variavel" || temp->tipo == "sinteiro" || temp->tipo == "sbooleano")
            r++;
        temp = temp->next;
    }
    return r;
}

int TabelaDeSimbolos::locEndMemoria(string lexema) {
    Node* temp = head;
    while (temp != nullptr) {
        if (temp->data == lexema)
            return temp->memoria;
        temp = temp->next;
    }    
    return -1;
}

bool TabelaDeSimbolos::pesquisa_declproc_tabela(string lexema) {
    // display();
    Node* temp = head;
    cout << "procurando: "<< lexema << endl;
    while (temp != nullptr) {
        if (temp->data == lexema && (temp->tipo == "procedimento")) {
            cout << "NAO SOU FKA" << endl;
            return true;
        }
        temp = temp->next;
    }
    cout << "FAKE" << endl;
    return false;
}