/*
 * test.h
 *
 *  Created on: Apr 15, 2011
 *      Author: leden
 */

#ifndef TEST_H_
#define TEST_H_

#include <cstdlib>
#include <cassert>

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "../base.h"
#include "../logic/predicate/types.h"
#include "../logic/predicate/io_base.h"

#include "../logic/predicate/semantics.h"
#include "../logic/predicate/term_vector.h"
#include "../logic/predicate/formula_builder.h"
#include "../logic/predicate/syntax_checker.h"
#include "../logic/predicate/forall.h"
#include "../logic/predicate/exists.h"

using namespace logic::predicate;

namespace testing {

Element Concat(const Arguments& args) {
  int sum = args.Get(0).As<int>() + args.Get<int>(1);
  return "hello world: " + ToString(sum);
}

bool Equals(const Arguments& args) {
  return args.Get(0) == args.Get(1);
}

void TestArgs() {
  Arguments a(1, "2fafd", 3.6);
  Arguments b = a;
  std::cout << b << std::endl;
}

void TestFunction() {
  Function a("CONCAT");
  Interpretation s;
  s.Bind(a, Concat);
  std::cout << s.Evaluate(a, Arguments(1, 2)) << std::endl;
}

void TestArgumentsMap() {
  PredicateMapping m;
  m[Arguments(1, 2)] = false;
  m[Arguments(2, 3)] = true;


  assert(m[Arguments(1, 2)] == false);
  assert(m[Arguments(2, 3)] == true);
  m[Arguments(2, 3)] = false;
  assert(m[Arguments(2, 3)] == false);

  Predicate p("EQ");
  PredicateMap m2;
  m2[p][Arguments(4)] = true;
  m2[p][Arguments(2)] = false;
  assert(m2[p][Arguments(4)] == true);
  assert(m2[p][Arguments(2)] == false);
  assert(m2[p][Arguments(1, 2, 3, 4)] == false);
}

void TestVariable() {
  Variable var("a");
  Term* term = &var;

  if (Variable* p = dynamic_cast<Variable*>(term)) {
    std::cout << "Var: " << *p << std::endl;
  }
}

void TestCompositeFormula() {
  Predicate EQ("EQ");
  Function min("min"), max("max");
  Variable x("x"), y("y");
  Element e = 2;

  FunctionTerm func_min(min, x, y);
  std::cout << "func_min: " << func_min << std::endl;

  FunctionTerm func_max = max(e, func_min);
  std::cout << "func_max: " << func_max << std::endl;

  std::cout << *UnaryOperator::kNot << std::endl;

  using namespace builder;
  const Formula& f = EQ(min(Element(1), Element(2)));
  std::cout << "f = " << f << std::endl;
  Predicate NE("NE");
  const Formula& f2 = NE() & EQ(min(Element(1), Element(2)),
                         max(Element(1), Element(0)));
  std::cout << "f2 = " << f2 << std::endl;
}

void TestInterpretation() {
  VariableValues inter;
  Variable x("x");
  inter[x] = "foo";

  std::cout << inter[x] << std::endl;
}

void TestQuantifiedFormula() {

}

TermVector Create(const std::string& s0, const std::string& s1) {
  return TermVector(Element(s0), Element(s1));
}

void TestTermVector() {
  Element e("Ivan");
  TermVector v(e);
  std::cout << (v[0] == NULL ? "BUG" : "OK") << std::endl;
  std::cout << v << std::endl;
  std::cout << Create("Filip", "Marko") << std::endl;
}

int* p;

const int& CreateInt(int x) {
  return *(p = new int(x));
}

void TestRef() {
  const int& x = CreateInt(2);
  delete p;
  std::cout << "x = " << x << std::endl;
  std::cout << "p = " << *p << std::endl;
}

void AssertSyntax(const Formula& f, bool expected) {
  std::cerr << "Syntax check: " << f << std::endl;
//  bool actual = true;
//  try {
//    CheckSyntax(f);
//  } catch(const SyntaxErrorException& e) {
//    actual = false;
//  }
//  assert(expected == actual);
}

void TestSyntaxCheck() {
  using namespace builder;
  Predicate P("P"), Q("Q"), R("R");
  Variable x("x"), y("y"), z("z");
  AssertSyntax(A(x, P(x)), true);
  AssertSyntax(A(x, P(y)), true);
  AssertSyntax(E(x, A(x, P(y))), false);
  AssertSyntax(P(x) & P(y), true);
  AssertSyntax(A(x, P(y)) & E(x, P(Element(1))), true);
  AssertSyntax(A(x, E(y, P(y))) & E(x, A(y, P(Element(1)))), true);

  ForAllVariable Ax(x), Ay(y), Az(z);
  ExistsVariable Ex(x), Ey(y), Ez(z);
  AssertSyntax(Ax(P(x)), true);

  AssertSyntax(Ax(Ey(P(x) > Q(y))), true);
}

void TestSemantics01() {
  using namespace builder;
  Interpretation s;

  Variable w("w"), x("x"), y("y"), z("z");
  for (int i = 0; i < 4; ++i)
    s.domain().insert(i);

  ForAllVariable Ax(x), Ay(y), Az(z);
  ExistsVariable Ex(x), Ey(y), Ez(z);

  Predicate EQ("EQ");
  s.Bind(EQ, Equals);

  Predicate P("P");
  s.predicate_map()[P][Arguments(0)] = true;
  s.predicate_map()[P][Arguments(1)] = true;
  s.predicate_map()[P][Arguments(2)] = false;
  s.predicate_map()[P][Arguments(3)] = true;

  Predicate Q("Q");
  s.predicate_map()[Q][Arguments(1)] = true;

  Function concat("concat");

  const Formula& f = Ax(Q(x));
  std::cout << s;
  std::cout << "formula = " << f << std::endl;
  std::cout << s.Evaluate(f) << std::endl;
}

}  // namespace testing


void Test() {
  using namespace testing;

//  TestTermVector();
//  TestRef();
//  TestArgs();
//  TestFunction();
//  TestArgumentsMap();
//  TestVariable();
//  TestInterpretation();
  TestCompositeFormula();
  TestSyntaxCheck();
  TestSemantics01();
}

int main(int argc, char **argv) {
  Test();
  std::cerr << "Main exited normally\n";
  return 0;
}



#endif /* TEST_H_ */
