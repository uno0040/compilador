#include <iostream>
#include <fstream>
#include <string>
#include "tokens.hpp"
#include "lexical.hpp"
#include "erros.hpp"

string erroTipoInvalido = "Erro tipo não existente! Na linha: ";
string erroIdentificadorNaoExiste = "Erro identificador não declarado! Na linha: ";
string erroIdentificadorPrograma = "Espera-se um identificador Programa na linha: ";
string erroIdentificador = "Espera-se um identificador na linha: ";
string erroPontoeVirgula = "Espera-se uma pontuação do tipo ; ";
string erroPontoFinal = "Espera-se uma pontuação do tipo . ";
string erroPontuacao = "Espera-se pontuação na linha: ";
string erroFechamentoDeParenteses = "Erro de fechamento de parenteses na linha: ";
string erroIdentificadorProcedimento = "Espera-se um identificador Procedimento na linha: ";
string erroConflitoIdentificadores = "Identificador já foi utilizado! Mude o identificador na linha: ";
using namespace std;

void Analisa_identificador_chamada_procedimento(Token &token, ifstream &codigo_fonte, string &lista_erros)
{
    // Checar se o identificados do procedimento existe na tabela
    // acho q é isso :D
    bool existe = true;
    if (existe)
    {
        // Ta tudo bem pq a função existe mas não é responsabilidade do sintatico chamar nada, eu acho
    }
    else
    {
        // Erro identificados não existe, procedimento não declarado
        string erroIdentificadorProcedimentoNaoExiste = "Procedimento " + token.lexema + " não foi declarado !";
        writeErrors(token.linha, codigo_fonte, lista_erros, erroIdentificadorProcedimentoNaoExiste);
    }
}

void Analisa_Tipo(Token &token, ifstream &codigo_fonte, string &lista_erros)
{

    if (token.simbolo != "sinteiro" && token.simbolo != "sbooleano")
    {
        writeErrors(token.linha, codigo_fonte, lista_erros, erroTipoInvalido);
    }
    else
    {

        // COLOCAR NA TABELA

        token = analisadorLexical(codigo_fonte);
    }
}

void AnalisaVariaveis(Token &token, ifstream &codigo_fonte, string &lista_erros)
{
    // do {
    //     if (token.simbolo == "sidentificador") {
    //         // PESQUISAR DUPLICATAS NA TABELA O LEXEMA DO TOKEN
    //         if (!Pesquisa_duplicvar_tabela(token.lexema)) {

    //             // COLOCAR O TOKEN NA TABELA SE ELE NÃO EXISTIR

    //             token = analisadorLexical(codigo_fonte);

    //             if (token.simbolo == "svirgula" || token.simbolo == "sdoispontos") {

    //                 if (token.simbolo == "svirgula") {

    //                     token = analisadorLexical(codigo_fonte);

    //                     if (token.simbolo == "sdoispontos") {
    //                         // Erro encontrou um dois pontos aos inves de um identificador <analisa_variaveis>
    //                         writeErrors(token.linha, codigo_fonte, lista_erros, erroIdentificador);
    //                     }

    //                 }

    //             } else {
    //                 // Erro para eseperar pontuação <analisa_variaveis>
    //                 writeErrors(token.linha, codigo_fonte, lista_erros,erroPontuacao);
    //             }
    //         }
    //     } else {
    //         // Erro de esperar um identificador <analisa_variaveis>
    //         writeErrors(token.linha, codigo_fonte, lista_erros,erroIdentificador);
    //     }
    // } while (token.simbolo != "sdoispontos");

    // token = analisadorLexical(codigo_fonte);
    // Analisa_Tipo(token, codigo_fonte, lista_erros);
}

