#include <iostream>
#include <fstream>
#include <string>
#include "tokens.hpp"
#include "lexical.hpp"
#include "erros.hpp"
#include "sintatico.hpp"

using namespace std;

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



void Analisa_et_variaveis(Token &token, ifstream &codigo_fonte, string &lista_erros, TabelaDeSimbolos& table)
{
    // cout << "bem vindo ao analisa_et_variaveis" << endl;
    if (token.simbolo == "svar")
    {
        token = analisadorLexical(codigo_fonte,table);
        if (token.simbolo == "sidentificador")
        {
            do
            {   // sou inocente
                AnalisaVariaveis(token, codigo_fonte, lista_erros,table);
                if (token.simbolo == "sponto_virgula")
                {
                    token = analisadorLexical(codigo_fonte,table);
                }
                else
                {
                    // erro de ponto e virgula <etapa de declaração de variaveis>
                    writeErrors(token.linha, codigo_fonte, lista_erros, erroPontoeVirgula);
                }

            } while (token.simbolo == "sidentificador");
        }
        else
        {
            // Erro espera-se identificador <etapa de declaração de variaveis>
            // cout << "analisa_et_variaveis" << endl;
            writeErrors(token.linha, codigo_fonte, lista_erros, erroIdentificador);
        }
    }
}

void AnalisaBloco(Token &token, ifstream &codigo_fonte, string &lista_erros, TabelaDeSimbolos& table)
{
    // cout << "bem vindo ao AnalisaBloco" << endl;
    token = analisadorLexical(codigo_fonte,table);

    Analisa_et_variaveis(token, codigo_fonte, lista_erros,table);
    Analisa_subrotinas(token, codigo_fonte, lista_erros,table);
    Analisa_comandos(token, codigo_fonte, lista_erros,table);
}

void Analisa_identificador(Token &token, ifstream &codigo_fonte, string &lista_erros, TabelaDeSimbolos& table)
{
    // cout << "bem vindo ao Analisa_identificador" << endl;
    // :D
    if (!isalpha(token.lexema[0])) {
        writeErrors(token.linha, codigo_fonte, lista_erros, erroIdentificadorInvalidoProc);
    } 
}

void Analisa_Tipo(Token &token, ifstream &codigo_fonte, string &lista_erros, TabelaDeSimbolos& table)
{
    // cout << "bem vindo ao Analisa_Tipo" << endl;
    if (token.simbolo != "sinteiro" && token.simbolo != "sbooleano")
    {
        writeErrors(token.linha, codigo_fonte, lista_erros, erroTipoInvalido);
    }
    else
    {
        table.coloca_tipo_tabela(token.simbolo);
    }
    token = analisadorLexical(codigo_fonte,table);
}

void AnalisaVariaveis(Token &token, ifstream &codigo_fonte, string &lista_erros, TabelaDeSimbolos& table)
{
    
    do {
        if (token.simbolo == "sidentificador") {
            // PESQUISAR DUPLICATAS NA TABELA O LEXEMA DO TOKEN
                if (!table.pesquisa_duplicvar_tabela(token.lexema)){
                    int mem = 12222222;
                    table.insertAtHead(token.lexema, token.simbolo, mem);
                    token = analisadorLexical(codigo_fonte,table);

                    if (token.simbolo == "svirgula" || token.simbolo == "sdoispontos") {

                        if (token.simbolo == "svirgula") {

                            token = analisadorLexical(codigo_fonte,table);

                            if (token.simbolo == "sdoispontos") {
                                // Erro encontrou um dois pontos aos inves de um identificador <analisa_variaveis>
                                writeErrors(token.linha, codigo_fonte, lista_erros, erroIdentificador);
                            }

                        }

                    } else {
                        // Erro para eseperar pontuação <analisa_variaveis>
                        writeErrors(token.linha, codigo_fonte, lista_erros,erroPontuacao);
                    }

                } else {
                    writeErrors(token.linha, codigo_fonte, lista_erros, erroDuplicidadeDecaracao);
                }      
        } else {
            // Erro de esperar um identificador <analisa_variaveis>
            cout << "AnalisaVariaveis 2" << endl;
            writeErrors(token.linha, codigo_fonte, lista_erros,erroIdentificador);
        }
    } while (token.simbolo != "sdoispontos");

    token = analisadorLexical(codigo_fonte,table);
    Analisa_Tipo(token, codigo_fonte, lista_erros,table);
}

