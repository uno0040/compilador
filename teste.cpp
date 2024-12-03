#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "tokens.hpp"
#include "lexical.hpp"
#include "sintatico.hpp"

using namespace std;

int main() {
    
    vector<int> t;
    t.push_back(1);
    t.push_back(2);
    cout << t.back() << endl;
    t.pop_back();
    cout << t.back() << endl;
    t.pop_back();
    return 0;
}