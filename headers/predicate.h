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
    Predicate();
    Predicate(std::string & name, std::vector<std::string> terms);
    Predicate(Predicate &pred);
    void fromString(std::string &s);
};

using Pred = Predicate;