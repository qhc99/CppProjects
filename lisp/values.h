//
// Created by QC on 2023-01-23.
//

#ifndef DEV_QHC_CPP_PROJECTS_VALUES_H
#define DEV_QHC_CPP_PROJECTS_VALUES_H

#include "exceptions.h"
#include <complex>
#include <functional>
#include <memory>
#include <string>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include <utility>

using std::string, std::shared_ptr, std::unordered_map;

class Value {
public:
  virtual ~Value() = default;

  virtual string to_string() = 0;
};

class Int : public Value {
public:
  int val{};

  inline Int(int v) : val(v) {} // NOLINT(google-explicit-constructor)

  inline operator int() const { // NOLINT(google-explicit-constructor)
    return val;
  }

  inline string to_string() override { return std::to_string(val); }
};

class Double : public Value {
public:
  double val{};

  inline Double(double d) : val(d) {} // NOLINT(google-explicit-constructor)

  inline operator double() const { // NOLINT(google-explicit-constructor)
    return val;
  }

  inline string to_string() override { return std::to_string(val); }
};

class Complex : public Value {
public:
  std::complex<double> val{};

  inline Complex(std::complex<double> v)
      : val(v) {} // NOLINT(google-explicit-constructor)

  inline
  operator std::complex<double>() const { // NOLINT(google-explicit-constructor)
    return val;
  }

  inline string to_string() override {
    return std::to_string(val.real()) + " + " + std::to_string(val.imag()) +
           "j";
  }
};

class Bool : public Value {
public:
  bool val{};

  inline Bool(bool b) : val{b} {} // NOLINT(google-explicit-constructor)

  inline operator bool() const { // NOLINT(google-explicit-constructor)
    return val;
  }

  inline string to_string() override { return std::to_string(val); }
};

class Nil : public Value {
public:
  inline string to_string() override { return "#Nil"; }
};

const shared_ptr<Nil> NIL{};

class String : public Value {
public:
  string val{};

  inline String() = default;

  inline String(std::string str)
      : val(std::move(str)) {} // NOLINT(google-explicit-constructor)

  inline operator string() const { // NOLINT(google-explicit-constructor)
    return val;
  }

  inline String(const String &other) {
    if (this != &other) {
      this->val = other.val;
    }
  }

  inline String(String &&other) noexcept {
    if (this != &other) {
      this->val = std::move(other.val);
    }
  }

  inline String &operator=(const String &other) {
    if (this != &other) {
      this->val = other.val;
    }
    return *this;
  }

  inline String &operator=(String &&other) noexcept {
    if (this != &other) {
      this->val = std::move(other.val);
    }
    return *this;
  }

  inline bool operator==(const String &p) const { return val == p.val; }

  inline string to_string() override { return val; }
};

inline std::ostream &operator<<(std::ostream &out, const String &str) {
  out << str.val;
  return out;
}

class Symbol : public Value {
public:
  string val{};

  inline Symbol() = default;

  inline explicit Symbol(string str) : val(std::move(str)) {}

  inline Symbol(const Symbol &other) {
    if (&other != this) {
      this->val = other.val;
    }
  };

  inline Symbol(Symbol &&other) noexcept {
    if (&other != this) {
      this->val = std::move(other.val);
    }
  };

  inline Symbol &operator=(const Symbol &other) {
    if (&other != this) {
      this->val = other.val;
    }
    return *this;
  }

  inline Symbol &operator=(Symbol &&other) noexcept {
    if (&other != this) {
      this->val = std::move(other.val);
    }
    return *this;
  }

  inline bool operator==(const Symbol &other) const { return val == other.val; }

  inline bool operator!=(const Symbol &other) const { return val != other.val; }

  inline string to_string() override { return val; }
};

inline std::ostream &operator<<(std::ostream &out, const Symbol &sym) {
  out << "Symbol(" << sym.val << ")";
  return out;
}

namespace std {
template <> struct hash<String> {
  inline auto operator()(const String &xyz) const -> size_t {
    return hash<string>{}(xyz.val);
  }
};

template <> struct hash<Symbol> {
  inline auto operator()(const Symbol &xyz) const -> size_t {
    return hash<string>{}(xyz.val);
  }
};
} // namespace std