void Analisa_declaracao_procedimento(Token &token, ifstream &codigo_fonte, string &lista_erros, TabelaDeSimbolos& table)
{
    // cout << "bem vindo ao Analisa_declaracao_procedimento" << endl;
    token = analisadorLexical(codigo_fonte,table);
    if (token.simbolo == "sidentificador")
    {
        token = analisadorLexical(codigo_fonte,table);
        if (token.simbolo == "sponto_virgula")
        {
            AnalisaBloco(token, codigo_fonte, lista_erros,table);
        }
        else
        {
            // erro de pontuação ponto_virgula
            writeErrors(token.linha, codigo_fonte, lista_erros, erroPontoeVirgula);
        }
    
    }
    else
    {
        // ERRO NAO TEM IDENTIFICADOR
        cout << "Analisa_declaracao_procedimento" << endl;
        writeErrors(token.linha, codigo_fonte, lista_erros, erroIdentificador);
        // RETIRAR O GALHO DA TABELA DE SIMBOLOS
    }
}

// ME ARRUMA CARAAAAAAAAAAAAAAAA
// ME IMPLEMENTA IRMÃO
void Analisa_declaracao_funcao(Token &token, ifstream &codigo_fonte, string &lista_erros, TabelaDeSimbolos& table)
{
    
    token = analisadorLexical(codigo_fonte,table);
    // Precisamos de uma função MARCA GALHO NA TABELA exatamente antes de entrar naquele if ali 
    // a função é só pegar o escopo e marcar (eu acho q ta bool se n estiver usa bool po)
    if (token.simbolo == "sidentificador") {
        // Implementar uma busca para procedimentos, verifica se não tem algum procedimento com o mesmo nome
        // se tiver com o mesmo nome e marcado -> B.O
        bool flag = false;

        if (flag){
            // Se não encontrou
            // Tem que implementar um insertAt do tipo procedimento (ele não vai ter memoria por exemplo)
            // mas eu n sei o que é nivel 
            // provavelmente vamos precisar de uma variavel global ?
            // table.insertAtHead(token.lexema, "procedimento",algo aqui , parte em vemelho :( )

             token = analisadorLexical(codigo_fonte,table);
            if (token.simbolo == "sdoispontos") {
                token = analisadorLexical(codigo_fonte,table);
                if (token.simbolo == "sinteiro" || token.simbolo == "sbooleano") {
                    token = analisadorLexical(codigo_fonte,table);
                    if (token.simbolo == "sponto_virgula") {
                        AnalisaBloco(token, codigo_fonte, lista_erros,table);
                    }
                }
                else {
                    writeErrors(token.linha, codigo_fonte, lista_erros, erroTipoInvalido);
                }
            }
            else {
                writeErrors(token.linha, codigo_fonte, lista_erros, erroDoisPontos);
            }

        }else{
            writeErrors(token.linha, codigo_fonte, lista_erros, erroDuplicidadeDecaracao);
        }
    }
    else {
   
        writeErrors(token.linha, codigo_fonte, lista_erros, erroIdentificador);
        table.pop();
    }
}

