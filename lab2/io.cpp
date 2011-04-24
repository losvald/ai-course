/*
 * io.cpp
 *
 *  Created on: Apr 24, 2011
 *      Author: leden
 */

#include <cassert>
#include <cctype>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "io.h"
#include "logic/predicate/types.h"
#include "logic/predicate/formula_builder.h"

namespace logic {

namespace predicate {

namespace parser {

bool IsVariable(const std::string& s) {
  return s.size() == 1 && islower(s[0]);
}

bool IsConstant(const std::string& s) {
  return s.size() >= 2 && *s.begin() == '"' && *--s.end() == '"';
}

bool IsPredicate(const std::string& s) {
  for (std::size_t i = 0; i < s.size(); ++i)
    if (!isupper(s[i]))
      return false;
  return true;
}

bool IsFunction(const std::string& s) {
  return !IsVariable(s) && !IsConstant(s) && !IsPredicate(s);
}

bool ToBool(const std::string& s) {
  return !(s.empty() || s == "0" || s == "f" || s == "false" || s == " ");
}

Element ParseElement(std::istream& is) {
  std::string s; is >> s;
  return Element(s.substr(1, (int)s.size() - 2));
}

Element ParseElement(const std::string& s) {
  std::istringstream ss(s);
  return ParseElement(ss);
}

Term& ParseTerm(std::istream& is);

TermVector ParseTermVector(std::istream& is) {
  Term& term = ParseTerm(is);
  std::string s; is >> s;
  if (s == ")") return TermVector(term);
  if (s == ",") return TermVector(term, ParseTermVector(is));
  assert(false);
}

Term& ParseTerm(std::istream& is) {
  std::string s; is >> s;
  if (IsConstant(s)) return *ParseElement(s).Clone();
  if (IsVariable(s)) return *Variable(s).Clone();
  std::string left_parenthesis; is >> left_parenthesis;
  TermVector function_arguments = ParseTermVector(is);
  return *Function(s)(function_arguments).Clone();
}

Formula& ParseFormula(std::istream& is) {
  using namespace builder;
  std::string t0; is >> t0;
  if (t0 == "~")
    return ~ParseFormula(is);
  if (t0 == "A" || t0 == "E") {
    std::string q_var; is >> q_var;
    return t0 == "A" ? A(q_var, ParseFormula(is)) : E(q_var, ParseFormula(is));
  }
  if (t0 == "(") {
    Formula& lhs = ParseFormula(is);
    std::string op; assert(is >> op);

    if (op == ")") return lhs;

    const Formula& rhs = ParseFormula(is);
    std::string right_parenthesis; assert(is >> right_parenthesis);
    if (op == "&") return lhs & rhs;
    else if (op == "|") return lhs | rhs;
    else if (op == "->" || op == ">") return lhs > rhs;
    else if (op == "<-" || op == "<") return lhs < rhs;
    else if (op == "<->" || op == "==") return lhs == rhs;
    assert(false);
  }
  std::string left_parenthesis; is >> left_parenthesis;
  TermVector predicate_arguments = ParseTermVector(is);
  return *Predicate(t0)(predicate_arguments).Clone();
}

} // namespace parser

bool PrintAndEval(const Interpretation& inter, const Formula& f) {
  try {
    bool ret = inter.Evaluate(f);
    std::cout << f << " == " << ret << std::endl;
    return ret;
  } catch (const UninterpretableException& e) {
    std::cout << f << " == " << "(uninterpretable)" << std::endl;
    throw e;
  }
}

Arguments ToArguments(const TermVector& term_vector) {
  std::vector<Element> args;
  for (TermVector::const_iterator it = term_vector.begin(),
      end = term_vector.end(); it != end; ++it)
    args.push_back(Element(*static_cast<Element*>(*it)));
  return Arguments(args);
}

bool ShouldSkipLine(const std::string& line) {
  for (std::size_t i = 0; i < line.size(); ++i)
    if (!isspace(line[i]))
      return false;
  return true;
}

void ProcessQueries(std::istream& is, Interpretation* inter) {
  using namespace parser;
  while (is) {
    std::cout << "Enter a command:" << std::endl;
    static char buf[1024];
    is.getline(buf, sizeof(buf));
    std::istringstream ss(buf + 1);
    if (ShouldSkipLine(buf)) continue;
    if (buf[0] == '?') {
      try { PrintAndEval(*inter, ParseFormula(ss)); }
      catch (const UninterpretableException& ignorable) {}
      catch (const IncompleteFunctionException& ignorable) {}
      catch (const IncompletePredicateException& ignorable) {}
    } else {
      if (buf[0] == '(') {
        Arguments args = ToArguments(ParseTermVector(ss));
        for (std::size_t i = 0; i < args.Count(); ++i)
          inter->domain().insert(args[i]);
      } else if (buf[0] == '+')
        inter->domain().insert(ParseTerm(ss));
      else if (buf[0] == '-')
        inter->domain().erase(ParseTerm(ss));
      else if (buf[0] == '#') {
        std::string name; ss >> name;
        std::string left_parenthesis; ss >> left_parenthesis;
        Arguments args = ToArguments(ParseTermVector(ss));
        std::string value; ss >> value;
        if (IsFunction(name))
          inter->function_map()[Function(name)][args] = ParseElement(value);
        else
          inter->predicate_map()[Predicate(name)][args] = ToBool(value);
      } else {
        std::cout << "Ignored invalid query: " << buf << std::endl;
        continue;
      }
      std::cout << *inter << std::endl;
    }
  }
}

void ProcessQueries(const std::string& filename, Interpretation* inter) {
  std::ifstream in; in.open(filename.c_str());
  ProcessQueries(in, inter);
  in.close();
}

}  // namespace predicate

}  // namespace logic
