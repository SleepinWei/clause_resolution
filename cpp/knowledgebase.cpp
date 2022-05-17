#include"knowlegebase.h"
#include"unify.h"
#include<vector> 
#include<map>
#include<iostream>

KnowledgeBase::KnowledgeBase():
    m_vList(std::vector<Impl>()),m_Fact(std::vector<Literal>()){

}
bool fSatisfyPremise(std::vector<Literal>& premises,std::vector<Literal>& facts, 
    std::map<std::string,std::string>& sub)
{
    std::map<std::string, std::string> newSub;
    for (int i = 0; i < premises.size();i++){
        int flag = false; 
        for (int j = 0; j < facts.size();j++){
            if(fUnifyLiteral(premises[i],facts[j],newSub)){
                // 如果两个表达式成功合一
                flag = true;
                break; 
            }
        }
        if(flag == false){
            // not found
            return false; 
        }
    }
    sub.insert(newSub.begin(), newSub.end());
    return true; 
}
/*****************************
 * fSubst: 使用 sub 置换 fact 中的变量
 * **************************/
Literal fSubst(Literal& fact, std::map<std::string,std::string> sub){
    Literal result(fact);
    std::vector<std::string> &args = fact.m_Predicate.m_vTerms;

    auto iter = sub.begin();
    for (int i = 0; i < args.size();i++){
        // 为 i-th 参数找代替
        if(args[i][0]=='x'){
            auto pos = sub.find(args[i]);
            if(pos != sub.end()){
                result.m_Predicate.m_vTerms[i] = pos->second; // 进行替换
            }else{
                std::cout << "fSubst error: can't find a substitute for " << args[i] << '\n';
            }
        }
    }
    return result;
}

bool KnowledgeBase::ask(Literal& query){
    while(true){
        std::vector<Literal> newKnowledge; 
        for (int i = 0; i < this->m_vList.size();i++){
            Implication& impl = m_vList[i];
            std::vector<Literal>& premises = impl.m_Condition.m_vList;
            Literal &conclusion = impl.m_Conclusion;

            std::map<std::string, std::string> sub;
            int successful = fSatisfyPremise(premises, m_Fact, sub);
            if(successful){
                // 如果成功归约，则
                Literal newFact = fSubst(conclusion, sub);
                // 输出提示信息
                std::cout << "Knowledge " << i << " is resolved." << '\n';
                if(true)//TODO: newfact does not unify with some sentence in KB or newKB
                {
                    newKnowledge.push_back(newFact);
                    std::map<std::string, std::string> tempSub; 
                    if(fUnifyLiteral(newFact,query,tempSub)){
                        std::cout << "Successful Resolution" << '\n';
                        return true; 
                    }
                }
            }
        }
        this->m_Fact.insert(m_Fact.end(), newKnowledge.begin(), newKnowledge.end());
        if (newKnowledge.empty())
        {
            break;
        }
    }
    return false; 
}

bool KnowledgeBase::addFromString(std::string& s){
    int index = 0;
    int isImpl = false;
    for (int i = s.length() - 1; i >= 0; i--)
    {
        if(s[i] == '-'){
            isImpl = true;
            break;
        }
    }
    if(isImpl){
        Impl newImpl;
        newImpl.fromString(s, index);
        this->m_vList.push_back(newImpl);
    }else{
        Literal newLiteral;
        newLiteral.fromString(s, index);
        this->m_Fact.push_back(newLiteral);
    }
    return true;
}

void KnowledgeBase::print(){
    std::cout << "Implicaton:\n";
    for (int i = 0; i < this->m_vList.size();i++){
        std::cout << i << " : ";
        this->m_vList[i].print();
        std::cout << '\n';
    }
    std::cout << "\nFact:\n";
    for (int i = 0; i < this->m_Fact.size();i++){
        std::cout << i << " : ";
        this->m_Fact[i].print();
        std::cout << '\n';
    }
}