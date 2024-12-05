#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include "tokens.hpp"
#include "lexical.hpp"
#include "erros.hpp"
#include "sintatico.hpp"
#include "geracao.hpp"

using namespace std;

// alterar funcoes para buscar escopos.
// marcar o bool escopo, buscar até la!
// NEM TODAS AS FUNCOES PRECISAM DISSO!

int mem = 1;
bool pos_neg_val = false;
bool save = false;
int counter = 0;

// bool flag_primeira = true;

string erroTipoInvalido = "!!! Erro tipo nao existente!";
string erroIdentificadorNaoExiste = "!!! Erro identificador nao declarado!";
string erroIdentificadorPrograma = "!!! Espera-se um identificador Programa";
string erroIdentificador = "!!! Espera-se um identificador";
string erroPontoeVirgula = "!!! Espera-se uma pontuacao do tipo ; ";
string erroPontoFinal = "!!! Espera-se uma pontuacao do tipo . ";
string erroPontuacao = "!!! Espera-se pontuacao ";
string erroFechamentoDeParenteses = "!!! Erro de fechamento de parenteses";
string erroIdentificadorProcedimento = "!!! Espera-se um identificador Procedimento";
string erroConflitoIdentificadores = "!!! Identificador ja foi utilizado! ";
string erroIdentificadorInvalidoProc = "!!! Identificador com sintaxe inválida";
string erroEsperaEntao = "!!! Espera-se um 'entao'.";
string erroDoisPontos = "!!! Espera-se ':'.";
string erroInicio = "!!! Espera-se 'inicio'.";
string erroChamadaProcedimento = "!!! Procedimento deve ter uma nome identificador.";
string erroDuplicidadeDecaracao = "!!! Duplicidade de declaracao encontrada!";
string erroNaoExisteVariavel = "!!! Variavel nao declarada";

vector<string> lista_expressao;
vector<string> posfix; // esta variavel segura a expressão infix para ser traduzida

vector<int> alocacoes;

// Limpa o vetor lista_expressao
void limpar_lista_expressao() {
    while (lista_expressao.empty() == false)
        lista_expressao.pop_back();
}

Token Lexical(ifstream& codigo, TabelaDeSimbolos& table) {
    Token token = analisadorLexical(codigo,table);
    if (save) {
        if (pos_neg_val){
            string temp = lista_expressao.back();
            lista_expressao.pop_back();
            lista_expressao.push_back(temp + 'u');
            pos_neg_val = false;
        }
        lista_expressao.push_back(token.lexema);
    }
    // cout << "saiu lexico" << endl;
    return token;
}

vector<string> conversao_posfixa() {
    // cout << "entrou posfixa" << endl;
    // Função interna para determinar a precedência dos operadores
    auto precedencia = [](const std::string& op) -> int {
        if (op == "nao" || op == "-u" || op == "+u")
            return 4;
        else if (op == "*" || op == "div")
            return 3;
        else if (op == "+" || op == "-")
            return 2;
        else if (op == "e")
            return 1;
        else if (op == "ou")
            return 0;
        else if (op == "=" || op == "!=" || op == "<" || op == "<=" || op == ">" || op == ">=")
            return -1;
        else
            return -2; // Para outros casos
    };

    // Função interna para verificar se o token é um operador
    auto isop = [](const std::string& token) -> bool {
        return token == "+" || token == "-" || token == "*" || token == "div" ||
               token == "e" || token == "ou" || token == "nao" || token == "-u" || token == "+u" ||
               token == "=" || token == "!=" || token == "<" || token == "<=" || token == ">" || token == ">=";
    };

    // Função interna para verificar se o token é um operador unário
    auto isunary = [](const std::string& op) -> bool {
        return op == "nao" || op == "-u" || op == "+u";
    };

    // Função interna para verificar se o token é um operando
    auto ehOperando = [&](const std::string& token) -> bool {
        // Aqui você pode adicionar verificações adicionais se necessário
        return !isop(token) && token != "(" && token != ")";
    };

    std::vector<std::string> saida;
    std::stack<std::string> pilha;

    for (size_t i = 0; i < lista_expressao.size(); ++i) {
        std::string token = lista_expressao[i];

        if (ehOperando(token)) {
            // Se for um operando, adiciona à saída
            saida.push_back(token);

            // Verificar se o topo da pilha é um operador unário
            while (!pilha.empty() && isunary(pilha.top())) {
                saida.push_back(pilha.top());
                pilha.pop();
            }
        }
        else if (token == "(") {
            pilha.push(token);
        }
        else if (token == ")") {
            while (!pilha.empty() && pilha.top() != "(") {
                saida.push_back(pilha.top());
                pilha.pop();
            }
            if (!pilha.empty() && pilha.top() == "(") {
                pilha.pop();
            }
            else {
                cerr << "Parenteses não balanceados." << endl;
                exit(-1);
            }

            // Após fechar parênteses, verificar por operadores unários
            while (!pilha.empty() && isunary(pilha.top())) {
                saida.push_back(pilha.top());
                pilha.pop();
            }
        }
        else if (isop(token)) {
            if (isunary(token)) {
                // Operadores unários são empilhados imediatamente
                pilha.push(token);
            }
            else {
                while (!pilha.empty() && precedencia(pilha.top()) >= precedencia(token)) {
                    saida.push_back(pilha.top());
                    pilha.pop();
                }
                pilha.push(token);
            }
        }
        else {
            cerr << "Token desconhecido." << endl;
            exit(-1);
        }
    }

    // Após processar todos os tokens, desempilha os operadores restantes
    while (!pilha.empty()) {
        if (pilha.top() == "(" || pilha.top() == ")") {
            cerr << "Parenteses não balanceados." << endl;
            exit(-1);
        }
        saida.push_back(pilha.top());
        pilha.pop();
    }

    limpar_lista_expressao();
    // cout << "saiu posfixa" << endl;
    return saida;
}


