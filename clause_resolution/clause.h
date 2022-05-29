#pragma once
#include "literal.h"
#include "predicate.h"
#include <string>
#include <vector>

class ConjunctiveClause {
  /*******************
   * 合取式，由若干literal组成
   ******************/
public:
  // variable
  std::vector<Literal> m_vList;

  // func
  ConjunctiveClause() = default;
  ConjunctiveClause(const ConjunctiveClause &c);
  bool fromString(std::string &s, int &index);
  void print();
};
std::ostream &operator<<(std::ostream &cout, const ConjunctiveClause &c);
class DisjunctiveClause {
  /*********************
   * 析取式，由若干合取式组成
   **********************/
public:
  // variable
  std::vector<ConjunctiveClause> m_vList;

  // func
  DisjunctiveClause() = default;
  bool fromString(std::string &s, int &index);
  void print();
};
std::ostream &operator<<(std::ostream &cout, const DisjunctiveClause &d);
using DNF = DisjunctiveClause;
using CNF = ConjunctiveClause;
