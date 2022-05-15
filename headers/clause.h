#pragma once
#include<vector>
#include<string> 
#include"predicate.h"
#include"literal.h"

class ConjunctiveClause{
    /*******************
     * 合取式，由若干literal组成
     ******************/
public:
    //variable
    std::vector<Literal> m_vList; 

    //func
};
class DisjunctiveClause{
    /*********************
    * 析取式，由若干合取式组成
    **********************/
public:
    //variable
    std::vector<ConjunctiveClause> m_vList;

    //func 
};
using DNF = DisjunctiveClause; 
using CNF = ConjunctiveClause;