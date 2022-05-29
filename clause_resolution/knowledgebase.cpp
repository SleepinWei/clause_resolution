#include "knowledgebase.h"
#include "unify.h"
#include <iostream>
#include <map>
#include <queue>
#include <unordered_map>
#include <vector>

KnowledgeBase::KnowledgeBase()
    : m_vList(std::vector<Impl>()), m_Fact(std::vector<Literal>()) {}
/************************************
 * fSatisfyPremise
 * @ param: premises, 合取范式的各个前提
 * @ param: facts, KB中的事实，即非推断式 e.g. H(a,b,c)
 * @ param: sub: 前提被成功推理后的置换
 * @ param: record: 记录当前蕴涵式被哪些facts证明
 * *********************************/
bool fSatisfyPremise(std::vector<Literal> &premises,
                     std::vector<Literal> &facts,
                     std::map<std::string, std::string> &sub,
                     std::vector<int> &record) {
  std::map<std::string, std::string> newSub;
  for (int i = 0; i < premises.size(); i++) {
    int flag = false;
    for (int j = 0; j < facts.size(); j++) {
      if (fUnifyLiteral(premises[i], facts[j], newSub)) {
        // 如果两个表达式成功合一
        record.push_back(j);
        flag = true;
        break;
      }
    }
    if (flag == false) {
      // not found
      return false;
    }
  }
  sub.insert(newSub.begin(), newSub.end());
  return true;
}
/*****************************
 * fSubst: 使用 sub 置换 fact 中的变量
 * return: 替换后的 Literal 值
 * **************************/
Literal fSubst(Literal &fact, std::map<std::string, std::string> sub) {
  Literal result(fact);
  std::vector<std::string> &args = fact.m_Predicate.m_vTerms;

  auto iter = sub.begin();
  for (int i = 0; i < args.size(); i++) {
    // 为 i-th 参数找代替
    if (args[i][0] == 'x') {
      auto pos = sub.find(args[i]);
      if (pos != sub.end()) {
        result.m_Predicate.m_vTerms[i] = pos->second; // 进行替换
      } else {
        std::cout << "fSubst error: can't find a substitute for " << args[i]
                  << '\n';
      }
    }
  }
  return result;
}

/****************************************
 * printInfo
 * 打印 归结 时的中间信息
 * **************************************/
void printInfo(std::ostream &cout, int implIndex, std::vector<int> record) {
  cout << "Impl" << implIndex;
  for (auto e : record) {
    cout << "&F" << e;
  }
  cout << "\n";
}

/****************************
 * ask
 * 前向连接函数，根据 query 的值在 KB 中查询是否满足。
 * **************************/
bool KnowledgeBase::ask(Literal &query) {
  while (true) {
    std::vector<Literal> newKnowledge;
    for (int i = 0; i < this->m_vList.size(); i++) {
      Implication &impl = m_vList[i];
      std::vector<Literal> &premises = impl.m_Condition.m_vList;
      Literal &conclusion = impl.m_Conclusion;

      std::map<std::string, std::string> sub;
      std::vector<int> record;
      int successful = fSatisfyPremise(premises, m_Fact, sub, record);
      if (successful) {
        // 如果成功归约，则
        Literal newFact = fSubst(conclusion, sub);
        // 输出提示信息
        printInfo(std::cout, i, record);

        if (true) // TODO: newfact does not unify with some sentence in KB or
                  // newKB
        {
          newKnowledge.push_back(newFact);
          std::map<std::string, std::string> tempSub;
          if (fUnifyLiteral(newFact, query, tempSub)) {
            std::cout << "Successful Resolution" << '\n';
            return true;
          }
        }
      }
    }
    this->m_Fact.insert(m_Fact.end(), newKnowledge.begin(), newKnowledge.end());
    if (newKnowledge.empty()) {
      break;
    }
  }
  return false;
}