string analisa_tipo_semantico(TabelaDeSimbolos& table) {
    posfix = conversao_posfixa();
    // cout << "pos fixo" << endl;
    // cout << "-=-=-=-=-=-=-=-=-=-" << endl;
    // for (size_t i = 0; i < posfix.size(); ++i) {
    //     cout << posfix[i] << endl;
    // }
    // cout << "-=-=-=-=-=-=-=-=-=-" << endl;
    // Imprimir a expressão pós-fixa para depuração

    /*cout << "Expressao posfixa: ";
    for (const string& t : posfix) {
        cout << t << " ";
    }
    cout << endl;*/
    
    
    stack<string> pilha;
    
    for (size_t i = 0; i < posfix.size(); ++i) {
        string token = posfix[i];
        
        if (token == "+" || token == "-" || token == "*" || token == "div" ||
            token == "=" || token == "!=" || token == "<" || token == "<=" || token == ">" || token == ">=" ||
            token == "e" || token == "ou") {
            
            // Operadores binários
            if (pilha.size() < 2) {
                cout << "Erro: Operador '" << token << "' requer dois operandos." << endl;
                exit(EXIT_FAILURE);
            }
            string tipoOperando2 = pilha.top(); pilha.pop();
            string tipoOperando1 = pilha.top(); pilha.pop();
            
            string tipoResultado;
            
            if (token == "+" || token == "-" || token == "*" || token == "div") {
                if (tipoOperando1 == "sinteiro" && tipoOperando2 == "sinteiro") {
                    tipoResultado = "sinteiro";
                } else {
                    cout << "Erro semântico: Operador '" << token << "' requer operandos inteiros." << endl;
                    exit(EXIT_FAILURE);
                }
            } else if (token == "=" || token == "!=" || token == "<" || token == "<=" || token == ">" || token == ">=") {
                if (tipoOperando1 == "sinteiro" && tipoOperando2 == "sinteiro") {
                    tipoResultado = "sbooleano";
                } else {
                    cerr << "Erro semântico: Operador '" << token << "' requer operandos inteiros." << endl;
                    exit(EXIT_FAILURE);
                }
            } else if (token == "e" || token == "ou") {
                if (tipoOperando1 == "sbooleano" && tipoOperando2 == "sbooleano") {
                    tipoResultado = "sbooleano";
                } else {
                    cerr << "Erro semântico: Operador '" << token << "' requer operandos booleanos." << endl;
                    exit(EXIT_FAILURE);
                }
            } else {
                cerr << "Erro: Operador desconhecido '" << token << "'." << endl;
                exit(EXIT_FAILURE);
            }
            
            pilha.push(tipoResultado);
        } else if (token == "nao" || token == "-u" || token == "+u") {
            // Operadores unários
            if (pilha.empty()) {
                cerr << "Erro: Operador '" << token << "' requer um operando." << endl;
                exit(EXIT_FAILURE);
            }
            string tipoOperando = pilha.top(); pilha.pop();
            
            string tipoResultado;
            
            if (token == "-u" || token == "+u") {
                if (tipoOperando == "sinteiro") {
                    tipoResultado = "sinteiro";
                } else {
                    cerr << "Erro semântico: Operador '" << token << "' requer operando inteiro." << endl;
                    exit(EXIT_FAILURE);
                }
            } else if (token == "nao") {
                if (tipoOperando == "sbooleano") {
                    tipoResultado = "sbooleano";
                } else {
                    cerr << "Erro semântico: Operador '" << token << "' requer operando booleano." << endl;
                    exit(EXIT_FAILURE);
                }
            } else {
                cerr << "Erro: Operador desconhecido '" << token << "'." << endl;
                exit(EXIT_FAILURE);
            }
            
            pilha.push(tipoResultado);
        } else if (token == "verdadeiro" || token == "falso") {
            // Constantes booleanas
            pilha.push("sbooleano");
        } else if (isdigit(token[0])) {
            // Números inteiros
            pilha.push("sinteiro");
        } else {
            // Deve ser um identificador (variável ou função)
            if (table.pesquisa_declvar_tabela(token)) {
                // Variável declarada
                string tipo = table.pesquisa_tipo_var_tabela(token);
                pilha.push(tipo);
                
            } else if (table.pesquisa_declprocfunc_tabela(token)) {
                string tipo = table.pesquisa_tipoprocfunc_tabela(token);
                if(tipo == "sprocedimento"){
                    cerr << "Erro semantico: Identificador '" << token << "' utilizado como variavel, mas e um procedimento." << endl;
                    exit(EXIT_FAILURE);
                }
                else{
                    pilha.push(tipo);
                }
                
            } else {
                // Identificador não declarado
                cerr << "Erro semântico: Variável '" << token << "' não declarada." << endl;
                exit(EXIT_FAILURE);
            }
        }
    }
    
    if (pilha.size() != 1) {
        cerr << "Erro: Expressão inválida, pilha de tipos inconsistente." << endl;
        exit(EXIT_FAILURE);
    }
    
    string tipoExpressao = pilha.top();

    return tipoExpressao;
}

