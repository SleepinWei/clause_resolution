#pragma once
#include<string>
#include<vector>

class Predicate{
    /**********************
     * 谓词结构，H(a),H(a,b)
     *********************/

public:
    // variable
    std::string m_sName;
    std::vector<std::string> m_vTerms; 

    // func
    Predicate()=default;
    Predicate(std::string & name, std::vector<std::string> terms);
    Predicate(Predicate &pred);
    bool fromString(std::string &s,int& index);
};

using Pred = Predicate;