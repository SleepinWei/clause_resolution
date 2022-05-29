#pragma once
#include "implication.h"
#include "util.h"
#include <sstream>
#include <string>
#include <vector>

class KnowledgeBase {
  // KB
  // variable
public:
  std::vector<Impl> m_vList;
  std::vector<Literal> m_Fact;
  std::vector<std::string> process;
  // std::vector<int> count;

  // function
  KnowledgeBase();
  bool ask(Literal &query);
  bool entails(Literal &query);
  bool addFromString(std::string &s);
  // void updateCount();
  void print();

  std::vector<std::string> getImplications() const;
  std::vector<std::string> getFacts() const;
  std::vector<std::string> getProcess() const;
};
using KB = KnowledgeBase;
