/*
 * main.cpp
 *
 *  Created on: Apr 15, 2011
 *      Author: leden
 */

//#define TEST
#ifdef TEST
#include "test/test.h"
#else

#define FOREACH(it, c) for (__typeof((c).begin()) it = (c).begin(), \
    _end = (c).end(); it != _end; ++it)

#include <cassert>
#include <ctime>
#include <iostream>

#include "io.h"
#include "logic/predicate/formula_builder.h"
#include "logic/predicate/types.h"

using namespace logic::predicate;
using namespace logic::predicate::builder;

namespace example1 {

const int kDomainMin = 0, kDomainMax = 9;

bool Odd(const Arguments& args) {
  return args[0].As<int>() % 2 != 0;
}

bool Positive(const Arguments& args) {
  return args[0].As<int>() > 0;
}

Element ModuloMinusOne(const Arguments& args) {
  int x = args[0].As<int>();
  return x > kDomainMin ? x - 1 : kDomainMax;
}

void Show() {
  Interpretation inter;

  // define domain of integers from range [kDomainMin, kDomainMax]
  for (int i = kDomainMin; i <= kDomainMax; ++i)
    inter.domain().insert(i);

  // define a predicate which test if an integer is odd
  Predicate ODD("ODD");
  inter.Bind(ODD, Odd);

  // define a predicate which test if an integer is postive
  Predicate POSITIVE("POSITIVE");
  inter.Bind(POSITIVE, Positive);

  // define a predicate by specifying truth table
  Predicate ZERO("ZERO");
  for (Domain::const_iterator e = inter.domain().begin(), end = inter.domain().end();
      e != end; ++e) {
    inter.predicate_map()[ZERO][Arguments(*e)] = false;
  }
  inter.predicate_map()[ZERO][Element(0)] = true;

  // define a function: f(x) = x - 1
  Function minus_one("minus_one"); inter.Bind(minus_one, ModuloMinusOne);

  std::cout << inter;

  Variable x("x");
  ForAllVariable Ax(x);

  assert(PrintAndEval(inter, Ax(ODD(x) > ~ODD(minus_one(x))) ) == true);

  assert(PrintAndEval(inter, Ax((~ODD(x) & POSITIVE(x)) > ~ZERO(x) ) ) == true);

  assert(PrintAndEval(inter, ODD(Element(1)) & POSITIVE(Element(3)) ) == true);

  assert(PrintAndEval(inter, POSITIVE(Element(0)) > Ax(ODD(x) & ~ODD(x)) ) == true);

  try {
    PrintAndEval(inter, ODD(x) );
    assert(false);
  } catch (const UninterpretableException& e) {
  }
}

} // namespace example1

namespace example2 {

static const int kMaxPalindromeLength = 30;

Element CharAt(const Arguments& args) {
  return std::string(1, args[0].string()[args[1].As<int>()]);
}

Element ReverseIndex(const Arguments& args) {
  return (int)args[1].string().size() - args[0].As<int>() - 1;
}

Element Length(const Arguments& args) {
  return (int)args[0].string().size();
}

bool IsIndex(const Arguments& args) {
  const std::string& s = args[0].string();
  for (std::size_t i = 0; i < s.size(); ++i)
    if (!isdigit(s[i]))
      return false;
  return true;
}

bool Equal(const Arguments& args) {
  return args[0] == args[1];
}

bool Greater(const Arguments& args) {
  return args[0].As<int>() > args[1].As<int>();
}

void Show() {
  Interpretation inter;
  for (char c = 'a'; c <= 'z'; ++c)
    inter.domain().insert(std::string(1, c));
  for (int i = 0; i <= kMaxPalindromeLength; ++i)
    inter.domain().insert(i);
  inter.domain().insert("neven");
  inter.domain().insert("anavolimilovana");

  Function char_at("char_at"); inter.Bind(char_at, CharAt);
  Function rindex("rindex"); inter.Bind(rindex, ReverseIndex);
  Function len("len"); inter.Bind(len, Length);

  Predicate IS_INDEX("IS_INDEX"); inter.Bind(IS_INDEX, IsIndex);
  Predicate EQ("EQ"); inter.Bind(EQ, Equal);
  Predicate GT("GT"); inter.Bind(GT, Greater);

  Variable i("i"), s("s");
  ForAllVariable Ai(i), As(s);
  ExistsVariable Ei(i);

  // for each string there exists a number equal to its size
  assert(PrintAndEval(inter, As(~IS_INDEX(s) > Ei(IS_INDEX(i) & EQ(i, len(s))) ) ) ==
      true);

  for (int itr = 0; itr < 2; ++itr) {
    std::cout << inter;
    // is_palin(x) <=> x[i] == x[len(x) - i - 1]
    // for each i such that i <= len(x) - i - 1
    assert(PrintAndEval(inter,
                        As(Ai((~IS_INDEX(s) & IS_INDEX(i)) >
                              (GT(i, rindex(i, s)) | EQ(char_at(s, i),
                                                        char_at(s, rindex(i, s))))
                        ))
    ) == !itr); // itr == 0 -> true; itr == 1 -> false

    inter.domain().insert("zed"); // insert non-palindrome for second iteration
  }
}

}  // namespace example2

