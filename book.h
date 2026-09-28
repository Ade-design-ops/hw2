#ifndef BOOK_H
#define BOOK_H
#include <iostream>
#include <string>
#include <set>
#include "product.h"
using namespace std;

class Book: public Product{
public:
  Book(const string category, const string name, double price, int qty,
      const string isbn, const string author);
  virtual ~Book();
  std::set<std::string> keywords() const;
  std::string displayString() const;
  void dump(std::ostream& os)const;

  private:
  std::string isbn_;
  std::string author_;

};
#endif