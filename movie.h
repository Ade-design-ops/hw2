#ifndef MOVIE_H
#define MOVIE_H
#include <string>
#include <set>
#include <iostream>
#include "product.h"
using namespace std;


class Movie : public Product{
public:
  Movie(const string category, const string name, double price, int qty,
        const string genre, const string rating);
  
  virtual ~Movie();

  std::set<std::string>keywords() const;
  std::string displayString() const;
  void dump(std::ostream& os) const;

private:
  std::string genre_;
  std::string rating_;

};
#endif