#include"unify.h"

/*****************************
* unify Predicate
* @ param: sub: substitution
*****************************/
bool fUnifyPred(Predicate& x, Predicate& y,std::map<std::string,std::string>& mapSub){
    if(x.m_sName.compare(y.m_sName)!=0)
        return false; 
    // 比较 args, 有顺序
    if(x.m_vTerms.size() != y.m_vTerms.size()){
        return false; 
    }
    std::map<std::string, std::string> newSub; 

    int flag = false; 
    for (int i = 0;i<x.m_vTerms.size();i++){
        std::string& argx = x.m_vTerms[i];
        std::string& argy = y.m_vTerms[i];
        if(argx.compare(argy) == 0)
            continue;
        else if(argx[0] == 'x' && argy[0] == 'x'){
            // all variables 
        }
        else if (argx[0] == 'x' || argy[0] == 'x'){
            // 如果是变量 x,y 中只有一个是 variable
            auto query = mapSub.find(argx);
            auto newquery = newSub.find(argx);
            if(query == mapSub.end() && newquery == newSub.end()){
                // if not found
                newSub.insert({argx, argy}); // add to map 
            } else if (query != mapSub.end()){
                //if already found in mapSub 
                if(argy.compare(mapSub[argx])!=0){
                    // 如果置换不是当前y中的参数
                    return false; 
                }
            } else if (newquery != newSub.end()){
                if(argy.compare(newSub[argx])!= 0){
                    return false; 
                }
            }
        }else {
            // 两个不相同的常量
            return false; 
        }
    }
    //successfully end
    // merge sub with new sub
    mapSub.insert(newSub.begin(), newSub.end());
    return true;
}

bool fUnifyLiteral(
    Literal & x, Literal& y,
    std::map<std::string,std::string> & mapSub
){
    if(x.bNot != y.bNot){
        return false;
    }
    return fUnifyPred(x.m_Predicate, y.m_Predicate,mapSub);
}

bool fUnifyCNF(
    CNF& x, CNF& y,
    std::map<std::string,std::string>& mapSub){
    int ixLen = x.m_vList.size();
    int iyLen = y.m_vList.size(); 
    if(ixLen!=iyLen)
        return false;
    std::vector<int> isUnifiedy(iyLen, 0);
    for (int i = 0; i < ixLen;i++){
        int flag = false; // 指示 x[i] 是否找到 y 中对应的 CNF
        for (int j = 0; j < iyLen;j++){
            if(!isUnifiedy[j] && fUnifyLiteral(x.m_vList[i],y.m_vList[j],mapSub)){
                // if two CNFs are successfully unified.
                flag = true;
                // isUnifiedx[i] = 1;
                isUnifiedy[j] = 1; 
                break; // next item in x 
            }
        }
        if(!flag){
            return false;  //failure
        }
    }
    return true; 
}
/*****************************
* unify DNF clauses 
* @ param: sub: substitution
* @ return: 是否合一成功
*****************************/
bool fUnifyDNF(DNF& x, DNF& y, std::map<std::string,std::string>& mapSub){
    int ixLen = x.m_vList.size();
    int iyLen = y.m_vList.size();
    if(ixLen != iyLen)
        return false;
    // std::vector<int> isUnifiedx(ixLen, 0);
    std::vector<int> isUnifiedy(iyLen, 0);
    for (int i = 0; i < ixLen;i++){
        int flag = false; // 指示 x[i] 是否找到 y 中对应的 CNF
        for (int j = 0; j < iyLen;j++){
            if(!isUnifiedy[j] && fUnifyCNF(x.m_vList[i],y.m_vList[j],mapSub)){
                // if two CNFs are successfully unified.
                flag = true;
                // isUnifiedx[i] = 1;
                isUnifiedy[j] = 1; 
                break; // next item in x 
            }
        }
        if(!flag){
            return false;  //failure
        }
    }
    return true;
}