namespace example3 {

void Show() {
  Interpretation inter;

  // partially define interpretation

  inter.domain().insert("c");

  Function f("ff");
  inter.function_map()[f][Arguments("a")] = "a";
  inter.function_map()[f][Arguments("b")] = "c";

  Predicate P("P");
  inter.predicate_map()[P][Arguments("a", "a")] = false;

  Predicate Q("Q");
  inter.predicate_map()[Q][Arguments("a", "b")] = false;
  inter.predicate_map()[Q][Arguments("c", "b")] = false;

  // add missing information from the file
  ProcessQueries("test-data/2-7.in.part0", &inter);

  Element a("a"), b("b");
  Variable x("x"), y("y"), z("z");
  ForAllVariable Ax(x), Ay(y), Az(z);
  ExistsVariable Ex(x), Ey(y), Ez(z);

  try { PrintAndEval(inter, Ax(Ay( P(x, y) | P(y, x) )) ); }
  catch (const UninterpretableException& ignorable) {}

  try { PrintAndEval(inter, ~Ay(Ex( Q(x, f(y)) )) ); }
  catch (const UninterpretableException& ignorable) {}

  // evaluate additional formulas from another file
  ProcessQueries("test-data/2-7.in.part1", &inter);
}

}  // namespace example3

namespace example4 {

void Show() {
  Interpretation inter;
  ProcessQueries("test-data/2-6.in", &inter);
}

}  // namespace example4

void ShowExample(void (*show_func_ptr)(), const std::string& name) {
  using namespace std;
  cout << "Running " << name << " ... " << endl;
  time_t start_time = clock();
  (*show_func_ptr)();
  double elapsed_time = 1000. * (clock() - start_time) / CLOCKS_PER_SEC;
  cout << "Exiting " << name << " ... (CPU time: " <<
      elapsed_time << " ms)" << endl;
}

void PrintHelp() {
  using std::cout; using std::endl;
  cout << "The input expects elements of the following grammar: " << endl;
  cout << "<FORMULA> ::= ~ <FORMULA> | ( <FORMULA> <2> <FORMULA> ) | " <<
      "A <VARIABLE> <FORMULA>" << endl <<  "            | " <<
      "<PREDICATE> \"(\" <TERM-LIST> \")\" | <TRUE> | <FALSE>" << endl;

  cout << "<TERM-LIST> ::= <TERM> | <TERM> , <TERM-LIST>" << endl;
  cout << "<TERM> ::= <CONSTANT> | <VARIABLE> | <FUNCTION>"
      " \"(\" <TERM-LIST> \")\"" <<
      endl;
  cout << "<2> ::= & | \"|\" | -> | > | <- | < | ==" << endl;
  cout << "<VARIABLE> ::= [a-z]" << endl;
  cout << "<CONSTANT> ::= \"[a-zA-Z0-9]*\"" << endl;
  cout << "<FUNCTION> ::= [a-z][a-zA-Z0-9]*" << endl;
  cout << "<PREDICATE> ::= [A-Z]+" << endl;
  cout << "<TRUE> ::= 1 | true" << endl;
  cout << "<FALSE> ::= 0 | false" << endl;
  cout << "Available commands:" << endl;
  cout << "\"(\" <TERM-LIST> \")\" - defines domain" << endl;
  cout << "+ <CONSTANT> - adds the specified constant from the domain" << endl;
  cout << "- <CONSTANT> - removes the specified constant from the domain" << endl;
  cout << "# <FUNCTION> \"(\" <TERM-LIST> \")\" <CONSTANT>"
      "\n\t- defines the value of a function named <FUNCTION>" << endl;
  cout << "# <PREDICATE> \"(\" <TERM-LIST> \")\" (<TRUE> | <FALSE>)"
      "\n\t- defines the value of a predicate named <PREDICATE>" << endl;
  cout << "? <FORMULA>" << endl;
  cout << "(See test-data/ for examples)" << endl;
}

int main(int argc, char** argv) {
  ShowExample(example1::Show, "example1");
  ShowExample(example2::Show, "example2");
  ShowExample(example3::Show, "example3");
  ShowExample(example4::Show, "example4");

  // run on custom input
  PrintHelp();
  Interpretation s; ProcessQueries(std::cin, &s);

  return 0;
}
#endif

