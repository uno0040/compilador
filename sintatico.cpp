#include <iostream>
#include <fstream>
#include <string>
#include "tokens.hpp"
#include "lexical.hpp"
#include "erros.hpp"
#include "sintatico.hpp"

using namespace std;

string erroTipoInvalido = "Erro tipo nao existente! Na linha: ";
string erroIdentificadorNaoExiste = "Erro identificador nao declarado! Na linha: ";
string erroIdentificadorPrograma = "Espera-se um identificador Programa na linha: ";
string erroIdentificador = "Espera-se um identificador na linha: ";
string erroPontoeVirgula = "Espera-se uma pontuacao do tipo ; ";
string erroPontoFinal = "Espera-se uma pontuacao do tipo . ";
string erroPontuacao = "Espera-se pontuacao na linha: ";
string erroFechamentoDeParenteses = "Erro de fechamento de parenteses na linha: ";
string erroIdentificadorProcedimento = "Espera-se um identificador Procedimento na linha: ";
string erroConflitoIdentificadores = "Identificador ja foi utilizado! Mude o identificador na linha: ";
string erroIdentificadorInvalidoProc = "Identificador com sintaxe inválida >:(";
string erroEsperaEntao = "Espera-se um 'entao'.";
string erroDoisPontos = "Espera-se ':'.";
string erroInicio = "Espera-se 'inicio'.";
string erroChamadaProcedimento = "Procedimento deve ter uma nome identificador.";



void Analisa_et_variaveis(Token &token, ifstream &codigo_fonte, string &lista_erros, TabelaDeSimbolos& table)
{
    cout << "bem vindo ao analisa_et_variaveis" << endl;
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
            writeErrors(token.linha, codigo_fonte, lista_erros, erroIdentificador);
        }
    }
}

void AnalisaBloco(Token &token, ifstream &codigo_fonte, string &lista_erros, TabelaDeSimbolos& table)
{
    cout << "bem vindo ao AnalisaBloco" << endl;
    token = analisadorLexical(codigo_fonte,table);

    Analisa_et_variaveis(token, codigo_fonte, lista_erros,table);
    Analisa_subrotinas(token, codigo_fonte, lista_erros,table);
    Analisa_comandos(token, codigo_fonte, lista_erros,table);
}

void Analisa_identificador(Token &token, ifstream &codigo_fonte, string &lista_erros, TabelaDeSimbolos& table)
{
    cout << "bem vindo ao Analisa_identificador" << endl;
    // :D
    if (!isalpha(token.lexema[0])) {
        writeErrors(token.linha, codigo_fonte, lista_erros, erroIdentificadorInvalidoProc);
    } 
}

void Analisa_Tipo(Token &token, ifstream &codigo_fonte, string &lista_erros, TabelaDeSimbolos& table)
{
    cout << "bem vindo ao Analisa_Tipo" << endl;
    if (token.simbolo != "sinteiro" && token.simbolo != "sbooleano")
    {
        writeErrors(token.linha, codigo_fonte, lista_erros, erroTipoInvalido);
    }
    else
    {

        // COLOCAR NA TABELA
    }
    token = analisadorLexical(codigo_fonte,table);
}

void AnalisaVariaveis(Token &token, ifstream &codigo_fonte, string &lista_erros, TabelaDeSimbolos& table)
{
    cout << "bem vindo ao AnalisaVariaveis" << endl;
    do {
        if (token.simbolo == "sidentificador") {
            // PESQUISAR DUPLICATAS NA TABELA O LEXEMA DO TOKEN

                // COLOCAR O TOKEN NA TABELA SE ELE NÃO EXISTIR

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
            // Erro de esperar um identificador <analisa_variaveis>
            writeErrors(token.linha, codigo_fonte, lista_erros,erroIdentificador);
        }
    } while (token.simbolo != "sdoispontos");

    token = analisadorLexical(codigo_fonte,table);
    Analisa_Tipo(token, codigo_fonte, lista_erros,table);
}

void Analisa_declaracao_procedimento(Token &token, ifstream &codigo_fonte, string &lista_erros, TabelaDeSimbolos& table)
{
    cout << "bem vindo ao Analisa_declaracao_procedimento" << endl;
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
        writeErrors(token.linha, codigo_fonte, lista_erros, erroIdentificador);
        // RETIRAR O GALHO DA TABELA DE SIMBOLOS
    }
}

void Analisa_declaracao_funcao(Token &token, ifstream &codigo_fonte, string &lista_erros, TabelaDeSimbolos& table)
{
    cout << "bem vindo ao Analisa_declaracao_funcao" << endl;
    token = analisadorLexical(codigo_fonte,table);
    if (token.simbolo == "sidentificador") {
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
    }
    else {
        writeErrors(token.linha, codigo_fonte, lista_erros, erroIdentificador);
    }
}

void Analisa_subrotinas(Token &token, ifstream &codigo_fonte, string &lista_erros, TabelaDeSimbolos& table)
{
    cout << "bem vindo ao Analisa_subrotinas" << endl;
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
}

