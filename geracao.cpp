#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "geracao.hpp"

using namespace std;

// vou colocar aqui ta vendo

void limpar_arquivo() {
    ofstream arquivo("saida.obj", ios::trunc); // Abre o arquivo em modo truncado
}

// esta função checa se o arquivo existe
inline bool arquivo_existe () {
    ifstream f("saida.obj");
    return f.good();
}

void geraLDC(string val){
    ofstream arquivo("saida.obj", ios::app);
    arquivo << "    " << left << setw(8) << "LDC" << val << "\n";
    arquivo.close();
}

void geraLDV(int val){
    ofstream arquivo("saida.obj", ios::app);
    arquivo << "    " << left << setw(8) << "LDV" << val << "\n";
    arquivo.close();
}

void geraADD() {
    ofstream arquivo("saida.obj", ios::app);
    arquivo << "    " << "ADD" << "\n";
    arquivo.close();
}

void geraSUB() {
    ofstream arquivo("saida.obj", ios::app);
    arquivo << "    " << "SUB" << "\n";
    arquivo.close();
}

void geraMULT() {
    ofstream arquivo("saida.obj", ios::app);
    arquivo << "    " << "MULT" << "\n";
    arquivo.close();
}

void geraDIVI() {
    ofstream arquivo("saida.obj", ios::app);
    arquivo << "    " << "DIVI" << "\n";
    arquivo.close();
}

void geraINV() {
    ofstream arquivo("saida.obj", ios::app);
    arquivo << "    " << "INV" << "\n";
    arquivo.close();
}

void geraAND() {
    ofstream arquivo("saida.obj", ios::app);
    arquivo << "    " << "AND" << "\n";
    arquivo.close();
}

void geraOR() {
    ofstream arquivo("saida.obj", ios::app);
    arquivo << "    " << "OR" << "\n";
    arquivo.close();
}

void geraNEG() {
    ofstream arquivo("saida.obj", ios::app);
    arquivo << "    " << "NEG" << "\n";
    arquivo.close();
}

void geraCME() {
    ofstream arquivo("saida.obj", ios::app);
    arquivo << "    " << "CME" << "\n";
    arquivo.close();
}

void geraCMA() {
    ofstream arquivo("saida.obj", ios::app);
    arquivo << "    " << "CMA" << "\n";
    arquivo.close();
}

void geraCEQ() {
    ofstream arquivo("saida.obj", ios::app);
    arquivo << "    " << "CEQ" << "\n";
    arquivo.close();
}

void geraCDIF() {
    ofstream arquivo("saida.obj", ios::app);
    arquivo << "    " << "CDIF" << "\n";
    arquivo.close();
}

void geraCMEQ() {
    ofstream arquivo("saida.obj", ios::app);
    arquivo << "    " << "CMEQ" << "\n";
    arquivo.close();
}

void geraCMAQ() {
    ofstream arquivo("saida.obj", ios::app);
    arquivo << "    " << "CMAQ" << "\n";
    arquivo.close();
}

void geraSTR(int val){
    ofstream arquivo("saida.obj", ios::app);
    arquivo << "    " << left << setw(8) << "STR" << val << "\n";
    arquivo.close();
}

void geraJMP(int val){
    ofstream arquivo("saida.obj", ios::app);
    arquivo << "    " << left << setw(8) << "JMP" << val << "\n";
    arquivo.close();
}

void geraJMPF(int val){
    ofstream arquivo("saida.obj", ios::app);
    arquivo << "    " << left << setw(8) << "JMPF" << val << "\n";
    arquivo.close();
}

void geraNULL(int val) {
    ofstream arquivo("saida.obj", ios::app);
    arquivo << left << setw(4) << val << "NULL" << "\n";
    arquivo.close();
}

void geraRD() {
    ofstream arquivo("saida.obj", ios::app);
    arquivo << "    " << "RD" << "\n";
    arquivo.close();
}

void geraPRN() {
    ofstream arquivo("saida.obj", ios::app);
    arquivo << "    " << "PRN" << "\n";
    arquivo.close();
}

void geraSTART() {
    ofstream arquivo("saida.obj", ios::app);
    arquivo << "    " << "START" << "\n";
    arquivo.close();
}

void geraALLOC(int val, int val2){
    ofstream arquivo("saida.obj", ios::app);
    arquivo << "    " << left << setw(8) << "ALLOC" << val;
    arquivo << setw(4) << right << setw(4) << val2 << "\n";
    arquivo.close();
}

void geraDALLOC(int val, int val2){
    ofstream arquivo("saida.obj", ios::app);
    arquivo << "    " << left << setw(8) << "DALLOC" << val;
    arquivo << setw(4) << right << setw(4) << val2 << "\n";
    arquivo.close();
}

void geraHLT() {
    ofstream arquivo("saida.obj", ios::app);
    arquivo << "    " << "HLT" << "\n";
    arquivo.close();
}

void geraCALL(int val) {
    ofstream arquivo("saida.obj", ios::app);
    arquivo << "    " << left << setw(8) << "CALL" << val << "\n";
    arquivo.close();
}

void geraRETURN() {
    ofstream arquivo("saida.obj", ios::app);
    arquivo << "    " << "RETURN" << "\n";
    arquivo.close();
}