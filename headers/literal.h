#pragma once 
#include"predicate.h"

class Literal{
    /*********************
     * ~P 或者 P
     * ******************/
public:
    //variable
    bool bNot;  // negate
    Predicate m_Predicate; 

    //func
    Literal()= default;
    Literal(bool isNot, Predicate &predicate);
    bool fromString(std::string &s,int& index);
};