// Função para gerar o código da pós fixa
void gerar_expressao(TabelaDeSimbolos& table){
    for(int i = 0; i < int(posfix.size()); i++){
        string item = posfix.at(i);
        int endereco = table.locEndMemoria(item);
        //cout << item << endl;
        if(table.pesquisa_declvar_tabela(item)){
            if (endereco == -1) 
                exit(99);
            geraLDV(endereco);
        }
        else{
            if(item == "+"){
                 geraADD();
            }
            else if(item == "-"){
                geraSUB();
            }
            else if(item == "*"){
                geraMULT();
            }
            else if(item == "div"){
                geraDIVI();
            }
            else if(table.pesquisa_declproc_tabela(item)){
                geraLDV(0); // mudar aqui
            }
            else if(item == ">"){
                geraCMA();
            }
            else if(item == "<"){
                geraCME();
            }
            else if(item == "="){
                geraCEQ();
            }
            else if(item == "!="){
                geraCDIF();
            }
            else if(item == "<="){
                geraCMEQ();
            }
            else if(item == ">="){
                geraCMAQ();
            }
            else if(item == "-u"){
                geraINV();
            }
            else if(item == "+u"){
                continue;
            }
            else if(item == "verdadeiro"){
                geraLDC("1");
            }
            else if(item == "falso"){
                geraLDC("0");
            }
            else if(item == "e"){
                geraAND();
            }
            else if(item == "ou"){
                geraOR();
            }
            else if(item == "nao"){
                geraNEG();
            }
            else if (table.pesquisa_declfunc_tabela(item)){
                geraLDV(0);
            }
            else{
                geraLDC(item); 
            }
        }
    }
}

void Analisa_et_variaveis(Token &token, ifstream &codigo_fonte, string &lista_erros, TabelaDeSimbolos& table, int &rotulo)
{
    counter = 0; // quantas variaveis estão sendo declaradas
    int backup = mem; // endereço inicial de alocação
    
    if (token.simbolo == "svar")
    {
        token = Lexical(codigo_fonte,table);
        if (token.simbolo == "sidentificador")
        {
            do
            {   // sou inocente
                AnalisaVariaveis(token, codigo_fonte, lista_erros,table,rotulo);
                if (token.simbolo == "sponto_virgula")
                {
                    token = Lexical(codigo_fonte,table);
                }
                else
                {
                    // erro de ponto e virgula <etapa de declaração de variaveis>
                    cerr << "Erro de ponto e virgula" << endl;
                    exit(-1);
                    writeErrors(token.linha, codigo_fonte, lista_erros, erroPontoeVirgula);
                }

            } while (token.simbolo == "sidentificador");

            alocacoes.push_back(backup);
            alocacoes.push_back(counter);
            geraALLOC(backup, counter);

        }
        else
        {
            cerr << "Espera-se identificador." << endl;
            exit(-1);
            writeErrors(token.linha, codigo_fonte, lista_erros, erroIdentificador);
        }
    }
}

void AnalisaBloco(Token &token, ifstream &codigo_fonte, string &lista_erros, TabelaDeSimbolos& table, int &rotulo)
{
    token = Lexical(codigo_fonte,table);

    Analisa_et_variaveis(token, codigo_fonte, lista_erros,table,rotulo);
    Analisa_subrotinas(token, codigo_fonte, lista_erros,table,rotulo);
    Analisa_comandos(token, codigo_fonte, lista_erros,table,rotulo);
}

void Analisa_identificador(Token &token, ifstream &codigo_fonte, string &lista_erros, TabelaDeSimbolos& table, int &rotulo)
{
    if (!isalpha(token.lexema[0])) {
        cerr << "Erro de sintaxe do identificador." << endl;
        exit(-1);
        writeErrors(token.linha, codigo_fonte, lista_erros, erroIdentificadorInvalidoProc);
    } 
}

void Analisa_Tipo(Token &token, ifstream &codigo_fonte, string &lista_erros, TabelaDeSimbolos& table, int &rotulo)
{
    if (token.simbolo != "sinteiro" && token.simbolo != "sbooleano")
    {
        cerr << "Tipo inválido." << endl;
        exit(0);
        writeErrors(token.linha, codigo_fonte, lista_erros, erroTipoInvalido);
    }
    else
    {
        table.coloca_tipo_tabela(token.simbolo);
    }
    token = Lexical(codigo_fonte,table);
}

void AnalisaVariaveis(Token &token, ifstream &codigo_fonte, string &lista_erros, TabelaDeSimbolos& table, int &rotulo)
{
    
    do {
        if (token.simbolo == "sidentificador") {
            // PESQUISAR DUPLICATAS NA TABELA O LEXEMA DO TOKEN
                if (!table.pesquisa_duplicvar_tabela(token.lexema)){
                    table.insertAtHead(token.lexema, "variavel", false, mem);
                    mem++;
                    counter++;
                    token = Lexical(codigo_fonte,table);

                    if (token.simbolo == "svirgula" || token.simbolo == "sdoispontos") {

                        if (token.simbolo == "svirgula") {

                            token = Lexical(codigo_fonte,table);

                            if (token.simbolo == "sdoispontos") {
                                cerr << "Esperava-se identificador, encontrou dois pontos." << endl;
                                exit(-1);
                                writeErrors(token.linha, codigo_fonte, lista_erros, erroIdentificador);
                            }

                        }

                    } else {
                        cerr << "Erro de pontuação." << endl;
                        exit(-1);
                        writeErrors(token.linha, codigo_fonte, lista_erros,erroPontuacao);
                    }

                } else {
                    cerr << "Declaração duplicada de variável." << endl;
                    exit(-1);
                    writeErrors(token.linha, codigo_fonte, lista_erros, erroDuplicidadeDecaracao);
                }      
        } else {
            cerr << "Esperava-se identificador." << endl;
            exit(-1);
            writeErrors(token.linha, codigo_fonte, lista_erros,erroIdentificador);
        }
    } while (token.simbolo != "sdoispontos");

    token = Lexical(codigo_fonte,table);
    Analisa_Tipo(token, codigo_fonte, lista_erros,table,rotulo);
}

