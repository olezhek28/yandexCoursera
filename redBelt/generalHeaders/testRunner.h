#pragma once

#include <sstream>
#include <stdexcept>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream& operator << (ostream& __assert_equal_private_os, const vector<T>& s) {
  __assert_equal_private_os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      __assert_equal_private_os << ", ";
    }
    first = false;
    __assert_equal_private_os << x;
  }
  return __assert_equal_private_os << "}";
}

template <class T>
ostream& operator << (ostream& __assert_equal_private_os, const set<T>& s) {
  __assert_equal_private_os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      __assert_equal_private_os << ", ";
    }
    first = false;
    __assert_equal_private_os << x;
  }
  return __assert_equal_private_os << "}";
}

template <class K, class V>
ostream& operator << (ostream& __assert_equal_private_os, const map<K, V>& m) {
  __assert_equal_private_os << "{";
  bool first = true;
  for (const auto& kv : m) {
    if (!first) {
      __assert_equal_private_os << ", ";
    }
    first = false;
    __assert_equal_private_os << kv.first << ": " << kv.second;
  }
  return __assert_equal_private_os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
  if (!(t == u)) {
    ostringstream __assert_equal_private_os;
    __assert_equal_private_os << "Assertion failed: " << t << " != " << u;
    if (!hint.empty()) {
       __assert_equal_private_os << " hint: " << hint;
    }
    throw runtime_error(__assert_equal_private_os.str());
  }
}

inline void Assert(bool b, const string& hint) {
  AssertEqual(b, true, hint);
}

class TestRunner {
public:
  template <class TestFunc>
  void RunTest(TestFunc func, const string& test_name) {
    try {
      func();
      cerr << test_name << " OK" << endl;
    } catch (exception& e) {
      ++fail_count;
      cerr << test_name << " fail: " << e.what() << endl;
    } catch (...) {
      ++fail_count;
      cerr << "Unknown exception caught" << endl;
    }
  }

  ~TestRunner() {
    if (fail_count > 0) {
      cerr << fail_count << " unit tests failed. Terminate" << endl;
      exit(1);
    }
  }

private:
  int fail_count = 0;
};

#define ASSERT_EQUAL(x, y) {            \
  ostringstream __assert_equal_private_os;                     \
  __assert_equal_private_os << #x << " != " << #y << ", "      \
    << __FILE__ << ":" << __LINE__;     \
  AssertEqual(x, y, __assert_equal_private_os.str());          \
}

#define ASSERT(x) {                     \
  ostringstream __assert_equal_private_os;                     \
  __assert_equal_private_os << #x << " is false, "             \
    << __FILE__ << ":" << __LINE__;     \
  Assert(x, __assert_equal_private_os.str());                  \
}

#define RUN_TEST(tr, func) \
  tr.RunTest(func, #func)