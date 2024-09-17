#include <iostream>
#include <string>

using namespace std;

class Node {
public:
    // Data part of the node
    string data;
    string tipo;
    int escopo;
    int memoria;
    // Pointer to the next node in the list
    Node* next;

    // Constructor to initialize the node with data
    Node(string data,string tipo = "", int escopo = NULL,int memoria = NULL)
    {
        this->data = data;
        this->tipo = tipo;
        this->escopo = escopo;
        this->memoria = memoria;
        this->next = NULL;
    }
};
class TabelaDeSimbolos {
    Node *head;
    public:
        TabelaDeSimbolos() // quando chamada define a head como null
        {
            head = NULL;
        }
        /**
         * @brief Insere um identificador no topo da pilha
         * 
         * @param data 
         * @param tipo Opcional senão ""
         * @param escopo Opcional senão -1
         * @param memoria Opcional senão -1
         */
        void insertAtHead(string data,string tipo = "", int escopo = NULL,int memoria = NULL) {
            
            Node *newNode = new Node(data,tipo,escopo,memoria);
            // se head nao exisir
            if (head == NULL) {
                head = newNode;
                return;
            }
            // criamos novo node, o mesmo sera o novo head, e o antigo head sera o proximo
            newNode->next = this->head;
            this->head = newNode;
        }
        /**
         * @brief Busca pelo identificador na pilha, se não for encontrado ele retorna NULL.
         * 
         * @param data 
         */
        Node* searchFor(string data) {
            Node *temp = head;
            // sociedade
            if (head == NULL) {
                return NULL;
            }
            // enquanto não for o node alvo
            while (temp != NULL) {
                if (temp->data == data)
                    return temp;
            }
            return NULL;
        }
        /**
         * @brief Altera o campo tipo de todas as variaveis com o nome passado.
         * 
         * @param tipo 
         * @param var
         */
        void setVarTypes(string tipo,string var) {
            Node *temp = head;
            if (head == NULL)
                return;
            
            while (temp != NULL) {
                if (temp->data == var)
                    temp->tipo = tipo;
            }
            return;
        }
};