void Analisa_subrotinas(Token &token, ifstream &codigo_fonte, string &lista_erros, TabelaDeSimbolos& table)
{
    // cout << "bem vindo ao Analisa_subrotinas" << endl;
    while (token.simbolo == "sprocedimento" || token.simbolo == "sfuncao") {
        if (token.simbolo == "sprocedimento") {
            Analisa_declaracao_procedimento(token, codigo_fonte, lista_erros,table);
        }
        else {
            Analisa_declaracao_funcao(token, codigo_fonte, lista_erros,table);
        }
        if (token.simbolo == "sponto_virgula") {
            token = analisadorLexical(codigo_fonte,table);
        }
        else {
            writeErrors(token.linha, codigo_fonte, lista_erros, erroPontoeVirgula);
        }
    }
}

void Analisa_atribuicao(Token &token, ifstream &codigo_fonte, string &lista_erros, TabelaDeSimbolos& table)
{
    
    token = analisadorLexical(codigo_fonte,table);
    Analisa_expressao(token, codigo_fonte, lista_erros,table);
    
}

void Chamada_procedimento(Token &token, ifstream &codigo_fonte, string &lista_erros, TabelaDeSimbolos& table, Token token_passado)
{
    
    // token = analisadorLexical(codigo_fonte,table);
    cout << "#[" << token_passado.lexema << "]#" <<endl;
    if (token_passado.simbolo == "sidentificador")
    {


        Analisa_identificador(token_passado, codigo_fonte, lista_erros,table);
        // token = analisadorLexical(codigo_fonte,table);
    }
    else
    {
        // Erro identificador não encontrado <chamada de procedimento>
        cout << "Chamada_procedimento" << endl;
        writeErrors(token.linha, codigo_fonte, lista_erros, erroIdentificador);
    }
}


// IMPLEMENTA AQUI CARA 
void Analisa_chamada_funcao(Token &token, ifstream &codigo_fonte, string &lista_erros, TabelaDeSimbolos& table) {
    
    // PRECISA MARCAR UM GALHO NA TABELA DE SIMBOLOSSSS
    if (token.simbolo == "sidentificador")
    {
        // PESQUISA NA TABELA DE SIMBOLOS SE EXISTE
        // AMIGAO TA ERRADO AQUI 
        // PRECISAMOS DE UMA BUSCA DO TIPO DECLARAÇAO DE FUNCAO 
        // PROCURA ATÉ ACHAR UM NOME MARCADO , SE FOR DIFERENTE IRMÃO RETORNA TRUE NESSA PORR
        bool flag = table.searchFor(token.lexema);
            if (!flag){
                Analisa_identificador(token, codigo_fonte, lista_erros,table);
                
                // AQUI PRECISA COLOCAR UM INSERE DO TIPO FUNÇÃO 

                token = analisadorLexical(codigo_fonte,table);
                if (token.simbolo == "sdoispontos")
                {
                    AnalisaBloco(token, codigo_fonte, lista_erros,table);
                    token = analisadorLexical(codigo_fonte,table);
                    Analisa_Tipo(token, codigo_fonte, lista_erros,table);
                    if (token.simbolo == "sponto_virgula") {
                        AnalisaBloco(token, codigo_fonte, lista_erros,table);
                    }
                    else {
                        writeErrors(token.linha, codigo_fonte, lista_erros, erroPontoeVirgula);    
                    }
                }
                else
                {
                    // erro de pontuação ponto_virgula
                    cout << "Analisa CHAMADA FUNCAO ERRO" << endl;
                    cout << token.lexema << " " << token.simbolo << endl;
                    writeErrors(token.linha, codigo_fonte, lista_erros, erroDoisPontos);
                }
            Analisa_identificador(token, codigo_fonte, lista_erros,table);
            token = analisadorLexical(codigo_fonte,table);
            }
            else{
                writeErrors(token.linha, codigo_fonte, lista_erros, erroDoisPontos);
            }

            
    }
    else
    {
        // ERRO NAO TEM IDENTIFICADOR
        cout << "Analisa_chamada_funcao" << endl;
        writeErrors(token.linha, codigo_fonte, lista_erros, erroIdentificador);
        // RETIRAR O GALHO DA TABELA DE SIMBOLOS
    }
}