namespace SYMBOLS {
const Symbol QUOTE_SYM{"quote"};
const Symbol IF_SYM{"if"};
const Symbol SET_SYM{"set!"};
const Symbol DEFINE_SYM{"define"};
const Symbol LAMBDA_SYM{"lambda"};
const Symbol BEGIN_SYM{"begin"};
const Symbol DEFINE_MACRO_SYM{"define-macro"};
const Symbol QUASI_QUOTE_SYM{"quasi-quote"};
const Symbol UNQUOTE_SYM{"unquote"};
const Symbol UNQUOTE_SPLICING_SYM{"unquote-splicing"};
const Symbol EOF_SYM{"#<symbol-eof>"};
const std::unordered_map<string, Symbol> QUOTES_MAP = {
    {"'", QUOTE_SYM},
    {"`", QUASI_QUOTE_SYM},
    {",", UNQUOTE_SYM},
    {",@", UNQUOTE_SPLICING_SYM},
};

const Symbol APPEND_SYM{"append"};
const Symbol CONS_SYM{"cons"};
const Symbol LET_SYM{"let"};
} // namespace SYMBOLS

void copy_from(shared_ptr<Value> &ptr, const shared_ptr<Value> &val);

class Pair : public Value {
public:
  shared_ptr<Value> car{NIL};
  shared_ptr<Value> cdr{NIL};

  static inline bool all_match(shared_ptr<Pair> p,
                               std::function<bool(shared_ptr<Value>)> pred) {
    shared_ptr<Value> ptr{p};
    while (typeid(*ptr) == typeid(Pair)) {
      if (!pred(std::dynamic_pointer_cast<Pair>(ptr)->car)) {
        return false;
      }
    }
    return true;
  }

  static inline shared_ptr<Pair>
  map(shared_ptr<Pair> p,
      std::function<shared_ptr<Value>(shared_ptr<Value>)> m) {
    shared_ptr<Pair> ret{nullptr};
    shared_ptr<Value> tail{nullptr};
    shared_ptr<Value> ptr{p};
    while (typeid(*ptr) == typeid(Pair)) {
      if (ret == nullptr) {
        ret = std::make_shared<Pair>(m(std::dynamic_pointer_cast<Pair>(ptr)->car));
        tail = ret;
      }
      else{
        auto tail_pair{std::dynamic_pointer_cast<Pair>(tail)};
        tail_pair->cdr = std::make_shared<Pair>(m(std::dynamic_pointer_cast<Pair>(ptr)->car));
        tail = tail_pair->cdr;
      }
    }
    return std::move(ret);
  }

  inline Pair(shared_ptr<Value> car, shared_ptr<Value> cdr) {
    this->car = std::move(car);
    this->cdr = std::move(cdr);
  }

  inline Pair(shared_ptr<Value> car) { this->car = std::move(car); }

  inline int lenth() {
    int len{1};
    shared_ptr<Value> p{cdr};
    while (typeid(*p) == typeid(Pair)) {
      len++;
      p = std::dynamic_pointer_cast<Pair>(p)->cdr;
    }
    return len;
  }

  inline ~Pair() override = default;

  inline Pair(const Pair &other) {
    if (&other != this) {
      copy_from(this->car, other.car);
      copy_from(this->cdr, other.cdr);
    }
  }

  inline Pair(Pair &&other) noexcept {
    if (&other != this) {
      this->car = other.car;
      this->cdr = other.cdr;
      other.car = nullptr;
      other.cdr = nullptr;
    }
  }

  inline Pair &operator=(const Pair &other) {
    if (&other != this) {
      copy_from(this->car, other.car);
      copy_from(this->cdr, other.cdr);
    }
    return *this;
  }

  inline Pair &operator=(Pair &&other) noexcept {
    if (&other != this) {
      this->car = other.car;
      this->cdr = other.cdr;
      other.car = nullptr;
      other.cdr = nullptr;
    }
    return *this;
  }

  inline string to_string() override {
    return string{"( "} + car->to_string() + " . " + cdr->to_string() + " )";
  }
};

#endif // DEV_QHC_CPP_PROJECTS_VALUES_H
