#ifndef CLOTHING_H
#define CLOTHING_H

#include <iostream>
#include <string>
#include <set>
#include "product.h"
using namespace std;

class Clothing : public Product{
  public:
    Clothing(const string category, const string name, double price, int qty,
            const string size, const string brand);

    virtual ~Clothing();

    std::set<std::string> keywords()const;
    std:: string displayString() const;
    void dump(std::ostream& os)const;

  private:
    std::string size_;
    std::string brand_; 
};
#endif
