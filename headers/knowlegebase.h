#pragma once
#include<vector>
#include<string>
#include"implication.h"

class KnowledgeBase{
    // KB
    //variable
public:
    std::vector<Impl> m_vList;
    std::vector<Literal> m_Fact; 

    //function
    KnowledgeBase();
    bool ask(Literal &query);
    bool addFromString(std::string &s);
    void print();
};
using KB = KnowledgeBase;