void Analisa_declaracao_procedimento(Token &token, ifstream &codigo_fonte, string &lista_erros, TabelaDeSimbolos& table, int &rotulo)
{
    token = Lexical(codigo_fonte,table);
    if (token.simbolo == "sidentificador")
    {
        // se o procedimento não tiver sido declarado
        if (!table.pesquisa_declprocfunc_tabela(token.lexema)) {
            // insere novo procedimento na tabela de simbolos
            table.insertAtHead(token.lexema, "procedimento", true, -1 ,rotulo);
            // gera NULL para este procedimento
            geraNULL(rotulo);
            rotulo++;
            token = Lexical(codigo_fonte,table);
            if (token.simbolo == "sponto_virgula")
            {
                AnalisaBloco(token, codigo_fonte, lista_erros,table,rotulo);

                // conta a quantidade de variaveis presentes neste escopo
                int variaveis_d = table.qt_var_escopo();
                
                // desempilha tudo neste escopo
                table.desempilhar_escopo();

                
                // se ouver variaveis para desempilhar, desempilha elas
                if (variaveis_d != 0){
                    // counter & backup
                    int c_temp = alocacoes.back();
                    alocacoes.pop_back();
                    int b_temp = alocacoes.back();
                    alocacoes.pop_back();
                    geraDALLOC(b_temp,c_temp);
                }

                geraRETURN();
            }
            else
            {
                cerr << "Esperava-se ponto e vírgula." << endl;
                exit(-1);
                writeErrors(token.linha, codigo_fonte, lista_erros, erroPontoeVirgula);
                exit(0);
            }
        }

        else {
            cerr << "Erro de identificador." << endl;
            exit(-1);
            writeErrors(token.linha, codigo_fonte, lista_erros, erroIdentificador);
        }
    }
    else
    {
        cerr << "Esperava-se identificador." << endl;
        exit(-1);
        writeErrors(token.linha, codigo_fonte, lista_erros, erroIdentificador);
    }
}

void Analisa_declaracao_funcao(Token &token, ifstream &codigo_fonte, string &lista_erros, TabelaDeSimbolos& table, int &rotulo)
{
    
    token = Lexical(codigo_fonte,table);
    if (token.simbolo == "sidentificador") {
        bool flag = table.pesquisa_declprocfunc_tabela(token.lexema);
        // se este nome NAO for uma funcao ja declarada
        if (!flag){

            int aux_rot = rotulo; // rotulo desta nova funcoa
            rotulo++;

            // insere nova funcao no tabela
            table.insertAtHead(token.lexema, "",true , -1, aux_rot);
            
            // gera NULL para a funcao  criada
            geraNULL(aux_rot);

            token = Lexical(codigo_fonte,table);

            if (token.simbolo == "sdoispontos") {
                token = Lexical(codigo_fonte,table);
                if (token.simbolo == "sinteiro" || token.simbolo == "sbooleano") {
                    // define o tipo para as funcoes aqui
                    if (token.simbolo == "sinteiro") 
                        table.define_tipo_funcao("funcao inteiro");
                    else
                        table.define_tipo_funcao("funcao booleana");
                    token = Lexical(codigo_fonte,table);
                    if (token.simbolo == "sponto_virgula") {
                        AnalisaBloco(token, codigo_fonte, lista_erros,table,rotulo);
                        
                        int variaveis_d = table.qt_var_escopo();
                        table.desempilhar_escopo();


                        // se ainda houver variaveis para desempilhar, desempilha elas
                        if (variaveis_d != 0){
                            // counter & backup
                            int c_temp = alocacoes.back();
                            alocacoes.pop_back();
                            int b_temp = alocacoes.back();
                            alocacoes.pop_back();
                            geraDALLOC(b_temp,c_temp);
                        }
            
                        geraRETURN();
                    }
                }
                else {
                    cerr << "Tipo inválido." << endl;
                    exit(-1);
                    writeErrors(token.linha, codigo_fonte, lista_erros, erroTipoInvalido);
                }
            }
            else {
                cerr << "Esperava-se dois pontos." << endl;
                exit(-1);
                writeErrors(token.linha, codigo_fonte, lista_erros, erroDoisPontos);
            }

        }else{
            cerr << "Declaração duplicada de função." << endl;
            exit(-1);
            writeErrors(token.linha, codigo_fonte, lista_erros, erroDuplicidadeDecaracao);
        }
    }
    else {
        cerr << "Erro de identificador." << endl;
        exit(-1);
        writeErrors(token.linha, codigo_fonte, lista_erros, erroIdentificador);
        table.pop();
    }
}

void Analisa_subrotinas(Token &token, ifstream &codigo_fonte, string &lista_erros, TabelaDeSimbolos& table, int &rotulo)
{
    int auxrot;
    int flag = 0; // flag marca se é procedimento ou funcao para gerar o NULL
    if (token.simbolo == "sprocedimento" || token.simbolo == "sfuncao") {
        // GERA ('  ',JMP,rotulo,'  ')
        geraJMP(rotulo);//salta sub-rotinas
        auxrot = rotulo;
        rotulo++;
        flag = 1;
    }
    while (token.simbolo == "sprocedimento" || token.simbolo == "sfuncao") {
        if (token.simbolo == "sprocedimento") {
            Analisa_declaracao_procedimento(token, codigo_fonte, lista_erros,table,rotulo);
        }
        else {
            Analisa_declaracao_funcao(token, codigo_fonte, lista_erros,table,rotulo);
        }
        if (token.simbolo == "sponto_virgula") {
            token = Lexical(codigo_fonte,table);
        }
        else {
            // cout << "subrotinas" << endl;
            cerr << "Espera-se ponto e vírgula." << endl;
            exit(-1);
            writeErrors(token.linha, codigo_fonte, lista_erros, erroPontoeVirgula);
        }
    }
    if (flag == 1) {
        geraNULL(auxrot); // gera null do procedimento / funcao
    }
}

