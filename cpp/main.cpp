// #include"info.h"
#include"unify.h"
#include"clause.h"
#include"predicate.h"
#include"literal.h" 
#include <iostream>
using namespace std;

int main() {
    // input();
    // transition();
    std::string s;
    std::cin >> s;
    DNF l; 
    int index = 0;
    l.fromString(s,index);
    l.print();
    cout << '\n';
    return 0;
}
