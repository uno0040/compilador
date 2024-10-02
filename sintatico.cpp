#include <iostream>
#include <fstream>
#include <string>
#include "tokens.hpp"
#include "lexical.hpp"
#include "erros.hpp"

using namespace std;

void Analisa_et_variaveis(Token token,ifstream& codigo_fonte, string& lista_erros){
    if (token.simbolo == "svar"){
        
    }
}

void Analisa_subrotinas(Token token,ifstream& codigo_fonte, string& lista_erros){
    
}

void Analisa_comandos(Token token,ifstream& codigo_fonte, string& lista_erros){
    
}

void AnalisaBloco(Token token,ifstream& codigo_fonte, string& lista_erros){
    token = analisadorLexical(codigo_fonte);

    Analisa_et_variaveis(token,codigo_fonte, lista_erros);
    Analisa_subrotinas(token,codigo_fonte, lista_erros);
    Analisa_comandos(token,codigo_fonte, lista_erros);
}


void analisadorSintatico(Token inicio,ifstream& codigo_fonte){

    string erroIdentificadorPrograma = "Espera-se um identificador Programa na linha: ";
    string erroIdentificadorPrograma = "Espera-se um identificador para o Programa na linha: ";
    string erroPontoeVirgula = "Espera-se uma pontuação do tipo ; ";
    string erroPontoFinal = "Espera-se uma pontuação do tipo . ";
    
    
    string lista_erros = "lista_erros.txt";
    Token token;

    if (inicio.simbolo == "sprograma"){
        
        token = analisadorLexical(codigo_fonte);

        if (token.simbolo == "sidentificador"){

            // COLOCAR O NOME DO PROGRAMA NA TABELA DE SIMBOLOS :D

            token = analisadorLexical(codigo_fonte);
            if (token.simbolo == "spontovirgula"){

                AnalisaBloco(token,codigo_fonte, lista_erros);

                if (token.simbolo == "sponto"){
                    cout<<"COMPILAMOS PORR"<< endl; 
                } else {
                    //Erro de ponto final <programa>
                    writeErrors(token.linha, codigo_fonte, lista_erros, erroPontoFinal);    
                }

            } else {
                // Erro de ponto-virgula <programa>
                writeErrors(token.linha, codigo_fonte, lista_erros, erroPontoeVirgula);    
            }
        } else {
            // Erro do identificador <programa>
            writeErrors(token.linha, codigo_fonte, lista_erros, erroIdentificadorPrograma);
        }

    } else {
        // Primeiro erro da regra Analisador sintatico <programa>
        writeErrors(token.linha, codigo_fonte, lista_erros, erroIdentificadorPrograma);

    }

}




