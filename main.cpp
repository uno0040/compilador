#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "tokens.hpp"

using namespace std;

unordered_set<char> operadorAritmetico = {'+','-','*'};
unordered_set<char> operadorRelacional = {'<','>','=','!'};
unordered_set<char> pontuacoes = {';',',','(',')','.'};

int token_count[39] = {0};

// unordered map usado para printar nome do simbolo
unordered_map<int, string> listIndex = {
    {0, "sprograma"},
    {1, "sinicio"},
    {2, "sfim"},
    {3, "sprocedimento"},
    {4, "sfuncao"},
    {5, "sse"},
    {6, "sentao"},
    {7, "ssenao"},
    {8, "senquanto"},
    {9, "sfaca"},
    {10, "satribuicao"},
    {11, "sescreva"},
    {12, "sleia"},
    {13, "svar"},
    {14, "sinteiro"},
    {15, "sbooleano"},
    {16, "sidentificador"},
    {17, "snumero"},
    {18, "sponto"},
    {19, "sponto_virgula"},
    {20, "svirgula"},
    {21, "sabre_parenteses"},
    {22, "sfecha_parenteses"},
    {23, "smaior"},
    {24, "smaiorig"},
    {25, "sig"},
    {26, "smenor"},
    {27, "smenorig"},
    {28, "sdif"},
    {29, "smais"},
    {30, "smenos"},
    {31, "smult"},
    {32, "sdiv"},
    {33, "se"},
    {34, "sou"},
    {35, "snao"},
    {36, "sdoispontos"},
    {37, "sverdadeiro"},
    {38, "sfalso"}
};

// unordered map usado para catalogar quantos simbolos tem de cada
unordered_map<string,int> tokenInd = {
    {"sprograma",0},
    {"sinicio",1},
    {"sfim",2},
    {"sprocedimento",3},
    {"sfuncao",4},
    {"sse",5},
    {"sentao",6},
    {"ssenao",7},
    {"senquanto",8},
    {"sfaca",9},
    {"satribuicao",10},
    {"sescreva",11},
    {"sleia",12},
    {"svar",13},
    {"sinteiro",14},
    {"sbooleano",15},
    {"sidentificador",16},
    {"snumero",17},
    {"sponto",18},
    {"sponto_virgula",19},
    {"svirgula",20},
    {"sabre_parenteses",21},
    {"sfecha_parenteses",22},
    {"smaior",23},
    {"smaiorig",24},
    {"sig",25},
    {"smenor",26},
    {"smenorig",27},
    {"sdif",28},
    {"smais",29},
    {"smenos",30},
    {"smult",31},
    {"sdiv",32},
    {"se",33},
    {"sou",34},
    {"snao",35},
    {"sdoispontos",36},
    {"sverdadeiro",37},
    {"sfalso",38}
};


unordered_map<string,string> tokenList = {
    {"programa" , "sprograma"},
    {"inicio" , "sinicio"},
    {"fim" , "sfim"},
    {"procedimento" , "sprocedimento"},
    {"funcao" , "sfuncao"},
    {"se" , "sse"},
    {"entao" , "sentao"},
    {"senao" , "ssenao"},
    {"enquanto" , "senquanto"},
    {"faca" , "sfaca"},
    {":=" , "satribuicao"},
    {"escreva" , "sescreva"},
    {"leia" , "sleia"},
    {"var" , "svar"},
    {"inteiro" , "sinteiro"},
    {"booleano" , "sbooleano"},
    {"identificador" , "sidentificador"},
    {"numero" , "snumero"},
    {"." , "sponto"},
    {";" , "sponto_virgula"},
    {"," , "svirgula"},
    {"(" , "sabre_parenteses"},
    {")" , "sfecha_parenteses"},
    {">" , "smaior"},
    {">=" , "smaiorig"},
    {"=" , "sig"},
    {"<" , "smenor"},
    {"<=" , "smenorig"},
    {"!=" , "sdif"},
    {"+" , "smais"},
    {"-" , "smenos"},
    {"*" , "smult"},
    {"div" , "sdiv"},
    {"e" , "se"},
    {"ou" , "sou"},
    {"nao" , "snao"},
    {":" , "sdoispontos"},
    {"verdadeiro" , "sverdadeiro"},
    {"falso" , "sfalso"}
};

// struct que define as informações de um token
// struct Token {
//     string lexema; 
//     string simbolo; 
// };