void Analisa_fator(Token &token, ifstream &codigo_fonte, string &lista_erros, TabelaDeSimbolos& table)
{
    // cout << "bem vindo ao Analisa_fator" << endl;
    // cout << token.lexema << " " << token.simbolo << " no Analisa_fator" << endl;
    // token = analisadorLexical(codigo_fonte,table);
    if (token.simbolo == "sidentificador")
    {
        // Pesquisar na tabela  e esse if ta errado provavelmente ;D
        Analisa_chamada_funcao(token, codigo_fonte, lista_erros,table);
    }
    else { 
        if (token.simbolo == "snumero")
        {
            // cout << "snumero" << endl;
            // cout << token.lexema << " " << token.simbolo << endl;
            token = analisadorLexical(codigo_fonte,table);
            // cout << token.lexema << " " << token.simbolo << endl;
        }
        else {
            if (token.simbolo == "snao")
                {
                    // cout << "snao" << endl;
                    // cout << token.lexema << " " << token.simbolo << endl;   
                    token = analisadorLexical(codigo_fonte,table);
                    // cout << token.lexema << " " << token.simbolo << endl;
                    Analisa_fator(token, codigo_fonte, lista_erros,table);
                }
            else {
                if (token.simbolo == "sabre_parenteses") {
                    // cout << "sabreparenteses" << endl;
                    // cout << token.lexema << " " << token.simbolo << endl;
                    token = analisadorLexical(codigo_fonte,table);
                    // cout << token.lexema << " " << token.simbolo << endl;
                    Analisa_expressao(token, codigo_fonte, lista_erros,table);
                    if (token.simbolo == "sfecha_parenteses"){
                        // cout << "sfrechaparetenses" << endl;
                        // cout << token.lexema << " " << token.simbolo << endl;
                        token = analisadorLexical(codigo_fonte,table);
                        // cout << token.lexema << " " << token.simbolo << endl;
                    }
                    else {
                        cout << "ha1" << endl;
                        cout << token.lexema << " " << token.simbolo << endl;
                        writeErrors(token.linha, codigo_fonte, lista_erros, erroFechamentoDeParenteses);        
                    }
                }   
                else {
                    if (token.simbolo == "sverdadeiro" || token.simbolo == "sfalso") {
                        // cout << "svdd ou smentira" << endl;
                        // cout << token.lexema << " " << token.simbolo << endl;
                        token = analisadorLexical(codigo_fonte,table);
                        // cout << token.lexema << " " << token.simbolo << endl;
                    }
                    else {
                        cout << "ha2" << endl;
                        cout << token.lexema << " " << token.simbolo << endl;
                        writeErrors(token.linha, codigo_fonte, lista_erros, erroFechamentoDeParenteses); // me mude :c
                        // OLHA PARA MIM
                        // SOCORRO
                        // ESTOU EM PERIGO
                        // ATENÇÃO
                    }
                }
            }
        }
    }
}
void Analisa_termo(Token &token, ifstream &codigo_fonte, string &lista_erros, TabelaDeSimbolos& table)
{
    // cout << "bem vindo ao Analisa_termo" << endl;
    // cout << "de fora do while do analisa_termo" << endl;
    Analisa_fator(token, codigo_fonte, lista_erros,table);
    
    while ((token.simbolo == "smult") || (token.simbolo == "sdiv") || (token.simbolo == "se"))
    {
        token = analisadorLexical(codigo_fonte,table);
        // cout << "de dentro do while do analisa_termo" << endl;
        Analisa_fator(token, codigo_fonte, lista_erros,table);

    } 
}