void Analisa_atribuicao(Token &token, ifstream &codigo_fonte, string &lista_erros, TabelaDeSimbolos& table, Token token_passado, int &rotulo)
{
    string varpassada = token_passado.lexema; // armazena o nome da variavel no lado esquerdo da atribuição
    token = Lexical(codigo_fonte,table);
    // caso seja atribuição de variável
    if (table.pesquisa_declvar_tabela(varpassada)) {
        // o bloco englobado pelos dois save abaixo armazena os dados na tabela de simbolos para analise
        save = true;    
        lista_expressao.push_back(token.lexema);
        Analisa_expressao(token, codigo_fonte, lista_erros,table,rotulo);
        save = false;

        lista_expressao.pop_back(); // retirar o ; salvo na lista
        string var_tipo = table.pesquisa_tipo_var_tabela(varpassada); // coleta tipo da variavel
        string expressao_tipo = analisa_tipo_semantico(table); // coleta tipo da expressao

        if (expressao_tipo != var_tipo) { // tipos devem ser iguais para realizar atribuição
            cerr << "Tipo não compatível de expressão atribuída a variável!" << endl;
            exit(-1);
        }
        // GERA CODIGO
        // resolve a expressão e gera o código dela
        gerar_expressao(table);
        // gera STR para o endereço 
        geraSTR(table.locEndMemoria(varpassada));
    }
    // caso seja função
    else {
        // o bloco englobado pelos dois save abaixo armazena os dados na tabela de simbolos para analise
        save = true;
        lista_expressao.push_back(token.lexema);
        Analisa_expressao(token, codigo_fonte, lista_erros,table,rotulo);
        save = false;

        lista_expressao.pop_back(); // retirar o ; salvo na lista

        string var_tipo = table.pesquisa_tipo_var_tabela(varpassada); // coleta tipo da variavel
        string expressao_tipo = analisa_tipo_semantico(table); // coleta tipo da expressao

        if (expressao_tipo != var_tipo) { // tipos devem ser iguais para realizar atribuição
            cerr << "Tipo não compatível de expressão atribuída a função!" << endl;
            exit(-1);
        }
        // GERA CODIGO
        // resolve a expressão e gera o código dela
        gerar_expressao(table);
        // gera STR para o retorno no 0 
        geraSTR(0);
    }
    // Analisa_expressao(token, codigo_fonte, lista_erros,table,rotulo);
    
}

void Chamada_procedimento(Token &token, ifstream &codigo_fonte, string &lista_erros, TabelaDeSimbolos& table, Token token_passado,int& rotulo)
{
    int aux = table.rotulo_funcao(token_passado.lexema); // busca o rotulo do procedimento passado
    if (aux == -1) {
        cerr << "Procedimento não existe." << endl;
        exit(-1);
    }

    geraCALL(aux); // gera o CALL para o rótulo do procedimento
}

void Analisa_chamada_funcao(Token &token, ifstream &codigo_fonte, string &lista_erros, TabelaDeSimbolos& table, int &rotulo) {
    int aux = table.rotulo_funcao(token.lexema); // busca o rotulo da função passada
    if (aux == -1) {
        cerr << "Funcao não existe." << endl;
        exit(-1);
    }
    geraCALL(aux); // gera o CALL para o rótulo da função
    token = Lexical(codigo_fonte,table);
}

void Analisa_fator(Token &token, ifstream &codigo_fonte, string &lista_erros, TabelaDeSimbolos& table, int &rotulo)
{
    if (token.simbolo == "sidentificador")
    {
        Node* declarada = table.pesquisa_tabela(token.lexema); // busca na tabela de simbolos este identificador
        if (declarada != nullptr) { // se encontrar 
            if (declarada->tipo == "funcao inteiro" || declarada->tipo == "funcao booleana")
                Analisa_chamada_funcao(token, codigo_fonte, lista_erros,table,rotulo);
            else
                token = Lexical(codigo_fonte,table);
        }
        else {
            cerr << "Identificador ou função não ainda declarada." << endl;
            exit(-1);
        }
    }
    else { 
        if (token.simbolo == "snumero")
        {
            token = Lexical(codigo_fonte,table);
        }
        else {
            if (token.simbolo == "snao")
                {
                    token = Lexical(codigo_fonte,table);
                    Analisa_fator(token, codigo_fonte, lista_erros,table,rotulo);
                }
            else {
                if (token.simbolo == "sabre_parenteses") {
                    token = Lexical(codigo_fonte,table);
                    Analisa_expressao(token, codigo_fonte, lista_erros,table,rotulo);
                    if (token.simbolo == "sfecha_parenteses"){
                        token = Lexical(codigo_fonte,table);
                    }
                    else {
                        cerr << "Parenteses não fechados." << endl;
                        exit(-1);
                        writeErrors(token.linha, codigo_fonte, lista_erros, erroFechamentoDeParenteses);        
                    }
                }   
                else {
                    if (token.simbolo == "sverdadeiro" || token.simbolo == "sfalso") {
                        token = Lexical(codigo_fonte,table);
                    }
                    else {
                        cerr << "Parenteses não fechados." << endl;
                        exit(-1);
                        writeErrors(token.linha, codigo_fonte, lista_erros, erroFechamentoDeParenteses);
                    }
                }
            }
        }
    }
}
void Analisa_termo(Token &token, ifstream &codigo_fonte, string &lista_erros, TabelaDeSimbolos& table, int &rotulo)
{
    Analisa_fator(token, codigo_fonte, lista_erros,table,rotulo);
    while ((token.simbolo == "smult") || (token.simbolo == "sdiv") || (token.simbolo == "se"))
    {
        token = Lexical(codigo_fonte,table);
        Analisa_fator(token, codigo_fonte, lista_erros,table,rotulo);
    } 
}

