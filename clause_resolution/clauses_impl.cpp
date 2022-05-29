#include "clause.h"
#include "knowlegebase.h"
#include "literal.h"
#include "predicate.h"
#include <iostream>

/*Predicate*/
Predicate::Predicate(std::string &name, std::vector<std::string> terms)
    : m_sName(name), m_vTerms(terms) {}

Predicate::Predicate(const Predicate &pred)
    : m_sName(pred.m_sName), m_vTerms(pred.m_vTerms) {}

bool Predicate::fromString(std::string &s, int &index) {
  // find bracket
  int pos = index;
  for (pos = index; pos < s.length(); pos++) {
    if (s[pos] == '(') {
      break;
    }
  }
  if (pos == index)
    return false; // no predicate name

  this->m_sName = s.substr(index, pos - index);

  // find args
  int prev = pos + 1; // 记录上一个逗号的位置
  while (pos != s.length()) {
    if (s[pos] == ',' || s[pos] == ')') {
      // args are seperated by ,
      if (pos == prev)
        return false; // 两个逗号之间没有参数
      std::string arg = s.substr(prev, pos - prev);
      this->m_vTerms.push_back(arg);
      prev = pos + 1; // update prev
    }
    if (s[pos] == ')') {
      index = pos + 1;
      return true; // 完成构建
    }
    ++pos;
  }
  return true;
}
bool Predicate::operator==(const Predicate &p) {
  if (m_sName.compare(p.m_sName) != 0) {
    return false;
  }
  for (int i = 0; i < m_vTerms.size(); i++) {
    if (m_vTerms[i].compare(p.m_vTerms[i]) != 0) {
      return false;
    }
  }
  return true;
}

void Predicate::print() {
  std::cout << this->m_sName << '(';
  for (int i = 0; i < this->m_vTerms.size(); i++) {
    if (i != 0)
      std::cout << ',';
    std::cout << m_vTerms[i];
  }
  std::cout << ")";
}
/*Literal*/
Literal::Literal(bool isNot, Predicate &Predicate)
    : bNot(isNot), m_Predicate(Predicate) {}

bool Literal::fromString(std::string &s, int &index) {
  if (s[index] == '~') {
    this->bNot = true;
    index += 1;
    this->m_Predicate.fromString(s, index);
  } else {
    this->bNot = false;
    this->m_Predicate.fromString(s, index);
  }
  return true;
}
Literal ::Literal(const Literal &l)
    : bNot(l.bNot), m_Predicate(l.m_Predicate) {}
void Literal::print() {
  if (this->bNot) {
    std::cout << "~";
  }
  this->m_Predicate.print();
}
bool Literal::operator==(const Literal &l) {
  return bNot == l.bNot && m_Predicate == l.m_Predicate;
}

/*Clause*/
bool ConjunctiveClause::fromString(std::string &s, int &index) {
  int pos = index;
  while (true) {
    Literal newLiteral;
    newLiteral.fromString(s, pos);
    m_vList.push_back(newLiteral);

    if (pos >= s.length() || s[pos] == '|' ||
        s[pos] ==
            '-') { // note:
                   // 因为literal的fromstring让index指向literal的下一个元素
      // 如果有 或 运算 or 到结尾，则结束
      index = pos + 1;
      return true;
    } else if (s[pos] == '&') {
      pos += 1;
      continue; // 如果有 与运算，则有下一个 literal.
    }
  }
  return true;
}

ConjunctiveClause::ConjunctiveClause(const ConjunctiveClause &c)
    : m_vList(c.m_vList) {}
void ConjunctiveClause::print() {
  // std::cout << m_vList.size();
  for (int i = 0; i < m_vList.size(); i++) {
    if (i != 0) {
      std::cout << "&";
    }
    m_vList[i].print();
  }
}

bool DisjunctiveClause::fromString(std::string &s, int &index) {
  int pos = index;
  while (true) {
    ConjunctiveClause newCNF;
    newCNF.fromString(s, pos);
    m_vList.push_back(newCNF);

    if (pos >= s.length()) {
      // 如果有 或 运算 or 到结尾，则结束
      index = pos + 1;
      return true;
    } else if (s[pos] == '|') {
      pos += 1;
      continue; // 如果有 与运算，则有下一个 literal.
    }
  }
}

void DisjunctiveClause::print() {
  for (int i = 0; i < m_vList.size(); i++) {
    if (i != 0) {
      std::cout << '|';
    }
    m_vList[i].print();
  }
}