void Analisa_expressao_simples(Token &token, ifstream &codigo_fonte, string &lista_erros, TabelaDeSimbolos& table)
{
    // cout << "bem vindo ao Analisa_expressao_simples" << endl;
    if (token.simbolo == "smais" || token.simbolo == "smenos")
    {
        token = analisadorLexical(codigo_fonte,table);
    }
    Analisa_termo(token, codigo_fonte, lista_erros,table);

    while ((token.simbolo == "smais") || (token.simbolo == "smenos") || (token.simbolo == "sou"))
    {
        token = analisadorLexical(codigo_fonte,table);
        Analisa_termo(token, codigo_fonte, lista_erros,table);

    } 
    
}

void Analisa_expressao(Token &token, ifstream &codigo_fonte, string &lista_erros, TabelaDeSimbolos& table)
{
    // cout << "bem vindo ao Analisa_expressao" << endl;
    Analisa_expressao_simples(token, codigo_fonte, lista_erros,table);

    if (token.simbolo == "smaior" || token.simbolo == "smaiorig" || token.simbolo == "sig" || token.simbolo == "smenor" || token.simbolo == "smenorig" || token.simbolo == "sdif")
    {

        token = analisadorLexical(codigo_fonte,table);
        Analisa_expressao_simples(token, codigo_fonte, lista_erros,table);
    }
}

void Analisa_chamada_procedimento(Token &token, ifstream &codigo_fonte, string &lista_erros, TabelaDeSimbolos& table) {
    cout << "chamado" << endl;
    // cout << "bem vindo ao Analisa_chamada_procedimento" << endl;
    token = analisadorLexical(codigo_fonte,table);
    if (token.simbolo != "sidentificador") {
        writeErrors(token.linha, codigo_fonte, lista_erros, erroChamadaProcedimento);
    } else {
        Analisa_identificador(token, codigo_fonte, lista_erros,table);
        token = analisadorLexical(codigo_fonte,table);
        if (token.simbolo != "sponto_virgula") {
            writeErrors(token.linha, codigo_fonte, lista_erros, erroPontoeVirgula);
        }
    }
}

// VOLTAR DEPOIS TEM COISA ERRADA
void Analisa_atrib_chprocedimento(Token &token, ifstream &codigo_fonte, string &lista_erros, TabelaDeSimbolos& table)
{
    // cout << "bem vindo ao Analisa_atrib_chprocedimento" << endl;
    Token token_passado = token;
    token = analisadorLexical(codigo_fonte,table); 
    // <stribuiçao_chprocedimento> ::= (<comando atribuicao> | <chamada de procedimento>)
    if (token.simbolo == "satribuicao")
    {
        Analisa_atribuicao(token, codigo_fonte, lista_erros,table);
    }
    else
    {
        Chamada_procedimento(token, codigo_fonte, lista_erros,table, token_passado);
    }
}

void Analisa_enquanto(Token &token, ifstream &codigo_fonte, string &lista_erros, TabelaDeSimbolos& table)
{
    // cout << "bem vindo ao Analisa_enquanto" << endl;
    token = analisadorLexical(codigo_fonte,table);

    Analisa_expressao(token, codigo_fonte, lista_erros,table);
    if (token.simbolo == "sfaca")
    {
        token = analisadorLexical(codigo_fonte,table);
        Analisa_comando_simples(token, codigo_fonte, lista_erros,table);
    }
    else
    {
        // ERRO ?
        writeErrors(token.linha, codigo_fonte, lista_erros, erroPontoFinal);
    }
}