void Chamada_procedimento(Token &token, ifstream &codigo_fonte, string &lista_erros, TabelaDeSimbolos& table)
{
    cout << "bem vindo ao Chamada_procedimento" << endl;
    token = analisadorLexical(codigo_fonte,table);
    if (token.simbolo == "sidentificador")
    {

        token = analisadorLexical(codigo_fonte,table);

        Analisa_identificador(token, codigo_fonte, lista_erros,table);
    }
    else
    {
        // Erro identificador não encontrado <chamada de procedimento>
        writeErrors(token.linha, codigo_fonte, lista_erros, erroIdentificador);
    }
}

void Analisa_chamada_funcao(Token &token, ifstream &codigo_fonte, string &lista_erros, TabelaDeSimbolos& table) {
    cout << "bem vindo ao Analisa_chamada_funcao" << endl;
    // PRECISA MARCAR UM GALHO NA TABELA DE SIMBOLOSSSS
    if (token.simbolo == "sidentificador")
    {
        // // PESQUISA NA TABELA DE SIMBOLOS SE EXISTE
        //     // Perfeito, não existe
        //     // COLOCA NA TABLEA DE SIMBOLOS

        //     Analisa_identificador(token, codigo_fonte, lista_erros,table);
        //     token = analisadorLexical(codigo_fonte,table);
        //     if (token.simbolo == "sdoispontos")
        //     {
        //         AnalisaBloco(token, codigo_fonte, lista_erros,table);
        //         token = analisadorLexical(codigo_fonte,table);
        //         Analisa_Tipo(token, codigo_fonte, lista_erros,table);
        //         if (token.simbolo == "sponto_virgula") {
        //             AnalisaBloco(token, codigo_fonte, lista_erros,table);
        //         }
        //         else {
        //             writeErrors(token.linha, codigo_fonte, lista_erros, erroPontoeVirgula);    
        //         }
        //     }
        //     else
        //     {
        //         // erro de pontuação ponto_virgula
        //         cout << "Analisa CHAMADA FUNCAO ERRO" << endl;
        //         cout << token.lexema << " " << token.simbolo << endl;
        //         writeErrors(token.linha, codigo_fonte, lista_erros, erroDoisPontos);
        //     }
        Analisa_identificador(token, codigo_fonte, lista_erros,table);
        token = analisadorLexical(codigo_fonte,table);
    }
    else
    {
        // ERRO NAO TEM IDENTIFICADOR
        writeErrors(token.linha, codigo_fonte, lista_erros, erroIdentificador);
        // RETIRAR O GALHO DA TABELA DE SIMBOLOS
    }
}

void Analisa_fator(Token &token, ifstream &codigo_fonte, string &lista_erros, TabelaDeSimbolos& table)
{
    cout << "bem vindo ao Analisa_fator" << endl;
    cout << token.lexema << " " << token.simbolo << " no Analisa_fator" << endl;
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
    cout << "bem vindo ao Analisa_termo" << endl;
    cout << "de fora do while do analisa_termo" << endl;
    Analisa_fator(token, codigo_fonte, lista_erros,table);
    
    while ((token.simbolo == "smult") || (token.simbolo == "sdiv") || (token.simbolo == "se"))
    {
        token = analisadorLexical(codigo_fonte,table);
        cout << "de dentro do while do analisa_termo" << endl;
        Analisa_fator(token, codigo_fonte, lista_erros,table);

    } 
}

void Analisa_expressao_simples(Token &token, ifstream &codigo_fonte, string &lista_erros, TabelaDeSimbolos& table)
{
    cout << "bem vindo ao Analisa_expressao_simples" << endl;
    if (token.simbolo == "smais" || token.simbolo == "smenos")
    {
        token = analisadorLexical(codigo_fonte,table);
    }
    Analisa_termo(token, codigo_fonte, lista_erros,table);

    do
    {
        token = analisadorLexical(codigo_fonte,table);
        Analisa_termo(token, codigo_fonte, lista_erros,table);

    } while ((token.simbolo == "smais") || (token.simbolo == "smenos") || (token.simbolo == "sou"));
    
}

void Analisa_expressao(Token &token, ifstream &codigo_fonte, string &lista_erros, TabelaDeSimbolos& table)
{
    cout << "bem vindo ao Analisa_expressao" << endl;
    Analisa_expressao_simples(token, codigo_fonte, lista_erros,table);

    if (token.simbolo == "smaior" || token.simbolo == "smaiorig" || token.simbolo == "sig" || token.simbolo == "smenor" || token.simbolo == "smenorig" || token.simbolo == "sdif")
    {

        token = analisadorLexical(codigo_fonte,table);
        Analisa_expressao_simples(token, codigo_fonte, lista_erros,table);
    }
}

