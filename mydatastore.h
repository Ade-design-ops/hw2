#ifndef MyDATASTORE_H
#define MyDATASTORE_H

#include "datastore.h"
#include <map>
#include <set>
#include <vector>
#include <string>
#include <iostream>

class MyDataStore :public DataStore{
public:
  MyDataStore();
  virtual ~MyDataStore();

  void addProduct(Product* p);
  void addUser(User* u);
  std::vector<Product*> search(std::vector<std::string>& terms, int type);
  void dump(std::ostream& ofile);

  bool hasUser(const std::string& username) const;
  void addToCart(const std::string& username, Product* p);
  void viewCart(const std::string& username);
  void buyCart(const std::string& username);

private:
  std::set<Product*> products_;
  std::map<std::string, std::set<Product*> > index_;
  std::map<std::string, User*> users_;
  std::map<std::string, std::vector<Product*> > carts_;

};
#endif