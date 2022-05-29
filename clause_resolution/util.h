#include "implication.h"
#include <map>
#include <sstream>
#include <string>

void printMap(std::map<std::string, std::string> &map);
std::ostream &operator<<(std::ostream &out, Predicate const &p);
std::ostream &operator<<(std::ostream &out, const Literal &l);
std::ostream &operator<<(std::ostream &out, const CNF &c);
std::ostream &operator<<(std::ostream &out, const DNF &d);
std::ostream &operator<<(std::ostream &out, const Implication &i);