void Analisa_chamada_procedimento(Token &token, ifstream &codigo_fonte, string &lista_erros, TabelaDeSimbolos& table) {
    cout << "chamado" << endl;
    cout << "bem vindo ao Analisa_chamada_procedimento" << endl;
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
    cout << "bem vindo ao Analisa_atrib_chprocedimento" << endl;
    token = analisadorLexical(codigo_fonte,table);
    // <stribuiçao_chprocedimento> ::= (<comando atribuicao> | <chamada de procedimento>)
    if (token.simbolo == "satribuicao")
    {

        // <comando atribuiçao> ::= <identificdor> := <expressao>
        // cout << "FUI CHAMADAAAAAAA" <<endl;
        Analisa_atribuicao(token, codigo_fonte, lista_erros,table);
    }
    else
    {
        Chamada_procedimento(token, codigo_fonte, lista_erros,table);
    }
}

void Analisa_enquanto(Token &token, ifstream &codigo_fonte, string &lista_erros, TabelaDeSimbolos& table)
{
    cout << "bem vindo ao Analisa_enquanto" << endl;
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
    cout << "bem vindo ao Analisa_se" << endl;
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

void Analisa_leia(Token &token, ifstream &codigo_fonte, string &lista_erros, TabelaDeSimbolos& table)
{
    // token = analisadorLexical(codigo_fonte,table);
    // if (token.simbolo == "sabre_parenteses")
    // {
    //     token = analisadorLexical(codigo_fonte,table);
    //     if (token.simbolo == "sidentificador")
    //     {
    //         // Pesquisa na tabela
    //         bool existe = true;
    //         // Se o identificado existe na tabela safe
    //         if (existe)
    //         {
    //             token = analisadorLexical(codigo_fonte,table);

    //             if (token.simbolo == "sfecha_parenteses")
    //             {
    //                 token = analisadorLexical(codigo_fonte,table);
    //             }
    //             else
    //             {
    //                 // Erro de fechamento de parenteses <comando leitura>
    //                 writeErrors(token.linha, codigo_fonte, lista_erros, erroFechamentoDeParenteses);
    //             }
    //         }
    //         else
    //         {
    //             // Erro identificador não existe <comando leitura>
    //             writeErrors(token.linha, codigo_fonte, lista_erros, erroIdentificadorNaoExiste);
    //         }
    //     }
    // }
    // else {
    //     writeErrors(token.linha, codigo_fonte, lista_erros, erroFechamentoDeParenteses);
    // }
    cout << "bem vindo ao Analisa_leia" << endl;
    token = analisadorLexical(codigo_fonte,table);
    if (token.simbolo == "sabre_parenteses") {
        token = analisadorLexical(codigo_fonte,table);
        if (token.simbolo == "sidentificador") {
            token = analisadorLexical(codigo_fonte,table);
            if (token.simbolo == "sfecha_parenteses") {
                token = analisadorLexical(codigo_fonte,table);
            }
            else {
                cout << "ha3" << endl;
                writeErrors(token.linha, codigo_fonte, lista_erros, erroFechamentoDeParenteses);
            }
        }
        else {
            cout << "ha4" << endl;
            writeErrors(token.linha, codigo_fonte, lista_erros, erroFechamentoDeParenteses);
        }
    }
    else {
        cout << "ha5" << endl;
        writeErrors(token.linha, codigo_fonte, lista_erros, erroFechamentoDeParenteses);
    }
}

void Analisa_escreva(Token &token, ifstream &codigo_fonte, string &lista_erros, TabelaDeSimbolos& table)
{
    cout << "bem vindo ao Analisa_escreva" << endl;
    token = analisadorLexical(codigo_fonte,table);
    if (token.simbolo == "sabre_parenteses")
    {
        token = analisadorLexical(codigo_fonte,table);
        if (token.simbolo == "sidentificador")
        {
            // // PESQUISAR NA TABELA
            // bool existe = true;

            // if (existe)
            // {
            //     token = analisadorLexical(codigo_fonte,table);

            //     if (token.simbolo == "sfecha_parenteses")
            //     {
            //         token = analisadorLexical(codigo_fonte,table);
            //     }
            //     else
            //     {
            //         writeErrors(token.linha, codigo_fonte, lista_erros, erroFechamentoDeParenteses);
            //     }
            // }
            // else
            // {
            //     writeErrors(token.linha, codigo_fonte, lista_erros, erroIdentificadorNaoExiste);
            // }
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
    cout << "bem vindo ao Analisa_comando_simples" << endl;
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
    cout << "bem vindo ao Analisa_comandos" << endl;
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
                // break;
            }
        }
        token = analisadorLexical(codigo_fonte,table);
    }
    else {
        writeErrors(token.linha, codigo_fonte, lista_erros, erroInicio);
    }
}

void analisadorSintatico(ifstream &codigo_fonte, TabelaDeSimbolos& table)
{

    string lista_erros = "lista_erros.txt";
    Token token = analisadorLexical(codigo_fonte,table);
    if (token.simbolo == "sprograma")
    {

        token = analisadorLexical(codigo_fonte,table);
        if (token.simbolo == "sidentificador")
        {

            // COLOCAR O NOME DO PROGRAMA NA TABELA DE SIMBOLOS :D

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
}
