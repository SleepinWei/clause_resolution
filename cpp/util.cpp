#include"predicate.h"
#include"literal.h"
#include"clause.h"
#include<iostream>

std::ostream& operator<< (std::ostream& out, Predicate const& p){
    out << p.m_sName << '(';
    for (int i = 0; i < p.m_vTerms.size();i++)
    {
        if(i!=0)
            out << ',';
        out << p.m_vTerms[i];
    }
    out << ")";
    return out;
}
std::ostream& operator << (std::ostream& out,const Literal& l){
    if(l.bNot){
        out<<"~";
    }
    out << l.m_Predicate;
    return out;
}
std::ostream& operator <<(std::ostream& out,const CNF& c){
    for (int i = 0; i < c.m_vList.size();i++){
        if(i!=0){
            out << "&";
        }
        out << c.m_vList[i];
    }
    return out;
}
std::ostream& operator<<(std::ostream& out,const DNF& d){
    for (int i = 0; i < d.m_vList.size();i++){
        if(i!=0){
            out << '|';
        }
        out << d.m_vList[i];
    }
    return out;
}