void Analisa_expressao_simples(Token &token, ifstream &codigo_fonte, string &lista_erros, TabelaDeSimbolos& table, int &rotulo)
{
    if (token.simbolo == "smais" || token.simbolo == "smenos")
    {
        pos_neg_val = true; // marca como unário
        token = Lexical(codigo_fonte,table);
        pos_neg_val = false;
    }
    Analisa_termo(token, codigo_fonte, lista_erros,table,rotulo);

    while ((token.simbolo == "smais") || (token.simbolo == "smenos") || (token.simbolo == "sou"))
    {
        token = Lexical(codigo_fonte,table);
        Analisa_termo(token, codigo_fonte, lista_erros,table,rotulo);

    } 
    
}

void Analisa_expressao(Token &token, ifstream &codigo_fonte, string &lista_erros, TabelaDeSimbolos& table, int &rotulo)
{
    Analisa_expressao_simples(token, codigo_fonte, lista_erros,table,rotulo);

    if (token.simbolo == "smaior" || token.simbolo == "smaiorig" || token.simbolo == "sig" || token.simbolo == "smenor" || token.simbolo == "smenorig" || token.simbolo == "sdif")
    {

        token = Lexical(codigo_fonte,table);
        Analisa_expressao_simples(token, codigo_fonte, lista_erros,table,rotulo);
    }
}

void Analisa_chamada_procedimento(Token &token, ifstream &codigo_fonte, string &lista_erros, TabelaDeSimbolos& table, int &rotulo) {
    token = Lexical(codigo_fonte,table);
    if (token.simbolo != "sidentificador") {
        cerr << "Esperava-se identificador para procedimento." << endl;
        exit(-1);
        writeErrors(token.linha, codigo_fonte, lista_erros, erroChamadaProcedimento);
    } else {
        Analisa_identificador(token, codigo_fonte, lista_erros,table,rotulo);
        token = Lexical(codigo_fonte,table);
        if (token.simbolo != "sponto_virgula") {
            cerr << "Esperava-se ponto e vírgula." << endl;
            exit(-1);
            writeErrors(token.linha, codigo_fonte, lista_erros, erroPontoeVirgula);
        }
    }
}

void Analisa_atrib_chprocedimento(Token &token, ifstream &codigo_fonte, string &lista_erros, TabelaDeSimbolos& table, int &rotulo)
{
    Token token_passado = token;
    token = Lexical(codigo_fonte,table); 
    // <stribuiçao_chprocedimento> ::= (<comando atribuicao> | <chamada de procedimento>)
    if (token.simbolo == "satribuicao")
    {
        Analisa_atribuicao(token, codigo_fonte, lista_erros,table, token_passado, rotulo);
    }
    else
    {
        Chamada_procedimento(token, codigo_fonte, lista_erros,table, token_passado,rotulo);
    }
}

void Analisa_enquanto(Token &token, ifstream &codigo_fonte, string &lista_erros, TabelaDeSimbolos& table, int &rotulo)
{
    token = Lexical(codigo_fonte,table);
    int auxrot1,auxrot2;
    // variaveis auxiliares do rótulo como definido nos slides
    auxrot1 = rotulo;
    //gera(rotulo,NULL,"    ","    ") // inicio do while
    
    geraNULL(rotulo); // gera NULL para o loop
    rotulo++;

    // o bloco englobado pelos dois save abaixo armazena os dados na tabela de simbolos para analise
    save = true;
    lista_expressao.push_back(token.lexema);
    // token = Lexical(codigo_fonte,table);
    Analisa_expressao(token, codigo_fonte, lista_erros,table,rotulo);
    
    save = false;
    lista_expressao.pop_back(); // <- tira o ;

    string exp_bool_tipo = analisa_tipo_semantico(table); // tipo da expressão analisada
    
    if (exp_bool_tipo != "sbooleano") { // tende ser booleano
        cerr << "Enquanto esperava expressão booleana, recebeu: " << exp_bool_tipo << endl;
        exit(-1);
    }
    gerar_expressao(table); // traduz para posfixa e gera seu respectivo codigo

    // Analisa_expressao(token, codigo_fonte, lista_erros,table,rotulo);
    if (token.simbolo == "sfaca")
    {
        auxrot2 = rotulo;
        // gera("",JMPF,rotulo,"");
        geraJMPF(rotulo);
        rotulo++;  
        token = Lexical(codigo_fonte,table);
        Analisa_comando_simples(token, codigo_fonte, lista_erros,table,rotulo);
        // gera("",JMP,auxrot1,""); // retorna inicio loop
        geraJMP(auxrot1);
        // gera(auxrot2,NULL,"",""); // fim do while
        geraNULL(auxrot2);
    }
    else
    {
        cerr << "Esperava-se 'faca' após enquanto." << endl;
        exit(-1);
    }
}