void Analisa_se(Token &token, ifstream &codigo_fonte, string &lista_erros, TabelaDeSimbolos& table)
{
    // cout << "bem vindo ao Analisa_se" << endl;
    token = analisadorLexical(codigo_fonte,table);
    // cout << "pos se" << endl;
    // cout << token.lexema << " " << token.simbolo << endl;
    Analisa_expressao(token, codigo_fonte, lista_erros,table);
    // cout << "decimo quinto cout" << endl;
    // cout << token.lexema << " " << token.simbolo << endl;
    if (token.simbolo == "sentao") {
        token = analisadorLexical(codigo_fonte,table);
        Analisa_comando_simples(token, codigo_fonte, lista_erros,table);
        if (token.simbolo == "ssenao") {
            cout << "SENAO OQ???" << endl;
            token = analisadorLexical(codigo_fonte,table);
            Analisa_comando_simples(token, codigo_fonte, lista_erros,table);    
        }
    }
    else {
        writeErrors(token.linha, codigo_fonte, lista_erros, erroEsperaEntao);
    }
}

// Falta um pesquisa toda tabela ? Não entendi 
// TEM QUE IMPLEMENTAR
// ME ARRUMA CARA 
// PELO AMOR DE DEUS ME ARRUMA IRMÃO
void Analisa_leia(Token &token, ifstream &codigo_fonte, string &lista_erros, TabelaDeSimbolos& table)
{
    
    token = analisadorLexical(codigo_fonte,table);
    if (token.simbolo == "sabre_parenteses") {
        token = analisadorLexical(codigo_fonte,table);
        if (token.simbolo == "sidentificador") {

            bool flag = table.pesquisa_declvar_tabela(token.lexema);
            if (flag){
                // Supostamente tem um busca toda tabela aqui e tem um erro 
                token = analisadorLexical(codigo_fonte,table);
                if (token.simbolo == "sfecha_parenteses") {
                    token = analisadorLexical(codigo_fonte,table);
                }
                else {
                    writeErrors(token.linha, codigo_fonte, lista_erros, erroFechamentoDeParenteses);
                }    
            } 
            else{
                writeErrors(token.linha, codigo_fonte, lista_erros, erroNaoExisteVariavel);
            }
            
        }
        else {
            writeErrors(token.linha, codigo_fonte, lista_erros, erroFechamentoDeParenteses);
        }
    }
    else {
        writeErrors(token.linha, codigo_fonte, lista_erros, erroFechamentoDeParenteses);
    }
}

void Analisa_escreva(Token &token, ifstream &codigo_fonte, string &lista_erros, TabelaDeSimbolos& table)
{
    
    token = analisadorLexical(codigo_fonte,table);
    if (token.simbolo == "sabre_parenteses")
    {
        token = analisadorLexical(codigo_fonte,table);
        if (token.simbolo == "sidentificador")
        {
            
            bool existe = table.searchFor(token.lexema);

            if (existe)
            {
                token = analisadorLexical(codigo_fonte,table);

                if (token.simbolo == "sfecha_parenteses")
                {
                    token = analisadorLexical(codigo_fonte,table);
                }
                else
                {
                    writeErrors(token.linha, codigo_fonte, lista_erros, erroFechamentoDeParenteses);
                }
            }
            else
            {
                writeErrors(token.linha, codigo_fonte, lista_erros, erroIdentificadorNaoExiste);
            }
            token = analisadorLexical(codigo_fonte,table);
            if (token.simbolo == "sfecha_parenteses") {
                token = analisadorLexical(codigo_fonte,table);
            }
            else {
                cout << "ha6" << endl;
                writeErrors(token.linha, codigo_fonte, lista_erros, erroFechamentoDeParenteses);
            }
        }
        else
        {
            cout << "Analisa_escreva" << endl;
            writeErrors(token.linha, codigo_fonte, lista_erros, erroIdentificador);
        }
    }
    else
    {
        cout << "ha7" << endl;
        writeErrors(token.linha, codigo_fonte, lista_erros, erroFechamentoDeParenteses);
    }
}
void Analisa_comando_simples(Token &token, ifstream &codigo_fonte, string &lista_erros, TabelaDeSimbolos& table)
{
    // cout << "bem vindo ao Analisa_comando_simples" << endl;
    if (token.simbolo == "sidentificador")
    {
        // TEM QUE OLHAR ESSA FUNÇAO !!!!
        Analisa_atrib_chprocedimento(token, codigo_fonte, lista_erros,table);
    }
    else if (token.simbolo == "sse")
    {
        Analisa_se(token, codigo_fonte, lista_erros,table);
    }
    else if (token.simbolo == "senquanto")
    {
        Analisa_enquanto(token, codigo_fonte, lista_erros,table);
    }
    else if (token.simbolo == "sleia")
    {
        Analisa_leia(token, codigo_fonte, lista_erros,table);
    }
    else if (token.simbolo == "sescreva")
    {
        Analisa_escreva(token, codigo_fonte, lista_erros,table);
    }
    else
    {
        Analisa_comandos(token, codigo_fonte, lista_erros,table);
    }
}

