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
    Literal();
    Literal(bool isNot, Predicate &predicate);
};