void Analisa_se(Token &token, ifstream &codigo_fonte, string &lista_erros, TabelaDeSimbolos& table, int &rotulo)
{
    token = Lexical(codigo_fonte,table);
    int aux_rot = rotulo; 
    rotulo++;
    int aux_rot1; // cria um novo rotulo para este se
    
    // o bloco englobado pelos dois save abaixo armazena os dados na tabela de simbolos para analise
    save = true;
    lista_expressao.push_back(token.lexema);

    Analisa_expressao(token, codigo_fonte, lista_erros,table,rotulo);

    save = false;
    lista_expressao.pop_back(); //remove ;

    string tipo = analisa_tipo_semantico(table); // coleta o tipo da expressao na tabela

    if (tipo != "sbooleano") {
        cerr << "Esperava-se tipo booleano." << endl;
        exit(-1);
    }

    gerar_expressao(table); // gera a expressao pos fixa e gera seus comandos
    geraJMPF(aux_rot); // gera um jump para o rotulo do se


    if (token.simbolo == "sentao") { 
        token = Lexical(codigo_fonte,table);
        Analisa_comando_simples(token, codigo_fonte, lista_erros,table,rotulo);
        if (token.simbolo == "ssenao") {
            aux_rot1 = rotulo; // se tiver senao, ele aloca um rotulo para ele
            rotulo++;
            token = Lexical(codigo_fonte,table);
            Analisa_comando_simples(token, codigo_fonte, lista_erros,table,rotulo); 
            geraNULL(aux_rot1); // gera o NULL para o comando senao
        }
        else {
            geraNULL(aux_rot); // gera apenas o comando NULL para o comando se
        }
    }
    else {
        cerr << "Esperava-se entao." << endl;
        exit(-1);
        writeErrors(token.linha, codigo_fonte, lista_erros, erroEsperaEntao);
    }
}

void Analisa_leia(Token &token, ifstream &codigo_fonte, string &lista_erros, TabelaDeSimbolos& table, int &rotulo)
{
    string aux; // variavel auxiliar
    token = Lexical(codigo_fonte,table);
    if (token.simbolo == "sabre_parenteses") {
        token = Lexical(codigo_fonte,table);
        if (token.simbolo == "sidentificador") {

            bool flag = table.pesquisa_declvar_tabela(token.lexema);
            // busca em toda a tabela pela variavel, se nao achar ele da erro.
            if (flag){
                if (table.pesquisa_tipo_var_tabela(token.lexema) == "sinteiro") {
                    aux = token.lexema; // coloca o nome da variavel no aux
                    token = Lexical(codigo_fonte,table);
                    if (token.simbolo == "sfecha_parenteses") {
                        geraRD(); // gera o RD
                        geraSTR(table.locEndMemoria(aux)); // busca o endereço da variável na tabela e gera o STR para esta variavel
                        token = Lexical(codigo_fonte,table);
                    }
                } else {
                    cerr << "Variavel no leia deve ser do tipo inteiro." << endl;
                    exit(-1);
                }
            } 
            else{
                cerr << "Variável não existe." << endl;
                exit(-1);
                writeErrors(token.linha, codigo_fonte, lista_erros, erroNaoExisteVariavel);
            }
            
        }
        else {
            cerr << "Parênteses não balanceados." << endl;
            exit(-1);
            writeErrors(token.linha, codigo_fonte, lista_erros, erroFechamentoDeParenteses);
        }
    }
    else {
        cerr << "Parênteses não balanceados." << endl;
        exit(-1);
        writeErrors(token.linha, codigo_fonte, lista_erros, erroFechamentoDeParenteses);
    }
}

// me checar ?
void Analisa_escreva(Token &token, ifstream &codigo_fonte, string &lista_erros, TabelaDeSimbolos& table, int &rotulo)
{
    string aux;  // usado para guardar a variavel
    token = Lexical(codigo_fonte,table);
    if (token.simbolo == "sabre_parenteses")
    {
        token = Lexical(codigo_fonte,table);
        if (token.simbolo == "sidentificador")
        {
            
            bool existe = table.pesquisa_declvarfunc_tabela(token.lexema); // verifica se a variavel existe

            if (existe)
            {
                if (table.pesquisa_tipo_var_tabela(token.lexema) == "sinteiro") {
                    aux = token.lexema; // guarda o nome da variavel após confirmar se tipo e que ela existe
                }
                else {
                    cerr << "Escreva espera uma variável do tipo inteiro." << endl;
                    exit(-1);   
                    writeErrors(token.linha, codigo_fonte, lista_erros, erroFechamentoDeParenteses);
                }
                token = Lexical(codigo_fonte,table);

                if (token.simbolo == "sfecha_parenteses") // se a sintaxe estiver certa
                {
                    token = Lexical(codigo_fonte,table);
                    geraLDV(table.locEndMemoria(aux)); // gera o LDV do endereço da variável
                    geraPRN(); // gera PRN
                }
                else
                {   
                    cerr << "Parênteses não balanceados." << endl;
                    exit(-1);   
                    writeErrors(token.linha, codigo_fonte, lista_erros, erroFechamentoDeParenteses);
                }
            }
            else
            {
                cerr << "Identificador não declarado." << endl;
                exit(-1);
                writeErrors(token.linha, codigo_fonte, lista_erros, erroIdentificadorNaoExiste);
            }
        }
        else
        {
            cerr << "Esperava-se identificador." << endl;
            exit(-1);
            writeErrors(token.linha, codigo_fonte, lista_erros, erroIdentificador);
        }
    }
    else
    {
        cerr << "Parênteses não balanceados." << endl;
        exit(-1);
        writeErrors(token.linha, codigo_fonte, lista_erros, erroFechamentoDeParenteses);
    }
}
void Analisa_comando_simples(Token &token, ifstream &codigo_fonte, string &lista_erros, TabelaDeSimbolos& table, int &rotulo)
{
    if (token.simbolo == "sidentificador")
    {
        Analisa_atrib_chprocedimento(token, codigo_fonte, lista_erros,table,rotulo);
    }
    else if (token.simbolo == "sse")
    {
        Analisa_se(token, codigo_fonte, lista_erros,table,rotulo);
    }
    else if (token.simbolo == "senquanto")
    {
        Analisa_enquanto(token, codigo_fonte, lista_erros,table,rotulo);
    }
    else if (token.simbolo == "sleia")
    {
        Analisa_leia(token, codigo_fonte, lista_erros,table,rotulo);
    }
    else if (token.simbolo == "sescreva")
    {
        Analisa_escreva(token, codigo_fonte, lista_erros,table,rotulo);
    }
    else
    {
        Analisa_comandos(token, codigo_fonte, lista_erros,table,rotulo);
    }
}


