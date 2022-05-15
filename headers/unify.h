#pragma once
#include"clause.h"
#include"knowlegebase.h"
#include<map>
bool fUnifyPred(Predicate &x, Predicate &y, std::map<std::string, std::string> &mapSub);
bool fUnifyLiteral(
    Literal &x, Literal &y,
    std::map<std::string, std::string> &mapSub);
bool fUnifyCNF(
    CNF &x, CNF &y,
    std::map<std::string, std::string> &mapSub);
bool fUnifyDNF(DNF &x, DNF &y, std::map<std::string, std::string> &mapSub);