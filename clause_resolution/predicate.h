#pragma once
#include <string>
#include <vector>

class Predicate {
  /**********************
   * 谓词结构，H(a),H(a,b)
   *********************/

public:
  // variable
  std::string m_sName;
  std::vector<std::string> m_vTerms;

  // func
  Predicate() = default;
  Predicate(std::string &name, std::vector<std::string> terms);
  Predicate(const Predicate &pred);
  bool fromString(std::string &s, int &index);
  bool operator==(const Predicate &p);

  // friend std::ostream &operator<<(std::ostream &cout, const Predicate &p);
  void print();
};
std::ostream &operator<<(std::ostream &cout, Predicate const &p);

using Pred = Predicate;