/*****************************
 * addFromString
 * 通过字符串添加 fact 或者 impl. 根据是否存在 "->" 判断是 fact 还是 impl
 * **************************/
bool KnowledgeBase::addFromString(std::string &s) {
  int index = 0;
  int isImpl = false;
  for (int i = s.length() - 1; i >= 0; i--) {
    if (s[i] == '-') {
      isImpl = true;
      break;
    }
  }
  if (isImpl) {
    Impl newImpl;
    newImpl.fromString(s, index);
    this->m_vList.push_back(newImpl);
  } else {
    Literal newLiteral;
    newLiteral.fromString(s, index);
    this->m_Fact.push_back(newLiteral);
  }
  return true;
}

/******************************
 * print()
 * 打印 KB 中的所有 Fact 和 Implication
 * ***************************/
void KnowledgeBase::print() {
  std::cout << "Implicaton:\n";
  for (int i = 0; i < this->m_vList.size(); i++) {
    std::cout << i << " : ";
    this->m_vList[i].print();
    std::cout << '\n';
  }
  std::cout << "\nFact:\n";
  for (int i = 0; i < this->m_Fact.size(); i++) {
    std::cout << i << " : ";
    this->m_Fact[i].print();
    std::cout << '\n';
  }
}

/*******************************
 * resize count vector
 * ****************************/
// void KnowledgeBase:: updateCount(){
//     int size = this->m_vList.size();
//     count.resize(size);
//     for (int i = 0; i < size;i++){
//         count[i] = m_vList[i].m_Condition.m_vList.size();
//     }
// }
/********************************
 * entails
 * 命题逻辑的前向连接算法
 * ******************************/
bool KnowledgeBase::entails(Literal &query) {
  int size = this->m_vList.size();
  std::vector<int> count(size);
  for (int i = 0; i < size; i++) {
    count[i] = m_vList[i].m_Condition.m_vList.size();
  }
  std::queue<int> agenda;
  for (int i = 0; i < m_Fact.size(); i++) {
    agenda.push(i);
  }
  std::vector<int> inferred(m_Fact.size(), false);

  while (agenda.size()) {
    int index = agenda.front();
    agenda.pop();
    if (m_Fact[index] == query) {
      return true;
    }
    if (inferred[index] == false) {
      inferred[index] = true;
      for (int i = 0; i < m_vList.size(); i++) {
        Impl &impl = m_vList[i];
        int flag = false;
        for (int j = 0; j < impl.m_Condition.m_vList.size(); j++) {
          if (impl.m_Condition.m_vList[j] == m_Fact[index]) {
            --count[i];
            std::ostringstream oss;
            if (count[i] == 0) {
              m_Fact.push_back(impl.m_Conclusion);
              inferred.push_back(false);
              agenda.push(m_Fact.size() - 1);

              /******print******/
              std::cout << "Fact" << index << " + Impl" << i << " =>";
              impl.m_Conclusion.print();
              std::cout << '\n';

              oss << "Fact" << index << " + Impl" << i << " => "
                  << impl.m_Conclusion;
            } else {
              /******print******/
              std::cout << "Fact" << index << " + Impl" << i << '\n';

              oss << "Fact" << index << " + Impl" << i;
            }
            process.push_back(oss.str());
            flag = true;
            break;
          }
        }
      }
    }
  }
  return false;
}

std::vector<std::string> KnowledgeBase::getImplications() const {
  std::vector<std::string> implVec;
  for (const auto &l : m_vList) {
    std::ostringstream ss;
    ss << l;
    implVec.push_back(ss.str());
  }
  return implVec;
}

std::vector<std::string> KnowledgeBase::getFacts() const {
  std::vector<std::string> factVec;
  for (const auto &l : m_Fact) {
    std::ostringstream ss;
    ss << l;
    factVec.push_back(ss.str());
  }
  return factVec;
}

std::vector<std::string> KnowledgeBase::getProcess() const { return process; }
