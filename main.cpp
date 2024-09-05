#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>


using namespace std;

unordered_set<char> operadorAritmetico = {'+','-','*'};
unordered_set<char> operadorRelacional = {'<','>','=','!'};
unordered_set<char> pontuacoes = {';',',','(',')','.'};

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
struct Token {
    string lexema; 
    string simbolo; 
};

// O analisador lexical vai ser responsavel por retornar todos os tokens que um arquivo fonte possui
vector<Token> analisadorLexical(const string& filename){
    ifstream file(filename);
    vector<Token> tokens; 

    char c;
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
                tokens.push_back({tokenValue,tokenList[tokenValue]});

            } else {
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
            tokens.push_back({tokenValue, "snumero"});
        }
        // Se são simbolos e operadores 
        else {
            string tokenValue(1,c);
            char next;

            // Precisamos saber o que é o proximo valor para saber qual decisão tomar (por causa do !=, >= etc)
            file >> noskipws >> next; 
            tokenValue+= next;

            if (tokenList.find(tokenValue) != tokenList.end()){
                tokens.push_back({tokenValue,tokenList[tokenValue]});
            } else {
                // Remove o next e volta o ponteiro de leitura --> caso de operadores unicos 
                tokenValue.pop_back();
                file.unget();  

                if (tokenList.find(tokenValue) != tokenList.end()){
                    tokens.push_back({tokenValue,tokenList[tokenValue]});
                } else {
                    // Desconhecido :D e por agora não faz nada 
                }
            }
        } 
        // else if (c == ':') {
        //     // trata atribuição
        // }
        // else if (operadorAritmetico.find(c) != operadorAritmetico.end()){
        //     // trata operador aritmetico
        // }
        // else if (operadorRelacional.find(c) != operadorRelacional.end()) {
        //     // trata operador relacional
        // }
        // else if (pontuacoes.find(c) != pontuacoes.end()) {
        //     // trata pontuacao
        // }
        // else {
        //     // ERRO!
        // }
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
    vector<Token> tokens = analisadorLexical(filename);

    // string filename = "abc.txt";
    // printFileContent(filename);

    for (const auto& tok : tokens) {
        cout << "Token Type: " << tok.lexema << ", Value: " << tok.simbolo << endl;
    }

    return 0;


}
