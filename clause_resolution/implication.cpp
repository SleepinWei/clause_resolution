#include "implication.h"

Implication::Implication() : m_Condition(CNF()), m_Conclusion(Literal()) {}

Implication::Implication(const Implication &impl)
    : m_Condition(impl.m_Condition), m_Conclusion(impl.m_Conclusion) {}

void Implication::fromString(std::string &s, int &index) {
  m_Condition.fromString(s, index);
  index += 1; // "->"
  m_Conclusion.fromString(s, index);
}

#include <iostream>
void Implication::print() {
  this->m_Condition.print();
  std::cout << "->";
  this->m_Conclusion.print();
}
