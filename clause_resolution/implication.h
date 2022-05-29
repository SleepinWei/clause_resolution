#pragma once
#include "clause.h"
#include <string>

class Implication {
  // variables
public:
  CNF m_Condition;
  Literal m_Conclusion;

  // func
  Implication();
  Implication(const Implication &impl);
  void fromString(std::string &s, int &index);
  void print();
};

using Impl = Implication;
