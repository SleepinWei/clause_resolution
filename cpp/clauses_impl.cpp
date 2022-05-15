#include "clause.h"
#include"knowlegebase.h"
#include"literal.h"
#include"predicate.h"

/*Predicate*/
Predicate::Predicate(std::string & name,std::vector<std::string> terms):
    m_sName(name),m_vTerms(terms){

}

Predicate::Predicate(Predicate& pred):
    m_sName(pred.m_sName),m_vTerms(pred.m_vTerms){

}

bool Predicate:: fromString(std::string & s,int& index){
    // find bracket
    int pos = index;
    for (pos = index; pos < s.length();pos++){
        if(s[pos] == '('){
            break;
        }
    }
    if(pos ==index)
        return false; // no predicate name

    this->m_sName = s.substr(index, pos);

    //find args
    int prev = pos+1;  // 记录上一个逗号的位置
    while(pos != s.length()){
        if (s[pos] == ',' || s[pos] == ')'){
            //args are seperated by ,
            if(pos == prev)
                return false; // 两个逗号之间没有参数
            std::string arg = s.substr(prev, pos - prev);
            this->m_vTerms.push_back(arg);
            prev = pos;  // update prev
        }
        if(s[pos] == ')'){
            index = pos + 1; 
            return true; // 完成构建
        }
        ++pos; 
    }
}


/*Literal*/
Literal::Literal(bool isNot,Predicate& Predicate):
    bNot(isNot),m_Predicate(Predicate){
}

bool Literal::fromString(std::string& s,int& index){
    if(s[0] == '~'){
        this->bNot = true;
        index += 1;
        this->m_Predicate.fromString(s,index);
    }else{
        this->bNot = false;
        this->m_Predicate.fromString(s, index);
    }
}

/*Clause*/ 
bool ConjunctiveClause::fromString(std::string& s, int & index){
    int pos = index; 
    while(true){
        Literal newLiteral;
        newLiteral.fromString(s, pos);
        m_vList.push_back(newLiteral);
        
        if (pos == s.length() || s[pos] =='|'){ //note: 因为literal的fromstring让index指向literal的下一个元素
            // 如果有 或 运算 or 到结尾，则结束
            index = pos+1;
            return true; 
        }else if(s[pos] == '& '){
            continue; // 如果有 与运算，则有下一个 literal. 
        }
    }
    return true; 
}

bool DisjunctiveClause::fromString(std::string& s,int & index){
    int pos = index; 
    while(true){
        ConjunctiveClause newCNF;
        newCNF.fromString(s, pos);
        m_vList.push_back(newCNF);
        
        if (pos >= s.length()){
            // 如果有 或 运算 or 到结尾，则结束
            index = pos+1;
            return true; 
        }else if(s[pos] == '|'){
            continue; // 如果有 与运算，则有下一个 literal. 
        }
    }
    
}

