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
    bool escopo;
    int memoria;
    int rotulo;
    // Ponteiro para o próximo nó
    Node* next;

    // Construtor do nó
    Node(string data, string tipo = "", bool escopo = false, int memoria = 99999999, int rotulo = -1);
};

// Declaração da classe TabelaDeSimbolos
class TabelaDeSimbolos {
    Node* head; // Cabeça da lista de nós

public:
    // Construtor da tabela
    TabelaDeSimbolos();

    // Insere um identificador no topo da pilha (insere_tabela)
    void insertAtHead(string data, string tipo = "", bool escopo = false, int memoria = -1, int rotulo = -1);

    // Retorna a primeira declaracao do item buscado
    Node* pesquisa_tabela(string data);

    // Busca a pilha pela declaração de procedimento
    bool pesquisa_declproc_tabela(string lexema);
    
    // Busca declaração de procedimento ou funcção
    bool pesquisa_declprocfunc_tabela(string lexema);

    // Busca pela pilha só pelo lexema
    bool pesquisa_tabela_simples(string data);

    Node* buscar(string data);

    // Altera o campo tipo de todas as variáveis com o nome passado (coloca_tipo_tabela)
    void coloca_tipo_tabela(string tipo);

    // Busca por duplicatas desta variavel (Pesquisa_duplicvar_tabela)
    bool pesquisa_duplicvar_tabela(string lexema);

    // Busca por duplicatas desta variavel ou funcao (pesquisa_declvarfunc_tabela)
    bool pesquisa_declvarfunc_tabela(string lexema);

    // Busca se a variável ja foi declarada na tabela de símbolos (pesquisa_declvar_tabela)
    bool pesquisa_declvar_tabela(string lexema);

    // Busca se a função já foi declarada
    bool pesquisa_declfunc_tabela(string lexema);

    // Define tipo da função que é o HEAD
    void define_tipo_funcao(string tipo);

    // Desempilha o escopo atual
    void desempilhar_escopo();

    // Exibe a tabela de símbolos
    void display();

    // Conta a quantidade de variaveis no escopo atual para uso de ALLOC
    int qt_var_escopo();

    // Conta a quantidade de variaveis na tabela 
    int qt_var_total();

    // Retorna o endereço onde o lexema buscado está armazenado.
    // Retorna -1 se não achar o endereço do lexema.
    int locEndMemoria(string lexema);

    // Retorna o tipo da variavel alocada na tabela
    // Retorna -1 se não achar.
    string pesquisa_tipo_var_tabela(string lexema);

    string pesquisa_tipoprocfunc_tabela(string lexema);

    int rotulo_funcao(string funcao);

    Node* pop();
};

void analisadorSintatico(ifstream &codigo_fonte, TabelaDeSimbolos& table);
void Analisa_subrotinas(Token &token, ifstream &codigo_fonte, string &lista_erros, TabelaDeSimbolos& table,int& rotulo);
void Analisa_identificador(Token &token, ifstream &codigo_fonte, string &lista_erros, TabelaDeSimbolos& table,int& rotulo);
void AnalisaBloco(Token &token, ifstream &codigo_fonte, string &lista_erros, TabelaDeSimbolos& table,int& rotulo);
void Analisa_et_variaveis(Token &token, ifstream &codigo_fonte, string &lista_erros, TabelaDeSimbolos& table,int& rotulo);
void AnalisaVariaveis(Token &token, ifstream &codigo_fonte, string &lista_erros, TabelaDeSimbolos& table,int& rotulo);
void Analisa_comandos(Token &token, ifstream &codigo_fonte, string &lista_erros, TabelaDeSimbolos& table,int& rotulo);
void Analisa_expressao(Token &token, ifstream &codigo_fonte, string &lista_erros, TabelaDeSimbolos& table,int& rotulo);
void Analisa_comando_simples(Token &token, ifstream &codigo_fonte, string &lista_erros, TabelaDeSimbolos& table,int& rotulo);
void Analisa_comandos(Token &token, ifstream &codigo_fonte, string &lista_erros, TabelaDeSimbolos& table,int& rotulo);
void Analisa_chamada_procedimento(Token &token, ifstream &codigo_fonte, string &lista_erros, TabelaDeSimbolos& table,int& rotulo);
string analisa_tipo_semantico(TabelaDeSimbolos& table);
vector<string> conversao_posfixa();
void limpar_lista_expressao();
void gerar_expressao(TabelaDeSimbolos& table);
Token Lexical(ifstream& codigo, TabelaDeSimbolos& table);

#endif
