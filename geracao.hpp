#ifndef GERACAO_HPP
#define GERACAO_HPP

#include <string>
#include <vector>
#include <fstream>
#include "sintatico.hpp"

using namespace std;

void limpar_arquivo();
inline bool arquivo_existe();
void geraLDC(string val);
void geraLDV(int val);
void geraADD();
void geraSUB();
void geraMULT();
void geraDIVI();
void geraINV();
void geraAND();
void geraOR();
void geraNEG();
void geraCME();
void geraCMA();
void geraCEQ();
void geraCDIF();
void geraCMEQ();
void geraCMAQ();
void geraSTR(int val);
void geraJMP(int val);
void geraJMPF(int val);
void geraNULL(int val);
void geraRD();
void geraPRN();
void geraSTART();
void geraALLOC(int val, int val2);
void geraDALLOC(int val, int val2);
void geraHLT();
void geraCALL(int val);
void geraRETURN();

#endif