// O analisador lexical vai ser responsavel por retornar todos os tokens que um arquivo fonte possui
vector<Token> analisadorLexical(const string& filename){
    ifstream file(filename);
    vector<Token> tokens; 

    char c;
    int linha = 1;
    // obs -> noskipws é um comando para ler o arquivo sem pular os espaços 
    while (file>>noskipws>>c){
        // Se encontramos um comentario, consumimos todos os caracteres e espaços em branco dentro do comentario
        // até que o programa ache o fechamento das chaves 
        if (c == '{'){
            while (file>> noskipws >> c && c !='}');
            continue;
        }

        // Se é um espaço em branco
        if (isspace(c)){
            continue;
        }

        // --------------------
        // Identificando tokens
        // --------------------

        // Se o caractere é uma letra, pode ser identificador ou palavra-chave
        // trata identificador e palavra reservada
        if (isalpha(c)){
            string tokenValue(1,c);

            //Vamos armazenar a leira em tokenValue, enquanto a entrada lida for letra/numero
            while (file >> noskipws >> c && (isalnum(c) || c == '_')){
                tokenValue+= c;
            }
            
            file.unget(); // voltamos o ponteiro para retornar o caractere que não faz parte da analise desse token

            // É uma entrada valida ?
            if (tokenList.find(tokenValue) != tokenList.end()){
                // Sim é uma entrada valida e podemos guardar esse token
                token_count[tokenInd[tokenList[tokenValue]]]++;
                tokens.push_back({tokenValue,tokenList[tokenValue]});

            } else {
                token_count[tokenInd[tokenList["identificador"]]]++;
                tokens.push_back({tokenValue,tokenList["identificador"]});
            } 

        }
        // Se é um numero, vamos ler o numero inteiro e guardar em tokens
        // trata digitos
        else if(isdigit(c)){
            string tokenValue(1,c);

            while (file >> noskipws >> c && isdigit(c)){
                tokenValue+= c;
            }

            file.unget();
            token_count[tokenInd["snumero"]]++;
            tokens.push_back({tokenValue, "snumero"});
        }
        // Se são simbolos e operadores 
        // else {
        //     string tokenValue(1,c);
        //     char next;

        //     // Precisamos saber o que é o proximo valor para saber qual decisão tomar (por causa do !=, >= etc)
        //     file >> noskipws >> next; 
        //     tokenValue+= next;

        //     if (tokenList.find(tokenValue) != tokenList.end()){
        //         token_count[tokenInd[tokenList[tokenValue]]]++;
        //         tokens.push_back({tokenValue,tokenList[tokenValue]});
        //     } else {
        //         // Remove o next e volta o ponteiro de leitura --> caso de operadores unicos 
        //         tokenValue.pop_back();
        //         file.unget();  

        //         if (tokenList.find(tokenValue) != tokenList.end()){
        //             token_count[tokenInd[tokenList[tokenValue]]]++;
        //             tokens.push_back({tokenValue,tokenList[tokenValue]});
        //         } else {
        //             tokens.push_back({tokenValue,"serro"});
        //         }
        //     }
        // } 
        else if (c == ':') {
            // trata atribuição
            string tokenValue(1,c);
            char next;
            int fl = 0;
            file.get(next);
            if (next != '='){
                file.unget();
            }
            else {
                tokenValue+=next;
            }
            if (tokenList.find(tokenValue) != tokenList.end()){
                token_count[tokenInd[tokenList[tokenValue]]]++;
                tokens.push_back({tokenValue,tokenList[tokenValue]});
            } else {
                tokens.push_back({tokenValue,"serro"});
            }
        }
        else if (operadorAritmetico.find(c) != operadorAritmetico.end()){
            // trata operador aritmetico
            string tokenValue(1,c);

            if (tokenList.find(tokenValue) != tokenList.end()){
                token_count[tokenInd[tokenList[tokenValue]]]++;
                tokens.push_back({tokenValue,tokenList[tokenValue]});
            } else {
                tokens.push_back({tokenValue,"serro"});
            }
        }
        else if (operadorRelacional.find(c) != operadorRelacional.end()) {
            // trata operador relacional
            string tokenValue(1,c);
            char next;

            while (file >> noskipws >> c && (operadorRelacional.find(c) != operadorRelacional.end())){
                tokenValue+= c;
            }

            file.unget(); //devolve caracter

            if (tokenList.find(tokenValue) != tokenList.end()){
                token_count[tokenInd[tokenList[tokenValue]]]++;
                tokens.push_back({tokenValue,tokenList[tokenValue]});
            } else {
                tokens.push_back({tokenValue,"serro"});
            }
        }
        else if (pontuacoes.find(c) != pontuacoes.end()) {
            // trata pontuacao
            string tokenValue(1,c);
            char next;

            if (tokenList.find(tokenValue) != tokenList.end()){
                token_count[tokenInd[tokenList[tokenValue]]]++;
                tokens.push_back({tokenValue,tokenList[tokenValue]});
            } else {
                tokens.push_back({tokenValue,"serro"});
            }
        }
        else {
            string tokenValue(1,c);
            tokens.push_back({tokenValue,"serro"});
        }
        linha++;
    }


    file.close();
    return tokens;

}

void printFileContent(const string& filename){
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Erro ao abrir o arquivo." << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        cout << line << endl;
    }

    file.close();
}

int main() {
    string filename = "oi.txt";
    ofstream outfile ("test.txt");
    vector<Token> tokens = analisadorLexical(filename);
    // ofstream outfile ("saida.txt");

    // string filename = "abc.txt";
    // printFileContent(filename);
    writeTokensToFile("test.txt",tokens);
    for (const auto& tok : tokens) {
        // outfile << "Token Type: " << tok.lexema << " , Value: " << tok.simbolo << endl;
        
        cout << "Token Type: " << tok.lexema << " , Value: " << tok.simbolo << endl;
    }
    cout << endl;
    for (int i = 0; i < 39; i++) {
        cout << "Quantidade de simbolos [" << listIndex[i] << "] no programa: " << token_count[i] << endl;
    }
    
    outfile.close();
    // criar contador de cada token tem
    return 0;


}
