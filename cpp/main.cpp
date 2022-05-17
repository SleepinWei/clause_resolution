// #include"info.h"
#include"unify.h"
#include"clause.h"
#include"predicate.h"
#include"literal.h" 
#include"implication.h"
#include "util.h"
#include<iostream>
using namespace std;

int main() {
    // input();
    // transition();
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    std::string x;
    KB base; 
    while(true){
        cin >> x;
        if(x == "#")
            break;
        base.addFromString(x);
    }
    base.print();

    Literal l;
    string query;
    cin >> query;
    int index = 0;
    l.fromString(query, index);
    base.ask(l);
    return 0;
}
