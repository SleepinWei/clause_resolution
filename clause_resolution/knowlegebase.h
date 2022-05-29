#pragma once
#include "implication.h"
#include <string>
#include <vector>

class KnowledgeBase {
  // KB
  // variable
public:
  std::vector<Impl> m_vList;
  std::vector<Literal> m_Fact;
  // std::vector<int> count;

  // function
  KnowledgeBase();
  bool ask(Literal &query);
  bool entails(Literal &query);
  bool addFromString(std::string &s);
  // void updateCount();
  void print();
};
using KB = KnowledgeBase;