void Analisa_et_variaveis(Token &token, ifstream &codigo_fonte, string &lista_erros)
{
    if (token.simbolo == "svar")
    {
        token = analisadorLexical(codigo_fonte);
        if (token.simbolo == "sidentificador")
        {
            do
            {
                AnalisaVariaveis(token, codigo_fonte, lista_erros);

                if (token.simbolo == "spontovirg")
                {

                    token = analisadorLexical(codigo_fonte);
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

void Analisa_declaracao_procedimento(Token &token, ifstream &codigo_fonte, string &lista_erros)
{
    token = analisadorLexical(codigo_fonte);
    // PRECISA MARCAR UM GALHO NA TABELA DE SIMBOLOSSSS
    if (token.simbolo == "sidentificador")
    {
        // PESQUISA NA TABELA DE SIMBOLOS SE EXISTE
        bool existe = true;

        if (!existe)
        {
            // Perfeito, não existe
            // COLOCA NA TABLEA DE SIMBOLOS

            token = analisadorLexical(codigo_fonte);
            if (token.simbolo == "sponto_virgula")
            {
                AnalisaBloco(token, codigo_fonte, lista_erros);
            }
            else
            {
                // erro de pontuação ponto_virgula
                writeErrors(token.linha, codigo_fonte, lista_erros, erroPontoeVirgula);
            }
        }
        else
        {
            // conflito de identificadores - identificador já existe
            writeErrors(token.linha, codigo_fonte, lista_erros, erroConflitoIdentificadores);
        }
    }
    else
    {
        // ERRO NAO TEM IDENTIFICADOR
        writeErrors(token.linha, codigo_fonte, lista_erros, erroIdentificador);
        // RETIRAR O GALHO DA TABELA DE SIMBOLOS
    }
}

void Analisa_subrotinas(Token &token, ifstream &codigo_fonte, string &lista_erros)
{
    do
    {
        if (token.simbolo == "sprocedimento")
        {
            Analisa_declaracao_procedimento(token, codigo_fonte, lista_erros);
        }
        else
        {
            // Erro de falta de palavra reservada Procedimento <declaração de procedimento>
            writeErrors(token.linha, codigo_fonte, lista_erros, erroIdentificadorProcedimento);
        }

    } while (token.simbolo == "sprocedimento" || token.simbolo == "sfuncao");
}

void Analisa_atribuicao(Token &token, ifstream &codigo_fonte, string &lista_erros)
{
}

void Chamada_procedimento(Token &token, ifstream &codigo_fonte, string &lista_erros)
{
    token = analisadorLexical(codigo_fonte);
    if (token.simbolo == "sidentificador")
    {

        token = analisadorLexical(codigo_fonte);

        Analisa_identificador_chamada_procedimento(token, codigo_fonte, lista_erros);
    }
    else
    {
        // Erro identificador não encontrado <chamada de procedimento>
        writeErrors(token.linha, codigo_fonte, lista_erros, erroIdentificador);
    }
}

void Analisa_fator(Token &token, ifstream &codigo_fonte, string &lista_erros)
{
    if (token.simbolo == "sidentificador")
    {
        // Pesquisar na tabela  e esse if ta errado provavelmente ;D

        bool existe = true;
        if (existe)
        {
        }
        else
        {
            // Erro função inteiro e erro função booleano ? não entendi o erro
            // TEM QUE MUDAR O ERRO ;D
            writeErrors(token.linha, codigo_fonte, lista_erros, erroPontoeVirgula);
        }
    }
    else if (token.simbolo == "snumero")
    {
        token = analisadorLexical(codigo_fonte);
        if (token.simbolo == "snao")
        {
        }
        else if (token.simbolo == "sabre_pareenteses")
        {
            // expressao entre parenteses
            token = analisadorLexical(codigo_fonte);
            Analisa_expressao(token, codigo_fonte, lista_erros);
            if (token.simbolo == "sfecha_parenteses")
            {
                token = analisadorLexical(codigo_fonte);
            }
            else
            {
                // Erro de fechamento de parenteses
                writeErrors(token.linha, codigo_fonte, lista_erros, erroFechamentoDeParenteses);
            }
        }
        else if (token.lexema == "verdadeiro" || token.lexema == "falso")
        {
            token = analisadorLexical(codigo_fonte);
        }
        else
        {
            // ERRO NÃO ENTENDI QUAL O ERRO SOCORRO :(
            writeErrors(token.linha, codigo_fonte, lista_erros, erroFechamentoDeParenteses);
        }
    }
}

void Analisa_termo(Token &token, ifstream &codigo_fonte, string &lista_erros)
{
    Analisa_fator(token, codigo_fonte, lista_erros);
    do
    {
        token = analisadorLexical(codigo_fonte);
        Analisa_fator(token, codigo_fonte, lista_erros);

    } while ((token.simbolo == "smult") || (token.simbolo == "sdiv") || (token.simbolo == "se"));
}

void Analisa_expressao_simples(Token &token, ifstream &codigo_fonte, string &lista_erros)
{
    if (token.simbolo == "smais" || token.simbolo == "smenos")
    {
        token = analisadorLexical(codigo_fonte);
        Analisa_termo(token, codigo_fonte, lista_erros);

        do
        {
            token = analisadorLexical(codigo_fonte);
            Analisa_termo(token, codigo_fonte, lista_erros);

        } while ((token.simbolo == "smais") || (token.simbolo == "smenos") || (token.simbolo == "sou"));
    }
}

void Analisa_expressao(Token &token, ifstream &codigo_fonte, string &lista_erros)
{

    Analisa_expressao_simples(token, codigo_fonte, lista_erros);

    if (token.simbolo == "smaior" || token.simbolo == "smaiorig" || token.simbolo == "sig" || token.simbolo == "smenor" || token.simbolo == "smenorig" || token.simbolo == "sdif")
    {

        token = analisadorLexical(codigo_fonte);
        Analisa_expressao_simples(token, codigo_fonte, lista_erros);
    }
}

// VOLTAR DEPOIS TEM COISA ERRADA
void Analisa_atrib_chprocedimento(Token &token, ifstream &codigo_fonte, string &lista_erros)
{

    token = analisadorLexical(codigo_fonte);
    // <stribuiçao_chprocedimento> ::= (<comando atribuicao> | <chamada de procedimento>)
    if (token.simbolo == "satribuicao")
    {

        // <comando atribuiçao> ::= <identificdor> := <expressao>
        Analisa_atribuicao(token, codigo_fonte, lista_erros);
    }
    else
    {
        Chamada_procedimento(token, codigo_fonte, lista_erros);
    }
}

void Analisa_enquanto(Token &token, ifstream &codigo_fonte, string &lista_erros)
{
    token = analisadorLexical(codigo_fonte);

    Analisa_expressao(token, codigo_fonte, lista_erros);
    if (token.simbolo == "sfaca")
    {
        token = analisadorLexical(codigo_fonte);
        Analisa_comando_simples(token, codigo_fonte, lista_erros);
    }
    else
    {
        // ERRO ?
        writeErrors(token.linha, codigo_fonte, lista_erros, erroPontoFinal);
    }
}

void Analisa_se(Token &token, ifstream &codigo_fonte, string &lista_erros)
{
    token = analisadorLexical(codigo_fonte);
    Analisa_expressao(token, codigo_fonte, lista_erros);
}

void Analisa_leia(Token &token, ifstream &codigo_fonte, string &lista_erros)
{
    token = analisadorLexical(codigo_fonte);
    if (token.simbolo == "sabre_parenteses")
    {
        token = analisadorLexical(codigo_fonte);
        if (token.simbolo == "sidentificador")
        {
            // Pesquisa na tabela
            bool existe = true;
            // Se o identificado existe na tabela safe
            if (existe)
            {
                token = analisadorLexical(codigo_fonte);

                if (token.simbolo == "sfecha_parenteses")
                {
                    token = analisadorLexical(codigo_fonte);
                }
                else
                {
                    // Erro de fechamento de parenteses <comando leitura>
                    writeErrors(token.linha, codigo_fonte, lista_erros, erroFechamentoDeParenteses);
                }
            }
            else
            {
                // Erro identificador não existe <comando leitura>
                writeErrors(token.linha, codigo_fonte, lista_erros, erroIdentificadorNaoExiste);
            }
        }
    }
}

void Analisa_escreva(Token &token, ifstream &codigo_fonte, string &lista_erros)
{
    token = analisadorLexical(codigo_fonte);
    if (token.simbolo == "sabre_parenteses")
    {
        token = analisadorLexical(codigo_fonte);
        if (token.simbolo == "sidentificador")
        {
            // PESQUISAR NA TABELA
            bool existe = true;

            if (existe)
            {
                token = analisadorLexical(codigo_fonte);

                if (token.simbolo == "sfecha_parenteses")
                {
                    token = analisadorLexical(codigo_fonte);
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
        }
        else
        {
            writeErrors(token.linha, codigo_fonte, lista_erros, erroIdentificador);
        }
    }
    else
    {
        writeErrors(token.linha, codigo_fonte, lista_erros, erroFechamentoDeParenteses);
    }
}
void Analisa_comando_simples(Token &token, ifstream &codigo_fonte, string &lista_erros)
{
    if (token.simbolo == "sidentificador")
    {
        // TEM QUE OLHAR ESSA FUNÇAO !!!!
        Analisa_atrib_chprocedimento(token, codigo_fonte, lista_erros);
    }
    else if (token.simbolo == "sse")
    {
        Analisa_se(token, codigo_fonte, lista_erros);
    }
    else if (token.simbolo == "senquanto")
    {
        Analisa_enquanto(token, codigo_fonte, lista_erros);
    }
    else if (token.simbolo == "sleia")
    {
        Analisa_leia(token, codigo_fonte, lista_erros);
    }
    else if (token.simbolo == "sescreva")
    {
        Analisa_escreva(token, codigo_fonte, lista_erros);
    }
    else
    {
        Analisa_comandos(token, codigo_fonte, lista_erros);
    }
}

void Analisa_comandos(Token &token, ifstream &codigo_fonte, string &lista_erros)
{
    if (token.simbolo == "sinicio")
    {
        token = analisadorLexical(codigo_fonte);

        Analisa_comando_simples(token, codigo_fonte, lista_erros);
    }
}

void AnalisaBloco(Token &token, ifstream &codigo_fonte, string &lista_erros)
{
    token = analisadorLexical(codigo_fonte);

    Analisa_et_variaveis(token, codigo_fonte, lista_erros);
    Analisa_subrotinas(token, codigo_fonte, lista_erros);
    Analisa_comandos(token, codigo_fonte, lista_erros);
}

void analisadorSintatico(Token inicio, ifstream &codigo_fonte)
{

    string lista_erros = "lista_erros.txt";
    Token token;

    if (inicio.simbolo == "sprograma")
    {

        token = analisadorLexical(codigo_fonte);

        if (token.simbolo == "sidentificador")
        {

            // COLOCAR O NOME DO PROGRAMA NA TABELA DE SIMBOLOS :D

            token = analisadorLexical(codigo_fonte);
            if (token.simbolo == "spontovirgula")
            {

                AnalisaBloco(token, codigo_fonte, lista_erros);

                if (token.simbolo == "sponto")
                {
                    cout << "COMPILAMOS PORR" << endl;
                }
                else
                {
                    // Erro de ponto final <programa>
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