void Analisa_comandos(Token &token, ifstream &codigo_fonte, string &lista_erros, TabelaDeSimbolos& table)
{
    // cout << "bem vindo ao Analisa_comandos" << endl;
    if (token.simbolo == "sinicio")
    {
        token = analisadorLexical(codigo_fonte,table);

        Analisa_comando_simples(token, codigo_fonte, lista_erros,table);

        while (token.simbolo != "sfim") {
            if (token.simbolo == "sponto_virgula") {
                token = analisadorLexical(codigo_fonte,table);
                if (token.simbolo != "sfim") {
                    Analisa_comando_simples(token, codigo_fonte, lista_erros,table);
                }
            }
            else {
                writeErrors(token.linha, codigo_fonte, lista_erros, erroPontoeVirgula);
                break;
            }
        }
        token = analisadorLexical(codigo_fonte,table);
    }
    else {
        writeErrors(token.linha, codigo_fonte, lista_erros, erroInicio);
    }
}

void analisadorSintatico(ifstream &codigo_fonte, TabelaDeSimbolos& table, TabelaDeSimbolos& SymbolTable)
{
    // table é utilizada para o LÉXICO
    // SymbolTable é utilizada pelo SEMÂNTICO
    string lista_erros = "lista_erros.txt";
    Token token = analisadorLexical(codigo_fonte,table);
    if (token.simbolo == "sprograma")
    {

        token = analisadorLexical(codigo_fonte,table);
        if (token.simbolo == "sidentificador")
        {

            // COLOCAR O NOME DO PROGRAMA NA TABELA DE SIMBOLOS :D
            int mem = 1022201455;
            table.insertAtHead(token.lexema, "declaração_programa", true, mem);
            
            token = analisadorLexical(codigo_fonte,table);
            
            if (token.simbolo == "sponto_virgula")
            {
                AnalisaBloco(token, codigo_fonte, lista_erros,table);
                
                if (token.simbolo == "sponto")
                {
                    cout << "COMPILAMOS PORR" << endl;
                }
                else
                {
                    // Erro de ponto final <programa>
                    cout << "sdfujibghnwdf8iougberg" << endl;
                    cout << token.lexema << " " << token.simbolo << endl;
                    writeErrors(token.linha, codigo_fonte, lista_erros, erroPontoFinal);
                }
            }
            else
            {
                // Erro de ponto-virgula <programa>
                writeErrors(token.linha, codigo_fonte, lista_erros, erroPontoeVirgula);
            }
        }
        else
        {
            // Erro do identificador <programa>
            writeErrors(token.linha, codigo_fonte, lista_erros, erroIdentificadorPrograma);
        }
    }
    else
    {
        // Primeiro erro da regra Analisador sintatico <programa>
        writeErrors(token.linha, codigo_fonte, lista_erros, erroIdentificadorPrograma);
    }
    token = analisadorLexical(codigo_fonte,table);
    // cout << token.lexema << " " << token.simbolo << endl;
    if (!token.isEmpty()) {
        writeErrors(token.linha, codigo_fonte, lista_erros, "!!! Comandos detectados apos o ponto final.");
    }
}