void Analisa_comandos(Token &token, ifstream &codigo_fonte, string &lista_erros, TabelaDeSimbolos& table, int &rotulo)
{
    if (token.simbolo == "sinicio")
    {
        token = Lexical(codigo_fonte,table);

        Analisa_comando_simples(token, codigo_fonte, lista_erros,table,rotulo);

        while (token.simbolo != "sfim") {
            if (token.simbolo == "sponto_virgula") {
                token = Lexical(codigo_fonte,table);
                if (token.simbolo != "sfim") {
                    if (token.simbolo != "sponto"){
                    } else {
                        cout << "Fim do inicio ausente." << endl;
                        exit(-1);
                    }
                    Analisa_comando_simples(token, codigo_fonte, lista_erros,table,rotulo);
                }
            }
            else {
                cerr << "Esperava-se ponto e vírgula." << endl;
                exit(-1);
                writeErrors(token.linha, codigo_fonte, lista_erros, erroPontoeVirgula);
                break;
            }
        }
        token = Lexical(codigo_fonte,table);
    }
    else {
        cerr << "Esperava-se início." << endl;
        exit(-1);
        writeErrors(token.linha, codigo_fonte, lista_erros, erroInicio);
    }
}

void analisadorSintatico(ifstream &codigo_fonte, TabelaDeSimbolos& table)
{
    string lista_erros = "lista_erros.txt";
    int rotulo = 0; // rótulo utilizado para referenciar funções

    // COMO FUNCIONA A TABELA DE SÍMBOLOS?
    // Ela possui 5 campos:
    // string data => nome do objeto
    // string tipo => tipo do objeto (ex. "funcao booleana", "sinteiro", "nomedoprograma")
    // bool escopo => equivalente de marcar um galho, quando marcado como true, marca um novo escopo. Utilizado para desempilhar escopos.
    // int mem => lugar aonde a variável está alocada, utilizado para referenciar variáveis. Sempre aloca de maneira crescente, alocando de 1 para cima. 0 é reservado para retorno de função
    // int rotulo => rótulo atribuído à função, começa em 0 e vai incrementando.
    // há valores padrões, 'escopo' quando não for relevante é false, 'mem' quando não for relevante é -1 e 'rótulo' quando não for relevante também é -1.
    
    Token token = Lexical(codigo_fonte,table);
    if (token.simbolo == "sprograma")
    {
        // gera os START e ALLOC 0 1 ambiguos para todos os programas
        geraSTART();
        geraALLOC(0,1);

        token = Lexical(codigo_fonte,table);
        if (token.simbolo == "sidentificador")
        {

            // COLOCAR O NOME DO PROGRAMA NA TABELA DE SIMBOLOS :D
            // insere o nome do programa na tabela de símbolos
            table.insertAtHead(token.lexema, "nomedeprograma", false, -1, rotulo);
            rotulo++;
            token = Lexical(codigo_fonte,table);
            
            if (token.simbolo == "sponto_virgula")
            {
                AnalisaBloco(token, codigo_fonte, lista_erros,table,rotulo);
                
                if (token.simbolo == "sponto")
                {
                    // Compilado com sucesso! Após detectar o ponto final.
                    cout << "Compilado com sucesso!" << endl;

                    // Esvazia o vetor de alocacoes
                    // Toda vez que uma alocação é feita (ALLOC) ele adiciona os valores neste vetor
                    // Este código abaixo realiza o DALLOC da primeira alocação feita no programa
                    if (!alocacoes.empty()) {
                    int c_temp = alocacoes.back();
                    alocacoes.pop_back();
                    int b_temp = alocacoes.back();
                    alocacoes.pop_back();
                    geraDALLOC(b_temp,c_temp);
                    }
                    
                    // gera o DALLOC e o HLT ambiguos para todos os programas
                    geraDALLOC(0,1);
                    geraHLT();
                }
                else
                {
                    cerr << "Esperava-se ponto final." << endl;
                    exit(-1);
                    writeErrors(token.linha, codigo_fonte, lista_erros, erroPontoFinal);
                }
            }
            else
            {
                cerr << "Esperava-se ponto e vírgula." << endl;
                exit(-1);
                writeErrors(token.linha, codigo_fonte, lista_erros, erroPontoeVirgula);
                exit(0);
            }
        }
        else
        {
            cerr << "Esperava-se identificador programa." << endl;
            exit(-1);
            writeErrors(token.linha, codigo_fonte, lista_erros, erroIdentificadorPrograma);
        }
    }
    else
    {
        // Primeiro erro da regra Analisador sintatico <programa>
        cerr << "Esperava-se identificador programa." << endl;
        exit(-1);
        writeErrors(token.linha, codigo_fonte, lista_erros, erroIdentificadorPrograma);
    }
}
